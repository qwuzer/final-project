#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include"struct.h"
#include"ai.h"

#define HI printf("\nhi\n");

// ai = "a" lot of "i"f-else 

int32_t roll_the_dice()
{
    
    int32_t dice1 = rand() % 6 + 1;
    int32_t dice2 = rand() % 6 + 1;
    int32_t sum = dice1 + dice2;
    return sum;
}

// for basic
//public function
void ai_turn( Player **ptr_player , tile *ptr_tile , node *ptr_node , road *ptr_road , int32_t index_num ); 
//private function
void ai_set_road( int32_t where , Arg arg );
void ai_set_village( int32_t where , Arg arg );
void ai_upgrade( int32_t where , Arg arg );
int32_t ai_find_empty_road( Arg arg );
int32_t ai_find_empty_node( Arg arg );
int32_t ai_find_village( Arg arg );
void ai_move_robber( int32_t where , Arg arg );
void ai_get_resource( int32_t dice_number , Arg arg );

// // for advance
// //public function
// void ai_advanced_pro_max_plus_ultra_turn();
// //private function
// int32_t ai_find_high_cp_empty_node();
// int32_t ai_find_high_ememy_tile();
// int32_t ai_find_next_long_road();
// void ai_use_card();
// void ai_judge_for_trade();
// void ai_judge_for_buy_card();
// void ai_sort_resource();


void ai_turn( Player **ptr_player , tile *ptr_tile , node *ptr_node , road *ptr_road , int32_t index_num )
{
    printf("Hi, this is player %d :D\n",index_num );
    Arg arg;
    arg.op = ptr_player;
    arg.p = ptr_player[index_num-1];
    arg.t = ptr_tile;
    arg.n = ptr_node;
    arg.r = ptr_road;
    arg.me = index_num;
    srand( time(NULL) );
    int32_t dice = roll_the_dice();
    printf("I roll the dice and get %d.\n",dice);
    sleep(1);
    // no buy card
    // no trade
    // random move robber
    if( dice == 7 )
    {
        printf("Oh, it's 7.");
        ai_move_robber( -1 , arg ); 
    }
    else
    {
        ai_get_resource( dice , arg );
    }
    // upgrade villige
    sleep(1);
    printf("I think maybe I can ...\n");
    ai_upgrade( ai_find_village( arg ) , arg );
    // build village
    sleep(3);
    printf("And then I can ...\n");
    ai_set_village( ai_find_empty_node( arg ) , arg );
    // bulid road 
    sleep(3);
    printf("At the end maybe I can ...\n");
    ai_set_road( ai_find_empty_road( arg ) , arg );
    sleep(3);
    printf("That's all,next one~\n");
    sleep(5);
}

// void ai_advanced_pro_max_plus_ultra_turn()
// {
//     int32_t dice = roll_the_dice();
//     //move robber
//     if( dice == 7 )
//     {
//         ai_move_robber( ai_find_high_ememy_tile() );
//     }
//     //sort
//     ai_sort_resource();
//     //
//     if(false/* have function cards*/)
//     {
//         ai_use_card();
//     }
//     //upgrade
//     ai_upgrade( ai_find_villige() );
//     // build village
//     ai_set_village( ai_find_empty_node() );
//     // bulid road 
//     ai_set_road( ai_find_next_long_road() );

//     ai_judge_for_trade();
//     ai_judge_for_buy_card();
// }

void ai_set_road( int32_t where , Arg arg )
{
    //printf("this is ai set road`\n");
    // check resource
    if( arg.p->resource[1] > 0 &&
        arg.p->resource[4] > 0 )
    {
        //check place and road_num
        if( where!=-1 && arg.p->road_num<15 )
        {
            int32_t who = arg.me;
            printf("Okay,I want to build a road at %d.\n", where );
            
            arg.p->resource[1] -= 1;
            arg.p->resource[4] -= 1;
            arg.p->road_num += 1;


            (arg.r+where-1)->owner = who;
        }
        else if( arg.p->road_num<15)
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
    //printf("this is ai set viliage\n");
    // check resource
    if( arg.p->resource[1] > 0 &&
        arg.p->resource[2] > 0 &&
        arg.p->resource[3] > 0 &&
        arg.p->resource[4] > 0 )
    {
        //check place and settlement_num
        if( where!=-1 && arg.p->settlement_num<5 )
        {
            int32_t who = arg.me;
            printf("I want to build a village at %d.\n", where );
            
            arg.p->resource[1] -= 1;
            arg.p->resource[2] -= 1;
            arg.p->resource[3] -= 1;
            arg.p->resource[4] -= 1;
            arg.p->settlement_num += 1;

            (arg.n+where-1)->type = 1;
            (arg.n+where-1)->owner = who;

            arg.p->building_index[where-1] = 1;
        }
        else if( arg.p->settlement_num<5 )
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
    //printf("this is ai upgrade\n");
    // check resource
    // printf("Brick: %d\n",arg.p->resource[Brick]);
    // printf("Grain: %d\n",arg.p->resource[Grain]);
    // printf("Sheep: %d\n",arg.p->resource[Sheep]);
    // printf("Lumber: %d\n",arg.p->resource[Lumber]);
    // printf("Ore: %d\n",arg.p->resource[Ore]);
    //printf("where : %d\n",where);
    if( arg.p->resource[Grain] > 1 &&
        arg.p->resource[Ore] > 2 )
    {
        //check place and city_num
        if( where!=-1 && arg.p->city_num<4 )
        {
            int32_t who = arg.me;
            printf("HA! I want to build a city at %d.\n", where );
            
            arg.p->resource[2] -= 2;
            arg.p->resource[5] -= 3;
            arg.p->city_num += 1;
            arg.p->settlement_num -= 1;

            (arg.n+where-1)->type = 2;
            arg.p->building_index[where-1] = 2;
        }
        else if( arg.p->city_num<4 )
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
    //printf("this is ai find empty road\n");
    int32_t who = arg.me;
    int32_t ava[72] = {};

    // find all avaliable road
    for( int32_t i=0 ; i<72 ; ++i )
    {
        int32_t yes = 0;
        // check node
        if( ( arg.r+i )->node1->owner == who || ( arg.r+i )->node2->owner == who )
        {
            if( ( arg.r+i )->owner == 0 )
            {
                yes = 1;
            }
        }
        // check road
        int32_t value1 = 0 , value2 = 0 , value3 = 0 , value4 = 0;
        if( ( arg.r+i )->dir1 != NULL && ( arg.r+i )->dir1->owner == who )
        {
            value1 = 1;
            if( (arg.r+i)->node1 == (arg.r+i)->dir1->node1)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node1 == (arg.r+i)->dir1->node2)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir1->node1)
            {
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir1->node2)
            {
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
            
        } 
        if( ( arg.r+i )->dir2 != NULL && ( arg.r+i )->dir2->owner == who )
        {
            value2 = 1;
            if( (arg.r+i)->node1 == (arg.r+i)->dir2->node1)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node1 == (arg.r+i)->dir2->node2)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir2->node1)
            {
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir2->node2)
            {
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
        } 
        if( ( arg.r+i )->dir3 != NULL && ( arg.r+i )->dir3->owner == who )
        {
            value3 = 1;
            if( (arg.r+i)->node1 == (arg.r+i)->dir3->node1)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node1 == (arg.r+i)->dir3->node2)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir3->node1)
            {
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir3->node2)
            {;
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
        }
        if( ( arg.r+i )->dir4 != NULL && ( arg.r+i )->dir4->owner == who )
        {
            value4 = 1;
            if( (arg.r+i)->node1 == (arg.r+i)->dir4->node1)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node1 == (arg.r+i)->dir4->node2)
            {
                if( (arg.r+i)->node1->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir4->node1)
            {
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
            if( (arg.r+i)->node2 == (arg.r+i)->dir4->node2)
            {
                if( (arg.r+i)->node2->owner != who )
                {
                    value1 = 0;
                }
            }
        }
        
        if( value1+value2+value3+value4 > 0 )
        {
            if( ( arg.r+i )->owner == 0 )
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
    //printf("this is the end of find empty road\n");
    if( non == 1 )
    {
        return -1;
    }

    // random select one
    srand( time(NULL) );
    int32_t num = rand()%54;
    for(;;num++)
    {
        if( ava[num] == 1 )
        {   
            //printf("this is end of ai find village\n");
            return num+1;
        }
        if(num == 71) num = 0;
    }

}

int32_t ai_find_empty_node( Arg arg )
{
    printf("Let me find some empty nodes...\n");
    sleep(1);
    int32_t who = arg.me;
    //printf("ai[%d] is finding node...\n",who);
    int32_t ava[54] = {};

    // pick node beside my roads
    for( int32_t i=0 ; i<72 ; ++i )
    {
        if( (arg.r+i)->owner == who )
        {
            ava[ (arg.r+i)->node1->index ] = 1;
            ava[ (arg.r+i)->node2->index ] = 1;
        }
    }

    // delete nearby node 
    for( int32_t i=0 ; i<54 ; ++i )
    {
        int32_t yes = 0;
        // check node
        if( !( ( arg.n+i )->dir1 == NULL || ( arg.n+i )->dir1->owner == 0 ) || 
            !( ( arg.n+i )->dir2 == NULL || ( arg.n+i )->dir2->owner == 0 ) ||
            !( ( arg.n+i )->dir3 == NULL || ( arg.n+i )->dir3->owner == 0 ) )
        {
            ava[i] = 0;
        }
        if( ( arg.n+i )->owner != 0 )
        {
            ava[i] = 0;
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
    //printf("this is the end of find empty node\n");
    if( non == 1 )
    {
        printf("That's too bad...\n");
        return -1;
    }

    // random select one
    srand( time(NULL) );
    int32_t num = rand()%54;
    for(;;num++)
    {
        if( ava[num] == 1 )
        {   
            //printf("this is end of ai find village\n");
            printf("Found!!\n");
            return num+1;
        }
        if(num == 53) num = -1;
    }
}

int32_t ai_find_village( Arg arg )
{
    //printf("this is ai find village.\n");
    int32_t who = arg.me;
    int32_t ava[54] = {};
    int32_t count = 0;

    //printf("village found : ");
    for( int32_t i=0 ; i<54 ; ++i )
    {
        if( (arg.n+i)->owner == who && (arg.n+i)->type == 1 )
        {
            // printf("i = %d \n",i);
            // printf(" %d == %d \n",(arg.n+i)->owner , who );
            ava[i] = 1;
            count++;
        } 
    }//printf("\n");
    
    if( count == 0 )
    {
        //printf("this is end of ai find village\n");
        return -1;
    }
    

    srand( time(NULL) );
    int32_t num = rand()%54;
    for(;;num++)
    {
        if( ava[num] == 1 )
        {   
            //printf("this is end of ai find village\n");
            return num+1;
        }
        if(num == 53) num = -1;
    }
}

void ai_move_robber( int32_t where , Arg arg )
{
    //printf("this is ai move robber\n");

    // cut in half
    for(int32_t i=0 ; i<4 ;++i)
    {
        int re_sum = 0;
        for(int j=1;j<6;j++)
        {
            re_sum += arg.op[i]->resource[j];
        }
        if( re_sum >= 8 )
        {
            int32_t half_sum = re_sum/2;
            while(re_sum>half_sum)
            {
                int temp_i = rand()%5+1;
                if( arg.op[i]->resource[temp_i] > 0 )
                {
                    arg.op[i]->resource[temp_i] -= 1;
                    re_sum -= 1;
                }
            }
        }
    }



    srand( time(NULL) );
    int32_t target_tile = rand() % 19;
    if( where == -1 )
    {
        while( (arg.t+target_tile)->robber == 1 )
        {
            target_tile = rand() % 19;
        }
    }
    else
    {
        target_tile = where-1;
    }
    printf("I want to move robber to tile %d!!!\n",target_tile+1);
    // find origin and move it
    int32_t origin = -1;
    for( int32_t i=0 ; i<19 ; ++i )
    {
        if( (arg.t+i)->robber == 1 )
        {
            origin = i;
            (arg.t+i)->robber = 0 ;
            break;
        }
    }
    (arg.t+target_tile)->robber = 1;

    // start to rob
    int32_t list_num = 0;
    int32_t rob_list[3] = {};
    int32_t who = arg.me;
    // choose target
    for( int32_t i=0 ; i<6 ; ++i )
    {
        if((arg.t+target_tile)->nodes[i]->owner != 0  &&
           (arg.t+target_tile)->nodes[i]->owner != who)
        {
            //check if record again
            int32_t rec = 0;
            for(int32_t j=0 ; j<list_num ; ++j )
            {
                if( rob_list[j] == (arg.t+target_tile)->nodes[i]->owner -1)
                {
                    rec = 1;
                }
            }
            if( rec == 0 )
            {
                rob_list[list_num] = (arg.t+target_tile)->nodes[i]->owner-1;
                list_num += 1;
            }
        }
    }

    if( list_num != 0 )
    {
        srand( time(NULL) );
        for(int32_t i=0 ; i<list_num ; ++i )
        {
            if( arg.op[rob_list[i]]->resource[1] +
                arg.op[rob_list[i]]->resource[2] +
                arg.op[rob_list[i]]->resource[3] +
                arg.op[rob_list[i]]->resource[4] +
                arg.op[rob_list[i]]->resource[5] != 0)
            {
                int32_t j=1;
                for( ; j<6 ; ++j)
                {
                    if(arg.op[rob_list[i]]->resource[j] >0)
                    {
                        arg.op[rob_list[i]]->resource[j] -= 1;
                        break;
                    }
                }
                arg.p->resource[j] += 1;
                break;
            }
        }
    }
    //printf("this is the end of ai move robber.\n");
}


void ai_get_resource( int32_t dice_number , Arg arg )
{
    //printf("this is ai get resource \n");
    int32_t who = arg.me;
    //printf("I am %d\n",who);
    for( int32_t i=0 ; i<19 ; i++ )
    {
        // printf(" i = %d\n",i);

        if( ( arg.t+i )->dice_num == dice_number &&
            ( arg.t+i )->robber == 0 )
        {

            // printf("found tile\n");

            for(int j=0;j<6;j++)
            {
                // printf("node [%d] : %d ",j,(arg.t+i)->nodes[j]->index);

                if((arg.t+i)->nodes[j]->type == 1 )
                {

                    // printf(" node type = %d \n",(arg.t+i)->nodes[j]->type);
                    // printf("arg.op[%d]->",(arg.t+i)->nodes[j]->owner);
                    // printf("resource[%d]  ",(arg.t+i)->resource_type);
                    // printf(" = %d + 1 ",arg.op[(arg.t+i)->nodes[j]->owner]->resource[(arg.t+i)->resource_type]);

                    arg.op[(arg.t+i)->nodes[j]->owner-1]->resource[(arg.t+i)->resource_type] += 1;

                }
                if((arg.t+i)->nodes[j]->type == 2 )
                {
                    arg.op[(arg.t+i)->nodes[j]->owner-1]->resource[(arg.t+i)->resource_type] += 1;
                }

                //printf("---------------------------\n");
            }

            //printf("the end of found tile\n");
        }

    }
    //printf("this is the end of ai get resource\n");
}