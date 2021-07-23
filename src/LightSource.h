//
//  LightSource.
//  
//
//  Created by HINGLI on 10/10/20.
//
#pragma once
#include "SceneObject.h"
class LightSource : public SceneObject
{
    public:
        LightSource();
        LightSource(glm::vec3 pos, float intensity, ofColor color = ofColor::white,float power = 1000);
        ~LightSource();
        // Adding for the Spotlight object.
        // Following functions are virtual function and spotlight obejct, which inheirt from this class,
        // will overrided the following function.
        virtual void draw();
        // Spot light
        virtual bool isSpotLight();
        virtual bool isPointWithinIlluminatedArea(glm::vec3 point);
        virtual void setSpotLightAngle(int angle,int spotLightIndex);
        virtual void setSpotLightPosition(glm::vec3 pos,int spotLightIndex);
        virtual void setSpotLightIndex(int spotLightIndex);
        // Area light
        virtual void setAreaLightIndex(int areaLightIndex);
        virtual void setAreaLightPosition(glm::vec3 pos,int areaLightIndex);
        virtual void setAreaLightAngle(int angle,int areaLightIndex);
        virtual bool isAreaLight();
        virtual float getDensity();
        virtual glm::vec3 getAreaLightNormal();
        virtual std::vector<LightSource *> * getLightList();
        virtual void setIsPartOfAreaLight(bool isPartOfAreaLigth);
        virtual bool getIsPartOfAreaLight();
        glm::vec3 getPosition();
        void setCombineMatrix(glm::mat4 M);
        //
        bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal);
        float getIntensity();
        float getPower();
        void setIntensity(int intensity);
        void setPower(int power);
        
    protected:
        glm::mat4 _m;
        glm::mat4 _M;
        float _intensity;
        float _power;
        ofColor _light_point_color;
        bool _is_part_of_area_light;
        
};
