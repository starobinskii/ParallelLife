#include <vector>
#include <iostream>

#include <mpi.h>

#include "life.hpp"
#include "tools.hpp"
#include "calcmodule.hpp"


void life(const std::size_t finalStep, const size_t dim){
    int *field = new int[dim * dim];
    int *field1 = new int[dim * dim];
    
    for(std::size_t i = 0; i < dim; ++i){
        for(std::size_t j = 0; j < dim; ++j){
            field[i * dim + j] = 0;
            field1[i * dim + j] = 0;
        }
    }
    
    MPI_Init(NULL, NULL);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int *fieldSend = new int[dim * dim / size];
    
    if(0 == rank){
        IniConfig(field , dim);
    }
	
    // std::cout << "Initial field :"<<std::endl;
    //
    // Showfield(field, dim);
    std::size_t step = 1;
    std::size_t part = 1;
    std::size_t index = 0;
     
    while(finalStep >= step){
        MPI_Bcast(field, dim * dim, MPI_INT, 0, MPI_COMM_WORLD);
        
        GetLife(field, field1, dim, rank * dim / size, (rank + 1) * dim / size);
        
        part = dim / size;
        
        for(std::size_t i = 0; i < dim * dim / size; ++i){
            fieldSend[i] = 0;
        }
        
        index = 0;
        for(std::size_t i = rank * dim / size; i < (rank + 1) * dim / size; ++i){
            for(std::size_t j = 0; j < dim; ++j){
                fieldSend[index] = field1[i * dim + j];
                ++index;
            }
        }
        
        // for(std::size_t i = 0; i < dim * dim / size; ++i){
        //     std::cout << "r = " << rank << ", v = " << fieldSend[i] << std::endl;
        // }
        
        if(dim * dim / size != index){
            std::cout << "warning" << std::endl;
        }
        
        MPI_Gather(fieldSend, dim * dim / size, MPI_INT, field1, dim * dim / size, MPI_INT, 0, MPI_COMM_WORLD);
        
        if(0 == rank){
            for(std::size_t i = 0; i < dim; ++i){
                for(std::size_t j = 0; j < dim; ++j){
                    field[i * dim + j] = field1[i * dim + j];
                    
                    // std::cout << field1[i * dim + j] << std::endl;
                }
            }
        }
        
        ++step;
        
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    if(0 == rank){
        ShowField(field, dim);
    }

        
    // if (rank == ping_pong_count % 2) {
    //     MPI_Send(&field1, 1, MPI_BOOL, partner_rank, 0,
    //              MPI_COMM_WORLD);
    //     printf("%d sent and incremented ping_pong_count "
    //            "%d to %d\n", rank, ping_pong_count,
    //            partner_rank);
    // } else {
    //     MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0,
    //              MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     printf("%d received ping_pong_count %d from %d\n",
    //            rank, ping_pong_count, partner_rank);
    // }
    
    // while (st < step)
    // {
    //
    //
    //         GetLife(field , field1, dim);
    //
    //         std::cout<<"\nfield step " <<st+1<<" : "<<std::endl;
    //
    //         Showfield(field1, dim);
    //
    //         // if()
    //         for(size_t i = 0; i<dim;++i)
    //             for(size_t j = 0; j <dim;++j)
    //                 field[i][j] = field1[i][j];
    //
    //     st++;
    //
    //         auto start = std::chrono::system_clock::now();
    //         bool sleep = true;
    //         while(sleep)
    //         {
    //             auto now = std::chrono::system_clock::now();
    //             auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
    //             if ( elapsed.count() > 500000 )
    //                 sleep = false;
    //         }
    // }
    
    MPI_Finalize();
    
    delete [] field;
    delete [] field1;
}