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

#ifndef oclUtility_h
#define oclUtility_h

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/cl.h>
#endif

//CheckError
bool CheckError(cl_int err, char *msg = NULL, bool abort = true);

//Select platform manually
cl_platform_id SelectPlatform(void);

//Select devices manually
cl_device_id SelectDevice(cl_platform_id);

//Select devices from all devices availiable
cl_device_id SelectDevicesAvailiable(cl_platform_id);

//Query device information
void QueryDeviceInfo(cl_device_id device);

//Load program source code
char* LoadProgramSourceCode(char *filename, size_t *source_size = NULL);

//Print build log
void PrintBuildLog(cl_program &, cl_device_id);

//Found kernel function index by name
int GetKernelFunctionIndex(cl_kernel *, int num, char *);

//Build program
cl_program BuildProgram(cl_context context, cl_device_id, char*);

//Create kernels in program
std::vector<cl_kernel> CreateKernelsInProgram(cl_program &);

//Release kernel
void ReleaseKernel(cl_kernel &kernel);

//Release program
void ReleaseProgram(cl_program &program);

//Release command queue
void ReleaseCommandQueue(cl_command_queue &cmd);

//Release context
void ReleaseContext(cl_context &ctx);

//Release device
//void ReleaseDevice(cl_device_id &device);

//Release memory object
void ReleaseMemObject(cl_mem &memobj);

//Release event
void ReleaseEvent(cl_event &event);

#endif
