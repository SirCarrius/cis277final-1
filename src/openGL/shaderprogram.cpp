#include "shaderprogram.h"
#include <la.h>


void ShaderProgram::create(const char *vertfile, const char *fragfile)
{
    prog.addShaderFromSourceFile(QOpenGLShader::Vertex  , vertfile);
    prog.addShaderFromSourceFile(QOpenGLShader::Fragment, fragfile);
    prog.link();

    attrPos = prog.attributeLocation("vs_Pos");
    attrNor = prog.attributeLocation("vs_Nor");
    attrCol = prog.attributeLocation("vs_Col");
    attrUV = prog.attributeLocation("vs_uv");
    unifModel      = prog.uniformLocation("u_Model");
    unifModelInvTr = prog.uniformLocation("u_ModelInvTr");
    unifViewProj   = prog.uniformLocation("u_ViewProj");
    //equivalent to GLint unifUV = glGetUniformLocation(program, "myTexture");
    unifUV = prog.uniformLocation("myTexture");
    unifTime = prog.uniformLocation("timer");

}

void ShaderProgram::setModelMatrix(const glm::mat4 &model)
{
    prog.bind();

    if (unifModel != -1) {
        prog.setUniformValue(unifModel, la::to_qmat(model));
    }

    if (unifModelInvTr != -1) {
        glm::mat4 modelinvtr = glm::transpose(model);
        modelinvtr = glm::inverse(glm::transpose(model));
        prog.setUniformValue(unifModelInvTr, la::to_qmat(modelinvtr));
    }
}

void ShaderProgram::setViewProjMatrix(const glm::mat4& vp)
{
    prog.bind();

    if(unifViewProj != -1){
        prog.setUniformValue(unifViewProj, la::to_qmat(vp));
    }
}

void ShaderProgram::setTimer(int time) {
    prog.bind();

    if (unifTime != -1) {
        GLint timer = time;
        prog.setUniformValue(unifTime, timer);
    }
}

//set unifUV thing
void ShaderProgram::setUVImage(QOpenGLTexture* texture) {
    //equivalent to calling glUseProgram
    prog.bind();

    textSampler = texture;
    if (unifUV != -1) {
        glActiveTexture(GL_TEXTURE0);

        //equivalent to this: glUniform1i(unifUV, 0);
        textSampler->create();
        textSampler->setWrapMode(QOpenGLTexture::Repeat);
        textSampler->setMinificationFilter(QOpenGLTexture::Nearest);
        textSampler->setMagnificationFilter(QOpenGLTexture::Nearest);
        textSampler->bind(0);
        GLuint ID = textSampler->textureId();

        prog.setUniformValue(unifUV, 0);

        glBindSampler(textSampler->textureId(), unifUV);
    }
}

// This function, as its name implies, uses the passed in GL widget
void ShaderProgram::draw(GLWidget277 &f, Drawable &d)
{
    prog.bind();

    // Each of the following blocks checks that:
    //   * This shader has this attribute, and
    //   * This Drawable has a vertex buffer for this attribute.
    // If so, it binds the appropriate buffers to each attribute.

    if (attrPos != -1 && d.bindPos()) {
        prog.enableAttributeArray(attrPos);
        f.glVertexAttribPointer(attrPos, 3, GL_FLOAT, false, 0, NULL);
    }

    if (attrNor != -1 && d.bindNor()) {
        prog.enableAttributeArray(attrNor);
        f.glVertexAttribPointer(attrNor, 3, GL_FLOAT, false, 0, NULL);
    }

    if (attrCol != -1 && d.bindCol()) {
        prog.enableAttributeArray(attrCol);
        f.glVertexAttribPointer(attrCol, 3, GL_FLOAT, false, 0, NULL);
    }

    //ADDED UV STUFF
    if (attrUV != -1 && d.bindUV()) {
        prog.enableAttributeArray(attrUV);
        f.glVertexAttribPointer(attrUV, 4, GL_FLOAT, false, 0, NULL);
    }

    // Bind the index buffer and then draw shapes from it.
    // This invokes the shader program, which accesses the vertex buffers.
    d.bindIdx();
    if(textSampler != nullptr)
    {
        textSampler->bind();
    }
    f.glDrawElements(d.drawMode(), d.elemCount(), GL_UNSIGNED_INT, 0);

    if (attrPos != -1) prog.disableAttributeArray(attrPos);
    if (attrNor != -1) prog.disableAttributeArray(attrNor);
    if (attrCol!= -1) prog.disableAttributeArray(attrCol);
    if (attrUV != -1) prog.disableAttributeArray(attrUV);

    f.printGLErrorLog();
}
