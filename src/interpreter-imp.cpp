module;

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

module interpreter;

using namespace std::chrono_literals;

std::string state_to_string(State state)
{
	switch (state) {
	case State::Stopped:
		return "STOPPED";
	case State::Paused:
		return "PAUSED";
	case State::Running:
		return "RUNNING";
	case State::Interrupted:
		return "INTERRUPTED";
	}
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
	std::cout << "\r\n\n----------\r\n\n\e[1;93m" << _output.str() << "\e[m\r\n\n";
	if (state != State::Running) std::cout << "\e[1;93m[" << state_to_string(state) << "]\e[m" << std::flush;
}

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

bool Interpreter::should_quit() const
{
	return state == State::Stopped || state == State::Interrupted;
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
	state = State::Running;
	while (state == State::Running || state == State::Paused) {
		print_info();
		std::this_thread::sleep_for(75ms);
		if (state == State::Paused) continue;
		if (_head >= _vector.size()) {
			_vector.resize(_head+1);
			_vector[_head] = 0;
		}
		else if (_head < 0) throw("Head out of range");
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
				state = State::Stopped;
				break;
		}
		++_instruction_pointer;
	}
	std::cout << "\r\nPress \e[1;93many key\e[m to exit" << std::flush;
	return _output.str();
}

void Interpreter::interrupt()
{
	state = State::Interrupted;
}

void Interpreter::toggle_pause()
{
	if (state == State::Paused) state = State::Running;
	else if (state == State::Running) state = State::Paused;
}
