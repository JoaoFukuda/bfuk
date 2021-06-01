#include "interpreter.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("Interpreter")
{
	SECTION("Basic programs") {
		auto& [code, output] = GENERATE( table<std::string, std::string> ({
				{"++++++++++++++++++++++++++++++++++++++++++++++++.", "0"},
				{"++++++[>++++++++<-]>.", "0"},
				{"++++++[>++++++++<-]++++++++++[>.+<-]", "0123456789"}
			}));

		Interpreter i;
		i.load_from_string(code);
		CHECK(i.run() == output);
	}

	SECTION("Indented programs") {
		auto& [code, output] = GENERATE( table<std::string, std::string> ({
				{"\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n.", "0"},
				{"++++++\n[\n\t>++++++++<-\n]\n>.", "0"},
				{"++++++\n[\n\t>++++++++<-\n]\n++++++++++\n[a\n\t>.+<-\n]\n", "0123456789"}
			}));

		Interpreter i;
		i.load_from_string(code);
		CHECK(i.run() == output);
	}

	SECTION("Commented programs") {
		auto& [code, output] = GENERATE( table<std::string, std::string> ({
				{"This part sums up to 48:\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\n\t++++++\nAnd this one prints it:\n\t.", "0"},
				{"Loops \"add 8\" 6 times to get 48:\n\t++++++\n\t[\n\t\t>++++++++<-\n\t]\n\t>.", "0"},
				{"++++++\n[\n\t>++++++++<-\n]\n++++++++++\n[a\n\t>.+<-\n]\nend this please", "0123456789"}
			}));

		Interpreter i;
		i.load_from_string(code);
		CHECK(i.run() == output);
	}
}
