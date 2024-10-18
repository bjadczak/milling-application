//
// Created by Bartosz Jadczak on 18/10/2024.
//

#include "mill.h"
#include "../alghorithm/Bresenham.h"

Mill::Mill(float height, float radius, glm::vec3 position, float velocity, float minAngleDescend, float minHeight) {
    type = Spherical;
    this->height = height;
    this->radius = radius;
    this->position = position;
    this->velocity = velocity;
    this->maxDescendAngle = minAngleDescend;
    this->minHeight = minHeight;

}

void Mill::setPath(std::vector<glm::vec3> newPath) {
    path = std::move(newPath);
}

void Mill::setType(MillType newType) {
    type = newType;
}
void Mill::setHeight(float newHeight) {
    height = newHeight;
}

void Mill::setRadius(float newRadius) {
    radius = newRadius;
}
