#include "visitor/visitor.hpp"
#include <iostream>

void ASTVisitorBase::space_counter_increase() {this->space_counter++;}
void ASTVisitorBase::space_counter_decrease() {this->space_counter--;}
void ASTVisitorBase::print_space() {for (size_t i = 0; i < space_counter; i++) { std::cout << "  "; }}