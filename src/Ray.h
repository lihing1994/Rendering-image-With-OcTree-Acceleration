//
//  Ray.hpp
//  
//
//  Created by HINGLI on 10/1/20.
//
#pragma once
#include "ofMain.h"
#include <glm/gtx/intersect.hpp>

class Ray
{
    private :
        glm::vec3 _point;
        glm::vec3 _direction;
        glm::vec3 _inv_direction;
        glm::vec3 _sign;
    public:
        Ray(glm::vec3 point, glm::vec3 direction);
        void draw(float t);
        glm::vec3 evalPoint(float t);
        glm::vec3 getPoint() const;
        glm::vec3 getDirecton() const;
        glm::vec3 getInvDirection() const;
        glm::vec3 getSign() const;
    
};
