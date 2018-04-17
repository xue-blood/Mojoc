/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2016-6-24
 * Author: scott.cgi
 */

#include <string.h>

#include "Engine/Toolkit/Head/UserData.h"
#include "Engine/Toolkit/Utils/TweenTool.h"
#include "Engine/Toolkit/Platform/Log.h"


enum
{
    TweenAction_Length = 30,
};


static Array(TweenAction*) actionArr[1] =
{
    (TweenAction*[TweenAction_Length]) {0},
    0
};


static TweenAction*      action      = NULL;
static TweenActionValue* actionValue = NULL;


#define CheckAction(tag) \
    ALog_A(action      != NULL, "ATweenTool " tag " TweenAction not created");


#define CheckActionValue(tag) \
    ALog_A(actionValue != NULL, "ATweenTool " tag " TweenActionValue can not NULL");


static struct _ATweenTool* AddAction()
{
    ALog_A
    (
        actionArr->length <= TweenAction_Length,
        "ATweenTool can not cache TweenActions = %d more than %d",
        actionArr->length,
        TweenAction_Length
    );

    action      = ATween->GetAction();
    actionValue = NULL;

    AArray_Set
    (
        actionArr,
        actionArr->length++,
        action,
        TweenAction*
    );

    return ATweenTool;
}


static inline struct _ATweenTool* SetValue(TweenActionValueGetSet* valueGetSet, float value)
{
    CheckAction("SetValue");

    actionValue        = ATween->AddTweenActionValue(action);
    actionValue->OnGet = valueGetSet->OnGet;
    actionValue->OnSet = valueGetSet->OnSet;
    actionValue->value = value;

    return ATweenTool;
}


static struct _ATweenTool* SetDuration(float duration)
{
    CheckAction("SetDuration");
    action->duration = duration;

    return ATweenTool;
}


static struct _ATweenTool* SetRelative(bool isRelative)
{
    CheckAction     ("SetRelative");
    CheckActionValue("SetRelative");
    actionValue->isRelative = isRelative;

    return ATweenTool;
}


static struct _ATweenTool* SetEaseType(TweenEaseType easeType)
{
    CheckAction     ("SetEaseType");
    CheckActionValue("SetEaseType");
    actionValue->easeType = easeType;

    return ATweenTool;
}


static struct _ATweenTool* AddInterval(float duration)
{
    AddAction();
    SetDuration(duration);

    return ATweenTool;
}


//----------------------------------------------------------------------------------------------------------------------


static struct _ATweenTool* AddMoveX(float moveX, float duration)
{
    AddAction();
    SetValue(ATweenActionValueGetSetImpl->moveX, moveX);
    SetDuration(duration);

    return ATweenTool;
}


static struct _ATweenTool* AddMoveY(float moveY, float duration)
{
    AddAction();
    SetValue(ATweenActionValueGetSetImpl->moveY, moveY);
    SetDuration(duration);

    return ATweenTool;
}


static struct _ATweenTool* AddMove2(float moveX, float moveY, float duration, bool isRelative, TweenEaseType easeType)
{
    AddAction  ();

    SetValue   (ATweenActionValueGetSetImpl->moveX, moveX);
    SetRelative(isRelative);
    SetEaseType(easeType);

    SetValue   (ATweenActionValueGetSetImpl->moveY, moveY);
    SetRelative(isRelative);
    SetEaseType(easeType);

    SetDuration(duration);

    return ATweenTool;
}


static struct _ATweenTool* AddMoveSame2(float move, float duration, bool  isRelative, TweenEaseType easeType)
{
    return AddMove2(move, move, duration, isRelative, easeType);
}


static struct _ATweenTool* AddScaleX(float scaleX, float duration)
{
    AddAction();

    SetValue(ATweenActionValueGetSetImpl->scaleX, scaleX);
    SetDuration(duration);

    return ATweenTool;
}


static struct _ATweenTool* AddScaleY(float scaleY, float duration)
{
    AddAction();

    SetValue(ATweenActionValueGetSetImpl->scaleY, scaleY);
    SetDuration(duration);

    return ATweenTool;
}


static struct _ATweenTool* AddScale2(float scaleX, float scaleY, float duration, bool isRelative, TweenEaseType easeType)
{
    AddAction  ();

    SetValue   (ATweenActionValueGetSetImpl->scaleX, scaleX);
    SetRelative(isRelative);
    SetEaseType(easeType);

    SetValue   (ATweenActionValueGetSetImpl->scaleY, scaleY);
    SetRelative(isRelative);
    SetEaseType(easeType);

    SetDuration(duration);

    return ATweenTool;
}


static struct _ATweenTool* AddScaleSame2(float scale, float duration, bool  isRelative, TweenEaseType  easeType)
{
    return AddScale2(scale, scale, duration, isRelative, easeType);
}


static struct _ATweenTool* AddRotateZ(float rotateZ, float duration)
{
    AddAction();

    SetValue(ATweenActionValueGetSetImpl->rotateZ, rotateZ);
    SetDuration(duration);

    return ATweenTool;
}


static struct _ATweenTool* AddFadeTo(float fadeTo, float duration)
{
    AddAction();

    SetValue(ATweenActionValueGetSetImpl->fadeTo, fadeTo);
    SetDuration(duration);

    return ATweenTool;
}


//----------------------------------------------------------------------------------------------------------------------


static struct _ATweenTool* SetUserData0Int(int userData)
{
    CheckAction("SetUserData0Int");
    action->userData->slot0->intValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData0Float(float userData)
{
    CheckAction("SetUserData0Float");
    action->userData->slot0->floatValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData0Ptr(void* userData)
{
    CheckAction("SetUserData0Ptr");
    action->userData->slot0->ptrValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData0String(char* userData)
{
    CheckAction("SetUserData0String");
    action->userData->slot0->stringValue= userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData1Int(int userData)
{
    CheckAction("SetUserData1Int");
    action->userData->slot1->intValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData1Float(float userData)
{
    CheckAction("SetUserData1Float");
    action->userData->slot1->floatValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData1Ptr(void* userData)
{
    CheckAction("SetUserData1Ptr");
    action->userData->slot1->ptrValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData1String(char* userData)
{
    CheckAction("SetUserData1String");
    action->userData->slot1->stringValue= userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData2Int(int userData)
{
    CheckAction("SetUserData2Int");
    action->userData->slot2->intValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData2Float(float userData)
{
    CheckAction("SetUserData2Float");
    action->userData->slot2->floatValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData2Ptr(void* userData)
{
    CheckAction("SetUserData2Ptr");
    action->userData->slot2->ptrValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData2String(char* userData)
{
    CheckAction("SetUserData2String");
    action->userData->slot2->stringValue= userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData3Int(int userData)
{
    CheckAction("SetUserData3Int");
    action->userData->slot3->intValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData3Float(float userData)
{
    CheckAction("SetUserData3Float");
    action->userData->slot3->floatValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData3Ptr(void* userData)
{
    CheckAction("SetUserData3Ptr");
    action->userData->slot3->ptrValue = userData;
    return ATweenTool;
}


static struct _ATweenTool* SetUserData3String(char* userData)
{
    CheckAction("SetUserData3String");
    action->userData->slot3->stringValue= userData;
    return ATweenTool;
}


static struct _ATweenTool* SetQueue(bool isQueue)
{
    CheckAction("SetQueue");
    action->isQueue = isQueue;

    return ATweenTool;
}


static struct _ATweenTool* SetOnComplete(TweenActionOnComplete OnComplete)
{
    CheckAction("SetOnComplete");
    action->OnComplete = OnComplete;

    return ATweenTool;
}


static struct _ATweenTool* SetTarget(void* target)
{
    CheckAction("SetTarget");
    action->target = target;

    return ATweenTool;
}


static struct _ATweenTool* GetAction(TweenAction** outActionPtr)
{
    CheckAction("GetAction");
    *outActionPtr = action;

    return ATweenTool;
}


//----------------------------------------------------------------------------------------------------------------------


static struct _ATweenTool* SetMoveX(float moveX)
{
    return SetValue(ATweenActionValueGetSetImpl->moveX, moveX);
}


static struct _ATweenTool* SetMoveY(float moveY)
{
    return SetValue(ATweenActionValueGetSetImpl->moveY, moveY);
}


struct _ATweenTool* SetMove2(float moveX, float moveY, bool isRelative, TweenEaseType easeType)
{
    SetValue   (ATweenActionValueGetSetImpl->moveX, moveX);
    SetRelative(isRelative);
    SetEaseType(easeType);

    SetValue   (ATweenActionValueGetSetImpl->moveY, moveY);
    SetRelative(isRelative);
    SetEaseType(easeType);

    return ATweenTool;
}


struct _ATweenTool* SetMoveSame2(float move, bool isRelative, TweenEaseType easeType)
{
    return SetMove2(move, move, isRelative, easeType);
}


static struct _ATweenTool* SetScaleX(float scaleX)
{
    return SetValue(ATweenActionValueGetSetImpl->scaleX, scaleX);
}


static struct _ATweenTool* SetScaleY(float scaleY)
{
    return SetValue(ATweenActionValueGetSetImpl->scaleY, scaleY);
}


struct _ATweenTool* SetScale2(float scaleX, float scaleY, bool isRelative, TweenEaseType easeType)
{
    SetValue   (ATweenActionValueGetSetImpl->scaleX, scaleX);
    SetRelative(isRelative);
    SetEaseType(easeType);

    SetValue   (ATweenActionValueGetSetImpl->scaleY, scaleY);
    SetRelative(isRelative);
    SetEaseType(easeType);

    return ATweenTool;
}


struct _ATweenTool* SetScaleSame2(float scale, bool isRelative, TweenEaseType easeType)
{
    return SetScale2(scale, scale, isRelative, easeType);
}


static struct _ATweenTool* SetRotateZ(float rotateZ)
{
    return SetValue(ATweenActionValueGetSetImpl->rotateZ, rotateZ);
}


static struct _ATweenTool* SetFadeTo(float fadeTo)
{
    return SetValue(ATweenActionValueGetSetImpl->fadeTo, fadeTo);
}


//----------------------------------------------------------------------------------------------------------------------


static void RunActions(void* target)
{
    ALog_A(target != NULL, "ATweenTool RunActions, target can not NULL");

    for (int i = 0; i < actionArr->length; i++)
    {
        TweenAction* action = AArray_Get(actionArr, i, TweenAction*);

        if (action->actionValueList->size > 0)
        {
            action->target = target;
        }
    }

    ATween->RunActions(actionArr, target);

    actionArr->length = 0;
    action            = NULL;
    actionValue       = NULL;
}


static void* RunTargets()
{
    for (int i = 0; i < actionArr->length; i++)
    {
        TweenAction* action = AArray_Get(actionArr, i, TweenAction*);

        if (action->actionValueList->size > 0)
        {
            ALog_A
            (
                 action->target != NULL,
                 "ATweenTool RunTargets, the {%d} action has actionValue, so must set target",
                 i
            );
        }
    }


    void* tweenId = ATween->RunActions(actionArr, NULL);

    actionArr->length = 0;
    action            = NULL;
    actionValue       = NULL;

    return tweenId;
}


struct _ATweenTool ATweenTool[1] =
{
    AddAction,
    AddInterval,

    AddMoveX,
    AddMoveY,
    AddMove2,
    AddMoveSame2,

    AddScaleX,
    AddScaleY,
    AddScale2,
    AddScaleSame2,

    AddRotateZ,
    AddFadeTo,

    SetDuration,
    SetQueue,
    SetOnComplete,
    SetTarget,
    SetUserData0Int,
    SetUserData0Float,
    SetUserData0Ptr,
    SetUserData0String,
    SetUserData1Int,
    SetUserData1Float,
    SetUserData1Ptr,
    SetUserData1String,
    SetUserData2Int,
    SetUserData2Float,
    SetUserData2Ptr,
    SetUserData2String,
    SetUserData3Int,
    SetUserData3Float,
    SetUserData3Ptr,
    SetUserData3String,
    GetAction,

    SetMoveX,
    SetMoveY,
    SetMove2,
    SetMoveSame2,
    SetScaleX,
    SetScaleY,
    SetScale2,
    SetScaleSame2,
    SetRotateZ,
    SetFadeTo,

    SetRelative,
    SetEaseType,

    RunActions,
    RunTargets,
};


#undef CheckAction
#undef CheckActionValue