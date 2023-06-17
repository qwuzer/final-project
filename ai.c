#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include"struct.h"
#include"ai.h"


// ai = "a" lot of "i"f-else 


typedef struct _arg
{
    Player *p;
    tile *t;
    node *n;
    road *r;
}Arg;


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
void ai_turn( Player *p , tile *t , node *n , road *r ); 
//private function
void ai_set_road( int32_t where , Arg arg );
void ai_set_village( int32_t where , Arg arg );
void ai_upgrade( int32_t where , Arg arg );
int32_t ai_find_empty_road( Arg arg );
int32_t ai_find_empty_node( Arg arg );
int32_t ai_find_village( Arg arg );
void ai_move_robber( int32_t where , Arg arg );

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


void ai_turn( Player *ptr_player , tile *ptr_tile , node *ptr_node , road *ptr_road )
{
    Arg arg;
    arg.p = ptr_player;
    arg.t = ptr_tile;
    arg.n = ptr_node;
    arg.r = ptr_road;
    int32_t dice = roll_the_dice();
    // no buy card
    // no trade
    // random move robber
    if( dice == 7 )
    {
        ai_move_robber( -1 , arg ); 
    }
    // upgrade villige
    ai_upgrade( ai_find_villige( arg ) , arg );
    // build village
    ai_set_village( ai_find_empty_node( arg ) , arg );
    // bulid road 
    ai_set_road( ai_find_empty_road( arg ) , arg );
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

void ai_set_road( int32_t where , Arg arg )
{
    // check resource
    if( arg.p->resource[1] > 0 &&
        arg.p->resource[4] > 0 )
    {
        //check place and road_num
        if( where!=-1 && arg.p->road_num>0 )
        {
            int32_t who = arg.p->index;
            printf("This is player %d, I want to build a road at %d.\n", who , where );
            
            arg.p->resource[1] -= 1;
            arg.p->resource[4] -= 1;
            arg.p->road_num -= 1;


            *(arg.r+where-1).owner = who;
        }
        else if( where!=-1 )
        {
            printf("It seems that there is no place to build a new road!\n");
        }
        else
        {
            printf("It seems that I didn't have enough road to build a new one!\n");
        }
    }
    else
    {
        printf("It seems that I didn't have enough resource to build a new road!\n");
    }
}

void ai_set_village( int32_t where , Arg arg )
{
    // check resource
    if( arg.p->resource[1] > 0 &&
        arg.p->resource[2] > 0 &&
        arg.p->resource[3] > 0 &&
        arg.p->resource[4] > 0 )
    {
        //check place and settlement_num
        if( where!=-1 && arg.p->settlement_num>0 )
        {
            int32_t who = arg.p->index;
            printf("This is player %d, I want to build a village at %d.\n", who , where );
            
            arg.p->resource[1] -= 1;
            arg.p->resource[2] -= 1;
            arg.p->resource[3] -= 1;
            arg.p->resource[4] -= 1;
            arg.p->settlement_num -= 1;

            *(arg.n+where-1).type = 1;
            *(arg.n+where-1).owner = who;

            arg.p->building_index[where-1] = 1;
        }
        else if( where!=-1 )
        {
            printf("It seems that there is no place to build a new village!\n");
        }
        else
        {
            printf("It seems that I didn't have enough village to build a new one!\n");
        }
    }
    else
    {
        printf("It seems that I didn't have enough resource to build a new village!\n");
    }
}

void ai_upgrade( int32_t where , Arg arg )
{
    // check resource
    if( arg.p->resource[2] > 1 &&
        arg.p->resource[5] > 2 )
    {
        //check place and city_num
        if( where!=-1 && arg.p->city_num>0 )
        {
            int32_t who = arg.p->index;
            printf("This is player %d, I want to build a city at %d.\n", who , where );
            
            arg.p->resource[2] -= 2;
            arg.p->resource[5] -= 3;
            arg.p->settlement_num -= 1;

            *(arg.n+where-1).type = 2;
            arg.p->building_index[where-1] = 2;
        }
        else if( where!=-1 )
        {
            printf("It seems that there is no place to build a new city!\n");
        }
        else
        {
            printf("It seems that I didn't have enough city to build a new one!\n");
        }
    }
    else
    {
        printf("It seems that I didn't have enough resource to build a new city!\n");
    }
}

int32_t ai_find_empty_road( Arg arg )
{
    int32_t who = arg.p->index;
    int32_t ava[72] = {};

    // find all avaliable road
    for( int32_t i=0 ; i<72 ; ++i )
    {
        int32_t yes = 0;
        // check node
        if( *( arg.r+i ).node1->owner == who || *( arg.r+i ).node2->owner == who )
        {
            if( *( arg.r+i ).owner == 0 )
            {
                yes = 1;
            }
        }
        // check road
        if( ( *( arg.r+i ).dir1 != NULL && *( arg.r+i ).dir1->owner == who ) || 
            ( *( arg.r+i ).dir2 != NULL && *( arg.r+i ).dir2->owner == who ) || 
            ( *( arg.r+i ).dir3 != NULL && *( arg.r+i ).dir3->owner == who ) ||
            ( *( arg.r+i ).dir4 != NULL && *( arg.r+i ).dir4->owner == who )  )
        {
            if( *( arg.r+i ).owner == 0 )
            {
                yes = 1;
            }
        } 

        if( yes == 1)
        {
            ava[i] = 1;
        }
    }

    // find nothing return -1
    int32_t non = 1;
    for( int32_t i=0 ; i<72 ; ++i )
    {
        if( ava[i] == 1 )
        {
            non = 0;
            break;
        }
    }
    if( non == 1 )
    {
        return -1;
    }

    // random select one
    while(1)
    {
        srand( time(NULL) );
        int32_t num = rand()%72;
        if( ava[num] == 1 )
        {
            return num+1;
        }
    }

}

int32_t ai_find_empty_node( Arg arg )
{
    int32_t who = arg.p->index;
    int32_t ava[54] = {};

    // pick node beside my roads
    for( int32_t i=0 ; i<72 ; ++i )
    {
        if( *(arg.r+i).onwer == who )
        {
            ava[ *(arg.r+i).node1->index ] = 1;
            ava[ *(arg.r+i).node2->index ] = 1;
        }
    }

    // delete nearby node 
    for( int32_t i=0 ; i<54 ; ++i )
    {
        int32_t yes = 0;
        // check node
        if( ( *( arg.n+i ).dir1 == NULL || *( arg.n+i ).dir1->owner == 0 ) && 
            ( *( arg.n+i ).dir2 == NULL || *( arg.n+i ).dir2->owner == 0 ) &&
            ( *( arg.n+i ).dir3 == NULL || *( arg.n+i ).dir3->owner == 0 ) &&
            ava[i] == 1 )
        {
            if( *( arg.n+i ).owner != 0 )
            {
                ava[i] = 0;
            }
        }    
    }

    // find nothing return -1
    int32_t non = 1;
    for( int32_t i=0 ; i<54 ; ++i )
    {
        if( ava[i] == 1 )
        {
            non = 0;
            break;
        }
    }
    if( non == 1 )
    {
        return -1;
    }

    // random select one
    while(1)
    {
        srand( time(NULL) );
        int32_t num = rand()%54;
        if( ava[num] == 1 )
        {
            return num+1;
        }
    }
}

int32_t ai_find_village( Arg arg )
{
    int32_t who = arg.p->index;
    int32_t ava[54] = {};
    int32_t count = 0;

    for( int32_t i=0 ; i<54 ; ++i )
    {
        if( *(arg.n+i).onwer == who && *(arg.n+i).type == 1 )
        {
            ava[54] = 1;
            ++count;
        } 
    }

    if( count == 0 )
    {
        return -1;
    }

    while(1)
    {
        srand( time(NULL) );
        int32_t num = rand()%54;
        if( ava[num] == 1 )
        {
            return num+1;
        }
    }
}

void ai_move_robber( int32_t where , Arg arg )
{
    srand( time(NULL) );
    int32_t target_tile = rand() % 19;
    if( where == -1 )
    {
        while( *(arg.t+target_tile).robber == 1 )
        {
            target_tile = rand() % 19;
        }
    }
    else
    {
        target_tile = where;
    }

    //origin
    int32_t origin = -1;
    for(int32_t i=0 ; i<19 ; ++i )
    {
        if( *(arg.t+target_tile).robber == 1 )
        {
            origin = i;
            *(arg.t+target_tile).robber = 0 ;
            break;
        }
    }
}
