/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2014-9-8
 * Author: scott.cgi
 */

#ifndef TOOLKIT_H
#define TOOLKIT_H


struct _AToolkit
{
    void (*Init)();
};


extern struct _AToolkit AToolkit[1];


#endif 
