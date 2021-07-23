#include "ofApp.h"
#include "ofApp.h"
void ofApp::setup(){
   
    this->_ray_tracing_system = new RayTracingSystem();
    //Adding reflectable floor plane
    this->_ray_tracing_system->addSceneObject(new Plane(glm::vec3(0,-2,0),glm::vec3(0,1,0),ofColor::lightCyan,40,40));
    /*
    //Addingg wall plane
    this->_ray_tracing_system->addSceneObject(new Plane(glm::vec3(0,18,-20),glm::vec3(0,0,1),ofColor::skyBlue,40,40, new ofImage("wallPlaneTexter.jpeg")));
    //Adding left side wall plane
    this->_ray_tracing_system->addSceneObject(new Plane(glm::vec3(-20,18,0),glm::vec3(1,0,0),ofColor::skyBlue,40,40, new ofImage("wallPlaneTexter.jpeg")));
    //Adding right side wall plane
    this->_ray_tracing_system->addSceneObject(new Plane(glm::vec3(20,18,0),glm::vec3(-1,0,0),ofColor::skyBlue,40,40, new ofImage("wallPlaneTexter.jpeg")));
    //Adding three sphere obejcts.
    
    //Adding three sphere obejcts.
    this->_ray_tracing_system->addSceneObject(new Sphere(glm::vec3(-4,2,0),3.0f,ofColor::blue));
    this->_ray_tracing_system->addSceneObject(new Sphere(glm::vec3(0,3,2),3.0f,ofColor::yellow));
    this->_ray_tracing_system->addSceneObject(new Sphere(glm::vec3(3,2,-2),3.0f,ofColor::red));
    */
    
    
    this->_obj_file = new ofxAssimpModelLoader();
    //monster.obj Rabbit_Lowpoly_1.obj // Torus.obj
    if(_obj_file->loadModel("Rabbit_Lowpoly_1.obj"))
    {
        // The last variable stands for the period of repetition
        //glm::vec3 pos,float rotate_by_X,float rotate_by_Y,float rotate_by_Z, ofxAssimpModelLoader* mesh_obj,ofColor diffColor, ofColor speColor
        this->_ray_tracing_system->addSceneObject(new MeshObj(glm::vec3(0,-2,0),0.0f,0.0f,0.0f,_obj_file,ofColor::blue,ofColor::white));
    }
    else
    {
        std::cout<<"Can't not load the obj file"<<std::endl;
        return;
    }
    /*
     if(_obj_file->loadModel("Rabbit_Lowpoly_1.obj"))
     {
         // The last variable stands for the period of repetition
         //glm::vec3 pos,float rotate_by_X,float rotate_by_Y,float rotate_by_Z, ofxAssimpModelLoader* mesh_obj,ofColor diffColor, ofColor speColor
         this->_ray_tracing_system->addSceneObject(new MeshObj(glm::vec3(0,6,2),0.0f,0.0f,0.0f,_obj_file,ofColor::blue,ofColor::white));
     }
     else
     {
         std::cout<<"Can't not load the obj file"<<std::endl;
         return;
     }
     
     
     
     
     */
    
    
    
    
    
    
    
    //Adding light source for sphere
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(0,-1,5),5.0f,ofColor::black));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(0,6,0),5.0f,ofColor::black));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-8,6,0),5.0f,ofColor::black));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(8,6,0),5.0f,ofColor::black));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(0,8,6),5.0f,ofColor::black));
    /*
     
    
    //First Layer light at the top of wall
    //LightSource(glm::vec3 pos, float intensity, ofColor color,float power = 1000);
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(0,23,-17),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-16,23,-17),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(16,23,-17),5.0f,ofColor::yellow));
    
    //Second Layer light at the wall
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-19,15,-17),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(0,15,-17),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(19,15,-17),5.0f,ofColor::yellow));
    //Thrid Layer light at the wall
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(0,10,-17),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-19,10,-17),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(19,10,-17),5.0f,ofColor::yellow));
    //Adding light at the bottom of coner of wall.
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(16,2,-17),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-16,2,-17),5.0f,ofColor::yellow));
    //Adding light at the left side wall
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-19,2,0),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-19,2,-5),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-19,10,0),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(-19,10,-5),5.0f,ofColor::yellow));
    //Adding light at the Right side wall
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(19,2,0),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(19,2,-5),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(19,10,0),5.0f,ofColor::yellow));
    this->_ray_tracing_system->addLightSource(new LightSource(glm::vec3(19,10,-5),5.0f,ofColor::yellow));
    //Adding two SpotLight
    //SpotLightSource(glm::vec3 pos, float intensity,float angle,glm::vec3 pointTo,ofColor color = ofColor::lightBlue);
    this->_ray_tracing_system->addLightSource(new SpotLightSource(glm::vec3(8,10,12),5.0f,15.0f,glm::vec3(-4,2,0),ofColor::white),true);
    this->_ray_tracing_system->addLightSource(new SpotLightSource(glm::vec3(-6,10,12),5.0f,15.0f,glm::vec3(3,2,-2),ofColor::yellow),true);
    
    
    // Adding Area light
    //
    //this->_ray_tracing_system->addLightSource(new AreaLight(glm::vec3(-15,5,0),glm::vec3(1,0,0),100.0f,-40.0f,ofColor::yellow,3.0f,3.0f,5),false,true);
    //this->_ray_tracing_system->addLightSource(new AreaLight(glm::vec3(15,5,0),glm::vec3(-1,0,0),100.0f,40.0f,ofColor::blue,3.0f,3.0f,5),false,true);
    */
    
    //Adding GUI
    this->_gui.setDefaultWidth(320);
    this->_gui.setup();
    this->_using_ray_intersection_technique.addListener(this, &ofApp::using_ray_intersection_technique);
    this->_gui.add(this->_using_ray_intersection_technique.setup("Ray Intersection Rendering Image",true));
    this->_using_ray_marching_technique.addListener(this, &ofApp::using_ray_marching_technique);
    this->_gui.add(this->_using_ray_marching_technique.setup("Ray Marching Rendering Image",false));
    this->_gui.add(this->_light_intensity.setup("Light intensity: ",10,1,100));
    this->_gui.add(this->_light_power.setup("Phong power: ",1000,10,10000));
    this->_gui.add(this->_spot_light_intensity.setup("Spot-light intensity: ",5,1,100));
    this->_gui.add(this->_spot_light_power.setup("Spot-light phong power",1000,10,10000));
    this->_gui.add(this->_area_light_intensity.setup("Area-light intensity: ",100,1,500));
    this->_gui.add(this->_area_light_power.setup("Area-light phong power:",1000,10,10000));
    this->_gui.add(this->_first_spot_light_position.setup("First(white) spot-light position:",ofVec3f(8,10,12),ofVec3f(-10,-10,-10), ofVec3f(20,20,20)));
    this->_gui.add(this->_first_spot_light_angle.setup("First(white) spot-light angle:",20,1,60));
    this->_gui.add(this->_second_spot_light_position.setup("Second(yellow) spot-light position:",ofVec3f(-6,10,12),ofVec3f(-10,-10,-10), ofVec3f(20,20,20)));
    this->_gui.add(this->_second_spot_light_angle.setup("Second(yellow) spot-light angle:",20,1,60));
    this->_gui.add(this->_first_area_light_position.setup("First(Yellow) area-light position: ",ofVec3f(-15,5,0),ofVec3f(-20,-20,-20), ofVec3f(20,20,20)));
    this->_gui.add(this->_first_area_light_angle.setup("First(Yellow) area-light angle:",-40,-90,90));
    this->_gui.add(this->_second_area_light_position.setup("Second(Blue) area-light position: ",ofVec3f(15,5,0),ofVec3f(-20,-20,-20), ofVec3f(20,20,20)));
    this->_gui.add(this->_second_area_light_angle.setup("Second(Blue) area-light angle:",40,-90,90));
    this->_gui.add(this->_thrid_area_light_position.setup("Thrid(New Added) area-light position: ",ofVec3f(15,5,0),ofVec3f(-20,-20,-20), ofVec3f(20,20,20)));
    ofSetFullscreen(true);
    
    
   
    
    
    
}
ofApp::~ofApp()
{
    delete this->_ray_tracing_system;
    delete this->_obj_file;
    
}
//--------------------------------------------------------------
void ofApp::update(){
    
    if(this->_ray_tracing_system->getLookAround()) this->_ray_tracing_system->lookAround();
    if(this->_using_ray_intersection_technique) this->_ray_tracing_system->setIsUsingRayMarchingTechnique(false);
    else if(this->_using_ray_marching_technique) this->_ray_tracing_system->setIsUsingRayMarchingTechnique(true);
    this->_ray_tracing_system->updateIntensityAndPowerForLight(this->_light_intensity, this->_light_power);
    this->_ray_tracing_system->updateIntensityAndPowerForSpotLight(this->_spot_light_intensity, this->_spot_light_power);
    this->_ray_tracing_system->updateIntensityAndPowerForAreaLight(this->_area_light_intensity, this->_area_light_power);
    this->_ray_tracing_system->updateSpotLightAngle(this->_first_spot_light_angle,0);
    this->_ray_tracing_system->updateSpotLightPosition(_first_spot_light_position,0);
    this->_ray_tracing_system->updateSpotLightAngle(this->_second_spot_light_angle, 1);
    this->_ray_tracing_system->updateSpotLightPosition(this->_second_spot_light_position, 1);
    this->_ray_tracing_system->updateAreaLightPosition(this->_first_area_light_position, 0);
    this->_ray_tracing_system->updateAreaLightAngle(this->_first_area_light_angle, 0);
    this->_ray_tracing_system->updateAreaLightPosition(this->_second_area_light_position, 1);
    this->_ray_tracing_system->updateAreaLightAngle(this->_second_area_light_angle, 1);
    this->_ray_tracing_system->updateAreaLightPosition(this->_thrid_area_light_position, 2);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    if(!this->_bShowImage)
    {
        this->_ray_tracing_system->draw();
        this->_gui.draw();
    }
    else
    {
        if(this->_image_has_been_generate.load("myImage.jpg"))
        {
            this->_image_has_been_generate.draw(glm::vec2(0,0), this->_image_has_been_generate.getWidth(), this->_image_has_been_generate.getHeight());
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key =='s'||key=='S')
    {
        float timeMarker = ofGetSystemTimeMillis();
        if(this->_using_ray_marching_technique) {
            std::cout<<"****************************************************************************************"<<std::endl;
            std::cout<<"Using Ray-Maching Algorithm renders an image(in process)....."<<std::endl;
        }
        else {
            std::cout<<"########################################################################################"<<std::endl;
            std::cout<<"Using Ray-Intersection Algorithm renders an Image(in process)....."<<std::endl;
        }
        this->_ray_tracing_system->rayTracingDrawImage();
        std::cout<<"The time elapsed to randering the image is around "<<(ofGetSystemTimeMillis()-timeMarker)/1000/60<<" min"<<std::endl;
        if(this->_using_ray_marching_technique) std::cout<<"****************************************************************************************"<<std::endl;
        else std::cout<<"########################################################################################"<<std::endl;
    }
    else if(key == OF_KEY_F1)
    {
        this->_bShowImage = false;
        this->_ray_tracing_system->setMainCam();
    }
    else if(key == OF_KEY_F2)
    {
        this->_bShowImage = false;
        this->_ray_tracing_system->setSideCam();
    }
    else if(key == OF_KEY_F3)
    {
        this->_bShowImage = false;
        this->_ray_tracing_system->setSideCam();
        this->_ray_tracing_system->setLookAround(true);
    }
    else if(key == OF_KEY_F4) this->_bShowImage = true;
    else if(key == OF_KEY_F5)
    {
        this->_bShowImage = false;
        this->_ray_tracing_system->setPreviewCam();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
void ofApp::using_ray_intersection_technique(bool & toggleValue)
{
    if(toggleValue) this->_using_ray_marching_technique = false;
    else if(!toggleValue) this->_using_ray_marching_technique = true;
}
void ofApp::using_ray_marching_technique(bool & toggleValue)
{
    if(toggleValue) this->_using_ray_intersection_technique = false;
    else if(!toggleValue) this->_using_ray_intersection_technique = true;
}
