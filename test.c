#include "color.h"
#include <stdio.h>

int main(){
    printf(CLR_24_FG(244,164,96)"test\n");
    printf("test\n");
    printf("    \n");
    printf(CLR_RST);
    printf(CLR_24_FG(165,42,42)"test\n");
    //printf(CLR_RST);
    printf("test\n");
    printf("    \n");

    return 0;
}                                                                                                                                      
