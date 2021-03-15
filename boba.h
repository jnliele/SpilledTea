#ifndef _BOBA_H
#define _BOBA_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <gtkmm.h>
#include <cstdlib>

using namespace std;

class Boba{
public:
  string drink;
  string topping;
  float drink_price;
  float topping_price;
  string quantity;
};
class Customer{
public:
  string full_name;
  vector<Boba> full_order;
  float total;
  int diff_drinks;
};
class Boba_shop: public Gtk::Window{
public:
    Boba_shop();
    ~Boba_shop();
    int order_num;
    vector<Customer> customers;
protected:
    Gtk::Button start_order, exit;
    Gtk::Grid grid;
    Gtk::Image logo;
    void print_receipt();
    void show_menu();
    void show_topping();
    void get_quantity();
    void order_more();
    void on_button_start_order();
    void on_button_exit();
};
#endif