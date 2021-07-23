//
//  RayTracingSystem.hpp
//  
//
//  Created by HINGLI on 10/2/20.
//
#pragma once
#include "RenderCam.h"
#include "SpotLightSource.h"
#include "AreaLight.h"
#include "Torus.h"
#include <iostream>
class RayTracingSystem
{
    public:
        RayTracingSystem();
        RayTracingSystem(int width,int height);
        ~RayTracingSystem();
        void addSceneObject(SceneObject* toAdd);
        void addLightSource(LightSource* toAdd,bool isSpotLight = false,bool isAreaLight = false);
        void draw();
        void rayTracingDrawImage();
        void setMainCam();
        void setSideCam();
        void setPreviewCam();
        void setLookAround(bool lookAround);
        void lookAround();
        bool getLookAround();
        // For normal light
        void updateIntensityAndPowerForLight(int intensity,int power);
        void updateIntensityAndPowerForSpotLight(int intensity,int power);
        void updateIntensityAndPowerForAreaLight(int intensity,int power);
        // Spot light
        void updateSpotLightAngle(int angle,int spotLightIndex);
        void updateSpotLightPosition(glm::vec3 pos,int spotLightIndex);
        // Area light
        void updateAreaLightPosition(glm::vec3 pos,int areaLightIndex);
        void updateAreaLightAngle(int angle,int areaLightIndex);
        // Mesh Object
        void updateMeshObject(glm::vec3 pos,float scale);
        void setIsUsingRayMarchingTechnique(bool isUsingRayMarching);
        bool get_is_using_ray_marching();
    
    private:
        ofCamera _previewCam;
        ofCamera * _theCam;
        ofCamera _sideCam;
        ofEasyCam _mainCam;
        RenderCam _renderCam;
        ofImage _image;
        vector<SceneObject *> _scene_object_list;
        vector<LightSource *> _light_source_list;
        int _imageWidth;
        int _imageHeight;
        bool _bHide;
        bool _bShowImage;
        bool _look_around;
        bool _look_around_backward_begin;
        int _spot_light_counter;
        int _area_light_counter;
        int _max_recusiver_ray_tracing_level;
        //Helper function for Project 2 part 2.
        ofColor _integralThreeColor(const glm::vec3 &point, const glm::vec3& normal, const ofColor diffuse, const ofColor specular, SceneObject*& obj_selected);
        ofColor _phong(const glm::vec3 &point, const glm::vec3& normal, const ofColor diffuse, const ofColor specular, LightSource* tempLight);
        ofColor _lambert(const glm::vec3 &point, const glm::vec3 &normal, const ofColor diffuse,LightSource* tempLight);
        // Helper function for Final Project.
        void _recusive_mirror_reflection(Ray tempRay,int level,ofColor& temp_diffus,ofColor& temp_spec);
    
        // ##############################################################
        // Following function Adding for CS116B Project 2
        // ##############################################################
        int _maximum_ray_marching_steps;
        // Helper function for rayMarching.
        float _scene_SDF(const glm::vec3 pos, SceneObject*& obj_selected);
        bool _ray_marching(Ray r,glm::vec3& hit_point,glm::vec3& normal,SceneObject*& obj_selected);
        bool _is_using_ray_marching_rending_image;
        glm::vec3 _get_normal_ray_marching(const glm::vec3 &p);
};
