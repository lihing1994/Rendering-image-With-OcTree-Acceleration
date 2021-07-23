//
//  AreaLight.cpp
//  
//
//  Created by HINGLI on 11/27/20.
//

#include "AreaLight.h"
AreaLight::AreaLight(glm::vec3 pos,glm::vec3 normal,float intensity,float angle ,ofColor color,float length,float width,float density):LightSource(pos, intensity/pow(density, 2), color)
{
    this->_length = length;
    this->_width = width;
    this->_normal = glm::normalize(normal);
    this->_density = density;
    this->_rotate_angle = angle;
    if(this->_normal == glm::vec3(0,1,0)||this->_normal == glm::vec3(0,-1,0)) plane.rotateDeg(-90, 1, 0, 0);
    else if(this->_normal == glm::vec3(1,0,0)||this->_normal == glm::vec3(-1,0,0)) plane.rotateDeg(-90, 0, 1, 0);
    this->_is_updated = false;
    this->_area_light_index = 0;
    this->_intensity_per_light = intensity/pow(density, 2);
    _power =500;
    _m = glm::translate(glm::mat4(1.0f), pos);
    if(this->_normal == glm::vec3(0,1,0)||this->_normal == glm::vec3(0,-1,0)) {
        _M = glm::rotate(this->_m, glm::radians(this->_rotate_angle), glm::vec3(1,0,0));
    }
    else if(this->_normal == glm::vec3(1,0,0)||this->_normal == glm::vec3(-1,0,0)){
        _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(0,0,1));
    }
    else{
        _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(1,0,0));
    }
    this->generate_light_source();
    setIsPartOfAreaLight(true);
}
AreaLight::~AreaLight()
{
    for(int i =0;i<this->_list_light.size();i++) delete this->_list_light.at(i);
    this->_list_light.clear();
}
void AreaLight::draw()
{
    ofDrawArrow(glm::vec3(0,0,0), glm::vec3(5,0,0));
    ofDrawArrow(glm::vec3(0,0,0), glm::vec3(0,5,0));
    ofDrawArrow(glm::vec3(0,0,0), glm::vec3(0,0,5));
    ofSetColor(_diffuseColor);
    plane.setPosition(glm::vec3(0,0,0));
    plane.setWidth(this->_width);
    plane.setHeight(this->_length);
    plane.setResolution(4, 4);
    ofPushMatrix();
    ofMultMatrix(_M);
    plane.draw();
    ofPopMatrix();
    ofSetColor(ofColor::white);
    for(int i=0;i<this->_list_light.size();i++)
    {
        glm::vec3 temp = this->_list_light.at(i)->getPosition();
        ofDrawArrow(temp, temp+this->_normal*2);
    }
}
void AreaLight::generate_light_source()
{
    
    this->_begin_point = glm::vec3(0,0,0);
    float dx = this->_length/this->_density;
    float dy = this->_width/this->_density;
    if(this->_normal == glm::vec3(0,1,0)||this->_normal == glm::vec3(0,-1,0))
    {
        this->_begin_point.x -= dx * (this->_density/2-1);
        this->_begin_point.z -= dy * (this->_density/2-1);
        for(int i=0;i<this->_density;i++)
        {
            for(int j=0;j<this->_density;j++)
            {
                glm::vec3 the_point = _begin_point;
                the_point.x += dx * (j) ;
                the_point.z += dy * (i) ;
                this->_list_light.push_back(new LightSource(the_point,_intensity_per_light,this->_diffuseColor));
                this->_list_light.back()->setIsPartOfAreaLight(true);
                this->_list_light.back()->setCombineMatrix(_M);
            }
           
        }
    }
    else if(this->_normal == glm::vec3(1,0,0)||this->_normal == glm::vec3(-1,0,0))
    {
        this->_begin_point.z -= dx * (this->_density/2-1);
        this->_begin_point.y -= dy * (this->_density/2-1);
        for(int i=0;i<this->_density;i++)
        {
            for(int j=0;j<this->_density;j++)
            {
                glm::vec3 the_point = _begin_point;
                the_point.z += dx * (j) ;
                the_point.y += dy * (i) ;
                this->_list_light.push_back(new LightSource(the_point,_intensity_per_light,this->_diffuseColor));
                this->_list_light.back()->setIsPartOfAreaLight(true);
                this->_list_light.back()->setCombineMatrix(_M);
            }
           
        }
    }
    else if(this->_normal == glm::vec3(0,0,1)||this->_normal == glm::vec3(0,0,-1))
    {
        this->_begin_point.x -= dx * (this->_density/2-1);
        this->_begin_point.y -= dy * (this->_density/2-1);
        for(int i=0;i<this->_density;i++)
        {
            for(int j=0;j<this->_density;j++)
            {
                glm::vec3 the_point = _begin_point;
                the_point.x += dx * (j) ;
                the_point.y += dy * (i) ;
                this->_list_light.push_back(new LightSource(the_point,_intensity_per_light,this->_diffuseColor));
                this->_list_light.back()->setIsPartOfAreaLight(true);
                this->_list_light.back()->setCombineMatrix(_M);
            }
            
        }
    }
}
std::vector<LightSource *> * AreaLight::getLightList()
{
    return &this->_list_light;
}
void AreaLight::setAreaLightIndex(int index)
{
    this->_area_light_index = index;
}
void AreaLight::setAreaLightPosition(glm::vec3 pos,int areaLightIndex)
{
    if(this->_area_light_index == areaLightIndex && this->_position != pos){
        _position = pos;
        _m = glm::translate(glm::mat4(1.0f), pos);
        if(this->_normal == glm::vec3(0,1,0)||this->_normal == glm::vec3(0,-1,0)){
            _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(1,0,0));
        }
        else if(this->_normal == glm::vec3(1,0,0)||this->_normal == glm::vec3(-1,0,0)){
            _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(0,0,1));
        }
        else{
            _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(1,0,0));
        }
        for(int i =0;i<this->_list_light.size();i++) this->_list_light.at(i)->setCombineMatrix(this->_M);
        this->_is_updated = true;
    }
   
}
void AreaLight::setAreaLightAngle(int angle,int areaLightIndex)
{
   
    if( this->_area_light_index == areaLightIndex && this->_rotate_angle != angle ){
        this->_rotate_angle = angle;
        _m = glm::translate(glm::mat4(1.0f), _position);
        if(this->_normal == glm::vec3(0,1,0)||this->_normal == glm::vec3(0,-1,0)){
            _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(1,0,0));
        }
        else if(this->_normal == glm::vec3(1,0,0)||this->_normal == glm::vec3(-1,0,0)){
            _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(0,0,1));
        }
        else{
            _M = glm::rotate(_m,glm::radians(this->_rotate_angle),glm::vec3(1,0,0));
        }
        for(int i =0;i<this->_list_light.size();i++) this->_list_light.at(i)->setCombineMatrix(this->_M);
        this->_is_updated = true;
    }
   
}

bool AreaLight::isAreaLight()
{
    return true;
}

glm::vec3 AreaLight::getAreaLightNormal()
{
    return this->_normal;
}
float AreaLight::getDensity()
{
    return this->_density;
}
