/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-4-6
 * Author: scott.cgi
 */

#ifndef BUFFER_READER_H
#define BUFFER_READER_H


#include <stdbool.h>
#include <stdint.h>
#include "Engine/Toolkit/Head/ArrayRange.h"


struct _ABufferReader
{
    /**
     * Read long from buffer data, where ArrayRange in buffer
     */
    int64_t (*ReadInt64)   (char* buffer, ArrayRange* range);

    /**
     * Read int from buffer data, where ArrayRange in buffer
     */
    int32_t (*ReadInt32)   (char* buffer, ArrayRange* range);

    /**
     * Read short from buffer data, where ArrayRange in buffer
     */
    int16_t (*ReadInt16)   (char* buffer, ArrayRange* range);

    /**
     * Read byte from buffer data, where ArrayRange in buffer
     */
    int8_t (*ReadInt8)     (char* buffer, ArrayRange* range);

    /**
     * Read line from buffer data, where ArrayRange in buffer
     * and record line ArrayRange
     */
    void   (*ReadLine)     (char* buffer, ArrayRange* range, ArrayRange* outLine);

    /**
     * Find string in buffer and make range start after string
     * return true found string or false not found
     */
    bool   (*TryFindString)(char* buffer, ArrayRange* range, char* str);
};


extern struct _ABufferReader ABufferReader[1];


#endif
