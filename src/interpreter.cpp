module;

#include <sstream>
#include <stack>
#include <string>
#include <vector>

export module interpreter;

export class Interpreter
{
	public:
		Interpreter();
		~Interpreter();

		void load_from_file(const std::string &);
		std::string run();

	private:
		void print_info() const;

		size_t _head, _instruction_pointer;
		std::string _code;
		std::stringstream _output;
		std::stack<size_t> _return_stack;
		std::vector<uint8_t> _vector;
};
