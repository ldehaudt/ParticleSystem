#include "GPU.hpp"

cl_mem GPU::particles_buff;
cl_command_queue GPU::command_queue;

char    *GPU::read_kernel(char *name, size_t *size)
{
    FILE *fp;
    char *buffer;

    fp = fopen(name, "r");
    fseek(fp, 0L, SEEK_END);
    *size = (size_t)ftell(fp);
    rewind(fp);
    buffer = (char*)calloc(1, *size + 1);
    fread(buffer, *size, 1, fp);
    fclose(fp);
    return (buffer);
}

GPU::GPU(size_t numParticles){
    global_item_size = numParticles;
    CGLContextObj    gl_ctx        = CGLGetCurrentContext();
    CGLShareGroupObj gl_sharegroup = CGLGetShareGroup(gl_ctx);
    cl_context_properties properties[] = {
        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties) gl_sharegroup, 0
    };
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_int ret;
    cl_uint db;
    clGetPlatformIDs(1, &platform_id, &db);
    clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, 
            &device_id, &db);
    context = clCreateContext( properties, 1, &device_id, NULL, NULL, &ret);    
}

void printVersion(cl_device_id device){
    char *str = (char *)malloc(20);
    clGetDeviceInfo(device, CL_DEVICE_VERSION, 20, str, NULL);
    printf("%s\n", str);

}

void    GPU::initKernel(unsigned int *glBuff, int square) {    
    size_t kernel_size = 0;
    char *kernel_str = read_kernel((char *)"kernel.cl", &kernel_size); 
    cl_platform_id platform_id = NULL;
    cl_int ret;
    cl_uint db;
    cl_device_id device_id = NULL;   
    ret = clGetPlatformIDs(1, &platform_id, &db);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, 
            &device_id, &db);
    printVersion(device_id);
    particles_buff = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, *glBuff, &ret);

    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    glFlush();
    program = clCreateProgramWithSource(context, 1, 
            (const char **)&kernel_str, (const size_t *)&kernel_size, &ret);
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    cl_kernel init = clCreateKernel(program, "initParticles", &ret);
    ret = clEnqueueAcquireGLObjects(command_queue, global_item_size, &particles_buff, 0, NULL, NULL);

    ret = clSetKernelArg(init, 0, sizeof(cl_mem), (void *)&particles_buff);
    ret = clSetKernelArg(init, 1, sizeof(int), (void *)&global_item_size);
    ret = clSetKernelArg(init, 2, sizeof(int), (void *)&square);
    
    ret = clEnqueueNDRangeKernel(command_queue, init, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    ret = clReleaseKernel(init);

    kernel = clCreateKernel(program, "calcVelo", &ret);
    kernel2 = clCreateKernel(program, "addVelo", &ret);
 
    ret = clEnqueueReleaseGLObjects(command_queue, 1, &particles_buff, 0, NULL, NULL);

    free(kernel_str);
    ret = clFlush(command_queue);
} 

void GPU::clLoop(){
    cl_int ret;

    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&particles_buff);
    ret = clSetKernelArg(kernel, 1, sizeof(int), (void *)&global_item_size);
    ret = clSetKernelArg(kernel, 2, sizeof(float), (void *)&Input::mouseX);
    ret = clSetKernelArg(kernel, 3, sizeof(float), (void *)&Input::mouseY);
    ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void *)&particles_buff);
    ret = clSetKernelArg(kernel2, 1, sizeof(int), (void *)&global_item_size);
    ret = clSetKernelArg(kernel2, 2, sizeof(float), (void *)&Input::scroll);
    ret = clSetKernelArg(kernel2, 3, sizeof(float), (void *)&Input::offsetX);
    ret = clSetKernelArg(kernel2, 4, sizeof(float), (void *)&Input::offsetY);

    Input::offsetX = 0;
    Input::offsetY = 0;
    if (!Input::noGrav){
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    }
    ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    clFlush(command_queue);
    ret = clEnqueueReleaseGLObjects(command_queue, 1, &particles_buff, 0, NULL, NULL);
    Input::scroll = 0;
}

GPU::~GPU(){
    cl_int ret;

    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseKernel(kernel2);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(particles_buff);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
}