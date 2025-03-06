# LANGUAGE

### A programming language.

---

## **Prerequisites**
- **CMake:** VERSION 3.30 or higher [Install CMake](https://cmake.org/install/)
- **Git:** [Install Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
- C++ Compiler (e.g., GCC, Clang, MSVC) with C++ 20 or higher
---

## FOR A CODE REVIEW:
I tend to mix programming paradigms (Imperative, OOP, Functional & Declarative) and pick the parts of each, which help me the most in the current situation, so don't freak out if you see a class/struct.<br><br>I know that C++ is way more, than just a OOP lang, and you can ignore the whole OOP indirectly, but a part where it is especially useful, in C++ specially is when you often forget to update the headers after you changed the args for a func and do often also forget to use the IDE tools for this. BTW my IDE is CLion.

---

## **Building the Project**


# LANG

## Build Instructions

### Building `LANG`

1. **Clone the Repository**:
```sh
git clone https://github.com/yourusername/LANG.git
cd LANG
```

2. **Create a Build Directory**:
```sh
mkdir build
cd build
```

3. **Configure with CMake**:
```sh
cmake ..
```
Optional: Specify a build type (e.g., Debug, Release):
```sh
cmake .. -DCMAKE_BUILD_TYPE=Release
```

4. **Build the Project**:
```sh
cmake --build .
```
Or with a specific build system (e.g., Make):
```sh
make -j4  # -j4 for parallel build
```

5. **Run the Application**:
```sh
./LANG
```
On Windows:
```sh
.\LANG.exe
```

