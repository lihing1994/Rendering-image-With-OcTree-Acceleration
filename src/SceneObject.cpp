//
//  SceneObject.cpp
//  
//
//  Created by HINGLI on 10/1/20.
//

#include "SceneObject.h"
SceneObject::SceneObject()
{
    this->_position = glm::vec3(0, 0, 0);
    this->_diffuseColor = ofColor::grey;
    this->_specularColor = ofColor::lightGray;
    this->_is_reflectable = false;
    this->_is_subDivideable = false;
}
SceneObject::SceneObject(glm::vec3 pos,ofColor diffColor, ofColor speColor)
{
    this->_position = pos;
    this->_diffuseColor = diffColor;
    this->_specularColor = speColor;
    this->_is_reflectable = false;
    this->_is_subDivideable = false;
}
bool SceneObject::intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal)
{
    return false;
}
SceneObject::~SceneObject()
{
    
}
ofColor SceneObject::getDiffuseColor()
{
    return this->_diffuseColor;
}
glm::vec3 SceneObject::getPosition()
{
    return this->_position;
}
ofColor SceneObject::getSpecularColor()
{
    return this->_specularColor;
}
bool SceneObject::isFloorPlane()
{
    return false;
}
glm::vec2 SceneObject::getTexterPixel(glm::vec3 point)
{
    return glm::vec2(point.x,point.z);
}
ofImage* SceneObject::getFloorPlaneTexter()
{
    return nullptr;
}
bool SceneObject::getReflectable()
{
    return this->_is_reflectable;
}
bool SceneObject::isMeshObj()
{
    return false; 
}
float SceneObject::sdf(const glm::vec3 & pos)
{
    return std::numeric_limits<float>::min();
}
glm::vec3 SceneObject::_infinte_repetition(glm::vec3 pos, glm::vec3 period_3d){
    glm::vec3 result = (pos + 0.5 * period_3d);
    result = glm::mod(result,period_3d);
    result -= 0.5 * period_3d;
    return result;
}
std::vector<glm::vec3> SceneObject::getBound(){
    std::vector<glm::vec3> result;
    result.push_back(glm::vec3(0,0,0));
    result.push_back(glm::vec3(0,0,0));
    return result;
}
void SceneObject::setDiffuseColor(ofColor diffuseColor){
    this->_diffuseColor = diffuseColor;
}
