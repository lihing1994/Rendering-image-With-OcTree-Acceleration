//
//  Torus.cpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 3/7/21.
//

#include "Torus.h"
Torus::Torus(glm::vec3 pos,glm::vec2 radius,float rotate_by_X , float rotate_by_Y ,float rotate_by_Z ,ofxAssimpModelLoader* mesh_obj, ofColor diffuse,ofColor speColor,glm::vec3 repetition) : MeshObj(pos, rotate_by_X, rotate_by_Y, rotate_by_Z, mesh_obj, diffuse, speColor)
{
    this->_radius = radius;
    this->_inverse_M_Martix = glm::inverse(this->_M_matrix);
    this->_repetition = repetition;
}
Torus::~Torus()
{
    
}
/*
 SDF function implemented by: Inigo Quilez
 Source: https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
 */
float Torus::sdf(const glm::vec3 & pos)
{
    glm::vec3 p = this->_inverse_M_Martix * glm::vec4(pos,1);
    p = _infinte_repetition(p, this->_repetition);
    glm::vec2 q = glm::vec2(glm::length(glm::vec2(p.x,p.z))-this->_radius.x,p.y);
    return glm::length(q) - this->_radius.y;
}
