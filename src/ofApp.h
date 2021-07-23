#pragma once
#include "RayTracingSystem.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp{
	public:
        ~ofApp();
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void rayTrace();
		void drawGrid();
		void drawAxis(glm::vec3 position);
    private:
        RayTracingSystem * _ray_tracing_system;
        int _imageWidth;
        int _imageHeight;
        bool _bHide;
        bool _bShowImage;
        ofImage _image_has_been_generate;
        ofxPanel _gui;
        ofxIntSlider _light_power;
        ofxIntSlider _light_intensity;
        ofxIntSlider _spot_light_power;
        ofxIntSlider _spot_light_intensity;
        ofxIntSlider _area_light_power;
        ofxIntSlider _area_light_intensity;
        ofxIntSlider _first_spot_light_angle;
        ofxVec3Slider _first_spot_light_position;
        ofxIntSlider _second_spot_light_angle;
        ofxVec3Slider _second_spot_light_position;
        ofxVec3Slider _first_area_light_position;
        ofxIntSlider _first_area_light_angle;
        ofxVec3Slider _second_area_light_position;
        ofxIntSlider _second_area_light_angle;
        ofxToggle _using_ray_marching_technique;
        ofxToggle _using_ray_intersection_technique;
        ofxVec3Slider _thrid_area_light_position;
        ofxAssimpModelLoader * _obj_file;
        void using_ray_intersection_technique(bool & toggleValue);
        void using_ray_marching_technique(bool & toggleValue);
        
};
 
