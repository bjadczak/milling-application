//
// Created by Bartosz Jadczak on 09/10/2024.
//

#ifndef MILLINGOBJECT_H
#define MILLINGOBJECT_H

#include "../mesh/mesh.h"



class MillingObject {

    float width;
    float depth;
    float height;

    std::unique_ptr<Mesh> objectMesh;

    void generateMesh();

public:
    explicit MillingObject();

    void render(int instanceCount);

};



#endif //MILLINGOBJECT_H
