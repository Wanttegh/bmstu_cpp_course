#include <assert.h>
#include "int2str.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

char * int2str(int number) {
    int i = 2, int_l = 0;
    int sign = (number >= 0 ? 1 : -1);
    int number_copy = number;
    while (number_copy > 10 || number_copy < -10){
        i++; int_l++;
        number_copy /= 10;
    }
    i++; int_l++;
    if (sign < 0) i++;
    char * str = calloc(i, 1);
    int it = 0, check = 0;
    while (check != int_l){
        str[it++] = (sign*(number % 10) + '0');
        check++;
        number /= 10;
    }
    if (sign < 0) str[it++] = '-';
    str[it] = '\0';
    for (int j = 0, k = it - 1; j < k; j++, k--){
        char c = str[j];
        str[j] = str[k];
        str[k] = c;
    }
    char * res = calloc(i, 1);
    for (int m = 0; m <= i; m++){
        res[m] = str[m];
    }
    return res;
}