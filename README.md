![image](https://github.com/user-attachments/assets/c62f2509-363a-4515-ab39-af35a83a3c10)# pycppgen

## Overview
`pycppgen` is a Python script designed to parse and generate C++ reflection code based on user-defined tags. By embedding specific tags within your C++ code, the script dynamically generates reflection-ready templates and attributes to streamline your development workflow.

## Motivation
This project was created as:
1. A learning exercise to explore Python programming.
2. A solution to improve reflection mechanisms within my Vulkan framework: [VkFramework](https://leobenaducci.visualstudio.com/VkFramework).

## Design requeriments
- **Non-instrusive**: except for the comments to declare attributes.
- **Fast**: short iteration times are important.
- **Flexible**: no fixed tags or attributes.
- **Plug & Play**: just run the script and include the generated files.
- **Inline everything**: Support static linking and inherit reflection data from dependencies.

## Features
- **Tag-Based Code Generation**: Add `$[[pycppgen]]` or `$[[pycppgen <attributes>]]` to a declaration in your C++ code to generate reflection data.
- **Reflection Support**: Includes both language reflection and user-provided attributes to enhance metadata management.
- **Fast change detection**: Caches as much data as possible to allow fast iteration

## The test
- Iterate over all enums and values, convert enum to string and string to enum (TODO: bit flags)
![image](https://github.com/user-attachments/assets/da24781d-aed4-466d-af34-9cfffd8a2ea0)

- Iterate over all reflected types and its members
![{9C197E77-9F82-488A-8910-D680E4C75A80}](https://github.com/user-attachments/assets/3547d9a1-2a7d-4b4b-91f7-525797294ebc)



## Usage
1. Clone the repository:
   ```bash
   git clone [https://github.com/<your-repo-name>.git](https://github.com/leobenaducci/pycppgen.git)
   ```
2. Run the Python script on your C++ files:
   ```bash
   python main.py <project-path> <options>
   options:
      -I<include_dir>
      -D<definition>
      --I<include_dirs_separated_by_semicolons>
      --D<dependencies>
   ```
3. Add `$[[pycppgen]]` or `$[[pycppgen <attributes>]]` tags in your C++ code where you want templates to be generated.

   Example struct decl: 
      ```
      //$[[pycppgen tag1=3.f;test_tag=string with spaces;serialize]]
      struct A {

         //$[[pycppgen editable]]
         size_t B = 1;
      };
      ```
   
   Example enum decl: 
      ```
      //$[[pycppgen bitflags]]
      enum class E : int {
         None = 0,
         Something = 1, //$[[pycppgen hidden]]
         Value = 2,
      };
      ```

## Contribution
Feel free to fork the repository and submit pull requests. Suggestions and improvements are always welcome!

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Author
Leo Benaducci (https://www.linkedin.com/in/leobenaducci/)
