#include "visitor/visitor.hpp"
#include "AST/while.hpp"
#include <iostream>

void ASTVisitor::visit(WhileNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->condition != nullptr)
            m->condition->accept(*this);

        if (m->body != nullptr)
            for(uint i=0; i< m->body->size(); i++)
                (*(m->body))[i]->accept(*this);
    this->space_counter_decrease();
};