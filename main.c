#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int sumNumbers(int initNumber){
    int sum = 0;
    while(initNumber != 0){
        sum =sum + (initNumber % 10);
        initNumber = initNumber / 10;
    }
    return sum;
}

int main(){


    return 0;
}