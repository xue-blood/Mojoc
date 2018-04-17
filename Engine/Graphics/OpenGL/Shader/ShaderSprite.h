/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-4-23
 * Author: scott.cgi
 */

#ifndef SHADER_SPRITE_H
#define SHADER_SPRITE_H


#include "Engine/Graphics/OpenGL/Platform/gl3.h"
#include "Engine/Toolkit/Math/Matrix.h"
#include "Engine/Toolkit/Math/Math.h"
#include "Engine/Graphics/Draw/Color.h"


struct _AShaderSprite
{
    GLuint program;
    GLuint attribPositionTexcoord;
    GLint  uniformSampler2D;
    GLint  uniformMVPMatrix;
    GLint  uniformColor;

    void (*Use) (Matrix4* mvpMatrix, Color* color);
    void (*Init)();
};


extern struct _AShaderSprite AShaderSprite[1];


#endif
