#ifndef TESTS_S21_maze_H
#define TESTS_S21_maze_H

#include <check.h>

#include "../additional.h"
#include "../maze.h"

#define SUCCESS 0
#define FAILURE 1

Suite *test_s21_maze_ideal();
Suite *test_s21_cave();
Suite *test_s21_get_route_maze();
Suite *test_s21_route_add();
Suite *test_s21_maze_ml_5x5();
Suite *test_s21_maze_ml_10x10();
Suite *test_s21_maze_ml_20x20();
Suite *test_s21_maze_ml_50x50();
Suite *test_s21_q_learn_add();

#endif  // TESTS_S21_maze_H
