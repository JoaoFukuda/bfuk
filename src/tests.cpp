#include "interpreter.hpp"

#include <catch2/catch_all.hpp>

TEST_CASE("Basic programs")
{
   auto& [code, output] = GENERATE(table<std::string, std::string>(
       {{"++++++++++++++++++++++++++++++++++++++++++++++++.", "0"},
        {"++++++[>++++++++<-]>.", "0"},
        {"++++++[>++++++++<-]++++++++++[>.+<-]", "0123456789"}}));

   Interpreter i;
   i.load_from_string(code);
   CHECK(i.run() == output);
}

TEST_CASE("Indented programs")
{
   auto& [code, output] = GENERATE(table<std::string, std::string>(
       {{"++++++\n[\n\t>++++++++<-\n]\n>.", "0"},
        {" ++++++ [ >++++++++<- ] ++++++++++ [ a >.+<- ] ", "0123456789"}}));

   Interpreter i;
   i.load_from_string(code);
   CHECK(i.run() == output);
}

TEST_CASE("Commented programs")
{
   auto& [code, output] = GENERATE(table<std::string, std::string>(
       {{"This part sums up to 48: ++++++++++++++++++++++++"
         "++++++++++++++++++++++++\nAnd this one prints it: .",
         "0"},
        {"Loops \"add 8\" 6 times to get 48:\n\t++++++[>++++++++<-]>.", "0"},
        {"++++++[>++++++++<-]++++++++++[a>.+<-]\nend this please",
         "0123456789"}}));

   Interpreter i;
   i.load_from_string(code);
   CHECK(i.run() == output);
}
