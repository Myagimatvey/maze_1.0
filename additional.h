#ifndef TESTS_S21_MAZE_ADDITIONAL_H
#define TESTS_S21_MAZE_ADDITIONAL_H

#include "maze.h"

// common
int load_from_file(char *filename, t_maze *maze);
int load_cave_from_file(char *path, t_cave *cave);
int lenght_route(t_point *route);

// route_graph
void search_graph(t_graph *g_maze, const int v1, const int v2);
void get_route_graph(t_graph *g_maze, int v1, t_point **steps);
int maze_mem_alloc(t_maze *maze);
void maze_to_graph(t_maze *maze, t_graph *g_maze);

// route q-learning
short initialize_Q(t_Qtable **Q, const int m, const int n);
type_Q max_strategy_and_action(t_Qtable *Q, const int v1, short *max_action);
void set_ML_mode(t_Qtable *Q, short mode);
void refresh_Q(t_Qtable *Q, const int v1, const int reward, const short action);
void check_exist(t_Qtable *Q, const int v1, const int v_finish);
short next_step(t_Qtable *Q, const int v1, const short action);
short choice_action(t_Qtable *Q, const int v1);
int get_reward(t_graph *g_maze, const int v, const short action,
               const int finish);

// create ideal maze
void fill_unique_sets(int *line, int size);
void fill_vwall(t_maze *maze, int *line, int row);
void fill_gwall(t_maze *maze, const int *line, int rows_);
void fill_last_walls(t_maze *maze, int *line);
void union_sets(int size, int *line, int i);
int save_maze_to_file(t_maze *maze);

// cave
void copy_cave(t_cave *tmp_cave, t_cave *cave);
void generate_cave(t_cave *cave, int alive_probability);

#endif