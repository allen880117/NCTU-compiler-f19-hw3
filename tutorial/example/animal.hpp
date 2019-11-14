#pragma once

class AnimalVisitorBase
{
public:
  virtual void visit(class Cat *e) = 0;
  virtual void visit(class Dog *e) = 0;
};

class Animal
{
public:
  virtual void accept(class AnimalVisitorBase &v) = 0;
  virtual ~Animal(){};
};

class Cat : public Animal
{
public:
  void accept(AnimalVisitorBase &v) { v.visit(this); }
  void make_sound();
};

class Dog : public Animal
{
public:
  /*virtual*/ void accept(AnimalVisitorBase &v) { v.visit(this); }
  void make_sound();
};