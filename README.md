<h1 align="center">IniLite</h1>

<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-green?style=flat-square" alt="MIT License" />
  <img src="https://img.shields.io/github/last-commit/simon-danielsson/inilite/main?style=flat-square&color=blue" alt="Last commit" />
      <img src="https://img.shields.io/badge/C_version-99-cyan?style=flat-square" alt="ANSI C" />
</p>
  
<p align="center">
  <a href="#info">Info</a> •
  <a href="#install">Install</a> •
  <a href="#usage">Usage</a> •
  <a href="#license">License</a>
</p>  
  
---
<div id="info"></div>

## Info
  
A header-only C library for serializing and de-serializing `.ini` files.
  
If you think this library could be of use to you, I'd recommend that you
first and foremost study the [source code](./inilite.h) on your own.
  
---
<div id="install"></div>

## Install
  
Simply clone or copy-paste [inilite.h](./inilite.h) into your codebase and include it.
  
``` c
#define INILITE_IMPLEMENTATION
#include "inilite.h"
```
  
---
<div id="usage"></div>
  
## Usage
   
### De-serialization
  
Regarding ownership: the `IniSection`/`Ini` structs keep ownership of memory. The `get`
functions only return references that would need to be properly copied if you want to
keep using them after `Ini_free()`.
    
``` c
Ini ini_in = {0};
Ini_init(&ini_in, content_of_ini_file);

IniSection *ini_db = Ini_get_section(&ini_in, "database");
printf("name: %s\n", IniSection_get_value(ini_db, "name"));

Ini_free(&ini_in);
```
   
### Serialization
  
Serialization is done procedurally. I chose this approach since it makes it
trivial to (for example) iterate on an array to save its values to an `.ini` file through a simple for-loop.
  
``` c
Ini ini_out = {0};
Ini_init(&ini_out, NULL);

Ini_append_section(&ini_out, "gojo");
Ini_append_kv(&ini_out, "name", "Satoru Gojo");
Ini_append_kv(&ini_out, "occupation", "Jujutsu Sorcerer");
Ini_append_kv(&ini_out, "birthday", "December 7, 1989");

Ini_append_section(&ini_out, "itadori");
Ini_append_kv(&ini_out, "name", "Yuji Itadori");
Ini_append_kv(&ini_out, "occupation", "Jujutsu Sorcerer, Student");
Ini_append_kv(&ini_out, "birthday", "March 20, 2003");

char new_content[128 * 100] = {0};
Ini_build(&ini_out, new_content);
Ini_free(&ini_out);

FILE *output = fopen("output.ini", "w");
fprintf(output, "%s", new_content);
```
    
---
<div id="license"></div>
  
## License
  
This project is licensed under the [MIT License](https://github.com/simon-danielsson/inilite/blob/main/LICENSE).  
