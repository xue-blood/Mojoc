/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2016-6-24
 * Author: scott.cgi
 */

#ifndef TWEEN_TOOL_H
#define TWEEN_TOOL_H


#include <stdbool.h>
#include "Engine/Toolkit/Utils/Tween.h"


typedef struct
{
    TweenActionValueOnGet OnGet;
    TweenActionValueOnSet OnSet;
}
TweenActionValueGetSet;


struct ATweenActionValueGetSetImpl
{
    TweenActionValueGetSet moveX  [1];
    TweenActionValueGetSet moveY  [1];

    TweenActionValueGetSet scaleX [1];
    TweenActionValueGetSet scaleY [1];

    TweenActionValueGetSet rotateZ[1];
    TweenActionValueGetSet fadeTo [1];
};


/**
 * Application must implement tween action value get set method
 */
extern struct ATweenActionValueGetSetImpl ATweenActionValueGetSetImpl[1];


struct _ATweenTool
{
    /**
     * Add one TweenAction in context for chain setting
     * the TweenAction can add several TweenActionValue
     */
	struct _ATweenTool* (*AddAction)  ();

    /**
     * Add action with no actionValue just through duration time then callback
     */
	struct _ATweenTool* (*AddInterval)(float duration);

/*
------------------------------------------------------------------------------------------------------------------------
    Add one TweenAction with TweenActionValue
------------------------------------------------------------------------------------------------------------------------
*/

	struct _ATweenTool* (*AddMoveX)     (float moveX, float duration);
	struct _ATweenTool* (*AddMoveY)     (float moveY, float duration);

	struct _ATweenTool* (*AddMove2)     (float moveX, float moveY, float duration, bool          isRelative, TweenEaseType easeType);
	struct _ATweenTool* (*AddMoveSame2) (float move, float duration, bool  isRelative, TweenEaseType easeType);

	struct _ATweenTool* (*AddScaleX)    (float scaleX, float duration);
	struct _ATweenTool* (*AddScaleY)    (float scaleY, float duration);

	struct _ATweenTool* (*AddScale2)    (float scaleX, float scaleY, float duration, bool           isRelative, TweenEaseType easeType);
	struct _ATweenTool* (*AddScaleSame2)(float scale, float duration, bool  isRelative, TweenEaseType  easeType);

	struct _ATweenTool* (*AddRotateZ)   (float rotateZ, float duration);
	struct _ATweenTool* (*AddFadeTo)    (float fadeTo, float duration);


/*
------------------------------------------------------------------------------------------------------------------------
    Set TweenAction property for current context
------------------------------------------------------------------------------------------------------------------------
*/

	struct _ATweenTool* (*SetDuration)           (float                   duration);
	struct _ATweenTool* (*SetQueue)              (bool                    isQueue);
	struct _ATweenTool* (*SetOnComplete)         (TweenActionOnComplete   OnComplete);
	struct _ATweenTool* (*SetTarget)             (void*                   target);

	struct _ATweenTool* (*SetUserData0Int)       (int                     userData);
	struct _ATweenTool* (*SetUserData0Float)     (float                   userData);
	struct _ATweenTool* (*SetUserData0Ptr)       (void*                   userData);
	struct _ATweenTool* (*SetUserData0String)    (char*                   userData);

	struct _ATweenTool* (*SetUserData1Int)       (int                     userData);
	struct _ATweenTool* (*SetUserData1Float)     (float                   userData);
	struct _ATweenTool* (*SetUserData1Ptr)       (void*                   userData);
	struct _ATweenTool* (*SetUserData1String)    (char*                   userData);

	struct _ATweenTool* (*SetUserData2Int)       (int                     userData);
	struct _ATweenTool* (*SetUserData2Float)     (float                   userData);
	struct _ATweenTool* (*SetUserData2Ptr)       (void*                   userData);
	struct _ATweenTool* (*SetUserData2String)    (char*                   userData);

	struct _ATweenTool* (*SetUserData3Int)       (int                     userData);
	struct _ATweenTool* (*SetUserData3Float)     (float                   userData);
	struct _ATweenTool* (*SetUserData3Ptr)       (void*                   userData);
	struct _ATweenTool* (*SetUserData3String)    (char*                   userData);

    /**
     * Get TweenAction in current context
     */
	struct _ATweenTool* (*GetAction)             (TweenAction**           outActionPtr);


/*
------------------------------------------------------------------------------------------------------------------------
    Set new TweenActionValue into context TweenAction
------------------------------------------------------------------------------------------------------------------------
*/


	struct _ATweenTool* (*SetMoveX)     (float moveX);
	struct _ATweenTool* (*SetMoveY)     (float moveY);

	struct _ATweenTool* (*SetMove2)     (float moveX, float moveY, bool          isRelative, TweenEaseType easeType);
	struct _ATweenTool* (*SetMoveSame2) (float move, bool  isRelative, TweenEaseType easeType);

	struct _ATweenTool* (*SetScaleX)    (float scaleX);
	struct _ATweenTool* (*SetScaleY)    (float scaleY);

	struct _ATweenTool* (*SetScale2)    (float scaleX, float scaleY, bool          isRelative, TweenEaseType easeType);
	struct _ATweenTool* (*SetScaleSame2)(float scale, bool  isRelative, TweenEaseType easeType);

	struct _ATweenTool* (*SetRotateZ)   (float rotateZ);
	struct _ATweenTool* (*SetFadeTo)    (float fadeTo);


/*
------------------------------------------------------------------------------------------------------------------------
    Set TweenActionValue property for current context
------------------------------------------------------------------------------------------------------------------------
*/


    /**
     * Set TweenActiveValue's isRelative
     */
	struct _ATweenTool* (*SetRelative)(bool          isRelative);

    /**
     * Set TweenActiveValue's easeType
     */
	struct _ATweenTool* (*SetEaseType)(TweenEaseType easeType);

//----------------------------------------------------------------------------------------------------------------------

    /**
     * Run actions all in current context, set action target if has actionValue
     * use target be tweenId
     */
    void               (*RunActions) (void* target);

    /**
     * Run actions all in current context, action must set target if has actionValue
     * all different targets will in same queue
     * return tweenId
     */
    void*              (*RunTargets) ();
};


extern struct _ATweenTool ATweenTool[1];


#endif
