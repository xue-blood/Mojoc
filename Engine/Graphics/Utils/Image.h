/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-08-30
 * Author: scott.cgi
 */

#ifndef IMAGE_H
#define IMAGE_H


#include "Engine/Toolkit/Head/Define.h"

typedef void(*ImageCallback)(void* pixel, float width, float height, void* extra);

struct _AImage
{
    /**
     * Read png pixel data from file, caller must be free it
     *
     * return NULL when error happened
     */
     bool (*CreatePixelDataFromPNG)(char* filePath, ImageCallback callback,void* param);
};


extern struct _AImage AImage[1];


#endif
