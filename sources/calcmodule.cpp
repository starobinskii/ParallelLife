#include <vector>
#include <cmath>

void Calc(std::vector <std::vector <bool> > &field)
{
	
}

int Mod(int a, int dim)
{
	 a -=  dim * std::floor(a/dim);
	 return abs(a);
}

void GetLife(
    int *field,
    int *field1, 
    size_t dim,
    const int startI = 0,
    int finishI = -1,
    const int startJ = 0,
    int finishJ = -1
){
    if(-1 == finishI){
        finishI = dim;
    }
    if(-1 == finishJ){
        finishJ = dim;
    }
    
    for(int i = startI; i < finishI; ++i){
        for(int j = startJ; j < finishJ; ++j){
			int de = 0;
			if (field[i * dim + j] == 0 )
			{
				if(field[Mod(i-1, dim) * dim + j]==1) de++;
				if(field[Mod(i-1,dim) * dim + Mod(j-1, dim)]==1) de++;
				if(field[Mod(i-1, dim) * dim + Mod(j+1,dim)]==1) de++;
				if(field[i * dim + Mod(j-1, dim)]==1) de++;
				if(field[i * dim + Mod(j+1, dim)]==1) de++;
				if(field[Mod(i+1, dim) * dim + j]==1) de++;
				if(field[Mod(i+1, dim) * dim + Mod(j-1, dim)]==1) de++;
				if(field[Mod(i+1, dim) * dim + Mod(j+1, dim)]==1) de++;
				
				if(de==3) field1[i * dim + j]= 1;
				
			}
			int se =0;
			if (field[i * dim + j]==1)
			{
				if(field[Mod(i-1, dim) * dim + j]==1) de++;
				if(field[Mod(i-1, dim) * dim + Mod(j-1, dim)]==1) de++;
				if(field[Mod(i-1, dim) * dim + Mod(j+1, dim)]==1) de++;
				if(field[i * dim + Mod(j-1, dim)]==1) de++;
				if(field[i * dim + Mod(j+1, dim)]==1) de++;
				if(field[Mod(i+1, dim) * dim + j]==1) de++;
				if(field[Mod(i+1, dim) * dim + Mod(j-1, dim)]==1) de++;
				if(field[Mod(i+1, dim) * dim + Mod(j+1, dim)]==1) de++;
				
				if(de==3 || de==2) field1[i * dim + j] = 1;
				else field1[i * dim + j] = 0;
			}
        }
    }
}

