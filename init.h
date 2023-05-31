#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

node *init_node();

tile *init_tile( node *pnode );

road *init_road( node *pnode );

void normal_init( node *pn , tile *pt , road *pr);