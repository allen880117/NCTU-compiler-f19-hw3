#include "visitor/visitor.hpp"
#include "AST/program.hpp"
#include <iostream>

void ASTVisitor::visit(ProgramNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->declaration_node_list != nullptr)
            for(uint i=0; i< m->declaration_node_list->size(); i++){
                (*(m->declaration_node_list))[i]->accept(*this);
            }

        if (m->function_node_list != nullptr)
            for(uint i=0; i< m->function_node_list->size(); i++){
                (*(m->function_node_list))[i]->accept(*this);
            }

        if (m->compound_statement_node != nullptr)
            m->compound_statement_node->accept(*this);
    this->space_counter_decrease();
}