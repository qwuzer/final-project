#pragma once
#include <stdint.h>
//#include "init.h"
#include "struct.h"
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
/*enum Resource{ Brick = 1 , Grain , Sheep , Lumber , Ore };

typedef struct _sPlayer
{
    int32_t index;//0-3
    int32_t color;//0-3
    int32_t resource[6];//1-5
    int32_t victory_point;//0-10
    int32_t road_num;//0-15
    int32_t settlement_num;//0-5
    int32_t building_index[54];//0-53 0,1,2
    int32_t city_num;//0-4
    int32_t knight_num;//0-5
    int32_t longest_road;//0,1
    int32_t largest_army;//0,1*/
    /*TODO add dev card type*/
   /* int32_t dev_card_num;
    int32_t dev_card[5];//0-25

}Player;*/
void check_owner( int32_t owner );
void print_tile( tile tile);
void print_node( node node);
void print_board( tile * pTile, node * pNode, road * pRoad, Player * pPlayer );


