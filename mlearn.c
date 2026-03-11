#include "additional.h"
#include "maze.h"

#define VICTORY 500000
#define WALL_PENALTY (-50000)
#define MIN_REWARD (WALL_PENALTY + 5000)
#define USUAL_STEP (-100)

#define NOT_LOOKING_EXIST 0
#define YES_EXIST 1
#define LOOKING_EXIST 2
#define NO_EXIST 4

#define LEARN_PASS 10

void set_ML_mode(t_Qtable *Q, short mode) {
  if (mode == STUDY) {
    Q->alpha = ALPHA_STD;
    Q->sigma = SIGMA_STD;
    Q->rand_choice = RAND_CHOICE_STD;
  } else if (mode == GREEDY) {
    Q->alpha = ALPHA_GREEDY;
    Q->sigma = SIGMA_GREEDY;
    Q->rand_choice = RAND_CHOICE_GREEDY;
  }
}

short initialize_Q(t_Qtable **Q, const int m, const int n) {
  short error = NO_ERROR;
  *Q = (t_Qtable *)calloc(1, sizeof(t_Qtable));
  if (*Q) {
    (*Q)->m = m;
    (*Q)->n = n;
    set_ML_mode(*Q, STUDY);
    int size = n * m;
    (*Q)->strategy[0] = (type_Q *)calloc(ACTION, size * sizeof(type_Q));

    error = ((*Q)->strategy[0] == NULL);
    if (!error)
      for (short i = 1; i < ACTION; ++i)
        (*Q)->strategy[i] = (*Q)->strategy[0] + i * size;

    (*Q)->exist = (short *)calloc(1, size * sizeof(short));
    if (!(*Q)->exist) error = ERROR_MEM;
  } else
    error = ERROR_MEM;

  if (error) {
    if (*Q) free(*Q);
    *Q = NULL;
  }

  return error;
}

t_Qtable *start_qlearn(t_maze *maze, const t_point finish) {
  t_graph g_maze[maze->n * maze->m];
  maze_to_graph(maze, g_maze);

  int v_finish = finish.y * maze->m + finish.x;

  short error = NO_ERROR;

  if (finish.x < 0 || finish.x >= maze->m || finish.y < 0 ||
      finish.y >= maze->n)
    error |= PATH_NO_EXIST;

  t_Qtable *Q = NULL;
  if (!error) error = initialize_Q(&Q, maze->m, maze->n);

  if (!error) {
    set_ML_mode(Q, STUDY);
    short size_maze = Q->n * Q->m;
    short action, gag, next_cell;
    int reward;

    short v_start = 0, v1 = v_start, pass = 0;
    while (pass < LEARN_PASS) {
      check_exist(Q, v1, v_finish);
      if (v1 == v_finish || Q->exist[v1] == NO_EXIST) {
        if ((max_strategy_and_action(Q, v_start, &gag) > 0) ||
            Q->exist[v1] == NO_EXIST || v_start == v_finish) {
          ++v_start;
          pass += v_start / size_maze;
          v_start = v_start % size_maze;

          // if (1) {
          //   FILE *f = fopen("tests/Q_10_10", "w");
          //   fprintf(f, "%d %d\n", Q->m, Q->n);

          //   for (int k = 0; k < 4; ++k) {
          //     fprintf(f, "%d\n", k);
          //     for (int i = 0; i < 10; ++i) {
          //       for (int j = 0; j < 10; ++j) {
          //         fprintf(f, "%d ", Q->strategy[k][i * Q->m + j]);
          //       }
          //       fprintf(f, "\n");
          //     }
          //   }
          //   fclose(f);
          // }
          // getchar();
        }
        v1 = v_start;
      } else {
        for (short j = 0; j < ACTION; ++j) {
          reward = get_reward(g_maze, v1, j, v_finish);
          refresh_Q(Q, v1, reward, j);
        }
        action = choice_action(Q, v1);
        next_cell = next_step(Q, v1, action);
        if (next_cell != EMPTY) v1 = next_cell;
      }
    }
  }
  return Q;
}

void check_exist(t_Qtable *Q, const int v1, const int v_finish) {
  short size_maze = Q->n * Q->m;
  type_Q minimal_Q = 0;
  if (Q->sigma < 1.0)
    minimal_Q = USUAL_STEP / (1 - Q->sigma) + 10 * (1 - Q->sigma);
  else if (Q->sigma == 1)
    minimal_Q = MIN_REWARD;

  if (minimal_Q < WALL_PENALTY) minimal_Q = MIN_REWARD;

  if (Q->exist[v1] == NOT_LOOKING_EXIST) Q->exist[v1] = LOOKING_EXIST;
  if ((Q->strategy[0][v1] < minimal_Q && Q->strategy[0][v1] > WALL_PENALTY) ||
      (Q->strategy[1][v1] < minimal_Q && Q->strategy[1][v1] > WALL_PENALTY) ||
      (Q->strategy[2][v1] < minimal_Q && Q->strategy[2][v1] > WALL_PENALTY) ||
      (Q->strategy[3][v1] < minimal_Q && Q->strategy[3][v1] > WALL_PENALTY))
    Q->exist[v1] = NO_EXIST;

  if (v1 == v_finish || Q->exist[v1] == NO_EXIST) {
    for (short i = 0; i < size_maze; ++i)
      if (Q->exist[i] == LOOKING_EXIST) {
        if (v1 == v_finish)
          Q->exist[i] = YES_EXIST;
        else
          Q->exist[i] = NO_EXIST;
      }
  }
}

t_point *get_quick_route_ml(t_Qtable *Q, const t_point start,
                            const t_point finish) {
  const int max_route = Q->m * Q->n + 2;  // 2 ... [0] + EMPTY
  int error = NO_ERROR;

  t_point *route = (t_point *)calloc(max_route, sizeof(t_point));
  if (route)
    for (int i = 0; i < max_route; ++i) route[i].y = route[i].x = EMPTY;
  else
    error = ERROR_MEM;

  int v1 = start.y * Q->m + start.x;
  if (Q->exist[v1] == NO_EXIST) error |= PATH_NO_EXIST;

  if (error == NO_ERROR) {
    set_ML_mode(Q, GREEDY);
    const int v_finish = finish.y * Q->m + finish.x;
    short index = 0;

    while (v1 != v_finish) {
      route[index].y = v1 / Q->m;
      route[index].x = v1 % Q->m;
      short action = choice_action(Q, v1);
      v1 = next_step(Q, v1, action);
      index++;
    }
    (route)[index].y = v_finish / Q->m;
    (route)[index].x = v_finish % Q->m;
  }
  return route;
}

//  action strategy/policy research
short choice_action(t_Qtable *Q, const int v1) {
  srand(time(NULL) + rand());
  short max_action, action;
  max_strategy_and_action(Q, v1, &max_action);
  do {
    action = max_action;
    if ((rand() % 100) < Q->rand_choice) action = rand() % ACTION;

  } while (Q->strategy[action][v1] == WALL_PENALTY);
  return action;
}

void refresh_Q(t_Qtable *Q, const int v1, const int reward,
               const short action) {
  const short next_cell = next_step(Q, v1, action);

  if (reward == VICTORY) {
    Q->strategy[action][v1] = reward;
  } else if (reward == WALL_PENALTY) {
    Q->strategy[action][v1] = reward;
  } else if (reward == USUAL_STEP) {
    short gag = 0;
    Q->strategy[action][v1] +=
        (type_Q)(Q->alpha *
                 (reward +
                  Q->sigma * max_strategy_and_action(Q, next_cell, &gag) -
                  Q->strategy[action][v1]));
  }
  // Q(s,a)_new = Q(s,a) + a[ strategy + y*Q(s', a') - Q(s,a) ]
}

short next_step(t_Qtable *Q, const int v1, const short action) {
  short next_cell = EMPTY;
  if (Q->strategy[action][v1] != WALL_PENALTY) {
    if (action == up && (v1 >= Q->m)) next_cell = v1 - Q->m;
    if (action == right && ((v1 + 1) % Q->m) != 0) next_cell = v1 + 1;
    if (action == down && ((v1 + Q->m) < Q->m * Q->n)) next_cell = v1 + Q->m;
    if (action == left && (v1 % Q->m) != 0) next_cell = v1 - 1;
  }
  return next_cell;
}

// strategy of enviroment
int get_reward(t_graph *g_maze, const int v, const short action,
               const int finish) {
  int reward = USUAL_STEP;
  if (g_maze[v].neibour[action] == finish)
    reward = VICTORY;
  else if (g_maze[v].neibour[action] == EMPTY)
    reward = WALL_PENALTY;

  return reward;
}

type_Q max_strategy_and_action(t_Qtable *Q, const int v1, short *max_action) {
  type_Q max_strategy = WALL_PENALTY;

  if (v1 >= 0 && (v1 < Q->m * Q->n)) {
    max_strategy = WALL_PENALTY - 1;

    for (short i = 0; i < ACTION; ++i)
      if (max_strategy < Q->strategy[i][v1]) {
        *max_action = i;
        max_strategy = Q->strategy[*max_action][v1];
      }
  }
  return max_strategy;
}

void free_Qtable(t_Qtable *Q) {
  if (Q) {
    if (Q->exist) {
      free(Q->exist);
      Q->exist = NULL;
    }
    if (Q->strategy[0]) {
      free(Q->strategy[0]);
      Q->strategy[0] = NULL;
    }
    free(Q);
  }
}
