#ifndef MACROS_H
#define MACROS_H

#include <typeinfo>

#ifdef FMT_API
   #if FMT_VERSION >= 40000
      #include <fmt/printf.h>
   #endif // FMT_VERSION
   #define NL fmt::printf("\n");
   #define NEWLINE fmt::printf("\n");
   #define DL fmt::printf("\n\n");
#else
   #define NL printf("\n");
   #define NEWLINE printf("\n");
   #define DL printf("\n\n");
#endif // FMT_API


#define Typename(x) typeid(x).name()

#endif//MACROS_H
