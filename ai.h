#pragma once

#include<stdint.h>
#include"struct.h"

// ai = "a" lot of "i"f-else 

typedef struct _arg
{
    Player *p;
    tile *t;
    node *n;
    road *r;
    int32_t me;
}Arg;

int32_t roll_the_dice();

// for basic
//public function
void ai_turn( Player *ptr_player , tile *ptr_tile , node *ptr_node , road *ptr_road , int32_t index_num );
//private function
void ai_set_road( int32_t where , Arg arg );
void ai_set_village( int32_t where , Arg arg );
void ai_upgrade( int32_t where , Arg arg );
int32_t ai_find_empty_road( Arg arg );
int32_t ai_find_empty_node( Arg arg );
int32_t ai_find_village( Arg arg );
void ai_move_robber( int32_t where , Arg arg );
void ai_get_resource( int32_t dice_number , Arg arg );

// for advance
//public function
void ai_advanced_pro_max_plus_ultra_turn();
//private function
int32_t ai_find_high_cp_empty_node();
int32_t ai_find_high_ememy_tile();
int32_t ai_find_next_long_road();
void ai_use_card();
void ai_judge_for_trade();
void ai_judge_for_buy_card();
void ai_sort_resource();



