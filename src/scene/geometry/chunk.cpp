#include "chunk.h"
#include <la.h>

//default constructor
Chunk::Chunk() {}


// Takes in a 16x16x16 list of Textures indicating what the cell is occupied by
// Currently not updated to work with the height variable
Chunk::Chunk(QList<QList<QList<Texture>>> cells) : cells(cells), height(0)
{}

// Empty constructor sets all cells as being EMPTY
Chunk::Chunk(int height) : height(height)
{
    texture = nullptr;
    for (int x = 0; x < 16; x++) {
        QList<QList<Texture>> Xs;
        for (int y = 0; y < 16; y++) {
            QList<Texture> Ys;
            for (int z = 0; z < 16; z++) {
                Ys.append(EMPTY);
            }
            Xs.append(Ys);
        }
        cells.append(Xs);
    }
}

Chunk::~Chunk()
{}

QVector<glm::vec3> Chunk::createChunkVertexPositions()
{
    //DO UV STUFF HERE
    QVector<glm::vec3> positions;
    for (int x = 0; x < cells.size(); x++) {
        for (int y = 0; y < cells.size(); y++) {
            for (int z = 0; z < cells.size(); z++) {
                if (cells[x][y][z] != EMPTY) {
                    // Front face
                    //if (z == cells.size()-1 || !cells[x][y][z+1]) {
                    if (z == cells.size() - 1 || cells[x][y][z+1] == EMPTY) {
                        positions.append(glm::vec3(x+1, y+1, z+1));         // UR
                        positions.append(glm::vec3(x+1, y, z+1));           // LR
                        positions.append(glm::vec3(x, y, z+1));             // LL
                        positions.append(glm::vec3(x, y+1, z+1));           // UL

                        switch (cells[x][y][z]) {
                            case STONE:
                                uvs.push_back(glm::vec4(2/16.f,0,0,0));
                                uvs.push_back(glm::vec4(2/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,0,0,0));
                                break;

                            case WOOD:
                                uvs.push_back(glm::vec4(5/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                break;

                            case GRASS:
                                uvs.push_back(glm::vec4(4/16.f,0,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,0,0,0));
                                break;

                            case WATER:
                                uvs.push_back(glm::vec4(14/16.f,12/16.f,1,0));
                                uvs.push_back(glm::vec4(14/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,12/16.f,1,0));
                                break;

                            case LAVA:
                                uvs.push_back(glm::vec4(14/16.f,14/16.f,1,1));
                                uvs.push_back(glm::vec4(14/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,14/16.f,1,1));
                                break;
                        }
                    }
                    // Right face
                    //if (x == cells.size() - 1 || !cells[x+1][y][z]) {
                    if (x == cells.size() - 1 || cells[x+1][y][z] == EMPTY) {
                        positions.append(glm::vec3(x+1, y+1, z));       // UR
                        positions.append(glm::vec3(x+1, y, z));         // LR
                        positions.append(glm::vec3(x+1, y, z+1));       // LL
                        positions.append(glm::vec3(x+1, y+1, z+1));     // UL

                        //EACH FACE GETS FOUR COORDINATES

                        switch (cells[x][y][z]) {
                            case STONE:
                                uvs.push_back(glm::vec4(2/16.f,0,0,0));
                                uvs.push_back(glm::vec4(2/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,0,0,0));
                                break;

                            case WOOD:
                                uvs.push_back(glm::vec4(5/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                break;

                            case GRASS:
                                uvs.push_back(glm::vec4(4/16.f,0,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,0,0,0));
                                break;
                            case WATER:
                                uvs.push_back(glm::vec4(14/16.f,12/16.f,1,0));
                                uvs.push_back(glm::vec4(14/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,12/16.f,1,0));
                                break;

                            case LAVA:
                                uvs.push_back(glm::vec4(14/16.f,14/16.f,1,1));
                                uvs.push_back(glm::vec4(14/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,14/16.f,1,1));
                                break;
                        }
                    }
                    // Left face
                    if (x == 0 || cells[x-1][y][z] == EMPTY) {
                    //if (x == 0 || cells[x-1][y][z]) {
                        positions.append(glm::vec3(x, y+1, z+1)); // UR
                        positions.append(glm::vec3(x, y, z+1)); // LR
                        positions.append(glm::vec3(x, y, z));       // LL
                        positions.append(glm::vec3(x, y+1, z)); // UL

                        //EACH FACE GETS FOUR COORDINATES

                        switch (cells[x][y][z]) {
                            case STONE:
                                uvs.push_back(glm::vec4(2/16.f,0,0,0));
                                uvs.push_back(glm::vec4(2/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,0,0,0));
                                break;

                            case WOOD:
                                uvs.push_back(glm::vec4(5/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                break;

                            case GRASS:
                                uvs.push_back(glm::vec4(4/16.f,0,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,0,0,0));
                                break;

                            case WATER:
                                uvs.push_back(glm::vec4(14/16.f,12/16.f,1,0));
                                uvs.push_back(glm::vec4(14/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,12/16.f,1,0));
                                break;

                            case LAVA:
                                uvs.push_back(glm::vec4(14/16.f,14/16.f,1,1));
                                uvs.push_back(glm::vec4(14/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,14/16.f,1,1));
                                break;
                        }
                    }
                    // Back face
                    if (z == 0 || cells[x][y][z-1] == EMPTY) {
                      //if (z == 0 || cells[x][y][z-1]) {
                        positions.append(glm::vec3(x, y+1, z)); // UR
                        positions.append(glm::vec3(x, y, z));       // LR
                        positions.append(glm::vec3(x+1, y, z)); // LL
                        positions.append(glm::vec3(x+1, y+1, z)); // UL

                        //EACH FACE GETS FOUR COORDINATES

                        switch (cells[x][y][z]) {
                            case STONE:
                                uvs.push_back(glm::vec4(2/16.f,0,0,0));
                                uvs.push_back(glm::vec4(2/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,0,0,0));
                                break;

                            case WOOD:
                                uvs.push_back(glm::vec4(5/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                break;

                            case GRASS:
                                uvs.push_back(glm::vec4(4/16.f,0,0,0));
                                uvs.push_back(glm::vec4(4/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(3/16.f,0,0,0));
                                break;
                            case WATER:
                                uvs.push_back(glm::vec4(14/16.f,12/16.f,1,0));
                                uvs.push_back(glm::vec4(14/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,12/16.f,1,0));
                                break;

                            case LAVA:
                                uvs.push_back(glm::vec4(14/16.f,14/16.f,1,1));
                                uvs.push_back(glm::vec4(14/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,14/16.f,1,1));
                                break;
                        }
                    }
                    // Top face
                    if (y == cells.size() - 1 || cells[x][y+1][z] == EMPTY) {
                      //if (y == cells.size() - 1 || cells[x][y+1][z]) {
                        positions.append(glm::vec3(x+1, y+1, z)); // UR
                        positions.append(glm::vec3(x+1, y+1, z+1)); // LR
                        positions.append(glm::vec3(x, y+1, z+1)); // LL
                        positions.append(glm::vec3(x, y+1, z)); // UL

                        //EACH FACE GETS FOUR COORDINATES

                        switch (cells[x][y][z]) {
                            case STONE:
                                uvs.push_back(glm::vec4(2/16.f,0,0,0));
                                uvs.push_back(glm::vec4(2/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,0,0,0));
                                break;

                            case WOOD:
                                uvs.push_back(glm::vec4(6/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(6/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,1/16.f,0,0));
                                break;

                            case GRASS:
                                uvs.push_back(glm::vec4(9/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(9/16.f,3/16.f,0,0));
                                uvs.push_back(glm::vec4(8/16.f,3/16.f,0,0));
                                uvs.push_back(glm::vec4(8/16.f,2/16.f,0,0));
                                break;
                            case WATER:
                                uvs.push_back(glm::vec4(14/16.f,12/16.f,1,0));
                                uvs.push_back(glm::vec4(14/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,12/16.f,1,0));
                                break;

                            case LAVA:
                                uvs.push_back(glm::vec4(14/16.f,14/16.f,1,1));
                                uvs.push_back(glm::vec4(14/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,14/16.f,1,1));
                                break;
                        }
                    }
                    // Bottom face
                    if (y == 0 || cells[x][y-1][z] == EMPTY) {
                      //if (y == 0 || cells[x][y-1][z]) {
                        positions.append(glm::vec3(x+1, y, z+1)); // UR
                        positions.append(glm::vec3(x+1, y, z)); // LR
                        positions.append(glm::vec3(x, y, z));       // LL
                        positions.append(glm::vec3(x, y, z+1)); // UL

                        //EACH FACE GETS FOUR COORDINATES
                        switch (cells[x][y][z]) {
                            case STONE:
                                uvs.push_back(glm::vec4(2/16.f,0,0,0));
                                uvs.push_back(glm::vec4(2/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(1/16.f,0,0,0));
                                break;

                            case WOOD:
                                uvs.push_back(glm::vec4(6/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(6/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,2/16.f,0,0));
                                uvs.push_back(glm::vec4(5/16.f,1/16.f,0,0));
                                break;

                            case GRASS:
                                uvs.push_back(glm::vec4(3/16.f,0,0,0));
                                uvs.push_back(glm::vec4(3/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(2/16.f,1/16.f,0,0));
                                uvs.push_back(glm::vec4(2/16.f,0,0,0));
                                break;

                            case WATER:
                                uvs.push_back(glm::vec4(14/16.f,12/16.f,1,0));
                                uvs.push_back(glm::vec4(14/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,13/16.f,1,0));
                                uvs.push_back(glm::vec4(13/16.f,12/16.f,1,0));
                                break;

                            case LAVA:
                                uvs.push_back(glm::vec4(14/16.f,14/16.f,1,1));
                                uvs.push_back(glm::vec4(14/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,15/16.f,1,1));
                                uvs.push_back(glm::vec4(13/16.f,14/16.f,1,1));
                                break;

                        }
                    }
                }
            }
        }
    }
    vertex_count = positions.size();
    return positions;
}

QVector<glm::vec3> Chunk::createChunkVertexNormals()
{
    QVector<glm::vec3> normals;
    for (int x = 0; x < cells.size(); x++) {
        for (int y = 0; y < cells.size(); y++) {
            for (int z = 0; z < cells.size(); z++) {
                if (cells[x][y][z] != EMPTY) {
                    // Front face
                    if (z == cells.size() - 1 || cells[x][y][z+1] == EMPTY) {
                        for (int i = 0; i < 4; i++) {
                            normals.append(glm::vec3(0, 0, 1));
                        }
                    }
                    // Right face
                    if (x == cells.size() - 1 || cells[x+1][y][z] == EMPTY) {
                        for (int i = 0; i < 4; i++) {
                            normals.append(glm::vec3(1, 0, 0));
                        }
                    }
                    // Left face
                    if (x == 0 || cells[x-1][y][z] == EMPTY) {
                        for (int i = 0; i < 4; i++) {
                            normals.append(glm::vec3(-1, 0, 0));
                        }
                    }
                    // Back face
                    if (z == 0 || cells[x][y][z-1] == EMPTY) {
                        for (int i = 0; i < 4; i++) {
                            normals.append(glm::vec3(0, 0, -1));
                        }
                    }
                    // Top face
                    if (y == cells.size() - 1 || cells[x][y+1][z] == EMPTY) {
                        for (int i = 0; i < 4; i++) {
                            normals.append(glm::vec3(0, 1, 0));
                        }
                    }
                    // Bottom face
                    if (y == 0 || cells[x][y-1][z] == EMPTY) {
                        for (int i = 0; i < 4; i++) {
                            normals.append(glm::vec3(0, -1, 0));
                        }
                    }
                }
            }
        }
    }
    return normals;
}

QVector<GLuint> Chunk::createChunkIndices()
{
    QVector<GLuint> indices;
    for (int i = 0; i < vertex_count/4; i++) {
        indices.append(i*4);
        indices.append(i*4+1);
        indices.append(i*4+2);
        indices.append(i*4);
        indices.append(i*4+2);
        indices.append(i*4+3);
    }
    index_count = indices.size();
    return indices;
}


void Chunk::create()
{
    QVector<glm::vec3> positions = createChunkVertexPositions();
    QVector<glm::vec3> normals = createChunkVertexNormals();
    QVector<GLuint> indices = createChunkIndices();
    QVector<glm::vec3> colors;

    const glm::vec3 color = glm::vec3(((float) rand()) / (float) RAND_MAX, ((float) rand()) / (float) RAND_MAX, ((float) rand()) / (float) RAND_MAX);

    for (int i = 0; i < vertex_count; i++) {
        colors.append(color);
    }

    count = index_count;

    bufIdx.create();
    bufIdx.bind();
    bufIdx.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufIdx.allocate(indices.data(), index_count * sizeof(GLuint));

    bufPos.create();
    bufPos.bind();
    bufPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufPos.allocate(positions.data(), vertex_count * sizeof(glm::vec3));

    bufNor.create();
    bufNor.bind();
    bufNor.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufNor.allocate(normals.data(), vertex_count * sizeof(glm::vec3));

    bufCol.create();
    bufCol.bind();
    bufCol.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufCol.allocate(colors.data(), vertex_count * sizeof(glm::vec3));

    bufUV.create();
    bufUV.bind();
    bufUV.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufUV.allocate(uvs.data(), vertex_count * sizeof(glm::vec4));

    uvs.clear();
}
