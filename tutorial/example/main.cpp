#include <iostream>
#include <memory>
#include <vector>

#include "animal.hpp"
#include "sound_visitor.hpp"

int main()
{
  std::vector<std::shared_ptr<Animal>> v;
  v.push_back(std::make_shared<Cat>());
  v.push_back(std::make_shared<Dog>());

  SoundVisitor sd;
  for (size_t i = 0; i < v.size(); i++)
    v[i]->accept(sd);
  return 0;
}
