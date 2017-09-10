
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
            : type_(type) {
			if (leaf.compare("") != 0) leafs_.push_back(leaf);
            if (first) childs_.push_back(first);
            if (second) childs_.push_back(second);
            if (third) childs_.push_back(third);
        }

		Expression::Expression(
			const Type                          type,
			const boost::shared_ptr<Expression> child,
			const std::string                   first,
			const std::string                   second,
			const std::string                   third,
			const std::string                   fourth,
			const std::string                   fifth)
			: type_(type) {
			if (child) childs_.push_back(child);
			if (first.compare("")  != 0) leafs_.push_back(first);
			if (second.compare("") != 0) leafs_.push_back(second);
			if (third.compare("")  != 0) leafs_.push_back(third);
			if (fourth.compare("") != 0) leafs_.push_back(fourth);
			if (fifth.compare("")  != 0) leafs_.push_back(fifth);
		}

        std::string Expression::toString(const size_t level) {
			std::string indent = "";
			for (size_t k = 0; k < level; ++k) indent = indent + "  ";
			if (type_ == Expression::NUMBER)     return std::string(indent + "NUM(" + ((leafs_.size()>0)?(leafs_[0]):("")) + ")\n");
			if (type_ == Expression::IDENTIFIER) return std::string(indent + "TXT(" + ((leafs_.size()>0)?(leafs_[0]):("")) + ")\n");
            std::string res;
            switch (type_) {
            case Expression::ASSIGNMENT  : res = "ASSIGNMENT";  break;
            case Expression::UNARYPLUS	 : res = "UNARYPLUS";   break;
            case Expression::UNARYMINUS	 : res = "UNARYMINUS";  break;
            case Expression::PLUS		 : res = "PLUS";        break;
            case Expression::MINUS		 : res = "MINUS";       break;
            case Expression::MULT		 : res = "MULT";        break;
            case Expression::DIVISION	 : res = "DIVISION";    break;
            case Expression::LOGICAL	 : res = "LOGICAL";     break;
            case Expression::NEXT        : res = "NEXT";        break;
            case Expression::IFTHENELSE	 : res = "IFTHENELSE";  break;
            case Expression::MIN		 : res = "MIN";         break;
            case Expression::MAX		 : res = "MAX";         break;
            case Expression::PAY		 : res = "PAY";         break;
			case Expression::PAY_WITHDATE: res = "PAY_WITHDATE"; break;
			case Expression::CACHE		 : res = "CACHE";       break;
            case Expression::PAYOFFAT	 : res = "PAYOFFAT";    break;
			case Expression::PAYOFFAT_WITHDATE: res = "PAYOFFAT_WITHDATE"; break;
			case Expression::UNKNOWNTYPE : res = "UNKNOWNTYPE"; break;
            default:
				res = "Error! Unhandled Type";
                break;
            }
            res = indent + res + "[ \n";
			indent = indent + "  ";
			for (size_t k = 0; k < leafs_.size(); ++k) {
				if (k==0) res = res + indent + "LEAF[ ";
				res = res + leafs_[k];
				if (k < (leafs_.size()-1)) res = res + ", ";
				else res = res + " ]\n";
			}
            for (size_t k = 0; k < childs_.size(); ++k) res = res + childs_[k]->toString(level+1);
            res = res + indent + "]\n";
            return res;
        }

    }
}