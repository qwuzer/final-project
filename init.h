#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "struct.h"


node *init_node();

tile *init_tile();

road *init_road();

void normal_init( node *pn , tile *pt , road *pr);