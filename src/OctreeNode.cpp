//
//  OctreeNode.cpp
//  CS116A-FinalProject
//
//  Created by HINGLI on 5/13/21.
//

#include "OctreeNode.h"
OctreeNode::OctreeNode(glm::vec3 pos, glm::vec3 min,glm::vec3 max,std::vector<ofMeshFace> mesh_face_list,ofColor color){
    this->_pos = pos;
    this->_min = min;
    this->_max = max;
    this->_color = color;
    this->_box = new BoundingBox(pos,min,max,this->_color);
    for(int i=0;i<(int)mesh_face_list.size();i++)
    {
        glm::vec3 p1 = mesh_face_list[i].getVertex(0);
        glm::vec3 p2 = mesh_face_list[i].getVertex(1);
        glm::vec3 p3 = mesh_face_list[i].getVertex(2);
        if((p1.x >= min.x && p1.x <= max.x)&&(p1.y >= min.y && p1.y <= max.y) &&(p1.z >= p1.z && p1.z <= max.z)) this->_mesh_list_face.push_back(mesh_face_list[i]);
        else if((p2.x >= min.x && p2.x <= max.x)&&(p2.y >= min.y && p2.y <= max.y) &&(p2.z >= p2.z && p2.z <= max.z)) this->_mesh_list_face.push_back(mesh_face_list[i]);
        else if((p3.x >= min.x && p3.x <= max.x)&&(p3.y >= min.y && p3.y <= max.y) &&(p3.z >= p3.z && p3.z <= max.z)) this->_mesh_list_face.push_back(mesh_face_list[i]);
    }
}
OctreeNode::~OctreeNode(){
    for(int i=0;i<(int)this->_child.size();i++) delete this->_child[i];
    delete this->_box;
}
std::vector<OctreeNode*> OctreeNode::getChild(){
    return this->_child;
}
void OctreeNode::draw(){
    this->_box->draw();
}
void OctreeNode::sub_divide(){
    if((int)this->_mesh_list_face.size() <= 30) return;
    float dx;
    float dy = (this->_max.y - this->_pos.y)/2;
    float dz;
    glm::vec3 temp_center;
    glm::vec3 temp_min;
    glm::vec3 temp_max;
    glm::vec3 first_layer_center = this->_pos;
    first_layer_center.y += dy;
    glm::vec3 second_layer_center = this->_pos;
    second_layer_center.y -= dy;
    
    // Top Right
    temp_center = first_layer_center;
    dz = (this->_max.z - temp_center.z)/2;
    dx = (this->_max.x - temp_center.x)/2;
    temp_center.z += dz;
    temp_center.x += dx;
    this->_child.push_back(new OctreeNode(temp_center,this->_pos,this->_max,this->_mesh_list_face,ofColor::blue));
    // Top Left
    temp_center = first_layer_center;
    temp_center.z += dz;
    temp_center.x -= dx;
    temp_max = this->_max;
    temp_max.x = first_layer_center.x;
    temp_min = this->_min;
    temp_min.y = this->_pos.y;
    temp_min.z = first_layer_center.z;
    this->_child.push_back(new OctreeNode(temp_center,temp_min,temp_max,this->_mesh_list_face,ofColor::blue));
    
    //Top Right back
    temp_center = first_layer_center;
    dz = (this->_pos.z - this->_min.z)/2;
    temp_center.z -= dz;
    temp_center.x += dx;
    temp_min = this->_pos;
    temp_min.z = this->_min.z;
    temp_max = this->_max;
    temp_max.z = this->_pos.z;
    this->_child.push_back(new OctreeNode(temp_center,temp_min,temp_max,this->_mesh_list_face,ofColor::blue));
    //Top Left back
    temp_center = first_layer_center;
    temp_center.z -= dz;
    temp_center.x -= dx;
    temp_min = this->_min;
    temp_min.y = this->_pos.y;
    temp_max = this->_pos;
    temp_max.y = this->_max.y;
    this->_child.push_back(new OctreeNode(temp_center,temp_min,temp_max,this->_mesh_list_face,ofColor::blue));
    // Bottom right
    temp_center = second_layer_center;
    dz = (this->_max.z - temp_center.z)/2;
    temp_center.z += dz;
    temp_center.x += dx;
    temp_min = this->_min;
    temp_min.x = second_layer_center.x;
    temp_min.z = second_layer_center.z;
    temp_max = this->_max;
    temp_max.y = this->_pos.y;
    this->_child.push_back(new OctreeNode(temp_center,temp_min,temp_max,this->_mesh_list_face,ofColor::blue));
    
    // Bottom left
    temp_center = second_layer_center;
    temp_center.z += dz;
    temp_center.x -= dx;
    temp_min = this->_min;
    temp_min.z = this->_pos.z;
    temp_max = this->_pos;
    temp_max.z = this->_max.z;
    this->_child.push_back(new OctreeNode(temp_center,temp_min,temp_max,this->_mesh_list_face,ofColor::blue));
    
    // Bottom right back
    temp_center = second_layer_center;
    dz = (this->_pos.z - this->_min.z)/2;
    temp_center.z -= dz;
    temp_center.x += dx;
    temp_min = this->_min;
    temp_min.x = second_layer_center.x;
    temp_max = this->_max;
    temp_max.y = this->_pos.y;
    temp_max.z = this->_pos.z;
    this->_child.push_back(new OctreeNode(temp_center,temp_min,temp_max,this->_mesh_list_face,ofColor::blue));
    // Bottom left back;
    temp_center = second_layer_center;
    temp_center.z -= dz;
    temp_center.x -= dx;
    this->_child.push_back(new OctreeNode(temp_center,this->_min,this->_pos,this->_mesh_list_face,ofColor::blue));
     
    
}
std::vector<ofMeshFace> OctreeNode::getMeshFace(){
    return this->_mesh_list_face;
}
BoundingBox* OctreeNode::getBoundingBox(){
    return this->_box;
}
