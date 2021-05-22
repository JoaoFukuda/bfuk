#include <iostream>
#include <thread>

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
			std::thread t ([&] () { p.run(); });
			while (true) {
				char input = std::cin.get();
				if (p.should_quit()) break;
				switch (input) {
					case 'q':
						p.interrupt();
						break;
					case ' ':
						p.toggle_pause();
						break;
				}
			}
			t.join();
		}
		catch (std::exception & e) {
			std::cerr << "\e[1;91m[ERROR]\e[m " << e.what();
		}
	}
}
