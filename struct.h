#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1: Hills - bricks - 3
//2: Fields - grain - 4
//3: Pasture - sheep - 4 
//4: Forest - lumber - 4
//5: Mountains - ore - 3
//6: Desert - no resource - 1
enum TileType{ Tile_Hills = 1 , Tile_Fields  , Tile_Pasture, Tile_Forest, Tile_Mountains, Tile_Desert };

int32_t tile_type[19];//1-6
//{ 5 , 2 , 2 , 4 , 1 , 2 , 3 , 3 , 5 , 1 , 4 , 2 , 1 , 4 , 5 , 2 , 4 , 3 , 6 };
//starting from upper-left corner and go counter-clockwise

int32_t tile_dice_num[18] = { 5 , 2 , 6 , 3 , 8 , 10 , 9 , 12 , 11 , 4 , 8 , 10 , 9 , 4 , 5 , 6 , 3 , 11 };//2-12
//{A-5} {B-2} {C-6} {D-3} {E-8} {F-10} {G-9} {H-12} {I-11} {J-4} {K-8} {L-10} {M-9} {N-4} {O-5} {P-6} {Q-3} {R-11} 

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


typedef struct _sTile
{
    int32_t index;//1-19
    int32_t resource_type;//1-6(represents terrain also resources)
    int32_t robber;//0,1
    int32_t dice_num;//2-12
    struct _sNode* nodes[6]; 
}tile;


enum Resource{ Brick = 0 , Grain , Sheep , Lumber , Ore };

typedef struct _sPlayer
{
    int32_t index;//0-3
    int32_t color;//0-3
    int32_t resource[5];//0-4
    int32_t victory_point;//0-10
    int32_t road_num;//0-15
    int32_t settlement_num;//0-5  
    int32_t building_index[54];//0-53 0,1,2
    int32_t city_num;//0-4
    int32_t knight_num;//0-5
    int32_t longest_road;//0,1
    int32_t largest_army;//0,1
}Player;


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
