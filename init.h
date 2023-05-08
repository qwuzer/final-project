#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum TileType{ Tile_Hills , Tile_Fields  , Tile_Pasture, Tile_Forest, Tile_Mountains, Tile_Desert };

//int32_t tile_type[19]={5,2,2,4,1,2,3,3,5,1,4,3,1,4,5,2,4,3,6};

//int32_t tile_dice_num[18] = { 5 , 2 , 6 , 3 , 8 , 10 , 9 , 12 , 11 , 4 , 8 , 10 , 9 , 4 , 5 , 6 , 3 , 11 };

typedef struct _sTile
{
    int32_t index;//1-19
    int32_t type;//1-7
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
      3 | *      or      * ㄧ 1
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

typedef struct _sRoad
{
    int32_t index;
    int32_t owner;
    struct _sRoad* dir1;
    struct _sRoad* dir2;
    struct _sRoad* dir3;
    struct _sRoad* dir4;
}road;



node *init_node();

tile *init_tile();

road *init_road();