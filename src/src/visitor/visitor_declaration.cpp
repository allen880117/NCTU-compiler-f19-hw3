#include "visitor/visitor.hpp"
#include "AST/declaration.hpp"
#include <iostream>

void ASTVisitor::visit(DeclarationNode *m) {
    this->print_space();
        m->print();
        
    this->space_counter_increase();
        if (m->variables_node_list != nullptr)
            for(uint i=0; i< m->variables_node_list->size(); i++){
                (*(m->variables_node_list))[i]->accept(*this);
            }
    this->space_counter_decrease();
};