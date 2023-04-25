#include <stdio.h>
#include <stdlib.h>

//1: Hills - bricks
//2: Fields - grain
//3: Pasture - sheep
//4: Forest - lumber
//5: Mountains - ore
//6: Desert - no resource
//7: Robber - no resource
enum TileType{ Tile-Hills = 1, Tile-Fields , Tile-Pasture, Tile-Forest, Tile-Mountains, Tile-Desert , Tile-Robber };

int32_t tile[19];//1-7

typedef struct _sNode
{
    int32_t index;//1-54
    int32_t type;//none, settlemet, city 0,1,2
    int32_t owner;//0-4
    int32_t triangle_type;//right or left 0,1
    /* 
             1          3 
            /            \
      3 ㄧ *    or.       * ㄧ 1
           \            /
           2           2
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
    printf("   *---*  \n");
    printf("  /     \\ \n");
    printf(" *       *\n");
    printf("  \\     /\n");
    printf("   *---*\n");

    
    return 0;
}