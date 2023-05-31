程設專題
===

###### tags: `final project` `C`

TODO
---
- [ ] Settlement build limit //max: 5
- [ ] Building index match with array:
    - [ ] select : 1 - 54 , array[54] //0-53
- [ ] resource limit (card pile)
- [ ] buy dev card
- [ ] use dev card
- [ ] Robber
    - [ ] steal from player
    - [ ] resource limit 



BEWARE
---
1. The index of resource in node is starts from 1
2.



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
    int32_t resource_type;//1-6(represents terrain also resources)
    int32_t robber;//0,1
    int32_t dice_num;//2-12
    struct _sNode* nodes[6]; 
}tile;

```

##### development card
Total : 25 cards
Player is able to buy any amount of development card but development card never go back to supply and player will not be able to buy if the supply is end

1. knight : 14 cards
2. road building: Immediatley place 2 roads
3. year of plenty: Immediatley take 2 cards from the supply stack
4. monoply : Select one resource and take it from other players
5. victory points : 5 cards


##### player 
``` C
enum Resource{ Brick = 0 , Grain , Sheep , Lumber , Ore };

typedef struct _sPlayer
{
    int32_t index;//0-3
    int32_t color;//0-3
    int32_t resource[5];//0-4
    int32_t victory_point;//0-10
    int32_t road_num;//0-15
    int32_t settlement_num;//0-5  
    int32_t building_index[54];//0-53 0,1,2
    int32_t city_num;//0-4
    int32_t knight_num;//0-5
    int32_t longest_road;//0,1
    int32_t largest_army;//0,1
}Player;
```

Playing Procedure
---

For every turn of each player, the procedure will break down into 4 states as the following list shows 

1. ROLLING DICE:
    As simple as it seems, the player will roll two dices of 6 to obtain resources.
    
2. CHECK STATE: 
     Checking whether the player is able to perform any of the 7 following options
- [ ] Buy development card
- [ ] Use development card
- [ ] Trade with other players
- [ ] Marine trade
- [ ] Build settlements
- [ ] Build city
- [ ] Build road


3. EXECUTE STATE:
    Any options that is offered and selected will be performed
    
4. GAMEOVER PENDING:
    After any option is successfully performed, the program will check if the winning condition is met, and thus end the game accordingly.

After all these states are over, depending on the player's status, the game will either go on to the next player or either the player voluntarily quit its turn and move on. 

* Beware that the states are not neccessarily performed in the preceeding sequent, for example,  one may use development card before rolling the dice.
    