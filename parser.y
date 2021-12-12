%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <memory>
    #include <Expression.h>
    /* Forward declaration of classes in order to disable cyclic dependencies */
    class Scanner;
    class Driver;
}


%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    /* Redefine parser to use our function from scanner */
    static yy::parser::symbol_type yylex(Scanner &scanner) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}
// token name in variable
%token
    END 0 "end of file"
    ASSIGN ":="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
    SEMICOLON ";"
    DOT "."
    BEGINTOKEN "begin"
    ENDTOKEN "end"
    PROGRAMKEYWORD "program"
    VARKEYWORD "var"
    DECLARATION ":"
    IFKEYWORD "if"
    THENKEYWORD "then"
    ELSEKEYWORD "else"
    EQUAL "=="
    NOTEQUAL "!="
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <std::unique_ptr<Expression>> exp
%nterm <std::unique_ptr<Expression>> exp_priority1
%nterm <std::unique_ptr<Expression>> exp_priority2
%nterm <std::unique_ptr<Expression>> exp_priority3
%nterm <std::unique_ptr<Expression>> exp_priority4
%nterm <std::vector<std::unique_ptr<Expression>>> exp_block
%nterm <std::unique_ptr<SequenceExpression>> code
%nterm <std::unique_ptr<Expression>> assignment

// Prints output in parsing option for debugging location terminal
%printer { yyo << 0; } <*>;

%%
%left "+" "-";
%left "*" "/";

%start program;
program: name init code_block {
    std::cout << "\nthat's all\n";

};
name: "program" "identifier" ";" {
    std::cout << "Program name is " << $2 << "\n";
}

init:
    %empty {}
    |"var" init_block;

init_block:
    %empty {}
    | init_exp init_block {};

init_exp:
    "identifier" ":" "identifier" ";" {
        if(driver.declared_types.find($3) == driver.declared_types.end()) {
            std::cerr << "Not correct type!\n";
        } else {
            driver.global.declare($1, driver.declared_types[$3], std::make_shared<VariableT>());
        }
    }
    | error ";" {
    	// Hint for compilation error, resuming producing messages
    	std::cerr << "You should provide declaration in the form: variable : type ; " << std::endl;
    };

code_block: exp "." {
    $1 -> calculate(driver.global);
};

code:
    %empty {$$=std::make_unique<SequenceExpression>();}
    | code exp ";"{
        $1->push_back(std::move($2));
        $$ = std::move($1);
    };


exp:
    exp_priority4 {$$ = std::move($1);}
    | assignment {$$ = std::move($1);};

assignment:
    "identifier" ":=" exp_priority4 {
        auto var = std::unique_ptr<Expression>(new AtomExpression($1));
        $$ = std::unique_ptr<Expression>(new BinaryOperation(":=", std::move(var), std::move($3)));
        if (driver.location_debug) {
            std::cerr << driver.location << std::endl;
        }
    }







exp_priority1:
    "(" exp ")" {$$ = std::move($2);}
    | "identifier" {$$ = std::unique_ptr<Expression>(new AtomExpression($1));}
    | "identifier" "(" exp_block ")" {

            $$ = std::unique_ptr<Expression>(new FunctionExpression($1, std::move($3)));
        }
    | "number" {
            $$ = std::unique_ptr<Expression>(
                        new ValueExpression(getId<int>, std::make_shared<VariableT> ($1))
                    );
        }
    | "begin" code "end" {
            $$ = std::unique_ptr<Expression>($2.release());
        }
    | "if" exp "then" exp "else" exp {

        $$ = std::unique_ptr<Expression> ( new ConditionExpression (
                std::move($2),
                std::move($4),
                std::move($6)
            )
        );
    };


exp_priority2:
    exp_priority1 {$$ = std::move($1);}
    | exp_priority2 "*" exp_priority1 {
            $$ = std::unique_ptr<Expression>(new BinaryOperation{"+", std::move($1), std::move($3)});
        }
    | exp_priority2 "/" exp_priority1 {
        $$ = std::unique_ptr<Expression>(new BinaryOperation{"+", std::move($1), std::move($3)});
    };

exp_priority3:
    exp_priority2 {$$ = std::move($1);}
    | exp_priority3 "+" exp_priority2 {
        $$ = std::unique_ptr<Expression>(new BinaryOperation{"+", std::move($1), std::move($3)});
    }
    | exp_priority3 "-" exp_priority2 {
        $$ = std::unique_ptr<Expression>(new BinaryOperation{"+", std::move($1), std::move($3)});
    };

exp_priority4:
    exp_priority3 {$$ = std::move($1);}
    | exp_priority4 "==" exp_priority3 {
        $$ = std::unique_ptr<Expression>(new BinaryOperation{"==", std::move($1), std::move($3)});
    }
    | exp_priority4 "!=" exp_priority3 {
        $$ = std::unique_ptr<Expression>(new BinaryOperation{"!=", std::move($1), std::move($3)});
    };

exp_block:
    %empty {$$ = std::vector<std::unique_ptr<Expression>>();}
    | exp {
        $$ = std::vector<std::unique_ptr<Expression>>();
        $$.push_back(std::move($1));
    }
    | exp_block "," exp{
        $$ = std::move($1);
        $$.push_back(std::move($3));
    };
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
