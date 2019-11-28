#include "visitor/visitor.hpp"
#include "AST/for.hpp"
#include <iostream>

void ASTVisitor::visit(ForNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->loop_variable_declaration != nullptr)
            m->loop_variable_declaration->accept(*this);
        
        if (m->initial_statement != nullptr)
            m->initial_statement->accept(*this);

        if (m->condition != nullptr)
            m->condition->accept(*this);

        if (m->body != nullptr)
            for(uint i=0; i< m->body->size(); i++)
                (*(m->body))[i]->accept(*this);
    this->space_counter_decrease();
};