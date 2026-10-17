#ifndef UTYPES_H
#define UTYPES_H

#if defined(__x86_64__) || defined(_M_X64)
    typedef unsigned char  uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int   uint32_t;
    typedef unsigned long  uint64_t;

#elif defined(__i386) || defined(_M_IX86)
    typedef unsigned char  uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int   uint32_t;
    typedef unsigned long long uint64_t;

#endif

#endif