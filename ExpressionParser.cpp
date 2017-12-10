// ExpressionParser.cpp : Defines the entry point for the example console application.
//

#include <iostream>

#include <boost/shared_ptr.hpp>

#include "expression.hpp"
#include "Parser.hpp"
#include "flexbisondriver.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
	bool trace_parsing = false;
	bool trace_scanning = false;
	for (++argv; argv[0]; ++argv) {
		if (*argv == std::string("-p")) trace_parsing = true;
		if (*argv == std::string("-s")) trace_scanning = true;
	}
	while (true) {
		std::cout << "ExpressionParser>";
		std::string text;
		std::getline(std::cin, text);
		if (text.compare("exit") == 0) return 0;
		QuantLib::Scripting::FlexBisonDriver driver(text, trace_scanning, trace_parsing);
		std::cout << "ExpressionParser::returnValue = " << driver.returnValue() << std::endl;
		std::cout << "ExpressionParser::errorMsg = " << driver.errorMsg() << std::endl;
		if (driver.expressionTree()) std::cout << driver.expressionTree()->toString();
	}
	return 0;
}
