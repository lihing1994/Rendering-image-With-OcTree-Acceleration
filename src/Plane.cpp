//
//  Plane.cpp
//  
//
//  Created by HINGLI on 10/1/20.
//

#include "Plane.h"
Plane::Plane()
{
    normal = glm::vec3(0, 1, 0);
    plane.rotateDeg(90, 1, 0, 0);
    this->_floor_plane_texter = nullptr;
    _is_subDivideable = false;
}
Plane::~Plane()
{
    delete _floor_plane_texter;
}
Plane::Plane(glm::vec3 p, glm::vec3 n, ofColor diffuse, float w, float h,ofImage * floorPlaneTexter,bool isReflectable)
{
    _position = p;
    normal = n;
    width = w;
    height = h;
    _diffuseColor = diffuse;
    if(normal == glm::vec3(0,1,0)) plane.rotateDeg(90, 1, 0, 0);
    else if(normal == glm::vec3(1,0,0)) plane.rotateDeg(90, 0, 1, 0);
    else if(normal == glm::vec3(-1,0,0)) plane.rotateDeg(-90, 0,1,0);
    this->_floor_plane_texter = floorPlaneTexter;
    _is_reflectable = isReflectable;
}
// Intersect Ray with Plane
bool Plane::intersect(const Ray &ray, glm::vec3 & point, glm::vec3 & normalAtIntersect) {
    float dist;
    bool insidePlane = false;
    bool hit = glm::intersectRayPlane(ray.getPoint(), ray.getDirecton(), _position, this->normal, dist);
    if (hit) {
        Ray r = ray;
        point = r.evalPoint(dist);
        normalAtIntersect = this->normal;
        glm::vec2 xrange = glm::vec2(_position.x - width / 2, _position.x + width / 2);
        glm::vec2 zrange = glm::vec2(_position.z - height / 2, _position.z + height / 2);
        if (point.x < xrange[1] && point.x > xrange[0] && point.z < zrange[1] && point.z > zrange[0]) {
                insidePlane = true;
        }
    }
    return insidePlane;
}
void Plane::draw()
{
    ofSetColor(_diffuseColor);
    plane.setPosition(_position);
    plane.setWidth(width);
    plane.setHeight(height);
    plane.setResolution(4, 4);
    plane.draw();
    std::vector<glm::vec3> range = this->getBound();
    ofNoFill();
    //if(this->normal == glm::vec3(0,1,0)) ofDrawBox(this->_position, (range[1].x-range[0].x)/2, 1, (range[1].z-range[0].z)/2);
    //else if(this->normal == glm::vec3(1,0,0)|| this->normal == glm::vec3(-1,0,0)) ofDrawBox(this->_position, 1, (range[1].y-range[0].y)/2, (range[1].z-range[0].z)/2);
    //else if(this->normal == glm::vec3(0,0,1)) ofDrawBox(this->_position, (range[1].x-range[0].x)/2,(range[1].y-range[0].y)/2, 1);
    ofFill();
    ofSetColor(ofColor::white);
}
glm::vec3 Plane::getNormal(const glm::vec3 &p)
{
    return this->normal;
}
bool Plane::isFloorPlane()
{
    return true;
}
glm::vec2 Plane::getTexterPixel(glm::vec3 point)
{
    glm::vec2 toReturn;
    float x_in_image;
    float y_in_image;
    // Floor plane.
    if(this->normal == glm::vec3(0,1,0))
    {
        x_in_image = ofMap(point.x, -20, 20, 0, 1000);
        y_in_image = ofMap(point.z, -20, 20, 0, 1000);
        x_in_image = width  * x_in_image - 0.5;
        y_in_image = height * y_in_image - 0.5;
        toReturn.x = fmod(x_in_image,this->_floor_plane_texter->getWidth());
        toReturn.y = fmod(y_in_image,this->_floor_plane_texter->getHeight());
        toReturn.y = this->_floor_plane_texter->getHeight() - 1 - toReturn.y;
    }
    // For wall
    else if(this->normal == glm::vec3(0,0,1))
    {
        x_in_image = ofMap(point.x, -20, 20, 0, 500);
        y_in_image = ofMap(point.y, -20, 20, 0, 500);
        x_in_image = width  * x_in_image - 0.5;
        y_in_image = height * y_in_image - 0.5;
        toReturn.x = fmod(x_in_image,this->_floor_plane_texter->getWidth());
        toReturn.y = fmod(y_in_image,this->_floor_plane_texter->getHeight());
        toReturn.y = this->_floor_plane_texter->getHeight() - 1 - toReturn.y;
    }
    // For left hand side and right hand side walls
    else if(this->normal == glm::vec3(1,0,0)||this->normal == glm::vec3(-1,0,0))
    {
        x_in_image = ofMap(point.z, -20, 20, 0, 500);
        y_in_image = ofMap(point.y, -20, 20, 0, 500);
        x_in_image = width  * x_in_image - 0.5;
        y_in_image = height * y_in_image - 0.5;
        toReturn.x = fmod(x_in_image,this->_floor_plane_texter->getWidth());
        toReturn.y = fmod(y_in_image,this->_floor_plane_texter->getHeight());
        toReturn.y = this->_floor_plane_texter->getHeight() - 1 - toReturn.y;
    }
    return toReturn;
}
ofImage* Plane::getFloorPlaneTexter()
{
    return this->_floor_plane_texter;
}
/*
 sdf function implement by Inigo Quilez
 https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
 */
float Plane::sdf(const glm::vec3 & pos)
{
    return glm::dot(pos-this->_position,this->normal);
}
std::vector<glm::vec3> Plane::getBound(){
    /*
     if(normal == glm::vec3(0,1,0)) plane.rotateDeg(90, 1, 0, 0);
     else if(normal == glm::vec3(1,0,0)) plane.rotateDeg(90, 0, 1, 0);
     else if(normal == glm::vec3(-1,0,0)) plane.rotateDeg(-90, 0,1,0);
     
     */
    std::vector<glm::vec3> result;
    if(this->normal == glm::vec3(0,1,0)){
        glm::vec3 min = this->_position;
        glm::vec3 max = this->_position;
        min.z -= this->width/2;
        min.x -= this->width/2;
        max.x += this->width/2;
        max.z += this->height/2;
        result.push_back(min);
        result.push_back(max);
    }
    else if(normal == glm::vec3(1,0,0) || normal == glm::vec3(-1,0,0)) {
        glm::vec3 min = this->_position;
        glm::vec3 max = this->_position;
        min.z -= this->width/2;
        min.y -= this->height/2;
        max.z += this->width/2;
        max.y += this->height/2;
        result.push_back(min);
        result.push_back(max);
    }
    else if(normal == glm::vec3(0,0,1)){
        glm::vec3 min = this->_position;
        glm::vec3 max = this->_position;
        //min.z -= this->width/2;
        min.x -= this->width/2;
        min.y -= this->height/2;
        max.x += this->width/2;
        max.y += this->height/2;
        result.push_back(min);
        result.push_back(max);
    }
    return result;
}
