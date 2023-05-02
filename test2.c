#include <stdio.h>
#include "color.h"

void print_node(){
	//check_owner();
	//if...print(*, V, C)
	//clr_rst
}
void check_owner(){
	//print_clr
}
void print_tile(){
	//print_clr
}

void print_board() {
    printf("              B   *---*   W   \n");
    printf("             / \\ /     \\ / \\ \n");
    printf("            *---*       *---*\n");
    printf("           /     \\     /     \\ \n");
    printf("  ?---*---*       *---*       *---*---?\n");
    printf("   \\ /     \\     /     \\     /     \\ /\n");
    printf("    *       *---*       *---*       *\n");
    printf("     \\     /     \\     /     \\     /\n");
    printf("      *---*       *---*       *---*\n");
    printf("     /     \\     /     \\     /     \\ \n");
    printf("    *       *---*       *---*       *\n");
    printf("   / \\     /     \\     /     \\     / \\ \n");
    printf("  ?---*---*       *---*       *---*---R\n");
    printf("     /     \\     /     \\     /     \\ \n");
    printf("    *       *---*       *---*       *\n");
    printf("     \\     /     \\     /     \\     /\n");
    printf("      *---*       *---*       *---*\n");
    printf("         / \\     /     \\     / \\ \n");
    printf("        F---*---*       *---*---S\n");
    printf("                 \\     /   \n");
    printf("                  *---*\n");
    printf("                   \\ /   \n");
    printf("                    ?\n");
}

int main() {
    print_board();
    return 0;
}

