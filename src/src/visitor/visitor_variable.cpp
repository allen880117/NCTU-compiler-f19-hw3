#include "visitor/visitor.hpp"
#include "AST/variable.hpp"
#include <iostream>

void ASTVisitor::visit(VariableNode *m) {
    this->print_space();
        m->print();

    this->space_counter_increase();
        if (m->constant_value_node != nullptr)
            m->constant_value_node->accept(*this);
    this->space_counter_decrease(); 
};