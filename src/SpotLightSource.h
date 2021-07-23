//
//  SpotLightsource.hpp
//  
//
//  Created by HINGLI on 10/15/20.
//
#pragma once
#include "LightSource.h"
class SpotLightSource : public LightSource
{
    public:
        SpotLightSource(glm::vec3 pos, float intensity,float angle,glm::vec3 pointTo,ofColor color = ofColor::lightBlue);
        void setAngle(float angle);
        void draw();
        float getAngle();
        void setDirection(glm::vec3 direction);
        glm::vec3 getDirection();
        bool isSpotLight();
        bool isPointWithinIlluminatedArea(glm::vec3 point);
        void setSpotLightAngle(int angle,int spotLightIndex);
        void setSpotLightPosition(glm::vec3 pos,int spotLightIndex);
        void setSpotLightIndex(int spotLightIndex);
    private:
        float _angle;
        ofConePrimitive _spot_light_image;
        glm::vec3 _point_to;
        glm::vec3 _direction;
        int _spot_light_index;
};

