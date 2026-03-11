#include "additional.h"

// void print_maze(t_maze *maze) {
//   for (int i = 0; i < maze->n; ++i) {
//     for (int j = 0; j < maze->m; ++j) {
//       if (maze->vwall[i][j] && maze->gwall[i][j]) printf("__|");
//       if (maze->vwall[i][j] && !maze->gwall[i][j]) printf("  |");
//       if (!maze->vwall[i][j] && !maze->gwall[i][j]) printf("   ");
//       if (!maze->vwall[i][j] && maze->gwall[i][j]) printf("__ ");
//     }
//     printf("\n");
//   }
// }

int equal(t_point *p1, t_point *p2) {
  return (p1->x == p2->x && p1->y == p2->y);
}

int lenght_route(t_point *route) {
  t_point empty = {EMPTY, EMPTY};
  int steps = 0;
  if (route)
    while (!equal(route + steps, &empty)) steps++;
  return steps;
}

int load_from_file(char *filename, t_maze *maze) {
  int error = NO_ERROR;
  FILE *f = fopen(filename, "r");

  if (!f) {
    error = ERROR_FILE;
  } else {
    fscanf(f, "%d", &maze->n);
    fscanf(f, "%d", &maze->m);
    error = maze_mem_alloc(maze);

    if (!error) {
      int count = 0;
      int max_index = maze->n * maze->m;
      while (count != max_index) fscanf(f, "%d", &maze->vwall[0][count++]);

      count = 0;
      while (count != max_index) fscanf(f, "%d", &maze->gwall[0][count++]);
    }
    fclose(f);
  }
  return error;
}

int maze_mem_alloc(t_maze *maze) {
  int error = NO_ERROR;
  maze->vwall = (byte **)calloc(1, maze->n * sizeof(byte *));
  maze->gwall = (byte **)calloc(1, maze->n * sizeof(byte *));

  if (!maze->vwall || !maze->gwall) error = ERROR_MEM;

  if (!error) {
    maze->vwall[0] = (byte *)calloc(1, maze->n * maze->m * sizeof(byte));
    maze->gwall[0] = (byte *)calloc(1, maze->n * maze->m * sizeof(byte));

    if (maze->vwall[0] && maze->gwall[0]) {
      for (byte i = 1; i < maze->n; ++i) {
        maze->vwall[i] = maze->vwall[0] + i * maze->m;
        maze->gwall[i] = maze->gwall[0] + i * maze->m;
      }
    } else
      error = ERROR_MEM;
  }

  return error;
}

void free_mem_maze(t_maze *maze) {
  if (maze) {
    if (maze->vwall) {
      if (maze->vwall[0]) {
        free(maze->vwall[0]);
        maze->vwall[0] = NULL;
      }
      free(maze->vwall);
      maze->vwall = NULL;
    }
    if (maze->gwall) {
      if (maze->gwall[0]) {
        free(maze->gwall[0]);
        maze->gwall[0] = NULL;
      }
      free(maze->gwall);
      maze->gwall = NULL;
    }
  }
}

int load_cave_from_file(char *path, t_cave *cave) {
  int error = NO_ERROR;
  if (cave->matrix) free_cave_mem(cave);
  FILE *f = fopen(path, "r");
  if (!f) {
    error = ERROR_FILE;
  } else {
    fscanf(f, "%d", &cave->n);
    fscanf(f, "%d", &cave->m);
    error = cave_mem_alloc(cave);
    if (!error) {
      int count = 0;
      int max_index = cave->n * cave->m;
      while (count != max_index) fscanf(f, "%d", &cave->matrix[0][count++]);
    }
    fclose(f);
  }
  return error;
}

int cave_mem_alloc(t_cave *cave) {
  int error = NO_ERROR;
  cave->matrix = (byte **)calloc(1, cave->n * sizeof(byte *));
  if (!cave->matrix) error = ERROR_MEM;
  if (!error) {
    cave->matrix[0] = (byte *)calloc(1, cave->n * cave->m * sizeof(byte));
    if (cave->matrix[0]) {
      for (byte i = 1; i < cave->n; ++i) {
        cave->matrix[i] = cave->matrix[0] + i * cave->m;
      }
    } else
      error = ERROR_MEM;
  }
  return error;
}

void free_cave_mem(t_cave *cave) {
  if (cave) {
    if (cave->matrix[0]) free(cave->matrix[0]);
    if (cave->matrix) free(cave->matrix);
  }
}