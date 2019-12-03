#pragma once

#include <memory>
#include <vector>
#include <string>
#include "visitor/visitor.hpp"

#define SAFE_DELETE(NODE)       \
    if((NODE) != nullptr)       \
    {                           \
        delete (NODE);          \
        (NODE) = nullptr;       \
    }                           \

#define NODELIST_PTR_DELETE(NODELIST_PTR)                       \
    if((NODELIST_PTR)!=nullptr)                                 \
    {                                                           \
        for(uint i=0; i<(NODELIST_PTR)->size(); i++)            \
        {                                                       \
            delete (*(NODELIST_PTR))[i];                        \
            (*(NODELIST_PTR))[i]=nullptr;                       \
        }                                                       \
        delete (NODELIST_PTR);                                  \
        (NODELIST_PTR)=nullptr;                                 \
    }                                                           \

using namespace std;

typedef vector< class ASTNodeBase* > NodeList;
typedef class ASTNodeBase*           Node;

enum enumOperator{
    OP_ASSIGN = 500,
    OP_OR,
    OP_AND,
    OP_NOT,
    OP_LESS,
    OP_LESS_OR_EQUAL,
    OP_EQUAL,
    OP_GREATER,
    OP_GREATER_OR_EQUAL,
    OP_NOT_EQUAL,
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_MOD,
    UNKNOWN_OP
};

enum enumTypeSet{
    SET_SCALAR = 300,
    SET_ACCUMLATED,
    SET_CONSTANT_LITERAL,
    UNKNOWN_SET
};

enum enumType{
    TYPE_INTEGER = 400,
    TYPE_REAL,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_VOID,
    UNKNOWN_TYPE
};

typedef struct __IntPair{
    int start;
    int end;
} IntPair;

enum BooleanLiteral{
    Boolean_TRUE = 400,
    Boolean_FALSE,
    UNKNOWN
};

typedef struct __VariableInfo{
    enumTypeSet type_set;
    enumType type;
    vector<IntPair> array_range;
    int int_literal;
    double real_literal;
    string string_literal;
    BooleanLiteral boolean_literal;
} VariableInfo ;

struct NodeWithTypeList{
    Node node;
    VariableInfo* type;
    uint counter;
};

class ASTNodeBase
{
    public:
        virtual void accept(class ASTVisitorBase &v) = 0;
        virtual ~ASTNodeBase(){};
};