#ifndef HW_PLATFORM_H_
#define HW_PLATFORM_H_

// OS
#if defined(WIN64) || defined(_WIN64)
    #define OS_WIN64
    #define OS_WIN32
#elif defined(WIN32)|| defined(_WIN32)
    #define OS_WIN32
#elif defined(ANDROID) || defined(__ANDROID__)
    #define OS_ANDROID
    #define OS_LINUX
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define OS_LINUX
#elif defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
    #include <TargetConditionals.h>
    #if defined(TARGET_OS_MAC) && TARGET_OS_MAC
        #define OS_MAC
        #define OS_DARWIN
        #ifdef __LP64__
            #define OS_DARWIN64
        #else
            #define OS_DARWIN32
        #endif
    #elif defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
        #define OS_IOS
    #else
        #define OS_MACOS
    #endif
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    #define OS_FREEBSD
    #define OS_BSD
#elif defined(__NetBSD__)
    #define OS_NETBSD
    #define OS_BSD
#elif defined(__OpenBSD__)
    #define OS_OPENBSD
    #define OS_BSD
#else
    #error "Unsupported operating system platform!"
#endif

#if defined(OS_WIN32) || defined(OS_WIN64)
    #undef  OS_UNIX
    #define OS_WIN
#else
    #define OS_UNIX
#endif

// CC
// _MSC_VER
// __MINGW32__
// __GNUC__
#ifdef __GNUC__
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#endif
// __clang__

// ARCH
#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
    #define ARCH_X86
    #define ARCH_X86_32
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
    #define ARCH_X64
    #define ARCH_X86_64
#elif defined(__arm__)
    #define ARCH_ARM
#elif defined(__aarch64__) || defined(__ARM64__)
    #define ARCH_ARM64
#endif

// ENDIAN
#ifndef BIG_ENDIAN
    #define BIG_ENDIAN      4321
#endif
#ifndef LITTLE_ENDIAN
    #define LITTLE_ENDIAN   1234
#endif
#define NET_ENDIAN     BIG_ENDIAN

#ifndef BYTE_ORDER
#if defined(ARCH_X86) || defined(ARCH_X86_64) || defined(__ARMEL__)
    #define BYTE_ORDER LITTLE_ENDIAN
#elif defined(__ARMEB__)
    #define BYTE_ORDER BIG_ENDIAN
#endif
#endif

// header files
#ifdef OS_WIN
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #define _CRT_SECURE_NO_WARNINGS
    #define _CRT_NONSTDC_NO_DEPRECATE
    #include <winsock2.h>
    #include <windows.h>
    #include <process.h>    // for getpid,exec
    #include <direct.h>     // for mkdir,rmdir,chdir,getcwd
    #include <io.h>         // for open,close,read,write,lseek,tell

    #define MKDIR(dir) mkdir(dir)
#else
    #include <unistd.h>
    #include <dirent.h>     // for mkdir,rmdir,chdir,getcwd
    #include <sys/time.h>   // for gettimeofday

    // socket
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <netinet/tcp.h>
    #include <netinet/udp.h>
    #include <fcntl.h>
    #include <netdb.h>  // for gethostbyname

    #define MKDIR(dir) mkdir(dir, 0777)
#endif

// ANSI C
#include <assert.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <signal.h>

// c99
#if defined(_MSC_VER) && _MSC_VER < 1700
typedef __int8              int8_t;
typedef __int16             int16_t;
typedef __int32             int32_t;
typedef __int64             int64_t;
typedef unsigned __int8     uint8_t;
typedef unsigned __int16    uint16_t;
typedef unsigned __int32    uint32_t;
typedef unsigned __int64    uint64_t;
#else
#include <stdbool.h>
#include <stdint.h>
#endif

// POSIX C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef _MSC_VER
#pragma warning (disable: 4100) // unused param
#pragma warning (disable: 4819) // Unicode
#else
#include <pthread.h>
#endif

#endif  // HW_PLATFORM_H_