#include "visitor/visitor.hpp"
#include "AST/variable_reference.hpp"
#include <iostream>

void ASTVisitor::visit(VariableReferenceNode *m) {
    this->print_space();
        m->print();
    
    if (m->expression_node_list != nullptr)
        for(uint i=0; i< m->expression_node_list->size(); i++){
            this->print_space();    
            std::cout<<"["<<std::endl;
            
            this->space_counter_increase();
                (*(m->expression_node_list))[i]->accept(*this);
            this->space_counter_decrease();
            
            this->print_space();    
            std::cout<<"]"<<std::endl;
        }
};