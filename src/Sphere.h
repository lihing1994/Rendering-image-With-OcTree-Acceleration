//
//  Sphere.hpp
//  
//
//  Created by HINGLI on 10/1/20.
//
#include "SceneObject.h"
class Sphere: public SceneObject {
    public:
        Sphere(glm::vec3 p, float r, ofColor diffuse = ofColor::lightGray,bool isReflectable = false);
        Sphere();
        ~Sphere();
        bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal);
        void draw();
        float getRadius();
        float sdf(const glm::vec3 & pos);
        std::vector<glm::vec3> getBound();
    private:
        float _radius = 1.0;
};
