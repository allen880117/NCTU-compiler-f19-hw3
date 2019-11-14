#ifndef __PROGRAM_H
#define __PROGRAM_H

#include "AST/ast.h"

typedef struct __ProgramNode {
  // TODO
} ProgramNode;

AstNode *newProgramNode(void);
void freeProgramNode(void *node);

#endif
