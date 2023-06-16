#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include"struct.h"
#include"ai.h"


// ai = "a" lot of "i"f-else 

int32_t roll_the_dice()
{
    srand( time(NULL) );
    int32_t dice1 = rand() % 6 + 1;
    int32_t dice2 = rand() % 6 + 1;
    int32_t sum = dice1 + dice2;
    return sum;
}

// for basic
//public function
void ai_turn(); 
//private function
void ai_set_road( int32_t where );
void ai_set_village( int32_t where );
void ai_upgrade( int32_t which );
int32_t ai_find_empty_road();
int32_t ai_find_empty_node();
int32_t ai_find_village();
int32_t ai_move_robber( int32_t where );

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


void ai_turn()
{
    int32_t dice = roll_the_dice();
    // no buy card
    // no trade
    // random move robber
    if( dice == 7 )
    {
        ai_move_robber( -1 ); 
    }
    // upgrade villige
    ai_upgrade(ai_find_villige());
    // build village
    ai_set_village(ai_find_empty_node());
    // bulid road 
    ai_set_road(ai_find_empty_road());
}

void ai_advanced_pro_max_plus_ultra_turn()
{
    int32_t dice = roll_the_dice();
    //move robber
    if( dice == 7 )
    {
        ai_move_robber( ai_find_high_ememy_tile() );
    }
    //sort
    ai_sort_resource();
    //
    if(false/* have function cards*/)
    {
        ai_use_card();
    }
    //upgrade
    ai_upgrade( ai_find_villige() );
    // build village
    ai_set_village( ai_find_empty_node() );
    // bulid road 
    ai_set_road( ai_find_next_long_road() );

    ai_judge_for_trade();
    ai_judge_for_buy_card();
}