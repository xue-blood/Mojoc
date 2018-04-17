/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2016-11-13
 * Author: scott.cgi
 */

#ifndef COROUTINE_H
#define COROUTINE_H


#include "Engine/Toolkit/Utils/ArrayList.h"
#include "Engine/Toolkit/Head/Define.h"


typedef enum
{
    /**
     * Coroutine wait for frame count to waitValue
     */
     CoroutineWaitType_Frames,

    /**
     * Coroutine wait for second count to waitValue
     */
     CoroutineWaitType_Seconds,

    /**
     * Coroutine wait for other Coroutine to finish
     */
     CoroutineWaitType_Coroutines,

    /**
     * Coroutine just run forward
     */
     CoroutineWaitType_Null,
}
CoroutineWaitType;


typedef enum
{
    /**
     * Coroutine enter queue ready to running
     */
     CoroutineState_Ready,

    /**
     * Coroutine has started to execute
     */
     CoroutineState_Running,

    /**
     * Coroutine already finished and waiting for reuse
     */
     CoroutineState_Finish,
}
CoroutineState;


typedef struct Coroutine Coroutine;
typedef void   (*CoroutineRun)(Coroutine* coroutine);


struct Coroutine
{
    /**
     * Record coroutine run step
	 * !! Define at top, friendly with asm
     */
    void*                 step;

    /**
     * Coroutine implement function
     */
    CoroutineRun          Run;

    /**
     * Coroutine current state
     */
    CoroutineState        state;

    /**
     * Coroutine wait value to execute
     */
    float                 waitValue;

    /**
     * Record wait progress
     */
    float                 curWaitValue;

    /**
     * Coroutine wait type
     */
    CoroutineWaitType     waitType;

    /**
     * Hold params for CoroutineRun to get
     * when coroutine finish clear but the param create memory control yourself
     */
    ArrayList(void*)      params[1];

    /**
     * Hold Coroutines wait for this Coroutine to finish
     */
    ArrayList(Coroutine*) waits [1];
};


struct _ACoroutine
{
    /**
     * Bind CoroutineRun with Coroutine and enter queue ready to run
     */
    Coroutine* (*StartCoroutine)(CoroutineRun Run);

    /**
     * Update on every frame
     */
    void       (*Update)        (float deltaSeconds);
};


extern struct _ACoroutine ACoroutine[1];


#define ACoroutine_AddParam(coroutine, value) \
    AArrayList_Add(coroutine->params, value)


/**
 * Get param value
 */
#define ACoroutine_GetParam(coroutine, index, type) \
    AArrayList_Get(coroutine->params, index, type)


/**
 * Get param valuePtr
 */
#define ACoroutine_GetPtrParam(coroutine, index, type) \
    AArrayList_GetPtr(coroutine->params, index, type)


/**
 * Construct goto label with line number
 */
#define ACoroutine_StepName(line) Step##line
#define ACoroutine_Step(line)     ACoroutine_StepName(line)


#define ACoroutine_Begin()                    \
    if (coroutine->step != NULL)              \
    {                                         \
        _asm {mov eax, dword ptr[coroutine]}	  \
		_asm {jmp dword ptr[eax]}			  \
    }                                         \
    coroutine->state = CoroutineState_Running 


#define ACoroutine_End() \
    coroutine->state = CoroutineState_Finish


/**
 * Called between ACoroutine_Begin and ACoroutine_End
 *
 * waitFrameCount: CoroutineRun wait frames and running again
 */
#define ACoroutine_YieldFrames(waitFrames)                  \
    coroutine->waitValue    = waitFrames;                   \
    coroutine->curWaitValue = 0.0f;                         \
    coroutine->waitType     = CoroutineWaitType_Frames;     \
	_asm {mov eax, [coroutine]}								\
	_asm {mov dword ptr[eax], offset ACoroutine_Step(__LINE__)}	\
    return;                                                 \
    ACoroutine_Step(__LINE__):


/**
 * Called between ACoroutine_Begin and ACoroutine_End
 *
 * waitSecond: CoroutineRun wait seconds and running again
 */
#define ACoroutine_YieldSeconds(waitSeconds)                \
    coroutine->waitValue    = waitSeconds;                  \
    coroutine->curWaitValue = 0.0f;                         \
    coroutine->waitType     = CoroutineWaitType_Seconds;    \
	_asm {mov eax, [coroutine]}								\
	_asm {mov dword ptr[eax], offset ACoroutine_Step(__LINE__)}	\
    return;                                                 \
    ACoroutine_Step(__LINE__):


/**
 * Called between ACoroutine_Begin and ACoroutine_End
 *
 * waitCoroutine: CoroutineRun wait other Coroutine finished and running again
 */
#define ACoroutine_YieldCoroutine(waitCoroutine)            \
    coroutine->waitValue    = 0.0f;                         \
    coroutine->curWaitValue = 0.0f;                         \
    coroutine->waitType     = CoroutineWaitType_Coroutines; \
    AArrayList_Add((waitCoroutine)->waits, coroutine);      \
	_asm {mov eax, [coroutine]}								\
	_asm {mov dword ptr[eax], offset ACoroutine_Step(__LINE__)}	\
    return;                                                 \
    ACoroutine_Step(__LINE__):


/**
 * Called between ACoroutine_Begin and ACoroutine_End
 * sotp coroutine running
 */
#define ACoroutine_YieldBreak()               \
    coroutine->state = CoroutineState_Finish; \
    return


#endif
