/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2016-1-28
 * Author: scott.cgi
 */

#include "Engine/Toolkit/Platform/Platform.h"


//----------------------------------------------------------------------------------------------------------------------
#ifdef IS_PLATFORM_WIN32
//----------------------------------------------------------------------------------------------------------------------


#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Application/Application.h"
#include "Engine/Toolkit/Utils/FileTool.h"
#include "Engine/Graphics/OpenGL/Platform/EGLTool.h"
#include "Engine/Toolkit/Platform/Log.h"
#include "Engine/Application/Application.h"
#include "Engine/Application/Input.h"

HINSTANCE gInstance;

enum
{
	LooperId_Input,
	LooperId_Sensor,
};

//----------------------------------------------------------------------------------------------------------------------


static struct
{
	GLFWwindow* window;

	// current window size
	int winX;
	int winY;

	int mouseBtn;	// save current mouse state
	int modKey;		// save the specify key state

	// mouse current position
	double mouseX;
	double mouseY;
}
AData[1] =
{
	0
};


//----------------------------------------------------------------------------------------------------------------------


//========================================================================
// Mouse position callback function
//========================================================================

static void cursorPosFun(GLFWwindow* window, double x, double y)
{
	AData->mouseX = x;
	AData->mouseY = y;

	if (AData->mouseBtn & (1 << GLFW_MOUSE_BUTTON_LEFT))
	{
		AApplication->Touch
			(
			AArray_Make
			(
			InputTouch*, 1,
			AInput->SetTouch
			(
			0,
			AData->mouseX,
			AData->mouseY,
			InputTouchType_Move
			)
			)
			);
	}
}

//========================================================================
// Mouse button callback function
//========================================================================

static void mouseButtonFun(GLFWwindow* window, int button, int action, int mods)
{
	// press mouse button
	if (action == GLFW_PRESS)
	{
		AData->mouseBtn |= 1 << button;
		AApplication->Touch
			(
			AArray_Make
			(
			InputTouch*, 1,
			AInput->SetTouch
			(
			0,
			AData->mouseX,
			AData->mouseY,
			InputTouchType_Down
			)
			)
			);
	}
	// release mouse button
	else
	{
		AData->mouseBtn &= ~(1 << button);
		AApplication->Touch
			(
			AArray_Make
			(
			InputTouch*, 1,
			AInput->SetTouch
			(
			0,
			AData->mouseX,
			AData->mouseY,
			InputTouchType_Up
			)
			)
			);
	}
}

//----------------------------------------------------------------------------------------------------------------------

static void OnWindowFocusChanged(HINSTANCE instance)
{
	ALog_D("hInstance OnWindowFocusChanged");
}


static void OnWindowResized(GLFWwindow* window, int x, int y)
{
	ALog_D("window OnWindowResized");
	AData->winX = x;
	AData->winY = y;
	AApplication->Resized(AData->winX, AData->winY);
}

static void OnFrameResized(GLFWwindow* window, int x, int y){
	ALog_D("frame OnWindowResized");

	AApplication->Resized(x, y);
}

static void OnGlfwError(int code, const char * err){
	MessageBoxA(NULL, err, "error", 0);
}


static void* MainLoop(void* param)
{
	//----------------------------------------------------------------------------------------------------------------------

	while (!glfwWindowShouldClose(AData->window))
	{
		// handle event
		glfwPollEvents();

		// application main loop
		AApplication->Loop();

		// render buffer
		glfwSwapBuffers(AData->window);
	}

	return NULL;
}

void initGLFW(){

	// init glfw
	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 16);

	glfwSwapInterval(1);



	// create window
	AData->winX = 640, AData->winY = 480;
	AData->window = glfwCreateWindow(AData->winX, AData->winY, "Simple example", NULL, NULL);
	if (!AData->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// setup callback
	glfwSetMouseButtonCallback(AData->window, mouseButtonFun);
	glfwSetCursorPosCallback(AData->window, cursorPosFun);
	glfwSetWindowSizeCallback(AData->window, OnWindowResized);
	glfwSetFramebufferSizeCallback(AData->window, OnFrameResized);
	glfwSetErrorCallback(OnGlfwError);

	glfwMakeContextCurrent(AData->window);

}

void initOGL(){

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Use Gouraud (smooth) shading
//	glShadeModel(GL_SMOOTH);
	// Switch on the z-buffer
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

//----------------------------------------------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance,    // HANDLE TO AN INSTANCE.  This is the "handle" to YOUR PROGRAM ITSELF.
	HINSTANCE hPrevInstance,// USELESS on modern windows (totally ignore hPrevInstance)
	LPSTR szCmdLine,        // Command line arguments.  similar to argv in standard C programs
	int iCmdShow)          // Start window maximized, minimized, etc.
{
	ALog_E("WinMain Start");
	gInstance = hInstance;

	initGLFW();
	initOGL();

	AApplication->Init();

	AApplication->GLReady(AData->winX, AData->winY);

	//----------------------------------------------------------------------------------------------------------------------

	MainLoop(NULL);

	//----------------------------------------------------------------------------------------------------------------------

	glfwDestroyWindow(AData->window);
	glfwTerminate();

	AApplication->Destroy();
}


//----------------------------------------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------------------------------------
