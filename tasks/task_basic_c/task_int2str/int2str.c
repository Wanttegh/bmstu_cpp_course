#include "int2str.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stdio.h"

char * int2str(int number) {
    char * res = calloc(12, 1);
    int sign = (number >= 0 ? 1 : -1);
    res[11] = '\0';
    for (int i = 10; i >= 1; i--) {
        res[i] = (number % 10) * sign + '0';
        number /= 10;
        if (number * sign == 0) {
            if (sign == -1) {
                res[i-1] = '-';
                return &res[i-1];
            }
            return &res[i];
        }
    }
    return res;
}
