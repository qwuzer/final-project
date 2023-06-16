#include <stdio.h>
void gotoxy(int x, int y) { 
    printf("%c[%d;%df", 0x1B, y, x); 
} 
int main()
{
    int x, y;

   x = 70;
   y = 30;

   gotoxy(x, y);

   printf("C program to change cursor position.");
   printf("rersef\n");
   printf("fesfaef\n");
    return 0;
}