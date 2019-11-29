#include "visitor/visitor.hpp"
#include "AST/assignment.hpp"
#include <iostream>

void ASTVisitor::visit(AssignmentNode *m) {
   this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->variable_reference_node != nullptr)
            m->variable_reference_node->accept(*this);
        
        if (m->expression_node != nullptr)
            m->expression_node->accept(*this);
    this->space_counter_decrease();  
};