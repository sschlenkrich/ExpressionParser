%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define api.namespace {QuantLib::Scripting}
%define parser_class_name {Parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert true

%output  "Parser.cpp"
%defines "Parser.hpp"

%code requires
{
#include <string>
#include <boost/shared_ptr.hpp>
namespace QuantLib{
    namespace Scripting {
        class Expression;
        class FlexBisonDriver;
	}
}

}
// The parsing context.
%parse-param { FlexBisonDriver& driver }
%parse-param { void* yyscanner         }
%lex-param   { FlexBisonDriver& driver }
%lex-param   { void* yyscanner         }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.text();
};
// %define parse.trace
// %define parse.error verbose
%debug
%error-verbose
%code
{
// further .cpp includes
#include "Expression.hpp"
#include "FlexBisonDriver.hpp"
// tell Bison that the scanner exists as expected...
QuantLib::Scripting::Parser::symbol_type yylex (QuantLib::Scripting::FlexBisonDriver& driver, void* yyscanner);

}
%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  ASSIGN      "="
  MINUS       "-"
  PLUS        "+"
  STAR        "*"
  SLASH       "/"
  LPAREN      "("
  RPAREN      ")"
  COMMA       ","
  EQUAL       "=="
  NEQUUAL     "!="
  LESSEQ      "<="
  GREATEREQ   ">="
  LESS        "<"
  GREATER     ">"
  LBRACK      "["
  RBRACK      "]"
;
%token <std::string> IDENTIFIER  "identifier"
%token <std::string> NUMBER      "number"
%token <std::string> IFTHENELSE  "IfThenElse"
%token <std::string> MIN         "Min"
%token <std::string> MAX         "Max"
%token <std::string> PAY         "Pay"
%token <std::string> CACHE       "Cache"

%type  <boost::shared_ptr<Expression>> exp
%type  <boost::shared_ptr<Expression>> assignment
%type  <boost::shared_ptr<Expression>> function
%type  <boost::shared_ptr<Expression>> funcname

%printer { yyoutput << $$; } <*>;
%%

%left "+" "-";
%left "*" "/";
%left UNARY;

%start unit;
unit: assignment  { driver.setExpressionTree($1); };

assignment:
  "identifier" "=" exp { $$ = boost::shared_ptr<Expression>(new Expression(Expression::ASSIGNMENT,$1,$3)); };

exp:
  "+" exp %prec UNARY
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::UNARYPLUS,"",$2)); }
| "-" exp %prec UNARY
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::UNARYMINUS,"",$2)); }
| exp "+" exp   { $$ = boost::shared_ptr<Expression>(new Expression(Expression::PLUS,"",$1,$3)); }
| exp "-" exp   { $$ = boost::shared_ptr<Expression>(new Expression(Expression::MINUS,"",$1,$3)); }
| exp "*" exp   { $$ = boost::shared_ptr<Expression>(new Expression(Expression::MULT,"",$1,$3)); }
| exp "/" exp   { $$ = boost::shared_ptr<Expression>(new Expression(Expression::DIVISION,"",$1,$3)); }
| exp "==" exp
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::LOGICAL,"==",$1,$3)); }
| exp "!=" exp
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::LOGICAL,"!=",$1,$3)); }
| exp "<=" exp
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::LOGICAL,"<=",$1,$3)); }
| exp ">=" exp
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::LOGICAL,">=",$1,$3)); }
| exp "<" exp
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::LOGICAL,"<",$1,$3)); }
| exp ">" exp
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::LOGICAL,">",$1,$3)); }
| "(" exp ")"   { $$ = $2; }
| IDENTIFIER    { $$ = boost::shared_ptr<Expression>(new Expression(Expression::IDENTIFIER,$1)); }
| NUMBER        { $$ = boost::shared_ptr<Expression>(new Expression(Expression::NUMBER,$1)); }
| IFTHENELSE "(" exp "," exp "," exp ")"
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::IFTHENELSE,"",$3,$5,$7));  }
| MIN "(" exp "," exp ")"
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::MIN,"",$3,$5));  }
| MAX "(" exp "," exp ")"
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::MAX,"",$3,$5));  }
| PAY "(" exp "," NUMBER ")"
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::PAY,$5,$3));  }
| CACHE "(" exp ")"
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::CACHE,"",$3));  }
| function      { $$ = $1; }
;


function:
  funcname "(" NUMBER ")"
                { $$ = boost::shared_ptr<Expression>(new Expression(Expression::PAYOFFAT,$3,$1)); } ;

funcname:
  IDENTIFIER { $$ = boost::shared_ptr<Expression>(new Expression(Expression::IDENTIFIER,$1)); } ;




%%

void QuantLib::Scripting::Parser::error (const location_type& l, const std::string& m) {
  driver.error (l, m);
}

// end of file