/*
 * Copyright (c) 2012-2018 scott.cgi All Rights Reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Since : 2013-08-29
 * Author: scott.cgi
 */

#include "Engine/Toolkit/Platform/Platform.h"


//----------------------------------------------------------------------------------------------------------------------
#ifdef IS_PLATFORM_WIN32
//----------------------------------------------------------------------------------------------------------------------


#include <stdio.h>
#include <direct.h>  
#include "Engine/Toolkit/Platform/File.h"
#include "Engine/Toolkit/Platform/Log.h"



static File* Open(char* relativeFilePath)
{
	//AAsset* asset = AAssetManager_open(nativeActivity->assetManager, relativeFilePath, AASSET_MODE_UNKNOWN);
	FILE* asset = fopen(relativeFilePath, "rb+");
	ALog_A(asset != NULL, "AFile open failed, relative file path = %s", relativeFilePath);

	return (File*)asset;
}


static int OpenFileDescriptor(char* relativeFilePath, long* outStart, long* outLength)
{
	//     AAsset* asset = AAssetManager_open(nativeActivity->assetManager, relativeFilePath, AASSET_MODE_UNKNOWN);
	// 
	//     // open asset as file descriptor
	//     int fd = AAsset_openFileDescriptor(asset, outStart, outLength);
	//     ALog_A(fd >= 0, "AFile OpenFileDescriptor failed, relative file path = %s", relativeFilePath);
	//     AAsset_close(asset);
	// 
	//     return fd;
	return Open(relativeFilePath);
}


static void Close(File* file)
{
	/*    AAsset_close((AAsset*) file);*/
	fclose(file);
}


static long GetLength(File* file)
{
	/*    return AAsset_getLength((AAsset*) file);*/
	long curPos = ftell(file);
	if (curPos == -1) return -1;

	fseek(file, 0, SEEK_END);
	long len = ftell(file);
	fseek(file, curPos, SEEK_SET);
	return len;
}


static int Read(File* file, void* buffer, size_t count)
{
	return fread(buffer, 1, count, file);
}


static int Seek(File* file, long offset, int whence)
{
	return fseek(file, offset, whence);
}

static char _absoluteDir[256] = { 0 };
static const char* GetAbsoluteDirPath()
{
	/*    return nativeActivity->internalDataPath;*/
	if (_absoluteDir[0] == 0)
	{
		getcwd(_absoluteDir, 256);
	}
	return _absoluteDir;
}


struct _AFile AFile[1] =
{
	Open,
	OpenFileDescriptor,
	Close,
	GetLength,
	Read,
	Seek,
	GetAbsoluteDirPath,
};


//----------------------------------------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------------------------------------
