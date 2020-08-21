#include "common.h"

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *text, chtype color)
{
  int length, x, y;
  float temp;

  if (win == NULL)
    win = stdscr;
  getyx(win, y, x);
  if (startx != 0)
    x = startx;
  if (starty != 0)
    y = starty;
  if (width == 0)
    width = 80;

  length = strlen(text);
  temp = (width - length) / 2;
  x = startx + (int)temp;
  wattron(win, color);
  mvwprintw(win, y, x, "%s", text);
  wattroff(win, color);
  refresh();
}

std::string getCurrentDate()
{
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
  std::string str(buffer);
  return (str);
}

void showAlert(WINDOW *win, const char *text, bool isError)
{
  chtype color = isError ? COLOR_PAIR(COLOR_ERROR) : COLOR_PAIR(COLOR_NORMAL);
  int maxX = getmaxx(win);
  print_in_middle(win, 1, 10, maxX - 1, (char *)text, color);
  print_in_middle(win, 2, 10, maxX - 1, "Pulse una tecla para continuar", COLOR_NORMAL);
  wrefresh(win);
  wtimeout(win, -1);
  wgetch(win);
  wtimeout(win, 0);
}
