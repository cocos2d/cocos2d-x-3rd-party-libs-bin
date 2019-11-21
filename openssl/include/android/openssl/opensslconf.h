#ifdef __aarch64__
#include "opensslconf-arm64.h"
#elif __arm__
#include "opensslconf-arm32.h"
#elif __i386__
#include "opensslconf-x86.h"
#elif __x86_64__
#include "opensslconf-x86_64.h"
#else
#error "Unsupported architecture!"
#endif
