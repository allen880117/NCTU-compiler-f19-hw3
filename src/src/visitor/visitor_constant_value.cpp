#include "visitor/visitor.hpp"
#include "AST/constant_value.hpp"
#include <iostream>

void ASTVisitor::visit(ConstantValueNode *m) {
    this->print_space();
        m->print();
    
    // this->space_counter_increase();
    // this->space_counter_decrease(); 
};