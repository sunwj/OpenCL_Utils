//
//  oclUtility.h
//  SelectPlatformandDevices
//
//  Created by sunwj on 14-4-8.
//  Copyright (c) 2014年 sunwj. All rights reserved.
//

#ifndef SelectPlatformandDevices_oclUtility_h
#define SelectPlatformandDevices_oclUtility_h

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/cl.h>
#endif

//CheckError
bool CheckError(cl_int err, char *msg = NULL);

//Select platform manually
cl_platform_id SelectPlatform(void);

//Select devices manually
cl_device_id SelectDevice(cl_platform_id);

//Load program source code
char* LoadProgramSourceCode(char *filename, size_t *source_size = NULL);

#endif
