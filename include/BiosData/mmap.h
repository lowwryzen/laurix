#ifndef KERNEL_MEMORY_MAP
#define KERNEL_MEMORY_MAP
#include <utypes.h>

typedef struct {
    uint32_t magic;        // validação por magic
    uint32_t count;        // quantas entradas E820 existem
    uint32_t entry_size;   // sizeof(e820_entry_t)
} memmap_header_t;
typedef struct {
    uint64_t base;   // endereço inicial da região
    uint64_t length; // tamanho da região em bytes
    uint32_t type;   // tipo da memória
} __attribute__((packed)) e820_entry_t;

#define MMAP_MAGIC 0x4D4D4150
#define MMAP_ADDR 0x8000

#define memory_header_info_addr ((memmap_header_t*)MMAP_ADDR)

#endif