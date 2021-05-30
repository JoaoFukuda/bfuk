module;

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

module interpreter;

using namespace std::chrono_literals;

inline bool isValidChar(const char c)
{
	for (const char valid_c : "-+,.[]<>") {
		if (c == valid_c)
			return true;
	}
	return false;
}

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
	case State::WaitingInput:
		return "WAITING_INPUT";
	}
	return "UNKNOWN";
}

void Interpreter::print_info() const
{
	std::stringstream buffer;
	buffer << "\e[2J" << "\e[1;1H";
	for (int i = 0; i != _code.size(); ++i) {
		buffer << (i == _instruction_pointer ? "\e[1;30;103m" : "\e[1;93m") << _code[i] << "\e[m";
		if (_code[i] == '\n') buffer << '\r';
	}
	buffer << "\r\n\n";
	for (int i = 0; i != _vector.size(); ++i) {
		buffer << "[" << (i == _head ? "\e[1;30;103m" : "\e[1;93m") << " " << static_cast<int>(_vector[i]) << " \e[m] ";
	}
	buffer << "\r\n\n----------\r\n\n\e[1;93m" << _output.str() << "\e[m\r\n\n";
	if (state != State::Running) buffer << "\e[1;93m[" << state_to_string(state) << "]\e[m";
	std::cout << buffer.str() << std::flush;
}

Interpreter::Interpreter()
{
	_head = 0;
	_instruction_pointer = 0;
	_vector = {};
	_return_stack = {};
	_code = "++++++\n[\n\t>++++++++\n\t<-\n]\n++++++++++\n[\n\t>.\n\t<-\n]";
	_input_m.lock();
}

Interpreter::~Interpreter()
{ }

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
		if (_head == static_cast<size_t>(-1)) {
			_vector.insert(_vector.begin(), 0);
			_head = 0;
		}
		else if (_head >= _vector.size()) {
			_vector.resize(_head+1);
			_vector[_head] = 0;
		}
		print_info();
		std::this_thread::sleep_for(50ms);
		if (state == State::Paused) continue;
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
				state = State::WaitingInput;
				print_info();
				_input_m.lock();
				state = State::Running;
				_vector[_head] = _input;
				if (_vector[_head] >= '0' && _vector[_head] <= '9') {
					_vector[_head] -= '0';
				}
				break;
			case '.':
				_output << static_cast<char>(_vector[_head]);
				if (static_cast<char>(_vector[_head]) == '\n') _output << '\r';
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
		do {
			++_instruction_pointer;
		} while (!isValidChar(_code[_instruction_pointer]));
	}
	std::cout << "\r\nPress \e[1;93many key\e[m to exit" << std::flush;
	return _output.str();
}

void Interpreter::send_input(char input)
{
	_input = input;
	_input_m.unlock();
}

bool Interpreter::waiting_input() const
{
	return state == State::WaitingInput;
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
