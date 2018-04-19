/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-9-8
 * Author: scott.cgi
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <stdbool.h>


struct _AGraphics
{
    /**
     * Default false
     * setting by method SetUseMapBuffer
     */
    bool isUseMapBuffer;

    /**
     * Initialize graphics each modules
     */
    void (*Init)           ();

    /**
     * If glMapBufferRange not support will use glBufferSubData
     * if not use VBO no effect
     */
    void (*SetUseMapBuffer)(bool isUseMapBuffer);
};


extern struct _AGraphics AGraphics[1];


#endif
