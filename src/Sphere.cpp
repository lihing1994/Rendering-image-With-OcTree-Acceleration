//
//  Sphere.cpp
//  
//
//  Created by HINGLI on 10/1/20.
//

#include "Sphere.h"
Sphere::Sphere(glm::vec3 p, float r, ofColor diffuse,bool isReflectable)
{
    _position = p;
    _diffuseColor = diffuse;
    this->_radius = r;
    _specularColor = ofColor::white;
    _is_reflectable = isReflectable;
    _is_subDivideable = false;
}
void Sphere::draw()
{
    ofSetColor(this->_diffuseColor);
    ofDrawSphere(_position, this->_radius);
    ofNoFill();
    //std::vector<glm::vec3> range = this->getBound();
    //ofDrawBox(this->_position, range[1].x-range[0].x, range[1].y-range[0].y, range[1].z-range[0].z);
    ofFill();
    ofSetColor(ofColor::white);
    
}
Sphere::~Sphere()
{}
bool Sphere::intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal)
{
    return glm::intersectRaySphere(ray.getPoint(), ray.getDirecton(), _position, this->_radius, point, normal);
}
float Sphere::getRadius()
{
    return this->_radius;
}
// From lecture note. 
float Sphere::sdf(const glm::vec3 & pos)
{
    return glm::length(pos-this->_position) - this->_radius;
}
std::vector<glm::vec3> Sphere::getBound(){
    std::vector<glm::vec3> result;
    glm::vec3 min = this->_position - this->_radius;
    glm::vec3 max = this->_position + this->_radius;
    result.push_back(min);
    result.push_back(max);
    return result;
}
