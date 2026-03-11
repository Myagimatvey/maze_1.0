#ifndef CONSOLE_INTERFACE_H
#define CONSOLE_INTERFACE_H

#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "../maze.h"

typedef struct {
  WINDOW *TV;
  WINDOW *field;
  WINDOW *display;
  WINDOW *control;
  WINDOW *control_y;
  WINDOW *control_x;
} window_display;

typedef enum {
  Start,
  M_Options,
  M_Download,
  M_Orient,
  M_learn,
  C_Generate,
  C_Download,
} fsm;

typedef struct {
  int y;
  int x;
  int n_coor;
  t_point start;
  t_point finish;
} Coor;

typedef struct {
  fsm stage;
  int switches;
  char menu_list[3][5][11];
  int i;
  int choice;
  t_maze *m_t;
  int access_m;
  Coor coor;
  int page;
  int cave_stage;
} logic;

int game(t_maze *maze, t_cave *cave, t_Qtable **qtable);
void init_library();
void n_color();

// меню

int menu(window_display *win_display, t_maze *maze, t_cave *cave,
         t_Qtable **qtable);
void check_menu(window_display *win_display, t_maze *maze, t_cave *cave,
                t_Qtable **qtable, logic *l);

void check_menu_start(window_display *win_display, logic *l, int *ch);
void check_menu_start_process(window_display *win_display, logic *l, int *ch);
void check_menu_start_tap(window_display *win_display, logic *l);
void call_rendering_menu(window_display *win_display, t_maze *maze, logic *l,
                         int *ch);

void ctr_switches(window_display *win_display, t_maze *maze, logic *l, int ch);

void maze_download(window_display *win_display, t_maze *maze, logic *l,
                   int *ch);
void maze_download_check(DIR *dir, t_maze *maze, window_display *win_display,
                         logic *l, int *ch);
void maze_download_pagination(window_display *win_display, logic *l, int *ch);

void maze_way(window_display *win_display, t_maze *maze, logic *l, int *ch);
void maze_way_check(window_display *win_display, t_maze *maze, logic *l,
                    int *ch);
void maze_way_choice(window_display *win_display, t_maze *maze, logic *l,
                     int *ch);
void maze_way_rendering(window_display *win_display, t_maze *maze, logic *l);

void maze_learn(window_display *win_display, t_maze *maze, t_Qtable **qtable,
                logic *l, int *ch);
void maze_learn_check(window_display *win_display, t_maze *maze,
                      t_Qtable **qtable, logic *l, int *ch);
void maze_learn_rendering(window_display *win_display, t_maze *maze,
                          t_Qtable **qtable, logic *l);

void cave_start(window_display *win_display, t_cave *cave, logic *l, int *ch);
void cave_rendering(window_display *win_display, t_cave *cave, int *ch,
                    int step);
void cave_switches(window_display *win_display, t_cave *cave, logic *l,
                   int *ch);
void cave_alive_probability(window_display *win_display, t_cave *cave, logic *l,
                            int *ch);
void cave_birth_death_cells(window_display *win_display, byte *n, byte *m,
                            logic *l, int *ch);
void cave_step_mode(window_display *win_display, logic *l, int *ch);
void cave_rendering_step(window_display *win_display, t_cave *cave, int *ch);
void cave_rendering_time(window_display *win_display, t_cave *cave, int *ch);

void cave_download(window_display *win_display, t_cave *cave, logic *l,
                   int *ch);
void cave_download_check(DIR *dir, t_cave *cave, window_display *win_display,
                         logic *l, int *ch);

int menu_switching(logic *l, const int *ch);
void coor_switching(t_maze *maze, logic *l, const int *ch);
void switches(window_display *win_display, byte *n, byte *m, logic *l, int ch);
void switch_selection(logic *l, int ch);
// отрисовка

void front_body(window_display *win_display);

//

void init_window_TV(WINDOW **TV);
void print_window_TV(WINDOW **TV);

void init_window_field(WINDOW **field, WINDOW *TV);
void print_window_field(WINDOW **field, WINDOW *TV);

void init_window_display(WINDOW **display, WINDOW *field);
void display_update(t_maze *maze, WINDOW *field);
void display_update_cave(t_cave *cave, WINDOW *display);
void clear_display(WINDOW *display);

void init_window_control(WINDOW **control, WINDOW *field, WINDOW *display);
void init_window_control_y(WINDOW **control_y, WINDOW *control);
void init_window_control_x(WINDOW **control_x, WINDOW *control);

void update_control_yx(WINDOW **control_yx, byte num);

void cell(t_maze *maze, int y, int x, WINDOW *display, int color);
void cell_cave(t_cave *cave, int y, int x, WINDOW *display, int color);

void print_rheostat(WINDOW *control_y);
void print_number(WINDOW *display, int y, int x, int num);
void print_alive_number(WINDOW *display, int y, int x, int num);

void print_manual(WINDOW *display);
void print_download(WINDOW *display);
void print_download_control(WINDOW *display);
void print_download_last_page(WINDOW *display);
void print_access(WINDOW *display);
void print_rule_maze(WINDOW *display);
void print_loading(WINDOW *display);
void print_no_way(WINDOW *display);
void print_cave_size(WINDOW *display, logic *l);
void print_cave_alive_probability(WINDOW *display);
void print_cave_birth_death(WINDOW *display, logic *l);
void print_cave_step_mode(WINDOW *display);
void print_cave_rendering_time(WINDOW *display);
void print_screensaver(WINDOW *display);

void print_ctr_display(WINDOW *control, byte num);
void print_ctr_display_board(WINDOW *control);
void print_ctr_pos(WINDOW *control, int pos);
void clear_ctr_pos(WINDOW *control);
int ctr_pos_1(int y, int x);
int ctr_pos_2(int y, int x);
int ctr_pos_3(int y, int x);
int ctr_pos_4(int y, int x);
int ctr_pos_5(int y, int x);
int ctr_pos_6(int y, int x);
int ctr_pos_7(int y, int x);
int ctr_pos_8(int y, int x);
int ctr_pos_9(int y, int x);

int clock_face(int num, int y, int x);
#endif