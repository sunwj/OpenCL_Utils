//
//  oclUtility.cpp
//  SelectPlatformandDevices
//
//  Created by sunwj on 14-4-8.
//  Copyright (c) 2014年 sunwj. All rights reserved.
//

#include "oclUtility.h"
#include <sys/stat.h>

#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/cl.h>
#endif

//Check Error
bool CheckError(cl_int err, char *msg)
{
	if(CL_SUCCESS != err)
	{
		switch(err)
		{
			case CL_DEVICE_NOT_FOUND:
				fprintf(stderr, "CL_DEVICE_NOT_FOUND\n");
			break;
			case CL_DEVICE_NOT_AVAILABLE:
				fprintf(stderr, "CL_DEVICE_NOT_AVAILABLE\n");
			break;
			case CL_COMPILER_NOT_AVAILABLE:
				fprintf(stderr, "CL_COMPLIER_NOT_AVAILABLE\n");
			break;
			case CL_MEM_OBJECT_ALLOCATION_FAILURE:
				fprintf(stderr, "CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
			break;
			case CL_OUT_OF_RESOURCES:
				fprintf(stderr, "CL_OUT_OF_RESOURCES\n");
			break;
			case CL_OUT_OF_HOST_MEMORY:
				fprintf(stderr, "CL_OUT_OF_HOST_MEMORY\n");
			break;
			case CL_PROFILING_INFO_NOT_AVAILABLE:
				fprintf(stderr, "CL_PROFILING_INFO_NOT_AVAILABLE\n");
			break;
			case CL_MEM_COPY_OVERLAP:
				fprintf(stderr, "CL_MEM_COPY_OVERLAP\n");
			break;
			case CL_IMAGE_FORMAT_MISMATCH:
				fprintf(stderr, "CL_IMAGE_FORMAT_MISMATCH\n");
			break;
			case CL_IMAGE_FORMAT_NOT_SUPPORTED:
				fprintf(stderr, "CL_IMAGE_FORMAT_NOT_SUPPORTED\n");
			break;
			case CL_BUILD_PROGRAM_FAILURE:
				fprintf(stderr, "CL_BUILD_PROGRAM_FAILURE\n");
			break;
			case CL_MAP_FAILURE:
				fprintf(stderr, "CL_MAP_FAILURE\n");
			break;
			case CL_INVALID_VALUE:
				fprintf(stderr, "CL_INVALID_VALUE\n");
			break;
			case CL_INVALID_DEVICE_TYPE:
				fprintf(stderr, "CL_INVALID_DEVICE_TYPE\n");
			break;
			case CL_INVALID_PLATFORM:
				fprintf(stderr, "CL_INVALID_PLATFORM\n");
			break;
			case CL_INVALID_DEVICE:
				fprintf(stderr, "CL_INVALID_DEVICE\n");
			break;
			case CL_INVALID_CONTEXT:
				fprintf(stderr, "CL_INVALID_CONTEXT\n");
			break;
			case CL_INVALID_QUEUE_PROPERTIES:
				fprintf(stderr, "CL_INVALID_QUEUE_PROPERTIES\n");
			break;
			case CL_INVALID_COMMAND_QUEUE:
				fprintf(stderr, "CL_INVALID_COMMAND_QUEUE\n");
			break;
			case CL_INVALID_HOST_PTR:
				fprintf(stderr, "CL_INVALID_HOST_PTR\n");
			break;
			case CL_INVALID_MEM_OBJECT:
				fprintf(stderr, "CL_INVALID_MEM_OBJECT:\n");
			break;
			case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
				fprintf(stderr, "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR\n");
			break;
			case CL_INVALID_IMAGE_SIZE:
				fprintf(stderr, "CL_INVALID_IMAGE_SIZE\n");
			break;
			case CL_INVALID_SAMPLER:
				fprintf(stderr, "CL_INVALID_SAMPLER\n");
			break;
			case CL_INVALID_BINARY:
				fprintf(stderr, "CL_INVALID_BINARY\n");
			break;
			case CL_INVALID_BUILD_OPTIONS:
				fprintf(stderr, "CL_INVALID_BUILD_OPTIONS\n");
			break;
			case CL_INVALID_PROGRAM:
				fprintf(stderr, "CL_INVALID_PROGRAM\n");
			break;
			case CL_INVALID_PROGRAM_EXECUTABLE:
				fprintf(stderr, "CL_INVALID_PROGRAM_EXECUTABLE\n");
			break;
			case CL_INVALID_KERNEL_NAME:
				fprintf(stderr, "CL_INVALID_KERNEL_NAME\n");
			break;
			case CL_INVALID_KERNEL_DEFINITION:
				fprintf(stderr, "CL_INVALID_KERNEL_DEFINITION\n");
			break;
			case CL_INVALID_KERNEL:
				fprintf(stderr, "CL_INVALID_KERNEL\n");
			break;
			case CL_INVALID_ARG_INDEX:
				fprintf(stderr, "CL_INVALID_ARG_INDEX\n");
			break;
			case CL_INVALID_ARG_VALUE:
				fprintf(stderr, "CL_INVALID_ARG_VALUE\n");
			break;
			case CL_INVALID_ARG_SIZE:
				fprintf(stderr, "CL_INVALID_ARG_SIZE\n");
			break;
			case CL_INVALID_KERNEL_ARGS:
				fprintf(stderr, "CL_INVALID_KERNEL_ARGS\n");
			break;
			case CL_INVALID_WORK_DIMENSION:
				fprintf(stderr, "CL_INVALID_WORK_DIMENSION\n");
			break;
			case CL_INVALID_WORK_GROUP_SIZE:
				fprintf(stderr, "CL_INVALID_WORK_GROUP_SIZE\n");
			break;
			case CL_INVALID_WORK_ITEM_SIZE:
				fprintf(stderr, "CL_INVALID_WORK_ITEM_SIZE\n");
			break;
			case CL_INVALID_GLOBAL_OFFSET:
				fprintf(stderr, "CL_INVALID_GLOBAL_OFFSET\n");
			break;
			case CL_INVALID_EVENT_WAIT_LIST:
				fprintf(stderr, "CL_INVALID_EVENT_WAIT_LIST\n");
			break;
			case CL_INVALID_EVENT:
				fprintf(stderr, "CL_INVALID_EVENT\n");
			break;
			case CL_INVALID_OPERATION:
				fprintf(stderr, "CL_INVALID_OPERATION\n");
			break;
			case CL_INVALID_GL_OBJECT:
				fprintf(stderr, "CL_INVALID_GL_OBJECT:");
			break;
			case CL_INVALID_BUFFER_SIZE:
				fprintf(stderr, "CL_INVALID_BUFFER_SIZE\n");
			break;
			case CL_INVALID_MIP_LEVEL:
				fprintf(stderr, "CL_INVALID_MIP_LEVEL\n");
			break;
			case CL_INVALID_GLOBAL_WORK_SIZE:
				fprintf(stderr, "CL_INVALID_GLOBAL_WORK_SIZE\n");
			
			default:
			break;
		}
		
		if(NULL != msg)
			fprintf(stderr, "%s\n", msg);
		
		return false;
	}
	
	return true;
}


//Select platform manually
cl_platform_id SelectPlatform(void)
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
	
	fclose(fp);

	return source;
}