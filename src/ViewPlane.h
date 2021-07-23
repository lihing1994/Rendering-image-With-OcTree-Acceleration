//
//  ViewPlane.hpp
//   
//
//  Created by HINGLI on 10/1/20.
//
#include "Plane.h"
class  ViewPlane: public Plane {
    public:
        ViewPlane(glm::vec2 p0, glm::vec2 p1);
        ViewPlane();
        ~ViewPlane();
        void setSize(glm::vec2 min, glm::vec2 max);
        float getAspect();
        glm::vec3 toWorld(float u, float v);
        void draw();
        float width();
        float height();
        glm::vec2 topLeft();
        glm::vec2 topRight();
        glm::vec2 bottomLeft();
        glm::vec2 bottomRight();
    private:
        glm::vec2 _min;
        glm::vec2 _max;
};
