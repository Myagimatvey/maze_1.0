#include "test_s21_maze.h"

START_TEST(test_get_route_maze_1) {
  t_maze maze = {0};
  load_from_file("mazes/example_1.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 9;
  finish.y = 9;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 1, "path not found - x");
  ck_assert_msg(route[1].y == 0, "path not found - y");
  ck_assert_msg(route[2].x == 2, "path not found - x");
  ck_assert_msg(route[2].y == 0, "path not found - y");
  ck_assert_msg(route[3].x == 2, "path not found - x");
  ck_assert_msg(route[3].y == 1, "path not found - y");
  ck_assert_msg(route[4].x == 2, "path not found - x");
  ck_assert_msg(route[4].y == 2, "path not found - y");
  ck_assert_msg(route[5].x == 1, "path not found - x");
  ck_assert_msg(route[5].y == 2, "path not found - y");
  ck_assert_msg(route[6].x == 1, "path not found - x");
  ck_assert_msg(route[6].y == 3, "path not found - y");
  ck_assert_msg(route[25].x == 8, "path not found - x");
  ck_assert_msg(route[25].y == 3, "path not found - y");
  ck_assert_msg(route[47].x == 8, "path not found - x");
  ck_assert_msg(route[47].y == 9, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 49, "path distance differ");
  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_2) {
  t_maze maze = {0};
  load_from_file("mazes/example_1.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 0;
  finish.y = 1;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 0, "path not found - x");
  ck_assert_msg(route[1].y == 1, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 2, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_3) {
  t_maze maze = {0};
  load_from_file("mazes/example_1.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 1;
  finish.y = 0;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 1, "path not found - x");
  ck_assert_msg(route[1].y == 0, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 2, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_4) {
  t_maze maze = {0};
  load_from_file("mazes/example_1.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 0;
  finish.y = 0;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[0].x == 0, "path not found - x");
  ck_assert_msg(route[0].y == 0, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 1, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_5) {
  t_maze maze = {0};
  load_from_file("mazes/example_2.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 9;
  finish.y = 9;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 0, "path not found - x");
  ck_assert_msg(route[1].y == 1, "path not found - y");
  ck_assert_msg(route[2].x == 0, "path not found - x");
  ck_assert_msg(route[2].y == 2, "path not found - y");
  ck_assert_msg(route[3].x == 0, "path not found - x");
  ck_assert_msg(route[3].y == 3, "path not found - y");
  ck_assert_msg(route[4].x == 0, "path not found - x");
  ck_assert_msg(route[4].y == 4, "path not found - y");
  ck_assert_msg(route[5].x == 1, "path not found - x");
  ck_assert_msg(route[5].y == 4, "path not found - y");
  ck_assert_msg(route[6].x == 1, "path not found - x");
  ck_assert_msg(route[6].y == 3, "path not found - y");
  ck_assert_msg(route[25].x == 3, "path not found - x");
  ck_assert_msg(route[25].y == 6, "path not found - y");
  ck_assert_msg(route[49].x == 9, "path not found - x");
  ck_assert_msg(route[49].y == 8, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 51, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_6) {
  t_maze maze = {0};
  load_from_file("mazes/example_2.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 0;
  finish.y = 1;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 0, "path not found - x");
  ck_assert_msg(route[1].y == 1, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 2, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_7) {
  t_maze maze = {0};
  load_from_file("mazes/example_2.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 1;
  finish.x = 1;
  finish.y = 1;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 1, "path not found - x");
  ck_assert_msg(route[1].y == 1, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 2, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_8) {
  t_maze maze = {0};
  load_from_file("mazes/example_2.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 9;
  start.y = 9;
  finish.x = 9;
  finish.y = 9;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[0].x == 9, "path not found - x");
  ck_assert_msg(route[0].y == 9, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 1, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_9) {
  t_maze maze = {0};
  load_from_file("mazes/example_3.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 19;
  finish.y = 19;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 1, "path not found - x");
  ck_assert_msg(route[1].y == 0, "path not found - y");
  ck_assert_msg(route[2].x == 2, "path not found - x");
  ck_assert_msg(route[2].y == 0, "path not found - y");
  ck_assert_msg(route[3].x == 3, "path not found - x");
  ck_assert_msg(route[3].y == 0, "path not found - y");
  ck_assert_msg(route[4].x == 4, "path not found - x");
  ck_assert_msg(route[4].y == 0, "path not found - y");
  ck_assert_msg(route[5].x == 4, "path not found - x");
  ck_assert_msg(route[5].y == 1, "path not found - y");
  ck_assert_msg(route[6].x == 4, "path not found - x");
  ck_assert_msg(route[6].y == 2, "path not found - y");
  ck_assert_msg(route[25].x == 5, "path not found - x");
  ck_assert_msg(route[25].y == 8, "path not found - y");
  ck_assert_msg(route[51].x == 19, "path not found - x");
  ck_assert_msg(route[51].y == 18, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 53, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_10) {
  t_maze maze = {0};
  load_from_file("mazes/example_3.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 0;
  finish.y = 1;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 0, "path not found - x");
  ck_assert_msg(route[1].y == 1, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 2, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_11) {
  t_maze maze = {0};
  load_from_file("mazes/example_3.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 1;
  finish.y = 0;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[1].x == 1, "path not found - x");
  ck_assert_msg(route[1].y == 0, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 2, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_get_route_maze_12) {
  t_maze maze = {0};
  load_from_file("mazes/example_3.txt", &maze);

  t_point start;
  t_point finish;
  start.x = 0;
  start.y = 0;
  finish.x = 0;
  finish.y = 0;
  t_point *route = NULL;
  route = get_route_maze(&maze, start, finish);
  ck_assert_msg(route[0].x == 0, "path not found - x");
  ck_assert_msg(route[0].y == 0, "path not found - y");

  int i = 0;
  while (route[i].y != -1) ++i;
  ck_assert_msg(i == 1, "path distance differ");

  free(route);
  free_mem_maze(&maze);
}
END_TEST

Suite *test_s21_get_route_maze(void) {
  Suite *s = suite_create("\033[45m-=test_s21_get_route_maze=-\033[0m");
  TCase *tc = tcase_create("test_s21_get_route_maze");

  tcase_add_test(tc, test_get_route_maze_1);
  tcase_add_test(tc, test_get_route_maze_2);
  tcase_add_test(tc, test_get_route_maze_3);
  tcase_add_test(tc, test_get_route_maze_4);
  tcase_add_test(tc, test_get_route_maze_5);
  tcase_add_test(tc, test_get_route_maze_6);
  tcase_add_test(tc, test_get_route_maze_7);
  tcase_add_test(tc, test_get_route_maze_8);
  tcase_add_test(tc, test_get_route_maze_9);
  tcase_add_test(tc, test_get_route_maze_10);
  tcase_add_test(tc, test_get_route_maze_11);
  tcase_add_test(tc, test_get_route_maze_12);

  suite_add_tcase(s, tc);
  return s;
}