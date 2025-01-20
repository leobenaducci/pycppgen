# pycppgen

## Overview
`pycppgen` is a Python script designed to parse and generate C++ code based on user-defined tags. By embedding specific tags within your C++ code, the script dynamically generates reflection-ready templates and attributes to streamline your development workflow.

## Features
- **Tag-Based Code Generation**: Add `$[[pycppgen]]` or `$[[pycppgen <flags>]]` after a declaration in your C++ code to generate a `struct meta<type>` template.
- **Reflection Support**: Includes both basic reflection and user-provided attributes to enhance metadata management.

## Motivation
This project was created as:
1. A learning exercise to explore Python programming.
2. A solution to improve reflection mechanisms within my Vulkan framework: [VkFramework](https://leobenaducci.visualstudio.com/VkFramework).

## Examples

Call function by name Iterate over members and enum values
![image](https://github.com/user-attachments/assets/d371a087-d21b-46ee-8402-6f585a83f96f)

Enum attributes
![image](https://github.com/user-attachments/assets/465ed9d8-33de-4e57-8c84-0ff174ca24d3)

Class generated code
![image](https://github.com/user-attachments/assets/5dc67e0c-e3d4-44a6-87e6-8604aa061f4b)

Optimized build
![image](https://github.com/user-attachments/assets/8624073f-2448-4aea-9cde-f8179bc301ac)

## Planned Features
The project is a work in progress, and additional features are planned for future updates:
- Enhanced template reflection capabilities.
- Support for function reflection.
- Reflection for global and static variables.

## Usage
1. Clone the repository:
   ```bash
   git clone [https://github.com/<your-repo-name>.git](https://github.com/leobenaducci/pycppgen.git)
   ```
2. Run the Python script on your C++ files:
   ```bash
   python main.py <input-file> <options>
   ```
3. Add `$[[pycppgen]]` or `$[[pycppgen <flags>]]` tags in your C++ code where you want templates to be generated.

## Contribution
Feel free to fork the repository and submit pull requests. Suggestions and improvements are always welcome!

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Author
Leo Benaducci (https://www.linkedin.com/in/leobenaducci/)

---
Happy coding! 🎉

