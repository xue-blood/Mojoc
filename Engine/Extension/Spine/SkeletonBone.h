/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-7-2
 * Author: scott.cgi
 */

#ifndef SKELETON_BONE_H
#define SKELETON_BONE_H


#include "Engine/Extension/Spine/SkeletonData.h"
#include "Engine/Graphics/Draw/Drawable.h"


typedef struct
{
    Drawable           drawable[1];
    SkeletonBoneData*  boneData;
}
SkeletonBone;


struct _ASkeletonBone
{
    SkeletonBone* (*Create)        (SkeletonBoneData* boneData);
    void          (*Init)          (SkeletonBoneData* boneData, SkeletonBone* outBone);

    /**
     * Set bone to setup pose
     */
    void          (*SetToSetupPose)(SkeletonBone* bone);
};


extern struct _ASkeletonBone ASkeletonBone[1];


#endif
