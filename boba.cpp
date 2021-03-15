#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <gtkmm.h>
#include <cstdlib>
#include "boba.h"

using namespace std;

Boba_shop::Boba_shop(){
  // keep a running total of number of orders
  order_num = 0;

  // set window border and title of window
  set_border_width(10);
  set_title("~~Welcome to SpilledTea~~");

  // set picture of shop logo
  logo.set("logo.png");
  grid.attach(logo,0,0,1,1);

  // create and attach buttons to start ordering or exit shop
  start_order.add_label("Start Order");
  start_order.signal_pressed().connect(sigc::mem_fun(*this,&Boba_shop::on_button_start_order));
  grid.attach(start_order,0,2,1,1);

  exit.add_label("Exit");
  exit.signal_pressed().connect(sigc::mem_fun(*this,&Boba_shop::on_button_exit));
  grid.attach(exit,0,3,1,1);

  // make the grid visible
  grid.show_all();
  add(grid);
}
Boba_shop::~Boba_shop(){}
void Boba_shop::show_menu()
{
  // show drink menu to customer
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_transient_for(w);
  dialog->set_size_request(500,100);
  dialog->set_title("~~Drink Menu~~");
  Gtk::Label *label = new Gtk::Label("1. Classic Milk Tea.....................$3.00\n2. Matcha Milk Tea....................$3.25\n3. Thai Tea...................................$3.50\n4. Taro Milk Tea..........................$3.75\n\nEnter the number of the drink you want (1-4):");
  dialog->get_content_area()->pack_start(*label);
  label->show();
  dialog->add_button("Next",1);
  dialog->set_default_response(1);

  // text box for customer to enter their choice of drink
  Gtk::Entry *choice = new Gtk::Entry();
  choice->set_max_length(1);
  choice->show();
  dialog->get_vbox()->pack_start(*choice);

  // store customer's input
  int result = dialog->run();
  if (result==1)
  {
    string input = choice->get_text();

    // create drink for customer
    Boba b1;
    b1.drink_price = 0;
    b1.topping_price = 0;
    customers.at(order_num-1).full_order.push_back(b1);

    // keep track of drink index
    int i = customers.at(order_num-1).diff_drinks; // index of current drink
    customers.at(order_num-1).diff_drinks += 1; // update current amount of different drinks

    if (input == "1")
    {
      // store drink and price information for customer
      customers.at(order_num-1).full_order.at(i).drink = "Classic Milk Tea";
      customers.at(order_num-1).full_order.at(i).drink_price = 3.00;
    }
    else if (input == "2")
    {
      // store drink and price information for customer
      customers.at(order_num-1).full_order.at(i).drink = "Matcha Milk Tea";
      customers.at(order_num-1).full_order.at(i).drink_price = 3.25;
    }
    else if (input == "3")
    {
      // store drink and price information for customer
      customers.at(order_num-1).full_order.at(i).drink = "Thai Tea";
      customers.at(order_num-1).full_order.at(i).drink_price = 3.50;
    }
    else if (input == "4")
    {
      // store drink and price information for customer
      customers.at(order_num-1).full_order.at(i).drink = "Taro Milk Tea";
      customers.at(order_num-1).full_order.at(i).drink_price = 3.75;
    }
  }
  dialog->close();
  delete dialog;
  delete label;
  delete choice;
}
void Boba_shop::show_topping()
{
  // show menu of toppings to customer
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_transient_for(w);
  dialog->set_size_request(500,100);
  dialog->set_title("~~Topping~~");
  Gtk::Label *label = new Gtk::Label("1. Classic Boba Pearls.....................$0.50\n2. Mini Boba Pearls..........................$0.75\n3. Lychee Jelly....................................$1.00\n4. None...............................................$0.00\n\nEnter the number of the topping you want (1-4):");
  dialog->get_content_area()->pack_start(*label);
  label->show();
  dialog->add_button("Next",1);
  dialog->set_default_response(1);

  // text box for customer to enter their choice of topping
  Gtk::Entry *choice = new Gtk::Entry();
  choice->set_max_length(1);
  choice->show();
  dialog->get_vbox()->pack_start(*choice);

  // store customer's input
  int result = dialog->run();
  if (result==1)
  {
    string input = choice->get_text();

    // get index of current drink
    int i = customers.at(order_num-1).diff_drinks - 1;

    if (input == "1")
    {
      // store topping and update price information for current drink
      customers.at(order_num-1).full_order.at(i).topping = "Classic Boba Pearls";
      customers.at(order_num-1).full_order.at(i).topping_price = 0.50;
    }
    else if (input == "2")
    {
      // store topping and update price information for current drink
      customers.at(order_num-1).full_order.at(i).topping = "Mini Boba Pearls";
      customers.at(order_num-1).full_order.at(i).topping_price = 0.75;
    }
    else if (input == "3")
    {
      // store topping and update price information for current drink
      customers.at(order_num-1).full_order.at(i).topping = "Lychee Jelly";
      customers.at(order_num-1).full_order.at(i).topping_price = 1.00;
    }
    else if (input == "4")
    {
      // customer chooses no topping
      customers.at(order_num-1).full_order.at(i).topping_price = 0;
    }
  }
  dialog->close();
  delete dialog;
  delete label;
  delete choice;
}
void Boba_shop::get_quantity()
{
  // get index of current drink
  int i = customers.at(order_num-1).diff_drinks - 1;

  // create window to get quantity of current drink
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_transient_for(w);
  dialog->set_size_request(500,100);
  dialog->set_title("Confirm order for current drink:");

  // construct string of customer's order to see the current drink they have ordered
  string order = customers.at(order_num-1).full_order.at(i).drink;
  if (!customers.at(order_num-1).full_order.at(i).topping.empty()) // if the customer has a topping
  {
    order += " with "+ customers.at(order_num-1).full_order.at(i).topping;
  }

  // ask for quantity of the current drink ordered
  order += "\nQuantity: ";
  Gtk::Label *label = new Gtk::Label(order);
  dialog->get_content_area()->pack_start(*label);
  label->show();
  dialog->add_button("Next",1);
  dialog->set_default_response(1);

  // text box for customer to enter desired quantity of current drink
  Gtk::Entry *quantity = new Gtk::Entry();
  quantity->set_text("1");
  quantity->set_max_length(2);
  quantity->show();
  dialog->get_vbox()->pack_start(*quantity);

  // store customer's input
  int result = dialog->run();
  if (result==1)
  {
    string ans = quantity->get_text();

    // get index of current drink
    int i = customers.at(order_num-1).diff_drinks - 1;
    // store desired quantity of current drink
    customers.at(order_num-1).full_order.at(i).quantity = ans;
    // update price for the current drink's price and topping price based on quantity of the current drink
    float multiplier = stof(ans);
    customers.at(order_num-1).full_order.at(i).drink_price *= multiplier;
    customers.at(order_num-1).full_order.at(i).topping_price *= multiplier;

    // update the total cost of customer's order
    customers.at(order_num-1).total += customers.at(order_num-1).full_order.at(i).drink_price + customers.at(order_num-1).full_order.at(i).topping_price;
  }
  dialog->close();
  delete dialog;
  delete label;
  delete quantity;
}
void Boba_shop::print_receipt()
{
  // print receipt for customer
  // create window showing receipt
  string message = "<b>Order #" + to_string(order_num)+"</b>";
  Gtk::MessageDialog dialog(*this,message,true,Gtk::MESSAGE_OTHER);

  // create the message for the body of the receipt
  string receipt = "Server: Julie Le";
  receipt += "\nCustomer: " + customers.at(order_num-1).full_name;
  receipt += "\n_____________________________________________";
  for (int i = 0; i<customers.at(order_num-1).full_order.size(); i++)
  {
    // format drink price to 2 decimal places
    stringstream stream;
    stream << fixed << setprecision(2) << customers.at(order_num-1).full_order.at(i).drink_price;
    string dp = stream.str();

    // add quantity and drink
    receipt += "\n" + customers.at(order_num-1).full_order.at(i).quantity + "\t" + customers.at(order_num-1).full_order.at(i).drink;
    receipt += " $" + dp;
    if (!customers.at(order_num-1).full_order.at(i).topping.empty()) // if the customer has a topping
    {
      // format topping price to 2 decimal places
      stringstream stream2;
      stream2 << fixed << setprecision(2) << customers.at(order_num-1).full_order.at(i).topping_price;
      string tp = stream2.str();
      // print topping info
      receipt += "\n\t" + customers.at(order_num-1).full_order.at(i).topping;
      receipt += " $" + tp;
    }
  }
  // format total price to 2 decimal places
  stringstream stream3;
  stream3 << fixed << setprecision(2) << customers.at(order_num-1).total;
  string tot = stream3.str();

  // print cost of total
  receipt += "\n_____________________________________________";
  receipt += "\nTotal: $" + tot;
  receipt += "\n\n\nThank you for your order.\nPlease come again! :)";

  dialog.set_secondary_text(receipt, true);
  dialog.run();
}
void Boba_shop::order_more()
{
  // allow user to choose to order another drink or complete ordering
  // create window to prompt the user
  Gtk::MessageDialog dialog(*this, "Complete your order?\nYes - Print Receipt\nNo - Add another drink to order",false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
  int answer = dialog.run();

  switch(answer)
  {
    case(Gtk::RESPONSE_YES): print_receipt(); break;
    case(Gtk::RESPONSE_NO): show_menu();
                            show_topping();
                            get_quantity();
                            order_more();
                            break;
  }
}
void Boba_shop::on_button_start_order()
{
  // start boba order
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_transient_for(w);
  dialog->set_size_request(500,100);
  dialog->set_title("Boba Order");

  // get customer's name
  Gtk::Label *label = new Gtk::Label("Welcome dear customer! Enter your full name:");
  dialog->get_content_area()->pack_start(*label);
  label->show();

  dialog->add_button("Next",1);
  dialog->set_default_response(1);

  // text box for customer to enter their full name
  Gtk::Entry *entry_name = new Gtk::Entry();
  entry_name->set_text("FirstName LastName");
  entry_name->set_max_length(50);
  entry_name->show();
  dialog->get_vbox()->pack_start(*entry_name);

  // store customer's input
  int result = dialog->run();
  if (result==1)
  {
    // create entry for customer's information
    Customer c1;
    c1.full_name = entry_name->get_text();
    c1.total = 0; // no items ordered yet so $0.00
    c1.diff_drinks = 0; // no drinks ordered yet
    customers.push_back(c1);

    // update order number
    order_num += 1;
  }
  dialog->close();
  delete dialog;
  delete label;
  delete entry_name;

  // show drink menu to customer
  show_menu();
  show_topping();
  get_quantity();
  order_more();
}
void Boba_shop::on_button_exit()
{
  close();
}