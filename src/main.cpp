#include <iostream>
#include <thread>

import terminal;
import interpreter;

int main(int argc, char* argv[])
{
	Interpreter interpreter;

	if (argc == 2) {
		interpreter.load_from_file(argv[1]);
	}

	{
		Terminal t;
		try {
			std::thread t ([&] () { interpreter.run(); });
			while (true) {
				char input = std::cin.get();
				if (interpreter.should_quit()) {
					break;
				}
				else if (interpreter.waiting_input()) {
					interpreter.send_input(input);
				}
				else {
					switch (input) {
						case 'q':
							interpreter.interrupt();
							break;
						case ' ':
							interpreter.toggle_pause();
							break;
					}
				}
			}
			t.join();
		}
		catch (std::exception & e) {
			std::cerr << "\e[1;91m[ERROR]\e[m " << e.what();
		}
	}
}
