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


