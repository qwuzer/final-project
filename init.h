#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "struct.h"


node *init_node();

card *init_card( card *pcard );

tile *init_tile( tile *ptile , node *pnode );

road *init_road( road *proad , node *pnode );

void normal_init( node *pn , tile *pt , road *pr);