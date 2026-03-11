#include "test_s21_maze.h"

START_TEST(test_s21_maze_ml_2) {
  t_maze maze;
  int error = load_from_file("mazes/maze_10_10", &maze);
  if (!error) {
    t_point p_finish = {maze.n - 1, maze.m - 1};

    t_Qtable *Q = start_qlearn(&maze, p_finish);
    t_point *route_path = NULL, *route_q = NULL;
    t_point p_start;

    int v_start = 0, size = maze.m * maze.n;

    while (v_start < size) {
      p_start.y = v_start / maze.m;
      p_start.x = v_start % maze.m;
      route_path = get_route_maze(&maze, p_start, p_finish);
      route_q = get_quick_route_ml(Q, p_start, p_finish);

      ck_assert_int_eq(lenght_route(route_path), lenght_route(route_q));
      if (route_path) free(route_path);
      if (route_q) free(route_q);
      route_path = route_q = NULL;
      v_start++;
    }

    free_Qtable(Q);
  }
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_s21_maze_ml_2_close) {
  t_maze maze;
  int error = load_from_file("mazes/maze_10_10", &maze);
  if (!error) {
    t_point p_finish = {0, 0};

    t_Qtable *Q = start_qlearn(&maze, p_finish);
    t_point *route_path = NULL, *route_q = NULL;
    t_point p_start;

    int v_start = 0, size = maze.m * maze.n;

    while (v_start < size) {
      p_start.y = v_start / maze.m;
      p_start.x = v_start % maze.m;
      route_path = get_route_maze(&maze, p_start, p_finish);
      route_q = get_quick_route_ml(Q, p_start, p_finish);

      ck_assert_int_eq(lenght_route(route_path), lenght_route(route_q));
      if (route_path) free(route_path);
      if (route_q) free(route_q);
      route_path = route_q = NULL;
      v_start++;
    }

    free_Qtable(Q);
  }
  free_mem_maze(&maze);
}
END_TEST

Suite *test_s21_maze_ml_10x10(void) {
  Suite *s = suite_create("\033[45m-=test_s21_maze_ml_10x10=-\033[0m");
  TCase *tc = tcase_create("test_s21_maze_ml_10x10");

  tcase_add_test(tc, test_s21_maze_ml_2);
  tcase_add_test(tc, test_s21_maze_ml_2_close);
  suite_add_tcase(s, tc);
  return s;
}