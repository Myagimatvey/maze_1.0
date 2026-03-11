#include "test_s21_maze.h"

START_TEST(test_1) {
  t_maze maze = {0};
  maze.n = maze.m = 5;
  create_maze(&maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_2) {
  t_maze maze = {0};
  maze.n = maze.m = 20;
  create_maze(&maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_3) {
  t_maze maze = {0};
  maze.n = maze.m = 50;
  create_maze(&maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_4) {
  t_maze maze = {0};
  maze.n = 10;
  maze.m = 20;
  create_maze(&maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_5) {
  t_maze maze = {0};
  maze.n = 20;
  maze.m = 10;
  create_maze(&maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_6) {
  t_maze maze = {0};

  load_from_file("mazes/example_1.txt", &maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");
  ck_assert_msg(maze.n == 10, "maze n load from file error");
  ck_assert_msg(maze.m == 10, "maze m load from file error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_7) {
  t_maze maze = {0};

  load_from_file("mazes/example_2.txt", &maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");
  ck_assert_msg(maze.n == 10, "maze n load from file error");
  ck_assert_msg(maze.m == 10, "maze m load from file error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_8) {
  t_maze maze = {0};

  load_from_file("mazes/example_3.txt", &maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");
  ck_assert_msg(maze.n == 20, "maze n load from file error");
  ck_assert_msg(maze.m == 20, "maze m load from file error");

  free_mem_maze(&maze);
}
END_TEST

START_TEST(test_9) {
  t_maze maze = {0};
  maze.n = 10;
  maze.m = 10;

  time_t mytime = time(NULL);
  struct tm *now = localtime(&mytime);
  char path[50] = {'\0'};
  sprintf(path, "mazes/maze_%d.%d.%d_%d:%d:%d", now->tm_year + 1900,
          now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min,
          now->tm_sec);
  create_maze(&maze);

  t_maze f_maze = {0};
  load_from_file(path, &f_maze);

  ck_assert_msg(maze.gwall != NULL, "maze gwall memory allocation error");
  ck_assert_msg(maze.vwall != NULL, "maze vwall memory allocation error");
  ck_assert_msg(f_maze.vwall != NULL,
                "loaded maze vwall memory allocation error");
  ck_assert_msg(f_maze.vwall != NULL,
                "loaded maze vwall memory allocation error");
  ck_assert_msg(maze.n == f_maze.n, "maze n save to file error");
  ck_assert_msg(maze.m == f_maze.m, "maze m save to file error");
  ck_assert_msg(maze.gwall[0][0] == f_maze.gwall[0][0],
                "save to file gwall not equal");
  ck_assert_msg(maze.vwall[0][0] == f_maze.vwall[0][0],
                "save to file vwall not equal");

  free_mem_maze(&maze);
  free_mem_maze(&f_maze);
}
END_TEST

START_TEST(test_10) {
  int *line = NULL;
  int size = 10;
  line = calloc(size, sizeof(int));
  if (line) {
    fill_unique_sets(line, size);

    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (i != j) ck_assert_msg(line[i] != line[j], "set is not unique");
      }
    }

    free(line);
  }
}
END_TEST

START_TEST(test_11) {
  int *line = NULL;
  int size = 10;
  line = calloc(size, sizeof(int));
  if (line) {
    fill_unique_sets(line, size);

    t_maze maze = {0};

    load_from_file("mazes/example_1.txt", &maze);

    fill_vwall(&maze, line, 0);

    int has_wall = 0;
    for (int i = 0; i < size; ++i) {
      if (maze.vwall[0][i]) has_wall = 1;
    }
    ck_assert_msg(has_wall, "vwall is not set");

    free(line);
    free_mem_maze(&maze);
  }
}
END_TEST

START_TEST(test_12) {
  int *line = NULL;
  int size = 10;
  line = calloc(size, sizeof(int));
  if (line) {
    fill_unique_sets(line, size);

    t_maze maze = {0};
    load_from_file("mazes/example_1.txt", &maze);

    fill_gwall(&maze, line, 0);

    int has_wall = 0;
    for (int i = 0; i < size; ++i) {
      if (maze.gwall[0][i]) has_wall = 1;
    }
    ck_assert_msg(has_wall, "gwall is not set");

    free(line);
    free_mem_maze(&maze);
  }
}
END_TEST

START_TEST(test_13) {
  int *line = NULL;
  int size = 10;
  line = calloc(size, sizeof(int));
  if (line) {
    fill_unique_sets(line, size);
    union_sets(size, line, 3);

    ck_assert_msg(line[3] == line[4], "union set error");

    free(line);
  }
}
END_TEST

Suite *test_s21_maze_ideal(void) {
  Suite *s = suite_create("\033[45m-=test_s21_maze_ideal=-\033[0m");
  TCase *tc = tcase_create("test_s21_maze_ideal");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);

  suite_add_tcase(s, tc);
  return s;
}