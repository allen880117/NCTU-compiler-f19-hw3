#include "visitor/visitor.hpp"
#include "AST/function_call.hpp"
#include <iostream>

void ASTVisitor::visit(FunctionCallNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->arguments != nullptr)
            for(uint i=0; i< m->arguments->size(); i++)
                (*(m->arguments))[i]->accept(*this);
    this->space_counter_decrease();
};