# JSON Library

**A lightweight C++17 static library for parsing, manipulating, and writing JSON files.**

Supports intuitive operations like `obj["age"][2] = false`, robust error handling, auto-resizing arrays, and a clean API for JSON file I/O.

---

## 📖 Overview

This is a **C++17 static library** (`jsonlib`) for working with JSON files. It provides functionality to:

- Parse JSON from files
- Manipulate JSON data structures (`objects`, `arrays`, `strings`, `numbers`, `booleans`, `null`)
- Write formatted JSON back to files

The library supports intuitive chained indexing (e.g., `obj["age"][2] = false`) with auto-resizing arrays and includes robust error handling for file operations and parsing.

---

## ✨ Features

- **Parse JSON:** Read and parse JSON files into a hierarchical data structure.
- **Manipulate JSON:** Modify data using intuitive syntax: `obj["age"][2] = false`, `obj["name"] = "gago"`.
- **Auto-resizing Arrays:** Automatically expands arrays on out-of-bound assignments.
- **Write JSON:** Output formatted JSON with customizable indentation.
- **Type Safety:** Strong runtime type checking.
- **C++17:** Clean, modern, efficient code using C++17.
- **No Dependencies:** Uses only the C++ standard library.

---

## 📁 Project Structure

```text
json_project/
├── include/
│   ├── json_value.hpp
│   ├── json_null.hpp
│   ├── json_boolean.hpp
│   ├── json_array.hpp
│   ├── json_string.hpp
│   ├── json_object.hpp
│   ├── json.hpp
│   ├── lexer.hpp
│   ├── parser.hpp
├── src/
│   ├── json_value.cpp
│   ├── json_null.cpp
│   ├── json_boolean.cpp
│   ├── json_array.cpp
│   ├── json_string.cpp
│   ├── json_object.cpp
│   ├── json.cpp
│   ├── lexer.cpp
│   ├── parser.cpp
├── CMakeLists.txt
└── README.md
```
## 📁 Project Structure

- **`include/`**  
  Contains header files for the JSON library classes:
  - `json_value.hpp`
  - `json_null.hpp`
  - `json_boolean.hpp`
  - `json_array.hpp`
  - `json_string.hpp`
  - `json_object.hpp`
  - `json.hpp`
  - `lexer.hpp`
  - `parser.hpp`

- **`src/`**  
  Contains implementation (`.cpp`) files for the library.

- **`CMakeLists.txt`**  
  CMake configuration script to build the static library `jsonlib`.

- **`README.md`**  
  Project documentation and usage instructions.

## ⚙️ Installation

### 📋 Prerequisites

- CMake **3.10** or higher  
- A **C++17-compatible compiler** (e.g., GCC, Clang, MSVC)  
- No external dependencies  

---

### 🛠️ Build Instructions

1. **Clone the repository**:

   ```bash
   git clone https://github.com/your-username/json_project.git
   cd json_project
2. **Create a build directory and run CMake**:
   ```bash
   mkdir build && cd build
   cmake ..
3. **Build the static library**:
   ```plain
   make
4. 🔧 The static library **`libjsonlib.a`** will be generated in the `build/` directory.

### 📦 Installation (Optional)

To install the library and headers system-wide (e.g., to `/usr/local`):
```bash
   sudo make install
```
(Note: The provided CMakeLists.txt does not include an install target. See "Contributing" for adding one.)

### 🚀 Usage

The library provides a `json` class for file I/O and a hierarchy of classes (`json_object`, `json_array`, etc.) for manipulating JSON data. Below is an example of reading, modifying, and writing a JSON file.

### Example

```cpp
#include "json.hpp"
#include <iostream>

int main() {
    try {
        // Read and parse JSON file
        json handler("input.json");

        // Modify JSON structure
        json_value& json_val = handler.get_json();
        if (json_val.is_object()) {
            json_object& obj = json_val.as_object();
            // Ensure "age" is an array
            if (!obj.has_key("age") || !obj["age"].is_array()) {
                obj["age"] = std::make_unique<json_array>();
            }
            obj["age"][2] = false; // Assigns false at index 2, auto-resizing array
            obj["name"] = "gago";  // Assigns string value
            std::cout << "JSON Context:\n" << handler.get_context(2) << std::endl;
            handler.write_file("output.json", 2); // Write with 2-space indentation
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
```
### Input (`input.json):

```json
{
  "name": "John",
  "age": [1, 2]
}
```

### Output (output.json):

```json
{
  "name": "gago",
  "age": [
    1,
    2,
    false
  ]
}
```

## Linking with the Library

To use **jsonlib** in your project:

1. Include the headers: '-I/path/to/json_project/include'
2. Link against the library: -L/path/to/json_project/build -ljsonlib
3. Example compilation:
```bash
   g++ -std=c++17 main.cpp -I/path/to/json_project/include -L/path/to/json_project/build -ljsonlib -o my_program
```

## 🧰 API Overview

### `json` Class

- `json(const std::string& file_path)`: Reads and parses a JSON file.

- `json_value& get_json()`: Returns the parsed JSON data.

- `std::string get_context(int indent)`: Returns the JSON as a formatted string.

- `void write_file(const std::string& file_path, int indent)`: Writes JSON to a file.

### `json_object` Class

- Supports key-value pairs with `operator[](const std::string&)` for access and assignment.

- **Example:**  
  ```cpp
  obj["key"] = "value";
  obj["age"][2] = false;

### `json_array` Class

- Supports indexed access with auto-resizing for out-of-bounds assignments.

- **Example:**  
  ```cpp
  arr[2] = false; // creates json_null for indices 0 and 1 if needed
  ```
### Other Classes:
- `json_value` (base class), `json_null`, `json_boolean`, `json_number`, `json_string` for type-safe JSON manipulation.

## Contributing
Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a feature branch  (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -m "Add your feature"`)
4. Push to the branch (`git push origin feature/your-feature`).
5. Open pull request

## Potential Improvements

- Add installation targets to `CMakeLists.txt` for system-wide installation.

- Support nested object indexing (e.g., `obj["key1"]["key2"]`).

- Add unit tests using a framework like Catch2.

- Extend parser to handle more edge cases (e.g., Unicode escapes).

- Create a LICENSE file (e.g., MIT License) for the project.

## 📄 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). See the `LICENSE` file for details.

*(Note: You may need to add a LICENSE file to the repository.)*
