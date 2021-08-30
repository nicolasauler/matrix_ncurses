#ifndef _UI_H_
#define _UI_H_

#define MAXX 159
#define MAXY 41

#define MAX_INTENSITY 13
#define MIN_INTENSITY 2

#include <stdbool.h>

typedef struct
{
    unsigned int char_value;
    int intensity;
} cell;

/* extern - defined elsewhere (matrix.c) */
extern cell matrix[MAXX][MAXY];

/* prototypes */
bool init_ui(void);
void cleanup_ui(void);
void show_matrix(void);

#endif
