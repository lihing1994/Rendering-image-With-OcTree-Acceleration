//
//  SpotLightsource.cpp
//  
//
//  Created by HINGLI on 10/15/20.
//

#include "SpotLightSource.h"
//Member Initialization list
SpotLightSource::SpotLightSource(glm::vec3 pos, float intensity,float angle,glm::vec3 pointTo,ofColor color) : LightSource(pos,intensity)
{
    this->_angle = angle;
    this->_direction = glm::normalize(pointTo - pos);
    this->_point_to = pointTo;
    this->_spot_light_image.setPosition(_position);
    this->_spot_light_image.setRadius(0.5f);
    this->_spot_light_image.setHeight(0.5f);
    this->_spot_light_index = 0;
    _specularColor = color;
}
void SpotLightSource::setAngle(float angle)
{
    this->_angle = angle;
}
float SpotLightSource::getAngle()
{
    return this->_angle;
}
void SpotLightSource::draw()
{
    ofSetColor(_specularColor);
    ofDrawCircle(_position, 0.1f);
    ofDrawArrow(_position, _position + _direction*2);
    ofSetColor(ofColor::white);
}
void SpotLightSource::setDirection(glm::vec3 direction)
{
    this->_direction = direction;
}
glm::vec3 SpotLightSource::getDirection()
{
    return this->_direction;
}
bool SpotLightSource::isSpotLight()
{
    return true;
}
bool SpotLightSource::isPointWithinIlluminatedArea(glm::vec3 point)
{
    glm::vec3 ray_light_to_point = point - _position;
    // a dot b = |a||b|cosTheta ==> cosTheta = (a dot b)/(|a||b|)
    // Given that b is direction vector and its length is 1.
    // cosTheta = (a dot b)/(|a|)
    float cos_theta = glm::dot(ray_light_to_point, _direction)/ glm::length(ray_light_to_point);
    float temp_angle = glm::degrees(glm::acos(cos_theta));
    // If the angle between the ray of light point to illumination point and the direction vector
    // is less than beam angle, then the point is within the illumination area.
    if(temp_angle <= this->_angle) return true;
    return false;
}
void SpotLightSource::setSpotLightAngle(int angle,int spotLightIndex)
{
    if(this->_spot_light_index == spotLightIndex)
    {
        this->_angle = angle;
    }
}
void SpotLightSource::setSpotLightPosition(glm::vec3 pos,int spotLightIndex)
{
    if(this->_spot_light_index == spotLightIndex)
    {
        this->_position = pos;
        this->_direction = glm::normalize(_point_to - _position);
    }
}
void SpotLightSource::setSpotLightIndex(int index)
{
    this->_spot_light_index = index;
}
