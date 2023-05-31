#include <stdio.h>
#include <stdint.h>
#include "color.h"
#include "struct.h"
#include "prt_board.h"
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
//void check_owner( int32_t owner );
//pttype

void print_node( node node ){
	check_owner( node.owner );
	//if...print(*, V, C)
	if( !node.type ) printf( "*" );//none
	else if( node.type == 1 ) printf( "V" );//settlemet
	else if( node.type == 2 ) printf( "C" );//city
	//clr_rst
	printf( CLR_RST );
}
void check_owner( int32_t owner ){
	//print_clr
	if( owner == 1 ) printf( CLR_RED );
	else if( owner == 2 ) printf( CLR_GRN );
	else if( owner == 3 ) printf( CLR_YLW );
	else if( owner == 4 ) printf( CLR_LBL );
	else printf( CLR_RST );
	return; 
}
void print_tile( tile tile ){
	//robber_check
	if( tile.robber ) {
		printf( CLR_24_BG( 104, 34, 139 ) );
		return;
	}
	//print_clr
	if( tile.resource_type == 1 ) printf( CLR_24_BG( 208, 102, 51 ) );//hill
	else if( tile.resource_type == 2 ) printf( CLR_24_BG( 105, 139, 34 ) );//fields
	else if( tile.resource_type == 3 ) printf( CLR_24_BG( 139, 139, 0 ) ) ;//pasture
	else if( tile.resource_type == 4 ) printf( CLR_24_BG( 34, 139, 34 ) );//forest
	else if( tile.resource_type == 5 ) printf( CLR_24_BG( 131, 139, 131 ) );//mountains
	else if( tile.resource_type == 6 ) printf( CLR_24_BG( 205, 149, 12 ) );//desert
	return;
}

void print_board( tile * pTile, node * pNode, road * pRoad ) {
    printf("              B   ");
	print_node( pNode[0] );//printf("*");
	check_owner( pRoad[0].owner );
	printf("---"CLR_RST);
	print_node( pNode[1] );//printf("*");
	printf("   L   \n");
	////the code above is for line 1-------------------------
    printf("             / \\ ");
	check_owner( pRoad[1].owner );
	printf("/"CLR_RST);
	print_tile( pTile[0] );
	printf("     "CLR_RST);
	check_owner( pRoad[2].owner );
	printf("\\"CLR_RST);
	printf(" / \\ \n");
	////the code above is for line 2-------------------------
    printf("            ");
	print_node( pNode[2] );//printf("*");
	check_owner( pRoad[3].owner );
	printf("---"CLR_RST);
	print_node( pNode[3] );//printf("*");
	print_tile( pTile[0] );
	printf("% 4d", 1);
	printf("   "CLR_RST);
	print_node( pNode[4] );//printf("*");
	check_owner( pRoad[4].owner );
	printf("---"CLR_RST);
	print_node( pNode[5] );//printf("*");
	printf("\n");
	////the code above is for line 3-------------------------
    printf("           ");
	check_owner( pRoad[5].owner );
	printf("/"CLR_RST);
	print_tile( pTile[1] );
	printf("     "CLR_RST);
	check_owner( pRoad[6].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[0] );
	printf("     "CLR_RST);
	check_owner( pRoad[7].owner );
	printf("/"CLR_RST);
	print_tile( pTile[11] );
	printf("     "CLR_RST);
	check_owner( pRoad[8].owner );
	printf("\\"CLR_RST" \n");
	////the code above is for line 4-------------------------
    printf("  ?---");
	print_node( pNode[6] );//printf("*");
	check_owner( pRoad[9].owner );
	printf("---"CLR_RST);
	print_node( pNode[7] );//printf("*");
	print_tile( pTile[1] );
	printf("% 4d", 2);
	printf("   "CLR_RST);
	print_node( pNode[8] );//printf("*");
	check_owner( pRoad[10].owner );
	printf("---"CLR_RST);
	print_node( pNode[9] );//printf("*");
	print_tile( pTile[11] );
	printf("% 4d", 12);
	printf("   "CLR_RST);
	print_node( pNode[10] );//printf("*");
	check_owner( pRoad[11].owner );
	printf("---"CLR_RST);
	print_node( pNode[11] );//printf("*");
	printf("---?\n");
	////the code above is for line 5-------------------------
    printf("   \\ ");
	check_owner( pRoad[12].owner );
	printf("/"CLR_RST);
	print_tile( pTile[2] );
	printf("     "CLR_RST);
	check_owner( pRoad[13].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[1] );
	printf("     "CLR_RST);
	check_owner( pRoad[14].owner );
	printf("/"CLR_RST);
	print_tile( pTile[12] ); 
	printf("     "CLR_RST);
	check_owner( pRoad[15].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[11] );
	printf("     "CLR_RST);
	check_owner( pRoad[16].owner );
	printf("/"CLR_RST);
	print_tile( pTile[10] );
	printf("     "CLR_RST);
	check_owner( pRoad[17].owner );
	printf("\\"CLR_RST" /\n");
	////the code above is for line 6-------------------------
    printf("    ");
	print_node( pNode[12] );//printf("*");
	print_tile( pTile[2] );
	printf("% 4d", 3);
	printf("   "CLR_RST);
	print_node( pNode[13] );//printf("*");
	check_owner( pRoad[18].owner );
	printf("---"CLR_RST);
	print_node( pNode[14] );//printf("*");
	print_tile( pTile[12] );
	printf("% 4d", 13);
	printf("   "CLR_RST);
	print_node( pNode[15] );//printf("*");
	check_owner( pRoad[19].owner );
	printf("---"CLR_RST);
	print_node( pNode[16] );//printf("*");
	print_tile( pTile[10] );
	printf("% 4d", 11);
	printf("   "CLR_RST);
	print_node( pNode[17] );//printf("*");
	printf("\n");
	////the code above is for line 7-------------------------
    printf("     ");
	check_owner( pRoad[20].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[2] );
	printf("     "CLR_RST);
	check_owner( pRoad[21].owner );
	printf("/"CLR_RST);
	print_tile( pTile[13] );
	printf("     "CLR_RST);
	check_owner( pRoad[22].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[12] );
	printf("     "CLR_RST);
	check_owner( pRoad[23].owner );
	printf("/"CLR_RST);
	print_tile( pTile[17] );
	printf("     "CLR_RST);
	check_owner( pRoad[24].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[10] );
	printf("     "CLR_RST);
	check_owner( pRoad[25].owner );
	printf("/"CLR_RST"\n");
	////the code above is for line 8-------------------------
    printf("      ");
	print_node( pNode[18] );//printf("*");
	check_owner( pRoad[26].owner );
	printf("---"CLR_RST);
	print_node( pNode[19] );//printf("*");
	print_tile( pTile[13] );
	printf("% 4d", 14);
	printf("   "CLR_RST);
	print_node( pNode[20] );//printf("*");
	check_owner( pRoad[27].owner );
	printf("---"CLR_RST);
	print_node( pNode[21] );//printf("*");
	print_tile( pTile[17] );
	printf("% 4d   "CLR_RST, 18);
	print_node( pNode[22] );//printf("*");
	check_owner( pRoad[28].owner );
	printf("---"CLR_RST);
	print_node( pNode[23] );//printf("*");
	printf("\n");
	////the code above is for line 9-------------------------
    printf("     ");
	check_owner( pRoad[29].owner );
	printf("/"CLR_RST);
	print_tile( pTile[3] );
	printf("     "CLR_RST);
	check_owner( pRoad[30].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[13] );
	printf("     "CLR_RST);
	check_owner( pRoad[31].owner );
	printf("/"CLR_RST);
	print_tile( pTile[18] );
	printf("     "CLR_RST);
	check_owner( pRoad[32].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[17] );
	printf("     "CLR_RST);
	check_owner( pRoad[33].owner );
	printf("/"CLR_RST);
	print_tile( pTile[9] );
	printf("     "CLR_RST);
	check_owner( pRoad[34].owner );
	printf("\\"CLR_RST" \n");
	////the code above is for line 10-------------------------
	printf("    ");
	print_node( pNode[24] );//printf("*");
	print_tile( pTile[3] );
	printf("% 4d   "CLR_RST, 4);
	print_node( pNode[25] );//printf("*");
	check_owner( pRoad[35].owner );
	printf("---"CLR_RST);
	print_node( pNode[26] );//printf("*");
	print_tile( pTile[18] );
	printf("% 4d   "CLR_RST, 19);
	print_node( pNode[27] );//printf("*");
	check_owner( pRoad[36].owner );
	printf("---"CLR_RST);
	print_node( pNode[28] );//printf("*");
	print_tile( pTile[9] );
	printf("% 4d   "CLR_RST, 10);
	print_node( pNode[29] );//printf("*");
	printf("\n");
	////the code above is for line 11-------------------------
    printf("   / ");
	check_owner( pRoad[37].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[3] );
	printf("     "CLR_RST);
	check_owner( pRoad[38].owner );
	printf("/"CLR_RST);
	print_tile( pTile[14] );
	printf("     "CLR_RST);
	check_owner( pRoad[39].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[18] );
	printf("     "CLR_RST);
	check_owner( pRoad[40].owner );
	printf("/"CLR_RST);
	print_tile( pTile[16] );
	printf("     "CLR_RST);
	check_owner( pRoad[41].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[9] );
	printf("     "CLR_RST);
	check_owner( pRoad[42].owner );
	printf("/"CLR_RST);
	printf(" \\ \n");
	////the code above is for line 12-------------------------
    printf("  ?---");
	print_node( pNode[30] );//printf("*");
	check_owner( pRoad[43].owner );
	printf("---"CLR_RST);
	print_node( pNode[31] );//printf("*");
	print_tile( pTile[14] );
	printf("% 4d   "CLR_RST, 15);
	print_node( pNode[32] );//printf("*");
	check_owner( pRoad[44].owner );	
	printf("---"CLR_RST);
	print_node( pNode[33] );//printf("*");
	print_tile( pTile[16] );
	printf("% 4d   "CLR_RST, 17);
	print_node( pNode[34] );//printf("*");
	check_owner( pRoad[45].owner );
	printf("---"CLR_RST);
	print_node( pNode[35] );//printf("*");
	printf("---G\n");
	////the code above is for line 13-------------------------
    printf("     ");
	check_owner( pRoad[46].owner );
	printf("/"CLR_RST);
	print_tile( pTile[4] );
	printf("     "CLR_RST);
	check_owner( pRoad[47].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[14] );
	printf("     "CLR_RST);
	check_owner( pRoad[48].owner );
	printf("/"CLR_RST);
	print_tile( pTile[15] );
	printf("     "CLR_RST);
	check_owner( pRoad[49].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[16] );
	printf("     "CLR_RST);
	check_owner( pRoad[50].owner );
	printf("/"CLR_RST);
	print_tile( pTile[8] );
	printf("     "CLR_RST);
	check_owner( pRoad[51].owner );
	printf("\\"CLR_RST" \n");
	////the code above is for line 14-------------------------
    printf("    ");
	print_node( pNode[36] );//printf("*");
	print_tile( pTile[4] );
	printf("% 4d   "CLR_RST, 5);
	print_node( pNode[37] );//printf("*");
	check_owner( pRoad[52].owner );
	printf("---"CLR_RST);
	print_node( pNode[38] );//printf("*");
	print_tile( pTile[15] );
	printf("% 4d   "CLR_RST, 16);
	print_node( pNode[39] );//printf("*");
	check_owner( pRoad[53].owner );
	printf("---"CLR_RST);
	print_node( pNode[40] );//printf("*");
	print_tile( pTile[8] );
	printf("% 4d   "CLR_RST, 9);
	print_node( pNode[41] );//printf("*");
	printf("\n");
	////the code above is for line 15-------------------------
    printf("     ");
	check_owner( pRoad[54].owner );	
	printf("\\"CLR_RST);
	print_tile( pTile[4] );
	printf("     "CLR_RST);
	check_owner( pRoad[55].owner );
	printf("/"CLR_RST);
	print_tile( pTile[5] );
	printf("     "CLR_RST);
	check_owner( pRoad[56].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[15] );
	printf("     "CLR_RST);
	check_owner( pRoad[57].owner );
	printf("/"CLR_RST);
	print_tile( pTile[7] );
	printf("     "CLR_RST);
	check_owner( pRoad[58].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[8] );
	printf("     "CLR_RST);
	check_owner( pRoad[59].owner );
	printf("/"CLR_RST"\n");
	////the code above is for line 16-------------------------
    printf("      ");
	print_node( pNode[42] );//printf("*");
	check_owner( pRoad[60].owner );
	printf("---"CLR_RST);
	print_node( pNode[43] );//printf("*");
	print_tile( pTile[5] );
	printf("% 4d   "CLR_RST, 6);
	print_node( pNode[44] );//printf("*");
	check_owner( pRoad[61].owner );
	printf("---"CLR_RST);
	print_node( pNode[45] );//printf("*");
	print_tile( pTile[7] );
	printf("% 4d   "CLR_RST, 8);
	print_node( pNode[46] );//printf("*");
	check_owner( pRoad[62].owner );
	printf("---"CLR_RST);
	print_node( pNode[47] );//printf("*");
	printf("\n");
	////the code above is for line 17-------------------------
    printf("         / ");
	check_owner( pRoad[63].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[5] );
	printf("     "CLR_RST);
	check_owner( pRoad[64].owner );
	printf("/"CLR_RST);
	print_tile( pTile[6] );
	printf("     "CLR_RST);
	check_owner( pRoad[65].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[7] );
	printf("     "CLR_RST);
	check_owner( pRoad[66].owner );
	printf("/"CLR_RST" \\ \n");
	////the code above is for line 18-------------------------
    printf("        S---");
	print_node( pNode[48] );//printf("*");
	check_owner( pRoad[67].owner );
	printf("---"CLR_RST);
	print_node( pNode[49] );//printf("*");
	print_tile( pTile[6] );
	printf("% 4d   "CLR_RST, 7);
	print_node( pNode[50] );//printf("*");
	check_owner( pRoad[68].owner );
	printf("---"CLR_RST);
	print_node( pNode[51] );//printf("*");
	printf("---O\n");
	////the code above is for line 19-------------------------
    printf("                 ");
	check_owner( pRoad[69].owner );
	printf("\\"CLR_RST);
	print_tile( pTile[6] );
	printf("     "CLR_RST);
	check_owner( pRoad[70].owner );
	printf("/"CLR_RST);
	printf("   \n");
	////the code above is for line 20-------------------------
    printf("                  ");
	print_node( pNode[52] );//printf("*");
	check_owner( pRoad[71].owner );
	printf("---"CLR_RST);
	print_node( pNode[53] );//printf("*");
	printf("\n");
	////the code above is for line 21-------------------------
    printf("                   \\ /   \n");
	////the code above is for line 22-------------------------
    printf("                    ?\n");
	////the code above is for line 23-------------------------
}
/*
int main() {
	//tile tile[19] = {0};node node[54] = {0};road road[76] = {0};
	tile* pTile = init_tile();
	road* pRoad = init_road();
	node* pNode = init_node();
    print_board( pTile, pNode, pRoad );
	free( pTile );
	free( pRoad );
	free( pNode );
    return 0;
}*/

