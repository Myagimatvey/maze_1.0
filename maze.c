#include "maze.h"

#include "interface/console-interface.h"

int main() {
  int error = NO_ERROR;

  t_maze maze = {0};
  maze.n = 50;
  maze.m = 50;
  t_cave cave = {0};
  cave.n = 50;
  cave.m = 50;
  cave.b_limit = 7;
  cave.d_limit = 3;
  t_Qtable *qtable = NULL;

  game(&maze, &cave, &qtable);

  if (maze.gwall || maze.vwall) free_mem_maze(&maze);  // сега при очистке
  if (cave.matrix) free_cave_mem(&cave);  // сега при очистке

  return error;
}