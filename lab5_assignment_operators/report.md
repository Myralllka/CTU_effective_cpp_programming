## Part 1

There are few differences between case 1 and cases 2 and 3.

- If `this == other` in case 1 program do nothing, but in cases 2 and 3 it always creates another, temporary object
- In cases 2, we always call a copy constructor even when we want to move the object. In case of std::vector or some
  other container, that own the object, copy operation will be much more resource consumable
- Both case 2 and case 3 call a custom swap function, that swaps the content of each object, not objects itself. So if
  the content can not be swapped as easy, it also will call copy/move constructors, but I am not sure how it will work
  there

## Part 2

#### Case 1

copy assignment: (CA)
move assignment: (MA)
std::swap: (MC)(MA)(MA)
custom swap:

#### Case 2

copy assignment: (CA)(CC)
move assignment: (MA)(CC)
std::swap: (MC)(MA)(CC)(MA)(CC)
custom swap:

#### Case 3

copy assignment: (CC)(UA)
move assignment: (MC)(UA)
std::swap: (MC)(MC)(UA)(MC)(UA)
custom swap:
