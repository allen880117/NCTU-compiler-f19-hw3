#include <iostream>
#include <memory>
#include <vector>

#include "animal.hpp"
#include "sound_visitor.hpp"

int main()
{
  //std::vector<std::shared_ptr<Animal>> v;
  //std::shared_ptr<Animal> a(std::make_shared<Cat>(12, 'c'));
  //std::shared_ptr<Animal> b(std::make_shared<Dog>(13));
  std::vector<Animal *> v;
  Cat* a = new Cat(12, 'c');
  Dog* b = new Dog(13);

  v.push_back(a);
  v.push_back(b);
  //v.push_back(std::make_shared<Cat>(12, 'c'));
  //v.push_back(std::make_shared<Dog>(13));

  SoundVisitor sd;
  for (size_t i = 0; i < v.size(); i++)
    v[i]->accept(sd);
  return 0;
}
