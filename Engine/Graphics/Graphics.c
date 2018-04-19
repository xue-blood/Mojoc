/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-9-8
 * Author: scott.cgi
 */

#include "Engine/Graphics/Graphics.h"
#include "Engine/Graphics/OpenGL/Shader/ShaderMesh.h"
#include "Engine/Graphics/OpenGL/Shader/ShaderSprite.h"
#include "Engine/Graphics/OpenGL/Shader/ShaderPrimitive.h"
#include "Engine/Graphics/OpenGL/GLInfo.h"


static void Init()
{
    AGLInfo         ->Init();
    AShaderMesh     ->Init();
    AShaderSprite   ->Init();
    AShaderPrimitive->Init();

    AGraphics->isUseMapBuffer = false;
}

static void SetUseMapBuffer(bool isUseMapBuffer)
{
    if (isUseMapBuffer && AGLInfo->version > 2.0f)
    {
        AGraphics->isUseMapBuffer = true;
    }
    else
    {
        AGraphics->isUseMapBuffer = false;
    }
}


struct _AGraphics AGraphics[1] =
{
    {
        .Init            = Init,
        .SetUseMapBuffer = SetUseMapBuffer,
    }
};
