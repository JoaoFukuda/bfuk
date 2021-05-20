#include <iostream>

import terminal;
import interpreter;

int main(int argc, char* argv[])
{
	Interpreter p;

	if (argc == 2) {
		p.load_from_file(argv[1]);
	}

	{
		Terminal t;
		try {
			p.run();
		}
		catch (std::exception & e) {
			std::cerr << "\e[1;91m[ERROR]\e[m " << e.what();
		}
	}
}
