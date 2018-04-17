/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2012-12-29
 * Author: scott.cgi
 */

#ifndef TEXTURE_H
#define TEXTURE_H


#include "Engine/Graphics/OpenGL/Platform/gl3.h"
#include "Engine/Toolkit/Head/Define.h"


typedef struct
{
    /**
     *  The openGL generated texture id
     */
    GLuint id;

    /**
     * The texture width
     */
    float  width;

    /**
     * The texture height
     */
    float  height;

    /**
     * All texture chaced in ArrayStrMap by filePath
     *
     * filePath: ArrayStrMap's key
     */
    char*  filePath;
}
Texture;


/**
 * Cache all texture with filePath as key
 */
struct _ATexture
{
    /**
     * Get Texture by filePath, not found will create one
     */
    Texture*  (*Get)    (char* filePath);

    /**
     * Release texture memory both in GPU and CPU
     * removed from cache
     */
    void      (*Release)(Texture* texture);
};


extern struct _ATexture ATexture[1];


#endif
