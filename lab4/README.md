# PIMPL practice
## Team
Morhunenko Mykola
## Task

1. Modify the content * of LookupTable.h and LookupTable.cpp files such that the LookupTable class was *implemented by the PIMPL idiom.
   - Definition of the interface class called LookupTable will contain only a single non-public member variable, namely a pointer to the implementation class object.
   - Except this variable, the class may have no non-public member functions and variables.
   - Definition of a non-public member type is allowed.
   - You may use either an “ordinary” (raw) pointer or a smart pointer of type std::unique_ptr.
   - In case of using a smart pointer, the implementation may be more complex
2. Verify the functionality of your solution such that you change the type for the lookup table container from std::map<int, std::string> to std::unordered_map<int, std::string>.
   - Don’t forget that this update will require also an update of included header files.
   - With the correctly working PIMPL idiom, this update must not require any modificatoin of the LookupTable.h header file.
3. From the LookupTable.h header file remove all header files inclusion (#include directives) that, are unnecessary after the PIMPL idiom implementation.



## IMPORTANT
cmake is a git submodule
either make submodule.recurse true globally
```
git config --global submodule.recurse true
```
or after cloning this template use...
```
git submodule init
git submodule update
```
or clone it using
```
git clone  --recurse-submodules <link>
```
