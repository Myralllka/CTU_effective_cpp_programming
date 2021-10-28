# Semester Project

## Team

[Morhunenko Mykola](https://github.com/Myralllka)

## Problem assignment

- Implement class template `optional`, which will represent a simplified analogy of the `std::optional` class template (
  optionally contained value).
- Put class `optional` into the `epc` namespace, such that its fully-qualified name will be `::epc::optional`
- Class `epc::optional<T>` will — similarly to `std::optional<T>` — implement optionally contained/owned/managed value (
  object) of type T.
    - An object of type `epc::optional<T>` may or may not contain/own a value-object of type T.
    - An object of type `epc::optional<T>` is not allowed, in any case, to perform dynamic memory allocations.
    - Consequence: the optionally contained value must be located directly inside the optional object.
    - Namely, the binary representation of contained-owned object must be stored inside the binary representation of the
      owning optional object.
- Conditions, under which `optional` object does not contain value:
    - Initialization with the default constructor.
    - Initialization by another `optional` object that does not contain value (with copy or move constructor).
    - Assignment another `optional` object that does not contain value (with copy or move assignment operator).
    - Swapping content with another `optional` object that does not contain value (with member of free function swap).
    - Calling member function `reset()`.
- For implementation use only “pure” C++, namely its standard C++11 or C++14.
    - During implementation, pay attention to general principles of correct and effective programming.
    - Try to achieve maximum efficiency from the perspective of utilization of computer resources, primarily CPU time
      and system memory.
    - Write code in a readable and understandable way and comment it well if necessary.

## Solution and submission

- All your implementation — that is, the definition of the `epc::optional` class template, its member functions, and
  corresponding free functions — create in the form of a single header file named `optional.h`.
- Individual development versions subsequently store into the branch called semwork of your repository of the NIE-EPC
  course on the faculty GitLab instance.
- Keep the implemented header file optional.h directly inside the root directory of the semwork branch.
- Deadline for submission of the semester work is the end of the last week of the semester teaching period, namely,
  Sunday, December the 19th (included).
- The final submission is considered to be the version of the optional.h header file present in the repository at this
  deadline date. Any further updates might not be taken into consideration for the classification.
- A part of the final course exam will be also the discussion about the submitted solution.
- Substantial suspicion of non-individual development of the submitted solution may result in loss of points for
  classification of semester work.

## Classification

- For classification, test programs will be used, which will verify correctness and functionality of the submitted
  solution.
- In case that it will not be possible to compile the submitted solution (its compilation will result in errors), the
  classification will be *based on “code review” (that is, based on code visual examination).
    - In such a case, there is no possibility to define objective criteria for points assessment, and this will be made
      on subjective basis without any point guarantees.
- Otherwise, the point assessment will stem from the success rate of the submitted solution with respect to the test
  programs set.

## API

##### Class template `epc::optional`:

```cpp
// header file optional.h

namespace epc {

template <typename T>
class optional
{
... // implementation to be made
};

... // free functions

} // namespace epc
```

##### Template parameters

- T - value type

##### Public member types

- `value_type` — value type of the class (T).

##### Constructors and destructor

- `optional()` - default constructor. Constructs an object that does not contain value.
- `optional(const optional& other)` - copy constructor.
    - if `other` does contain value, initializes value by the expression `*other`.
    - if `other` does not contain value, constructs an object that does not contain value (similarly as default
      constructor).
- `optional(optional&& other)` - move constructor.
    - if `other` does contain value, initializes value by the expression `std::move(*other)`.
    - if `other` does not contain value, constructs an object that does not contain value (similarly as default
      constructor).
- `template <typename... Ts> optional(std::in_place_t, Ts&&... args)` - converting constructor.
    - Initializes value by the perfect forwarding technique applied on arguments `args...`
- `~optional()` - destructor
    - If the actual object `(*this)` does contain value, that is destructed.
    - Otherwise, it does not perform any operation.

##### Assignment operators

- `optional& operator=(const optional& other)` — copy assignment operator.
    - If the source object (`other`) and the destination object (`*this`) both do not contain value, it has no effect.
    - If the destination object does contain value and the source object does not, the value of the destination object
      is destructed.
    - If the destination object does not contain value and the source object does, initializes the value of the
      destination object by the expression `*other`.
    - If both the source object and the destination object do contain value, the value of the destination object is
      assigned to the value of the source object by the expression = `*other`.
    - Returns a reference to itself (destination object).
- `optional& operator=(optional&& other)` - move assignment operator.
    - If the source object (`other`) and the destination object (`*this`) both do not contain value, it has no effect.
    - If the destination object does contain value and the source object does not, the value of the destination object
      is destructed.
    - If the destination object does not contain value and the source object does, initializes the value of the
      destination object by the expression `std::move(*other)`.
    - If both the source object and the destination object do contain value, the value of the destination object is
      assigned to the value of the source object by the expression `= std::move(*other)`.
    - Returns a reference to itself (destination object).

##### Other member functions

- `const T* operator->() const` — returns a pointer to the contained value. In case there is no value contained, yields
  undefined behavior.
- `T* operator->()` — returns a pointer to the contained value. In case there is no value contained, yields undefined
  behavior.
- `const T& operator*() const` — returns a reference to the contained value. In case there is no value contained, yields
  undefined behavior.
- `T& operator*()` — returns a reference to the contained value. In case there is no value contained, yields undefined
  behavior.
- `operator bool()` const — returns `true` or `false` in case that the actual object (`*this`) does or does not contain
  value, respectively.
- `void swap(optional& other)` — swap content of the destination object (`*this`) and the source object (`other`).
    - If the source object and the destination object both do not contain value, it has no effect.
    - If the destination object does contain value and the source object does not, first, initializes the value of the
      source object by the expression `std::move(**this)`, and then, destructs the value of the destination object.
    - If the destination object does not contain value and the source object does, first, initializes the value of the
      destination object by the expression `std::move(*other)`, and then, destructs the value of the source object.
    - If both the source object and the destination object do contain value, swaps their content by calling
      using `std::swap; swap(**this, *other);`.
- `void reset()`
    - If the actual object (`*this`) does contain value, this is destructed.
    - Otherwise, it has no effect.
- `template <typename... Ts> void emplace(Ts&&... args)`
    - If the actual object (`*this`) does contain value, this is destructed first.
    - Then, it initializes the new value by the perfect forwarding technique applied to the arguments `args...`.

##### Free functions

- `template <typename T> void swap(optional<T>& a, optional<T>& b)` - swaps content of the objects `a` and `b` (
  effectively equivalent with calling a.swap(b)).
- Free functions shall be in the same namespace epc.

## Usage
