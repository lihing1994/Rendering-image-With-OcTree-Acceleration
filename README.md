# Introduction
The goal of the project is to implement the Octree acceleration algorithm and use it to improve the performance of the rendering system, which has been implemented previous([Click herer to view the previous project](https://github.com/lihing1994/Rendering-image)). The ray-tracing system was implemented using openFrameWork, which is C++ toolkit. In this GitHub page, it will only cover implementation that has been never discussed in the prevous project's page.

## Abstract
The Octree acceleration algorithm is a space partitioning algorithm using Axis Aligned Bounding Box(AABB) technique to keep dividing a three-dimensional space into eight sub three-dimensional space until a terminal condition is reached. In this project, the terminal condition can be either the sub three-dimensional space containing a number of renderable objects less than threshold value or the Octree has depth value that is equal to a preset value. 

## Implementation
In this project, a MeshObj class has been defined and implemented such that any Triangle-Mesh object can be loaded into the rendering system. As you can see in the image, implementation-1, the MeshObj is inherited from the SceneObject. Given that our ray-tracing system will render all the SceneObjects that were added into the RayTracingSystem, it guarantees that our MeshObj is able to be added into the system and be rendered. 
In addition, as you can see in the same image, a MeshObj also contains an object called _octree. The main reason why a MeshObj contains an Octree object is that we only want to subdivide a 3D space, where a Mesh is located. There is no need to subdivide a 3D space, where a geometry object located it. For example, the algorithm to find out if there is an intersection between a Ray and Sphere object is fast enough and we don’t need to use the Octree algorithm to render a geometry object.  
    ![image](https://user-images.githubusercontent.com/25276186/126746407-4b4fd22d-1875-4d0e-be5c-548ba4bddefa.png) <br />
In the constructor of the MeshObj, the translation matrix and rotation matrix has been
calculated. As you can see in the image Implementation-2, a matrix called _M_matrix has
been calculated. The _M_matrix is a combination of translation matrix and rotation matrix.
Then, we apply this matrix to each vertex of the Mesh so that we are able to
place any Mesh to the rendering system in any position at any angle. Once the Mesh has been
successfully loaded into the rendering system, the constructor MeshObj will generate an
Octree for the Mesh. Given that, a MeshObj is inherited from the SceneObject, it is also
necessary to overwrite the virtual function called draw. As you can see in the image,
implementation-3, the for-loop will draw each unique face of the Mesh on the screen.
 ![CS116B Final Project Report -2](https://user-images.githubusercontent.com/25276186/126746527-e15c9ea9-3d2a-4ba7-bba7-b6a86b42df1f.jpg)

