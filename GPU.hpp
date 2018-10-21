#ifndef GPU_HPP
#define GPU_HPP
#include "particle.h"
#include "Input.hpp"

class GPU
{
    public:
        size_t global_item_size;
        size_t local_item_size = 250;
        char *read_kernel(char *name, size_t *size);
        GPU(size_t num_particle);
        void clLoop();
        void initKernel(unsigned int *glBuff, int square);
        ~GPU();
        

    private:
        cl_context context;
        static cl_command_queue command_queue;
        cl_kernel kernel, kernel2;
        cl_program program;
        static cl_mem particles_buff;
};

#endif