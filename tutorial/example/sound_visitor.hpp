#include "animal.hpp"

class SoundVisitor : public AnimalVisitorBase
{
public:
  void visit(Cat *m) override;
  void visit(Dog *m) override;
};