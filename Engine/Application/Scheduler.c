/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2014-1-16
 * Author: scott.cgi
 */

#include <stdlib.h>
#include "Engine/Toolkit/Head/Define.h"
#include "Engine/Application/Scheduler.h"
#include "Engine/Toolkit/Platform/Log.h"
#include "Engine/Toolkit/Utils/ArrayList.h"


static ArrayList(Scheduler*) schedulerRun [1] = AArrayList_Init(Scheduler*, 30);
static ArrayList(Scheduler*) schedulerList[1] = AArrayList_Init(Scheduler*, 30);


static inline Scheduler* GetScheduler(SchedulerUpdate Update, float intervalTime)
{
    ALog_A(Update != NULL, "ASchedule GetScheduler Update must not NULL");

    Scheduler* scheduler = AArrayList_Pop(schedulerList, Scheduler*);

    if (scheduler == NULL)
    {
        scheduler = (Scheduler*) malloc(sizeof(Scheduler));
    }

    AUserData_Init(scheduler->userData);
    scheduler->currentTime  = 0.0f;
    scheduler->intervalTime = intervalTime;
    scheduler->Update       = Update;

    AArrayList_Add(schedulerRun, scheduler);

    return scheduler;
}


static Scheduler* Schedule(SchedulerUpdate Update, float intervalTime)
{
    Scheduler* scheduler = GetScheduler(Update, intervalTime);
    scheduler->isCancel  = false;
    return scheduler;
}


static Scheduler* ScheduleOnce(SchedulerUpdate Update, float intervalTime)
{
    Scheduler* scheduler = GetScheduler(Update, intervalTime);
    scheduler->isCancel  = true;
    return scheduler;
}


static void Update(float deltaSeconds)
{
    for (int i = schedulerRun->size - 1; i > -1; i--)
    {
        Scheduler* scheduler = AArrayList_Get(schedulerRun, i, Scheduler*);

        if (scheduler->currentTime < scheduler->intervalTime)
        {
            scheduler->currentTime += deltaSeconds;
        }
        else
        {
            scheduler->Update(scheduler, deltaSeconds);

            if (scheduler->isCancel)
            {
                AArrayList->RemoveByLast(schedulerRun, i);
                AArrayList_Add(schedulerList, scheduler);
            }
            else
            {
                scheduler->currentTime = 0.0f;
            }
        }
    }
}


struct _AScheduler AScheduler[1] =
{
    Schedule,
    ScheduleOnce,
    Update,
};
