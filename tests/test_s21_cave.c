#include "test_s21_maze.h"

START_TEST(test_1) {
  t_cave cave = {0};
  cave.n = cave.m = 10;
  cave.b_limit = cave.d_limit = 4;

  generate_cave(&cave, 30);
  refresh_cave(&cave);

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_2) {
  t_cave cave = {0};
  cave.n = cave.m = 50;
  cave.b_limit = cave.d_limit = 7;

  generate_cave(&cave, 99);
  refresh_cave(&cave);

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_3) {
  t_cave cave = {0};
  cave.n = 30;
  cave.m = 40;
  cave.b_limit = 4;
  cave.d_limit = 3;

  generate_cave(&cave, 50);
  refresh_cave(&cave);

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_4) {
  t_cave cave = {0};
  cave.n = 40;
  cave.m = 30;
  cave.b_limit = 2;
  cave.d_limit = 5;

  generate_cave(&cave, 50);
  refresh_cave(&cave);

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_5) {
  t_cave cave = {0};
  load_cave_from_file("caves/example_1.txt", &cave);

  cave.b_limit = 3;
  cave.d_limit = 4;

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");
  ck_assert_msg(cave.matrix[0][0] == 1, "cave loaded incorrectly");
  ck_assert_msg(cave.matrix[9][9] == 0, "cave loaded incorrectly");
  ck_assert_msg(cave.n == 10, "cave size n loaded incorrectly");
  ck_assert_msg(cave.m == 10, "cave size m loaded incorrectly");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_6) {
  t_cave cave = {0};
  load_cave_from_file("caves/example_2.txt", &cave);

  cave.b_limit = 3;
  cave.d_limit = 4;

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");
  ck_assert_msg(cave.matrix[0][0] == 1, "cave loaded incorrectly");
  ck_assert_msg(cave.matrix[19][19] == 1, "cave loaded incorrectly");
  ck_assert_msg(cave.n == 20, "cave size n loaded incorrectly");
  ck_assert_msg(cave.m == 20, "cave size m loaded incorrectly");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_7) {
  t_cave cave = {0};
  load_cave_from_file("caves/example_3.txt", &cave);

  cave.b_limit = 3;
  cave.d_limit = 4;

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");
  ck_assert_msg(cave.matrix[0][0] == 1, "cave loaded incorrectly");
  ck_assert_msg(cave.matrix[49][49] == 0, "cave loaded incorrectly");
  ck_assert_msg(cave.n == 50, "cave size n loaded incorrectly");
  ck_assert_msg(cave.m == 50, "cave size m loaded incorrectly");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_8) {
  t_cave cave = {0};
  cave.n = 50;
  cave.m = 50;
  cave.b_limit = 3;
  cave.d_limit = 4;

  generate_cave(&cave, 55);
  refresh_cave(&cave);
  refresh_cave(&cave);
  refresh_cave(&cave);
  refresh_cave(&cave);
  refresh_cave(&cave);

  ck_assert_msg(cave.matrix != NULL, "cave memory allocation error");

  free_cave_mem(&cave);
}
END_TEST

START_TEST(test_9) {
  t_cave cave = {0};
  cave.n = 50;
  cave.m = 50;
  cave.b_limit = 3;
  cave.d_limit = 4;

  generate_cave(&cave, 55);
  t_cave tmp_cave;
  tmp_cave.n = cave.n;
  tmp_cave.m = cave.m;
  cave_mem_alloc(&tmp_cave);
  copy_cave(&cave, &tmp_cave);

  for (int i = 0; i < cave.n; ++i) {
    for (int j = 0; j < cave.m; ++j)
      ck_assert_msg(cave.matrix[i][j] == tmp_cave.matrix[i][j],
                    "cave copy is not done");
  }

  free_cave_mem(&cave);
  free_cave_mem(&tmp_cave);
}
END_TEST

Suite *test_s21_cave(void) {
  Suite *s = suite_create("\033[45m-=test_s21_cave=-\033[0m");
  TCase *tc = tcase_create("test_s21_cave");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);

  suite_add_tcase(s, tc);
  return s;
}