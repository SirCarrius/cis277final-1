#pragma once
#include <QList>
#include <scene/camera.h>
#include "terrain/terrain.h"
#include "point3.h"
#include <scene/geometry/chunk.h>
#include "generators/lparser.h"
#include <QOpenGLTexture>


class Scene {
    // Our entire world is 64 by 64 chunks
    static const int WORLD_DIM = 64;

public:
    Scene();
    QOpenGLTexture* texture;
    //void CreateChunkScene();
    void CreateNewChunks();
    void CreateNewChunks(Point UL, Point LR);
    void shift(int dx, int dy, int dz);

    Chunk* getContainingChunk(Point3 p) const;
    OctNode* getContainingNode(Point3 p) const;
    Point3 worldToChunk(Point3 p);
    void voxelize(const QVector<LPair_t> &pairs, const Point3 &pt);
    void bresenham(const glm::vec4 &p1, const glm::vec4 &p2);
    bool isFilled(Point3 p);
    void parseImage(QImage image, glm::vec3 eye);

    glm::ivec3 dimensions;
    glm::vec3 origin;
    Terrain terrain;
    OctNode* octree;

    int num_chunks;

private:
    void addVoxel(QSet<OctNode *> &set, Point3 &p);
    QMap<Point, float> heightmap;
};
