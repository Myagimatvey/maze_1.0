#include "additional.h"
#include "maze.h"

/*generates ideal maze using Eller's algorithm*/
int create_maze(t_maze* maze) {
  int error = NO_ERROR;
  srand(time(NULL));

  if (maze->gwall || maze->vwall) free_mem_maze(maze);
  maze_mem_alloc(maze);

  int* line = NULL;
  line = calloc(maze->m, sizeof(int));
  if (!line) error = ERROR_MEM;

  if (!error) {
    fill_unique_sets(line, maze->m);

    for (int row_ = 0; row_ < maze->n; ++row_) {
      fill_vwall(maze, line, row_);
      fill_gwall(maze, line, row_);
      if (row_ < maze->n - 1) {
        for (int j = 0; j < maze->m; ++j)
          if (maze->gwall[row_][j]) line[j] = 0;
        fill_unique_sets(line, maze->m);
      } else {
        fill_last_walls(maze, line);
      }
    }
    save_maze_to_file(maze);
  }

  if (line) free(line);

  return error;
}

/*generates an unique set for empty (0) cells*/
void fill_unique_sets(int* line, int size) {
  for (int i = 0; i < size; ++i) {
    if (!line[i]) {
      int found = 1;
      int value = 1;
      while (found) {
        found = 0;
        for (int j = 0; j < size; ++j) {
          if (value == line[j]) found = 1;
        }
        if (found) value++;
      }
      line[i] = value;
    }
  }
}

/*fills the maze row with vertical lines*/
void fill_vwall(t_maze* maze, int* line, int row_) {
  // заполнение правых стен
  for (int i = 0; i < maze->m - 1; ++i) {
    int decision = rand() % 2;
    if (decision || line[i] == line[i + 1]) {
      maze->vwall[row_][i] = 1;
    } else {
      union_sets(maze->m, line, i);
    }
  }
  maze->vwall[row_][maze->m - 1] = 1;
}

/*fills the maze row with goriztontal lines*/
void fill_gwall(t_maze* maze, const int* line, int row_) {
  for (int i = 0; i < maze->m; ++i) {
    int decision = rand() % 2;

    if (decision) {
      int without_gwall = 0;
      for (int j = 0; j < maze->m; ++j) {
        if (line[i] == line[j] && !maze->gwall[row_][j]) without_gwall++;
      }
      if (without_gwall > 1) maze->gwall[row_][i] = 1;
    }
  }
}

/*fills the last maze row with vertical and goriztontal lines*/
void fill_last_walls(t_maze* maze, int* line) {
  // проверка правых стен
  for (int i = 0; i < maze->m - 1; ++i) {
    if (line[i] != line[i + 1]) {
      maze->vwall[maze->n - 1][i] = 0;
      union_sets(maze->m, line, i);
    }
  }
  maze->vwall[maze->n - 1][maze->m - 1] = 1;
  for (int i = 0; i < maze->m; ++i) maze->gwall[maze->n - 1][i] = 1;
}

/*union current set with a set in the next cell*/
void union_sets(int size, int* line, int i) {
  int set_ = line[i + 1];
  for (int j = 0; j < size; ++j) {
    if (line[j] == set_) line[j] = line[i];
  }
}

/*saves generated maze to file
dir: mazes/*/
int save_maze_to_file(t_maze* maze) {
  int error = NO_ERROR;
  time_t mytime = time(NULL);
  struct tm* now = localtime(&mytime);
  char path[50] = {'\0'};
  sprintf(path, "mazes/maze_%d.%d.%d_%d:%d:%d", now->tm_year + 1900,
          now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min,
          now->tm_sec);
  FILE* file = NULL;
  if ((file = fopen(path, "w")) != NULL) {
    fprintf(file, "%d %d\n", maze->n, maze->m);
    for (int i = 0; i < maze->n; ++i) {
      for (int j = 0; j < maze->m; ++j) {
        if (j == maze->m - 1)
          fprintf(file, "%d", maze->vwall[i][j]);
        else
          fprintf(file, "%d ", maze->vwall[i][j]);
      }
      fprintf(file, "\n");
    }
    fprintf(file, "\n");
    for (int i = 0; i < maze->n; ++i) {
      for (int j = 0; j < maze->m; ++j) {
        if (j == maze->m - 1)
          fprintf(file, "%d", maze->gwall[i][j]);
        else
          fprintf(file, "%d ", maze->gwall[i][j]);
      }
      fprintf(file, "\n");
    }
    fclose(file);
  } else {
    error = ERROR_FILE;
  }
  return error;
}