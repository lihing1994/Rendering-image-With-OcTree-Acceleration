//
//  RayTracingSystem.cpp
//  
//
//  Created by HINGLI on 10/2/20.
//

#include "RayTracingSystem.h"
RayTracingSystem::RayTracingSystem()
{
    // this->_easy_cam.setDistance(30.0);
    //this->_easy_cam.lookAt(glm::vec3(0,0,0));
    this->_mainCam.setDistance(55.0);
    this->_mainCam.setPosition(0, 30, 80);
    this->_mainCam.lookAt(glm::vec3(0,1,0));
    //_position = glm::vec3(0, 0, 20);
    this->_sideCam.lookAt(glm::vec3(-1,0,-1));
    this->_sideCam.setPosition(glm::vec3(30,0,30));
    this->_previewCam.setPosition(glm::vec3(0, 0, 20));
    this->_previewCam.lookAt(glm::vec3(0,0,-1));
    ofSetBackgroundColor(ofColor::black);
    this->_theCam = &_mainCam;
    //Keep the screen resolution to 1.5 : 1
    this->_imageWidth = ofGetScreenWidth();
    this->_imageHeight = _imageWidth/1.5;
    this->_look_around_backward_begin = false;
    this->_spot_light_counter = 0;
    this->_area_light_counter = 0;
    this->_max_recusiver_ray_tracing_level = 2;
    this->_maximum_ray_marching_steps = 100;
    this->_is_using_ray_marching_rending_image = false;
}
RayTracingSystem::RayTracingSystem(int width,int hight)
{
    this->_imageWidth = width;
    this->_imageHeight = hight;
    this->_mainCam.setDistance(30.0);
    this->_mainCam.lookAt(glm::vec3(0,10,0));
    this->_sideCam.setPosition(this->_renderCam.getPosition());
    this->_sideCam.lookAt(this->_renderCam.getAim());
    ofSetBackgroundColor(ofColor::black);
    this->_theCam = &_mainCam;
    this->_spot_light_counter = 0;
    this->_area_light_counter = 0;
    this->_max_recusiver_ray_tracing_level = 2;
    this->_maximum_ray_marching_steps = 100;
    this->_is_using_ray_marching_rending_image = false;
}
RayTracingSystem::~RayTracingSystem()
{
    for(int i=0;i<this->_scene_object_list.size();i++) delete _scene_object_list.at(i);
    for(int i=0;i<this->_light_source_list.size();i++) delete _light_source_list.at(i);
    //delete _my_octree;
}
void RayTracingSystem::addSceneObject(SceneObject *toAdd)
{
    this->_scene_object_list.push_back(toAdd);
}
void RayTracingSystem::addLightSource(LightSource* toAdd, bool isSpotLight,bool isAreaLight)
{
    if(isSpotLight) toAdd->setSpotLightIndex(this->_spot_light_counter++);
    else if(isAreaLight) toAdd->setAreaLightIndex(this->_area_light_counter++);
    this->_light_source_list.push_back(toAdd);
}
void RayTracingSystem::draw()
{
    this->_theCam->begin();
    for(int i =0;i<this->_scene_object_list.size();i++) this->_scene_object_list.at(i)->draw();
    for(int i =0;i<this->_light_source_list.size();i++) this->_light_source_list.at(i)->draw();
    //if(this->_my_octree!=nullptr) this->_my_octree->draw();
    this->_theCam->end();
}
void RayTracingSystem::rayTracingDrawImage()
{
    this->_image.allocate(this->_imageWidth,this->_imageHeight, OF_IMAGE_COLOR);
    for(int i=0;i<this->_imageWidth;i++)
    {
        for(int j=0;j<this->_imageHeight;j++)
        {
            // Finding the value of u and v.
            // Bascilly, we will convert the world 3D coordinate,
            // into the local ViewPlane coordinate.
            float u = (float(i) + 0.5)/float(this->_imageWidth);
            float v = (float(j) + 0.5)/float(this->_imageHeight);
            Ray temp_ray = this->_renderCam.getRay(u, v);
            //A pointer points to the temp closest object.
            SceneObject * temp_closest_object = nullptr;
            float temp_shortest_distance = std::numeric_limits<float>::infinity();
            bool is_intersect = false;
            glm::vec3 temp_intersect_point;
            glm::vec3 temp_normal;
            glm::vec3 temp_closest_point;
            glm::vec3 temp_closest_normal;
            bool is_ray_selected_object = false;
            if(!_is_using_ray_marching_rending_image)
            {
                for(int k = 0;k<this->_scene_object_list.size();k++)
                {
                    if(!this->_is_using_ray_marching_rending_image && this->_scene_object_list.at(k)->intersect(temp_ray, temp_intersect_point, temp_normal))
                    {
                        // If a ray select an object
                        // Then we are trying to find the closest object to draw on our image.
                        is_ray_selected_object = true;
                        // We are going to keep tracking the closest sence object
                        //until we loop all the sence object on that pixel.
                        float temp_distance = glm::length2(temp_intersect_point-this->_renderCam.getPosition());
                        // If a closest sence object was find.
                        // We update the pointer variable, which is pointing to the closest object to the ray.
                        if(temp_distance < temp_shortest_distance)
                        {
                            temp_shortest_distance = temp_distance;
                            temp_closest_object = this->_scene_object_list.at(k);
                            temp_closest_point = temp_intersect_point;
                            temp_closest_normal = temp_normal;
                        }
                    }
                }
            }
            else if(this->_ray_marching(temp_ray, temp_closest_point, temp_closest_normal, temp_closest_object)) is_ray_selected_object = true;
            //If our ray selected a secen object.
            if(is_ray_selected_object)
            {
                // Fulfill the image using color using the scene object's color.
                // To fix the issue regarding to the image is upside down.
                // The range of the image is from 0 to (image height -1).
                // e.g, if a image has a height in 400 pixel.
                // Then the range of the pixel in Y dirction should be from 0 to 399.
                ofColor temp_color = ofColor::black;
                // If the closest object selected by the ray tracing algorithm is not a plane,
                if(!temp_closest_object->isFloorPlane())
                {
                    // If the object is not reflectable.
                    if(!temp_closest_object->getReflectable())
                    {
                        //Now adding ambient,Phong, and diffuse color to the pixel be selected.
                        temp_color += this->_integralThreeColor(temp_closest_point, temp_closest_normal, temp_closest_object->getDiffuseColor(), temp_closest_object->getSpecularColor(),temp_closest_object);
                        this->_image.setColor(i, _imageHeight - 1 -j, temp_color);
                    }
                    // If object is reflectable, then a perfect reflection effect will be obtianed
                    // Based on physic, perfect reflection means there is no energy lost.
                    else
                    {
                        // Following steps is used to find the reflection vector.
                        ofColor temp_diffus = ofColor::black;
                        ofColor temp_spec = ofColor::black;
                        glm::vec3 temp_ray_dir = temp_ray.getDirecton();
                        temp_closest_normal = glm::normalize(temp_closest_normal);
                        temp_ray_dir = glm::normalize(temp_ray_dir);
                        // Finding the ray projection on the normal vector of the intersection point.
                        glm::vec3 projection_vector = glm::dot(temp_ray_dir, temp_closest_normal)/(glm::length(temp_closest_normal)) * temp_closest_normal;
                        // Then based on the report, the reflection vector = input ray - 2 x projection vector.
                        glm::vec3 reflection_direction_vector = temp_ray_dir - 2 * projection_vector;
                        // Finding some offset point, which is slightly off the intersection point.
                        // Therefore, the reflection ray will not be blocked by the object, which intersection point on it.
                        glm::vec3 off_set = temp_closest_point +  0.0001 * glm::normalize(temp_closest_normal);
                        reflection_direction_vector = glm::normalize(reflection_direction_vector);
                        // Now the reflection ray is obtained.
                        Ray reflection_ray(off_set,reflection_direction_vector);
                        // Using the recursive way to find the return color for the mirror reflection.
                        this->_recusive_mirror_reflection(reflection_ray,0,temp_diffus,temp_spec);
                        temp_color += this->_integralThreeColor(temp_closest_point, temp_closest_normal, temp_closest_object->getDiffuseColor(), temp_closest_object->getSpecularColor(),temp_closest_object);
                        temp_color += this->_integralThreeColor(temp_closest_point, temp_closest_normal, temp_diffus , temp_spec,temp_closest_object);
                        this->_image.setColor(i, _imageHeight - 1 -j, temp_color);
                        
                    }
                }
                // If the floor plane is selected.
                else
                {
                    // If a floor plane is reflectable.
                    if(temp_closest_object->getReflectable())
                    {
                        ofColor temp_diffus = ofColor::black;
                        ofColor temp_spec = ofColor::black;
                        glm::vec3 temp_ray_dir = temp_ray.getDirecton();
                        temp_closest_normal = glm::normalize(temp_closest_normal);
                        temp_ray_dir = glm::normalize(temp_ray_dir);
                        glm::vec3 projection_vector = glm::dot(temp_ray_dir, temp_closest_normal)/(glm::length(temp_closest_normal)) * temp_closest_normal;
                        glm::vec3 reflection_direction_vector = temp_ray_dir - 2 * projection_vector;
                        glm::vec3 off_set = temp_closest_point +  0.0001 * glm::normalize(temp_closest_normal);
                        reflection_direction_vector = glm::normalize(reflection_direction_vector);
                        Ray reflection_ray(off_set,reflection_direction_vector);
                        this->_recusive_mirror_reflection(reflection_ray,0,temp_diffus,temp_spec);
                        // If a floor-plane is reflectable, regardless the floor-plane contained an image,
                        // we used the diffuse color and specular color to rendering the image instead of using the color value from the image.
                        temp_color += this->_integralThreeColor(temp_closest_point, temp_closest_normal, temp_closest_object->getDiffuseColor(), temp_closest_object->getSpecularColor(),temp_closest_object);
                        temp_color += this->_integralThreeColor(temp_closest_point, temp_closest_normal, temp_diffus, temp_spec,temp_closest_object);
                        this->_image.setColor(i, _imageHeight - 1 -j, temp_color);
                    }
                    else
                    {
                        // If floor-plane don't have an image.
                        if(temp_closest_object->getFloorPlaneTexter()!=nullptr)
                        {
                            // If the closest object slected by the ray tracing algorithm is a plane,
                            // We find the corresponding pixel in the textrue image.
                            glm::vec2 pixel_at_image = temp_closest_object->getTexterPixel(temp_closest_point);
                            //Make sure the plane object contain a valid pointer to ofImage.
                            // Get the color from the texture image
                            ofColor temp_diffuse_color_floor = temp_closest_object->getFloorPlaneTexter()->getColor(pixel_at_image.x, pixel_at_image.y);
                            temp_color += this->_integralThreeColor(temp_closest_point, temp_closest_normal, temp_diffuse_color_floor, ofColor::darkGray,temp_closest_object);
                            this->_image.setColor(i, _imageHeight - 1 -j, temp_color);
                        }
                        else
                        {
                            temp_color += this->_integralThreeColor(temp_closest_point, temp_closest_normal, temp_closest_object->getDiffuseColor(), temp_closest_object->getSpecularColor(),temp_closest_object);
                            this->_image.setColor(i, _imageHeight - 1 -j, temp_color);
                        }
                    }
                    
                }
            }
            else
            {
                // If no object is selected by the ray,
                // fulfill the image using the background color.
                this->_image.setColor(i, _imageHeight - 1 - j, ofColor::black);
            }
            
        }
    }
    //Finally save the image
    this->_image.save("myImage.jpg");
    std::cout<<"Picture saved!"<<std::endl;
}

void RayTracingSystem::setMainCam()
{
    this->_theCam = &(this->_mainCam);
}
void RayTracingSystem::setSideCam()
{
    this->_theCam = &(this->_sideCam);
}
void RayTracingSystem::lookAround()
{
    if(!this->_look_around) return;
    else if(this->_theCam == &_sideCam)
    {
        if(this->_theCam->getX()> -30 && !_look_around_backward_begin)
        {
            this->_theCam->setPosition(glm::vec3(this->_theCam->getX()-0.25,this->_theCam->getY(),this->_theCam->getZ()));
            float tempRatio = this->_theCam->getX()/this->_theCam->getZ();
            this->_theCam->lookAt(glm::vec3(-tempRatio,0,-1));
        }
        else if(this->_theCam->getZ() > - 30 && !_look_around_backward_begin)
        {
            this->_theCam->setPosition(glm::vec3(this->_theCam->getX(),this->_theCam->getY(),this->_theCam->getZ()-0.25));
            float tempRatio = this->_theCam->getZ()/this->_theCam->getX();
            this->_theCam->lookAt(glm::vec3(1,0,-tempRatio));
        }
        else if(this->_theCam->getX() < 30)
        {
            this->_theCam->setPosition(glm::vec3(this->_theCam->getX()+0.25,this->_theCam->getY(),this->_theCam->getZ()));
            float tempRatio = this->_theCam->getX()/this->_theCam->getZ();
            this->_theCam->lookAt(glm::vec3(tempRatio,0,1));
            _look_around_backward_begin = true;
        }
        else if(this->_theCam->getZ() < 30)
        {
            this->_theCam->setPosition(glm::vec3(this->_theCam->getX(),this->_theCam->getY(),this->_theCam->getZ()+0.25));
            float tempRatio = this->_theCam->getZ()/this->_theCam->getX();
            this->_theCam->lookAt(glm::vec3(1,0,tempRatio));
        }
        else if(this->_theCam->getX()== 30 && this->_theCam->getZ()== 30)
        {
            this->_look_around_backward_begin = false;
            this->_look_around = false;
        }
    }
}
void RayTracingSystem::setLookAround(bool lookAround)
{
    this->_look_around = lookAround;
}
bool RayTracingSystem::getLookAround()
{
    return this->_look_around;
}
void RayTracingSystem::setPreviewCam()
{
    this->_theCam = &(this->_previewCam);
}
ofColor RayTracingSystem::_integralThreeColor(const glm::vec3 &point, const glm::vec3& normal, const ofColor diffuse, const ofColor specular,SceneObject*& obj_selected)
{
    // Start with the black color.
    ofColor sum = ofColor::black;
    // Iterating a our light source.
    for(int i=0;i<this->_light_source_list.size();i++)
    {
        bool is_area_light = this->_light_source_list.at(i)->isAreaLight();
        // If the light is not an area light,
        // then do the following.
        if(!is_area_light)
        {
            bool is_blocked = false;
            // Checking each if each light has been block by scene object.
            // Instead of getting a point exactly at the intersection point,
            // We find a point that is slightly off the point.
            // In this way, we prevent the situation that the ray
            // from the light source to the intersection point
            // is blocked by the object where the point located at.
            glm::vec3 off_set_point = point + 0.0001 * glm::normalize(normal);
            if(!this->_is_using_ray_marching_rending_image)
            {
                for(int j=0;j<this->_scene_object_list.size();j++)
                {
                    if(!this->_light_source_list.at(i)->isPointWithinIlluminatedArea(off_set_point))
                    {
                        // If a light source is spot light and the intersection point
                        // is not within the Illuminated area, we don't need to contuine check.
                        is_blocked = true;
                        break;
                    }
                    glm::vec3 direction = glm::normalize( off_set_point - this->_light_source_list.at(i)->getPosition());
                    Ray temp_ray(this->_light_source_list.at(i)->getPosition(),direction);
                    glm::vec3 temp_point;
                    glm::vec3 temp_normal;
                    if(this->_scene_object_list.at(j)->intersect(temp_ray, temp_point, temp_normal))
                    {
                        // Checking if the distacne from the insection point to light source is farther than
                        // the distacne from the insection point to any other scene object.
                        // If distance from the light source to insection point is shorter,
                        // The light ray is not being blocked.
                        // For the detail explantion , you can see the project's report.
                        if(glm::length2(off_set_point-this->_light_source_list.at(i)->getPosition())>glm::length2(this->_light_source_list.at(i)->getPosition()-temp_point))
                        {
                            is_blocked = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                glm::vec3 direction = glm::normalize( off_set_point - this->_light_source_list.at(i)->getPosition());
                Ray temp_ray(this->_light_source_list.at(i)->getPosition(),direction);
                glm::vec3 temp_point;
                glm::vec3 temp_normal;
                SceneObject* temp_obj_selected;
                if(this->_ray_marching(temp_ray, temp_point, temp_normal, temp_obj_selected))
                {
                    // If ray from light to scene object that has been selected is block by another scene,
                    // the light ray is blocked.
                    if(obj_selected != temp_obj_selected)
                    {
                        is_blocked = true;
                    }
                }
            }
            if(!is_blocked)
            {
                
                // If the ray is not being blocked,
                // then we add the light's contribution at this pixel.
                // Adding the ambient effect to each pixel has been selected.
                sum += ofColor::white * 0.0001;
                sum += this->_phong(point, normal, diffuse, specular, _light_source_list.at(i));
                sum += this->_lambert(point, normal, diffuse, _light_source_list.at(i));
                
                
            }
            
        }
        // If the light is an area light,
        // then do the following
        else if(is_area_light)
        {
            for(int j =0;j<this->_light_source_list.at(i)->getLightList()->size();j++)
            {
                bool is_blocked = false;
                glm::vec3 off_set_point = point + 0.0001 * glm::normalize(normal);
                if(!this->_is_using_ray_marching_rending_image)
                {
                    for(int k=0;k<this->_scene_object_list.size();k++)
                    {
                        glm::vec3 direction =  glm::normalize( off_set_point - this->_light_source_list.at(i)->getLightList()->at(j)->getPosition());
                        glm::vec3 area_light_normal = this->_light_source_list.at(i)->getAreaLightNormal();
                        float cos_theta = glm::dot(area_light_normal, -direction)/(glm::length(area_light_normal)*glm::length(direction));
                        float angle = glm::degrees(glm::acos(cos_theta));
                        if(angle >= 60.0f)
                        {
                            is_blocked = true;
                            break;
                        }
                        Ray temp_ray(this->_light_source_list.at(i)->getLightList()->at(j)->getPosition(),direction);
                        glm::vec3 temp_point;
                        glm::vec3 temp_normal;
                        if(this->_scene_object_list.at(k)->intersect(temp_ray, temp_point, temp_normal))
                        {
                            // Checking if the distacne from the insection point to light source is farther than
                            // the distacne from the insection point to scene object.
                            // If distance from the light source to insection point is shorter,
                            // The ray is not being blocked.
                            // For the detail explantion , you can see the project's report.
                            if(glm::length2(off_set_point-this->_light_source_list.at(i)->getLightList()->at(j)->getPosition()) > glm::length2(this->_light_source_list.at(i)->getPosition()-temp_point))
                            {
                                is_blocked = true;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    glm::vec3 direction =  glm::normalize( off_set_point - this->_light_source_list.at(i)->getLightList()->at(j)->getPosition());
                    glm::vec3 area_light_normal = this->_light_source_list.at(i)->getAreaLightNormal();
                    float cos_theta = glm::dot(area_light_normal, -direction)/(glm::length(area_light_normal)*glm::length(direction));
                    float angle = glm::degrees(glm::acos(cos_theta));
                    if(angle >= 60.0f)
                    {
                        is_blocked = true;
                        break;
                    }
                    Ray temp_ray(this->_light_source_list.at(i)->getLightList()->at(j)->getPosition(),direction);
                    glm::vec3 temp_point;
                    glm::vec3 temp_normal;
                    SceneObject * temp_obj_selected;
                    if(this->_ray_marching(temp_ray, temp_point, temp_normal, temp_obj_selected))
                    {
                        // If ray from light to scene object that has been selected is block by another scene,
                        // the light ray is blocked.
                        if(obj_selected != temp_obj_selected)
                        {
                            is_blocked = true;
                        }
                    }
                }
                if(!is_blocked)
                {
                    // If the ray is not being blocked,
                    // then we add the light's contribution at this pixel.
                    // Adding the ambient effect to each pixel has been selected.
                    sum += ofColor::white * 0.0001;
                    sum += this->_phong(point, normal, diffuse, specular, _light_source_list.at(i)->getLightList()->at(j));
                    sum += this->_lambert(point, normal, diffuse, _light_source_list.at(i)->getLightList()->at(j));
                }
            }
        }
    }
    return sum;
}
ofColor RayTracingSystem::_phong(const glm::vec3 &point, const glm::vec3& normal, const ofColor diffuse, const ofColor specular, LightSource* tempLight)
{
    //Starting with the black color.
    ofColor sum = ofColor::black;
    // Finding the vector from the selected pixel to view point, which is the rander camera position.
    glm::vec3 view_vector = glm::normalize(this->_renderCam.getPosition() - point);
    // Fiding the vector from selected pixel to light poistion.
    glm::vec3 light_vector = glm::normalize(tempLight->getPosition() - point);
    // Finding the bisector.
    glm::vec3 bisector = (view_vector + light_vector)/glm::length(view_vector + light_vector);
    // Fiding the distance between light and selected pixel.
    float temp_distance_from_point_to_light = glm::length(tempLight->getPosition()-point);
    // Following steps calcuate the Phong shading.
    double temp = (tempLight->getIntensity()) / glm::pow(temp_distance_from_point_to_light,2) * glm::pow(glm::max(0.0f,glm::dot(glm::normalize(normal),bisector)),tempLight->getPower());
    sum += specular * temp;
    return sum;
}

ofColor RayTracingSystem::_lambert(const glm::vec3 &point, const glm::vec3 &normal, const ofColor diffuse,LightSource* lightPos)
{
    
    //Starting with the black color.
    ofColor sum = ofColor::black;
    // Fiding the vector from selected pixel to light poistion.
    glm::vec3 light_vector = glm::normalize(lightPos->getPosition() - point);
    // Fiding the distance between light and selected pixel.
    float temp_distance_from_point_to_light = glm::length(lightPos->getPosition()-point);
    // Following steps calcuate the lambert shading.
    double temp = (lightPos->getIntensity()) / glm::pow(temp_distance_from_point_to_light,2) * glm::max(0.0f,glm::dot(glm::normalize(normal),light_vector));
    sum += diffuse * temp;
    return sum;
}
void RayTracingSystem::updateIntensityAndPowerForLight(int intensity, int power)
{
    for(int i=0;i<this->_light_source_list.size();i++)
    {
        if(!this->_light_source_list.at(i)->isAreaLight()&&!this->_light_source_list.at(i)->isSpotLight())
        {
            this->_light_source_list.at(i)->setIntensity(intensity);
            this->_light_source_list.at(i)->setPower(power);
        }
    }
}
void RayTracingSystem::updateIntensityAndPowerForSpotLight(int intensity, int power)
{
    for(int i=0;i<this->_light_source_list.size();i++)
    {
        if(this->_light_source_list.at(i)->isSpotLight())
        {
            this->_light_source_list.at(i)->setIntensity(intensity);
            this->_light_source_list.at(i)->setPower(power);
        }
    }
}
void RayTracingSystem::updateIntensityAndPowerForAreaLight(int intensity, int power)
{
    for(int i=0;i<this->_light_source_list.size();i++)
    {
        if(this->_light_source_list.at(i)->isAreaLight())
        {
            for(int j=0;j<this->_light_source_list.at(i)->getLightList()->size();j++)
            {
                this->_light_source_list.at(i)->getLightList()->at(j)->setIntensity(intensity/pow(this->_light_source_list.at(i)->getDensity(),2));
                this->_light_source_list.at(i)->getLightList()->at(j)->setPower(power);
            }
        }
    }
}
void RayTracingSystem::updateSpotLightAngle(int angle,int spotLightIndex)
{
    for(int i=0;i<this->_light_source_list.size();i++) this->_light_source_list.at(i)->setSpotLightAngle(angle,spotLightIndex);
}
void RayTracingSystem::updateSpotLightPosition(glm::vec3 pos,int spotLightIndex)
{
    for(int i=0;i<this->_light_source_list.size();i++) this->_light_source_list.at(i)->setSpotLightPosition(pos,spotLightIndex);
}
// Adding the final project
void RayTracingSystem::updateAreaLightPosition(glm::vec3 pos,int areaLightIndex)
{
    for(int i=0;i<this->_light_source_list.size();i++) this->_light_source_list.at(i)->setAreaLightPosition(pos, areaLightIndex);
}
void RayTracingSystem::updateAreaLightAngle(int angle, int areaLightIndex)
{
    for(int i=0;i<this->_light_source_list.size();i++) this->_light_source_list.at(i)->setAreaLightAngle(angle, areaLightIndex);
}
void RayTracingSystem::updateMeshObject(glm::vec3 pos,float scale)
{
    for(int i=0;i<this->_scene_object_list.size();i++);
}
void RayTracingSystem::_recusive_mirror_reflection(Ray temp_ray, int level,ofColor& temp_diffus,ofColor& temp_spec)
{
    if(level == this->_max_recusiver_ray_tracing_level)
    {
        return;
    }
    else
    {
        SceneObject * temp_closest_object = nullptr;
        float temp_shortest_distance = std::numeric_limits<float>::infinity();
        bool is_intersect = false;
        glm::vec3 temp_intersect_point;
        glm::vec3 temp_normal;
        glm::vec3 temp_closest_point;
        glm::vec3 temp_closest_normal;
        bool is_ray_selected_object = false;
        for(int i=0;i<this->_scene_object_list.size();i++)
        {
            if(this->_scene_object_list.at(i)->intersect(temp_ray, temp_intersect_point, temp_normal))
            {
                // If a ray select an object
                // Then we are trying to find the closest object to draw on our image.
                is_ray_selected_object = true;
                // We are going to keep tracking the closest sence object
                //until we loop all the sence object on that pixel.
                float temp_distance = glm::length2(temp_intersect_point-this->_renderCam.getPosition());
                // If a closest sence object was find.
                // We update the pointer variable, which is pointing to the closest object to the ray.
                if(temp_distance < temp_shortest_distance)
                {
                    temp_shortest_distance = temp_distance;
                    temp_closest_object = this->_scene_object_list.at(i);
                    temp_closest_point = temp_intersect_point;
                    temp_closest_normal = temp_normal;
                }
            }
        }
        if(is_ray_selected_object)
        {
            if(temp_closest_object->isFloorPlane())
            {
                glm::vec2 pixel_at_image = temp_closest_object->getTexterPixel(temp_closest_point);
                if(temp_closest_object->getFloorPlaneTexter()!=nullptr)
                {
                    // Get the color from the texture image
                    temp_diffus += temp_closest_object->getFloorPlaneTexter()->getColor(pixel_at_image.x, pixel_at_image.y);
                    //temp_spec += ofColor::lightGrey;
                }
                else{
                    temp_diffus += temp_closest_object->getDiffuseColor();
                }
            }
            else
            {
                temp_diffus += temp_closest_object->getDiffuseColor();
                temp_spec += temp_closest_object->getSpecularColor();
            }
            if(temp_closest_object->getReflectable())
            {
                glm::vec3 temp_ray_dir = temp_ray.getDirecton();
                temp_closest_normal = glm::normalize(temp_closest_normal);
                temp_ray_dir = glm::normalize(temp_ray_dir);
                glm::vec3 projection_vector = glm::dot(temp_ray_dir, temp_closest_normal)/(glm::length(temp_closest_normal)) * temp_closest_normal;
                glm::vec3 reflection_direction_vector = temp_ray_dir - 2 * projection_vector;
                reflection_direction_vector = glm::normalize(reflection_direction_vector);
                glm::vec3 off_set = temp_closest_point +  0.0001 * glm::normalize(temp_closest_normal);
                Ray reflection_ray(off_set,temp_ray_dir);
                this->_recusive_mirror_reflection(reflection_ray, level+1,temp_diffus,temp_spec);
                return;
            }
            return;
        }
        return;
    }
}
float RayTracingSystem::_scene_SDF(const glm::vec3 pos,SceneObject*& obj_selected)
{
    float temp_min_sdf = std::numeric_limits<float>::max();
    for(int i =0;i<this->_scene_object_list.size();i++)
    {
        float temp_result = this->_scene_object_list.at(i)->sdf(pos);
        if(temp_result < temp_min_sdf) {
            temp_min_sdf = temp_result;
            obj_selected = this->_scene_object_list.at(i);
        }
    }
    return temp_min_sdf;
}
bool RayTracingSystem::_ray_marching(Ray r,glm::vec3& hit_point,glm::vec3& normal,SceneObject*& obj_selected)
{
    bool result = false;
    float hit_threshold_value = 0.01;
    float unhit_threshold_value = 2000;
    glm::vec3 ray_begin_pos = r.getPoint();
    float temp_distance;
    for(int i=0;i<this->_maximum_ray_marching_steps;i++)
    {
        temp_distance = this->_scene_SDF(ray_begin_pos,obj_selected);
       
        if(temp_distance < hit_threshold_value){
            hit_point = ray_begin_pos;
            normal = this->_get_normal_ray_marching(ray_begin_pos);
            return true;
        }
        // If unhit has been determined.
        else if(temp_distance > unhit_threshold_value) return false;
        else ray_begin_pos += r.getDirecton() * temp_distance;
    }
    return false;
}
glm::vec3 RayTracingSystem::_get_normal_ray_marching(const glm::vec3 &p)
{
    float eps = 0.01;
    SceneObject* unused = nullptr;
    float dp = this->_scene_SDF(p,unused);
    glm::vec3 n( dp - this->_scene_SDF(glm::vec3(p.x-eps,p.y,p.z),unused),
                 dp - this->_scene_SDF(glm::vec3(p.x,p.y-eps,p.z),unused),
                 dp - this->_scene_SDF(glm::vec3(p.x,p.y,p.z-eps),unused)
                );
    return glm::normalize(n);
}
void RayTracingSystem::setIsUsingRayMarchingTechnique(bool isUsingRayMarching)
{
    this->_is_using_ray_marching_rending_image = isUsingRayMarching;
}
bool RayTracingSystem::get_is_using_ray_marching()
{
    return this->_is_using_ray_marching_rending_image;
}

