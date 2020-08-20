#include "crear_articulo.h"
#define CREATE_MENU_SIZE 3

CrearArticulo::CrearArticulo(DbInterface *db)
{
  this->running = true;
  this->db = db;
  this->dlgArea = newwin(20,70,3,5);
  keypad(this->dlgArea, true);
  start_color();
  this->setupForm();
  this->draw();
}

void CrearArticulo::run()
{
  int ch = wgetch(this->dlgArea);
  switch (ch)
  {
  case KEY_DOWN:
    /* Go to next field */
    form_driver(this->form, REQ_NEXT_FIELD);
    form_driver(this->form, REQ_END_LINE);
    break;
  case KEY_UP:
    /* Go to previous field */
    form_driver(this->form, REQ_PREV_FIELD);
    form_driver(this->form, REQ_END_LINE);
    break;
  case KEY_F(2):
    form_driver(this->form, REQ_VALIDATION);
    this->saveData();
    this->startNew();
    break;
  case KEY_F(4):
    form_driver(this->form, REQ_VALIDATION);
    this->saveData();
    this->running = false;
    break;
  case KEY_F(8):
    this->running = false;
    break;
  case KEY_BACKSPACE:
    form_driver(this->form, REQ_DEL_PREV);
    break;
  case KEY_DC:
    form_driver(form, REQ_DEL_CHAR);
    break;
  case KEY_LEFT:
    form_driver(this->form, REQ_PREV_CHAR);
    break;
  case KEY_RIGHT:
    form_driver(this->form, REQ_NEXT_CHAR);
    break;
  default:
    form_driver(this->form, ch);
    break;
  }
  wrefresh(this->dlgArea);
}

CrearArticulo::~CrearArticulo()
{
  free_field(this->fields[0]);
  free_field(this->fields[1]);
  free_field(this->fields[2]);
  free_field(this->fields[3]);
  free_field(this->fields[4]);
  unpost_form(this->form);
  free_form(this->form);
  delwin(this->dlgArea);
}

void CrearArticulo::draw()
{
  box(this->dlgArea, 0, 0);
  mvwprintw(this->dlgArea, 4, 1, "NOMBRE     :");
  mvwprintw(this->dlgArea, 5, 1, "DESCRIPCION:");
  mvwprintw(this->dlgArea, 6, 1, "PRECIO     :");
  mvwprintw(this->dlgArea, 7, 1, "UPC        :");
  mvwprintw(this->dlgArea, 8, 1, "SKU        :");
  init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
  wattron(this->dlgArea, COLOR_PAIR(1));
  mvwprintw(this->dlgArea, 1, 6, "F8 Cancel, F4 Save and return, F2 Save and continue");
  wattroff(this->dlgArea, COLOR_PAIR(1));
  wrefresh(this->dlgArea);
}

void CrearArticulo::setupForm()
{
  this->fields[0] = new_field(1, 30, 0, 0, 0, 0);
  this->fields[1] = new_field(1, 50, 1, 0, 0, 0);
  this->fields[2] = new_field(1, 8, 2, 0, 0, 0);
  this->fields[3] = new_field(1, 15, 3, 0, 0, 0);
  this->fields[4] = new_field(1, 30, 4, 0, 0, 0);
  this->fields[5] = NULL;

  set_field_back(this->fields[0], A_UNDERLINE); /* Print a line for the option 	*/
  set_field_back(this->fields[1], A_UNDERLINE); /* Print a line for the option 	*/
  set_field_back(this->fields[2], A_UNDERLINE); /* Print a line for the option 	*/
  set_field_back(this->fields[3], A_UNDERLINE); /* Print a line for the option 	*/
  set_field_back(this->fields[4], A_UNDERLINE); /* Print a line for the option 	*/
  field_opts_off(this->fields[0], O_AUTOSKIP);
  field_opts_off(this->fields[1], O_AUTOSKIP);
  field_opts_off(this->fields[2], O_AUTOSKIP);
  field_opts_off(this->fields[3], O_AUTOSKIP);
  field_opts_off(this->fields[4], O_AUTOSKIP);
  this->form = new_form(this->fields);
  set_form_win(this->form, this->dlgArea);
  set_form_sub(this->form, derwin(this->dlgArea, 15, 50, 4, 15));
  post_form(this->form);
  wrefresh(this->dlgArea);
}

bool CrearArticulo::saveData()
{
  Articulo art;
  art.nombre = field_buffer(fields[0], 0);
  art.descripcion = field_buffer(fields[1], 0);
  art.precio = atof(field_buffer(fields[2], 0));
  art.upc = field_buffer(fields[3], 0);
  art.sku = field_buffer(fields[4], 0);
  art.fecha = getCurrentDate();
  bool ret = this->db->grabarArticulo(&art);
  return(ret);
}

void CrearArticulo::startNew()
{
  for (int i = 0; i < 5; i++)
  {
    set_current_field (this->form, this->fields[i]);
    form_driver (this->form, REQ_CLR_FIELD);
  }
  return;
}