#include <iostream>

void IniConfig(int *Field , size_t dim)
{
    
    
    for (int i = 0 ; i < dim ; ++i)
    {
        for (int j = 0 ; j <dim ; ++j)
        {
            if (i == dim/2 && j ==dim/2)
            {
                // std::cout <<" i = "<<i <<" j = "<<j <<std::endl;
                Field[i * dim + j] = 1;
                Field[(i+1) * dim + j] = 1;
                Field[(i-1) * dim + j] = 1;
                Field[i * dim + j+1] = 1;
                Field[i * dim + j-1] = 1;
                Field[(i+1) * dim + j-1] = 1;
                Field[(i+1) * dim + j+1] = 1;
                Field[i * dim + j+1] = 1;
                Field[(i-1) * dim + j-1] = 1;
                Field[(i-1) * dim + j+1] = 1;
                
            }
        }
    }
}



                                                                   
// 88b           d88  ad88888ba     88          88    ad88
// 888b         d888 d8"     "8b    88          ""   d8"
// 88`8b       d8'88 Y8,            88               88
// 88 `8b     d8' 88 `Y8aaaaa,      88          88 MM88MMM ,adPPYba,
// 88  `8b   d8'  88   `"""""8b,    88          88   88   a8P_____88
// 88   `8b d8'   88         `8b    88          88   88   8PP"""""""
// 88    `888'    88 Y8a     a8P    88          88   88   "8b,   ,aa
// 88     `8'     88  "Y88888P"     88888888888 88   88    `"Ybbd8"'

// ##     ##  ######     ##       #### ######## ########       ##         #####
// ###   ### ##    ##    ##        ##  ##       ##           ####        ##   ##
// #### #### ##          ##        ##  ##       ##             ##       ##     ##
// ## ### ##  ######     ##        ##  ######   ######         ##       ##     ##
// ##     ##       ##    ##        ##  ##       ##             ##       ##     ##
// ##     ## ##    ##    ##        ##  ##       ##             ##   ###  ##   ##
// ##     ##  ######     ######## #### ##       ########     ###### ###   #####
//░

void ShowField(int *field, std::size_t dim){
    std::cout << "\x1B[2J\x1B[H";
    
    std::cout << "╔";
    for(std::size_t i = 0; i + 1 < dim; ++i){
        std::cout << "═╦";
    }
    std::cout << "═╗" << std::endl;
    
    for(std::size_t i = 0; i < dim; ++i){
        std::cout << "║";
        
        for(std::size_t j = 0; j < dim; ++j){
            if(1 == field[i * dim + j]){
                std::cout << "█";
            }else{
                std::cout << " ";
            }
            if(j + 1 < dim){
                std::cout << "|";
            }
        }
        
        std::cout << "║" << std::endl;
        
        if(i + 1 < dim){
            std::cout << "╠";
            
            for(std::size_t j = 0; j < dim; ++j){
                std::cout << "─";
            
                if(j + 1 < dim){
                    std::cout << "┼";
                }
            }
            std::cout << "╣" << std::endl;
        }else{
            std::cout << "╚";
            
            for(std::size_t j = 0; j < dim; ++j){
                std::cout << "═";
            
                if(j + 1 < dim){
                    std::cout << "╩";
                }
            }
            std::cout << "╝" << std::endl;
        }
    }
}
