#include "AST/ast.hpp"
#include "AST/program.hpp"
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

        m->compound_statement_node->accept(*this);
    this->space_counter_decrease();
}
void ASTVisitor::visit(DeclarationNode *m) {m->print();};
void ASTVisitor::visit(VariableNode *m) {m->print();};
void ASTVisitor::visit(ConstantValueNode *m) {m->print();};
void ASTVisitor::visit(FunctionNode *m) {m->print();};
void ASTVisitor::visit(CompoundStatementNode *m) {
    this->print_space();
        m->print();
    
    this->space_counter_increase();
    this->space_counter_decrease();    
};
void ASTVisitor::visit(AssignmentNode *m) {m->print();};
void ASTVisitor::visit(PrintNode *m) {m->print();};
void ASTVisitor::visit(ReadNode *m) {m->print();};
void ASTVisitor::visit(VariableReferenceNode *m) {m->print();};
void ASTVisitor::visit(BinaryOperatorNode *m) {m->print();};
void ASTVisitor::visit(UnaryOperatorNode *m) {m->print();};
void ASTVisitor::visit(IfNode *m) {m->print();};
void ASTVisitor::visit(WhileNode *m) {m->print();};
void ASTVisitor::visit(ForNode *m) {m->print();};
void ASTVisitor::visit(ReturnNode *m) {m->print();};
void ASTVisitor::visit(FunctionCallNode *m) {m->print();};

void ASTVisitorBase::space_counter_increase() {this->space_counter++;}
void ASTVisitorBase::space_counter_decrease() {this->space_counter--;}
void ASTVisitorBase::print_space() {for (size_t i = 0; i < space_counter; i++) { std::cout << "  "; }}
