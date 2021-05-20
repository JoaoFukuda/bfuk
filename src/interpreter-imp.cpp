module;

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

module interpreter;

using namespace std::chrono_literals;

Interpreter::Interpreter()
{
	_head = 0;
	_instruction_pointer = 0;
	_vector = {};
	_return_stack = {};
	_code = "++++++++++++++++++++++++++++++++++++++++++++++++>++++++++++[<.>-]";
}

Interpreter::~Interpreter()
{
}

void Interpreter::load_from_file(const std::string & filename)
{
	std::ifstream file(filename);
	if (file) {
		std::stringstream sstr;
		sstr << file.rdbuf();
		_code = sstr.str();
		file.close();
	}
}

std::string Interpreter::run()
{
	bool quit = false;
	while (!quit) {
		print_info();
		std::this_thread::sleep_for(75ms);
		if (_head >= _vector.size()) {
			_vector.resize(_head+1);
			_vector[_head] = 0;
		}
		else if (_head < 0) throw("_Head out of range");
		switch (_code[_instruction_pointer]) {
			case '+':
				++_vector[_head];
				break;
			case '-':
				--_vector[_head];
				break;
			case '>':
				++_head;
				break;
			case '<':
				--_head;
				break;
			case ',':
				_vector[_head] = static_cast<char>(std::cin.get());
				break;
			case '.':
				_output << static_cast<char>(_vector[_head]);
				break;
			case'[':
				_return_stack.push(_instruction_pointer);
				break;
			case ']':
				if (_vector[_head] != 0) {
					if (!_return_stack.empty()) {
						_instruction_pointer = _return_stack.top();
					}
					else {
						throw("No loop to return to");
					}
				}
				else {
					_return_stack.pop();
				}
				break;
			default:
				quit = true;
				break;
		}
		++_instruction_pointer;
	}
	return _output.str();
}

void Interpreter::print_info() const
{
	std::cout << "\e[2J" << "\e[1;1H";
	for (int i = 0; i != _code.size(); ++i) {
		std::cout << (i == _instruction_pointer ? "\e[1;30;103m" : "\e[1;93m") << _code[i] << "\e[m";
	}
	std::cout << "\r\n\n";
	for (int i = 0; i != _vector.size(); ++i) {
		std::cout << "[" << (i == _head ? "\e[1;30;103m" : "\e[1;93m") << " " << static_cast<int>(_vector[i]) << " \e[m] ";
	}
	std::cout << "\r\n\n----------\r\n\n\e[1;93m" << _output.str() << "\e[m" << std::flush;
}
