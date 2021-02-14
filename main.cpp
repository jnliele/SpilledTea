#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <gtkmm.h>
#include "boba.h"

using namespace std;

int main(int argc, char **argv)
{
    Gtk::Main app(argc, argv);
    Order o1;
    Gtk::Main::run(o1);
    return 0;
}
