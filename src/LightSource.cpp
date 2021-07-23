//
//  LightSource.cpp
//  
//
//  Created by HINGLI on 10/10/20.
//

#include "LightSource.h"
LightSource::LightSource()
{
    _position = glm::vec3(0,10,0);
    _diffuseColor = ofColor::white;
    _specularColor = ofColor::white;
    this->_light_point_color = ofColor::lightGray;
    this->_intensity = 1;
    this->_is_part_of_area_light = false;
    this->_m = glm::translate(glm::mat4(1.0f), _position);
    this->_M = glm::rotate(this->_m, glm::radians(0.0f), glm::vec3(1,0,0));
}
LightSource::LightSource(glm::vec3 pos, float intensity,ofColor color,float power)
{
    _position = pos;
    _specularColor = ofColor::white;
    this->_light_point_color = color;
    _diffuseColor = color;
    this->_intensity = intensity;
    this->_power = 1000;
    this->_is_part_of_area_light = false;
    this->_m = glm::translate(glm::mat4(1.0f), _position);
    this->_M = glm::rotate(this->_m, glm::radians(0.0f), glm::vec3(1,0,0));
}
LightSource::~LightSource()
{
    
}
void LightSource::draw()
{
    ofSetColor(_diffuseColor);
    ofDrawSphere(_position, 0.1);
    ofSetColor(ofColor::white);
}
bool LightSource::intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal)
{
    return false;
}
float LightSource::getIntensity()
{
    return this->_intensity;
}
float LightSource::getPower()
{
    return this->_power;
}
void LightSource::setPower(int power)
{
    this->_power = power;
}
void LightSource::setIntensity(int intensity)
{
    this->_intensity = intensity;
}
bool LightSource::isSpotLight()
{
    return false;
}
bool LightSource::isPointWithinIlluminatedArea(glm::vec3 point)
{
    // Given that we conisder light source as point light
    // we don't need to check it at all.
    return true;
}
void LightSource::setSpotLightAngle(int angle,int spotLightIndex)
{
    // We did nothing for a point light
    return;
}
void LightSource::setSpotLightPosition(glm::vec3 pos,int spotLightIndex)
{
    // We did nothing for a point light
    return;
}
void LightSource::setSpotLightIndex(int spotLightIndex)
{
    // We did nothing for a point light
    return;
}
void LightSource::setAreaLightIndex(int areaLightIndex)
{
    // We did nothing for a point light
    return;
}
void LightSource::setAreaLightPosition(glm::vec3 pos,int spotLightIndex)
{
    // We did nothing for a point light
    return;
}
void LightSource::setAreaLightAngle(int angle,int spotLightIndex)
{
    // We did nothing for a point light
    return;
}
bool LightSource::isAreaLight()
{
    return false;
}
std::vector<LightSource *> * LightSource::getLightList()
{
    return nullptr;
}
glm::vec3 LightSource::getAreaLightNormal()
{
    return glm::vec3(0,0,0);
}
float LightSource::getDensity()
{
    return 1.0f;
}
void LightSource::setIsPartOfAreaLight(bool isPartOfAreaLigth)
{
    this->_is_part_of_area_light = isPartOfAreaLigth;
}
bool LightSource::getIsPartOfAreaLight()
{
    return this->_is_part_of_area_light;
}
glm::vec3 LightSource::getPosition()
{
    if(this->_is_part_of_area_light) return this->_M * glm::vec4(_position,1.0f);
    else return this->_position;
}
void LightSource::setCombineMatrix(glm::mat4 M)
{
    this->_M = M;
}

