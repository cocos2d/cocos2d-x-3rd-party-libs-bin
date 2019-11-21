#ifdef __aarch64__
#include "curlbuild-arm64.h"
#elif __arm__
#include "curlbuild-arm32.h"
#elif __i386__
#include "curlbuild-x86.h"
#elif __x86_64__
#include "curlbuild-x86_64.h"
#else
#error "Unsupported architecture!"
#endif
