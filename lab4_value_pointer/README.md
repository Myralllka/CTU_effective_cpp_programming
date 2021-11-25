# Value pointer

## Introduction
The standard C++ library contains only smart pointers that are able to copy or move the ownership of a particular object. It does not contain any smart pointer that would be able to create new objects and, at the same time, to copy or move their content.

## Assignment

- Implement the class template ValuePtr that serves as a smart pointer with the ability to create new objects with copying or moving their content.
- The content of an object of the ValuePtr<T> class is the ownership of an object of type T.
- This ownership is optional, similarly as, for instance, with the library smart pointer std::unique_ptr<T>.
- The ValuePtr class template implement in the ValuePtr.h header file.
