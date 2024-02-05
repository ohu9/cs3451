//#####################################################################
// Main
// CS3451 Computer Graphics Starter Code
// Contact: Bo Zhu (bo.zhu@gatech.edu)
//#####################################################################
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "OpenGLMesh.h"
#include "OpenGLMarkerObjects.h"
#include "OpenGLCommon.h"
#include "OpenGLWindow.h"
#include "OpenGLViewer.h"
#include "TinyObjLoader.h"

#ifndef __Main_cpp__
#define __Main_cpp__

#ifdef __APPLE__
#define CLOCKS_PER_SEC 100000
#endif

#define DegreesToRadians(degrees) (degrees * M_PI / 180)

class MyDriver : public OpenGLViewer
{
	std::vector<OpenGLTriangleMesh*> mesh_object_array;						////mesh objects, every object you put in this array will be rendered.
	OpenGLSegmentMesh* floor=nullptr;
	std::vector<OpenGLSegmentMesh*> coords, trajectory;
	clock_t startTime;
public:
	virtual void Initialize()
	{
		//// If you want to change the current background color: 		
		//// Goto OpenGLShaderProgrammcpp Line 247 and 248 and change the two colors

		draw_bk=true;						//// This flag specifies a customized way to draw the background. If you turn it off, there is no background.
		draw_axes=false;					//// This flag controls the rendering of the default axes (turned off by default)
		startTime=clock();
		OpenGLViewer::Initialize();
		opengl_window->camera_distance = 25.f;
		opengl_window->camera_target = Vector3f(0, 3.5, 0);
		opengl_window->Update_Clip_Planes();
	}

	virtual void Initialize_Data()
	{
		OpenGLShaderLibrary::Instance()->Add_Shader_From_File("a3_vert.vert","a3_frag.frag","a3_shading");	////bind shader for this assignment
		Create_Angry_Bird_Palace();
	}

	void Create_Angry_Bird_Palace()
	{
		//// draw the three axes
		Add_Coord({ Vector3(0, 0, 0), Vector3(5, 0, 0) }, OpenGLColor(1, 0, 0, 1));	//// X axis
		Add_Coord({ Vector3(0, 0, 0), Vector3(0, 5, 0) }, OpenGLColor(0, 1, 0, 1));	//// Y axis
		Add_Coord({ Vector3(0, 0, 0), Vector3(0, 0, 5) }, OpenGLColor(0, 0, 1, 1));	//// Z zxis
		// 		
		//// draw the ground
		Add_Ground();

		// add castle
		auto castle = Add_Tranformable_Obj_From_File("castle.obj",OpenGLColor(.5f,.5f,.5f,1.f));
		{
			Matrix4f t;
			t << 5., 0., 0., 0.,
				 0., 5., 0., 1.3,
				 0., 0., 5., 0.,
				 0., 0., 0., 1.;
			float angle = 3.1415927f * -.5f;
			Matrix4f r;
			r << cos(angle), 0., -sin(angle), 0.,
				0., 1., 0., 0.,
				sin(angle), 0., cos(angle), 0.,
				0., 0., 0., 1.;

			castle->Set_Model_Matrix(t*r);
		}
		
		//// add axes
		auto axes = Add_Tranformable_Obj_From_File("axes.obj", OpenGLColor(.9f, .5f, .0f, 1.f));
		{
			Matrix4f r;
			float angle = 3.1415927f * -.5f;
			r << cos(angle), 0., -sin(angle), 0.,
				0., 1., 0., 0.,
				sin(angle), 0., cos(angle), 0.,
				0., 0., 0., 1.;

			Matrix4f t;
			t << 2., 0., 0., 6.,
				0., 2., 0., 1.,
				0., 0., 2., 0.,
				0., 0., 0., 1.;

			Matrix4f transform = t * r;
			axes->Set_Model_Matrix(transform);
		}

		//// add tower
		auto tower = Add_Tranformable_Obj_From_File("tower.obj", OpenGLColor(.0f, .5f, .5f, 1.f));
		{
			Matrix4f r;
			float angle = 3.1415927f * .25f;
			r << cos(angle), 0., -sin(angle), 0.,
				0., 1., 0., 0.,
				sin(angle), 0., cos(angle), 0.,
				0., 0., 0., 1.;

			Matrix4f t;
			t << 2., 0., 0., -6.,
				0., 6., 0., 3.,
				0., 0., 2., 0.,
				0., 0., 0., 1.;

			Matrix4f transform = t * r;
			tower->Set_Model_Matrix(transform);
		}

		//// add trees
		int tree_num = 24;
		float theta = 3.1415927f * 2.f / (float)tree_num;
		for (int i = 0; i < tree_num; i++) {
			float angle = theta * (float)i;
			auto tree = Add_Tranformable_Obj_From_File("tree1.obj", OpenGLColor(0.f, 1.f, 0.f, 1.f));
			{
				Matrix4f r;
				r << cos(angle), 0., -sin(angle), 0.,
					0., 1., 0., 0.,
					sin(angle), 0., cos(angle), 0.,
					0., 0., 0., 1.;
				Matrix4f t;
				t << 1., 0., 0., 8.,
					 0., 1., 0., 0.5,
					 0., 0., 1., 0.,
					 0., 0., 0., 1.;
				Matrix4f transform = r * t;
				tree->Set_Model_Matrix(transform);
			}
		}

		int tree2_num = 36;
		float theta2 = 3.1415927f * 2.f / (float)tree2_num;
		for (int i = 0; i < tree2_num; i++) {
			float angle = theta2 * (float)i;
			auto tree = Add_Tranformable_Obj_From_File("tree2.obj", OpenGLColor(0.f, 1.f, 0.f, 1.f));
			{
				Matrix4f r;
				r << cos(angle), 0., -sin(angle), 0.,
					0., 1., 0., 0.,
					sin(angle), 0., cos(angle), 0.,
					0., 0., 0., 1.;
				Matrix4f t;
				t << 1., 0., 0., 10.,
					0., 1., 0., 0.5,
					0., 0., 1., 0.,
					0., 0., 0., 1.;
				Matrix4f transform = r * t;
				tree->Set_Model_Matrix(transform);
			}
		}

		//// add angry birds
		/**
		 * Capture keyframes of a throwing bird
		 * An angry bird is thrown from (-5, 0, 0) with initial velocity (5, 9.8, 0) (unit/sec)
		 * and angular velocity omega = 150 (deg/sec) clockwise (be careful about the direction of rotation)
		 * Given gravity g = -9.8 (unit/sec) in y direction
		 * Compute x using x = x0 + ux * t
		 * Compute y using y = uy * t - 0.5 * g * t * t
		 * your goal is to draw 6 birds at time t = 0.2, 0.5, 0.8, 1.1, 1.4, 1.7 respectively.
		**/

		//Add_Arc_Trajectory();

		std::vector<float> time = { 0.2, 0.5, 0.8, 1.1, 1.4, 1.7, 2. };
		int bird_num = 6;
		float omega = -3.1415927f * 2.f * 150.f / 360.f;
		float ux = 5.f;
		float uy = 9.8f;
		float g = 9.8f;
		for (int i = 0; i < bird_num; i++) {
			float t = time[i];
			float angle = omega*t;
			float x = -5. + ux * t;
			float y = uy * t - 0.5 * g * t * t;

			auto bird = Add_Tranformable_Obj_From_File("bird.obj", OpenGLColor(1.f, 0.2f, 0.f, 1.f));
			{
				Matrix4f t;
				t << cos(angle), -sin(angle), 0., x,
					 sin(angle), cos(angle), 0., y,
					0., 0., 1., 0.,
					0., 0., 0., 1.;
				bird->Set_Model_Matrix(t);
			}
		}

		// draw a cube
		for (int i = 0; i < 5; i++) {
			float offset = 3. + (float)i;
			auto cube1 = Add_Cube(1.f, OpenGLColor(1.f, 1.f, 1.f, 1.f));
			{
				Matrix4f t;
				t << 1, 0, 0, 0,
					0, 0.1, 0, 0.,
					0, 0, 0.5, offset,
					0, 0, 0, 1;
				cube1->Set_Model_Matrix(t);
			}
		}
	}

	//////////////////////////////////////////////////////////////
	//// The following functions are auxiliary functions to add mesh objects into the scene
	//////////////////////////////////////////////////////////////
	
	//// This function adds a mesh object from an obj file
	int Add_Obj_Mesh_Object(std::string obj_file_name)
	{
		auto mesh_obj = Add_Interactive_Object<OpenGLTriangleMesh>();

		Array<std::shared_ptr<TriangleMesh<3> > > meshes;
		Obj::Read_From_Obj_File(obj_file_name, meshes);
		mesh_obj->mesh = *meshes[0];
		std::cout << "load tri_mesh from obj file, #vtx: " << mesh_obj->mesh.Vertices().size() << ", #ele: " << mesh_obj->mesh.Elements().size() << std::endl;

		mesh_object_array.push_back(mesh_obj);
		return (int)mesh_object_array.size() - 1;
	}

	//// This function adds a mesh object from an .obj file and allows the user to specify its model matrix
	OpenGLTriangleMesh* Add_Tranformable_Obj_From_File(std::string file_name, OpenGLColor color = OpenGLColor::White())
	{
		int obj_idx = Add_Obj_Mesh_Object(file_name);
		auto obj = mesh_object_array[obj_idx];
		obj->use_model_matrix = true; // enable model matrix to be set to shader
		obj->color = color; // set color

		obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("a3_shading"));
		Set_Polygon_Mode(obj, PolygonMode::Fill);
		Set_Shading_Mode(obj, ShadingMode::A2);
		obj->Set_Data_Refreshed();
		obj->Initialize();

		return obj;
	}
	//// This function adds a cube with a specified length and color
	OpenGLTriangleMesh* Add_Cube(float length = 1, OpenGLColor color = OpenGLColor::White()) {
		auto obj = Add_Interactive_Object<OpenGLTriangleMesh>();
		mesh_object_array.push_back(obj);
		obj->use_model_matrix = true; // enable model matrix to be set to shader
		obj->color = color; // set color
		// set up vertices and elements
		std::vector<Vector3> vertices{Vector3(0,0,0),Vector3(1,0,0),Vector3(0,1,0),Vector3(1,1,0), Vector3(0,0,1),Vector3(1,0,1),Vector3(0,1,1),Vector3(1,1,1)};
		std::vector<Vector3i> elements{Vector3i(4,5,7),Vector3i(4,7,6),
										Vector3i(5,1,7),Vector3i(7,1,3),
										Vector3i(2,3,1),Vector3i(0,2,1),
										Vector3i(6,2,4),Vector3i(2,0,4),
										Vector3i(2,6,3),Vector3i(6,7,3),
										Vector3i(0,1,4),Vector3i(1,5,4)};
		for (auto& v3 : vertices) {v3 -= Vector3(0.5, 0.5, 0.5); v3 *= length;};
		obj->mesh.Vertices() = vertices;
		obj->mesh.Elements() = elements;
		
		obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("a3_shading"));
		Set_Polygon_Mode(obj, PolygonMode::Fill);
		Set_Shading_Mode(obj, ShadingMode::A2);
		obj->Set_Data_Refreshed();
		obj->Initialize();

		return obj;
	}

	//// This function adds an axis with a specified color
	void Add_Coord(std::vector<Vector3> pts, OpenGLColor color)
	{
		auto axis = Add_Interactive_Object<OpenGLSegmentMesh>();
		coords.push_back(axis);
		Set_Polygon_Mode(axis, PolygonMode::Fill);
		Set_Shading_Mode(axis, ShadingMode::None);
		auto line_mesh = &axis->mesh;
		line_mesh->Vertices() = pts;
		line_mesh->Elements() = { Vector2i(0,1) };
		Set_Line_Width(axis, 2.5f);
		Set_Color(axis, color);
		axis->Set_Data_Refreshed();
		axis->Initialize();
	}

	//// This function adds a wireframe ground
	void Add_Ground()
	{
		floor = Add_Interactive_Object<OpenGLSegmentMesh>();
		Set_Polygon_Mode(floor, PolygonMode::Fill);
		Set_Shading_Mode(floor, ShadingMode::None);
		auto line_mesh = &floor->mesh;
		std::vector<Vector3> pts;
		std::vector<Vector2i> eles;
		for (int i = -10; i <= 10; i++) {
			if (i == 0) {
				pts.push_back(Vector3(i, 0, -10));
				pts.push_back(Vector3(i, 0, 0));
				pts.push_back(Vector3(-10, 0, i));
				pts.push_back(Vector3(0, 0, i));
			}
			else {
				pts.push_back(Vector3(i, 0, -10));
				pts.push_back(Vector3(i, 0, 10));
				pts.push_back(Vector3(-10, 0, i));
				pts.push_back(Vector3(10, 0, i));
			}
		}
		for (int i = 0; i < pts.size(); i += 2) {
			eles.push_back(Vector2i(i, i + 1));
		}
		line_mesh->Vertices() = pts;
		line_mesh->Elements() = eles;
		Set_Line_Width(floor, 3.f);
		Set_Color(floor, OpenGLColor(0, 0, 0, 1));
		floor->Set_Data_Refreshed();
		floor->Initialize();
	}

	//// This function adds a parabola trajectory
	void Add_Arc_Trajectory()
	{
		float ux = 5, uy = 9.8, g = 9.8;
		std::vector<Vector3> pts;
		std::vector<Vector2i> eles;
		for (float t = 0; t <= 2; t += 0.02) {
			float x = ux * t - 5;
			float y = uy * t - 0.5 * g * t * t;
			pts.push_back(Vector3(x, y, 0));
		}
		for (int i = 0; i < pts.size() - 1; i++) {
			eles.push_back(Vector2i(i, i + 1));
		}
		auto traj = Add_Interactive_Object<OpenGLSegmentMesh>();
		trajectory.push_back(traj);
		Set_Polygon_Mode(traj, PolygonMode::Fill);
		Set_Shading_Mode(traj, ShadingMode::None);
		auto line_mesh = &traj->mesh;
		line_mesh->Vertices() = pts;
		line_mesh->Elements() = eles;
		Set_Line_Width(traj, 2.f);
		Set_Color(traj, OpenGLColor(0, 0, 1, 1));
		traj->Set_Data_Refreshed();
		traj->Initialize();
	}

	void Init_Bird_Vertices(OpenGLTriangleMesh* obj)
	{
		std::vector<Vector3>& vertices = obj->mesh.Vertices();
		for (auto& v : vertices) {
			v += Vector3(-8.35, 0, 0);
			auto x = v.x(); v.x() = v.z(); v.z() = -x;
			v /= 10.f;
		}
	}

	//// Go to next frame 
	virtual void Toggle_Next_Frame()
	{
		for (auto& mesh_obj : mesh_object_array) {
			mesh_obj->setTime(GLfloat(clock() - startTime) / CLOCKS_PER_SEC);
		}
		OpenGLViewer::Toggle_Next_Frame();
	}

	virtual void Run()
	{
		OpenGLViewer::Run();
	}
};

int main(int argc,char* argv[])
{
	MyDriver driver;
	driver.Initialize();
	driver.Run();	
}

#endif