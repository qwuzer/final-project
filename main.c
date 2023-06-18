#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "struct.h"
#include "init.h"
#include "color.h"
#include "prt_board2.h"
#include "prtInfo.h"
#include "ai.h"

//generate random number
int32_t roll_dice( Player *player )
{
    int32_t dice1 = rand() % 6 + 1;
    int32_t dice2 = rand() % 6 + 1;
    int32_t sum = dice1 + dice2;
    printf("Player %d rolled a value of %d\n",player->index,sum);
   //sum = 7;
    return sum;
}

void largest_army( Player *player[] , road *proad  )
{
    // for( int32_t i = 0 ; i < 4 ; i++ )
    // {
    //     player[i]->largest_army = 0;
    // }

    //find the player with the largest knight number
    int32_t max = 3;
    for(int32_t i = 0 ; i < 4 ; i++ )
    {
        if( player[i]->knight_num >= max )
        {
            max = player[i]->knight_num;
        }
    }

    //set the player's largest army to 1 if it has the largest knight number
    for(int32_t i = 0 ; i < 4 ; i++ )
    {
        if( player[i]->knight_num == max )
        {
            player[i]->largest_army = 1;
            //player[i]->victory_point += 2;
        }
    }
}


void longest_road( Player *player[] , road *proad )
{
    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        if( proad[i].owner != 0 )
        {
            player[proad[i].owner - 1]->road_num += 1;
        }
    }
    // //find the player with the longest road
    // for(int32_t i = 0 ; i < 4 ; i++ )
    // {
    //     int32_t max = 0;
    //     if( player[i]->road_num > max )
    //     {
    //         max = player[i]->road_num;
    //     }
    // }
    // //set the player's longest road to 1 if it has the longest road
    // for(int32_t i = 0 ; i < 4 ; i++ )
    // {
    //     if( player[i]->road_num == max )
    //     {
    //         player[i]->longest_road = 1;
    //     }
    // }
}

//check if any player has settlement on the number
//if yes, give the player resources
//check robber! -> reduce resources 
void obtain_resources( int32_t sum , Player *player , tile *ptile )
{
    char* resource_string[5] = { "Brick" , "Grain" , "Sheep" , "Lumber" , "Ore" };
   // printf("Player %d rolled a value of %d\n",player->index,sum);

    for( int32_t i = 0 ; i < 19 ; i++ )
    {
        if( ptile[i].dice_num == sum && ptile[i].robber != 1 )
        {
            for( int32_t j = 0 ; j < 6 ; j++ )
            {
                if( ptile[i].nodes[j]->owner != 0 )//if there is a building on the node
                {
                    if( ptile[i].nodes[j]->type == 1 )//settlment 
                    {
                        player[ptile[i].nodes[j]->owner - 1].resource[ptile[i].resource_type] += 1;
                    printf("Player %d obtained 1 %s\n",ptile[i].nodes[j]->owner ,resource_string[ptile[i].resource_type-1]);
                    }
                    else if( ptile[i].nodes[j]->type == 2 )//city
                    {
                        player[ptile[i].nodes[j]->owner - 1].resource[ptile[i].resource_type] += 2;
                    }
                    
                }
            }
        }
    }
}

//check if any player has 10 points
int32_t is_game_over( Player *players[] )
{
    //longest_army( players , proad );
    if( players[0]->largest_army == 1)
    {
        if( players[0]->victory_point + 2 >= 10 )
        {
            return 1;
        }
    }
    for( int32_t i = 1 ; i < 4 ; i++ )
    {
        int32_t is_largest_army = 0 ;
        if( players[i]->largest_army == 1 )
        {
            is_largest_army = 1;
        }
        players[i]->victory_point = players[i]->settlement_num + players[i]->city_num * 2 + (is_largest_army * 2);
    }


    print_all( players);
    for( int32_t  i = 0 ; i < 4 ; i++ )
    {
        //printf("Player %d has %d points\n",players[i]->index,players[i]->victory_point);
        if( players[i]->victory_point >= 10 )
        {
            return 1;
        }
    }
    return 0;
}

/* AFTER ANY OPTION IS PERFORMED, OPTION MUST BE UPDATED*/
/*The reason of this option array is to provide a cleaner user's menu every turn*/
enum options {  buy_dev_card = 0 , use_dev_card = 1 , trade_with_player , marine_trade , build_settlement , build_road , build_city , end_turn };
///int32_t option[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1};

int32_t print_option_menu( int32_t option[] , size_t size )
{
    int32_t ret = 0;
    printf("Please select an option:\n");
    int32_t index = 1;

    for( int32_t i = 0 ; i < 8 ; i++ )
    {
        if( option[i] == 1 )
        {
            printf("%d. ",index);
            switch( i )
            {
                case 0:
                    printf("Buy development card\n");
                    index++;
                    break;
                case 1:
                    printf("Use development card\n");
                    index++;
                    break;
                case 2:
                    printf("Trade with player\n");
                    index++;
                    break;
                case 3:
                    printf("Marine trade\n");
                    index++;
                    break;
                case 4:
                    printf("Build settlement\n");
                    index++;
                    break;
                case 5:
                    printf("Build road\n");
                    index++;
                    break;
                case 6:
                    printf("Build city\n");
                    index++;
                    break;
                case 7:
                    printf("End turn\n");
                    index++;
                    break;
                default:
                    break;
            }
            
        }
    }

    if( index == 1 )
    {
        printf("No option available!\n");
        return -1;
    }

    printf("----------------------------\n");
    printf("Please enter your option: ");
    // printf("index = %d\n",index);
    scanf("%d",&ret);

    if( ret >= index || ret < 1 )
    {
        printf("Invalid input!\n");
        print_option_menu( option , size );
    }

    return ret;
}

enum marine_trade_opt { no_port = 0 , normal_port = 1 , brick_port = 2 , wood_port = 3 , sheep_port = 4 , grain_port = 5 , ore_port = 6};


void marine_trade_func( Player *player , int32_t *tmp_marine_option  )
{
    marine_trade:
    for( int32_t i = 7 ; i >= 0 ; i-- )
    {
        //printf("%d ",tmp_marine_option[i]);
        int32_t on_any_port = 0;
        if( tmp_marine_option[i] )
        {
            //on_any_port += 1;
            switch (i)
            {
                case 1:
                    // if( player->resource[brick] >= 3)
                    printf("1.)Trade 3 resources for 1 resource!\n");
                    break;
                case 2:
                    printf("2.)Trade 2 bricks for 1 resource!\n");
                    break;
                case 3:
                    printf("3.)Trade 2 lumber for 1 resource!\n");
                    break;
                case 4:
                    printf("4.)Trade 2 sheep for 1 resource!\n");
                    break;
                case 5:
                    printf("5.)Trade 2 grain for 1 resource!\n");
                    break;
                case 6:
                    printf("6.)Trade 2 ore for 1 resource!\n");
                    break;
                default:
                    break;
            }
        }
        if( i == 0 )// && on_any_port == 0 
        {
            printf("7.)You can trade any 4 resources with one resource!\n");
            break;
            //return;
        }
    }

    
    int32_t select_opt = 0;
    printf("Select a option.\n");
    scanf("%d",&select_opt);
    if( (select_opt > 7 || select_opt < 1) && tmp_marine_option[select_opt] != 0 )
    {
        printf("Invalid input!\n");
        goto marine_trade;
    }


    char *resource_name[5] = { "Brick" , "Grain" , "Sheep" , "Lumber" , "Ore" };
    int32_t select = 0;
    printf("Select a resource you wish to obtain.\n");
    printf("1.)Brick 2.)Lumber 3.)Sheep 4.)Grain 5.)Ore\n");
    scanf("%d",&select);
    //TODO input check

    switch (select_opt)
    {
        case 1:        
            printf("Select a resource you wish to give.\n");
            for( int32_t i = 1 ; i < 6 ; i++)
            {
                if( player->resource[i] >= 3)
                {
                    printf("%d.)%s ",i,resource_name[i-1]);
                }
            }
            //printf("1.)Brick 2.)Lumber 3.)Sheep 4.)Grain 5.)Ore\n");
            int32_t choose1;
            scanf("%d",&choose1);
            if( choose1 > 5 || choose1 < 1  )
            {
                printf("Invalid input!\n");
                // goto case 1;
            }
            player->resource[choose1] -= 3;
            player->resource[select] += 1;
            break;
        case 2:
            player->resource[Brick] -= 2;
            player->resource[select] += 1;
            break;
        case 3:
            player->resource[Lumber] -= 2;
            player->resource[select] += 1;
            break;
        case 4:
            player->resource[Sheep] -= 2;
            player->resource[select] += 1;
            break;
        case 5:
            player->resource[Grain] -= 2;
            player->resource[select] += 1;
            break;
        case 6:
            player->resource[Ore] -= 2;
            player->resource[select] += 1;
            break;
        case 7:
            case_7: 
           // int32_t resource_index[6] = { 0 };
            printf("Select a resource you wish to give.\n");
            for( int32_t i = 1 ; i < 6 ; i++)
            {
                if( player->resource[i] >= 4 )
                {
                    printf("%d.)%s ",i,resource_name[i-1]);
                    //resource_index[i] = 1;
                }
            }
            //printf("1.)Brick 2.)Grain 3.)Sheep 4.)Lumber 5.)Ore\n");
            int32_t choose2;
            scanf("%d",&choose2);
            if( choose2 > 5 || choose2 < 1 )//&& resource_index[choose2] != 0 
            {
                printf("Invalid input!\n");
                goto case_7;
            }
            player->resource[choose2] -= 4;
            player->resource[select] += 1;
            break;
    }

    return;
}

int32_t *if_settlement_on_port( Player player , node *pnode , int32_t ports[] )
{
    //printf("building index:{");
    for( int32_t i = 0 ; i < 54 ; i++ )
    {
    //printf("%d ",player.building_index[i]);
        if( player.building_index[i] )
        {
            if( i == 6 || i == 11 || i == 12 || i == 17 || i == 24 || i == 30 || i == 52 || i == 53 )
            {
                ports[normal_port] += 1;
            }
            if( i == 2 || i == 3 )//3,4 Brick
            {
                ports[brick_port] += 1;
            }
            if( i == 4 || i == 5 )//5,6 Wood
            {
                ports[wood_port] += 1;
            }
            if( i == 43 || i == 48 )//44,49 Sheep
            {
                ports[sheep_port] += 1;
            }   
            if( i == 29 || i == 35 )//30,36 Grain
            {
                ports[grain_port] += 1;
            }
            if( i == 46 || i == 51 )//47,52 Ore
            {
                ports[ore_port] += 1;
            }
        } 
    } 
    return &(ports[0]);
}


int32_t marine_trade_chk( Player *player , node *pnode , int32_t ports[] , int32_t **marine_option)
{
    int32_t* on_port = if_settlement_on_port( *player , pnode , ports );

    int32_t chk = 0;//check if on any port
    //printf("on port:");
    for( int32_t i = 6 ; i >= 0 ; i-- )
    {
    //printf("%d ",on_port[i]);
        if( on_port[i] )
        {
            chk++;
            if( i == 6 )
            {
                if( player->resource[Ore] >= 2 )
                {
                    (*marine_option)[Ore+1] = 1;
                    //printf("You can trade 2 ore for 1 resource!\n");
                }
            }
            if( i == 5 )
            {
                if( player->resource[Grain] >= 2 )
                {
                    (*marine_option)[Grain+1] = 1;
                    //printf("You can trade 2 grain for 1 resource!\n");
                }
            }
            if( i == 4 )
            {
                if( player->resource[Sheep] >= 2 )
                {
                    (*marine_option)[Sheep+1] = 1;
                    //printf("You can trade 2 sheep for 1 resource!\n");
                }
            }
            if( i == 3 )
            {
                if( player->resource[Lumber] >= 2 )
                {
                    (*marine_option)[Lumber+1] = 1;
                    //printf("You can trade 2 lumber for 1 resource!\n");
                }
            }
            if( i == 2 )
            {
                //printf("i = 2\n");
                if( player->resource[Brick] >= 2 )
                {
                    (*marine_option)[Brick+1] = 1;
                    //printf("You can trade 2 brick for 1 resource!\n");
                }
            }
            if( i == 1 )
            {
                //if any resource is >= 3
                if( player->resource[Brick] >= 3 || player->resource[Grain] >= 3 ||player->resource[Sheep] >= 3 || player->resource[Lumber] >= 3 || player->resource[Ore] >= 3)
                {
                    (*marine_option)[1] = 1;
                    //printf("You can trade 3 resource for 1 resource!\n");
                }
            }
            if( i == 0 )
            {
                //if any resource is >= 4
                if( player->resource[Brick] >= 4 || player->resource[Grain] >= 4 ||player->resource[Sheep] >= 4 || player->resource[Lumber] >= 4 || player->resource[Ore] >= 4)
                {
                    (*marine_option)[0] = 1;
                    //printf("You can trade 4 resource for 1 resource!\n");
                }
            }
        }
    }
    return 0;
}


int32_t chk_settlement_func( Player *player , road *proad , node *pnode)
{
    int32_t build_index[54] = {0}; 
     for( int32_t i = 0 ; i < 72 ; i++ )
    {
        node *tmp1 = (proad + i)->node1;
        node *tmp2 = (proad + i)->node2;
        if( (proad + i)->owner == player->index)
        {
        int32_t chk_3_dir = 1;//check if the 3 directioins has a building
        if( tmp1->dir1 != NULL )
        {
            if( tmp1->dir1->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp1->dir2 != NULL )
        {
            if( tmp1->dir2->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp1->dir3 != NULL )
        {
            if( tmp1->dir3->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }

        if( chk_3_dir > 0 )
        {
            build_index[(tmp1->index)-1] = 1;
        }

        chk_3_dir = 1;//check if the 3 directioins has a building
        if( tmp2->dir1 != NULL )
        {
            if( tmp2->dir1->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp2->dir2 != NULL )
        {
            if( tmp2->dir2->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp2->dir3 != NULL )
        {
            if( tmp2->dir3->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }

        if( chk_3_dir > 0 )
        {
            build_index[(tmp2->index)-1] = 1;
        }
        }
    }

    //if the node is already occupied, set the index to 0
    for( int32_t i = 0 ; i < 54 ; i++ )
    {
       
        if( (pnode + i)->owner != 0 )
        {
            build_index[i] = 0;
        }
    }

    for( int32_t i = 0 ; i < 54 ; i++ )
    {
         
        if( build_index[i] )
        {
            return 1;
        }
    }
    return 0;
}

int32_t chk_city_func( Player *player , node *pnode )
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t build_index[54] = {0};

    for( int32_t i = 0 ; i < 54 ; i++ )
    {
        if( (pnode + i)->owner == player->index && (pnode + i)->type == 1 )
        {
            build_index[i] = 1;
            return 1;
        }
    }
    return 0;
}

int32_t chk_road_func( Player *player , road *proad )
{
    int32_t road_index[72] = {0};

    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        road *road = proad + i;

        if( road->owner == 0 ) {
            if( road->dir1 != NULL )
            {
                if( road->dir1->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir2 != NULL )
            {
                if( road->dir2->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir3 != NULL )
            {
                if( road->dir3->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir4 != NULL )
            {
                if( road->dir4->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }

            if( road->node1->owner == player->index )
            {
                road_index[i] = 1;
            }
            if( road->node2->owner == player->index )
            {
                road_index[i] = 1;
            }
        }
    }
    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        if( road_index[i] )
        {
            return 1;
        }
    }
    return 0;
}

//play one development card each turn
int32_t is_able_to( Player *player , int32_t devUsage , card *pcard , road *proad , node *pnode , int32_t **tmp_marine_option , int32_t* option )
{
    int32_t ret = 0;

    //print the option 
    //printf("int32_t option[] = { ");
    // for( int32_t i = 0 ; i < 7 ; i++ )
    // {
    //     printf("%d ",option[i]);
    // }
    //printf("};\n");

    //reset the options 
    for( int32_t i = 0 ; i < 7 ; i++ )
    {
        option[i] = 0;
        
    }

    /*checks if the card pile is still available*/
    int32_t count = 0;
    for( int32_t i = 0 ; i < 25 ; i++ ) 
    {
        if( pcard[i].type == -1 ) {
            count++;
        }
    }
    if( count != 25 ) 
    {
        if( player->resource[Sheep] >= 1 && player->resource[Grain] >= 1 && player->resource[Ore] >= 1 )
        {
            option[buy_dev_card] = 1;
            //ret = 1;
            ret++;
        }
    }
    

    /*check if the dev card is usable in this round*/
    /*If the card the player holds has a timestamp that is not aquired this round, then we can use */
    if( player->dev_card_num >= 1 )
    {
        //printf("dev_card_num = %d\n",player->dev_card_num);
        for(int32_t i = 0 ; i < 25 ; i++ )
        {
            //printf("%d %d\n",player->dev_card[i].type,player->dev_card[i].timestamp);
            // if( pcard[i].timestamp != devUsage && pcard[i].type != -1)
            // {
            //     option[use_dev_card] = 1;
            //     ret++;
            // }
            if( player->dev_card[i].type != -1 && player->dev_card[i].timestamp != devUsage && player->dev_card[i].timestamp != 0 )
            {
                option[use_dev_card] = 1;
                ret++;
            }
        }
    }

    if( player->resource[Lumber] >= 1 && player->resource[Brick] >= 1 && player->resource[Sheep] >= 1 && player->resource[Grain] >= 1 )
    {
        option[trade_with_player] = 1;
        //ret = 1;
        ret++;
    }
    
    int32_t ports[7] = { 1, 0 , 0 , 0 , 0 , 0 , 0};//correpsonding to the port type, 1 is for no port
    int32_t *marine_option = malloc( sizeof(int32_t) * 7 );
    //set the marine option to 0
    for( int32_t i = 0 ; i < 7 ; i++ ) {
        marine_option[i] = 0;
    }

    marine_trade_chk( player , pnode , ports , &marine_option );
    //check if any trade is possible
    //printf("marine option :");
    for( int32_t i = 0 ; i < 7 ; i++ )
    {
        //printf("%d ",marine_option[i]);
        if( marine_option[i] != 0 )
        {
            option[marine_trade] = 1;
            //ret = 1;
            ret++;
        }
    }
    //printf("}\n");

    //int32_t *tmp_marine_option = malloc( sizeof(int32_t) * 7 );
    for( int32_t i = 0 ; i < 7 ; i++ )
    {
       (*tmp_marine_option)[i] = marine_option[i];
    }
    free(marine_option);
    

    if( player->resource[Lumber] >= 1 && player->resource[Brick] >= 1 && player->resource[Sheep] >= 1 && player->resource[Grain] >= 1 )
    {
        if (chk_settlement_func( player , proad , pnode ))
        {
            option[build_settlement] = 1;
            //ret = 1;
            ret++;
        }

    }

    if( player->resource[Lumber] >=1 && player->resource[Brick] >= 1 )
    {
        if( chk_road_func( player , proad ))
        {
            option[build_road] = 1;
            //ret = 1;
            ret++;
        }
       
    }

    if( player->resource[Grain] >= 2 && player->resource[Ore] >= 3 && player->settlement_num != 0 )
    {
        if( chk_city_func( player , pnode ))
        {
            option[build_city] = 1;
            //ret = 1;
            ret++;
        }
    }

    // printf("FIbal option :");
    //  for( int32_t i = 0 ; i < 7 ; i++ )
    // {
    //     printf("%d ",option[i]);
    // }
    // printf("}\n");


    if( ret == 0)
    {
        ret++;
       // printf("You have no option to do in this turn. Skipping.\n");
    }
    return ret;
}


void print_build( Player player )
{
    int32_t select = 0;
    printf("Select a place to build your settlement: \n");
    scanf("%d",&select);
    //check if the node is legal to build       
}

//check if any player has 1 wood, 1 brick, 1 sheep, 1 wheat
//offer mutiple times in the same turn if condition is met
void build_settlement_func( Player *player , road *proad , node *pnode)
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t build_index[54] = {0};

    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        node *tmp1 = (proad + i)->node1;
        node *tmp2 = (proad + i)->node2;

        if( (proad + i)->owner == player->index )
        {
        int32_t chk_3_dir = 1;//check if the 3 directioins has a building
        if( tmp1->dir1 != NULL )
        {
            if( tmp1->dir1->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp1->dir2 != NULL )
        {
            if( tmp1->dir2->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp1->dir3 != NULL )
        {
            if( tmp1->dir3->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }

        if( chk_3_dir > 0 )
        {
            build_index[(tmp1->index)-1] = 1;
        }

        chk_3_dir = 1;//check if the 3 directioins has a building
        if( tmp2->dir1 != NULL )
        {
            if( tmp2->dir1->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp2->dir2 != NULL )
        {
            if( tmp2->dir2->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp2->dir3 != NULL )
        {
            if( tmp2->dir3->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }

        if( chk_3_dir > 0)
        {
            build_index[(tmp2->index)-1] = 1;
        }
        }
    }

    //if the node is already occupied, set the index to 0
    for( int32_t i = 0 ; i < 54 ; i++ )
    {
        if( (pnode + i)->owner != 0 )
        {
            build_index[i] = 0;
        }
    }

    // for( int32_t i = 0 ; i < 54 ; i++ )
    // {
    //     if( build_index[i] != 0 )
    //     {
    //         printf("%d ",i+1);
    //     }
    // }
    // printf("\n");
    prtNode( player , proad , pnode , build_index );

    printf("Select a place to build your settlement:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 || build_index[select-1] == 0)
    {
        printf("Invalid input!\n");
        build_settlement_func( player , proad , pnode );
        return;
    }

    player->resource[Lumber] -= 1;
    player->resource[Brick] -= 1;
    player->resource[Sheep] -= 1;
    player->resource[Grain] -= 1;


    //record settlemnt build in player's attributes
    player->building_index[select-1] = 1;
    player->settlement_num += 1;

    //gain 1 victory point
    player->victory_point += 1;

    //Update node's attributes
    (pnode + (select - 1))->owner = player->index;
    (pnode + (select - 1))->type = 1;
}

//remember to minus settlement_num!!!
//check if any player has 2 wheat, 3 ore
void build_city_func( Player *player , node *pnode , road *proad )
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t build_index[54] = {0};

    for( int32_t i = 0 ; i < 54 ; i++ )
    {
        if( (pnode + i)->owner == player->index && (pnode + i)->type == 1 )
        {
            build_index[i] = 1;
        }
    }

    prtNode( player , proad , pnode , build_index);
    printf("Select a place to build your city:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 || build_index[select-1] == 0 )
    {
        printf("Invalid input!\n");
        build_city_func( player , pnode , proad );
        return;
    }

    player->resource[Grain] -= 2;
    player->resource[Ore] -= 3;

    //record settlemnt buidl in player's attributes
    player->building_index[select-1] = 2;
    pnode[select-1].type = 2;
    pnode[select-1].owner = player->index;

    //gain 2 victory point
    player->victory_point += 2;

    player->settlement_num -= 1; 

    return;
}

//check if any player has 1 wood, 1 brick
void build_road_func( Player *player , road *proad )
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t road_index[72] = {0};

    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        road *road = proad + i;

        if( road->owner == 0 ) {
            if( road->dir1 != NULL )
            {
                if( road->dir1->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir2 != NULL )
            {
                if( road->dir2->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir3 != NULL )
            {
                if( road->dir3->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir4 != NULL )
            {
                if( road->dir4->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }

            if( road->node1->owner == player->index )
            {
                road_index[i] = 1;
            }
            if( road->node2->owner == player->index )
            {
                road_index[i] = 1;
            }
        }
    }


    // for( int32_t i = 0 ; i < 72 ; i++ )
    // {
    //     if( road_index[i] != 0 )
    //     {
    //         printf("%d ",i+1);
    //     }
    // }

    prtRoad( player , proad , road_index );
    printf("Select a place to build your road:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 72 || select < 1 || road_index[select-1] == 0 )
    {
        printf("Invalid input!\n");
        build_road_func( player , proad );
        return;
    }

    player->resource[Lumber] -= 1;
    player->resource[Brick] -= 1;

    //record road build in player's attributes
    player->road_num += 1;
    (proad + (select-1))->owner = player->index;

    return;
}

void print_dev_card( int32_t i )
{
    //enum card_type{ Card_Empty = -1 , Card_Knight = 0 , Card_Victory_Point , Card_Road_Building , Card_Monopoly , Card_Year_of_Plenty };
    char *card_name[5] = {"Knight","Victory Point","Road Building","Monopoly","Year of Plenty"};
    printf("You have obtained a %s card\n",card_name[i]);
    return;
}

//check if dev is obtained in the same turn
void buy_dev_card_func( Player *player , card *pcard , int32_t timestamp  )
{
    player->resource[Sheep] -= 1;
    player->resource[Grain] -= 1;
    player->resource[Ore] -= 1;
    //add card to player's hand
    // for(int32_t i = 0 ; i < 25 ; i++)
    // {
    //     if( card[i] != -1 )
    //     {
    //         //printf("You have obtained a %s card!\n",card_name[card[i]])
    //         print_dev_card( card[i] );
    //         player->dev_card[card[i]] += 1; 
    //         player->dev_card_num += 1;
    //         card[i] = -1;
    //         break;
    //     }
    // }

    for( int32_t i = 0 ; i < 25 ; i++ )
    {
        if( pcard[i].type != Card_Empty )
        {
            print_dev_card( pcard[i].type );
            //player->dev_card[pcard[i].type] += 1; 
            //update player's dev card
            for( int32_t j = 0 ; j < 25 ; j++ )
            {
                if( player->dev_card[j].type == Card_Empty )
                {
                    player->dev_card[j].type = pcard[i].type;
                    player->dev_card[j].timestamp = timestamp;
                    // printf("timestamp : %d\n",timestamp);
                    // printf("player->dev_card[i].type = %d\n",player->dev_card[j].type);
                    // printf("hi");
                    break;
                }
            }
            player->dev_card_type_num[pcard[i].type] += 1;
            player->dev_card_num += 1;

            //update card pile
            pcard[i].type = Card_Empty;
            pcard[i].timestamp = timestamp;
            break;
        }
    }
    
    //turn off the option //player is able to buy mutliple cards if condition is met
    //option[buy_dev_card] = 0; 
}

void moveRobber( tile *ptile , Player *player1 , Player **player_start )//player is the one who moves the robber, player_start is for the reference of all players
{
    //player with more than 7 cards will lose half of the cards
    for( int32_t i = 0 ; i < 4 ; i++ )
    {
        int32_t sum = 0;
        for( int32_t j = 1 ; j < 5 ; j++ )
        {
            sum += player_start[i]->resource[j];
        }
        
        if( sum > 7 )
        {
            printf("Player%d have a total of %d resources, so player%d will be taken %1.f resources\n",player_start[i]->index,sum , player_start[i]->index , (floor(sum / 2)));
            int32_t cnt = floor(sum / 2);
            for( int32_t j = 0 ; j < cnt ; j++ )
            {
                int32_t index = rand() % 5 + 1;
                if( player_start[i]->resource[index] != 0 )
                {
                    player_start[i]->resource[index] -= 1;
                }
                else
                {
                    j--;
                }
            }

        }
    }
    prtTile();
    moverobber:
    printf("Select a tile to place the robber:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 19 || select < 1 || (ptile + (select - 1))->robber == 1 )
    {
        printf("Invalid input!\n");
        //moveRobber( ptile , player1 , player_start );
        goto moverobber;
    }

    //set the robber to a new tile, clear the old one
    for( int32_t i = 0 ; i < 19 ; i++ )
    {
        if( (ptile + i)->robber == 1 )
        {
            (ptile + i)->robber = 0;
            break;
        }
    }
    
    (ptile + (select - 1))->robber = 1;

   
    //steal a resource from a player if there are any
    int32_t steal_index[6] = {0};

    for( int32_t i = 0 ; i < 6 ; i++ )
    {
        steal_index[i] = (ptile + (select - 1))->nodes[i]->owner ;
    }

    int32_t cnt = 0;
    for( int32_t i = 0 ; i < 6 ; i++ )
    {
        if( steal_index[i] != 0 && (steal_index[i])!= player1->index )
        {
            cnt++;
        }
    }

    if( cnt == 0 )
    {
        return;
    }
    else
    {
        int32_t able_to_steal = 0;
        for( int32_t i = 0 ; i < 6 ; i++ )
        {
            if( steal_index[i] != 0 && steal_index[i] != player1->index )
            {
                able_to_steal = 1;
            }
        }

        if( able_to_steal )
        {
            steal : 
            printf("Select a player to steal from:(enter 1-6)\n");
            for( int32_t i = 0 ; i < 6 ; i++ )
            {
                if( steal_index[i] != 0 && steal_index[i] != player1->index )
                {
                    printf("Player %d\n",steal_index[i]);
                }
            }

            select = 0;
            printf("Playes's index :");
            scanf("%d",&select);
            if( select > 4 || select < 1  )
            {
                printf("Invalid input!\n");
                goto steal;
            }

            //steal a random resource from the player
            int32_t random_num = rand() % 5 + 1;
            int32_t steal_resource = 0;
            for(int32_t i = 0 ; i < 5 ; i++ )
            {
                if( player_start[select-1]->resource[(random_num + i)%5+1] == 0 )
                {
                    continue;
                }
                else
                {
                    steal_resource = (random_num + i)%5+1;
                    break;
                }
            }
            // while( player_start[select-1]->resource[steal_resource] == 0 )
            // {
            //     steal_resource = rand() % 5 + 1;
            // }

            //show the resource stolen
            char* resource_string[5] = { "Brick" , "Grain" , "Sheep" , "Lumber" , "Ore" };
            printf("You have stolen 1 %s from player %d\n",resource_string[steal_resource-1],select);

            player_start[select-1]->resource[steal_resource] -= 1;
            player1->resource[steal_resource] += 1;
        }
    }
    return;
}

void devBuildRoad( Player *player , road *proad )//not done!
{
    int32_t road_index[72] = {0};

    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        road *road = proad + i;

        if( road->owner == 0 ) {
            //check if the road is connected to other roads of the player
            if( road->dir1 != NULL )
            {
                if( road->dir1->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir2 != NULL )
            {
                if( road->dir2->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir3 != NULL )
            {
                if( road->dir3->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir4 != NULL )
            {
                if( road->dir4->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }

            //check if the road is connected to other nodes of the player
            if( road->node1->owner == player->index )
            {
                road_index[i] = 1;
            }
            if( road->node2->owner == player->index )
            {
                road_index[i] = 1;
            }
        }
    }
      //print the road that is available
    // for( int32_t i = 0 ; i < 72 ; i++ )
    // {
    //     if( road_index[i] != 0 )
    //     {
    //         printf("%d ",i+1);
    //     }
    // }
    prtRoad( player, proad , road_index);

    dev_build : printf("Select a place to build your road:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 72 || select < 1 || road_index[select-1] == 0 )
    {
        printf("Invalid input!\n");
        goto dev_build ;
    }

    //record road build in player's attributes
    player->road_num += 1;

    //Update node's attributes
    (proad + (select-1))->owner = player->index;
    


    return;
}

void Monopoly( Player *monopoler , Player *p1, Player *p2 , Player *p3 )
{
    
    printf("Select a resource to monopolize:\n");
    printf("1. Brick\n");
    printf("2. Grain\n");
    printf("3. Sheep\n");
    printf("4. Lumber\n");
    printf("5. Ore\n");
    
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 5 || select < 1 )
    {
        printf("Invalid input!\n");
        Monopoly( monopoler , p1 , p2 , p3 );
    }
    //select -= 1;

    //show how many resources the player has monopolized from other players
    char* resource_string[5] = { "Brick" , "Grain" , "Sheep" , "Lumber" , "Ore" };
    printf("You have monopolized %d %s from player %d\n",p1->resource[select],resource_string[select-1],p1->index);
    printf("You have monopolized %d %s from player %d\n",p2->resource[select],resource_string[select-1],p2->index);
    printf("You have monopolized %d %s from player %d\n",p3->resource[select],resource_string[select-1],p3->index);

    int32_t total = p1->resource[select] + p2->resource[select] + p3->resource[select];
    monopoler->resource[select] += total;

    p1->resource[select] = 0;
    p2->resource[select] = 0;
    p3->resource[select] = 0;

    return;
}

//take two resources from the bank
void Year_of_Plenty( Player *player  )
{
    printf("Select a resource to take:\n");
    printf("1. Brick\n");
    printf("2. Grain\n");
    printf("3. Sheep\n");
    printf("4. Lumber\n");
    printf("5. Ore\n");

    int32_t select1 = 0;
    scanf("%d",&select1);
    if( select1 > 5 || select1 < 1 )
    {
        printf("Invalid input!\n");
        Year_of_Plenty( player );
    }
   // select1 -= 1;

    printf("Select another resource to take:\n");
    printf("1. Brick\n");
    printf("2. Grain\n");
    printf("3. Sheep\n");
    printf("4. Lumber\n");
    printf("5. Ore\n");

    int32_t select2 = 0;
    scanf("%d",&select2);
    if( select2 > 5 || select2 < 1 )
    {
        printf("Invalid input!\n");
        Year_of_Plenty( player );
    }
   // select2 -= 1;

    player->resource[select1] += 1;
    player->resource[select2] += 1;

    return;
}


void use_dev_card_func( Player *player , Player *p1 , Player *p2 , Player *p3 , road *proad , node* pnode, tile *ptile , Player **player_start )
{
    show_dev:
    for( int32_t i = 0 ; i < 5 ; i++ )
    {
        if( player->dev_card_type_num[i] )
        {
            switch(i)
            {
                case Card_Knight:
                    printf("0)You have %d Knight cards, you can move the robber and steal resources from a player\n",player->dev_card_type_num[i]);
                    break;
                case Card_Victory_Point:
                    printf("1)You have %d Victory Point cards, you can get 2 victory points\n",player->dev_card_type_num[i]);
                    break;
                case Card_Road_Building:
                    printf("2)You have %d Road Building cards, you can build 2 roads\n",player->dev_card_type_num[i]);
                    break;
                case Card_Monopoly:
                    printf("3)You have %d Monopoly cards, you can monopolize a resource\n",player->dev_card_type_num[i]);
                    break;
                case Card_Year_of_Plenty:
                    printf("4)You have %d Year of Plenty cards, you can take 2 resources from the bank\n",player->dev_card_type_num[i]);
                    break;
            }
        }
    }

    printf("Select a card to use:\n");
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 4 || select < 0 || player->dev_card_type_num[select] == 0 )
    {
        printf("Invalid input!\n");
        goto show_dev;
    }

    switch(select)
    {
        case 0:
            if( player->dev_card_type_num[Card_Knight] )
            {
                player->dev_card_num--;
                player->knight_num++;
                player->dev_card_type_num[Card_Knight]--;
                for( int32_t i = 0 ; i < 25 ; i++ )
                {
                    if( player->dev_card[i].type == Card_Knight ) {
                        player->dev_card[i].type = Card_Empty;
                        player->dev_card[i].timestamp = 0;
                        break;
                    }       
                }
                //TODO
                //move the robber
                //steal a resource from a player
                moveRobber( ptile , player , player_start );//not done!1!!
            }
            break;
        case 1:
            if( player->dev_card_type_num[Card_Victory_Point] )
            {
                player->dev_card_num--;
                player->dev_card_type_num[Card_Victory_Point]--;
                for( int32_t i = 0 ; i < 25 ; i++ )
                {
                    if( player->dev_card[i].type == Card_Victory_Point ) {
                        player->dev_card[i].type = Card_Empty;
                        player->dev_card[i].timestamp = 0;
                        break;
                    }       
                }
                player->victory_point += 2;
            }
            break;
        case 2:
            if( player->dev_card_type_num[Card_Road_Building] )
            {
                player->dev_card_num--;
                player->dev_card_type_num[Card_Road_Building]--;
                for( int32_t i = 0 ; i < 25 ; i++ )
                {
                    if( player->dev_card[i].type == Card_Road_Building ) {
                        player->dev_card[i].type = Card_Empty;
                        player->dev_card[i].timestamp = 0;
                        break;
                    }       
                }
                //TODO
                //build 2 roads
                devBuildRoad( player , proad );
                print_board( ptile , pnode , proad, player);
                devBuildRoad( player , proad );
            }
            break;
        case 3:
            if( player->dev_card_type_num[Card_Monopoly] )
            {
                player->dev_card_num--;
                player->dev_card_type_num[Card_Monopoly]--;
                for( int32_t i = 0 ; i < 25 ; i++ )
                {
                    if( player->dev_card[i].type == Card_Monopoly ) {
                        player->dev_card[i].type = Card_Empty;
                        player->dev_card[i].timestamp = 0;
                        break;
                    }       
                }
                //TODO
                //choose a resource and take all of that resource from all players
                Monopoly( player , p1 , p2 , p3 );
            }
            break;
        case 4:
            if( player->dev_card_type_num[Card_Year_of_Plenty] )
            {
                player->dev_card_num--;
                player->dev_card_type_num[Card_Year_of_Plenty]--;
                for( int32_t i = 0 ; i < 25 ; i++ )
                {
                    if( player->dev_card[i].type == Card_Year_of_Plenty ) {
                        player->dev_card[i].type = Card_Empty;
                        player->dev_card[i].timestamp = 0;
                        break;
                    }       
                }
                //TODO
                //take two resources from the bank
                Year_of_Plenty( player );
            }
            break;
    }
    return;
}
// void use_dev_card_func( Player *player , Player *p1 , Player *p2 , Player *p3 , road *proad , tile *ptile , Player *player_start )
// {
//     show_dev :
//     if( player->dev_card_num != 0 )
//     {
//         //check which dev card the player has, and show the player what he can do
//         for( int32_t i = 0 ; i < 5 ; i++)
//         {
//             if( player->dev_card[i] )
//             {
//                 switch(i)
//                 {
//                     case Card_Knight:
//                         printf("0)You have %d Knight cards, you can move the robber and steal a resource from a player\n",player->dev_card[i]);
//                         break;
//                     case Card_Victory_Point:
//                         printf("1)You have %d Victory Point cards, you can get 2 victory points\n",player->dev_card[i]);
//                         break;
//                     case Card_Road_Building:
//                         printf("2)You have %d Road Building cards, you can build 2 roads\n",player->dev_card[i]);
//                         break;
//                     case Card_Monopoly:
//                         printf("3)You have %d Monopoly cards, you can monopolize a resource\n",player->dev_card[i]);
//                         break;
//                     case Card_Year_of_Plenty:
//                         printf("4)You have %d Year of Plenty cards, you can take 2 resources from the bank\n",player->dev_card[i]);
//                         break;
//                 }
//             }
//         }

//         printf("Select a card to use:\n");
//         int32_t select = 0;
//         scanf("%d",&select);
//         if( select > 4 || select < 0 || player->dev_card[select] == 0 )
//         {
//             printf("Invalid input!\n");
//             goto show_dev;
//         }

//         switch(select)
//         {
//             case 0:
//                 if( player->dev_card[Card_Knight] )
//                 {
//                     player->dev_card[Card_Knight]--;
//                     //TODO
//                     //move the robber
//                     //steal a resource from a player
//                     moveRobber( ptile , player , player_start );//not done!1!!
//                 }
//                 break;
//             case 1:
//                 if( player->dev_card[Card_Victory_Point] )
//                 {
//                     player->dev_card[Card_Victory_Point]--;
//                     player->victory_point += 2;
//                 }
//                 break;
//             case 2:
//                 if( player->dev_card[Card_Road_Building] )
//                 {
//                     player->dev_card[Card_Road_Building]--;
//                     //TODO
//                     //build 2 roads
//                     devBuildRoad( player , proad );
//                 }
//                 break;
//             case 3:
//                 if( player->dev_card[Card_Monopoly] )
//                 {
//                     player->dev_card[Card_Monopoly]--;
//                     //TODO
//                     //choose a resource and take all of that resource from all players
//                     Monopoly( player , p1 , p2 , p3 );
//                 }
//                 break;
//             case 4:
//                 if( player->dev_card[Card_Year_of_Plenty] )
//                 {
//                     player->dev_card[Card_Year_of_Plenty]--;
//                     //TODO
//                     //take two resources from the bank
//                     Year_of_Plenty( player );
//                 }
//                 break;
//         }
//     }
   
// }

void SetupBuildRoad( Player *player , road *proad )
{
    int32_t road_index[72] = {0};

    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        road *road = proad + i;

        if( road->owner == 0 ) {
            if( road->dir1 != NULL )
            {
                if( road->dir1->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir2 != NULL )
            {
                if( road->dir2->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir3 != NULL )
            {
                if( road->dir3->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }
            if( road->dir4 != NULL )
            {
                if( road->dir4->owner == player->index )
                {
                    road_index[i] = 1;
                }
            }

            if( road->node1->owner == player->index )
            {
                printf("node1\n");
                road_index[i] = 1;
            }
            if( road->node2->owner == player->index )
            {
                printf("node2\n");
                road_index[i] = 1;
            }
        }
    }

    //print the road that is available
    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        if( road_index[i] != 0 )
        {
            printf("%d ",i+1);
        }
    }

    prtRoad( player, proad , road_index );
    build : printf("Select a place to build your road:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 72 || select < 1 || road_index[select-1] == 0 )
    {
        printf("Invalid input!\n");
        goto build ;
        //devBuildRoad( player , proad );
    }

    //record road build in player's attributes
    player->road_num += 1;

    //Update node's attributes
    (proad + (select-1))->owner = player->index;
    

    return;
}

int32_t SetupBuildSettlement( Player *player , road *proad , node *pnode )
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t build_index[54] = {0};

    //printf("index =  %d",proad->index);
    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        node *tmp1 = (proad + i)->node1;
        node *tmp2 = (proad + i)->node2;

        int32_t chk_3_dir = 1;//check if the 3 directioins has a building
        if( tmp1->dir1 != NULL )
        {
            if( tmp1->dir1->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp1->dir2 != NULL )
        {
            if( tmp1->dir2->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp1->dir3 != NULL )
        {
            if( tmp1->dir3->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }

        if( chk_3_dir > 0 )
        {
            build_index[(tmp1->index)-1] = 1;
        }

        chk_3_dir = 1;//check if the 3 directioins has a building
        if( tmp2->dir1 != NULL )
        {
            if( tmp2->dir1->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp2->dir2 != NULL )
        {
            if( tmp2->dir2->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }
        if( tmp2->dir3 != NULL )
        {
            if( tmp2->dir3->owner != 0 )
            {
                chk_3_dir -= 1;
            }
        }

        if( chk_3_dir > 0 )
        {
            build_index[(tmp2->index)-1] = 1;
        }

    }


    //if the node is already occupied, set the index to 0
    for( int32_t i = 0 ; i < 54 ; i++ )
    {
        if( (pnode + i)->owner != 0 )
        {
            build_index[i] = 0;
        }
    }


    // for( int32_t i = 0 ; i < 54 ; i++ )
    // {
    //     if( build_index[i] != 0 )
    //     {
    //         printf("%d ",i+1);
    //     }
    // }
    // printf("\n");
   
    
    prtNode( player , proad , pnode , build_index );

   
    build_set :    
    printf("Select a place to build your settlement:\n");
     int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 || build_index[select-1] == 0)
    {
        printf("Invalid input!\n");
        goto build_set;
        //SetupBuildSettlement( player , proad , pnode);
    }
    /*TODO*/

    //record settlemnt build in player's attributes
    player->building_index[select-1] = 1;
    player->settlement_num += 1;
    player->victory_point += 1;

    //Update node's attributes
    (pnode + (select - 1))->owner = player->index;
    (pnode + (select - 1))->type = 1;

    return select;//0-54

}

//given the index of the settlement builded, allocate resources from tiles
void SetupObtainResource( int32_t index , Player *player ,  node *pnode  )
{
    int32_t t1 = 0 , t2 = 0 , t3 = 0;
    t1 = (pnode + (index - 1))->tile1;
    t2 = (pnode + (index - 1))->tile2;
    t3 = (pnode + (index - 1))->tile3;
    if( t1 != 6 )//dessert
    {
        player->resource[(t1)] += 1;
    }
    if( t2 != 6 )
    {
        player->resource[(t2)] += 1;
    }
    if( t3 != 6 )
    {
        player->resource[(t3)] += 1;
    }
}

//print the resource of the player
void print_player_resource( Player *player )
{
    printf("Player %d's resource:\n",player->index);
    printf("Brick: %d\n",player->resource[Brick]);
    printf("Grain: %d\n",player->resource[Grain]);
    printf("Lumber: %d\n",player->resource[Lumber]);
    printf("Ore: %d\n",player->resource[Ore]);
    printf("Sheep: %d\n",player->resource[Sheep]);
    return;
}


int main ()
{
     srand( time(NULL) );
/*init*/
    Player *player[4];
    for(int32_t i = 0 ; i < 4 ; i++ )
    {
        player[i] = (Player*)calloc(sizeof(Player),1);
        player[i]->index = i+1;
        //init card in player to empty and set time stamp to 0
        for( int32_t j = 0 ; j < 25 ; j++ )
        {
            player[i]->dev_card[j].type = -1;
            player[i]->dev_card[j].timestamp = 0;
        }   
    }

    card *pCard = calloc(25,sizeof(card));
    pCard = init_card(pCard);

    node *pNode = calloc(54,sizeof(node));
    pNode = init_node(pNode);
 
    road *pRoad = calloc( 72 , sizeof(road) );
    pRoad = init_road(pRoad , pNode);

    tile *pTile = calloc(19,sizeof(tile));
    pTile = init_tile(pTile , pNode);


    for( int32_t i = 0 ; i < 4 ; i++ )
    {
         player[i]->resource[Brick] = 3;
        player[i]->resource[Grain] = 3;
        player[i]->resource[Sheep] = 3;
        player[i]->resource[Lumber] = 3;
        player[i]->resource[Ore] = 3;
    }

    // player[0]->resource[Brick] = 5;
    // player[0]->resource[Grain] = 5;
    // player[0]->resource[Sheep] = 5;
    // player[0]->resource[Lumber] = 5;
    // player[0]->resource[Ore] = 5;
    // player[0]->largest_army = 1;
    // print_board( pTile, pNode, pRoad , player[0] );


    // player[1]->resource[Brick] = 5;
    // player[1]->resource[Grain] = 5;
    // player[1]->resource[Sheep] = 5;
    // player[1]->resource[Lumber] = 5;
    // player[1]->resource[Ore] = 5;

    int32_t settlement_index = 0;
/*init*/

/*-------------------------Setup Phase--------------------------------*/
    SetupBuildSettlement( player[0] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupBuildRoad( player[0] , pRoad );
    print_board( pTile, pNode, pRoad , player[0]);

    SetupBuildSettlement( player[1] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupBuildRoad( player[1] , pRoad );
    print_board( pTile, pNode, pRoad , player[0]);

    SetupBuildSettlement( player[2] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupBuildRoad( player[2] , pRoad );
    print_board( pTile, pNode, pRoad , player[0]);


    SetupBuildSettlement( player[3] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupBuildRoad( player[3] , pRoad );
    print_board( pTile, pNode, pRoad , player[0]);

    settlement_index = SetupBuildSettlement( player[3] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupObtainResource( settlement_index , player[3] , pNode );
    SetupBuildRoad( player[3] , pRoad );
    print_board( pTile, pNode, pRoad , player[0]);

    settlement_index = SetupBuildSettlement( player[2] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupObtainResource( settlement_index , player[2] , pNode );
    SetupBuildRoad( player[2] , pRoad );
    print_board( pTile, pNode, pRoad , player[0]);

    settlement_index = SetupBuildSettlement( player[1] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupObtainResource( settlement_index , player[1] , pNode );
    SetupBuildRoad( player[1] , pRoad );
    print_board( pTile, pNode, pRoad , player[0]);

    settlement_index = SetupBuildSettlement( player[0] , pRoad , pNode );
    print_board( pTile, pNode, pRoad , player[0]);
    SetupObtainResource( settlement_index , player[0] , pNode );
    SetupBuildRoad( player[0] , pRoad );
     print_board( pTile, pNode, pRoad , player[0]);

/*-------------------------Setup Phase--------------------------------*/

/*test*/
    // int32_t turn = 1;//player 1's turn
    //             int32_t *tmp_marine_option = malloc( sizeof( int32_t ) * 7 );
    //             int32_t quit = 1 , devUsage = 0;
    //             while( is_able_to( player[0] , devUsage , pRoad , pNode, &tmp_marine_option ) && quit )
    //             {
    //                 int32_t c = print_option_menu( option , 8 );
    //                 int32_t choice = 0;
                    
    //                 //this is a terrible design but bear with me :(
    //                 //offers the choice
    //                 for( int32_t i = 0 ; i < 8 ; i++ )
    //                 {   
    //                     if( option[i] == 1 )
    //                     {
    //                         choice++;
    //                     }
    //                     if( choice == c )
    //                     {
    //                         choice = i + 1;
    //                         break;
    //                     }
    //                 }
    //                 switch( choice )
    //                 {
    //                     case 1: 
    //                         buy_dev_card_func( player[0] );
    //                         break;
    //                     case 2:
    //                         use_dev_card_func( player[0] , player[1] , player[2] , player[3] , pRoad , pTile , player[0] );
    //                         print_board( pTile, pNode, pRoad);
    //                         devUsage++;
    //                         break;
    //                     case 3:
    //                         //trade_with_player( player[0] );
    //                         break;
    //                     case 4:
    //                          marine_trade_func( player[0] , tmp_marine_option);
    //                         break;
    //                     case 5:
    //                         build_settlement_func( player[0] , pRoad , pNode );
    //                         print_board( pTile, pNode, pRoad );
    //                         break;
    //                     case 6:
    //                         build_road_func( player[0]  , pRoad );
    //                         print_board( pTile, pNode, pRoad );
    //                         break;
    //                     case 7:
    //                         build_city_func( player[0] , pNode , pRoad );
    //                         print_board( pTile, pNode, pRoad );
    //                         break;
    //                     case 8:
    //                         quit = 0;
    //                         break;
    //                     default:
    //                         break;
    //                 }
    //                 is_game_over( player );//check if any player has 10 points
                    
    //             }
    //             free( tmp_marine_option);
/*test*/
    int32_t turn = 4;
    
    while( 1 ) 
    {
        int32_t option[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1};
        int32_t *tmp_marine_option = malloc( sizeof( int32_t ) * 7 );
        int32_t quit = 1;
        int32_t devUsage = 0;
        int32_t dice_val = 0;
        printf("===============\n");
        switch( turn % 4 + 1)
        {
            case 1:
                print_board( pTile, pNode, pRoad , player[0] );
                printf( "Player 1's turn\n" );
                dice_val = roll_dice( player[0] );
                if( dice_val == 7 ) {
                    //printf("Player 1 rolled a 7\n");
                    moveRobber( pTile , player[0] , player);
                    print_board( pTile, pNode, pRoad , player[0] );
                } 
                obtain_resources( dice_val , player[0] , pTile );
                quit = 0;
                devUsage = 1;//1 means dev card can be used
                int32_t num = 0;
                while( is_able_to( player[0] , turn , pCard , pRoad , pNode ,  &tmp_marine_option , option ) && !quit )
                {
                    int32_t c = print_option_menu( option , num );
                    int32_t choice = 0;

                    //offers the choice
                    for( int32_t i = 0 ; i < 8 ; i++ )
                    {   
                        if( option[i] == 1 )
                        {
                            choice++;
                        }
                        if( choice == c )
                        {
                            choice = i + 1;
                            //printf("choice = %d\n", choice);
                            break;
                        }
                    }
                    // for( int32_t i = 0 ; i < 8 ; i++ )
                    // {
                    //     printf("option[%d] = %d\n", i , option[i]);
                    // }
                    // printf("choice = %d\n", choice);
                    switch( choice )
                    {
                        case 1: 
                            print_board( pTile, pNode, pRoad , player[0]);
                            buy_dev_card_func( player[0] , pCard , turn );         
                            print_board( pTile, pNode, pRoad , player[0]);
                            break;
                        case 2:
                            use_dev_card_func( player[0] , player[1] , player[2] , player[3] , pRoad , pNode, pTile , player );
                            print_board( pTile, pNode, pRoad, player[0]);
                            devUsage++;//update turn
                            break;
                        case 3:
                            //trade_with_player( player[0] );
                            break;
                        case 4:
                            marine_trade_func( player[0] , tmp_marine_option);
                            print_board( pTile, pNode, pRoad, player[0]);
                            break;
                        case 5:
                            build_settlement_func( player[0] , pRoad , pNode );
                            print_board( pTile, pNode, pRoad , player[0]);
                            break;
                        case 6:
                            build_road_func( player[0]  , pRoad );
                            print_board( pTile, pNode, pRoad, player[0] );
                            break;
                        case 7:
                            build_city_func( player[0] , pNode , pRoad );
                            print_board( pTile, pNode, pRoad , player[0]);
                            break;
                        case 8:
                            quit = 1;
                            break;
                        default:
                            break;
                    }
                    largest_army( player , pRoad );
                    if(is_game_over( player ))//check if any player has 10 points
                    {
                        goto game_over;
                    }
                    //printf("quit: %d\n", quit);
                }               
                free( tmp_marine_option);     
                break;
            case 2: 
                print_board( pTile, pNode, pRoad , player[1] );
                ai_turn( player , pTile , pNode , pRoad ,  2 );
                print_board( pTile, pNode, pRoad , player[1] );
                largest_army( player , pRoad );
                if(is_game_over( player ))
                {
                    goto game_over;
                }
                break;
            case 3:
                print_board( pTile, pNode, pRoad , player[2] );
                ai_turn( player , pTile , pNode , pRoad ,  3 );
                print_board( pTile, pNode, pRoad , player[2] );
                largest_army( player , pRoad );
                if(is_game_over( player ))
                {
                    goto game_over;
                }
                break;
            case 4:
                print_board( pTile, pNode, pRoad , player[3] );
                ai_turn( player , pTile , pNode , pRoad ,  4 );
                print_board( pTile, pNode, pRoad , player[3] );
                largest_army( player , pRoad );
                if(is_game_over( player ))
                {
                    goto game_over;
                }
                break;
            
            // case 2:
            //     print_board( pTile, pNode, pRoad , player[1] );
            //     printf( "Player 2's turn\n" );
            //     quit = 0;
            //     devUsage = 1;//1 means dev card can be used
            //     dice_val = roll_dice( player[1]);
            //     if( dice_val == 7 ) {
            //        // printf("Player 2 rolled a 7\n");
            //         moveRobber( pTile , player[1] , player);
            //         print_board( pTile, pNode, pRoad , player[1] );
            //     }
            //         obtain_resources( dice_val , player[0] , pTile );
            //         //print_player_resource(player[1]);
            //         while( is_able_to( player[1] , turn , pCard ,pRoad , pNode ,  &tmp_marine_option , option) && !quit )
            //         {
            //             int32_t c = print_option_menu( option , 8 );
            //             int32_t choice = 0;
                        
            //             //this is a terrible design but bear with me :(
            //             //offers the choice
            //             for( int32_t i = 0 ; i < 8 ; i++ )
            //             {   
            //                 if( option[i] == 1 )
            //                 {
            //                     choice++;
            //                 }
            //                 if( choice == c )
            //                 {
            //                     choice = i + 1;
            //                     //printf("choice = %d\n", choice);
            //                     break;
            //                 }
            //             }
            //             switch( choice )
            //             {
            //                 case 1: 
            //                     print_board( pTile, pNode, pRoad , player[1]);
            //                     buy_dev_card_func( player[1] , pCard , turn);
            //                     print_board( pTile, pNode, pRoad , player[1]);
            //                     break;
            //                 case 2:
            //                     use_dev_card_func( player[1] , player[0] , player[2] , player[3] , pRoad ,pNode, pTile , player );
            //                     print_board( pTile, pNode, pRoad , player[1]);
            //                     devUsage++;//update turn
            //                     break;
            //                 case 3:
            //                     //trade_with_player( player[0] );
            //                     break;
            //                 case 4:
            //                     marine_trade_func( player[1] , tmp_marine_option);
            //                     break;
            //                 case 5:
            //                     build_settlement_func( player[1] , pRoad , pNode );
            //                     print_board( pTile, pNode, pRoad , player[1]);
            //                     break;
            //                 case 6:
            //                     build_road_func( player[1]  , pRoad );
            //                     print_board( pTile, pNode, pRoad , player[1]);
            //                     break;
            //                 case 7:
            //                     build_city_func( player[1] , pNode , pRoad );
            //                     print_board( pTile, pNode, pRoad, player[1]);
            //                     break;
            //                 case 8:
            //                     quit = 1;
            //                     break;
            //                 default:
            //                     break;
            //             }
            //             largest_army( player , pRoad );
            //             if(is_game_over( player ))//check if any player has 10 points
            //             {
            //                 goto game_over;
            //             }
            //         }
            //     free( tmp_marine_option);
                
            //     break;
            // case 3:
            //     print_board( pTile, pNode, pRoad , player[2] );
            //     printf( "Player 3's turn\n" );
            //     quit = 0;
            //     devUsage = 1;//1 means dev card can be used
            //     dice_val = roll_dice( player[2] );
            //     obtain_resources( dice_val , player[0] , pTile );
            //     while( is_able_to( player[2] , turn  , pCard, pRoad , pNode ,  &tmp_marine_option , option )&& !quit )
            //     {
            //         int32_t c = print_option_menu( option , 8 );
            //         int32_t choice = 0;
                    
            //         //this is a terrible design but bear with me :(
            //         //offers the choice
            //         for( int32_t i = 0 ; i < 8 ; i++ )
            //         {   
            //             if( option[i] == 1 )
            //             {
            //                 choice++;
            //             }
            //             if( choice == c )
            //             {
            //                 choice = i + 1;
            //                 break;
            //             }
            //         }
            //         switch( choice )
            //         {
            //             case 1: 
            //                 print_board( pTile, pNode, pRoad , player[2]);
            //                 buy_dev_card_func( player[2] , pCard , turn );
            //                 print_board( pTile, pNode, pRoad , player[2]);
            //                 break;
            //             case 2:
            //                 use_dev_card_func( player[2] , player[0] , player[1] , player[3] , pRoad , pNode ,pTile , player );
            //                 print_board( pTile, pNode, pRoad, player[2]);
            //                 devUsage++;//update turn
            //                 break;
            //             case 3:
            //                 //trade_with_player( player[0] );
            //                 break;
            //             case 4:
            //                 marine_trade_func( player[2] , tmp_marine_option);
            //                 break;
            //             case 5:
            //                 build_settlement_func( player[2] , pRoad , pNode );
            //                 print_board( pTile, pNode, pRoad, player[2] );
            //                 break;
            //             case 6:
            //                 build_road_func( player[2]  , pRoad );
            //                 print_board( pTile, pNode, pRoad ,player[2]);
            //                 break;
            //             case 7:
            //                 build_city_func( player[2] , pNode , pRoad );
            //                 print_board( pTile, pNode, pRoad, player[2] );
            //                 break;
            //             case 8:
            //                 quit = 1;
            //                 break;
            //             default:
            //                 break;
            //         }
            //         largest_army( player , pRoad);
            //         if(is_game_over( player ))//check if any player has 10 points
            //         {
            //             goto game_over;
            //         }
            //     }
            //     free( tmp_marine_option);
            //     break;
            // case 4:
            //     print_board( pTile, pNode, pRoad , player[3] );
            //     printf( "Player 4's turn\n" );
            //     quit = 0;
            //     devUsage = 1;//1 means dev card can be used
            //     dice_val = roll_dice( player[3]);
            //     obtain_resources( dice_val , player[0] , pTile );
            //     print_player_resource( player[3] );
            //     while( is_able_to( player[3] , turn , pCard ,pRoad , pNode ,  &tmp_marine_option , option )&& !quit )
            //     {
            //         int32_t c = print_option_menu( option , 8 );
            //         int32_t choice = 0;
                    
            //         //this is a terrible design but bear with me :(
            //         //offers the choice
            //         for( int32_t i = 0 ; i < 8 ; i++ )
            //         {   
            //             if( option[i] == 1 )
            //             {
            //                 choice++;
            //             }
            //             if( choice == c )
            //             {
            //                 choice = i + 1;
            //                 break;
            //             }
            //         }
            //         switch( choice )
            //         {
            //             case 1: 
            //                 print_board( pTile, pNode, pRoad , player[3]);
            //                 buy_dev_card_func( player[3] , pCard , turn);
            //                 print_board( pTile, pNode, pRoad , player[3]);
            //                 break;
            //             case 2:
            //                 use_dev_card_func( player[3] , player[0] , player[1] , player[2] , pRoad , pNode , pTile , player);
            //                 print_board( pTile, pNode, pRoad ,player[3]);
            //                 devUsage++;//update turn
            //                 break;
            //             case 3:
            //                 //trade_with_player( player[0] );
            //                 break;
            //             case 4:
            //                 marine_trade_func( player[3] , tmp_marine_option);
            //                 break;
            //             case 5:
            //                 build_settlement_func( player[3] , pRoad , pNode );
            //                 print_board( pTile, pNode, pRoad, player[3] );
            //                 break;
            //             case 6:
            //                 build_road_func( player[3]  , pRoad );
            //                 print_board( pTile, pNode, pRoad ,player[3]);
            //                 break;
            //             case 7:
            //                 build_city_func( player[3] , pNode , pRoad );
            //                 print_board( pTile, pNode, pRoad , player[3]);
            //                 break;
            //             case 8:
            //                 quit = 1;
            //                 break;
            //             default:
            //                 break;
            //         }
            //         largest_army( player , pRoad);
            //         if(is_game_over( player ))//check if any player has 10 points
            //         {
            //             goto game_over;
            //         }
            //     }
            //     free( tmp_marine_option);
            //     break;
         }
         turn++;
    }

    game_over:
    printf("Game Over!\n");

    free(pNode);
    free(pTile);
    free(pRoad);

    //free player
    for( int32_t i = 0 ; i < 4 ; i++ )
    {
        free(player[i]);
    }

    return 0;
}