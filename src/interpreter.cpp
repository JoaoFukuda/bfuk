module;

#include <sstream>
#include <stack>
#include <string>
#include <vector>

export module interpreter;

enum class State
{
	Stopped,
	Paused,
	Running,
	Interrupted
};

export class Interpreter
{
	private:
		State state = State::Stopped;
		size_t _head, _instruction_pointer;
		std::string _code;
		std::stringstream _output;
		std::stack<size_t> _return_stack;
		std::vector<uint8_t> _vector;

		void print_info() const;

	public:
		Interpreter();
		~Interpreter();

		bool should_quit() const;

		void load_from_file(const std::string &);
		std::string run();
		void interrupt();
		void toggle_pause();
};
