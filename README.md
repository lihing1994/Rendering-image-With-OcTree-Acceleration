# Introduction
The goal of the project is to implement the Octree acceleration algorithm and use it to improve the performance of the rendering system, which has been implemented previous([Click herer to view the previous project](https://github.com/lihing1994/Rendering-image)). The ray-tracing system was implemented using openFrameWork, which is C++ toolkit. In this GitHub page, it will only cover implementation that has been never discussed in the prevous project's page.

## Abstract
The Octree acceleration algorithm is a space partitioning algorithm using Axis Aligned Bounding Box(AABB) technique to keep dividing a three-dimensional space into eight sub three-dimensional space until a terminal condition is reached. In this project, the terminal condition can be either the sub three-dimensional space containing a number of renderable objects less than threshold value or the Octree has depth value that is equal to a preset value. 

## Implementation
In this project, a MeshObj class has been defined and implemented such that any Triangle-Mesh object can be loaded into the rendering system. As you can see in the image, implementation-1, the MeshObj is inherited from the SceneObject. Given that our ray-tracing system will render all the SceneObjects that were added into the RayTracingSystem, it guarantees that our MeshObj is able to be added into the system and be rendered. <br />
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
 ![CS116B Final Project Report -2](https://user-images.githubusercontent.com/25276186/126746527-e15c9ea9-3d2a-4ba7-bba7-b6a86b42df1f.jpg) <br/>
 ![CS116B Final Project Report -2](https://user-images.githubusercontent.com/25276186/126746685-7baf372a-963b-401c-be17-1c916121749d.jpg) <br/>
In the Octree class, there are two curial variables. One is called _root and the other
called _all_renderable_mesh_face_obj. The type of _root variable is the root node of the tree
while _all_renderable_mesh_face_obj is a list that contains all the faces of the Mesh object.
<br/>
In the constructor of Octree, it will start with finding out the boundary of the Mesh
object. As you can see in the implementation-5, it loops all the faces of Mesh, and marks
down the minimum and maximum value of x,y, and z coordinates of the Mesh. Once the
boundary of the Mesh is obtained, we are able to build the Octree for the Mesh object. As
you can see in the image, implementation-6, the _generate_octree function uses pre-order
traversal technique to recursively subdivide the 3D space by recursively calling the function
in the sub_divide function OctreeNode class. <br/>
![CS116B Final Project Report -2](https://user-images.githubusercontent.com/25276186/126746725-4dcb9c21-e2b3-4390-8446-a06a95ba5246.jpg) <br />
![CS116B Final Project Report -2](https://user-images.githubusercontent.com/25276186/126746729-8577f2e3-55d9-4888-8b46-ecfc9398e0ad.jpg)<br />
![CS116B Final Project Report -2](https://user-images.githubusercontent.com/25276186/126746739-8d9409c9-3958-46f9-bbe5-77c30388e306.jpg)<br />
In the OctreeNode class, it has several crucial member variables. The BoundingBox
which is an Axis Aligned Bounding Box(AABB) class. The _min and _max variables are
two variables that will pass into the constructor of BoundingBox. In other words, we can
consider that each OctreeNode has a BoundingBox that represents a volume of 3D space.
<br/>
The _child variable is a dynamic array that holds the child node of the OctreeNode
object. Finally the _mesh_list_face is a dynamic array that holds the faces of the Mesh,
where their position is within the node’s BoundingBox’s boundary. Then, as you can see in
the image, Implementation-8, at the constructor of OctreeNode, we added all the MeshFace
into the dynamic array when the MeshFace is within the volume of the OctreeNode’s
boundary.<br/>
![image](https://user-images.githubusercontent.com/25276186/126746813-0df032f2-111d-4503-9218-f144770bee02.png) <br/>
![image](https://user-images.githubusercontent.com/25276186/126746818-229eb868-db49-4709-86d9-34d7d94f5349.png)<br/>
In the OctreeNode class, there is a function called sub_divide. It will divide the
volume that the OctreeNode is representing into 8 different sub-volumes. As you can see in
the image, implementation-9, the 3D volume will be subdivided based on the x-y, y-z, and
x-z. Finally, we generate the subnode for this node and add it to the child list.<br/>
![image](https://user-images.githubusercontent.com/25276186/126746854-e0ede7be-265a-4873-95fc-9d72697bdd8e.png) <br/>
In the BoundingBox class, the intersect function is used to determine if there is
intersection between ray and with BoundingBox. The intersect function is implemented by
professor Amy Williams at University of Utah. Therefore, as you can see in the image,
Reference-1, it is the source code professor Amy Williams implemented and shared on the
GitHub page. In this project, there is a possibility that Ray has an intersection with
SceneObject that BoundingBox contains if and only if there is intersection between Ray and
BoundingBox itself.<br/>
![image](https://user-images.githubusercontent.com/25276186/126746888-74041550-9307-4575-bcc0-1ca0da9bd7ac.png)<br/>
As mentioned above, the MeshObj is inherited from SceneObject. When we check if
there is intersection between the Ray and MeshObj, we recursively check if there is
intersection between Ray and the BoundingBox. As you can see in the image,
Implementation-10, it is called the private helper function _intersect_helper and tests if there
is intersection between the ray and root node of Octree. If there is an intersection between ray
and the root node of Octree, then we recursively check if there is intersection between the
child node of Octree’s root node.<br/>
![image](https://user-images.githubusercontent.com/25276186/126746922-dab3174a-9ac0-4087-8d53-e4d746242345.png)<br/>
As you can see in the image, implementation-11, it shows you one of the base cases
of the private helper function _intersect_helper in the MeshObj class. When the number of
MeshFace object that a OctreeNode less than 30, we start to check if there is intersection
between each MeshFace object.<br/>
![image](https://user-images.githubusercontent.com/25276186/126746955-a4101cc3-06c0-4c79-be3e-34e98171ca37.png)<br/>


# Testing - I
Using OcTree to subdivide a triangle Mesh Object. 
State University.<br/>
![image](https://user-images.githubusercontent.com/25276186/126747205-19c6c3f5-fd76-4bcb-aba5-f565fdd42f3e.png)<br/>

# Testing - II
To render the following image, it took my MacBook Pro 16 inch 1.36 min to complete the
whole job. The Mesh contains 432 unique faces. The resolution of image is 3440x2293.
![image](https://user-images.githubusercontent.com/25276186/126747326-6ae40e8e-adf8-4ba7-a4da-86a005b3ab20.png)

# Testing - III
To render the following image, it took a Macbook Pro 16 inch laptop about 23.96 min to
complete the job. The resolution of image is 3440x2293.
Rendering environment included:
1. A mirror reflective table.
2. Two area lights.
3. A Mesh object with 432 unique faces.
![image](https://user-images.githubusercontent.com/25276186/126747469-e0af52fc-3e0a-41ba-aee2-8b09040857ac.png)

