#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "init.h"
#include "color.h"
#include "prt_board.h"

//generate random number
int32_t roll_dice()
{
    srand( time(NULL) );
    int32_t dice1 = rand() % 6 + 1;
    int32_t dice2 = rand() % 6 + 1;
    int32_t sum = dice1 + dice2;
    return sum;
}

//check if any player has settlement on the number
//if yes, give the player resources
//check robber! -> reduce resources 
void obtain_resources( int32_t sum , Player *player , tile *ptile )
{
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
                        player[ptile[i].nodes[j]->owner].resource[ptile[i].resource_type] += 1;
                    }
                    else if( ptile[i].nodes[j]->type == 2 )//city
                    {
                        player[ptile[i].nodes[j]->owner].resource[ptile[i].resource_type] += 2;
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
        if( players[i]->victory_point >= 10 )
        {
            return 1;
        }
    }
    return 0;
}

/* AFTER ANY OPTION IS PERFORMED, OPTION MUST BE UPDATED*/
/*The reason of this option array is to provide a cleaner user's menu every turn*/
enum options {  buy_dev_card = 0 , use_dev_card = 1 , trade_with_player , marine_trade , build_settlement , build_road , build_city };
int32_t option[7] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 };

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

    printf("----------------------------\n");
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
int32_t if_settlement_on_port( Player player , node *pnode )
{
    //if( player.settlement_index = port ) ---> additional info in player?
    /*
    for( int32_t i = 0 ; i < 18 ; i++ )//18 ports
    {
        if( pnode[i].owner == player.index && pnode[i] == port )
        {
            return 1;
        }
        else( pnode[i].owner == player.index && pnode[i] == special port )
        {
            return i;//return the index of the port
        }
    }
    */
    return 0;
    
}


int32_t marine_trade_chk( Player *player , node *pnode )
{
    int32_t on_port = if_settlement_on_port( *player , pnode );
    if( on_port == 1 )//normal port
    {
        if( player->resource[Brick] >= 3 || player->resource[Grain] >= 3 ||player->resource[Sheep] >= 3 || player->resource[Lumber] >= 3 || player->resource[Ore] >= 3  )
        {
            //offer trade
        }
    }
    else if( on_port != 0 )//any special port
    {
        switch( on_port )
        {
            //check port condition
            //return port num
        }
    }
    else if ( player->resource[Brick] >= 4 || player->resource[Grain] >= 4 ||player->resource[Sheep] >= 4 || player->resource[Lumber] >= 4 || player->resource[Ore] >= 4 )
    {
        //offer trade
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

//check if any player has any resources
/*
int32_t player_trade( struct player player )
{
    
}
*/


//play one development card each turn
int32_t is_able_to( Player *player , int32_t turn , node *pnode )
{
    //reset the options 
    for( int32_t i = 0 ; i < 7 ; i++ )
    {
        option[i] = 0;
    }

    /*checks the card pile is still available*/
    int32_t count = 0;
    for( int32_t i = 0 ; i < 25 ; i++ ) 
    {
        if( card[i] == -1 ) {
            count++;
        }
    }
    if( count != 25 ) 
    {
        if( player->resource[Sheep] >= 1 && player->resource[Grain] >= 1 && player->resource[Ore] >= 1 )
        {
            option[buy_dev_card] = 1;
            return 1;
        }
    }

    /*check if the dev card is usable in this round*/
    /*TODO*/
    if( player->dev_card_num >= 1 && turn == 1 )
    {
        option[use_dev_card] = 1;
        return 1;
    }

    if( player->resource[Lumber] >= 1 && player->resource[Brick] >= 1 && player->resource[Sheep] >= 1 && player->resource[Grain] >= 1 )
    {
        option[trade_with_player] = 1;
        return 1;
    }
    
    int32_t port_type = marine_trade_chk( player , pnode );
    if( port_type )
    {
        option[marine_trade] = port_type;
        return 1;
    }

    if( player->resource[Lumber] >= 1 && player->resource[Brick] >= 1 && player->resource[Sheep] >= 1 && player->resource[Grain] >= 1 )
    {
        option[build_settlement] = 1;
        return 1;
    }

    if( player->resource[Lumber] >=1 && player->resource[Brick] >= 1 )
    {
        option[build_road] = 1;
        return 1;
    }

    if( player->resource[Grain] >= 2 && player->resource[Ore] >= 3 && player->settlement_num != 0 )
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
void build_settlement_func( Player *player , road *proad , node *pnode)
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t build_index[54] = {0};

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

        if( chk_3_dir )
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

        if( chk_3_dir )
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

    printf("Select a place to build your settlement:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 || build_index[select-1] == 0)
    {
        printf("Invalid input!\n");
        build_settlement_func( player , proad , pnode );
    }

    player->resource[Lumber] -= 1;
    player->resource[Brick] -= 1;
    player->resource[Sheep] -= 1;
    player->resource[Grain] -= 1;


    //record settlemnt build in player's attributes
    player->building_index[select-1] = 1;
    player->settlement_num += 1;

    //Update node's attributes
    (pnode + (select - 1))->owner = player->index;
    (pnode + (select - 1))->type = 1;
    //option[build_settlement] = 0;
}

//remember to minus settlement_num!!!
//check if any player has 2 wheat, 3 ore
void build_city_func( Player *player , node *pnode , road *proad )
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t build_index[54] = {0};

    for( int32_t i = 0 ; i < 54 ; i++ )
    {
        if( pnode[i].owner != player->index  ){
            continue;
        }
        else{
            if( pnode[i].type == 1 ){
                build_index[i] = 1;
            }
        }
    }

    printf("Select a place to build your city:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 )
    {
        printf("Invalid input!\n");
        build_settlement_func( player , proad , pnode );
    }

    player->resource[Grain] -= 2;
    player->resource[Ore] -= 3;

    //record settlemnt buidl in player's attributes
    return;
}

//check if any player has 1 wood, 1 brick
void build_road_func( Player *player , road *road )
{
    /*Iterate thru node and flash the node that is available, provide the index*/
    int32_t road_index[72] = {0};

    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        if( road->owner == 0 ){
            continue;
        }
        else{
            if( road->dir1->owner == player->index || road->dir2->owner == player->index || road->dir3->owner == player->index || road->dir4->owner == player->index ){
                road_index[road->node1->index] = 1;
            }
        }
    }

    printf("Select a place to build your road:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 )
    {
        printf("Invalid input!\n");
        build_road_func( player , road );
    }

    player->resource[Grain] -= 2;
    player->resource[Ore] -= 3;

    return;
}

//check if dev is obtained in the same turn
void buy_dev_card_func( Player *player )
{
    player->resource[Sheep] -= 1;
    player->resource[Grain] -= 1;
    player->resource[Ore] -= 1;
    //add card to player's hand
    for(int32_t i = 0 ; i < 25 ; i++)
    {
        if( player->dev_card[i] != -1 )
        {
            player->dev_card[card[i]]++; 
            break;
        }
    }
    //turn off the option //player is able to buy mutliple cards if condition is met
    //option[buy_dev_card] = 0; 
}

void moveRobber( tile *ptile , Player *player1 , Player *player_start )//player is the one who moves the robber, player_start is for the reference of all players
{
    printf("Select a tile to place the robber:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 19 || select < 1 || (ptile + (select - 1))->robber == 1 )
    {
        printf("Invalid input!\n");
        moveRobber( ptile , player1 , player_start );
    }
    (ptile + (select - 1))->robber = 1;

    //player with more than 7 cards will lose half of the cards

    //steal a resource from a player
    int32_t steal_index[6] = {0};
    for( int32_t i = 0 ; i < 6 ; i++ )
    {
        steal_index[i] = (ptile + (select - 1))->nodes[i]->owner ;
    }

    printf("Select a player to steal from:\n");
    for( int32_t i = 0 , j = 1 ; i < 6 ; i++ )
    {
        if( steal_index[i] )
        {
            printf("%d. Player %d\n",j++,i+1);
        }
    }

    select = 0;
    scanf("%d",&select);
    if( select > 6 || select < 1 || steal_index[select-1] == 0 )
    {
        printf("Invalid input!\n");
        moveRobber( ptile , player1 , player_start );
    }

    //steal a random resource from the player
    int32_t steal_resource = rand() % 5 + 1;
    while( player_start[select-1].resource[steal_resource] == 0 )
    {
        steal_resource = rand() % 5 + 1;
    }

    player_start[select-1].resource[steal_resource] -= 1;
    player1->resource[steal_resource] += 1;
    
    return;
}

void devBuildRoad( Player *player , road *road )
{
    int32_t road_index[72] = {0};

    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        if( road->owner == 0 ){
            continue;
        }
        else{
            if( road->dir1->owner == player->index || road->dir2->owner == player->index || road->dir3->owner == player->index || road->dir4->owner == player->index ){
                road_index[road->node1->index] = 1;
            }
        }
    }

    printf("Select a place to build your road:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 )
    {
        printf("Invalid input!\n");
        devBuildRoad( player , road );
    }

    return;
}

void Monopoly( Player *monopoler , Player *p1, Player *p2 , Player *p3 )
{
    printf("Select a resource to monopolize:\n");
    printf("1. Brick\n");
    printf("2. grain\n");
    printf("3. Sheep\n");
    printf("4. lumber\n");
    printf("5. Ore\n");
    
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 5 || select < 1 )
    {
        printf("Invalid input!\n");
        Monopoly( monopoler , p1 , p2 , p3 );
    }
    select -= 1;

    int32_t total = p1->resource[select] + p2->resource[select] + p3->resource[select];
    monopoler->resource[select] += total;

    p1->resource[select] = 0;
    p2->resource[select] = 0;
    p3->resource[select] = 0;

    return;
}

void use_dev_card_func( Player *player , Player *p1 , Player *p2 , Player *p3 , road *proad , tile *ptile)
{
    if( player->dev_card_num != 0 )
    {
        if( player->dev_card[Card_Knight] )
        {
            player->dev_card[Card_Knight]--;
            //TODO
            //move the robber
            //steal a resource from a player
            //moveRobber( ptile , player , p1 );//not done!1!!
        }
        else if( player->dev_card[Card_Victory_Point] )
        {
            player->dev_card[Card_Victory_Point]--;
            player->victory_point += 2;
        }
        else if( player->dev_card[Card_Road_Building] )
        {
            player->dev_card[Card_Road_Building]--;
            //TODO
            //build 2 roads
            devBuildRoad( player , proad );
        }
        else if( player->dev_card[Card_Monopoly] )
        {
            player->dev_card[Card_Monopoly]--;
            //TODO
            //choose a resource and take all of that resource from all players
            Monopoly( player , p1 , p2 , p3 );
        }
        else if( player->dev_card[Card_Year_of_Plenty] )
        {
            player->dev_card[Card_Year_of_Plenty]--;
            //TODO
            //choose 2 resources and take 1 of each from the bank
            
        }
    }
}

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
                road_index[i] = 1;
            }
            if( road->node2->owner == player->index )
            {
                road_index[i] = 1;
            }
        }
    }

    //print the road that is available
    for( int32_t i = 0 ; i < 72 ; i++ )
    {
        printf("%d ",road_index[i]);
    }
    printf("\n");

    printf("Select a place to build your road:\n");
    /*TODO*/
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 72 || select < 1 || road_index[select-1] == 0 )
    {
        printf("Invalid input!\n");
        devBuildRoad( player , proad );
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

        if( chk_3_dir )
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

        if( chk_3_dir )
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

    for( int32_t i = 0 ; i < 54 ; i++ )
    {
        printf("%d ",build_index[i]);
    }
    printf("\n");

    printf("Select a place to build your settlement:\n");
    int32_t select = 0;
    scanf("%d",&select);
    if( select > 54 || select < 1 || build_index[select-1] == 0)
    {
        printf("Invalid input!\n");
        SetupBuildSettlement( player , proad , pnode);
    }
    /*TODO*/

    //record settlemnt build in player's attributes
    player->building_index[select-1] = 1;
    player->settlement_num += 1;

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

int main ()
{
    Player *player[4];
    for(int32_t i = 0 ; i < 4 ; i++ )
    {
        player[i] = (Player*)malloc(sizeof(Player));
        player[i]->index = i+1;
    }

    node *pNode = calloc(54,sizeof(node));
    pNode = init_node(pNode);
 
    road *pRoad = calloc( 72 , sizeof(road) );
    pRoad = init_road(pRoad , pNode);

    tile *pTile = calloc(19,sizeof(tile));
    pTile = init_tile(pTile , pNode);

    int32_t settlement_index = 0;

/*-------------------------Setup Phase--------------------------------*/
    SetupBuildSettlement( player[0] , pRoad , pNode );
    SetupBuildRoad( player[0] , pRoad );

    // SetupBuildSettlement( player[1] , pRoad , pNode );
    // SetupBuildRoad( player[1] , pRoad );

    // SetupBuildSettlement( player[2] , pRoad , pNode );
    // SetupBuildRoad( player[2] , pRoad );

    // SetupBuildSettlement( player[3] , pRoad , pNode );
    // SetupBuildRoad( player[3] , pRoad );

    // settlement_index = SetupBuildSettlement( player[3] , pRoad , pNode );
    // SetupObtainResource( settlement_index , player[3] , pNode );
    // SetupBuildRoad( player[3] , pRoad );

    // settlement_index = SetupBuildSettlement( player[2] , pRoad , pNode );
    // SetupObtainResource( settlement_index , player[2] , pNode );
    // SetupBuildRoad( player[2] , pRoad );

    // settlement_index = SetupBuildSettlement( player[1] , pRoad , pNode );
    // SetupObtainResource( settlement_index , player[1] , pNode );
    // SetupBuildRoad( player[1] , pRoad );

    settlement_index = SetupBuildSettlement( player[0] , pRoad , pNode );
    SetupObtainResource( settlement_index , player[0] , pNode );
    SetupBuildRoad( player[0] , pRoad );

/*--------------------------------------------*/


    print_board( pTile, pNode, pRoad );
    printf( "Player 1's turn\n" );
    //int32_t choice;
    int32_t turn = 1;//how many times the player has used the dev card this round

    /*roll dice*/
    //int32_t sum = roll_dice();
    int32_t sum = 7;


    printf("sum = %d\n",sum);
    //allocate resources
    if( sum != 7 )
    {
        obtain_resources( sum , player[0] , pTile );
    }
    else
    {
        //move robber
        moveRobber( pTile , player[0] , player[0] );
        //steal a resource from a player
    }

    //print the resources of player1
    for( int32_t i = 0 ; i < 5 ; i++ )
    {
        printf("%d ",player[0]->resource[i]);
    }
    printf("\n");

    while( is_able_to( player[1] , turn , pNode ) )
    {
        int32_t c = print_option_menu( option , 6 );
        int32_t choice = 0;
        //this is a terrible design but bear with me :(
        //offers the choice
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
                buy_dev_card_func( player[0] );
                break;
            case 2:
                use_dev_card_func( player[0] , player[1] , player[2] , player[3] , pRoad , pTile );
                turn++;//update turn
                break;
            case 3:
                //trade_with_player( player[0] );
                break;
            case 4:
                //marine_trade( player[0]);
                break;
            case 5:
                build_settlement_func( player[0] , pRoad , pNode );
                break;
            case 6:
                build_road_func( player[0]  , pRoad );
                break;
            case 7:
                build_city_func( player[0] , pNode , pRoad );
                break;
            default:
                break;
        }
        is_game_over( player );//check if any player has 10 points
    }

    
    free(pNode);
    free(pTile);
    free(pRoad);

    //free player
    for( int32_t i = 0 ; i < 4 ; i++ )
    {
        free(player[i]);
    }

    /*
    while( 1 ) 
    {
        switch( turn )
        {
            case 1:
                printf( "Player 1's turn\n" );
                //int32_t choice;
                int32_t turn = 1;//player 1's turn
                while( is_able_to( player[1] , turn , pNode ) )
                {
                    int32_t c = print_option_menu( option , 6 );
                    int32_t choice = 0;
                    //this is a terrible design but bear with me :(
                    //offers the choice
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
                            buy_dev_card_func( player[0] );
                            break;
                        case 2:
                            use_dev_card_func( player[0] , player[1] , player[2] , player[3] , pRoad , pTile );
                            turn++;
                            break;
                        case 3:
                            //trade_with_player( player[0] );
                            break;
                        case 4:
                            //marine_trade( player[0]);
                            break;
                        case 5:
                            build_settlement_func( player[0] , pRoad );
                            break;
                        case 6:
                            build_road_func( player[0]  , pRoad );
                            break;
                        case 7:
                            build_city_func( player[0] , pNode , pRoad );
                            break;
                        default:
                            break;
                    }
                    is_game_over( player );//check if any player has 10 points
                    
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
    
    */

    return 0;
}