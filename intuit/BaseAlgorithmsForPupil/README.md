### cmake
https://cmake.org/cmake/help/latest/guide/tutorial/index.html

### refs
https://intuit.ru/studies/courses/997/313/info

### additional materials
http://cppalgo.blogspot.com/

### Build Instructions

To build the `BaseAlgorithmsForPupil` project, follow these steps:

1. **Navigate to the Project Directory**:
   ```bash
   cd /home/oleg/dev/algorithmsAndDataStructures/intuit/BaseAlgorithmsForPupil
   ```

2. **Create a Build Directory**:
   ```bash
   mkdir -p build && cd build
   ```

3. **Run CMake**:
   Configure the project using CMake:
   ```bash
   cmake ..
   ```

4. **Build the Project**:
   Compile the project:
   ```bash
   make
   ```

### Running Tests

To run the tests for the project:

1. **Build the Tests**:
   Ensure the tests are built along with the project (this is done automatically if the `test` subdirectories are included).

2. **Run Tests Using CTest**:
   From the `build` directory, execute:
   ```bash
   ctest
   ```
   Notes on using CTest:
   List Available Tests:
    ```bash 
    ctest -N
    ```
    Run a Specific Test:
    Use the -R option followed by a regex pattern matching the test name:

    ```bash
    ctest -R <test_name>
    ```
    Run Tests with Verbose Output:
    ```bash
    ctest -R <test_name> -V
    ```

3. **View Test Results**:
   CTest will display the results of all tests defined in the `test` subdirectories of the lectures.

### Notes
- The project uses GoogleTest for unit testing.
- Each lecture has its own `CMakeLists.txt` file to define executables, libraries, and tests.
- Tests are added using the `packageAddTestAndPractice` macro defined in `cmake/package_add_test.cmake`.