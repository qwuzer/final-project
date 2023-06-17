#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "struct.h"
#include "init.h"

//int32_t card[25] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 };

int32_t tile_dice_num[18] = { 5 , 2 , 6 , 3 , 8 , 10 , 9 , 12 , 11 , 4 , 8 , 10 , 9 , 4 , 5 , 6 , 3 , 11 };//2-12

int32_t tile_type[19] = { 5 , 2 , 2 , 4 , 1 , 2 , 3 , 3 , 5 , 1 , 4 , 2 , 1 , 4 , 5 , 2 , 4 , 3 , 6 };


card *init_card( card *pcard )
{
    int32_t tmp[25] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 };
    //shuffle tmp
    // for( int32_t i = 0 ; i < 25 ; i++ ){
    //     int32_t j = rand() % 25;
    //     int32_t tmp2 = tmp[i];
    //     tmp[i] = tmp[j];
    //     tmp[j] = tmp2;
    // }
    //init card
    for( int32_t i = 0 ; i < 25 ; i++ ){
        pcard[i].type = tmp[i];
        pcard[i].timestamp = 0;
    }
    return pcard;
}


node *init_node( node *pnode )
{
    //node *pnode=calloc(54,sizeof(node));
    node *p_ret=pnode;

    for( int i=1 ; i<=54 ; i++ ) //connect nodes
    {
        if( i == 1 || i == 3 || i == 7 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 1;
            tmp->dir1 = ( pnode + i );
            if(i==1) tmp->dir2 = ( pnode + 3 );
            if(i==3) tmp->dir2 = ( pnode + 7 );
            if(i==7) tmp->dir2 = ( pnode + 12 );
            tmp->dir3 = NULL;
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
        else if( i == 2 || i == 6 || i == 12 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 0;
            tmp->dir1 = NULL;
            if(i==2) tmp->dir2 = ( pnode + 4 );
            if(i==6) tmp->dir2 = ( pnode + 10 );
            if(i==12) tmp->dir2 = ( pnode + 17 );
            tmp->dir3 = (pnode+i-2);
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
        else if( i == 13 || i == 25 || i == 37 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 0;
            if(i==13) tmp->dir1 = ( pnode + 6  );
            if(i==25) tmp->dir1 = ( pnode + 18 );
            if(i==37) tmp->dir1 = ( pnode + 30 );
            if(i==13) tmp->dir2 = ( pnode + 18 );
            if(i==25) tmp->dir2 = ( pnode + 30 );
            if(i==37) tmp->dir2 = ( pnode + 42 );
            tmp->dir3 = NULL;
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
        else if( i == 18 || i == 30 || i == 42 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 1;
            tmp->dir1 = NULL;
            if(i==18) tmp->dir2 = ( pnode + 11 );
            if(i==30) tmp->dir2 = ( pnode + 23 );
            if(i==42) tmp->dir2 = ( pnode + 35 );
            if(i==18) tmp->dir3 = ( pnode + 23 );
            if(i==30) tmp->dir3 = ( pnode + 35 );
            if(i==42) tmp->dir3 = ( pnode + 51 );
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
        else if( i == 43 || i == 49 || i == 53 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 1;
            if(i==43) tmp->dir1 = ( pnode + i );
            if(i==49) tmp->dir1 = ( pnode + i );
            if(i==53) tmp->dir1 = ( pnode + i );
            tmp->dir2 = NULL;
            if(i==43) tmp->dir3 = ( pnode + 36 );
            if(i==49) tmp->dir3 = ( pnode + 43 );
            if(i==53) tmp->dir3 = ( pnode + 49 );
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
        else if( i == 48 || i == 52 || i == 54 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 0;
            if(i==48) tmp->dir1 = ( pnode + 41 );
            if(i==52) tmp->dir1 = ( pnode + 46 );
            if(i==54) tmp->dir1 = ( pnode + 51 );
            tmp->dir2 = NULL;
            if(i==48) tmp->dir3 = ( pnode + i - 2 );
            if(i==52) tmp->dir3 = ( pnode + i - 2 );
            if(i==54) tmp->dir3 = ( pnode + i - 2 );
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
        else if( i ==  5 || i ==  9 || i == 11 || i == 14 || i == 16 ||
                 i == 19 || i == 21 || i == 23 || i == 26 || i == 28 ||
                 i == 31 || i == 33 || i == 35 || i == 38 || i == 40 ||
                 i == 45 || i == 47 || i == 51 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 1;
            tmp->dir1 = ( pnode + i );
            tmp->dir2 = ( pnode + i + 5 - (i==5||i==15||i==47) - (i==51)*3 );
            tmp->dir3 = ( pnode + i - 7 + (i==9||i==11||i==51) + (i==5)*3 );
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
        else if( i ==  4 || i ==  8 || i == 10 || i == 15 || i == 17 ||
                 i == 20 || i == 22 || i == 24 || i == 27 || i == 29 ||
                 i == 32 || i == 34 || i == 36 || i == 39 || i == 41 ||
                 i == 44 || i == 46 || i == 50 )
        {
            node *tmp=(pnode+i-1);
            tmp->index = i;
            tmp->type = 0;
            tmp->owner = 0;
            tmp->triangle_type = 0;
            tmp->dir1 = ( pnode + i - 7 + (i==8||i==10||i==50) + (i==4)*3 );
            tmp->dir2 = ( pnode + i + 5 - (i==4||i==44||i==46) - (i==50)*3 );
            tmp->dir3 = ( pnode + i - 1 );
            tmp->tile1 = 0;
            tmp->tile2 = 0;
            tmp->tile3 = 0;
        }
    }
    for( int i=1 ; i<=19 ; i++ ) // connect node and tile
    {
        node *tmp=pnode;
        if(i==1){
            tmp=pnode+0;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+1;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+3;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+4;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+8;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+9;
            tmp->tile1 = tile_type[i-1];
        }else if(i==2){
            tmp=pnode+2;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+3;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+7;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+8;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+13;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+14;
            tmp->tile1 = tile_type[i-1];
        }else if(i==3){
            tmp=pnode+6;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+7;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+12;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+13;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+18;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+19;
            tmp->tile1 = tile_type[i-1];
        }else if(i==4){
            tmp=pnode+18;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+19;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+24;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+25;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+30;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+31;
            tmp->tile1 = tile_type[i-1];
        }else if(i==5){
            tmp=pnode+30;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+31;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+36;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+37;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+42;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+43;
            tmp->tile1 = tile_type[i-1];
        }else if(i==6){
            tmp=pnode+37;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+38;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+43;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+44;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+48;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+49;
            tmp->tile1 = tile_type[i-1];
        }else if(i==7){
            tmp=pnode+44;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+45;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+49;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+50;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+52;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+53;
            tmp->tile1 = tile_type[i-1];
        }else if(i==8){
            tmp=pnode+39;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+40;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+45;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+46;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+50;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+51;
            tmp->tile1 = tile_type[i-1];
        }else if(i==9){
            tmp=pnode+34;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+35;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+40;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+41;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+46;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+47;
            tmp->tile1 = tile_type[i-1];
        }else if(i==10){
            tmp=pnode+22;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+23;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+28;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+29;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+34;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+35;
            tmp->tile2 = tile_type[i-1];
        }else if(i==11){
            tmp=pnode+10;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+11;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+16;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+17;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+22;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+23;
            tmp->tile2 = tile_type[i-1];
        }else if(i==12){
            tmp=pnode+4;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+5;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+9;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+10;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+15;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+16;
            tmp->tile2 = tile_type[i-1];
        }else if(i==13){
            tmp=pnode+8;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+9;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+14;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+15;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+20;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+21;
            tmp->tile1 = tile_type[i-1];
        }else if(i==14){
            tmp=pnode+13;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+14;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+19;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+20;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+25;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+26;
            tmp->tile1 = tile_type[i-1];
        }else if(i==15){
            tmp=pnode+25;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+26;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+31;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+32;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+37;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+38;
            tmp->tile2 = tile_type[i-1];
        }else if(i==16){
            tmp=pnode+32;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+33;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+38;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+39;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+44;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+15;
            tmp->tile3 = tile_type[i-1];
        }else if(i==17){
            tmp=pnode+27;
            tmp->tile1 = tile_type[i-1];
            tmp=pnode+28;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+33;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+34;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+39;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+40;
            tmp->tile3 = tile_type[i-1];
        }else if(i==18){
            tmp=pnode+15;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+16;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+21;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+22;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+27;
            tmp->tile2 = tile_type[i-1];
            tmp=pnode+28;
            tmp->tile3 = tile_type[i-1];
        }else if(i==19){
            tmp=pnode+20;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+21;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+26;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+27;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+32;
            tmp->tile3 = tile_type[i-1];
            tmp=pnode+33;
            tmp->tile3 = tile_type[i-1];
        }
    }


    return p_ret;
}

tile *init_tile( tile *ptile ,  node *pnode )
{
   // tile *ptile=calloc(19,sizeof(tile));
    for(int i=0;i<19;++i)
    {
        tile tmp;
        tmp.index=i+1;
        tmp.resource_type = tile_type[i];
        tmp.robber= 0 + (i==18); //if i=18 means it's dessert, so put the robber
        if( i!=18 ) 
        {
            tmp.dice_num=tile_dice_num[i];
        }
        else
        {
            tmp.dice_num = 0;
        }
        // connect to node
        if( i==0 )
        {
            tmp.nodes[0] = ( pnode +  0 );
            tmp.nodes[1] = ( pnode +  1 );
            tmp.nodes[2] = ( pnode +  3 );
            tmp.nodes[3] = ( pnode +  4 );
            tmp.nodes[4] = ( pnode +  8 );
            tmp.nodes[5] = ( pnode +  9 );
        }
        else if( i==1 )
        {
            tmp.nodes[0] = ( pnode +  2 );
            tmp.nodes[1] = ( pnode +  3 );
            tmp.nodes[2] = ( pnode +  7 );
            tmp.nodes[3] = ( pnode +  8 );
            tmp.nodes[4] = ( pnode + 13 );
            tmp.nodes[5] = ( pnode + 14 );
        }
        else if( i==2 )
        {
            tmp.nodes[0] = ( pnode +  6 );
            tmp.nodes[1] = ( pnode +  7 );
            tmp.nodes[2] = ( pnode + 12 );
            tmp.nodes[3] = ( pnode + 13 );
            tmp.nodes[4] = ( pnode + 18 );
            tmp.nodes[5] = ( pnode + 19 );
        }
        else if( i==3 )
        {
            tmp.nodes[0] = ( pnode + 18 );
            tmp.nodes[1] = ( pnode + 19 );
            tmp.nodes[2] = ( pnode + 24 );
            tmp.nodes[3] = ( pnode + 25 );
            tmp.nodes[4] = ( pnode + 30 );
            tmp.nodes[5] = ( pnode + 31 );
        }
        else if( i==4 )
        {
            tmp.nodes[0] = ( pnode + 30 );
            tmp.nodes[1] = ( pnode + 31 );
            tmp.nodes[2] = ( pnode + 36 );
            tmp.nodes[3] = ( pnode + 37 );
            tmp.nodes[4] = ( pnode + 42 );
            tmp.nodes[5] = ( pnode + 43 );
        }
        else if( i==5 )
        {
            tmp.nodes[0] = ( pnode + 37 );
            tmp.nodes[1] = ( pnode + 38 );
            tmp.nodes[2] = ( pnode + 43 );
            tmp.nodes[3] = ( pnode + 44 );
            tmp.nodes[4] = ( pnode + 48 );
            tmp.nodes[5] = ( pnode + 49 );
        }
        else if( i==6 )
        {
            tmp.nodes[0] = ( pnode + 44 );
            tmp.nodes[1] = ( pnode + 45 );
            tmp.nodes[2] = ( pnode + 49 );
            tmp.nodes[3] = ( pnode + 50 );
            tmp.nodes[4] = ( pnode + 52 );
            tmp.nodes[5] = ( pnode + 53 );
        }
        else if( i==7 )
        {
            tmp.nodes[0] = ( pnode + 39 );
            tmp.nodes[1] = ( pnode + 40 );
            tmp.nodes[2] = ( pnode + 45 );
            tmp.nodes[3] = ( pnode + 46 );
            tmp.nodes[4] = ( pnode + 50 );
            tmp.nodes[5] = ( pnode + 51 );
        }
        else if( i==8 )
        {
            tmp.nodes[0] = ( pnode + 34 );
            tmp.nodes[1] = ( pnode + 35 );
            tmp.nodes[2] = ( pnode + 40 );
            tmp.nodes[3] = ( pnode + 41 );
            tmp.nodes[4] = ( pnode + 46 );
            tmp.nodes[5] = ( pnode + 47 );
        }
        else if( i==9 )
        {
            tmp.nodes[0] = ( pnode + 22 );
            tmp.nodes[1] = ( pnode + 23 );
            tmp.nodes[2] = ( pnode + 28 );
            tmp.nodes[3] = ( pnode + 29 );
            tmp.nodes[4] = ( pnode + 34 );
            tmp.nodes[5] = ( pnode + 35 );
        }
        else if( i==10 )
        {
            tmp.nodes[0] = ( pnode + 10 );
            tmp.nodes[1] = ( pnode + 11 );
            tmp.nodes[2] = ( pnode + 16 );
            tmp.nodes[3] = ( pnode + 17 );
            tmp.nodes[4] = ( pnode + 22 );
            tmp.nodes[5] = ( pnode + 23 );
        }
        else if( i==11 )
        {
            tmp.nodes[0] = ( pnode +  4 );
            tmp.nodes[1] = ( pnode +  5 );
            tmp.nodes[2] = ( pnode +  9 );
            tmp.nodes[3] = ( pnode + 10 );
            tmp.nodes[4] = ( pnode + 15 );
            tmp.nodes[5] = ( pnode + 16 );
        }
        else if( i==12 )
        {
            tmp.nodes[0] = ( pnode +  8 );
            tmp.nodes[1] = ( pnode +  9 );
            tmp.nodes[2] = ( pnode + 14 );
            tmp.nodes[3] = ( pnode + 15 );
            tmp.nodes[4] = ( pnode + 20 );
            tmp.nodes[5] = ( pnode + 21 );
        }
        else if( i==13 )
        {
            tmp.nodes[0] = ( pnode + 13 );
            tmp.nodes[1] = ( pnode + 14 );
            tmp.nodes[2] = ( pnode + 19 );
            tmp.nodes[3] = ( pnode + 20 );
            tmp.nodes[4] = ( pnode + 25 );
            tmp.nodes[5] = ( pnode + 26 );
        }
        else if( i==14 )
        {
            tmp.nodes[0] = ( pnode + 25 );
            tmp.nodes[1] = ( pnode + 26 );
            tmp.nodes[2] = ( pnode + 31 );
            tmp.nodes[3] = ( pnode + 32 );
            tmp.nodes[4] = ( pnode + 37 );
            tmp.nodes[5] = ( pnode + 38 );
        }
        else if( i==15 )
        {
            tmp.nodes[0] = ( pnode + 32 );
            tmp.nodes[1] = ( pnode + 33 );
            tmp.nodes[2] = ( pnode + 38 );
            tmp.nodes[3] = ( pnode + 39 );
            tmp.nodes[4] = ( pnode + 44 );
            tmp.nodes[5] = ( pnode + 45 );
        }
        else if( i==16 )
        {
            tmp.nodes[0] = ( pnode + 27 );
            tmp.nodes[1] = ( pnode + 28 );
            tmp.nodes[2] = ( pnode + 33 );
            tmp.nodes[3] = ( pnode + 34 );
            tmp.nodes[4] = ( pnode + 39 );
            tmp.nodes[5] = ( pnode + 40 );
        }
        else if( i==17 )
        {
            tmp.nodes[0] = ( pnode + 15 );
            tmp.nodes[1] = ( pnode + 16 );
            tmp.nodes[2] = ( pnode + 21 );
            tmp.nodes[3] = ( pnode + 22 );
            tmp.nodes[4] = ( pnode + 27 );
            tmp.nodes[5] = ( pnode + 28 );
        }
        else if( i==18 )
        {
            tmp.nodes[0] = ( pnode + 20 );
            tmp.nodes[1] = ( pnode + 21 );
            tmp.nodes[2] = ( pnode + 26 );
            tmp.nodes[3] = ( pnode + 27 );
            tmp.nodes[4] = ( pnode + 32 );
            tmp.nodes[5] = ( pnode + 33 );
        }


        *( ptile + i ) = tmp;
    }
    return ptile;
}

road *init_road( road *proad , node *pnode )
{
   // road *proad = calloc( 72 , sizeof(road) );
    road *p_ret = proad;
    for( int i = 0 ; i < 72 ; i++ )
    {
        road *tmp = ( proad + i );
        tmp->index = i + 1;
        tmp->owner = 0;
        //connect each other
        if( i == 12 || i == 54 )
        {
            tmp->dir1 = ( proad +  9*(i==12) + 46*(i==54) );
            tmp->dir2 = ( proad + 20*(i==12) + 60*(i==54) );
            tmp->dir3 = NULL;
            tmp->dir4 = NULL;
        }
        else if( i == 0 )
        {
            tmp->dir3 = ( proad + 1 );
            tmp->dir2 = ( proad + 2 );
            tmp->dir1 = NULL;
            tmp->dir4 = NULL;
        }
        else if( i == 17 || i == 59 )
        {
            tmp->dir3 = ( proad + 26*(i==17) + 51*(i==59) );
            tmp->dir4 = ( proad + 11*(i==17) + 62*(i==59) );
            tmp->dir1 = NULL;
            tmp->dir2 = NULL;
        }
        else if( i == 72 )
        {
            tmp->dir1 = ( proad + 70 );
            tmp->dir4 = ( proad + 69 );
            tmp->dir2 = NULL;
            tmp->dir3 = NULL;
        }
        else if( i ==  1 || i ==  3 || i ==  5 || i ==  9 || i == 20 || i == 37 )
        {
            tmp->dir1 = ( proad +  0*(i== 1) +  1*(i== 3) +  3*(i== 5) +  5*(i== 9) + 12*(i==20) + 29*(i==37) );
            tmp->dir2 = ( proad +  6*(i== 1) +  6*(i== 3) + 13*(i== 5) + 13*(i== 9) + 26*(i==20) + 43*(i==37) );
            tmp->dir3 = ( proad +  3*(i== 1) +  5*(i== 3) +  9*(i== 5) + 12*(i== 9) + 29*(i==20) + 46*(i==37) );
            tmp->dir4 = NULL;
        }
        else if( i == 29 || i == 40 || i == 60 || i == 63 || i == 67 || i == 69 )
        {
            tmp->dir1 = ( proad + 26*(i==29) + 43*(i==40) + 55*(i==60) + 55*(i==63) + 64*(i==67) + 64*(i==69) );
            tmp->dir2 = ( proad + 37*(i==29) + 54*(i==40) + 63*(i==60) + 67*(i==63) + 69*(i==67) + 71*(i==69) );
            tmp->dir4 = ( proad + 20*(i==29) + 37*(i==40) + 54*(i==60) + 60*(i==63) + 63*(i==67) + 67*(i==69) );
            tmp->dir3 = NULL;
        }
        else if( i == 34 || i == 51 || i == 62 || i == 66 || i == 68 || i == 70 )
        {
            tmp->dir1 = ( proad + 25*(i==34) + 42*(i==51) + 59*(i==62) + 62*(i==66) + 66*(i==68) + 68*(i==70) );
            tmp->dir3 = ( proad + 42*(i==34) + 59*(i==51) + 66*(i==62) + 68*(i==66) + 70*(i==68) + 71*(i==70) );
            tmp->dir4 = ( proad + 28*(i==34) + 45*(i==51) + 58*(i==62) + 58*(i==66) + 65*(i==68) + 65*(i==70) );
            tmp->dir2 = NULL;
        }
        else if( i ==  2 || i ==  4 || i ==  8 || i == 11 || i == 25 || i == 42 )
        {
            tmp->dir2 = ( proad +  4*(i== 2) +  8*(i== 4) + 11*(i== 8) + 17*(i==11) + 34*(i==25) + 51*(i==42) );
            tmp->dir3 = ( proad +  7*(i== 2) +  7*(i== 4) + 16*(i== 8) + 16*(i==11) + 28*(i==25) + 45*(i==42) );
            tmp->dir4 = ( proad +  0*(i== 2) +  2*(i== 4) +  4*(i== 8) +  8*(i==11) + 17*(i==25) + 34*(i==42) );
            tmp->dir1 = NULL;
        }
        else if( i == 10 || i == 18 || i == 19 || i == 26 || i == 27 || i == 28 || i == 35 ||
                 i == 36 || i == 43 || i == 44 || i == 45 || i == 52 || i == 53 || i == 61 )
        {
            tmp->dir1 = ( proad +  7*(i==10) + 14*(i==18) + 16*(i==19) + 21*(i==26) + 23*(i==27) + 25*(i==28) + 31*(i==35) 
                                + 33*(i==36) + 38*(i==43) + 40*(i==44) + 42*(i==45) + 48*(i==52) + 50*(i==53) + 57*(i==61) );
            tmp->dir2 = ( proad + 15*(i==10) + 22*(i==18) + 24*(i==19) + 30*(i==26) + 32*(i==27) + 34*(i==28) + 39*(i==35) 
                                + 41*(i==36) + 47*(i==43) + 49*(i==44) + 51*(i==45) + 56*(i==52) + 58*(i==53) + 65*(i==61) );
            tmp->dir3 = ( proad + 14*(i==10) + 21*(i==18) + 23*(i==19) + 29*(i==26) + 31*(i==27) + 33*(i==28) + 38*(i==35) 
                                + 40*(i==36) + 46*(i==43) + 48*(i==44) + 50*(i==45) + 55*(i==52) + 57*(i==53) + 64*(i==61) );
            tmp->dir4 = ( proad +  6*(i==10) + 13*(i==18) + 15*(i==19) + 20*(i==26) + 22*(i==27) + 24*(i==28) + 30*(i==35) 
                                + 32*(i==36) + 37*(i==43) + 39*(i==44) + 41*(i==45) + 47*(i==52) + 49*(i==53) + 56*(i==61) );
        }
        else if( i ==  7 || i == 14 || i == 16 || i == 21 || i == 23 || i == 31 || i == 33 ||
                 i == 38 || i == 40 || i == 48 || i == 50 || i == 55 || i == 57 || i == 64 )
        {
            tmp->dir1 = ( proad +  4*(i== 7) + 10*(i==14) + 11*(i==16) + 18*(i==21) + 19*(i==23) + 27*(i==31) + 28*(i==33) 
                                + 35*(i==38) + 36*(i==40) + 44*(i==48) + 45*(i==50) + 52*(i==55) + 53*(i==57) + 61*(i==64) );
            tmp->dir2 = ( proad + 15*(i== 7) + 22*(i==14) + 24*(i==16) + 30*(i==21) + 32*(i==23) + 39*(i==31) + 41*(i==33) 
                                + 47*(i==38) + 49*(i==40) + 56*(i==48) + 58*(i==50) + 63*(i==55) + 65*(i==57) + 69*(i==64) );
            tmp->dir3 = ( proad + 10*(i== 7) + 18*(i==14) + 19*(i==16) + 26*(i==21) + 27*(i==23) + 35*(i==31) + 36*(i==33) 
                                + 43*(i==38) + 44*(i==40) + 52*(i==48) + 53*(i==50) + 60*(i==55) + 61*(i==57) + 67*(i==64) );
            tmp->dir4 = ( proad +  2*(i== 7) +  6*(i==14) +  8*(i==16) + 13*(i==21) + 15*(i==23) + 22*(i==31) + 24*(i==33) 
                                + 30*(i==38) + 32*(i==40) + 39*(i==48) + 41*(i==50) + 47*(i==55) + 49*(i==57) + 56*(i==64) );
        }
        else if( i ==  6 || i == 13 || i == 15 || i == 22 || i == 24 || i == 30 || i == 32 ||
                 i == 39 || i == 41 || i == 47 || i == 49 || i == 56 || i == 58 || i == 65 )
        {
            tmp->dir1 = ( proad +  1*(i== 6) +  5*(i==13) +  7*(i==15) + 14*(i==22) + 16*(i==24) + 21*(i==30) + 23*(i==32) 
                                + 31*(i==39) + 33*(i==41) + 38*(i==47) + 40*(i==49) + 48*(i==56) + 50*(i==58) + 57*(i==65) );
            tmp->dir2 = ( proad + 10*(i== 6) + 18*(i==13) + 19*(i==15) + 27*(i==22) + 28*(i==24) + 35*(i==30) + 36*(i==32) 
                                + 44*(i==39) + 45*(i==41) + 52*(i==47) + 53*(i==49) + 61*(i==56) + 62*(i==58) + 68*(i==65) );
            tmp->dir3 = ( proad + 14*(i== 6) + 21*(i==13) + 23*(i==15) + 31*(i==22) + 33*(i==24) + 38*(i==30) + 40*(i==32) 
                                + 48*(i==39) + 50*(i==41) + 55*(i==47) + 57*(i==49) + 64*(i==56) + 66*(i==58) + 70*(i==65) );
            tmp->dir4 = ( proad +  3*(i== 6) +  9*(i==13) + 10*(i==15) + 18*(i==22) + 19*(i==24) + 26*(i==30) + 27*(i==32) 
                                + 35*(i==39) + 36*(i==41) + 43*(i==47) + 44*(i==49) + 52*(i==56) + 53*(i==58) + 61*(i==65) );
        }
        //connect to node up to down left to right
        // - : 1,4,5,10,11,12,19,20,27,28,29,36,37,44,45,46,53,54,61,62,63,68,69,72
        // / : 2,6,8,13,15,17,22,24,26,30,32,34,39,41,43,47,49,51,56,58,60,65,67,71
        // \ : 3,7,9,14,16,18,21,23,25,31,33,35,38,40,42,48,50,52,55,57,59,64,66,70
        if(i==0) { tmp->node1 = ( pnode +  0 ); tmp->node2 = ( pnode +  1); }
        else if(i== 1) { tmp->node1 = ( pnode +  0 ); tmp->node2 = ( pnode +  3); }
        else if(i== 2) { tmp->node1 = ( pnode +  1 ); tmp->node2 = ( pnode +  4); }
        else if(i== 3) { tmp->node1 = ( pnode +  2 ); tmp->node2 = ( pnode +  3); }
        else if(i== 4) { tmp->node1 = ( pnode +  4 ); tmp->node2 = ( pnode +  5); }//
        else if(i== 5) { tmp->node1 = ( pnode +  2 ); tmp->node2 = ( pnode +  7); }
        else if(i== 6) { tmp->node1 = ( pnode +  3 ); tmp->node2 = ( pnode +  8); }
        else if(i== 7) { tmp->node1 = ( pnode +  4 ); tmp->node2 = ( pnode +  9); }
        else if(i== 8) { tmp->node1 = ( pnode +  5 ); tmp->node2 = ( pnode + 10); }
        else if(i== 9) { tmp->node1 = ( pnode +  6 ); tmp->node2 = ( pnode +  7); }
        else if(i==10) { tmp->node1 = ( pnode +  8 ); tmp->node2 = ( pnode +  9); }
        else if(i==11) { tmp->node1 = ( pnode + 10 ); tmp->node2 = ( pnode + 11); }
        else if(i==12) { tmp->node1 = ( pnode +  6 ); tmp->node2 = ( pnode + 12); }
        else if(i==13) { tmp->node1 = ( pnode +  7 ); tmp->node2 = ( pnode + 13); }
        else if(i==14) { tmp->node1 = ( pnode +  8 ); tmp->node2 = ( pnode + 14); }
        else if(i==15) { tmp->node1 = ( pnode +  9 ); tmp->node2 = ( pnode + 15); }
        else if(i==16) { tmp->node1 = ( pnode + 10 ); tmp->node2 = ( pnode + 16); }
        else if(i==17) { tmp->node1 = ( pnode + 11 ); tmp->node2 = ( pnode + 17); }//25%
        else if(i==18) { tmp->node1 = ( pnode + 13 ); tmp->node2 = ( pnode + 14); }
        else if(i==19) { tmp->node1 = ( pnode + 15 ); tmp->node2 = ( pnode + 16); }
        else if(i==20) { tmp->node1 = ( pnode + 12 ); tmp->node2 = ( pnode + 18); }
        else if(i==21) { tmp->node1 = ( pnode + 13 ); tmp->node2 = ( pnode + 19); }
        else if(i==22) { tmp->node1 = ( pnode + 14 ); tmp->node2 = ( pnode + 20); }
        else if(i==23) { tmp->node1 = ( pnode + 15 ); tmp->node2 = ( pnode + 21); }
        else if(i==24) { tmp->node1 = ( pnode + 16 ); tmp->node2 = ( pnode + 22); }
        else if(i==25) { tmp->node1 = ( pnode + 17 ); tmp->node2 = ( pnode + 23); }
        else if(i==26) { tmp->node1 = ( pnode + 18 ); tmp->node2 = ( pnode + 19); }
        else if(i==27) { tmp->node1 = ( pnode + 20 ); tmp->node2 = ( pnode + 21); }
        else if(i==28) { tmp->node1 = ( pnode + 22 ); tmp->node2 = ( pnode + 23); }
        else if(i==29) { tmp->node1 = ( pnode + 18 ); tmp->node2 = ( pnode + 24); }
        else if(i==30) { tmp->node1 = ( pnode + 19 ); tmp->node2 = ( pnode + 25); }
        else if(i==31) { tmp->node1 = ( pnode + 20 ); tmp->node2 = ( pnode + 26); }
        else if(i==32) { tmp->node1 = ( pnode + 21 ); tmp->node2 = ( pnode + 27); }
        else if(i==33) { tmp->node1 = ( pnode + 22 ); tmp->node2 = ( pnode + 28); }
        else if(i==34) { tmp->node1 = ( pnode + 23 ); tmp->node2 = ( pnode + 29); }
        else if(i==35) { tmp->node1 = ( pnode + 24 ); tmp->node2 = ( pnode + 25); }//50%
        else if(i==36) { tmp->node1 = ( pnode + 26 ); tmp->node2 = ( pnode + 27); }
        else if(i==37) { tmp->node1 = ( pnode + 24 ); tmp->node2 = ( pnode + 30); }
        else if(i==38) { tmp->node1 = ( pnode + 25 ); tmp->node2 = ( pnode + 31); }
        else if(i==39) { tmp->node1 = ( pnode + 26 ); tmp->node2 = ( pnode + 32); }
        else if(i==40) { tmp->node1 = ( pnode + 27 ); tmp->node2 = ( pnode + 33); }
        else if(i==41) { tmp->node1 = ( pnode + 28 ); tmp->node2 = ( pnode + 34); }
        else if(i==42) { tmp->node1 = ( pnode + 29 ); tmp->node2 = ( pnode + 35); }
        else if(i==43) { tmp->node1 = ( pnode + 30 ); tmp->node2 = ( pnode + 31); }
        else if(i==44) { tmp->node1 = ( pnode + 32 ); tmp->node2 = ( pnode + 33); }
        else if(i==45) { tmp->node1 = ( pnode + 34 ); tmp->node2 = ( pnode + 35); }
        else if(i==46) { tmp->node1 = ( pnode + 30 ); tmp->node2 = ( pnode + 36); }
        else if(i==47) { tmp->node1 = ( pnode + 31 ); tmp->node2 = ( pnode + 37); }
        else if(i==48) { tmp->node1 = ( pnode + 32 ); tmp->node2 = ( pnode + 38); }
        else if(i==49) { tmp->node1 = ( pnode + 33 ); tmp->node2 = ( pnode + 39); }
        else if(i==50) { tmp->node1 = ( pnode + 34 ); tmp->node2 = ( pnode + 40); }
        else if(i==51) { tmp->node1 = ( pnode + 35 ); tmp->node2 = ( pnode + 41); }
        else if(i==52) { tmp->node1 = ( pnode + 37 ); tmp->node2 = ( pnode + 38); }
        else if(i==53) { tmp->node1 = ( pnode + 39 ); tmp->node2 = ( pnode + 40); }//75%
        else if(i==54) { tmp->node1 = ( pnode + 36 ); tmp->node2 = ( pnode + 42); }
        else if(i==55) { tmp->node1 = ( pnode + 37 ); tmp->node2 = ( pnode + 43); }
        else if(i==56) { tmp->node1 = ( pnode + 38 ); tmp->node2 = ( pnode + 44); }
        else if(i==57) { tmp->node1 = ( pnode + 39 ); tmp->node2 = ( pnode + 45); }
        else if(i==58) { tmp->node1 = ( pnode + 40 ); tmp->node2 = ( pnode + 46); }
        else if(i==59) { tmp->node1 = ( pnode + 41 ); tmp->node2 = ( pnode + 47); }
        else if(i==60) { tmp->node1 = ( pnode + 42 ); tmp->node2 = ( pnode + 43); }
        else if(i==61) { tmp->node1 = ( pnode + 44 ); tmp->node2 = ( pnode + 45); }
        else if(i==62) { tmp->node1 = ( pnode + 46 ); tmp->node2 = ( pnode + 47); }
        else if(i==63) { tmp->node1 = ( pnode + 43 ); tmp->node2 = ( pnode + 48); }
        else if(i==64) { tmp->node1 = ( pnode + 44 ); tmp->node2 = ( pnode + 49); }
        else if(i==65) { tmp->node1 = ( pnode + 45 ); tmp->node2 = ( pnode + 50); }
        else if(i==66) { tmp->node1 = ( pnode + 46 ); tmp->node2 = ( pnode + 51); }
        else if(i==67) { tmp->node1 = ( pnode + 48 ); tmp->node2 = ( pnode + 49); }
        else if(i==68) { tmp->node1 = ( pnode + 50 ); tmp->node2 = ( pnode + 51); }
        else if(i==69) { tmp->node1 = ( pnode + 49 ); tmp->node2 = ( pnode + 52); }
        else if(i==70) { tmp->node1 = ( pnode + 50 ); tmp->node2 = ( pnode + 53); }
        else if(i==71) { tmp->node1 = ( pnode + 52 ); tmp->node2 = ( pnode + 53); }//100%

    }

    return p_ret;
}


void normal_init( node *pn , tile *pt , road *pr)
{
    // pn = init_node();
    // pt = init_tile(pn);
    // pr = init_road(pn);
    
}