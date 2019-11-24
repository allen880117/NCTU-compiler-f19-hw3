%{
#include "include/AST/ast.hpp"
#include "include/visitor/visitor.hpp"
#include "include/core/error.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

/* Declared by scanner.l */
extern int32_t LineNum;
extern char Buffer[512];

/* Declared by lex */
extern FILE *yyin;
extern char *yytext;

extern int yylex(void);
static void yyerror(const char *msg);

/* Datatype for Return Non-terminals */
struct id_info{
    string name;
    uint32_t line_number;
    uint32_t col_number;
};

static Node AST;

%}
    /* Useful Header */
%code requires { #include "include/AST/ast.hpp" }

    /* Union Define */
%union {
    int    val;
    double dval;
    char*  text;

    int    op_type;

    NodeList* node_list_ptr;
    Node      node;

    vector<struct id_info>* id_list_ptr;
    VariableInfo*           variable_info_ptr;
}

%locations

    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token FALSE TRUE
%token PRINT READ

    /* Identifier */
%token <text> ID

    /* Literal */
%token <val> INT_LITERAL
%token <dval> REAL_LITERAL
%token <text> STRING_LITERAL

    /* Type of Nonterminals */
%type <text> ProgramName
%type <text> FunctionName

%type <node> Declaration
%type <node_list_ptr> Declarations
%type <node_list_ptr> DeclarationList

%type <node> FunctionDeclaration
%type <node_list_ptr> Functions
%type <node_list_ptr> FunctionList

%type <node> FormalArg
%type <node_list_ptr> FormalArgs
%type <node_list_ptr> FormalArgList

%type <node> CompoundStatement

%type <id_list_ptr> IdList
%type <variable_info_ptr> ReturnType
%type <variable_info_ptr> Type
%type <variable_info_ptr> ScalarType
%type <variable_info_ptr> ArrType
%type <variable_info_ptr> ArrDecl
%type <variable_info_ptr> TypeOrConstant
%type <variable_info_ptr> LiteralConstant

%%
    /*
       Program Units
                     */

Program:
    ProgramName SEMICOLON DeclarationList FunctionList CompoundStatement END ProgramName {
        // Program Node (Also root Node)
        string return_type = "void";
        AST = new ProgramNode(
            @1.first_line,
            @1.first_column,
            $1,
            return_type,
            $3,
            $4,
            $5,
            @7.first_line,
            @7.first_column,
            $7
        );
    }
;

ProgramName:
    ID{
        $$ = $1;
    }
;

    /*
    ProgramBody:
        DeclarationList FunctionList CompoundStatement
    ;
    */

DeclarationList:
    Epsilon {
        $$ = nullptr;
    }
    |
    Declarations {
        $$ = $1;
    }
;

Declarations:
    Declaration{
        $$ = new NodeList();
        $$->push_back($1);
    }
    |
    Declarations Declaration{
        $1->push_back($2);
        $$ = $1;
    }
;

FunctionList:
    Epsilon{
        $$ = nullptr;
    }
    |
    Functions{
        $$ = $1;
    }
;

Functions:
    FunctionDeclaration{
        $$ = new NodeList();
        $$->push_back($1);
    }
    |
    Functions FunctionDeclaration{
        $1->push_back($2);
        $$ = $1;
    }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON
    CompoundStatement
    END FunctionName {
        // Function Node
        $$ = new FunctionNode(
            @1.first_line,
            @1.first_column,
            $1,
            $3,
            $5,
            $7,
            @9.first_line,
            @9.first_column,
            $9
        );
    }
;

FunctionName:
    ID{
        $$ = $1;
    }
;

FormalArgList:
    Epsilon {
        $$ = nullptr;
    }
    |
    FormalArgs {
        $$ = $1;
    }
;

FormalArgs:
    FormalArg{
        $$ = new NodeList();
        $$->push_back($1);
    }
    |
    FormalArgs SEMICOLON FormalArg {
        $1->push_back($3);
        $$ = $1;
    }
;

FormalArg:
    IdList COLON Type{
        // Declaration Node (but location is not KWvar)
        NodeList* var_list = new NodeList();
        for(uint i=0; i<$1->size(); i++){
            VariableNode* variable_node = new VariableNode(
                (*$1)[i].line_number,
                (*$1)[i].col_number,
                (*$1)[i].name,
                $3,
                nullptr
            );
            var_list->push_back(variable_node);
        }

        $$ = new DeclarationNode(
            @1.first_line,
            @1.first_column,
            var_list
        );
    }
;

IdList:
    ID{
        $$ = new vector<id_info>();
        $$->push_back(id_info{$1, @1.first_line, @1.first_column});
    }
    |
    IdList COMMA ID{
        $1->push_back(id_info{$3, @3.first_line, @3.first_column});
        $$ = $1;
    }
;

ReturnType:
    COLON ScalarType{
        $$ = $2;
    }
    |
    Epsilon{
        $$ = new VariableInfo;
        $$->type_set = UNKNOWN_SET;
        $$->type = UNKNOWN_TYPE;
    }
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON TypeOrConstant SEMICOLON{
        // Declaration Node
        NodeList* var_list = new NodeList();
        for(uint i=0; i<$2->size(); i++){
            if( $4->type_set == SET_CONSTANT_LITERAL ){ 
                // Literal Constant
                ConstantValueNode* constant_value_node = new ConstantValueNode(
                    @4.first_line,
                    @4.first_column,
                    $4
                );

                VariableNode* variable_node = new VariableNode(
                    (*$2)[i].line_number,
                    (*$2)[i].col_number,
                    (*$2)[i].name,
                    $4,
                    constant_value_node
                );

                var_list->push_back(variable_node);
                
            } else { 
                // Type
                VariableNode* variable_node = new VariableNode(
                    (*$2)[i].line_number,
                    (*$2)[i].col_number,
                    (*$2)[i].name,
                    $4,
                    nullptr
                );

                var_list->push_back(variable_node);
            }
        }

        $$ = new DeclarationNode(
            @1.first_line,
            @1.first_column,
            var_list
        );
    }
;

TypeOrConstant:
    Type{
        $$ = $1;
    }
    |
    LiteralConstant{
        $$ = $1;
    }
;

Type:
    ScalarType{
        $$ = $1;
    }
    |
    ArrType{
        $$ = $1;
    }
;

ScalarType:
    INTEGER{
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_INTEGER;
    }
    |
    REAL{
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_REAL;
    }
    |
    STRING{
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_STRING;
    }
    |
    BOOLEAN{
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_BOOLEAN;
    }
;

ArrType:
    ArrDecl ScalarType{
        $$ = new VariableInfo();
        $$->type_set = SET_ACCUMLATED;
        $$->type = $2->type;
        $$->array_range = $1->array_range;
    }
;

ArrDecl:
    ARRAY INT_LITERAL TO INT_LITERAL OF{
        $$ = new VariableInfo();
        $$->type_set = SET_ACCUMLATED;
        $$->type = UNKNOWN_TYPE;
        $$->array_range.push_back(IntPair{$2, $4});
    }
    |
    ArrDecl ARRAY INT_LITERAL TO INT_LITERAL OF{
        $1->array_range.push_back(IntPair{$3, $5});
        $$ = $1;
    }
;

LiteralConstant:
    INT_LITERAL{
        $$ = new VariableInfo();
        $$->type_set=SET_CONSTANT_LITERAL;
        $$->type=TYPE_INTEGER;
        $$->int_literal=$1;
    }
    |
    REAL_LITERAL{
        $$ = new VariableInfo();
        $$->type_set=SET_CONSTANT_LITERAL;
        $$->type=TYPE_REAL;
        $$->real_literal=$1;
    }
    |
    STRING_LITERAL{
        $$ = new VariableInfo();
        $$->type_set=SET_CONSTANT_LITERAL;
        $$->type=TYPE_STRING;
        $$->string_literal=string($1);
    }
    |
    TRUE{
        $$ = new VariableInfo();
        $$->type_set=SET_CONSTANT_LITERAL;
        $$->type=TYPE_BOOLEAN;
        $$->boolean_literal=Boolean_TRUE;
    }
    |
    FALSE{
        $$ = new VariableInfo();
        $$->type_set=SET_CONSTANT_LITERAL;
        $$->type=TYPE_BOOLEAN;
        $$->boolean_literal=Boolean_FALSE;
    }
;

    /*
       Statements
                  */

Statement:
    CompoundStatement
    |
    Simple
    |
    Condition
    |
    While
    |
    For
    |
    Return
    |
    FunctionInvokation
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END {
        CompoundStatementNode* compound_statement_node = new CompoundStatementNode(
            @1.first_line, 
            @1.first_column, 
            nullptr,
            nullptr
        );
        $$ = compound_statement_node;
    }
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON
    |
    PRINT Expression SEMICOLON
    |
    READ VariableReference SEMICOLON
;

VariableReference:
    ID
    |
    ID ArrForm
;

ArrForm:
    L_BRACKET Expression R_BRACKET
    |
    ArrForm L_BRACKET Expression R_BRACKET
;

Condition:
    IF Expression THEN
    StatementList
    ElseOrNot
    END IF
;

ElseOrNot:
    ELSE
    StatementList
    |
    Epsilon
;

While:
    WHILE Expression DO
    StatementList
    END DO
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    StatementList
    END DO
;

Return:
    RETURN Expression SEMICOLON
;

FunctionInvokation:
    FunctionCall SEMICOLON
;

FunctionCall:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS
;

ExpressionList:
    Epsilon
    |
    Expressions
;

Expressions:
    Expression
    |
    Expressions COMMA Expression
;

StatementList:
    Epsilon
    |
    Statements
;

Statements:
    Statement
    |
    Statements Statement
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS
    |
    MINUS Expression %prec UNARY_MINUS
    |
    Expression MULTIPLY Expression
    |
    Expression DIVIDE Expression
    |
    Expression MOD Expression
    |
    Expression PLUS Expression
    |
    Expression MINUS Expression
    |
    Expression LESS Expression
    |
    Expression LESS_OR_EQUAL Expression
    |
    Expression GREATER Expression
    |
    Expression GREATER_OR_EQUAL Expression
    |
    Expression EQUAL Expression
    |
    Expression NOT_EQUAL Expression
    |
    NOT Expression
    |
    Expression AND Expression
    |
    Expression OR Expression
    |
    LiteralConstant
    |
    VariableReference
    |
    FunctionCall
;

    /*
       misc
            */
Epsilon:
;
%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            LineNum, Buffer, yytext);
    exit(-1);
}

void dumpAST(ASTNodeBase* node){
    ASTVisitor visitor;
    node->accept(visitor);
}

int main(int argc, const char *argv[]) {
    CHECK((argc >= 2) && (argc<=3), "Usage: ./parser <filename> [--dump-ast]\n");
    
    int isDumpNeed;
    if(argc == 3)
        isDumpNeed = strcmp(argv[2], "--dump-ast");
    if(isDumpNeed != 0){
        fprintf(stderr, "Usage: ./parser <filename> [--dump-ast]\n");
        exit(-1);                                                          
    }

    FILE *fp = fopen(argv[1], "r");

    CHECK(fp != NULL, "fopen() fails.\n");
    yyin = fp;
    yyparse();

    if(argc == 3 && isDumpNeed == 0)
        dumpAST(AST);

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
