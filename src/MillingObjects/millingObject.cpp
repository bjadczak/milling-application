//
// Created by Bartosz Jadczak on 09/10/2024.
//

#include "millingObject.h"

#include "../QuadUtils.h"

void MillingObject::generateMesh() {
}

MillingObject::MillingObject(): width(15), depth(15), height(5) {
    generateMesh();
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    vertices.push_back(Vertex{});
    objectMesh = std::make_unique<Mesh>(Mesh(vertices, indices, GL_FILL, GL_POINTS));
}

void MillingObject::render(int instanceCount) {
    objectMesh->Draw(instanceCount);
}
