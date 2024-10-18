//
// Created by Bartosz Jadczak on 18/10/2024.
//

#ifndef MILL_H
#define MILL_H

#include "../shader/shaderProgram.h"

#include <vector>

enum MillType {
    Flat,
    Spherical
};

class Mill {
    MillType type;
    float height;
    float radius;
    glm::vec3 position;
    float velocity;
    float maxDescendAngle;
    float minHeight;

    std::vector<glm::vec3> path;


public:
    Mill(float height, float radius, glm::vec3 position, float velocity, float minAngleDescend, float minHeight);

    void setPath(std::vector<glm::vec3> newPath);
    void setType(MillType newType);
    void setHeight(float newHeight);
    void setRadius(float newRadius);
};



#endif //MILL_H
