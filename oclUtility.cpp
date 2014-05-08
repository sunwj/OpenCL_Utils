/*

* Copyright (c) 2014, Nantong University
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Carnegie Mellon University, nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY NANTONG UNIVERSITY ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  Code author: sun wanjie, 2014-2017
  Research: sun wanjie
  Version: 1.0

*/

#include "oclUtility.h"
#include <sys/stat.h>
#include <string.h>
#include <vector>

#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/cl.h>
#endif

//Check Error
bool CheckError(cl_int err, char *msg, bool abort)
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

		if (abort)
		{
			printf("Aborting...\n");
			exit(1);
		}
		
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
        printf("Please select a valid platform number:");
        scanf("%i", &choice);
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

	cl_device_id default_device = NULL;
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &default_device, NULL);
    
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
    if(!CheckError(err, "Failed to get any GPU device!", false))
	{
		printf("Using default device!\n");
		return default_device;
	}
    
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
        printf("Please select a valid device number:");
        scanf("%i", &choice);
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

	fread(source,filestate.st_size, 1, fp);
	
	if(NULL != source_size)
		*source_size = strlen(source);
	
	fclose(fp);

	return source;
}

//Query device information
void QueryDeviceInfo(cl_device_id device)
{
	char buffer[2048] = {0};
	size_t code = 0;
	size_t triple[3] = {0};
	cl_int err = 0;

	err = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(buffer), buffer, NULL);
	CheckError(err);
	printf("----------------------------------------------------\n");
	printf("%s\n", buffer);
	printf("----------------------------------------------------\n");

	err = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(buffer), buffer, NULL);
	CheckError(err);
	printf("Device vender:               %s\n", buffer);

	err = clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(buffer), buffer, NULL);
	CheckError(err);
	printf("Device driver version:       %s\n", buffer);

	err = clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(buffer), buffer, NULL);
	CheckError(err);
	printf("Device version:              %s\n", buffer);

	err = clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, sizeof(buffer), buffer, NULL);
	CheckError(err);
	printf("OpenCL C version:            %s\n", buffer);

	err = clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(size_t), &code, NULL);
	CheckError(err);
	switch (code)
	{
	case CL_DEVICE_TYPE_CPU:
		printf("Device type:                 CPU\n");
	break;
	case CL_DEVICE_TYPE_GPU:
		printf("Device type:                 GPU\n");
	break;
	case CL_DEVICE_TYPE_ACCELERATOR:
		printf("Device type:                 Accelerator\n");
	default:
		break;
	}

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(size_t), &code, NULL);
	CheckError(err);
    printf("Max compute unit:            %i\n", code);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Max work item dimensions:    %i\n", code);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(triple), triple, NULL);
	CheckError(err);
	printf("Max work item sizes:         %i / %i / %i\n", triple[0], triple[1], triple[2]);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Max work group size:         %i\n", code);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Max clock frequency:         %i MHz\n", code);

	err = clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Address bits:                %i\n", code);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Max memery allocation size:  %i MB\n", code / 1024 / 1024);

	err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Global memery size:          %i MB\n", code / 1024 / 1024);

	err = clGetDeviceInfo(device, CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(size_t), &code, NULL);
	CheckError(err);
	if (!code)
		printf("Error correction support:    %s\n", "NO");
	else
		printf("Error correction support:    %s\n", "YES");

	err = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Local memery sizes:          %i KB\n", code / 1024);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Max const buffer size:       %i KB\n", code / 1024);

	err = clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Image support:               %i\n", code);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Max read image args:         %i\n", code);

	err = clGetDeviceInfo(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(size_t), &code, NULL);
	CheckError(err);
	printf("Max write image args:        %i\n", code);
}

//Print build log
void PrintBuildLog(cl_program *program, cl_device_id device)
{
    size_t log_size = 0;
    cl_int err = 0;
    err = clGetProgramBuildInfo(*program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    CheckError(err);
    
    char *log = (char*)malloc(log_size + 1);
    err = clGetProgramBuildInfo(*program, device, CL_PROGRAM_BUILD_LOG, log_size + 1, log, NULL);
    CheckError(err);
    
    fprintf(stderr, "Build log:\n%s\n", log);
    
    free(log);
}

//Found kernel function index by name
int GetKernelFunctionIndex(cl_kernel *kernels, int num, char *name)
{
    cl_int err = 0;
    char func_name[512] = {0};

    for(int i = 0; i < num; ++i)
    {
        err = clGetKernelInfo(kernels[i], CL_KERNEL_FUNCTION_NAME, sizeof(func_name), func_name, NULL);
        CheckError(err);

        if(strcmp(name, func_name) == 0)
            return i;
    }

    return -1;
}
