# JSON Library

**A lightweight C++17 static library for parsing, manipulating, and writing JSON.**

Supports intuitive operations like `obj["age"][2] = false`, implicit type conversions, STL-like container methods, and a clean API for JSON manipulation.

---

## Features

- **Parse JSON:** From files or strings using `json::parse()`
- **Factory Methods:** Create empty objects/arrays with `json::object()` and `json::array()`
- **Implicit Conversions:** `std::string name = obj["name"]` works directly
- **Chained Indexing:** `obj["users"][0]["name"] = "John"`
- **Auto-resizing Arrays:** Automatically expands arrays on out-of-bound assignments
- **STL-like Containers:** `size()`, `empty()`, `clear()`, `begin()`/`end()` for iteration
- **Comparison:** `operator==` and `operator!=` for all JSON types
- **Type Safety:** Strong runtime type checking with `is_*()` and `as_*()` methods
- **No Dependencies:** Uses only the C++ standard library
- **Single Header Include:** Just `#include "json.hpp"` to access everything

---

## Project Structure

```
JsonAPI/
├── include/
│   ├── json.hpp              # Main API entry point (includes all types)
│   ├── types/                # JSON value type classes
│   │   ├── json_value.hpp    # Core value type using std::variant (PIMPL)
│   │   ├── json_null.hpp
│   │   ├── json_boolean.hpp
│   │   ├── json_number.hpp
│   │   ├── json_string.hpp
│   │   ├── json_array.hpp
│   │   └── json_object.hpp
│   └── parser/               # Parsing components
│       ├── lexer.hpp
│       └── parser.hpp
├── src/                      # Implementation files (mirrors include/)
├── CMakeLists.txt
└── README.md
```

---

## Installation

### Prerequisites

- CMake **3.10** or higher
- A **C++17-compatible compiler** (e.g., GCC, Clang, MSVC)

### Build Instructions

```bash
mkdir build && cd build
cmake ..
make
```

The static library `libjsonlib.a` will be generated in the `build/` directory.

---

## Usage

### Parsing JSON

```cpp
#include "json.hpp"

// From string
json data = json::parse(R"({"name": "John", "age": 30})");

// From file
json file_data("input.json");
```

### Creating JSON

```cpp
#include "json.hpp"

// Create empty containers
json obj = json::object();
json arr = json::array();

// Build structure
json_object& root = obj.get_json().as_object();
root["name"] = "John";
root["age"] = 30;
root["active"] = true;
root["data"] = nullptr;
```

### Accessing Values

```cpp
json data = json::parse(R"({"name": "John", "age": 30, "active": true})");
json_object& obj = data.get_json().as_object();

// Implicit conversions
std::string name = obj["name"];  // "John"
double age = obj["age"];         // 30.0
int age_int = obj["age"];        // 30
bool active = obj["active"];     // true

// Explicit type checking
if (obj["name"].as_value().is_string()) {
    std::string value = obj["name"].as_value().as_string().get_value();
}
```

### Array Operations

```cpp
json arr_json = json::array();
json_array& arr = arr_json.get_json().as_array();

arr.push_back(json_value(1));
arr.push_back(json_value(2));
arr[5] = 10;  // Auto-resizes, fills with null

std::cout << arr.size() << std::endl;  // 6
std::cout << arr.empty() << std::endl; // false
```

### Iteration

```cpp
// Iterate over array
json_array& arr = data.get_json().as_array();
for (const auto& elem : arr) {
    std::cout << elem.dump() << std::endl;
}

// Iterate over object
json_object& obj = data.get_json().as_object();
for (const auto& [key, value] : obj) {
    std::cout << key << ": " << value.dump() << std::endl;
}
```

### Comparison

```cpp
json a = json::parse(R"({"x": 1})");
json b = json::parse(R"({"x": 1})");
json c = json::parse(R"({"x": 2})");

if (a.get_json() == b.get_json()) {
    std::cout << "Equal" << std::endl;
}

if (a.get_json() != c.get_json()) {
    std::cout << "Not equal" << std::endl;
}
```

### Writing JSON

```cpp
json data = json::parse(R"({"name": "John"})");

// To string (compact)
std::string compact = data.get_context();

// To string (formatted with 2-space indent)
std::string formatted = data.get_context(2);

// To file
data.write_file("output.json", 2);
```

---

## API Reference

### `json` Class

| Method | Description |
|--------|-------------|
| `json()` | Default constructor (empty) |
| `json(const std::string& file_path)` | Parse JSON from file |
| `static json parse(const std::string& str)` | Parse JSON from string |
| `static json object()` | Create empty JSON object |
| `static json array()` | Create empty JSON array |
| `json_value& get_json()` | Get root value reference |
| `std::string get_context(int indent = -1)` | Serialize to string |
| `void write_file(const std::string& path, int indent = 2)` | Write to file |

### `json_value` Class

| Method | Description |
|--------|-------------|
| `json_value()` | Default constructor (null) |
| `json_value(bool)` | Construct boolean value |
| `json_value(int)` / `json_value(double)` | Construct number value |
| `json_value(const char*)` / `json_value(const std::string&)` | Construct string value |
| `json_value(std::nullptr_t)` | Construct null value |
| `static json_value make_array()` | Create empty array value |
| `static json_value make_object()` | Create empty object value |
| `type()` | Get `json_type` enum |
| `is_null()`, `is_boolean()`, `is_number()`, `is_string()`, `is_array()`, `is_object()` | Type checking |
| `as_null()`, `as_boolean()`, `as_number()`, `as_string()`, `as_array()`, `as_object()` | Type casting (throws on mismatch) |
| `dump(int indent = -1)` | Serialize to string |
| `clone()` | Deep copy |
| `operator==` / `operator!=` | Value comparison |

### `json_object` Class

| Method | Description |
|--------|-------------|
| `operator[](const std::string& key)` | Access/create value by key |
| `size()` | Number of key-value pairs |
| `empty()` | Check if empty |
| `clear()` | Remove all entries |
| `contains(const std::string& key)` | Check if key exists |
| `erase(const std::string& key)` | Remove key |
| `begin()` / `end()` | Iterators for range-for |

### `json_array` Class

| Method | Description |
|--------|-------------|
| `operator[](size_t index)` | Access/create element (auto-resizes) |
| `size()` | Number of elements |
| `empty()` | Check if empty |
| `clear()` | Remove all elements |
| `push_back(json_value)` | Add element |
| `begin()` / `end()` | Iterators for range-for |

---

## Architecture

The library uses a **value-based design** with `std::variant` internally:

- `json_value` is the core type that can hold any JSON value
- Uses the **PIMPL idiom** to hide implementation details and reduce compile times
- All JSON types (`json_null`, `json_boolean`, `json_number`, `json_string`, `json_array`, `json_object`) are standalone classes
- The variant is stored internally: `std::variant<std::monostate, json_null, json_boolean, json_number, json_string, std::unique_ptr<json_array>, std::unique_ptr<json_object>>`

---

## Linking

```bash
g++ -std=c++17 main.cpp -I/path/to/JsonAPI/include -L/path/to/JsonAPI/build -ljsonlib -o my_program
```

---

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
