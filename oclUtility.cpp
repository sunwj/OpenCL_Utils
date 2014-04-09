//
//  oclUtility.cpp
//  SelectPlatformandDevices
//
//  Created by sunwj on 14-4-8.
//  Copyright (c) 2014年 sunwj. All rights reserved.
//

#include "oclUtility.h"

#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#include <sys/stat.h>
#else
#include <CL\cl.h>
#include <sys\stat.h>
#endif


//Select platform manually
cl_platform_id SelectPlatform()
{
    cl_int err = 0;
    char msg[256] = {0};
    cl_uint num_platforms = 0;
    int choice = 0;
    
    err = clGetPlatformIDs(0, NULL, &num_platforms);
    CheckError(err, "Failed to get any OpenCL platform!");
    
    std::vector<cl_platform_id> platforms(num_platforms);
    err = clGetPlatformIDs(num_platforms, &platforms[0], &num_platforms);
    CheckError(err, "Failed to get any OpenCL platform!");
    
    printf("%i OpenCL platforms found!\n", num_platforms);
    for(int i = 0; i < num_platforms; ++i)
    {
        err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(msg), msg, NULL);
        CheckError(err, "Failed to get platform information!");
        
        printf("[%i] %s\n", i+1, msg);
    }
    
    if(num_platforms == 1)
    {
        err = clGetPlatformInfo(platforms[0], CL_PLATFORM_NAME, sizeof(msg), msg, NULL);
        CheckError(err, "Failed to get platform information!");
        printf("%s selected!\n", msg);
        
        return platforms[0];
    }
    
    printf("Please select a platform:");
    scanf("%i", &choice);
    
    while(choice<1 || choice>num_platforms)
    {
        fprintf(stderr, "Invalid choice!\n");
    }
    
    err = clGetPlatformInfo(platforms[choice-1], CL_PLATFORM_NAME, sizeof(msg), msg, NULL);
    CheckError(err, "Failed to get platform information!");
    printf("%s selected!\n", msg);
    
    return platforms[choice-1];
}

//Select device manually
cl_device_id SelectDevice(cl_platform_id platform)
{
    cl_int err = 0;
    cl_uint num_devices = 0;
    char msg[256] = {0};
    int choice = 0;
    
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
    CheckError(err, "Failed to get any GPU device!");
    
    std::vector<cl_device_id> devices(num_devices);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, num_devices, &devices[0], &num_devices);
    CheckError(err, "Failed to get any GPU device!");
    
    printf("%i GPU found!\n", num_devices);
    for(int i = 0; i < num_devices; ++i)
    {
        err = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(msg), msg, NULL);
        CheckError(err, "Failed to get device information!");
        printf("[%i] %s\n", i+1, msg);
    }
    
    if(num_devices == 1)
    {
        err = clGetDeviceInfo(devices[0], CL_DEVICE_NAME, sizeof(msg), msg, NULL);
        CheckError(err, "Failed to get device information!");
        printf("%s selected!\n", msg);
        
        return devices[0];
    }
    
    printf("Please select a device:");
    scanf("%i", &choice);
    
    while (choice<0 || choice>num_devices)
    {
        fprintf(stderr, "Invalid choice!\n");
    }
    
    err = clGetDeviceInfo(devices[choice-1], CL_DEVICE_NAME, sizeof(msg), msg, NULL);
    CheckError(err, "Failed to get device information!");
    printf("%s selected!\n", msg);
    
    return devices[choice-1];
}

//Load program source code
char* LoadProgramSourceCode(char *filename, size_t *source_size)
{
	struct stat filestate;
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to open kernel source code: %s\n", filename);
		exit(1);
	}

	stat(filename, &filestate);

	char *source = (char*)malloc(sizeof(char)*(filestate.st_size+1));
	memset(source, 0, sizeof(char)*(filestate.st_size+1));

	if(source_size!=NULL)
		*source_size = fread(source,filestate.st_size, 1, fp);
	else
		fread(source,filestate.st_size, 1, fp);

	return source;
}