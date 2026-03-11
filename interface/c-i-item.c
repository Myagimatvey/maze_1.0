#include "console-interface.h"

void cell(t_maze *maze, int y, int x, WINDOW *display, int color) {
  if (maze == NULL || maze->vwall == NULL || maze->vwall[y] == NULL ||
      maze->gwall == NULL || maze->gwall[y] == NULL)
    return;
  char str[30] = {'\0'};
  int increase = 0;
  for (int i = maze->m, j = maze->n; i <= 50 && j <= 50;
       i *= 2, j *= 2, increase++) {
    if (maze->gwall[y][x])
      strcat(str, "__");
    else
      strcat(str, "  ");
  }

  int st_x = (150 - (maze->m * (2 * increase + 1))) / 2;
  int st_y = (50 - (maze->n * increase)) / 2;

  if (y == maze->n - 1 && x == 0) {
    for (int i = 0; i < maze->m; i++)
      mvwprintw(display, st_y, st_x + (i * (2 * increase + 1) + 2), "%s", str);

    for (int i = 1; i <= maze->n * increase; i++)
      mvwprintw(display, st_y + i, st_x + 1, "%c", '|');
  }

  if (maze->vwall[y][x])
    strcat(str, "|");
  else
    strcat(str, " ");

  wattron(display, COLOR_PAIR(color));
  mvwprintw(display, st_y + (y * increase) + increase,
            st_x + (x * (2 * increase + 1) + 2), "%s", str);

  for (int j = 0; j < increase; j++) {
    str[j * 2] = ' ';
    str[j * 2 + 1] = ' ';
  }
  for (int i = 1; i < increase; i++) {
    mvwprintw(display, st_y + (y * increase) + increase - i,
              st_x + (x * (2 * increase + 1) + 2), "%s", str);
  }
  wattroff(display, COLOR_PAIR(color));
}

void cell_cave(t_cave *cave, int y, int x, WINDOW *display, int color) {
  if (cave == NULL || cave->matrix == NULL || cave->matrix[y] == NULL) return;

  char str[30] = {'\0'};
  int increase = 0;
  for (int i = cave->m, j = cave->n; i <= 50 && j <= 50;
       i *= 2, j *= 2, increase++)
    strcat(str, "   ");

  int st_x = (150 - (cave->m * (3 * increase))) / 2;
  int st_y = (50 - (cave->n * increase)) / 2;

  wattron(display, COLOR_PAIR(cave->matrix[y][x] ? color : 1));
  for (int i = 0; i < increase; i++)
    mvwprintw(display, st_y + (y * increase) + i + 1,
              st_x + (x * 3 * increase) + 2, "%s", str);
  wattroff(display, COLOR_PAIR(cave->matrix[y][x] ? color : 1));
}