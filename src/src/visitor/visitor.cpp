#include "visitor/visitor.hpp"
#include "AST/ast.hpp"
#include <iostream>

// TODO
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

void ASTVisitor::visit(VariableNode *m) {
    this->print_space();
        m->print();

    this->space_counter_increase();
        if (m->constant_value_node != nullptr)
            m->constant_value_node->accept(*this);
    this->space_counter_decrease(); 
};

void ASTVisitor::visit(ConstantValueNode *m) {
    this->print_space();
        m->print();
    
    // this->space_counter_increase();
    // this->space_counter_decrease(); 
};

void ASTVisitor::visit(FunctionNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->parameters != nullptr)
            for(uint i=0; i< m->parameters->size(); i++){
                (*(m->parameters))[i]->accept(*this);
            }
        
        if (m->body != nullptr)
            m->body->accept(*this);
    this->space_counter_decrease();    
};


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

void ASTVisitor::visit(PrintNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->expression_node != nullptr)
            m->expression_node->accept(*this);
    this->space_counter_decrease();  
};

void ASTVisitor::visit(ReadNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->variable_reference_node != nullptr)
            m->variable_reference_node->accept(*this);    
    this->space_counter_decrease();
};

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

void ASTVisitor::visit(UnaryOperatorNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->operand != nullptr)
            m->operand->accept(*this);
    this->space_counter_decrease();
};

void ASTVisitor::visit(IfNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->condition != nullptr)
            m->condition->accept(*this);

        if (m->body != nullptr)
            for(uint i=0; i< m->body->size(); i++)
                (*(m->body))[i]->accept(*this);
    this->space_counter_decrease();

        if (m->body_of_else != nullptr){
            this->print_space();
            std::cout<<"else"<<std::endl;

            this->space_counter_increase();
                for(uint i=0; i< m->body_of_else->size(); i++)
                    (*(m->body_of_else))[i]->accept(*this);
            this->space_counter_decrease();
        }
};

void ASTVisitor::visit(WhileNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->condition != nullptr)
            m->condition->accept(*this);

        if (m->body != nullptr)
            for(uint i=0; i< m->body->size(); i++)
                (*(m->body))[i]->accept(*this);
    this->space_counter_decrease();
};

void ASTVisitor::visit(ForNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->loop_variable_declaration != nullptr)
            m->loop_variable_declaration->accept(*this);
        
        if (m->initial_statement != nullptr)
            m->initial_statement->accept(*this);

        if (m->condition != nullptr)
            m->condition->accept(*this);

        if (m->body != nullptr)
            for(uint i=0; i< m->body->size(); i++)
                (*(m->body))[i]->accept(*this);
    this->space_counter_decrease();
};

void ASTVisitor::visit(ReturnNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->return_value != nullptr)
            m->return_value->accept(*this);
    this->space_counter_decrease();
};

void ASTVisitor::visit(FunctionCallNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
        if (m->arguments != nullptr)
            for(uint i=0; i< m->arguments->size(); i++)
                (*(m->arguments))[i]->accept(*this);
    this->space_counter_decrease();
};

void ASTVisitorBase::space_counter_increase() {this->space_counter++;}
void ASTVisitorBase::space_counter_decrease() {this->space_counter--;}
void ASTVisitorBase::print_space() {for (size_t i = 0; i < space_counter; i++) { std::cout << "  "; }}
