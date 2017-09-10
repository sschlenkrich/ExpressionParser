%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "FlexBisonDriver.hpp"
# include "Parser.hpp"
#define YY_DECL QuantLib::Scripting::Parser::symbol_type yylex (QuantLib::Scripting::FlexBisonDriver& driver, yyscan_t yyscanner)


// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
// # undef yywrap
// # define yywrap() 1

// The location of the current token.
// static yy::location loc;
%}

%option outfile="Lexer.cpp"
%option noyywrap nounput batch debug noinput reentrant
id      [a-zA-Z][a-zA-Z_0-9]*
int     [0-9]+
double  [0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?
blank   [ \t]

date    [0-9]{2}(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)[0-9]{4}

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  driver.loc().columns (yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  driver.loc().step();
%}

{blank}+         driver.loc().step ();
[\n]+            driver.loc().lines (yyleng); driver.loc().step ();

{date}           return QuantLib::Scripting::Parser::make_DATE(yytext, driver.loc());

"=="             return QuantLib::Scripting::Parser::make_EQUAL(driver.loc());
"!="             return QuantLib::Scripting::Parser::make_NEQUUAL(driver.loc());
"<="             return QuantLib::Scripting::Parser::make_LESSEQ(driver.loc());
">="             return QuantLib::Scripting::Parser::make_GREATEREQ(driver.loc());
"<"              return QuantLib::Scripting::Parser::make_LESS(driver.loc());
">"              return QuantLib::Scripting::Parser::make_GREATER(driver.loc());

"&&"             return QuantLib::Scripting::Parser::make_AND(driver.loc());
"||"             return QuantLib::Scripting::Parser::make_OR(driver.loc());

"-"              return QuantLib::Scripting::Parser::make_MINUS(driver.loc());
"+"              return QuantLib::Scripting::Parser::make_PLUS(driver.loc());
"*"              return QuantLib::Scripting::Parser::make_STAR(driver.loc());
"/"              return QuantLib::Scripting::Parser::make_SLASH(driver.loc());
"("              return QuantLib::Scripting::Parser::make_LPAREN(driver.loc());
")"              return QuantLib::Scripting::Parser::make_RPAREN(driver.loc());
","              return QuantLib::Scripting::Parser::make_COMMA(driver.loc());
"="              return QuantLib::Scripting::Parser::make_ASSIGN(driver.loc());

"IfThenElse"	 return QuantLib::Scripting::Parser::make_IFTHENELSE(yytext,driver.loc());
"Min"            return QuantLib::Scripting::Parser::make_MIN(yytext,driver.loc());       
"Max"            return QuantLib::Scripting::Parser::make_MAX(yytext,driver.loc());       
"Pay"            return QuantLib::Scripting::Parser::make_PAY(yytext,driver.loc());       
"Cache"          return QuantLib::Scripting::Parser::make_CACHE(yytext,driver.loc());     

{double}         return QuantLib::Scripting::Parser::make_NUMBER(yytext, driver.loc());
{id}             return QuantLib::Scripting::Parser::make_IDENTIFIER(yytext, driver.loc());

.                driver.error (driver.loc(), "invalid character");

<<EOF>>  return QuantLib::Scripting::Parser::make_END(driver.loc());

%%

// scan_begin() and scan_end() need to be defined here because they
// access the global variable yyin
void QuantLib::Scripting::FlexBisonDriver::scan_begin () {  
    struct yyguts_t * yyg;
    yylex_init(&yyscanner_);
    yyg = (struct yyguts_t*)yyscanner_;
    yy_flex_debug = trace_scanning_;
    yy_scan_string(text_.c_str(),yyscanner_);
}
void QuantLib::Scripting::FlexBisonDriver::scan_end () {
    yylex_destroy(yyscanner_);
}

