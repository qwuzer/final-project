#pragma once

#include<stdint.h>
#include"struct.h"

// ai = "a" lot of "i"f-else 

int32_t roll_the_dice();

// for basic
//public function
void ai_turn(); 
//private function
void ai_set_road();
void ai_set_village();
void ai_upgrade();
void ai_find_empty_road();
void ai_find_empty_node();
void ai_find_village();
void ai_move_robber();

// for advance
//public function
void ai_advanced_pro_max_plus_ultra_turn();
//private function
void ai_find_high_cp_empty_node();
void ai_find_high_ememy_tile();
void ai_find_next_long_road();
void ai_use_crad();
void ai_judge_for_trade();
void ai_judge_for_buy_card();
void ai_sort_resource();



