# ExpressionParser
A parser for expressions and assignments based on Flex and Bison

# Compilation under Windows and Linux
Depending on how the file *Lexer.cpp* was generated, it can define an include for either *unistd.h* or *io.h*.
The first file only exists on Linux, the latter only on Windows.
To allow compilation on both, Linux and Windows, the file *Lexer.cpp* has to be manually adapted after generation, and either

```
#include <unistd.h>
```

or

```
#include <io.h>
```

should be replaced with

```
#if defined _WIN32 || defined _WIN64
#include <io.h>
#elif __linux__
#include <unistd.h>
#endif
```