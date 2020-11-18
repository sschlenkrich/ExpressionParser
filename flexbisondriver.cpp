/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
Copyright (C) 2017, Sebastian Schlenkrich

*/

/*! \file flexbisondriver.hpp
\brief a wrapper class for an reentrant Flex/Bison parser

*/


#include "Parser.hpp"

#include "flexbisondriver.hpp"

#include <sstream>

namespace QuantLib {

    namespace Scripting {

        FlexBisonDriver::FlexBisonDriver(const std::string text,
            const bool trace_scanning,
            const bool trace_parsing)
            : text_(text), trace_scanning_(trace_scanning), trace_parsing_(trace_parsing), expressionTree_() {
            scan_begin();
            Parser parser(*this, yyscanner_);
            parser.set_debug_level(trace_parsing_);
            returnValue_ = parser.parse();
            scan_end();
        }

        void FlexBisonDriver::error(const location& l, const std::string& m) {
            //std::cerr << l << ": " << m << std::endl;
            std::stringstream ss;
            ss << l << ": " << m;
            errorMsg_ = ss.str();
        }

        void FlexBisonDriver::error(const std::string& m) {
            // std::cerr << m << std::endl;
            std::stringstream ss;
            ss << m;
            errorMsg_ = ss.str();
        }

    }
}