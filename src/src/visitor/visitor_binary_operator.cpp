#include "visitor/visitor.hpp"
#include "AST/binary_operator.hpp"
#include <iostream>

void ASTVisitor::visit(BinaryOperatorNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->left_operand != nullptr)
            m->left_operand->accept(*this);

        if (m->right_operand != nullptr)
            m->right_operand->accept(*this);
    this->space_counter_decrease();
};