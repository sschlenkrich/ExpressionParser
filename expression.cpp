
/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
Copyright (C) 2017, Sebastian Schlenkrich

*/

/*! \file expression.cpp
\brief an abstract expression object for payoff representation

*/



#include "expression.hpp"


namespace QuantLib {

    namespace Scripting {

        Expression::Expression(
            const Type                          type,
            const std::string                   leaf,
            const boost::shared_ptr<Expression> first,
            const boost::shared_ptr<Expression> second,
            const boost::shared_ptr<Expression> third)
            : type_(type), leaf_(leaf) {
            if (first) childs_.push_back(first);
            if (second) childs_.push_back(second);
            if (third) childs_.push_back(third);
        }

        std::string Expression::toString(const size_t level) {
			std::string indent = "";
			for (size_t k = 0; k < level; ++k) indent = indent + "  ";
            if (type_ == Expression::NUMBER)     return std::string(indent + "NUM(" + leaf_ + ")\n");
            if (type_ == Expression::IDENTIFIER) return std::string(indent + "TXT(" + leaf_ + ")\n");
            std::string res;
            switch (type_) {
            case Expression::ASSIGNMENT  : res = "ASSIGNMENT "; break;
            case Expression::UNARYPLUS	 : res = "UNARYPLUS	 "; break;
            case Expression::UNARYMINUS	 : res = "UNARYMINUS" ; break;
            case Expression::PLUS		 : res = "PLUS		 "; break;
            case Expression::MINUS		 : res = "MINUS		 "; break;
            case Expression::MULT		 : res = "MULT		 "; break;
            case Expression::DIVISION	 : res = "DIVISION	 "; break;
            case Expression::LOGICAL	 : res = "LOGICAL	 "; break;
            case Expression::NEXT        : res = "NEXT       "; break;
            case Expression::IDENTIFIER	 : res = "IDENTIFIER "; break;
            case Expression::NUMBER		 : res = "NUMBER	 "; break;
            case Expression::IFTHENELSE	 : res = "IFTHENELSE" ; break;
            case Expression::MIN		 : res = "MIN		 "; break;
            case Expression::MAX		 : res = "MAX		 "; break;
            case Expression::PAY		 : res = "PAY		 "; break;
            case Expression::CACHE		 : res = "CACHE		 "; break;
            case Expression::PAYOFFAT	 : res = "PAYOFFAT	 "; break;
            case Expression::UNKNOWNTYPE : res = "UNKNOWNTYPE"; break;
            default:
				res = "Error! Unhandled Type";
                break;
            }
            res = indent + res + "[ \n";
			indent = indent + "  ";
			res = res + indent + "LEAF[" + leaf_ + "]\n";
            for (size_t k = 0; k < childs_.size(); ++k) res = res + childs_[k]->toString(level+1);
            res = res + indent + "] \n";
            return res;
        }

    }
}