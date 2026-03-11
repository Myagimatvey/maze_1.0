#include "alphabet.h"

#include "console-interface.h"

void write_str(WINDOW *win, int y, int x, char *str, int check) {
  int str_lenght = strlen(str);
  char (*ptr_aphbt[27])(int, int) = {
      aphbt_a, aphbt_b, aphbt_c, aphbt_d, aphbt_e, aphbt_f, aphbt_g,
      aphbt_h, aphbt_i, aphbt_j, aphbt_k, aphbt_l, aphbt_m, aphbt_n,
      aphbt_o, aphbt_p, aphbt_q, aphbt_r, aphbt_s, aphbt_t, aphbt_u,
      aphbt_v, aphbt_w, aphbt_x, aphbt_y, aphbt_z};

  wattron(win, COLOR_PAIR(check));

  for (int i = 0; i < str_lenght; i++) {
    for (int n = 0; n < 4; n++)
      for (int m = 0; m < 3; m++)
        mvwprintw(
            win, y + n, x + m + (i * 3), "%c",
            (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
                ? ptr_aphbt[tolower(str[i]) - 'a'](n, m)
            : (str[i] >= '0' && str[i] <= '9') ? clock_face(str[i] - '0', n, m)
                                               : ' ');
  }

  wattroff(win, COLOR_PAIR(check));

  wrefresh(win);
}

char aphbt_a(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', '_', '|'}, {'|', ' ', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_b(int y, int x) {
  char dis[4][3] = {
      {'.', '_', ' '}, {'|', '_', '\\'}, {'|', '_', '/'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_c(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', ' ', ' '}, {'|', '_', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_d(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', ' ', '\\'}, {'|', '_', '/'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_e(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', '_', ' '}, {'|', '_', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_f(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', '_', ' '}, {'|', ' ', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_g(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', ' ', ' '}, {'|', '_', ']'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_h(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', '_', '|'}, {'|', ' ', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_i(int y, int x) {
  char dis[4][3] = {
      {' ', '.', ' '}, {' ', '|', ' '}, {' ', '|', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_j(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {' ', ' ', '|'}, {'|', '_', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_k(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', '/', '_'}, {'|', ' ', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_l(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', ' ', ' '}, {'|', '_', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_m(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', '|', '|'}, {'|', ' ', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_n(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', '\\', '|'}, {'|', ' ', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_o(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', ' ', '|'}, {'|', '_', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_p(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', '_', '|'}, {'|', ' ', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_q(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', ' ', '|'}, {'|', '_', '\\'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_r(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', '_', '|'}, {'|', '\\', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_s(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {'|', '_', ' '}, {' ', '_', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_t(int y, int x) {
  char dis[4][3] = {
      {'_', '_', '_'}, {' ', '|', ' '}, {' ', '|', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_u(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', ' ', '|'}, {'|', '_', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_v(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', ' ', '|'}, {' ', 'V', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_w(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', ' ', '|'}, {'\\', '|', '/'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_x(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'\\', ' ', '/'}, {'/', ' ', '\\'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_y(int y, int x) {
  char dis[4][3] = {
      {' ', ' ', ' '}, {'|', '_', '|'}, {' ', '_', '|'}, {' ', ' ', ' '}};

  return dis[y][x];
}
char aphbt_z(int y, int x) {
  char dis[4][3] = {
      {' ', '_', ' '}, {' ', '/', ' '}, {'/', '_', ' '}, {' ', ' ', ' '}};

  return dis[y][x];
}