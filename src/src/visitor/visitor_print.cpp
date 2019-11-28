#include "visitor/visitor.hpp"
#include "AST/print.hpp"
#include <iostream>

void ASTVisitor::visit(PrintNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->expression_node != nullptr)
            m->expression_node->accept(*this);
    this->space_counter_decrease();  
};