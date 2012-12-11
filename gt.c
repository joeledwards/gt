/*
 * gt - a git launcher
 *
 * Copyright 2012 by Joel Edwards <joeledwards@gmail.com>
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting documentation.  No representations are made about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#define GIT_NAME "git"

#ifndef GT_SPEED
#define GT_SPEED 50
#endif

int  term_width(void);
void init_space(void);
void move_to_top(void);
void line_at(int start_x, const char *s);
void draw_car(int x);
void clear_car(int x);

int TERM_WIDTH;
int SLEEP_DELAY;

int main(int argc, char **argv)
{
    (void) argc;
    int i;
    TERM_WIDTH = term_width();
    SLEEP_DELAY = 1000000 / (TERM_WIDTH + GT_SPEED);
    
    init_space();
    for (i = TERM_WIDTH; i > -85; i--) {
        draw_car(i);
        usleep(SLEEP_DELAY);
        clear_car(i);
    }
    char *git_path = getenv("GIT");
    if (git_path) {
      execv(git_path, argv);
    } else {
      execvp(GIT_NAME, argv);
    }
    /* error in exec if we land here */
    perror(GIT_NAME);
    return 1;
}

int term_width(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void init_space(void)
{
    puts("\n\n\n\n\n\n\n\n\n\n"); /* 10 lines */
}

void move_to_top(void)
{
    printf("\033[10A");
}

void line_at(int start_x, const char *s)
{
    int x;
    size_t i;
    if (start_x > 1)
        printf("\033[%dC", start_x);
    for (x = start_x, i = 0; i < strlen(s); x++, i++) {
        if (x > 0 && x < TERM_WIDTH)
            putchar(s[i]);
    }
    putchar('\n');
}

void draw_car(int x)
{
    line_at(x, "                                       ______________");
    line_at(x, "                                  _.-''         || \\ `-.");
    line_at(x, "                             _.-''              ||   \\  `-._       -=====/");
    line_at(x, "                   _____..-''.<(]_______________||_____\\    `-------/--/.");
    line_at(x, "         _..---''''__      /  ``     ____________|__________.....________\\");
    if (x % 2) {
    line_at(x, "   _.-'''__.-.='_`_`-.\\---|---'''''''       ` `  |   __  /.-'_`_`-.\\      \\.");
    line_at(x, " .' --''' .'/ /  |  \\ \\`. |    Pontiac GT       /   '='.'/ /\\ | /\\ \\`.  __.|");
    line_at(x, " |--------|| |``-O-''| ||--\\-------------------/-------|| |''-O-``| ||''  /");
    line_at(x, " '''----..| \\ \\/_ _\\/ / |______________________________| \\ \\ _|_ / / `--'\"");
    line_at(x, "             `-.....-'                                    `-.....-'");
    } else {
    line_at(x, "   _.-'''__.-.='_`_`-.\\---|---'''''''       ` `  |   __  /.-'_`_`-.\\      \\.");
    line_at(x, " .' --''' .'/ /\\   /\\ \\`. |   Pontiac GT        /   '='.'/ /  |  \\ \\`.  __.|");
    line_at(x, " |--------|| |''-O-``| ||--\\-------------------/-------|| |``-O-''| ||''  /");
    line_at(x, " '''----..| \\ \\ _|_ / / |______________________________| \\ \\/_ _\\/ / `--'\"");
    line_at(x, "             `-.....-'                                    `-.....-'");
    }
}

void clear_car(int x)
{
    move_to_top();
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
    line_at(x, "  ");
}

