#include <vector>
#include <iostream>
#include <ai>

#include <mpi.h>

#include "life.hpp"

int main(const int argc, const char *argv[]){
    std::size_t numberOfSteps = 100;
    std::size_t numberOfRuns = 1;
    std::size_t meshSize = 16;
    
    for(int i = 1; i < argc; ++i){
        if("-h" == std::string(argv[i]) || "--help" == std::string(argv[i])){
            std::cout << "usage: parallelLife [options]"
                << std::endl
                << "    -h  --help            print this usage and exit"
                << std::endl << std::endl
                << "    --runs=<value>        number of runs"
                << "[uint]"
                << std::endl
                << "    --steps=<value>       number of steps to calculate"
                << "[uint]"
                << std::endl
                << "    --mesh-size=<value>   mesh size in cells"
                << "[uint]"
                << std::endl;
            
            return 0;
        }
        
        if(
            ai::assignParameter(argv[i], "--runs=", numberOfRuns)
            || ai::assignParameter(argv[i], "--steps=", numberOfSteps)
            || ai::assignParameter(argv[i], "--mesh-size=", meshSize)
        ){
            continue;
        }
    }
    
    MPI_Init(NULL, NULL);
    
    for(std::size_t i = 0; i < numberOfRuns; ++i){
        parallelLife(numberOfSteps, meshSize);
    }
    
    MPI_Finalize();

    return 0;
}