#include "additional.h"
#include "maze.h"

t_point *get_route_maze(t_maze *maze, const t_point start,
                        const t_point finish) {
  t_graph g_maze[maze->n * maze->m];
  int v_start = start.y * maze->m + start.x;
  int v_finish = finish.y * maze->m + finish.x;
  maze_to_graph(maze, g_maze);

  g_maze[v_start].distance = 0;
  t_point *route = NULL;
  if (finish.x >= 0 && finish.x < maze->m && finish.y >= 0 &&
      finish.y < maze->n && start.x >= 0 && start.x < maze->m && start.y >= 0 &&
      start.y < maze->n) {
    search_graph(g_maze, v_start, v_finish);
    if (g_maze[v_finish].distance != EMPTY)
      get_route_graph(g_maze, v_finish, &route);
  }
  return route;
}

void search_graph(t_graph *g_maze, const int v1, const int v2) {
  for (int i = 0; i < ACTION; ++i)
    if (g_maze[v1].neibour[i] != EMPTY) {
      int *to_neibour = &(g_maze[g_maze[v1].neibour[i]].distance);
      if (*to_neibour == EMPTY || *to_neibour > g_maze[v1].distance + 1) {
        *to_neibour = g_maze[v1].distance + 1;
        search_graph(g_maze, g_maze[v1].neibour[i], v2);
      }
    }
}

void maze_to_graph(t_maze *maze, t_graph *g_maze) {
  for (int i = 0; i < maze->m * maze->n; ++i) {
    g_maze[i].distance = EMPTY;
    g_maze[i].neibour[0] = g_maze[i].neibour[1] = g_maze[i].neibour[2] =
        g_maze[i].neibour[3] = EMPTY;
    g_maze[i].n = maze->n;
    g_maze[i].m = maze->m;
  }
  for (int i = 0; i < maze->n; ++i)
    for (int j = 0; j < maze->m; ++j) {
      int index = i * maze->m + j;
      // up
      if (i > 0 && maze->gwall[i - 1][j] == 0)
        g_maze[index].neibour[up] = index - maze->m;

      // right
      if (maze->vwall[i][j] == 0) g_maze[index].neibour[right] = index + 1;

      // down
      if (maze->gwall[i][j] == 0) g_maze[index].neibour[down] = index + maze->m;

      // left
      if (j > 0 && maze->vwall[i][j - 1] == 0)
        g_maze[index].neibour[left] = index - 1;
    }
}

void get_route_graph(t_graph *g_maze, int v1, t_point **route) {
  short c_steps = g_maze[v1].distance;

  if (*route == NULL) {
    // 2 ... [0] + EMPTY
    *route = (t_point *)calloc(c_steps + 2, sizeof(t_point));
    if (*route)
      for (int i = 0; i < (c_steps + 2); ++i)
        (*route)[i].y = (*route)[i].x = EMPTY;
  }

  if (c_steps >= 0) {
    (*route)[c_steps].y = v1 / g_maze[0].m;
    (*route)[c_steps].x = v1 % g_maze[0].m;
    --c_steps;
    short find = 0;
    for (short i = 0; i < ACTION && !find && c_steps >= 0; ++i) {
      short distance = EMPTY;
      short next_cell = g_maze[v1].neibour[i];
      if (next_cell != EMPTY) distance = g_maze[next_cell].distance;

      if (distance == c_steps) {
        find = 1;
        get_route_graph(g_maze, next_cell, route);
      }
    }
  }
}
