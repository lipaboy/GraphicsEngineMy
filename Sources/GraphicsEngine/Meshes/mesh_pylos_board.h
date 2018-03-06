#ifndef MESH_PYLOS_BOARD_H
#define MESH_PYLOS_BOARD_H

#include "Mesh.h"

namespace PylosGame {

class MeshPylosBoard : public Mesh
{
public:
    MeshPylosBoard(int levelCount = 1);

    virtual void Init();
    virtual void Deinit();

private:
    void InitCubeSimple();
    void InitCubeDetailedStrip();
    void InitCubeDetailedList();

    int m_levelCount;
};

}

#endif // MESH_PYLOS_BOARD_H
