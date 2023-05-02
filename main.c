#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"

//1: Hills - bricks - 3
//2: Fields - grain - 4
//3: Pasture - sheep - 4 
//4: Forest - lumber - 4
//5: Mountains - ore - 3
//6: Desert - no resource - 1
enum TileType{ Tile_Hills , Tile_Fields  , Tile_Pasture, Tile_Forest, Tile_Mountains, Tile_Desert };

int32_t tile_type[19];//1-6
//{ 5 , 2 , 2 , 4 , 1 , 2 , 3 , 3 , 5 , 1 , 4 , 2 , 1 , 4 , 5 , 2 , 4 , 3 , 6 };
//starting from upper-left corner and go counter-clockwise

int32_t tile_dice_num[18] = { 5 , 2 , 6 , 3 , 8 , 10 , 9 , 12 , 11 , 4 , 8 , 10 , 9 , 4 , 5 , 6 , 3 , 11 };//2-12
//{A-5} {B-2} {C-6} {D-3} {E-8} {F-10} {G-9} {H-12} {I-11} {J-4} {K-8} {L-10} {M-9} {N-4} {O-5} {P-6} {Q-3} {R-11} 

typedef struct _sTile
{
    int32_t index;//1-19
    int32_t type;//1-6
    int32_t robber;//0,1
    int32_t dice_num;//2-12
}tile;

typedef struct _sNode
{
    int32_t index;//1-54
    int32_t type;//none, settlemet, city 0,1,2
    int32_t owner;//0-4
    int32_t triangle_type;//right or left 0,1
    /* 
             1          3 
            /            \
      3 ㄧ *      or      * ㄧ 1
            \            /
             2          2
    */
    struct _sNode* dir1;
    struct _sNode* dir2;
    struct _sNode* dir3;
    int32_t tile1;
    int32_t tile2;
    int32_t tile3;
}node;

int32_t road_built[72];//0,1,2,3,4

typedef struct _sRoad
{
    int32_t index;
    int32_t owner;
    struct _sRoad* dir1;
    struct _sRoad* dir2;
    struct _sRoad* dir3;
    struct _sRoad* dir4;
}road;

void init_node( int32_t i )
{
    node* n1 = (node*)malloc(sizeof(node));
    n1->index = i;
    n1->type = 0;
    n1->owner = 0;
    
    return;
}


int main ()
{
    printf(CLR_BOLD CLR_GRN"   *---*  \n"CLR_RST);
    printf("  /     \\ \n");
    printf(CLR_FLASH CLR_CYN" *       *\n"CLR_RST);
    printf("  \\     /\n");
    printf(CLR_24_FG(244,164,96)"   *---*\n"CLR_RST);

    
    return 0;
}