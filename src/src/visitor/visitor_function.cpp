#include "visitor/visitor.hpp"
#include "AST/function.hpp"
#include <iostream>

void ASTVisitor::visit(FunctionNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->parameters != nullptr)
            for(uint i=0; i< m->parameters->size(); i++){
                (*(m->parameters))[i]->accept(*this);
            }
        
        if (m->body != nullptr)
            m->body->accept(*this);
    this->space_counter_decrease();    
};