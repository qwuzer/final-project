#include "color.h"
#include <stdio.h>

int main(){
	printf("THis is HILL!\n");
	printf(CLR_24_BG(208,102,51));
	printf("1   \n");
	printf("    \n");
	printf(CLR_RST);
	printf("THis is Pasture!\n");
	printf(CLR_24_BG(139,139,0));
	//printf(CLR_RST);
	printf("1   \n");
	printf("    \n");
	printf(CLR_RST);
    printf("THis is Desert!\n");
    printf(CLR_24_BG(205,149,12));
    //printf(CLR_RST);
    printf("1   \n");
    printf("    \n");
	printf(CLR_RST);
    printf("THis is Field!\n");
    printf(CLR_24_BG(105,139,34));
    //printf(CLR_RST);
    printf("1   \n");
    printf("    \n");
    printf(CLR_RST);	
    printf("THis is Forest!\n");
    printf(CLR_24_BG(34,139,34));
    //printf(CLR_RST);
    printf("1   \n");
    printf("    \n");
    printf(CLR_RST);	
    printf("THis is Moutains!\n");
    printf(CLR_24_BG(131,139,131));
    //printf(CLR_RST);
    printf("1   \n");
    printf("    \n");
    printf(CLR_RST);	
	return 0;
}
