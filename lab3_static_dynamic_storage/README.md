# Included vs dynamical storage

## Introduction

Consider the PairInt class that represents a pair of integer numbers. This class is defined in the PairInt.h header file

## Assignment
- Implement the PairIntOwner class that serves as an optional owner of an object of type PairInt, while the owned object will be upon request stored either in the included or dynamically allocated storage. <br>
- The PairIntOwner class will be implemented in the PairIntOwner.h header file.<br>
  To avoid violation of the ODR (one definition rule), the member functions needs to be defined either inside the class definition or outside with the inline specifier.<br>
### Class interface

- `enum Storage { INCLUDED, DYNAMIC }` – constants used below.
- `PairIntOwner()` - default constructor. Does not initialize any object of type PairInt.
- `PairIntOwner(Storage s , int a, int b)` -- converting constructor. Creates an object of type PairInt initialized by the a and b parameters in storage that:
  - will be included inside the storage of the owner object *this in case when s equals INCLUDED;
  - will be dynamically allocated in case when s equals DYNAMIC.
- `~PairIntOwner()` – destructor. If the owner *this has initialized/owns an object of type PairInt then this is destructed (independently of in which storage it is).
- `PariInt& value()` – if the owner *this owns an object of type PairInt, returns a reference bound to it. Otherwise, causes undefined behavior.

### Further requirements
- Implement the class in such a way that when the owned object is accessed (by using the member function value()) no branching is necessary.
- At the same time, try to make the size of the class objects storage (size of its binary representation) as small as possible, that is, avoid unnecessary member variables.
