/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
Copyright (C) 2017, Sebastian Schlenkrich

*/

/*! \file flexbisondriver.hpp
\brief a wrapper class for an reentrant Flex/Bison parser

*/



#ifndef quantlib_scripting_flexbisondriver_hpp
#define quantlib_scripting_flexbisondriver_hpp

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include "Parser.hpp"


namespace QuantLib {

	namespace Scripting {

		class Expression;

		// Conducting the whole scanning and parsing of Calc++.
		class FlexBisonDriver {
		private:
			// The text to be parsed
			std::string text_;
			// The result of the parsing algorithm is an abstract syntax tree (AST)
			boost::shared_ptr<Expression> expressionTree_;
			// encapsulate the state for a reentrant scanner
			// this is initialised in scan_begin()
			void *yyscanner_;
			// the current location of the scanner
			location loc_;
			// the parser return value
			int returnValue_;
			// any error messages
			std::string errorMsg_;
			// Whether parser traces should be generated.
			bool trace_scanning_;
			bool trace_parsing_;

		public:
			FlexBisonDriver(const std::string text,
				const bool trace_scanning = true,
				const bool trace_parsing = true);


			// : trace_scanning_(trace_scanning), trace_parsing_(trace_parsing) { }

			// Handling the scanner.
			void scan_begin();
			void scan_end();
			// set the result value during parsing
			void setExpressionTree(const boost::shared_ptr<Expression> expressionTree) { expressionTree_ = expressionTree; }
			// Error handling.
			void error(const location& l, const std::string& m);
			void error(const std::string& m);
			// inspector
			std::string text() { return text_; }
			std::string errorMsg() { return errorMsg_; }
			boost::shared_ptr<Expression> expressionTree() { return expressionTree_; }
			int returnValue() { return returnValue_; }
			// return a reference to allow acccess to methods
			location& loc() { return loc_; }
		};

	}

}

#endif // !FLEX_BISON_DRIVER_HPP
