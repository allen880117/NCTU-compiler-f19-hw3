#include "AST/ast.hpp"
#include "AST/program.hpp"
#include <iostream>

// TODO
void ASTVisitor::visit(ProgramNode *m) {m->print(*this);}
void ASTVisitor::visit(DeclarationNode *m) {m->print(*this);};
void ASTVisitor::visit(VariableNode *m) {m->print(*this);};
void ASTVisitor::visit(ConstantValueNode *m) {m->print(*this);};
void ASTVisitor::visit(FunctionNode *m) {m->print(*this);};
void ASTVisitor::visit(CompoundStatementNode *m) {m->print(*this);};
void ASTVisitor::visit(AssignmentNode *m) {m->print(*this);};
void ASTVisitor::visit(PrintNode *m) {m->print(*this);};
void ASTVisitor::visit(ReadNode *m) {m->print(*this);};
void ASTVisitor::visit(VariableReferenceNode *m) {m->print(*this);};
void ASTVisitor::visit(BinaryOperatorNode *m) {m->print(*this);};
void ASTVisitor::visit(UnaryOperatorNode *m) {m->print(*this);};
void ASTVisitor::visit(IfNode *m) {m->print(*this);};
void ASTVisitor::visit(WhileNode *m) {m->print(*this);};
void ASTVisitor::visit(ForNode *m) {m->print(*this);};
void ASTVisitor::visit(ReturnNode *m) {m->print(*this);};
void ASTVisitor::visit(FunctionCallNode *m) {m->print(*this);};

void ASTVisitorBase::space_counter_increase() {this->space_counter++;}
void ASTVisitorBase::space_counter_decrease() {this->space_counter--;}
void ASTVisitorBase::print_space() {for (size_t i = 0; i < space_counter; i++) { std::cout << "  "; }}
