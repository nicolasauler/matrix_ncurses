#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"
#include "ui.h"

#define NUM_DRIPS 250
#define PROB_DRIP_SPAWN 0.65
#define PROB_DIMMING 0.55
#define PROB_CHANGE 0.95
#define RANDOM_PRINTABLE_CHARACTER (unsigned int)(33 + (rand() % 80))
/* tentar trocar por uma palavra, tipo "FELIZ" */

typedef struct
{
    int x,y;
    bool live;
    bool bright;
} drip;

drip drips[NUM_DRIPS];

cell matrix[MAXX][MAXY];

static double rand01()
{
    return((double) rand()/ (double)RAND_MAX);
}

static void init_drips()
{
    int i;
    for(i = 0; i < NUM_DRIPS; i++)
    {
        drips[i].live = false;
    }
}

void matrix_init()
{
    int x, y;

    /* set the matrix all to black */
    for(x = 0; x < MAXX; x++)
    {
        for(y = 0; y < MAXY; y++)
        {
            matrix[x][y].char_value = 0;
            matrix[x][y].intensity = 0;
        }
    }

    /* init the drips */
    init_drips();
}

static void fade_n_change_matrix()
{
    int x, y;

    for(x = 0; x < MAXX; x++)
    {
        for(y = 0; y < MAXY; y++)
        {
            /* randomly change characters -- even invisible ones */
            if((rand01() < PROB_CHANGE) || matrix[x][y].char_value == 0)
            {
                matrix[x][y].char_value = RANDOM_PRINTABLE_CHARACTER;
            }

            /* randomly dimm the cells */
            if(rand01() < PROB_DIMMING)
            {
                if(matrix[x][y].intensity > 0)
                {
                    matrix[x][y].intensity--;
                }
            }
        }
    }
}

static void try_add_drips()
{
    int i;
    for(i = 0; i < NUM_DRIPS; i++)
    {
        if(drips[i].live == false)
        {
            drips[i].live = true;
            drips[i].x = (rand() % MAXX);
            drips[i].y = 0; /* start at the top */
            /* drips[i].y = rand() % MAXY to start at the middle */
            drips[i].bright = 1/*(rand() % 2)*/;
            return; /* only add a drip */
        }
    }
}

static void update_drips()
{
    FILE *fp;
    int i;
    fp = fopen("output.txt", "w");
    for(i = 0; i < NUM_DRIPS; i++)
    {
        if(drips[i].live)
        {
            if(drips[i].bright)
            {
                matrix[drips[i].x][drips[i].y].intensity = MAX_INTENSITY;
                fprintf(fp, "%d ", matrix[drips[i].x][drips[i].y].intensity);
            }
            else
            {
                matrix[drips[i].x][drips[i].y].intensity = MIN_INTENSITY;
            }

            /* drips die when hit bottom of screen */
            if(++drips[i].y >= (MAXY - 1))
            {
                drips[i].live = false;
            }
        }
    }
}

void matrix_update()
{
    if(rand01() < PROB_DRIP_SPAWN)
    {
        try_add_drips();
    }
    update_drips();

    fade_n_change_matrix();
}
