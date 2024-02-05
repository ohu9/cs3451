//#####################################################################
// Main
// CS3451 Computer Graphics Starter Code
// Contact: Bo Zhu (bo.zhu@gatech.edu)
//#####################################################################
#include <iostream>
#include <random>

#include "OpenGLMesh.h"
#include "OpenGLCommon.h"
#include "OpenGLWindow.h"
#include "OpenGLViewer.h"

const std::string author="Olivia Hu";

/////////////////////////////////////////////////////////////////////
//// These are helper functions we created to generate circles and triangles by testing whether a point is inside the shape or not.
//// They can be used in the paintGrid function as "if the pixel is inside, draw some color; else skip."
//// You may create your own functions to draw your own shapes

//// The paintGrid function is implemented as a GLSL fragment shader. 
//// The GLSL grammar is C-style, and if you are curious about its full picture (which we will start to learn the details in Week 3), 
//// you may find more information on https://www.khronos.org/files/opengl43-quick-reference-card.pdf (Page 6 - 7 would probably be helpful!)
//// You don't need advanced GLSL features for this assignment (reading the starter code should be enough).
//// You can also test it (copy the whole string) in Shadertoy: https://www.shadertoy.com/new    
/////////////////////////////////////////////////////////////////////

const std::string draw_pixels=To_String(
const float M_PI=3.1415926535; 

// The side length of the minimum unit (or the new "pixels")
const float PIXEL_SIZE=10.; 

// To check if a point is inside a circle
bool inCircle(vec2 p, vec2 center, float radius) {
	vec2 to_center=p - center;
	if (dot(to_center, to_center) < radius * radius) {
		return true;
	}
	return false;
}

// To check if a point is inside an ellipse (a = x axis, b = y axis)
bool inEllipse(vec2 p, vec2 center, float a, float b) {
	if ( (pow((p.x - center.x), 2) / pow(a, 2)) 
	   + (pow((p.y - center.y), 2) / pow(b, 2)) < 1) {
		return true;
	}
	return false;
}

// To check if a point is inside a triangle
bool inTriangle(vec2 p, vec2 p1, vec2 p2, vec2 p3) {
	if (dot(cross(vec3(p2 - p1, 0), vec3(p - p1, 0)), cross(vec3(p2 - p1, 0), vec3(p3 - p1, 0))) >= 0. &&
		dot(cross(vec3(p3 - p2, 0), vec3(p - p2, 0)), cross(vec3(p3 - p2, 0), vec3(p1 - p2, 0))) >= 0. &&
		dot(cross(vec3(p1 - p3, 0), vec3(p - p3, 0)), cross(vec3(p1 - p3, 0), vec3(p2 - p3, 0))) >= 0.) {
		return true;
	}
	return false;
}

// To check if a point is inside a reactangle (1 is bottom left, 2 is top right)
bool inRectangle(vec2 p, vec2 p1, vec2 p2) {
	if (p.x >= p1.x &&
		p.x <= p2.x &&
		p.y >= p1.y &&
		p.y <= p2.y) {
		return true;
	}
	return false;
}

// To convert from Polar Coordinates to Cartesian coordinates
vec2 polar2cart(float angle, float length) {
	return vec2(cos(angle) * length, sin(angle) * length);
}

/////////////////////////////////////////////////////////////////////
// Useful variables:											   //
// iTime: the passed seconds from the start of the program         //
// iResolution: the size of the window (default: 1280*960)         //
/////////////////////////////////////////////////////////////////////

// Return the rgba color of the grid at position (x, y) 
vec4 paintGrid(float x, float y) {
	bool coffee = inEllipse(vec2(x, y), vec2(64, 65), 17,7);
	bool rim = inEllipse(vec2(x, y), vec2(64, 65), 18, 8);
	bool cup = inRectangle(vec2(x, y), vec2(46,46), vec2(82,65));
	bool cupbottom = inCircle(vec2(x, y), vec2(64,46), 19);
	bool handle = inEllipse(vec2(x, y), vec2(82, 50), 11, 12) && !inEllipse(vec2(x, y), vec2(82, 50), 6, 8);

	bool coffeelight = inEllipse(vec2(x, y), vec2(64, 65), 16,6) && !inEllipse(vec2(x, y), vec2(60, 64), 16,6);
	bool coffeeshadow = inEllipse(vec2(x, y), vec2(64, 65), 16,6) && !inEllipse(vec2(x, y), vec2(68, 66), 16,6);
	bool cuplight = (inCircle(vec2(x, y), vec2(64,46), 18) //offset cupbottom
				&& !inCircle(vec2(x, y), vec2(70,46), 18) 
				&& inTriangle(vec2(x, y), vec2(46, 27), vec2(82, 27), vec2(46, 41)))
				|| inRectangle(vec2(x, y), vec2(47, 27), vec2(52, 65)) && (cup || inCircle(vec2(x, y), vec2(64,46), 18));
	bool cupshadow = (inCircle(vec2(x, y), vec2(64,46), 18) //offset cupbottom
				&& !inCircle(vec2(x, y), vec2(61,46), 18))
				|| inRectangle(vec2(x, y), vec2(76, 27), vec2(81, 64)) && (cup || inCircle(vec2(x, y), vec2(64,46), 18));
	bool rimlight = rim && inTriangle(vec2(x, y), vec2(46, 57), vec2(82, 57), vec2(46, 72));
	bool handlelight = handle && inEllipse(vec2(x, y), vec2(83, 48), 6, 8);
	
	bool shadow = inEllipse(vec2(x, y), vec2(72, 35), 22,7);

	if (coffeelight) {
		return vec4(vec3(242, 212, 174) / 255., 1.); 
	}
	else if (coffeeshadow) {
		return vec4(vec3(133, 101, 62) / 255., 1.); 
	}
	else if (coffee) {
		return vec4(vec3(191, 152, 103) / 255., 1.); 
	}
	else if (rimlight) {
		return vec4(1.); 
	}
	else if (rim) {
		return vec4(vec3(245, 242, 240) / 255., 1.); 
	}
	else if (cuplight) {
		return vec4(1.); 
	}
	else if (cupshadow) {
		return vec4(vec3(214, 212, 210) / 255., 1.); 
	}
	else if (cup) {
		return vec4(vec3(245, 242, 240) / 255., 1.); 
	}
	else if (cupbottom) {
		return vec4(vec3(245, 242, 240) / 255., 1.); 
	}
	else if (handlelight) {
		return vec4(vec3(245, 242, 240) / 255., 1.); 
	}
	else if (handle) {
		return vec4(vec3(189, 186, 183) / 255., 1.); 
	}
	else if (shadow) {
		return vec4(vec3(150, 148, 146) / 255., 1.); 
	}
	else { //background
		// return vec4(vec3(225-y, 255-x, 159) / 255., 1.);
		return vec4(vec3(195-y, 255-x, 159) / 255., 1.);
	}

}

// The function called in the fragment shader
void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
	// To divide the screen into the grids for painting!
	fragColor=paintGrid(floor(fragCoord.x / PIXEL_SIZE), floor(fragCoord.y / PIXEL_SIZE));
}

);

class ScreenDriver : public OpenGLViewer
{
	OpenGLScreenCover* screen_cover=nullptr;
	clock_t startTime=clock();

public:
	virtual void Initialize()
	{
		OpenGLViewer::Initialize();
	}

	//// Initialize the screen covering mesh and shaders
	virtual void Initialize_Data()
	{
		OpenGLShaderLibrary::Instance()->Create_Screen_Shader(draw_pixels, "shaderToy");
		screen_cover=Add_Interactive_Object<OpenGLScreenCover>();
		Set_Polygon_Mode(screen_cover, PolygonMode::Fill);
		Uniform_Update();

		screen_cover->Set_Data_Refreshed();
		screen_cover->Initialize();
		screen_cover->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("shaderToy"));
	}

	//// Update the uniformed variables used in shader
	void Uniform_Update()
	{
		screen_cover->setResolution((float)Win_Width(), (float)Win_Height());
		screen_cover->setTime(GLfloat(clock() - startTime) / CLOCKS_PER_SEC);
	}

	//// Go to next frame 
	virtual void Toggle_Next_Frame()
	{
		Uniform_Update();
		OpenGLViewer::Toggle_Next_Frame();
	}

	////Keyboard interaction
	virtual void Initialize_Common_Callback_Keys()
	{
		OpenGLViewer::Initialize_Common_Callback_Keys();
	}

	virtual void Run()
	{
		OpenGLViewer::Run();
	}
};

int main(int argc,char* argv[])
{
	if(author==""){std::cerr<<"***** The author name is not specified. Please put your name in the author string first. *****"<<std::endl;return 0;}
	else std::cout<<"Assignment 1 demo by "<<author<<" started"<<std::endl;
	ScreenDriver driver;
	driver.Initialize();
	driver.Run();	
}

