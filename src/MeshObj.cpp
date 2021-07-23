//
//  MeshObj.cpp
//  
//
//  Created by HINGLI on 1/3/21.
//

#include "MeshObj.h"
#include <glm/gtx/euler_angles.hpp>
MeshObj::MeshObj(glm::vec3 pos,float rotate_by_X,float rotate_by_Y,float rotate_by_Z, ofxAssimpModelLoader* mesh_obj,ofColor diffColor, ofColor speColor) : SceneObject(pos, diffColor, speColor)
{
    this->_mesh_obj = mesh_obj;
    _is_reflectable = false;
    _is_subDivideable = true;
    this->_rotate_by_X = rotate_by_X;
    this->_rotate_by_Y = rotate_by_Y;
    this->_rotate_by_Z = rotate_by_Z;
    glm::mat4 m = glm::translate(glm::mat4(1.0), this->_position);
    this->_M_matrix = glm::rotate(m, glm::radians(this->_rotate_by_X), glm::vec3(1,0,0));
    this->_M_matrix = glm::rotate(this->_M_matrix, glm::radians(this->_rotate_by_Y), glm::vec3(0,1,0));
    this->_M_matrix = glm::rotate(this->_M_matrix,glm::radians(this->_rotate_by_Z),glm::vec3(0,0,1));
    this->_mesh_vertex_size = 3;
    if(this->_mesh_obj != nullptr){
        this->_mesh_list = this->_mesh_obj->getMesh(0).getUniqueFaces();
        for(int i=0;i<this->_mesh_list.size();i++){
            for(int j=0;j<this->_mesh_vertex_size;j++){
                _mesh_list[i].setVertex(j, this->_M_matrix*glm::vec4(this->_mesh_list[i].getVertex(j),1.0f));
            }
        }
        this->_octree = new Octree(this->_mesh_list,this->_position,7);
    }
}
MeshObj::~MeshObj()
{
    
}
void MeshObj::draw()
{
    if(this->_mesh_obj != nullptr)
    {
        ofNoFill();
        ofSetColor(getDiffuseColor());
        for(int i=0;i<this->_mesh_list.size();i++)
        {
            glm::vec3 p1 = this->_mesh_list[i].getVertex(0);
            glm::vec3 p2 = this->_mesh_list[i].getVertex(1);
            glm::vec3 p3 = this->_mesh_list[i].getVertex(2);
            ofDrawTriangle(p1, p2, p3);
        }
        ofSetColor(ofColor::white);
        if(this->_octree != nullptr) this->_octree->draw();
        ofFill();
    }
}
bool MeshObj::isMeshObj()
{
    return true;
}
void MeshObj::setRotationXAxis(float angle)
{
    this->_rotate_by_X = angle;
}
void MeshObj::setRotationYAxis(float angle)
{
    this->_rotate_by_Y = angle;
}
void MeshObj::setRotationZAxis(float angle)
{
    this->_rotate_by_Z = angle;
}
std::vector<glm::vec3> MeshObj::getBound(){
    std::vector<glm::vec3> result;
    float temp_max = std::numeric_limits<float>::max();
    float temp_min = std::numeric_limits<float>::min();
    glm::vec3 min = glm::vec3(temp_max,temp_max,temp_max);
    glm::vec3 max = glm::vec3(temp_min,temp_min,temp_min);
    if(this->_mesh_obj!=nullptr)
    {
        std::vector<ofMeshFace> mesh_list = this->_mesh_obj->getMesh(0).getUniqueFaces();
        for(int i=0;i<mesh_list.size();i++){
            for(int j = 0;j<this->_mesh_vertex_size;j++){
                glm::vec3 temp = mesh_list[i].getVertex(j);
                if(temp.x < min.x) min.x = temp.x;
                if(temp.x > max.x) max.x = temp.x;
                if(temp.y < min.y) min.y = temp.y;
                if(temp.y > max.y) max.y = temp.y;
                if(temp.z < min.z) min.z = temp.z;
                if(temp.z > max.z) max.z = temp.z;
            }
        }
        result.push_back(min);
        result.push_back(max);
    }
    return result;
}
bool MeshObj::intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal)
{
    if(this->_mesh_obj==nullptr || this->_octree ==nullptr) return false;
    else{
        bool is_intersect = false;
        if(!this->_octree->get_root()->getBoundingBox()->intersect(ray)) return false;
        else{
            float the_shortest_distance = std::numeric_limits<float>::infinity();
            if(this->_intersect_helper(ray, point, normal,this->_octree->get_root(),the_shortest_distance))
                return true;
            else return false;
        }
    }
    return false;
}
bool MeshObj::_intersect_helper(const Ray &ray, glm::vec3 &point, glm::vec3 &normal,OctreeNode * root,float& the_shortest_distance){
    if(!root->getBoundingBox()->intersect(ray)){
        return false;
    }
    else if((int)root->getMeshFace().size() <= 30)
    {
        bool is_intersect = false;
        float temp_distance;
        glm::vec3 temp_normal;
        glm::vec2 temp;
        glm::vec3 the_shortest_normal;
        for(int i=0;(int)i<root->getMeshFace().size();i++)
        {
            ofMeshFace temp_face = root->getMeshFace()[i];
            glm::vec3 p1 = temp_face.getVertex(0);
            glm::vec3 p2 = temp_face.getVertex(1);
            glm::vec3 p3 = temp_face.getVertex(2);
            temp_normal = glm::normalize(glm::cross(p2-p1, p3-p1));
            if(glm::intersectRayTriangle(ray.getPoint(), ray.getDirecton(), p1, p2, p3, temp, temp_distance))
            {
                if(the_shortest_distance > temp_distance)
                {
                    is_intersect = true;
                    the_shortest_distance = temp_distance;
                    the_shortest_normal = temp_normal;
                }
            }
        }
        if(is_intersect)
        {
            normal = the_shortest_normal;
            point = ray.getPoint() + ray.getDirecton() * the_shortest_distance;
        }
        return is_intersect;
    }
    else{
        // Recursive check sub-bounding box
        bool is_intersect = false;
        for(int i=0;i<root->getChild().size();i++){
            if(this->_intersect_helper(ray, point, normal, root->getChild()[i],the_shortest_distance)){
                is_intersect = true;
            }
        }
        return is_intersect;
    }
}
/*
bool MeshObj::intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal)
{
    if(this->_mesh_obj==nullptr) return false;
    else
    {
        bool is_intersect = false;
        glm::vec2 temp;
        glm::vec3 first_edge;
        glm::vec3 second_edge;
        glm::vec3 temp_normal;
        glm::vec3 the_shortest_normal;
        float temp_distance;
        float the_shortest_distance = std::numeric_limits<float>::infinity();
        std::vector<ofMeshFace> mesh_list = this->_mesh_obj->getMesh(0).getUniqueFaces();
        for(int i =0;i<mesh_list.size();i++)
        {
            ofMeshFace temp_face = mesh_list.at(i);
            glm::vec3 p1 = this->_M_matrix * glm::vec4(mesh_list.at(i).getVertex(0),1.0f);
            glm::vec3 p2 = this->_M_matrix * glm::vec4(mesh_list.at(i).getVertex(1),1.0f);
            glm::vec3 p3 = this->_M_matrix * glm::vec4(mesh_list.at(i).getVertex(2),1.0f);
            //Finding the face normal for a Trinagle Mesh.
            temp_normal = glm::normalize(glm::cross(p2-p1, p3-p1));
            if(glm::intersectRayTriangle(ray.getPoint(), ray.getDirecton(), p1, p2, p3, temp, temp_distance))
            {
                is_intersect = true;
                if(the_shortest_distance > temp_distance)
                {
                    the_shortest_distance = temp_distance;
                    the_shortest_normal = temp_normal;
                }
            }
        }
        normal = the_shortest_normal;
        point = ray.getPoint() + ray.getDirecton() * the_shortest_distance;
        return is_intersect;
    }
}
*/
