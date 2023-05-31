#pragma once
#include <stdint.h>
#include "struct.h"
//#include "init.h"
//type
/*
typedef struct _sTile
{
    int32_t index;//1-19
    int32_t type;//1-6
    int32_t robber;//0,1
    int32_t dice_num;//2-12
}tile;
typedef struct _sRoad
{
    int32_t index;
    int32_t owner;
    struct _sRoad* dir1;
    struct _sRoad* dir2;
    struct _sRoad* dir3;
    struct _sRoad* dir4;
}road;
typedef struct _sNode
{
    int32_t index;//1-54
    int32_t type;//none, settlemet, city 0,1,2
    int32_t owner;//0-4
    int32_t triangle_type;//right or left 0,1*/
    /*
             1          3
            /            \
      3 ㄧ *      or      * ㄧ 1
            \            /
             2          2
    *//*
    struct _sNode* dir1;
    struct _sNode* dir2;
    struct _sNode* dir3;
    int32_t tile1;
    int32_t tile2;
    int32_t tile3;
}node;*/
void check_owner( int32_t owner );
void print_tile( tile tile);
void print_node( node node);
void print_board( tile * pTile, node * pNode, road * pRoad );


