#include "AST/ast.hpp"
#include "AST/program.hpp"

// TODO
void ASTVisitor::visit(ProgramNode *m) {m->print();}
void ASTVisitor::visit(DeclarationNode *m) {m->print();};
void ASTVisitor::visit(VariableNode *m) {m->print();};
void ASTVisitor::visit(ConstantValueNode *m) {m->print();};
void ASTVisitor::visit(FunctionNode *m) {m->print();};
void ASTVisitor::visit(CompoundStatementNode *m) {m->print();};
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
