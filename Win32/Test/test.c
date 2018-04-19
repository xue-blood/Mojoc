
#include "Engine/Application/Application.h"
#include "Engine/Toolkit/Utils/Coroutine.h"
#include "Engine/Toolkit/Platform/Log.h"
#include "Engine/Toolkit/Platform/File.h"

#include "Engine/Graphics/OpenGL/GLTool.h"
#include "Engine/Graphics/OpenGL/GLInfo.h"

void Test_init();

struct _Test
{
	Component component[1];

	void(*Init)();
} Test[1] = {
	{
		.Init = Test_init
	}
};
void Test_update(Component* component, float delta){
	GLfloat data[] = { 1.0, 0.0, 0.0, 0, 0,
		0.0, 1.0, 0.0, .9, .9,
		0.0, 0.0, 1.0, .9, -.9,
		1.0, 0.0, 1.0, -.2, -.4 };
	GLubyte index[] = { 0, 1, 2, 3 };


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glColorPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), &data[0]);
	glVertexPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), &data[3]);

	glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_BYTE, index);
}

void Test_onmsg(Component* component, void* sender, int subject, void* extraData){

}

void Test_init(){

	Array(int) *ints = AArray_Make(int, 2, 2, 3);
	Array(int) ints1 = AArray_Init(int, 3, 2, 3, 4);

	int a = AArray_Get(ints, 1, int);


	ArrayList(int) intss = AArrayList_Init(int, 5);

	AComponent->Init(Test->component);

	Test->component->curState->Update = Test_update;
	Test->component->curState->OnMessage = Test_onmsg;

	AApplication_AppendChild(Test->component);
}



void OnReady(){

}

void OnDestroy(){

}
void LoadingRun(Coroutine* coroutine){

	ACoroutine_Begin();


	ALog_W("ACoroutine_YieldSeconds(2.5f);");
	ACoroutine_YieldSeconds(2.5f);


	ALog_W("ACoroutine_YieldSeconds(2.5f);");
	ACoroutine_YieldSeconds(2.5f);


	ALog_W("ACoroutine_End;");
	ACoroutine_End();
}

#include <stdio.h>
void Application_Main()
{
	char* path = AFile->GetAbsoluteDirPath();
	FILE* f = fopen("Font/hp.atlas", "rb");

	AApplication->callbacks->OnReady = OnReady;
	AApplication->callbacks->OnDestroy = OnDestroy;

	Test->Init();

	ACoroutine->StartCoroutine(LoadingRun);
}
