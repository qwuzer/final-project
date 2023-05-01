程設專題
===

###### tags: `final project` `C`

basic implements
---
    19 terrain tiles
    6 sea frame pieces
    9 harbor pieces
    18 circular number tokens
    95 resource cards( brick , grain , wool , lumber , ore )
    25 development( 14 knight , 6 progress , 5 victory points )
    16 cities(4 of each color)
    20 settlements(5 of each color)
    60 roads
    2 dice
    1 robber
    
structures of basic components
---

##### settlement(city) struct
```Ｃ
typedef struct _sNode
{
    int32_t index;//1-54
    int32_t type;//0-1 
    int32_t owner;
    int32_t triangle_type;//right or left
    /* 
             1          3 
            /            \
      3 ㄧ *    or.       * ㄧ 1
           \            /
           2           2
    */
    //*directions of other node*/
    typedef struct _sNode* dir1;
    typedef struct _sNode* dir2;
    typedef struct _sNode* dir3;
    //*surronding tiles*//
    int32_t tile1;
    int32_t tile2;
    int32_t tile3;
}node;

```

##### tile(terrain)
``` C
enum TileType{ Tile-Hills = 1, Tile-Fields , Tile-Pasture, Tile-Forest, Tile-Mountains, Tile-Desert , Tile-Robber };

int32_t tile_type[19];//1-6
//{ 5 , 2 , 2 , 4 , 1 , 2 , 3 , 3 , .... };

int32_t tile_dice_num[18] = { 5 , 2 , 6 , 3 , 8 , 10 , 9 , 12 , 11 , 4 , 8 , 10 , 9 , 4 , 5 , 6 , 3 , 11 };//2-12
//{A-5} {B-2} {C-6} {D-3} {E-8} {F-10} {G-9} {H-12} {I-11} {J-4} {K-8} {L-10} {M-9} {N-4} {O-5} {P-6} {Q-3} {R-11} 

typedef struct _sTile
{
    int32_t index;//1-19
    int32_t type;//1-7
    int32_t robber;//0,1
    int32_t dice_num;//2-12
}tile;

```

