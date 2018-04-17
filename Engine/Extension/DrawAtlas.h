/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2017-1-5
 * Author: scott.cgi
 */

#ifndef DRAW_ATLAS_H
#define DRAW_ATLAS_H


#include "Engine/Extension/TextureAtlas.h"
#include "Engine/Graphics/OpenGL/Mesh.h"


typedef struct
{
    /**
     * DrawAtlas used TextureAtlas
     */
    TextureAtlas*        textureAtlas;

    /**
     * TextureAtlas used mesh
     */
    Mesh                 mesh    [1];

    /**
     * Quad in mesh texture
     */
    ArrayList(Drawable*) quadList[1];
}
DrawAtlas;


struct _ADrawAtlas
{
    DrawAtlas* (*Get)          (char*       filePath);
    Drawable*  (*GetQuad)      (DrawAtlas*  drawAtlas, char*     quadName);

    /**
     * Make drawAtlas can reuse in Get method
     */
    void       (*Reuse)        (DrawAtlas*  drawAtlas);

    /**
     * Make quad can reuse in GetQuad method
     */
    void       (*ReuseQuad)    (DrawAtlas* drawAtlas, Drawable* drawable);
};


extern struct _ADrawAtlas ADrawAtlas[1];


static inline void ADrawAtlas_Draw(DrawAtlas* drawAtlas)
{
    AMesh_Draw(drawAtlas->mesh);
}


#endif
