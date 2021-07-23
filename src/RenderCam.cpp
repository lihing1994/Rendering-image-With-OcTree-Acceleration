//
//  RenderCam.cpp
// 
//
//  Created by HINGLI on 10/1/20.
//

#include "RenderCam.h"

// Get a ray from the current camera position to the (u, v) position on
// the ViewPlane
//
RenderCam::RenderCam()
{
    _position = glm::vec3(0, 5, 20);
    _aim = glm::vec3(0, -1, -1);
}
RenderCam::~RenderCam()
{
    
}
Ray RenderCam::getRay(float u, float v) {
    glm::vec3 pointOnPlane = _view.toWorld(u, v);
    return(Ray(_position, glm::normalize(pointOnPlane - _position)));
}
void RenderCam::draw()
{
    ofDrawBox(_position, 1.0);
}
void RenderCam::setPosition(glm::vec3 pos)
{
    this->_position = pos;
}
glm::vec3 RenderCam::getPosition()
{
    return this->_position;
}
glm::vec3 RenderCam::getAim()
{
    return this->_aim;
}
