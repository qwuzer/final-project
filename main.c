#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "color.h"
#include "init.h"

//generate random number
int32_t roll_dice()
{
    srand( time(NULL) );
    int32_t dice1 = rand() % 6 + 1;
    int32_t dice2 = rand() % 6 + 1;
    sum = dice1 + dice2;
    return sum;
}

//check if any player has settlement on the number
//if yes, give the player resources
//check robber! -> reduce resources 
void obtain_resources( int32_t sum , Player *player[] , tile *ptile )
{
    for( int32_t i = 0 ; i < 19 ; i++ )
    {
        if( ptile[i].dice_num == sum && robber != 1 )
        {
            for( int32_t j = 0 ; j < 6 ; j++ )
            {
                if( ptile[i].node[j]->owner != 0 )//if there is a building on the node
                {
                    if( ptile[i].node[j]->type = 1 )//settlment 
                    {
                        player[ptile[i].node[j]->owner]->resource[ptile[i].resource_type] += ptile[i].recsource[j];
                    }
                    else if( ptile[i].node[j].type = 2 )//city
                    {
                        player[ptile[i].node[j]->owner]->resource[ptile[i].resource_type] += (ptile[i].recsource[j] * 2);
                    }
                    
                }
            }
        }
    }
}

//check if any player has 10 points
int32_t is_game_over( Player *players[] )
{
    int32_t i = 0;
    for( i = 0 ; i < 4 ; i++ )
    {
        if( player[i].points >= 10 )
        {
            return 1;
        }
    }
    return 0;
}

/* AFTER ANY OPTION IS PERFORMED, OPTION MUST BE UPDATED*/
/*The reason of this option array is to provide a cleaner user's menu every turn*/
enum options {  buy_dev_card = 0 , use_dev_card = 1 , trade_with_player , marine_trade , build_settlement , build_road , build_city };
int32_t option[6] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 };

int32_t print_option_menu( int32_t option[] , size_t size )
{
    int32_t ret = 0;
    printf("Please select an option:\n");
    int32_t index = 1;
    for( int32_t i = 0 ; i < size ; i++ )
    {
        if( option[i] == 1 )
        {
            printf("%d. ",index);
            switch( i )
            {
                case 0:
                    printf("Buy development card\n");
                    break;
                case 1:
                    printf("Use development card\n");
                    break;
                case 2:
                    printf("Trade with player\n");
                    break;
                case 3:
                    printf("Marine trade\n");
                    break;
                case 4:
                    printf("Build settlement\n");
                    break;
                case 5:
                    printf("Build road\n");
                    break;
                case 6:
                    printf("Build city\n");
                    break;
                default:
                    break;
            }
            index++;
        }
    }

    if( index == 1 )
    {
        printf("No option available!\n");
        return -1;
    }

    printf("----------------------------\n")
    printf("Please enter your option: ");
    scanf("%d",&ret);

    if( ret > index || ret < 1 )
    {
        printf("Invalid input!\n");
        print_option_menu( option , size );
    }

    return ret;
}



enum marine_trade_opt { no_port = 0 , normal_port = 1 , brick_port = 2 , wood_port = 3 , sheep_port = 4 , grain_port = 5 , ore_port = 6};
/*IF ANY BUILD OF USE CARD FUNC IS SUCCESSFUL , BE SURE TO DECREASE CORRESPONDING VALUES*/
int32_t if_settlement_on_port( Player player )
{
    //if( player.settlement_index = port ) ---> additional info in player?
    
    for( int32_t i = 0 ; i < 18 ; i++ )//18 ports
    {
        if( node[i].owner == player.index && node[i] == port )
        {
            return 1;
        }
        else( node[i].owner == player.index && node[i] == special port )
        {
            return i;//return the index of the port
        }
    }
    return 0;
    
}


int32_t marine_trade_chk( Player *player )
{
    int32_t on_port = if_settlement_on_port( *player );
    if( on_port == 1 )//normal port
    {
        if( player->wood >= 3 || player->brick >= 3 || player->sheep >= 3 || player->wheat >= 3 || player->ore >= 3 )
        {
            //offer trade
            return 1;
        }
    }
    else if( on_port != 0 )//any special port
    {
        switch( on_port )
        {
            //check port cond
            //return port num
        }
    }
    else if ( player->wood >= 4 || player->brick >= 4 || player->sheep >= 4 || player->wheat >= 4 || player->ore >= 4 )
    {
        //offer trade
        return 1;
    }
    else
    {
        return 0;
    }
}

//check if any player has any resources
/*
int32_t player_trade( struct player player )
{
    
}
*/


//other restrictions? e.g development card can only be used once per turn
int32_t is_able_to( Player *player )
{
    if( player->sheep >= 1 && player->wheat >= 1 && player->ore >= 1 )
    {
        option[buy_dev_card] = 1;
        return 1;
    }

    if( player->dev_card_num >= 1 )
    {
        option[use_dev_card] = 1;
        return 1;
    }

    if( player->wood >= 1 || player->brick >= 1 || player->sheep >= 1 || player->wheat >= 1 )
    {
        option[trade_with_player] = 1;
        return 1;
    }

    if( int32_t port_type = marine_trade_chk( player ) )
    {
        option[marine_trade] = port_type;
        return 1;
    }

    if( player->wood >= 1 && player->brick >= 1 && player->sheep >= 1 && player->wheat >= 1 )
    {
        option[build_settlement] = 1;
        return 1;
    }

    if( player->wood >= 1 && player->brick >= 1 )
    {
        option[build_road] = 1;
        return 1;
    }

    if( player->wheat >= 2 && player->ore >= 3 && player->settlement_num >= 1 )
    {
        option[build_city] = 1;
        return 1;
    }

    return 0;
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
int32_t build_settlement( Player player )
{
    printf("Select a place to build your settlement:\n");

    player.wood -= 1;
    player.brick -= 1;
    player.sheep -= 1;
    player.wheat -= 1;

    option[build_settlement] = 0;
}

//remember to minus settlement_num!!!
//check if any player has 2 wheat, 3 ore
build_city()
{
    
}

//check if any player has 1 wood, 1 brick
build_road()
{
    
}

//check if dev is obtained in the same turn, if yes, unable to use
buy_dev_card()
{
    //check if any player has 1 sheep, 1 wheat, 1 ore
}

use_dev_card()
{

}

int main ()
{
    Player *player[4];
    for(int32_t i = 0 ; i < 4 ; i++ )
    {
        player[i] = (Player*)malloc(sizeof(Player));
    }

    int32_t turn = 1;
    int32_t game_not_over = 1;
    while( 1 ) 
    {
        switch( turn )
        {
            case 1:
                printf( "Player 1's turn\n" );
                int32_t choice;
                while( is_able_to( player1 ) )
                {
                    int32_t c = print_option_menu( option , 6 );
                    int32_t choice = 0;
                    //this is a terrible design but bear with me :(
                    for( int32_t i = 0 ; i < 7 ; i++ )
                    {   
                        if( option[i] == 1 )
                        {
                            choice++;
                        }
                        if( choice == c )
                        {
                            choice = i;
                            break;
                        }
                    }
                    switch( choice )
                    {
                        case 1: 
                            buy_dev_card( player1 );
                            break;
                        case 2:
                            use_dev_card( player1 );
                            break;
                        case 3:
                            trade_with_player( player1 );
                            break;
                        case 4:
                            marine_trade( player1 );
                            break;
                        case 5:
                            build_settlement( player1 );
                            break;
                        case 6:
                            build_road( player1 );
                            break;
                        case 7:
                            build_city( player1 );
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 2:
                printf( "Player 2's turn\n" );
                break;
            case 3:
                printf( "Player 3's turn\n" );
                break;
            case 4:
                printf( "Player 4's turn\n" );
                break;
            default:
                break;
        }
    }


    for( int32_t i = 0 ; i < 4 ; i++ )
    {
        free(player[i]);
    }
    return 0;
}