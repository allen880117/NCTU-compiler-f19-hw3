#include "visitor/visitor.hpp"
#include "AST/read.hpp"
#include <iostream>

void ASTVisitor::visit(ReadNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->variable_reference_node != nullptr)
            m->variable_reference_node->accept(*this);    
    this->space_counter_decrease();
};