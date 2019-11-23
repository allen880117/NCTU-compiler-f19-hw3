#include "animal.hpp"
#include <iostream>

void Cat::make_sound() { std::cout << "Meow!" << std::endl; }
Cat::Cat(int, char){;}
void Dog::make_sound() { std::cout << "Woof!!" << std::endl; }
Dog::Dog(int){;}
void Dog::quake() { std::cout << "Woof Woof!!" << std::endl; }