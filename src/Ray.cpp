//
//  Ray.cpp
//  
//
//  Created by HINGLI on 10/1/20.
//

#include "Ray.h"
Ray::Ray(glm::vec3 point, glm::vec3 direction)
{
    this->_point = point;
    this->_direction = direction;
    this->_inv_direction.x = 1/direction.x;
    this->_inv_direction.y = 1/direction.y;
    this->_inv_direction.z = 1/direction.z;
    this->_sign.x = (this->_inv_direction.x < 0);
    this->_sign.y = (this->_inv_direction.y < 0);
    this->_sign.z = (this->_inv_direction.z < 0);
}
void Ray::draw(float t)
{
    ofDrawLine(this->_point, this->_point + this->_direction * t);
}
glm::vec3 Ray::evalPoint(float t)
{
    return this->_point+this->_direction*t;
}
glm::vec3 Ray::getPoint() const
{
    return this->_point;
}
glm::vec3 Ray::getDirecton() const
{
    return this->_direction;
}
glm::vec3 Ray::getInvDirection() const
{
    return this->_inv_direction;
}
glm::vec3 Ray::getSign() const{
    return this->_sign;
}
