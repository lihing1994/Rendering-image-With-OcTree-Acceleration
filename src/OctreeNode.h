//
//  OctreeNode.hpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 5/13/21.
//

#include <stdio.h>
#include "BoundingBox.h"
class OctreeNode{
    public:
        OctreeNode(glm::vec3 pos,glm::vec3 min,glm::vec3 max,std::vector<ofMeshFace> mesh_face_list,ofColor color = ofColor::white);
        ~OctreeNode();
        std::vector<OctreeNode* > getChild();
        std::vector<ofMeshFace> getMeshFace();
        BoundingBox* getBoundingBox();
        void sub_divide();
        void draw();
    private:
        glm::vec3 _pos;
        glm::vec3 _min;
        glm::vec3 _max;
        BoundingBox * _box;
        ofColor _color;
        std::vector<OctreeNode* > _child;
        std::vector<ofMeshFace> _mesh_list_face;
        glm::mat4 _M_Matrix;
};
