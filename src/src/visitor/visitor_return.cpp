#include "visitor/visitor.hpp"
#include "AST/return.hpp"
#include <iostream>

void ASTVisitor::visit(ReturnNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->return_value != nullptr)
            m->return_value->accept(*this);
    this->space_counter_decrease();
};