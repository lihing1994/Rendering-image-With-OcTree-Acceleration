//
//  Torus.hpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 3/7/21.
//
#include "MeshObj.h"
class Torus : public MeshObj
{
    public:
        // vec2 : inner radius & outer radius for Torus.
        Torus(glm::vec3 pos,glm::vec2 radius,float rotate_by_X , float rotate_by_Y ,float rotate_by_Z ,ofxAssimpModelLoader* mesh_obj, ofColor diffuse,ofColor speColor, glm::vec3 repetition = glm::vec3(0,0,0));
        ~Torus();
        float sdf(const glm::vec3 & pos);
    private:
        glm::vec2 _radius;
        // M matrix is inherited from MeshObj.
        glm::mat4 _inverse_M_Martix;
        glm::vec3 _repetition;
        MeshObj * _mesh_obj_torus;
        bool _is_load;
};
