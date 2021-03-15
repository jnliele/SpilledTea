#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <gtkmm.h>
#include <cstdlib>
#include "boba.h"

using namespace std;

int main(int argc, char **argv)
{
  Gtk::Main app(argc, argv);
  Boba_shop b1;
  Gtk::Main::run(b1);
  return 0;
}
