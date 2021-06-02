#include "term.hpp"

#include <iostream>

using namespace Terminal;

void Terminal::begin()
{
   system("/bin/stty raw -echo");
   std::cout << "\x1b[?1049h"
             << "\x1b[?25l"
             << "\x1b[1;1H";
}

void Terminal::end()
{
   std::cout << "\x1b[?25h"
             << "\x1b[?1049l" << std::flush;
   system("/bin/stty -raw echo");
}
