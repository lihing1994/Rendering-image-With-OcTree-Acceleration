//
//  Octree.hpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 5/13/21.
//


#include <stdio.h>
#include "OctreeNode.h"

class Octree{
    public:
        Octree(std::vector<ofMeshFace> mesh_face,glm::vec3 pos, int sub_divide_level = 7);
        ~Octree();
        OctreeNode * get_root();
        glm::vec3 getMin();
        glm::vec3 getMax();
        void draw();
    private:
        glm::vec3 _pos;
        glm::vec3 _min;
        glm::vec3 _max;
        glm::vec3 _center_pos;
        OctreeNode * _root; 
        std::vector<ofMeshFace> _all_renderable_mesh_face_obj;
        int _mesh_vertex_size;
        int _sub_divide_level;
        // Private helper function.
        void _generate_octree(OctreeNode* & root,int level,int &max_level);
        void draw_helper(OctreeNode* root,int& level,int& max_level);
        
        
};

