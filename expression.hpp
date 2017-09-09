/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
Copyright (C) 2017, Sebastian Schlenkrich

*/

/*! \file expression.hpp
\brief an abstract expression object for payoff representation

*/



#ifndef quantlib_scripting_expression_hpp
#define quantlib_scripting_expression_hpp

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace QuantLib {

	namespace Scripting {

		class Expression {
		public:
			enum Type {
				NEXT,
				ASSIGNMENT,
				UNARYPLUS,
				UNARYMINUS,
				PLUS,
				MINUS,
				MULT,
				DIVISION,
				LOGICAL,
				IDENTIFIER,
				NUMBER,
				IFTHENELSE,
				MIN,
				MAX,
				PAY,
				CACHE,
				PAYOFFAT,
				UNKNOWNTYPE
			};
			Expression(const Type                   type,
				const std::string                   leaf,
				const boost::shared_ptr<Expression> first =  boost::shared_ptr<Expression>(),
				const boost::shared_ptr<Expression> second = boost::shared_ptr<Expression>(),
				const boost::shared_ptr<Expression> third =  boost::shared_ptr<Expression>());

			std::string toString(const size_t level = 0);

			// inspectors
			inline Type type()         { return type_;  }
			inline std::string leaf()  { return leaf_;  }
			inline const std::vector< boost::shared_ptr<Expression> >& childs() { return childs_; };
		private:
			Type type_;
			std::string leaf_;
			std::vector< boost::shared_ptr<Expression> > childs_;

		};
	}
}

#endif // !EXPRESSION_HPP
