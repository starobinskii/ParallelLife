#pragma once

void GetLife(
    int *field,
    int *field1, 
    size_t dim,
    const int startI = 0,
    int finishI = -1,
    const int startJ = 0,
    int finishJ = -1
);

int Mod(int a, int dim);