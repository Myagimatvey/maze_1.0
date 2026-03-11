#include "../additional.h"
#include "alphabet.h"
#include "console-interface.h"

int menu(window_display *win_display, t_maze *maze, t_cave *cave,
         t_Qtable **qtable) {
  logic l = {.stage = Start,
             .switches = 0,
             .menu_list = {{"maze      ", "cave      ", "          ",
                            "          ", "exit      "},
                           {"generate  ", "load maze ", "find way  ",
                            "m learning", "back      "},
                           {"generate  ", "load cave ", "          ",
                            "          ", "back      "}},
             .i = 0,
             .choice = 0,
             .m_t = maze,
             .access_m = 0,
             .coor = {0, 0, 0, {0}, {0}},
             .page = 0,
             .cave_stage = 0};
  update_control_yx(&win_display->control_y, maze->n);
  update_control_yx(&win_display->control_x, maze->m);
  print_screensaver(win_display->display);
  napms(3000);
  clear_display(win_display->display);
  check_menu(win_display, maze, cave, qtable, &l);

  return 0;
}

void check_menu(window_display *win_display, t_maze *maze, t_cave *cave,
                t_Qtable **qtable, logic *l) {
  int ch = '\0';
  call_rendering_menu(win_display, maze, l, &ch);

  while (ch != 'q') {
    ch = getch();

    if (l->stage == Start) check_menu_start(win_display, l, &ch);

    if (l->stage == M_Options) ctr_switches(win_display, maze, l, ch);
    if (l->stage == M_Download) maze_download(win_display, maze, l, &ch);
    if (l->stage == M_Orient) maze_way(win_display, maze, l, &ch);
    if (l->stage == M_learn) maze_learn(win_display, maze, qtable, l, &ch);

    if (l->stage == C_Generate) cave_start(win_display, cave, l, &ch);
    if (l->stage == C_Download) cave_download(win_display, cave, l, &ch);

    if (ch == 'b') {
      l->stage = Start;
      l->i = 0;
      l->choice = 0;
      l->cave_stage = 0;
      ch = '\0';
      clear_display(win_display->display);
      call_rendering_menu(win_display, maze, l, &ch);
      free_Qtable(*qtable);
      *qtable = NULL;
    }
  }
}

void check_menu_start(window_display *win_display, logic *l, int *ch) {
  check_menu_start_process(win_display, l, ch);

  if (l->stage == Start)
    for (int i = 0; i < 5; i++) {
      write_str(win_display->display, 10 + (i * 4), 30, l->menu_list[l->i][i],
                l->choice == i ? 3 : 1);
    }
}

void check_menu_start_process(window_display *win_display, logic *l, int *ch) {
  menu_switching(l, ch);

  if (*ch == '\n') {
    if (l->i == 0 && l->choice == 4)
      *ch = 'q';
    else if (l->choice == 4) {
      l->i = 0;
      l->choice = 0;
      *ch = '\0';
    } else {
      check_menu_start_tap(win_display, l);
      l->i = l->choice + 1;
      l->choice = 0;
      *ch = '\0';
    }
  }
}

void check_menu_start_tap(window_display *win_display, logic *l) {
  clear_display(win_display->display);
  if (l->i == 1) {
    if (l->choice == 0) {
      l->stage = M_Options;
      print_manual(win_display->display);
    }
    if (l->choice == 1) {
      l->stage = M_Download;
      l->choice = 0;
      write_str(win_display->display, 45, 45, " b ", 3);
      write_str(win_display->display, 45, 60, "return to menu", 1);
    }
    if (l->choice == 2) {
      l->stage = M_Orient;
      l->coor.n_coor = 0;
    }
    if (l->choice == 3) {
      l->stage = M_learn;
      l->coor.n_coor = 0;
    }
  } else if (l->i == 2) {
    if (l->choice == 0) {
      l->stage = C_Generate;
    }

    if (l->choice == 1) {
      l->stage = C_Download;
      l->choice = 0;
    }
  }
}

void call_rendering_menu(window_display *win_display, t_maze *maze, logic *l,
                         int *ch) {
  check_menu_start(win_display, l, ch);
  update_control_yx(&win_display->control_y, maze->n);
  update_control_yx(&win_display->control_x, maze->m);
}

void ctr_switches(window_display *win_display, t_maze *maze, logic *l, int ch) {
  switches(win_display, &maze->n, &maze->m, l, ch);

  if (ch == '\n') {
    create_maze(maze);
    l->access_m = 1;
    display_update(maze, win_display->display);
  }
}

void maze_download(window_display *win_display, t_maze *maze, logic *l,
                   int *ch) {
  nodelay(stdscr, FALSE);
  DIR *dir = opendir("./mazes");
  if (dir == NULL) {
    write_str(win_display->display, 20, 50, "folder not found", 1);
    write_str(win_display->display, 24, 70, "404", 3);
  } else {
    maze_download_check(dir, maze, win_display, l, ch);
  }
  closedir(dir);
}

void maze_download_check(DIR *dir, t_maze *maze, window_display *win_display,
                         logic *l, int *ch) {
  struct dirent *entity = readdir(dir);
  int count_file = 0;
  maze_download_pagination(win_display, l, ch);
  for (int i = 0; i < (l->page * 5); i++) entity = readdir(dir);
  for (int i = 0; i < 5 && entity != NULL; i++) {
    if (strcmp(entity->d_name, ".gitkeep") != 0 && entity->d_type == 8) {
      if (*ch != '\n')
        write_str(win_display->display, (i * 4) + 10, 30, entity->d_name,
                  l->choice == i ? 3 : 1);
      if (l->choice == i) {
        char path[300] = {0};
        snprintf(path, sizeof(path), "./mazes/%s%c", entity->d_name, '\0');
        if (*ch == '\n') {
          if (!load_from_file(path, maze)) l->access_m = 1;
          display_update(maze, win_display->display);
        } else if (*ch == 'd') {
          remove(path);
          nodelay(stdscr, TRUE);
          *ch = '\0';
        }
      }
      count_file++;
    } else
      i--;
    entity = readdir(dir);
  }
  if (!count_file) {
    if (l->page != 0) {
      l->page = 0;
      print_download_last_page(win_display->display);
    } else
      print_download(win_display->display);
  } else if (*ch != '\n')
    print_download_control(win_display->display);
}

void maze_download_pagination(window_display *win_display, logic *l, int *ch) {
  clear_display(win_display->display);
  l->page += menu_switching(l, ch);
  l->page = l->page < 0 ? 0 : l->page;
}

void maze_way(window_display *win_display, t_maze *maze, logic *l, int *ch) {
  clear_display(win_display->display);
  if (!l->access_m)
    print_access(win_display->display);
  else
    maze_way_check(win_display, maze, l, ch);
}

void maze_way_check(window_display *win_display, t_maze *maze, logic *l,
                    int *ch) {
  if (l->coor.n_coor == 0) {
    print_rule_maze(win_display->display);
    if (*ch == '\n') {
      l->coor.n_coor++;
      *ch = '\0';
    }
  }
  if (l->coor.n_coor >= 1 && l->coor.n_coor <= 2)
    maze_way_choice(win_display, maze, l, ch);

  if (l->coor.n_coor == 3 && *ch != 'q' && *ch != 'b')
    maze_way_rendering(win_display, maze, l);
  wrefresh(win_display->display);
}

void maze_way_choice(window_display *win_display, t_maze *maze, logic *l,
                     int *ch) {
  coor_switching(maze, l, ch);
  display_update(maze, win_display->display);
  if (*ch == '\n') {
    if (l->coor.n_coor == 1) {
      l->coor.start.y = l->coor.y;
      l->coor.start.x = l->coor.x;
    } else {
      l->coor.finish.y = l->coor.y;
      l->coor.finish.x = l->coor.x;
    }
    l->coor.n_coor++;
  }

  cell(maze, l->coor.y, l->coor.x, win_display->display,
       l->coor.n_coor == 1 ? 10 : 11);
}

void maze_way_rendering(window_display *win_display, t_maze *maze, logic *l) {
  display_update(maze, win_display->display);
  t_point *path = get_route_maze(maze, l->coor.start, l->coor.finish);
  for (int i = 0; path != NULL && path[i].y != -1; i++) {
    cell(maze, path[i].y, path[i].x, win_display->display, 10);
    napms(100);
    wrefresh(win_display->display);
  }

  if (path != NULL)
    free(path);
  else
    print_no_way(win_display->display);

  l->coor.n_coor = 0;
}

void maze_learn(window_display *win_display, t_maze *maze, t_Qtable **qtable,
                logic *l, int *ch) {
  clear_display(win_display->display);
  if (!l->access_m)
    print_access(win_display->display);
  else
    maze_learn_check(win_display, maze, qtable, l, ch);
}

void maze_learn_check(window_display *win_display, t_maze *maze,
                      t_Qtable **qtable, logic *l, int *ch) {
  if (l->coor.n_coor == 0) {
    print_rule_maze(win_display->display);
    if (*ch == '\n') {
      l->coor.n_coor++;
      *ch = '\0';
    }
  }

  if (l->coor.n_coor == 1) {
    maze_way_choice(win_display, maze, l, ch);
    if (*ch == '\n') {
      *ch = '\0';
      print_loading(win_display->display);
      *qtable = start_qlearn(maze, l->coor.start);
    }
  }

  if (l->coor.n_coor == 2) {
    maze_way_choice(win_display, maze, l, ch);
    if (*ch == '\n') {
      maze_learn_rendering(win_display, maze, qtable, l);
      *ch = '\0';
    }
    l->coor.n_coor = 2;
  }

  wrefresh(win_display->display);
}

void maze_learn_rendering(window_display *win_display, t_maze *maze,
                          t_Qtable **qtable, logic *l) {
  display_update(maze, win_display->display);
  t_point *path = get_quick_route_ml(*qtable, l->coor.finish, l->coor.start);
  for (int i = 0; path != NULL && path[i].y != -1; i++) {
    cell(maze, path[i].y, path[i].x, win_display->display, 10);
    napms(100);
    wrefresh(win_display->display);
  }
  if (lenght_route(path) != 0)
    free(path);
  else
    print_no_way(win_display->display);
}

void cave_start(window_display *win_display, t_cave *cave, logic *l, int *ch) {
  if (l->cave_stage == 0) cave_switches(win_display, cave, l, ch);

  if (l->cave_stage == 1) cave_alive_probability(win_display, cave, l, ch);

  if (l->cave_stage == 2)
    cave_birth_death_cells(win_display, &cave->b_limit, &cave->d_limit, l, ch);

  if (l->cave_stage == 3) cave_step_mode(win_display, l, ch);

  if (l->cave_stage == 4) cave_rendering_step(win_display, cave, ch);

  if (l->cave_stage == 5) cave_rendering_time(win_display, cave, ch);
}

void cave_rendering(window_display *win_display, t_cave *cave, int *ch,
                    int step) {
  print_number(win_display->display, 23, 30, 0);
  int help_ch;
  struct timeval time_before, time_after;

  gettimeofday(&time_before, NULL);

  clear_display(win_display->display);
  refresh_cave(cave);
  display_update_cave(cave, win_display->display);

  if (step) nodelay(stdscr, TRUE);
  while ((help_ch = getch()) != '\n') {
    gettimeofday(&time_after, NULL);
    int diff = (time_after.tv_sec - time_before.tv_sec) * 1000000 +
               (time_after.tv_usec - time_before.tv_usec);
    if (diff > step) {
      refresh_cave(cave);
      display_update_cave(cave, win_display->display);
      gettimeofday(&time_before, NULL);
    }
  }
  clear_display(win_display->display);

  if (help_ch == '\n') *ch = 'b';
}

void cave_switches(window_display *win_display, t_cave *cave, logic *l,
                   int *ch) {
  switches(win_display, &cave->n, &cave->m, l, *ch);

  print_cave_size(win_display->display, l);
  if (*ch == '\n') {
    l->cave_stage = 1;
    clear_display(win_display->display);
    *ch = '\0';
  }
}

void cave_alive_probability(window_display *win_display, t_cave *cave, logic *l,
                            int *ch) {
  print_cave_alive_probability(win_display->display);
  print_alive_number(win_display->display, 23, 72, 0);
  int alive = 0;
  while ((*ch = getch()) != '\n' && *ch != 'b') {
    if (*ch >= '0' && *ch <= '9') alive = alive * 10 + (*ch - '0');
    if (alive >= 99) alive = 99;
    print_alive_number(win_display->display, 23, 72, alive);
  }

  if (*ch == '\n') {
    generate_cave(cave, alive);
    clear_display(win_display->display);
    l->cave_stage = 2;
    *ch = '\0';
  }
}

void cave_birth_death_cells(window_display *win_display, byte *n, byte *m,
                            logic *l, int *ch) {
  switch_selection(l, *ch);
  print_cave_birth_death(win_display->display, l);
  update_control_yx(&win_display->control_y, *n);
  update_control_yx(&win_display->control_x, *m);

  if (l->switches == 0) {
    if (*ch == KEY_RIGHT)
      if (++(*n) > 7) *n = 7;
    if (*ch == KEY_LEFT)
      if (--(*n) < 0) *n = 0;
    update_control_yx(&win_display->control_y, *n);
  } else {
    if (*ch == KEY_RIGHT)
      if (++(*m) > 7) *m = 7;
    if (*ch == KEY_LEFT)
      if (--(*m) < 0) *m = 0;
    update_control_yx(&win_display->control_x, *m);
  }

  if (*ch == '\n') {
    l->cave_stage = 3;
    clear_display(win_display->display);
    *ch = '\0';
  }
}

void cave_step_mode(window_display *win_display, logic *l, int *ch) {
  print_cave_step_mode(win_display->display);
  switch_selection(l, *ch);
  write_str(win_display->display, 20, 65, " step ", l->switches ? 1 : 3);
  write_str(win_display->display, 25, 65, " time ", l->switches ? 3 : 1);

  if (*ch == '\n') {
    l->cave_stage = l->switches ? 5 : 4;
    clear_display(win_display->display);
    print_number(win_display->display, 23, 30, 0);
    *ch = '\0';
  }
}

void cave_rendering_step(window_display *win_display, t_cave *cave, int *ch) {
  cave_rendering(win_display, cave, ch, 0);
}

void cave_rendering_time(window_display *win_display, t_cave *cave, int *ch) {
  print_cave_rendering_time(win_display->display);
  int time = 0;
  nodelay(stdscr, TRUE);
  while ((*ch = getch()) != '\n' && *ch != 'b') {
    nodelay(stdscr, FALSE);
    if (*ch >= '0' && *ch <= '9') time = time * 10 + (*ch - '0');
    if (time >= 999999990) time = 999999999;
    print_number(win_display->display, 23, 30, time);
  }
  if (*ch == '\n') {
    cave_rendering(win_display, cave, ch, time);
    *ch = '\0';
  }
}

void cave_download(window_display *win_display, t_cave *cave, logic *l,
                   int *ch) {
  nodelay(stdscr, FALSE);
  DIR *dir = opendir("./caves");
  if (dir == NULL) {
    write_str(win_display->display, 20, 50, "folder not found", 1);
    write_str(win_display->display, 24, 70, "404", 3);
  } else {
    cave_download_check(dir, cave, win_display, l, ch);
  }
  closedir(dir);
}

void cave_download_check(DIR *dir, t_cave *cave, window_display *win_display,
                         logic *l, int *ch) {
  struct dirent *entity = readdir(dir);
  int count_file = 0;
  maze_download_pagination(win_display, l, ch);
  for (int i = 0; i < (l->page * 5); i++) entity = readdir(dir);
  for (int i = 0; i < 5 && entity != NULL; i++) {
    if (strcmp(entity->d_name, ".gitkeep") != 0 && entity->d_type == 8) {
      if (*ch != '\n')
        write_str(win_display->display, (i * 4) + 10, 30, entity->d_name,
                  l->choice == i ? 3 : 1);
      if (l->choice == i) {
        char path[300] = {0};
        snprintf(path, sizeof(path), "./caves/%s%c", entity->d_name, '\0');
        if (*ch == '\n' && !load_cave_from_file(path, cave)) {
          l->cave_stage = 2;
          l->stage = C_Generate;
          clear_display(win_display->display);
          update_control_yx(&win_display->control_y, cave->b_limit);
          update_control_yx(&win_display->control_x, cave->d_limit);
          print_cave_birth_death(win_display->display, l);
        }
      }
      count_file++;
    } else
      i--;
    entity = readdir(dir);
  }
  if (!count_file) {
    if (l->page != 0) {
      l->page = 0;
      print_download_last_page(win_display->display);
    } else
      print_download(win_display->display);
  } else if (*ch != '\n')
    print_download_control(win_display->display);
}

int menu_switching(logic *l, const int *ch) {
  int result = 0;

  do {
    if (*ch == KEY_DOWN && ++l->choice > 4) {
      l->choice = 0;
      result = 1;
    }
    if (*ch == KEY_UP && --l->choice < 0) {
      l->choice = 4;
      result = -1;
    }
  } while (l->menu_list[l->i][l->choice][0] == ' ');

  return result;
}

void coor_switching(t_maze *maze, logic *l, const int *ch) {
  if (*ch == KEY_UP) l->coor.y--;
  if (*ch == KEY_DOWN) l->coor.y++;
  if (*ch == KEY_LEFT) l->coor.x--;
  if (*ch == KEY_RIGHT) l->coor.x++;

  l->coor.y = l->coor.y < 0 ? maze->n - 1 : l->coor.y % maze->n;
  l->coor.x = l->coor.x < 0 ? maze->m - 1 : l->coor.x % maze->m;
}

void switches(window_display *win_display, byte *n, byte *m, logic *l, int ch) {
  if (l->switches == 0) {
    if (ch == KEY_RIGHT)
      if (++(*n) > 50) *n = 50;
    if (ch == KEY_LEFT)
      if (--(*n) < 2) *n = 2;
    update_control_yx(&win_display->control_y, *n);
  } else {
    if (ch == KEY_RIGHT)
      if (++(*m) > 50) *m = 50;
    if (ch == KEY_LEFT)
      if (--(*m) < 2) *m = 2;
    update_control_yx(&win_display->control_x, *m);
  }

  switch_selection(l, ch);
}

void switch_selection(logic *l, int ch) {
  if (ch == KEY_UP)
    l->switches = 0;
  else if (ch == KEY_DOWN)
    l->switches = 1;
}