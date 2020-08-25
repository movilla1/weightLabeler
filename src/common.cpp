#include "common.h"

void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *text, chtype color)
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
  WINDOW *alert = derwin(win, 10, 40, 5, 5);
  wclear(alert);
  start_color();
  box(alert, 0, 0);
  if (isError) {
    wattron(alert, COLOR_PAIR(COLOR_ERROR));
  } else {
    wattron(alert, COLOR_PAIR(COLOR_NORMAL));
  }
  mvwprintw(alert, 1, 2, text);
  if (isError) {
    wattroff(alert, COLOR_PAIR(COLOR_ERROR));
  } else {
    wattroff(alert, COLOR_PAIR(COLOR_NORMAL));
  }
  wattron(alert, COLOR_PAIR(COLOR_NORMAL));
  mvwprintw(alert, 2, 2, "Pulse una tecla para continuar");
  wattroff(alert, COLOR_PAIR(COLOR_NORMAL));
  wrefresh(alert);
  wrefresh(win);
  wtimeout(alert, -1);
  wgetch(alert);
  wtimeout(alert, 0);
  delwin(alert);
  wrefresh(win);
}
