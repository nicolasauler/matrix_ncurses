#include <ncurses.h>
#include "ui.h"

static void set_colors();

WINDOW *uiwindow = NULL;

short int color_map[MAX_INTENSITY+1] = {1,2,2,3,3,3,4,4,4,4,4,5,3,6};

static void set_colors()
{
    short int i;
    for(i = 0; i < 8; i++)
    {
        init_pair(i+1, i, COLOR_BLACK);
    }

    /* set shades of green */
    for(i = 0; i <= 5; i++)
    {
        init_color(i, 0, i*200, 0);
    }

    /* CHANGE 6 TO i */
    init_color(6, 800, 1000, 800);
}

bool init_ui()
{
    /* init curses */
    uiwindow = initscr();
    if(uiwindow == NULL)
    {
        return(false);
    }

    noecho(); /* don't echo keypresses */

    /* timeout(10);*/

    curs_set(FALSE);

    start_color();
    if((!has_colors()) || (!can_change_color()) || (COLOR_PAIRS < 6))
    {
        printf("Warning. Your terminal can't handle this bitch.\n");
        return(false);
    }

    set_colors();

    return(true);
}

void cleanup_ui()
{
    delwin(uiwindow);
    endwin();
    refresh();
}

void show_matrix()
{
    FILE *fp;
    int x,y;
    fp = fopen("output2.txt", "w");
    for(x = 0; x < MAXX; x++)
    {
        for(y = 0; y < MAXY; y++)
        {
            fprintf(fp, "%d ", color_map[matrix[x][y].intensity]);
            fprintf(fp, "\n%d ", color_map[13]);
            color_set(color_map[matrix[x][y].intensity], NULL);
            mvaddch(y,x,matrix[x][y].char_value);
        }
    }
    refresh();
}
