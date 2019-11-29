#include "visitor/visitor.hpp"
#include "AST/compound_statement.hpp"
#include <iostream>

void ASTVisitor::visit(CompoundStatementNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->declaration_node_list != nullptr)
            for(uint i=0; i< m->declaration_node_list->size(); i++){
                (*(m->declaration_node_list))[i]->accept(*this);
            }
        if (m->statement_node_list != nullptr)
            for(uint i=0; i< m->statement_node_list->size(); i++){
                (*(m->statement_node_list))[i]->accept(*this);
            }
    this->space_counter_decrease();    
};