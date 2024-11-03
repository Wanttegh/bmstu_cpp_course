#include "int2str.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stdio.h"

char * int2str(int number) {
    char * res = calloc(12, 1);
    int i = 10, sign = (number >= 0 ? 1 : -1);
    res[11] = '\0';
    while (number > 10 || number < -10) {
        res[i--] = sign*(number%10) + '0';
        number /= 10;
    }
    res[i--] = sign*number + '0';
    if (sign == -1) {
        res[i--] = '-';
    }
    return &res[i+1];
}
