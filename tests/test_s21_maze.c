#include "test_s21_maze.h"

int main(void) {
  int failed = 0;
  int total = 0;

  Suite *test_s21_maze[] = {test_s21_maze_ideal(),     test_s21_cave(),
                            test_s21_get_route_maze(), test_s21_maze_ml_5x5(),
                            test_s21_maze_ml_10x10(),  test_s21_maze_ml_20x20(),
                            test_s21_maze_ml_50x50(),  test_s21_q_learn_add(),
                            test_s21_route_add(),      NULL};

  for (int i = 0; test_s21_maze[i]; i++) {
    SRunner *sr = srunner_create(test_s21_maze[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    total += srunner_ntests_run(sr);
    srunner_free(sr);
  }
  printf("\033[41m========= FAILED : %-3d =========\033[0m\n", failed);
  printf("\033[42m\033[30m========= SUCCESS: %-3d =========\033[0m\n",
         total - failed);
  printf("\033[42m\033[30m========= TOTAL: %-3d =========\033[0m\n", total);

  return failed == 0 ? 0 : 1;
}
