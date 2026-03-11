#include "console-interface.h"

#include "alphabet.h"
#include "default-size.h"

int game(t_maze *maze, t_cave *cave, t_Qtable **qtable) {
  window_display win_display = {NULL};
  init_library();
  front_body(&win_display);

  wrefresh(win_display.TV);
  wrefresh(win_display.field);
  wrefresh(win_display.display);
  wrefresh(win_display.control);

  menu(&win_display, maze, cave, qtable);

  delwin(win_display.control_x);
  delwin(win_display.control_y);
  delwin(win_display.control);
  delwin(win_display.display);
  delwin(win_display.field);
  delwin(win_display.TV);
  delwin(stdscr);
  endwin();

  return 0;
}

void init_library() {
  initscr();
  noecho();
  curs_set(0);
  // nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  // raw(); // Убирает комбинацию ctr + c
  n_color();

  refresh();
}

void n_color() {
  start_color();
  init_color(100, 866, 753, 517);  // цвет - светло оранж
  init_color(101, 700, 700, 700);  // цвет - светлосерый
  init_color(102, 560, 337, 227);  // цвет - светло-коричневый
  init_color(103, 270, 192, 149);  // цвет - коричневый
  init_color(104, 184, 98, 43);  // цвет - коричневый (темно)
  init_color(105, 133, 126, 208);  // цвет - ТЕМНО синий
  init_color(106, 100, 100, 200);  // цвет - ТЕМНО синий
  init_color(107, 960, 51, 403);   // цвет - красный
  init_color(108, 137, 619, 866);  // цвет - синий
  init_color(109, 0, 1000, 0);     // цвет - зеленый
  init_color(110, 1000, 0, 1000);  // цвет - фиолетовый

  init_pair(1, COLOR_BLACK, COLOR_WHITE);  // цвет фона - белый
  init_pair(2, COLOR_WHITE, COLOR_BLACK);  // цвет фона - черный

  init_pair(3, COLOR_BLACK, 100);  // цвет фона - светло оранж
  init_pair(4, COLOR_BLACK, 101);  // цвет фона - светлосерый
  init_pair(5, COLOR_WHITE, 102);  // цвет фона - светло-коричневый
  init_pair(6, COLOR_BLACK, 103);  // цвет фона - коричневый
  init_pair(7, COLOR_BLACK, 104);  // цвет фона - коричневый (темно)
  init_pair(8, COLOR_GREEN, 105);   // цвет фона - ТЕМНО синий
  init_pair(9, COLOR_GREEN, 106);   // цвет фона - ТЕМНО синий
  init_pair(10, COLOR_WHITE, 107);  // цвет фона - красный
  init_pair(11, COLOR_WHITE, 108);  // цвет фона - синий
  init_pair(12, COLOR_BLACK, 109);  // цвет фона - зеленый
  init_pair(13, COLOR_BLACK, 110);  // цвет фона - фиолетовый

  bkgd(COLOR_PAIR(3));
}

void front_body(window_display *win_display) {
  init_window_TV(&win_display->TV);

  init_window_field(&win_display->field, win_display->TV);
  init_window_display(&win_display->display, win_display->field);

  init_window_control(&win_display->control, win_display->TV,
                      win_display->display);

  init_window_control_y(&win_display->control_y, win_display->control);
  init_window_control_x(&win_display->control_x, win_display->control);

  // update_control_yx(&win_display->control_y);
}

// TV
void init_window_TV(WINDOW **TV) {
  int max_height = 0, max_width = 0, x = 0, y = 0;
  getmaxyx(stdscr, max_height, max_width);
  x = (max_width - WIDTH_TV) / 2;
  y = (max_height - HEIGHT_TV) / 2;

  *TV = newwin(HEIGHT_TV, WIDTH_TV, y < 0 ? 1 : y, x < 0 ? 1 : x);
  wbkgd(*TV, COLOR_PAIR(4));
  print_window_TV(TV);
}

void print_window_TV(WINDOW **TV) {
  wattron(*TV, COLOR_PAIR(3));
  for (int i = 0; i < WIDTH_TV; i += WIDTH_TV - 4)
    for (int j = 0; j < HEIGHT_TV; j += HEIGHT_TV - 2)
      for (int xx = 0; xx < 4; xx++)
        for (int yy = 0; yy < 2; yy++)
          mvwprintw(*TV, yy + j, xx + i, "%c", ' ');
  wattroff(*TV, COLOR_PAIR(3));
  wattron(*TV, COLOR_PAIR(2));

  for (int i = 4; i < WIDTH_TV - 4; i++) {
    mvwprintw(*TV, 0, i, "%c", ' ');
    mvwprintw(*TV, HEIGHT_TV - 1, i, "%c", ' ');
  }

  for (int i = 2; i < HEIGHT_TV - 2; i++) {
    mvwprintw(*TV, i, 0, "%s", "  ");
    mvwprintw(*TV, i, WIDTH_TV - 2, "%s", "  ");
  }
  mvwprintw(*TV, 1, 2, "%s", "  ");
  mvwprintw(*TV, 1, WIDTH_TV - 4, "%s", "  ");
  mvwprintw(*TV, HEIGHT_TV - 2, 2, "%s", "  ");
  mvwprintw(*TV, HEIGHT_TV - 2, WIDTH_TV - 4, "%s", "  ");
  wattroff(*TV, COLOR_PAIR(2));

  wrefresh(*TV);
}

// field display
void init_window_field(WINDOW **field, WINDOW *TV) {
  int parent_x = 0, parent_y = 0;
  getbegyx(TV, parent_y, parent_x);
  *field = subwin(TV, HEIGHT_FIELD + 6, WIDTH_FIELD + 12, parent_y + 3,
                  parent_x + 6);
  wbkgd(*field, COLOR_PAIR(5));
  print_window_field(field, TV);
}

void print_window_field(WINDOW **field, WINDOW *TV) {
  wattron(*field, COLOR_PAIR(2));

  for (int i = 4; i < WIDTH_FIELD + 4; i++) {
    mvwprintw(*field, 0 + 1, i + 2, "%c", ' ');
    mvwprintw(*field, HEIGHT_FIELD + 3 + 1, i + 2, "%c", ' ');
  }

  for (int i = 2; i < HEIGHT_FIELD + 2; i++) {
    mvwprintw(*field, i + 1, 0 + 2, "%s", "  ");
    mvwprintw(*field, i + 1, WIDTH_FIELD + 6 + 2, "%s", "  ");
  }

  mvwprintw(*field, 1 + 1, 2 + 2, "%s", "  ");
  mvwprintw(*field, 1 + 1, WIDTH_FIELD + 4 + 2, "%s", "  ");
  mvwprintw(*field, HEIGHT_FIELD + 2 + 1, 2 + 2, "%s", "  ");
  mvwprintw(*field, HEIGHT_FIELD + 2 + 1, WIDTH_FIELD + 4 + 2, "%s", "  ");

  wattroff(*field, COLOR_PAIR(2));
  wattron(TV, COLOR_PAIR(2));
  for (int i = 6; i < WIDTH_FIELD + 18; i++) {
    mvwprintw(TV, 2, i, "%c", ' ');
    mvwprintw(TV, 59, i, "%c", ' ');
  }

  for (int i = 3; i < HEIGHT_TV - 3; i++) {
    mvwprintw(TV, i, 4, "%s", "  ");
    mvwprintw(TV, i, 168, "%s", "  ");
  }
  wattroff(TV, COLOR_PAIR(2));
}

// display

void init_window_display(WINDOW **display, WINDOW *field) {
  int parent_x = 0, parent_y = 0;
  getbegyx(field, parent_y, parent_x);
  *display = subwin(field, HEIGHT_DISPLAY + 2, WIDTH_DISPLAY + 4, parent_y + 2,
                    parent_x + 4);
  wbkgd(*display, COLOR_PAIR(1));
}

void display_update(t_maze *maze, WINDOW *display) {
  clear_display(display);

  for (int i = 0; i < maze->n; ++i) {
    for (int j = 0; j < maze->m; ++j) {
      cell(maze, i, j, display, 1);
    }
  }

  wrefresh(display);
}

void display_update_cave(t_cave *cave, WINDOW *display) {
  for (int i = 0; i < cave->n; ++i) {
    for (int j = 0; j < cave->m; ++j) {
      cell_cave(cave, i, j, display, 7);
    }
  }

  wrefresh(display);
}

void clear_display(WINDOW *display) {
  for (int i = 0; i < 50; ++i) {
    for (int j = 0; j < 50; ++j) {
      mvwprintw(display, i + 1, j * 3 + 2, "%s", "   ");
    }
  }

  for (int i = 0; i < 50; i++) {
    mvwprintw(display, 0, i * 3 + 2, "%s", "   ");
    mvwprintw(display, i + 1, 1, "%c", ' ');
  }
  wrefresh(display);
}

// control

void init_window_control(WINDOW **control, WINDOW *TV, WINDOW *display) {
  int parent_x = 0, parent_y = 0;
  getbegyx(display, parent_y, parent_x);
  *control = subwin(TV, HEIGHT_CONTROL, WIDTH_CONTROL, parent_y - 2,
                    parent_x + WIDTH_DISPLAY + 12);

  wbkgd(*control, COLOR_PAIR(8));

  wattron(TV, COLOR_PAIR(2));
  for (int i = 2; i < WIDTH_CONTROL - 2; i++) {
    mvwprintw(TV, 2, WIDTH_FIELD + 22 + i, "%c", ' ');
    mvwprintw(TV, HEIGHT_CONTROL + 3, WIDTH_FIELD + 22 + i, "%c", ' ');
  }

  for (int i = 0; i < HEIGHT_CONTROL; i++) {
    mvwprintw(TV, i + 3, WIDTH_FIELD + 22, "%s", "  ");
    mvwprintw(TV, i + 3, WIDTH_FIELD + 20 + WIDTH_CONTROL, "%s", "  ");
  }
  wattroff(TV, COLOR_PAIR(2));

  wattron(*control, COLOR_PAIR(6));
  for (int i = 0; i < 20; i += 4) {
    for (int j = 2; j < WIDTH_CONTROL - 2; j++) {
      mvwprintw(*control, HEIGHT_CONTROL + 2 - i, j, "%c", ' ');
      mvwprintw(*control, HEIGHT_CONTROL + 2 - i + 1, j, "%c", ' ');
    }
  }
  wattroff(*control, COLOR_PAIR(6));
  wattron(*control, COLOR_PAIR(7));
  for (int i = 2; i < 22; i += 4) {
    for (int j = 2; j < WIDTH_CONTROL - 2; j++) {
      mvwprintw(*control, HEIGHT_CONTROL + 2 - i, j, "%c", ' ');
      mvwprintw(*control, HEIGHT_CONTROL + 2 - i + 1, j, "%c", ' ');
    }
  }
  wattroff(*control, COLOR_PAIR(7));
}

// control_y

void init_window_control_y(WINDOW **control_y, WINDOW *control) {
  int parent_x = 0, parent_y = 0;
  getbegyx(control, parent_y, parent_x);
  *control_y =
      subwin(control, WIDTH_CONTROL / 2 + 2, WIDTH_CONTROL, parent_y, parent_x);
  print_rheostat(*control_y);
  print_ctr_display_board(*control_y);
  // wbkgd(*control_y, COLOR_PAIR(6));
}

void init_window_control_x(WINDOW **control_x, WINDOW *control) {
  int parent_x = 0, parent_y = 0;
  getbegyx(control, parent_y, parent_x);
  *control_x = subwin(control, WIDTH_CONTROL / 2 + 2, WIDTH_CONTROL,
                      parent_y + WIDTH_CONTROL / 2 + 2, parent_x);
  print_rheostat(*control_x);
  print_ctr_display_board(*control_x);
}

void update_control_yx(WINDOW **control_yx, byte num) {
  clear_ctr_pos(*control_yx);
  print_ctr_pos(*control_yx, num % 8);
  print_ctr_display(*control_yx, num);

  wrefresh(*control_yx);
}

void print_rheostat(WINDOW *control_y) {
  int dis[15][15] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                     {0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
                     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                     {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                     {0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
                     {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      int color = dis[i][j];
      if (color) {
        wattron(control_y, COLOR_PAIR(color == 1 ? 3 : 5));
        mvwprintw(control_y, i, j * 2 + 2, "%s", "  ");
        wattroff(control_y, COLOR_PAIR(color == 1 ? 3 : 5));
      }
    }
  }
}

void print_number(WINDOW *display, int y, int x, int num) {
  int coor_x = x + 27;
  wattron(display, COLOR_PAIR(5));
  for (int i = 0, shift = 3; i < 9; i++, shift += 3) {
    int digit = num % 10;
    num /= 10;
    if (i == 6) {
      shift += 2;
      wattroff(display, COLOR_PAIR(5));
      wattron(display, COLOR_PAIR(3));
    }
    for (int n = 0; n < 4; n++)
      for (int m = 0; m < 3; m++)
        mvwprintw(display, y + n, x + m + coor_x - shift, "%c",
                  clock_face(digit, n, m));
  }
  wattroff(display, COLOR_PAIR(3));

  wrefresh(display);
}
void print_alive_number(WINDOW *display, int y, int x, int num) {
  int coor_x = x + 6;
  wattron(display, COLOR_PAIR(5));
  for (int i = 0, shift = 3; i < 2; i++, shift += 3) {
    int digit = num % 10;
    num /= 10;
    for (int n = 0; n < 4; n++)
      for (int m = 0; m < 3; m++)
        mvwprintw(display, y + n, m + coor_x - shift, "%c",
                  clock_face(digit, n, m));
  }
  wattroff(display, COLOR_PAIR(5));

  wrefresh(display);
}

void print_manual(WINDOW *display) {
  write_str(display, 6, 35, "choose the size of the maze", 1);
  write_str(display, 15, 40, " left  ", 3);
  write_str(display, 15, 70, "decrease value", 1);

  write_str(display, 20, 40, " right ", 3);
  write_str(display, 20, 70, "increase value", 1);

  write_str(display, 25, 40, " up    ", 3);
  write_str(display, 25, 70, "change height", 1);

  write_str(display, 30, 40, " down  ", 3);
  write_str(display, 30, 70, "change width", 1);

  write_str(display, 35, 40, " enter ", 3);
  write_str(display, 35, 70, "maze generation", 1);

  write_str(display, 40, 40, " B     ", 3);
  write_str(display, 40, 70, "open menu", 1);
}

void print_download(WINDOW *display) {
  write_str(display, 15, 28, " There are no files to download ", 5);

  write_str(display, 23, 44, "You can create a map", 1);
  write_str(display, 27, 56, "in the menu", 1);

  write_str(display, 40, 60, " b ", 3);
  write_str(display, 40, 75, "exit", 1);
}

void print_download_control(WINDOW *display) {
  write_str(display, 40, 50, " d ", 3);
  write_str(display, 40, 65, "delete file", 1);

  write_str(display, 45, 60, " b ", 3);
  write_str(display, 45, 75, "menu", 1);
}

void print_download_last_page(WINDOW *display) {
  write_str(display, 15, 37, " There are no more files ", 5);

  write_str(display, 23, 50, "Scroll back pages", 1);
  write_str(display, 27, 72, "or", 1);
  write_str(display, 31, 60, "go to menu", 1);

  write_str(display, 40, 60, " b ", 3);
  write_str(display, 40, 75, "menu", 1);
}

void print_access(WINDOW *display) {
  write_str(display, 15, 29, " Labyrinth or cave is not load ", 5);

  write_str(display, 23, 30, "You can create or upload a map", 1);
  write_str(display, 27, 56, "in the menu", 1);

  write_str(display, 40, 60, " b ", 3);
  write_str(display, 40, 75, "menu", 1);
}

void print_rule_maze(WINDOW *display) {
  write_str(display, 15, 55, "   ", 10);
  write_str(display, 15, 70, "start", 1);

  write_str(display, 20, 55, "   ", 11);
  write_str(display, 20, 70, "finish", 1);

  write_str(display, 35, 40, "press", 1);
  write_str(display, 35, 60, " enter ", 3);
  write_str(display, 35, 85, "to start", 1);

  write_str(display, 40, 45, "press", 1);
  write_str(display, 40, 65, " b ", 3);
  write_str(display, 40, 80, "to exit", 1);
}

void print_loading(WINDOW *display) {
  write_str(display, 18, 43, "                      ", 11);
  write_str(display, 22, 43, "                      ", 11);
  write_str(display, 26, 43, "                      ", 11);
  write_str(display, 29, 43, "                      ", 11);

  write_str(display, 19, 46, "                    ", 1);
  write_str(display, 22, 46, "  Machine learning  ", 1);
  write_str(display, 25, 46, "      loading       ", 1);
  write_str(display, 28, 46, "                    ", 1);
}

void print_no_way(WINDOW *display) {
  write_str(display, 18, 43, "                      ", 10);
  write_str(display, 22, 43, "                      ", 10);
  write_str(display, 26, 43, "                      ", 10);
  write_str(display, 29, 43, "                      ", 10);

  write_str(display, 19, 46, "                    ", 1);
  write_str(display, 22, 46, "   Path not found   ", 1);
  write_str(display, 25, 46, "    repeat again    ", 1);
  write_str(display, 28, 46, "                    ", 1);
}

void print_cave_size(WINDOW *display, logic *l) {
  write_str(display, 4, 110, " vertically ", l->switches ? 1 : 11);
  write_str(display, 22, 110, " horizontally ", l->switches ? 11 : 1);

  write_str(display, 6, 15, "choose the size of the cave", 1);
  write_str(display, 15, 20, " left  ", 3);
  write_str(display, 15, 50, "decrease value", 1);

  write_str(display, 20, 20, " right ", 3);
  write_str(display, 20, 50, "increase value", 1);

  write_str(display, 25, 20, " up    ", 3);
  write_str(display, 25, 50, "change height", 1);

  write_str(display, 30, 20, " down  ", 3);
  write_str(display, 30, 50, "change width", 1);

  write_str(display, 35, 20, " enter ", 3);
  write_str(display, 35, 50, "to next", 1);

  write_str(display, 40, 20, " B     ", 3);
  write_str(display, 40, 50, "open menu", 1);
}

void print_cave_alive_probability(WINDOW *display) {
  write_str(display, 8, 18, " Choose the chance of a cell appearing ", 1);
  write_str(display, 12, 56, " from 0 to 99 ", 1);

  write_str(display, 23, 69, "    ", 5);
  write_str(display, 27, 65, "percent", 1);

  write_str(display, 45, 42, "press enter to continue", 1);
}

void print_cave_birth_death(WINDOW *display, logic *l) {
  write_str(display, 4, 110, " birth ", l->switches ? 1 : 11);
  write_str(display, 22, 110, " death ", l->switches ? 11 : 1);

  write_str(display, 6, 15, "choose the size of the cave", 1);
  write_str(display, 15, 20, " left  ", 3);
  write_str(display, 15, 50, "decrease value", 1);

  write_str(display, 20, 20, " right ", 3);
  write_str(display, 20, 50, "increase value", 1);

  write_str(display, 25, 20, " up    ", 3);
  write_str(display, 25, 50, "change birth", 1);

  write_str(display, 30, 20, " down  ", 3);
  write_str(display, 30, 50, "change death", 1);

  write_str(display, 35, 20, " enter ", 3);
  write_str(display, 35, 50, "to next", 1);

  write_str(display, 40, 20, " B     ", 3);
  write_str(display, 40, 50, "open menu", 1);
}

void print_cave_step_mode(WINDOW *display) {
  write_str(display, 8, 36, " select step by step mode ", 1);
  write_str(display, 45, 42, "press enter to continue", 1);
}

void print_cave_rendering_time(WINDOW *display) {
  write_str(display, 8, 36, " select step by step mode ", 1);

  write_str(display, 23, 40, "sec", 1);
  write_str(display, 23, 95, "microseconds", 1);

  write_str(display, 45, 42, "press enter to continue", 1);
}

void print_screensaver(WINDOW *display) {
  for (int i = 0; i < 44; i += 4) {
    write_str(display, i + 1, 0 + 2, "        ", 0);
    write_str(display, i + 1, 25 + 2, "        ", 3);
    write_str(display, i + 1, 50 + 2, "        ", 12);
    write_str(display, i + 1, 75 + 2, "        ", 10);
    write_str(display, i + 1, 100 + 2, "        ", 13);
    write_str(display, i + 1, 125 + 2, "        ", 11);
  }
  write_str(display, 44, 0 + 2, "        ", 11);
  write_str(display, 44, 25 + 2, "        ", 13);
  write_str(display, 44, 50 + 2, "        ", 10);
  write_str(display, 44, 75 + 2, "        ", 12);
  write_str(display, 44, 100 + 2, "        ", 3);
  write_str(display, 44, 125 + 2, "        ", 0);

  write_str(display, 47, 0 + 2, "        ", 9);
  write_str(display, 47, 25 + 2, "        ", 8);
  write_str(display, 47, 50 + 2, "        ", 7);
  write_str(display, 47, 75 + 2, "        ", 6);
  write_str(display, 47, 100 + 2, "        ", 5);
  write_str(display, 47, 125 + 2, "        ", 4);

  write_str(display, 20, 60, "          ", 2);
  write_str(display, 22, 60, "          ", 2);
  write_str(display, 21, 60, "   maze   ", 2);
}