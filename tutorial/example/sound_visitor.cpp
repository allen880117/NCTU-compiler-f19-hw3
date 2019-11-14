#include "sound_visitor.hpp"
#include "animal.hpp"

void SoundVisitor::visit(Cat *m) { m->make_sound(); }
void SoundVisitor::visit(Dog *m) { m->make_sound(); }