#ifndef _S21_MAZE_H
#define _S21_MAZE_H

#define MAX 50
#define NO_ERROR 0
#define ERROR_VALUE 1
#define ERROR_FILE 2
#define ERROR_MEM 4
#define PATH_NO_EXIST 8

#define EMPTY (-1)
#define ACTION 4

#define ALPHA_STD 1
#define SIGMA_STD 1
#define RAND_CHOICE_STD 10
#define ALPHA_GREEDY 1
#define SIGMA_GREEDY 1
#define RAND_CHOICE_GREEDY 0
#define STUDY 0
#define GREEDY 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef int byte;
typedef float type_Q;

enum action_list { up, right, down, left };

typedef struct S_point {
  byte y;
  byte x;
} t_point;

typedef struct S_Maze {
  byte n;
  byte m;
  byte **vwall;
  byte **gwall;
} t_maze;

typedef struct S_Cave {
  byte n;
  byte m;
  byte **matrix;
  int b_limit, d_limit;
} t_cave;

typedef struct S_graph {
  byte n;
  byte m;
  byte neibour[ACTION];
  byte distance;
} t_graph;

typedef struct S_Qtable {
  byte n;
  byte m;
  type_Q *strategy[ACTION];
  short *exist;
  float alpha;
  float sigma;
  short rand_choice;
} t_Qtable;

int create_maze(t_maze *maze);
t_point *get_route_maze(t_maze *maze, const t_point start,
                        const t_point finish);
int refresh_cave(t_cave *cave);
t_Qtable *start_qlearn(t_maze *maze, const t_point finish);
t_point *get_quick_route_ml(t_Qtable *Q, const t_point start,
                            const t_point finish);

// additional functions
void free_mem_maze(t_maze *maze);
void free_Qtable(t_Qtable *Q);
int cave_mem_alloc(t_cave *cave);
void free_cave_mem(t_cave *cave);

#endif  // _S21_MAZE_H