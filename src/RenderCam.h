//
//  RenderCam.hpp
// 
//
//  Created by HINGLI on 10/1/20.
//
#include "ViewPlane.h"
#include "Sphere.h"
class RenderCam: public SceneObject
{
    public:
        RenderCam();
        ~RenderCam();
        Ray getRay(float u, float v);
        void draw();
        void drawFrustum();
        void setPosition(glm::vec3 pos);
        glm::vec3 getPosition();
        glm::vec3 getAim();
    private:
        glm::vec3 _aim;
        ViewPlane _view;          // The camera viewplane, this is the view that we will render
};
