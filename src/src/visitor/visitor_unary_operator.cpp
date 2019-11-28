#include "visitor/visitor.hpp"
#include "AST/unary_operator.hpp"
#include <iostream>

void ASTVisitor::visit(UnaryOperatorNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->operand != nullptr)
            m->operand->accept(*this);
    this->space_counter_decrease();
};