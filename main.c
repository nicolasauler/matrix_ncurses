#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "ui.h"
#include "matrix.h"

#define ITERATIONS 300
#define REFRESH_DELAY 50000000L

static int ui_refresh();

static int ui_refresh()
{
    struct timespec req, rem;
    req.tv_sec = 0;
    req.tv_nsec = REFRESH_DELAY;
    return(nanosleep(&req, &rem));
}

int main()
{
    int i;

    if(!init_ui())
    {
        return(EXIT_FAILURE);
    }

    matrix_init();

    for(i = 0; i < ITERATIONS; i++)
    {
        matrix_update();
        show_matrix();
        if(ui_refresh() == -1)
        {
            return(EXIT_FAILURE);
        }
    }

    cleanup_ui();
    return(EXIT_SUCCESS);
}
