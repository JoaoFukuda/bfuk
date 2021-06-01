#include "term.hpp"

#include <iostream>

Terminal::Terminal()
{
	system("/bin/stty raw -echo");
	std::cout << "\x1b[?1049h" << "\x1b[?25l" << "\x1b[1;1H";
}

Terminal::~Terminal()
{
	std::cout << "\x1b[?25h" << "\x1b[?1049l" << std::flush;
	system("/bin/stty -raw echo");
}
