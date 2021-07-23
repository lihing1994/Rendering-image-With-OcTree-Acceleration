//
//  Octree.cpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 5/13/21.
//

#include "Octree.h"
Octree::Octree(std::vector<ofMeshFace> mesh_face,glm::vec3 pos,int sub_divide_level){
    this->_root = nullptr;
    this->_sub_divide_level = sub_divide_level;
    this->_mesh_vertex_size = 3;
    this->_all_renderable_mesh_face_obj = mesh_face;
    this->_min = glm::vec3(std::numeric_limits<float>::max(),std::numeric_limits<float>::max(),std::numeric_limits<float>::max());
    this->_max =glm::vec3(std::numeric_limits<float>::min(),std::numeric_limits<float>::min(),std::numeric_limits<float>::min());
    for(int i =0;i<this->_all_renderable_mesh_face_obj.size();i++){
        for(int j = 0;j<this->_mesh_vertex_size;j++){
            glm::vec3 temp = this->_all_renderable_mesh_face_obj[i].getVertex(j);
            if(temp.x < this->_min.x) this->_min.x = temp.x;
            if(temp.x > this->_max.x) this->_max.x = temp.x;
            if(temp.y < this->_min.y) this->_min.y = temp.y;
            if(temp.y > this->_max.y) this->_max.y = temp.y;
            if(temp.z < this->_min.z) this->_min.z = temp.z;
            if(temp.z > this->_max.z) this->_max.z = temp.z;
        }
    }
    //Draw the bounding-box.
    this->_pos = pos;
    this->_center_pos = pos;
    this->_center_pos.y += (this->_max.y - this->_min.y)/2;
    float timeMarker = ofGetSystemTimeMillis();
    std::cout<<"Gernate a Octree for an object with "<<sub_divide_level<<" max depth"<<std::endl;
    this->_generate_octree(this->_root,0,this->_sub_divide_level);
    std::cout<<"The time elapsed to gernate the Octree "<<(ofGetSystemTimeMillis()-timeMarker)/1000/60<<" min"<<std::endl;
}
Octree::~Octree(){
    delete this->_root; 
}
void Octree::draw(){
    if(this->_root == nullptr) return;
    else {
        int level = 0;
        int max_level = this->_sub_divide_level;
        draw_helper(this->_root,level,this->_sub_divide_level);
    }
}
void Octree::draw_helper(OctreeNode* root,int& level,int& max_level){
    if(root->getChild().size()>0 && level < max_level){
        root->draw();
        for(int i=0;(int)i<root->getChild().size();i++){
            level++;
            draw_helper(root->getChild()[i],level,max_level);
            level--;
        }
    }
}
void Octree::_generate_octree(OctreeNode* & root,int level,int& max_level){
    if(root == nullptr) root = new OctreeNode(this->_center_pos,this->_min,this->_max,this->_all_renderable_mesh_face_obj);
    root->sub_divide();
    std::vector<OctreeNode* > temp_child = root->getChild();
    if(level < max_level){
        for(int i=0;i<(int)temp_child.size();i++){
            _generate_octree(temp_child[i], level+1,max_level);
        }
    }
}
OctreeNode* Octree::get_root(){
    return this->_root;
}
glm::vec3 Octree::getMin(){
    return this->_min;
}
glm::vec3 Octree::getMax(){
    return this->_max;
}

