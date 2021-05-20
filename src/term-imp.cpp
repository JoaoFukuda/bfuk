module;

#include <iostream>

module terminal;

Terminal::Terminal()
{
	system("/bin/stty raw -echo");
	std::cout << "\e[?1049h" << "\e[?25l" << "\e[1;1H";
}

Terminal::~Terminal()
{
	std::cout << "\r\nPress \e[1;93many key\e[m to exit";
	std::cin.get();
	std::cout << "\e[?25h" << "\e[?1049l" << std::flush;
	system("/bin/stty -raw echo");
}
