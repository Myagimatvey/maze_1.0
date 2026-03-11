#include "../additional.h"
#include "test_s21_maze.h"

// char *direct[ACTION] = {"UP", "RIGHT", "DOWN", "LEFT"};
// void print_Q(t_Qtable *Q) {
//   for (short k = up; k < ACTION; ++k) {
//     printf("Qstrategy ...%s\n", direct[k]);
//     for (int i = 0; i < 10; ++i) {
//       for (int j = 0; j < 10; ++j) {
//         printf("% 8.1f  ", *(Q->strategy[k] + i * Q->m + j));
//       }
//       printf("\n");
//     }
//   }
// }

void read_Q(t_Qtable **Q) {
  initialize_Q(Q, 10, 10);
  FILE *f = fopen("tests/Q_10_10", "r");
  fscanf(f, "%d %d", &((*Q)->m), &((*Q)->n));
  int tmp = 0;
  for (int k = 0; k < 4; ++k) {
    fscanf(f, "%d", &tmp);
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        fscanf(f, "%f", &((*Q)->strategy[k][i * (*Q)->m + j]));
      }
    }
  }
  fclose(f);
}

START_TEST(test_q_add_1) {
  t_Qtable *Q = NULL;
  read_Q(&Q);

  short max_action = 0;
  type_Q max_s = max_strategy_and_action(Q, 0, &max_action);
  ck_assert_int_eq(max_action, 1);
  ck_assert_float_eq(max_s, 498300);

  max_s = max_strategy_and_action(Q, 90, &max_action);
  ck_assert_int_eq(max_action, 0);
  ck_assert_float_eq(max_s, 0);

  max_s = max_strategy_and_action(Q, 9, &max_action);
  ck_assert_int_eq(max_action, 2);
  ck_assert_float_eq(max_s, -800);

  max_s = max_strategy_and_action(Q, 89, &max_action);
  ck_assert_int_eq(max_action, 2);
  ck_assert_float_eq(max_s, 500000);

  free_Qtable(Q);
}
END_TEST

START_TEST(test_q_add_2) {
  t_Qtable *Q = NULL;
  read_Q(&Q);

  short next = 0;
  next = next_step(Q, 1, up);
  ck_assert_int_eq(next, -1);

  next = next_step(Q, 1, left);
  ck_assert_int_eq(next, 0);

  next = next_step(Q, 1, right);
  ck_assert_int_eq(next, 2);

  next = next_step(Q, 1, down);
  ck_assert_int_eq(next, 11);

  next = next_step(Q, 53, up);
  ck_assert_int_eq(next, 43);

  next = next_step(Q, 53, right);
  ck_assert_int_eq(next, -1);

  next = next_step(Q, 53, down);
  ck_assert_int_eq(next, 63);

  next = next_step(Q, 53, left);
  ck_assert_int_eq(next, -1);

  free_Qtable(Q);
}
END_TEST

START_TEST(test_q_add_3) {
  t_Qtable *Q = NULL;
  read_Q(&Q);
  set_ML_mode(Q, GREEDY);

  short next_action = 0;
  next_action = choice_action(Q, 0);
  ck_assert_int_eq(next_action, right);

  next_action = choice_action(Q, 1);
  ck_assert_int_eq(next_action, down);

  next_action = choice_action(Q, 40);
  ck_assert_int_eq(next_action, down);

  next_action = choice_action(Q, 94);
  ck_assert_int_eq(next_action, left);

  free_Qtable(Q);
}
END_TEST

START_TEST(test_q_add_4) {
  t_Qtable *Q = NULL;
  read_Q(&Q);

  set_ML_mode(Q, STUDY);
  ck_assert_float_eq(Q->alpha, ALPHA_STD);
  ck_assert_float_eq(Q->sigma, SIGMA_STD);
  ck_assert_int_eq(Q->rand_choice, RAND_CHOICE_STD);

  set_ML_mode(Q, GREEDY);
  ck_assert_float_eq(Q->alpha, ALPHA_GREEDY);
  ck_assert_float_eq(Q->sigma, SIGMA_GREEDY);
  ck_assert_int_eq(Q->rand_choice, RAND_CHOICE_GREEDY);

  free_Qtable(Q);
}
END_TEST

START_TEST(test_q_add_5) {
  t_maze maze;
  load_from_file("mazes/maze_10_10", &maze);
  t_graph g_maze[10 * 10];
  maze_to_graph(&maze, g_maze);
  int reward = 0;
  reward = get_reward(g_maze, 1, down, 99);
  ck_assert_int_eq(reward, -100);

  reward = get_reward(g_maze, 1, up, 99);
  ck_assert_int_eq(reward, -50000);

  reward = get_reward(g_maze, 89, down, 99);
  ck_assert_int_eq(reward, 500000);

  free_mem_maze(&maze);
}
END_TEST

Suite *test_s21_q_learn_add(void) {
  Suite *s = suite_create("\033[45m-=test_s21_q_learn_add=-\033[0m");
  TCase *tc = tcase_create("test_s21_q_learn_add");

  tcase_add_test(tc, test_q_add_1);
  tcase_add_test(tc, test_q_add_2);
  tcase_add_test(tc, test_q_add_3);
  tcase_add_test(tc, test_q_add_4);
  tcase_add_test(tc, test_q_add_5);

  suite_add_tcase(s, tc);
  return s;
}