//
//  MeshObj.hpp
//  
//
//  Created by HINGLI on 12/24/20.
//

#pragma once
#include "Octree.h"
#include "ofxAssimpModelLoader.h"

class MeshObj : public SceneObject
{
    public:
        MeshObj(glm::vec3 pos,float rotate_by_X,float rotate_by_Y,float rotate_by_Z, ofxAssimpModelLoader* mesh_obj,ofColor diffColor, ofColor speColor);
        ~MeshObj();
        bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal);
        void draw();
        bool isMeshObj();
        void setRotationXAxis(float angle);
        void setRotationYAxis(float angle);
        void setRotationZAxis(float angle);
        std::vector<glm::vec3> getBound();
    protected:
        Octree * _octree;
        std::vector<ofMeshFace> _mesh_list;
        ofxAssimpModelLoader * _mesh_obj = nullptr;
        float _rotate_by_X;
        float _rotate_by_Y;
        float _rotate_by_Z;
        glm::mat4 _M_matrix;
        int _mesh_vertex_size;
        bool _intersect_helper(const Ray &ray,glm::vec3 &point, glm::vec3 &normal,OctreeNode* root,float& the_shortest_distance);
};

