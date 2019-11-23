#if 0
#include "AST/program.h"

#include <stdio.h>

AstNode *newProgramNode(void) {
    // TODO
    printf("I didn't put the Program Node down in black and white, so it's "
           "between existence and non-existence. Surprise!\n");
    return NULL;
}

void freeProgramNode(void *node) {
    // TODO
    printf("You're a mature adult until you remember to free the memory space "
           "you allocated.\n");
}
#endif

#include "AST/program.hpp"
#include <iostream>

void ProgramNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void DeclarationNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void VariableNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ConstantValueNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void FunctionNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void CompoundStatementNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void AssignmentNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void PrintNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ReadNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void VariableReferenceNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void BinaryOperatorNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void UnaryOperatorNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void IfNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void WhileNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ForNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void ReturnNode::print() {std::cout<<"Is Hello?"<<std::endl;}
void FunctionCallNode::print() {std::cout<<"Is Hello?"<<std::endl;}