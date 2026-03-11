#include "test_s21_maze.h"

START_TEST(test_s21_route_add_maze_to_graph) {
  t_maze maze;
  load_from_file("mazes/maze_10_10", &maze);
  t_graph g_maze[10 * 10];
  maze_to_graph(&maze, g_maze);

  ck_assert_int_eq(g_maze[0].neibour[up], -1);
  ck_assert_int_eq(g_maze[0].neibour[left], -1);
  ck_assert_int_eq(g_maze[0].neibour[right], 1);
  ck_assert_int_eq(g_maze[0].neibour[down], -1);

  ck_assert_int_eq(g_maze[1].neibour[up], -1);
  ck_assert_int_eq(g_maze[1].neibour[left], 0);
  ck_assert_int_eq(g_maze[1].neibour[right], 2);
  ck_assert_int_eq(g_maze[1].neibour[down], 11);

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_s21_route_add_search) {
  t_maze maze;
  load_from_file("mazes/maze_10_10", &maze);
  t_graph g_maze[10 * 10];
  maze_to_graph(&maze, g_maze);

  g_maze[0].distance = 0;
  search_graph(g_maze, 0, 99);
  ck_assert_int_eq(g_maze[99].distance, 18);

  g_maze[2].distance = 0;
  search_graph(g_maze, 2, 99);
  ck_assert_int_eq(g_maze[99].distance, 18);

  g_maze[1].distance = 0;
  search_graph(g_maze, 1, 99);
  ck_assert_int_eq(g_maze[99].distance, 17);

  g_maze[29].distance = 0;
  search_graph(g_maze, 29, 99);
  ck_assert_int_eq(g_maze[99].distance, 11);

  g_maze[98].distance = 0;
  search_graph(g_maze, 98, 99);
  ck_assert_int_eq(g_maze[99].distance, 1);

  g_maze[90].distance = 0;
  g_maze[99].distance = -1;
  search_graph(g_maze, 90, 99);
  ck_assert_int_eq(g_maze[99].distance, -1);

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_s21_route_add_get_route) {
  t_maze maze = {0};
  load_from_file("mazes/maze_10_10", &maze);
  t_graph g_maze[10 * 10] = {0};
  maze_to_graph(&maze, g_maze);

  g_maze[0].distance = 0;
  search_graph(g_maze, 0, 99);
  t_point *route = NULL;
  get_route_graph(g_maze, 99, &route);
  ck_assert_int_eq(lenght_route(route), 19);
  free(route);

  g_maze[2].distance = 0;
  search_graph(g_maze, 2, 99);
  route = NULL;
  get_route_graph(g_maze, 99, &route);
  ck_assert_int_eq(lenght_route(route), 19);
  free(route);

  g_maze[1].distance = 0;
  search_graph(g_maze, 1, 99);
  route = NULL;
  get_route_graph(g_maze, 99, &route);
  ck_assert_int_eq(lenght_route(route), 18);
  free(route);

  g_maze[29].distance = 0;
  search_graph(g_maze, 29, 99);
  route = NULL;
  get_route_graph(g_maze, 99, &route);
  ck_assert_int_eq(lenght_route(route), 12);
  free(route);

  g_maze[98].distance = 0;
  search_graph(g_maze, 98, 99);
  route = NULL;
  get_route_graph(g_maze, 99, &route);
  ck_assert_int_eq(lenght_route(route), 2);
  free(route);

  g_maze[90].distance = 0;
  g_maze[99].distance = -1;
  search_graph(g_maze, 90, 99);
  route = NULL;
  get_route_graph(g_maze, 99, &route);
  ck_assert_int_eq(lenght_route(route), 0);
  free(route);

  free_mem_maze(&maze);
}
END_TEST

Suite *test_s21_route_add(void) {
  Suite *s = suite_create("\033[45m-=test_s21_path_add=-\033[0m");
  TCase *tc = tcase_create("test_s21_path_add");

  tcase_add_test(tc, test_s21_route_add_maze_to_graph);
  tcase_add_test(tc, test_s21_route_add_search);
  tcase_add_test(tc, test_s21_route_add_get_route);

  suite_add_tcase(s, tc);
  return s;
}