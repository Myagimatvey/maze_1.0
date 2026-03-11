#include "additional.h"
#include "maze.h"

/*refreshes cave state according to birth and death limits*/
int refresh_cave(t_cave* cave) {
  int error = NO_ERROR;
  t_cave tmp_cave;
  tmp_cave.n = cave->n;
  tmp_cave.m = cave->m;
  cave_mem_alloc(&tmp_cave);
  copy_cave(cave, &tmp_cave);

  for (int i = 0; i < cave->n; ++i) {
    for (int j = 0; j < cave->m; ++j) {
      int count_alive = 0;
      count_alive += !j ? 1 : cave->matrix[i][j - 1];
      count_alive += (!j || !i) ? 1 : cave->matrix[i - 1][j - 1];
      count_alive += !i ? 1 : cave->matrix[i - 1][j];
      count_alive += (!i || j == cave->m - 1) ? 1 : cave->matrix[i - 1][j + 1];
      count_alive += (j == cave->m - 1) ? 1 : cave->matrix[i][j + 1];
      count_alive += (i == cave->n - 1 || j == cave->m - 1)
                         ? 1
                         : cave->matrix[i + 1][j + 1];
      count_alive += (i == cave->n - 1) ? 1 : cave->matrix[i + 1][j];
      count_alive += (i == cave->n - 1 || !j) ? 1 : cave->matrix[i + 1][j - 1];
      if (cave->matrix[i][j] == 1 && count_alive < cave->d_limit)
        tmp_cave.matrix[i][j] = 0;
      if (cave->matrix[i][j] == 0 && count_alive > cave->b_limit)
        tmp_cave.matrix[i][j] = 1;
    }
  }

  copy_cave(&tmp_cave, cave);
  free_cave_mem(&tmp_cave);

  return error;
}

/*copy cave matrix from tmp_cave to cave*/
void copy_cave(t_cave* tmp_cave, t_cave* cave) {
  for (int i = 0; i < cave->n; ++i) {
    for (int j = 0; j < cave->m; ++j) {
      cave->matrix[i][j] = tmp_cave->matrix[i][j];
    }
  }
}

/*randomly generates  alive / dead cells according to alive_probability %*/
void generate_cave(t_cave* cave, int alive_probability) {
  if (cave->matrix) free_cave_mem(cave);
  cave_mem_alloc(cave);
  srand(time(NULL));
  for (int i = 0; i < cave->n; ++i) {
    for (int j = 0; j < cave->m; ++j) {
      cave->matrix[i][j] = 1 + rand() % 99 <= alive_probability ? 1 : 0;
    }
  }
}
