//
//  BoundingBox.cpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 5/13/21.
//

#include "BoundingBox.h"
BoundingBox::BoundingBox(glm::vec3 pos, glm::vec3 min,glm::vec3 max,ofColor color) : SceneObject(pos,ofColor::gray,ofColor::gray){
    this->_range.push_back(min);
    this->_range.push_back(max);
    this->_color = color;
}
bool BoundingBox:: intersect(const Ray &ray){
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    float t0 = 0;
    float t1 = 1000;
    tmin = (this->_range[ray.getSign()[0]].x - ray.getPoint().x) * ray.getInvDirection().x;
    tmax = (this->_range[1-ray.getSign()[0]].x - ray.getPoint().x) * ray.getInvDirection().x;
    tymin = (this->_range[ray.getSign()[1]].y - ray.getPoint().y) * ray.getInvDirection().y;
    tymax = (this->_range[1-ray.getSign()[1]].y - ray.getPoint().y) * ray.getInvDirection().y;
    if ( (tmin > tymax) || (tymin > tmax) )
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    tzmin = (this->_range[ray.getSign()[2]].z - ray.getPoint().z) * ray.getInvDirection().z;
    tzmax = (this->_range[1-ray.getSign()[2]].z - ray.getPoint().z) * ray.getInvDirection().z;
    if ( (tmin > tzmax) || (tzmin > tmax) )
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    return ( (tmin < t1) && (tmax > t0) );
}
void BoundingBox::draw(){
    ofNoFill();
    ofSetColor(this->_color);
    ofDrawBox(this->_position, this->_range[1].x-this->_range[0].x, this->_range[1].y - this->_range[0].y,this->_range[1].z - this->_range[0].z);
    ofSetColor(ofColor::white);
    ofFill();
}
