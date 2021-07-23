//
//  BoundingBox.hpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 5/13/21.
//

#include <stdio.h>
#include "SceneObject.h"
class BoundingBox : public SceneObject{
    public:
        BoundingBox(glm::vec3 pos, glm::vec3 min,glm::vec3 max,ofColor color = ofColor::white);
        void draw();
        bool intersect(const Ray &ray);
    private:
        ofColor _color;
        std::vector<glm::vec3> _range;
        std::vector<SceneObject*> _scene_obj_list;
        Ray _test_ray = Ray(glm::vec3(0,10,10),glm::vec3(0,-1,-1));
};

