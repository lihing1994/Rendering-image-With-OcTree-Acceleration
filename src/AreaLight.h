//
//  AreaLight.hpp
//  
//
//  Created by HINGLI on 11/27/20.
//
#pragma once
#include "LightSource.h"
class AreaLight : public LightSource
{
    public:
        AreaLight(glm::vec3 pos = glm::vec3(0,0,0),glm::vec3 normal = glm::vec3(0,1,0),float intensity = 15.0f, float angle = 15.0f, ofColor color = ofColor::white ,float length =10,float width = 10,float density = 10);
        ~AreaLight();
        void draw();
        void setAreaLightIndex(int index);
        void setAreaLightPosition(glm::vec3 pos,int areaLightIndex);
        void setAreaLightAngle(int angle,int areaLightIndex);
        void updateLightSourceList();
        float getDensity();
        bool isAreaLight();
        glm::vec3 getAreaLightNormal();
        std::vector<LightSource *> * getLightList();
    private:
        int _area_light_index;
        bool _is_updated;
        ofPlanePrimitive plane;
        std::vector<LightSource *> _list_light;
        glm::vec3 _normal;
        glm::vec3 _begin_point;
        glm::vec3 _point_to;
        glm::vec3 _direction;
        float _rotate_angle;
        float _density; 
        float _length;
        float _width;
        float _intensity_per_light;
        void generate_light_source();
};
    
