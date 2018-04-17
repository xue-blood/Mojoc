/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2012-12-25
 * Author: scott.cgi
 */

#include <string.h>
#include <stdlib.h>

#include "Engine/Graphics/Draw/Quad.h"
#include "Engine/Graphics/OpenGL/GLTool.h"


static void Init(float width, float height, Quad* outQuad)
{
    outQuad->width          =  width;
    outQuad->height         =  height;
    
    outQuad->offsetCenterX  = -width  / 2;
    outQuad->offsetCenterY  =  height / 2;
    
    outQuad->offsetTextureX =  0.0f;
    outQuad->offsetTextureY =  0.0f;
}


static Quad* Create(float width, float height)
{
    Quad* quad = (Quad*) malloc(sizeof(Quad));
    Init(width, height, quad);

    return quad;
}


static void MaxSize(Array(Quad)* quadArr,  float* outWidth, float* outHeight)
{
    Quad* quads  = AArray_GetData(quadArr, Quad);
    Quad* quad   = quads;

    float leftX  = quad->offsetCenterX;
    float leftY  = quad->offsetCenterY;

    float rightX = leftX + quad->width;
    float rightY = leftY - quad->height;

    for (int i = 1; i < quadArr->length; i++)
    {
        quad            = quads + i;
        float tmpLeftX  = quad->offsetCenterX;
        float tmpLeftY  = quad->offsetCenterY;

        float tmpRightX = tmpLeftX + quad->width;
        float tmpRightY = tmpLeftY - quad->height;

        // find the min x
        if (tmpLeftX < leftX)
        {
            leftX = tmpLeftX;
        }

        // find the max y
        if (tmpLeftY > leftY)
        {
            leftY = tmpLeftY;
        }

        // find the max x
        if (tmpRightX > rightX)
        {
            rightX = tmpRightX;
        }

        // find the min y
        if (tmpRightY < rightY)
        {
            rightY = tmpRightY;
        }
    }

    *outWidth  = rightX - leftX;
    *outHeight = leftY  - rightY;
}


static void GetQuadVertex(Quad* quad, Texture* texture, float outVertexData[Quad_VertexNum])
{
    float qx = quad->offsetCenterX;
    float qy = quad->offsetCenterY;

    float qw = qx + quad->width;
    float qh = qy - quad->height;

    float tx = AGLTool_ToUVWidth (quad->offsetTextureX, texture->width);
    float ty = AGLTool_ToUVHeight(quad->offsetTextureY, texture->height);

    float tw = tx + AGLTool_ToUVWidth (quad->width,  texture->width);
    float th = ty + AGLTool_ToUVHeight(quad->height, texture->height);

    memcpy
    (
        outVertexData,
        (
            (float[])
            {
                qx, qy, // Position 0
                tx, ty, // TexCoord 0
          
                qx, qh, // Position 1
                tx, th, // TexCoord 1
          
                qw, qh, // Position 2
                tw, th, // TexCoord 2
          
                qw, qy, // Position 3
                tw, ty, // TexCoord 3
            }
        ),
        Quad_VertexNumBytes
    );
}


static void GetQuadPosition3(Quad* quad, float outBornPositionData[Quad_Position3Num])
{
    float qx = quad->offsetCenterX;
    float qy = quad->offsetCenterY;

    float qw = qx + quad->width;
    float qh = qy - quad->height;

    memcpy
    (
        outBornPositionData,
        (
            (float[])
            {
                qx, qy, 0.0f, // Position 0
        
                qx, qh, 0.0f, // Position 1
        
                qw ,qh, 0.0f, // Position 2
        
                qw, qy, 0.0f, // Position 3
            }
        ),
        Quad_Position3NumBytes
    );
}


static void GetQuadUV(Quad* quad, Texture* texture, float outUVData[Quad_UVNum])
{
    float tx = AGLTool_ToUVWidth (quad->offsetTextureX, texture->width);
    float ty = AGLTool_ToUVHeight(quad->offsetTextureY, texture->height);

    float tw = tx + AGLTool_ToUVWidth (quad->width,  texture->width);
    float th = ty + AGLTool_ToUVHeight(quad->height, texture->height);

    memcpy
    (
        outUVData,
        (
            (float[])
            {
                tx, ty, // TexCoord 0

                tx, th, // TexCoord 1

                tw, th, // TexCoord 2

                tw, ty, // TexCoord 3
            }
        ),
        Quad_UVNumBytes
    );
}


static void GetQuadIndex(int vertexNumBefore, short outIndexData[Quad_IndexNum])
{
    memcpy
    (
        outIndexData,
        (
            (short[])
            {
                (short) (0 + vertexNumBefore),
                (short) (1 + vertexNumBefore),
                (short) (2 + vertexNumBefore),

                (short) (2 + vertexNumBefore),
                (short) (3 + vertexNumBefore),
                (short) (0 + vertexNumBefore),
            }
        ),
        Quad_IndexNumBytes
    );
}


struct _AQuad AQuad[1] =
{
    Create,
    Init,
    MaxSize,

    GetQuadVertex,
    GetQuadPosition3,
    GetQuadUV,
    GetQuadIndex,
};
