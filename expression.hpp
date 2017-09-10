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
				PAY_WITHDATE,
				CACHE,
				PAYOFFAT,
				PAYOFFAT_WITHDATE,
				UNKNOWNTYPE
			};
			Expression(const Type                   type,
				const std::string                   leaf,
				const boost::shared_ptr<Expression> first =  boost::shared_ptr<Expression>(),
				const boost::shared_ptr<Expression> second = boost::shared_ptr<Expression>(),
				const boost::shared_ptr<Expression> third =  boost::shared_ptr<Expression>());

			Expression(const Type                   type,
				const boost::shared_ptr<Expression> child,
				const std::string                   first  = std::string(),
				const std::string                   second = std::string(),
				const std::string                   third  = std::string(),
				const std::string                   fourth = std::string(),
				const std::string                   fifth  = std::string()
			);

			std::string toString(const size_t level = 0);

			// inspectors
			inline Type type()                                                  { return type_;   }
			std::vector< std::string > leafs()                                  { return leafs_;  }
			inline const std::vector< boost::shared_ptr<Expression> >& childs() { return childs_; };
		private:
			Type type_;
			std::vector< std::string > leafs_;
			std::vector< boost::shared_ptr<Expression> > childs_;

		};
	}
}

#endif // !EXPRESSION_HPP
