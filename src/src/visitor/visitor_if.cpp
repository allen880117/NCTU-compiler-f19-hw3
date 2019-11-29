#include "visitor/visitor.hpp"
#include "AST/if.hpp"
#include <iostream>

void ASTVisitor::visit(IfNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->condition != nullptr)
            m->condition->accept(*this);

        if (m->body != nullptr)
            for(uint i=0; i< m->body->size(); i++)
                (*(m->body))[i]->accept(*this);
    this->space_counter_decrease();

    if (m->body_of_else != nullptr){
        this->print_space();
        std::cout<<"else"<<std::endl;

        this->space_counter_increase();
            for(uint i=0; i< m->body_of_else->size(); i++)
                (*(m->body_of_else))[i]->accept(*this);
        this->space_counter_decrease();
    }
};