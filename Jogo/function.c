#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function.h"


int randomValue(){
    srand(time(NULL));
    int i = rand() % 1000;
    if(i % 2 == 0){
        return 0;
    }
    else{
        return 1;
    }
}