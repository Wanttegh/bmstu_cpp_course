#include <assert.h>
#include "str2int.h"
#include <stdlib.h>
// если строка пустая или состоит из одного символа, который не цифра

int str_size(const char * str){
	int i = 0;
	const char * strc = str;
	while (*strc) {i++; strc++;}
	return i;
}

int access(const char * str){
	const char * strc = str;
	if (str_size(strc) == 0) return 0;
	else if (str_size(strc) == 1){
		if (*strc < '0' || *strc > '9') return 0;
	}	
	return 1;
}

int str2int(const char *str) {
    assert(*str != '\0');
    int sign = 1;
    int num = 0;
    const char * strc = str;  
    if (str[0] == '-' || str[0] == '+'){
    	sign = (*str == '-') ? -1 : 1;
	str++;
    }
    while (*str == ' ') str++;
    assert(access(str) != 0);

    while (*str){
    	    if (*str >= '0' && *str <= '9') num = num*10 + (*str - '0');
	        else assert(*str >= '0' && *str <= '9');
        	str++;
    }

	char * ptr;
    assert(num*sign == strtol(strc, &ptr, 10));

    return num * sign;
}