#include "term.hpp"

#include <iostream>

Terminal::Terminal()
{
	system("/bin/stty raw -echo");
	std::cout << "\e[?1049h" << "\e[?25l" << "\e[1;1H";
}

Terminal::~Terminal()
{
	std::cout << "\e[?25h" << "\e[?1049l" << std::flush;
	system("/bin/stty -raw echo");
}
