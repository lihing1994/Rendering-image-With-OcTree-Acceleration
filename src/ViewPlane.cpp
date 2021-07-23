//
//  ViewPlane.cpp
//  
//
//  Created by HINGLI on 10/1/20.
//

#include "ViewPlane.h"
ViewPlane::ViewPlane(glm::vec2 p0, glm::vec2 p1) {
    this->_min = p0;
    this->_max = p1;
    _is_subDivideable = false;
}
ViewPlane::ViewPlane()
{
    this->_min = glm::vec2(-18, -12);
    this->_max = glm::vec2(18, 12);
    _position = glm::vec3(0, 0, 5);
    normal = glm::vec3(0, 0, 1);
    _is_subDivideable = false;
}
ViewPlane::~ViewPlane()
{
    
}
// Convert (u, v) to (x, y, z)
// We assume u,v is in [0, 1]
glm::vec3 ViewPlane::toWorld(float u, float v) {
    float w = width();
    float h = height();
    return (glm::vec3((u * w) + this->_min.x, (v * h) + this->_min.y, _position.z));
}
void ViewPlane::setSize(glm::vec2 min, glm::vec2 max)
{
    this->_min = min;
    this->_max = max;
}
float ViewPlane::getAspect()
{
    return width() / height();
}
void ViewPlane::draw()
{
    ofDrawRectangle(glm::vec3(this->_min.x, this->_min.y, _position.z), width(), height());
}
float ViewPlane::width()
{
    return (this->_max.x - this->_min.x);
}
float ViewPlane::height()
{
    return (this->_max.y - this->_min.y);
}
glm::vec2 ViewPlane::topLeft()
{
    return glm::vec2(this->_min.x, this->_max.y);
}
glm::vec2 ViewPlane::topRight()
{
    return this->_max;
}
glm::vec2 ViewPlane::bottomLeft()
{
    return this->_min;
}
glm::vec2 ViewPlane::bottomRight()
{
    return glm::vec2(this->_max.x, this->_min.y);
}
