#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "EndianTranslator.h"


/* ELF identification values */

#define ELFCLASS32 1
#define ELFCLASS64 2

#define ELFDATA2LSB 1
#define ELFDATA2MSB 2


/* ELF types */

#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4


/* Machine types */

#define EM_X86_64 62


/* Program Header types */

#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4


/* Section types */

#define SHT_NULL     0
#define SHT_PROGBITS 1
#define SHT_SYMTAB   2
#define SHT_STRTAB   3
#define SHT_RELA     4
#define SHT_NOBITS   8
#define SHT_DYNSYM   11


/* Section flags */

#define SHF_WRITE     0x1
#define SHF_ALLOC     0x2
#define SHF_EXECINSTR 0x4


uint16_t read16(const unsigned char bytes[2], int little_endian)
{
    if (little_endian)
        return read_uint16_le(bytes);

    return read_uint16_be(bytes);
}


uint32_t read32(const unsigned char bytes[4], int little_endian)
{
    if (little_endian)
        return read_uint32_le(bytes);

    return read_uint32_be(bytes);
}


uint64_t read64(const unsigned char bytes[8], int little_endian)
{
    if (little_endian)
        return read_uint64_le(bytes);

    return read_uint64_be(bytes);
}


const char *get_elf_class(unsigned char elf_class)
{
    switch (elf_class) {
        case ELFCLASS32:
            return "ELF32";

        case ELFCLASS64:
            return "ELF64";

        default:
            return "Unknown";
    }
}


const char *get_endianness(unsigned char endian)
{
    switch (endian) {
        case ELFDATA2LSB:
            return "Little Endian";

        case ELFDATA2MSB:
            return "Big Endian";

        default:
            return "Unknown";
    }
}


const char *get_type(uint16_t type)
{
    switch (type) {
        case ET_NONE:
            return "NONE";

        case ET_REL:
            return "REL (Relocatable)";

        case ET_EXEC:
            return "EXEC (Executable)";

        case ET_DYN:
            return "DYN (Shared Object / PIE)";

        case ET_CORE:
            return "CORE";

        default:
            return "Unknown";
    }
}


const char *get_machine(uint16_t machine)
{
    switch (machine) {
        case EM_X86_64:
            return "x86-64";

        default:
            return "Unknown";
    }
}


const char *get_program_type(uint32_t type)
{
    switch (type) {
        case PT_NULL:
            return "NULL";

        case PT_LOAD:
            return "LOAD";

        case PT_DYNAMIC:
            return "DYNAMIC";

        case PT_INTERP:
            return "INTERP";

        case PT_NOTE:
            return "NOTE";

        default:
            return "UNKNOWN";
    }
}


const char *get_section_type(uint32_t type)
{
    switch (type) {
        case SHT_NULL:
            return "NULL";

        case SHT_PROGBITS:
            return "PROGBITS";

        case SHT_SYMTAB:
            return "SYMTAB";

        case SHT_STRTAB:
            return "STRTAB";

        case SHT_RELA:
            return "RELA";

        case SHT_NOBITS:
            return "NOBITS";

        case SHT_DYNSYM:
            return "DYNSYM";

        default:
            return "UNKNOWN";
    }
}


void print_section_flags(uint64_t flags)
{
    printf("%c", (flags & SHF_ALLOC) ? 'A' : ' ');
    printf("%c", (flags & SHF_WRITE) ? 'W' : ' ');
    printf("%c", (flags & SHF_EXECINSTR) ? 'X' : ' ');
}


void print_program_headers(
    FILE *file,
    uint64_t phoff,
    uint16_t phentsize,
    uint16_t phnum,
    int little_endian,
    int is_64_bit
)
{
    printf("\n========== PROGRAM HEADERS ==========\n");

    printf("Offset: 0x%lX\n", phoff);
    printf("Entry size: %u bytes\n", phentsize);
    printf("Number of entries: %u\n\n", phnum);

    for (uint16_t i = 0; i < phnum; i++) {

        uint64_t offset = phoff + ((uint64_t)i * phentsize);

        fseek(file, (long)offset, SEEK_SET);

        unsigned char buffer[64];

        if (phentsize > sizeof(buffer)) {
            printf("Program Header too large.\n");
            return;
        }

        if (fread(buffer, 1, phentsize, file) != phentsize) {
            printf("Failed to read Program Header.\n");
            return;
        }

        printf("Program Header %u\n", i);
        printf("-------------------------\n");

        if (is_64_bit) {

            uint32_t p_type = read32(buffer, little_endian);
            uint32_t p_flags = read32(buffer + 4, little_endian);

            uint64_t p_offset = read64(buffer + 8, little_endian);
            uint64_t p_vaddr  = read64(buffer + 16, little_endian);
            uint64_t p_paddr  = read64(buffer + 24, little_endian);
            uint64_t p_filesz = read64(buffer + 32, little_endian);
            uint64_t p_memsz  = read64(buffer + 40, little_endian);
            uint64_t p_align  = read64(buffer + 48, little_endian);

            printf("Type:   %s\n", get_program_type(p_type));

            printf("Flags:  %c%c%c\n",
                   (p_flags & 4) ? 'R' : '-',
                   (p_flags & 2) ? 'W' : '-',
                   (p_flags & 1) ? 'X' : '-');

            printf("Offset: 0x%lX\n", p_offset);
            printf("VAddr:  0x%lX\n", p_vaddr);
            printf("PAddr:  0x%lX\n", p_paddr);
            printf("FileSz: 0x%lX\n", p_filesz);
            printf("MemSz:  0x%lX\n", p_memsz);
            printf("Align:  0x%lX\n", p_align);
        }

        printf("\n");
    }
}


void print_section_headers(
    FILE *file,
    uint64_t shoff,
    uint16_t shentsize,
    uint16_t shnum,
    uint16_t shstrndx,
    int little_endian,
    int is_64_bit
)
{
    printf("\n========== SECTION HEADERS ==========\n");

    printf("Offset: 0x%lX\n", shoff);
    printf("Entry size: %u bytes\n", shentsize);
    printf("Number of entries: %u\n", shnum);
    printf("String table index: %u\n\n", shstrndx);


    /*
     * First we need the section containing the section names.
     */

    uint64_t string_table_offset = 0;
    uint64_t string_table_size = 0;

    if (shstrndx < shnum) {

        uint64_t string_header_offset =
            shoff + ((uint64_t)shstrndx * shentsize);

        fseek(file, (long)string_header_offset, SEEK_SET);

        unsigned char buffer[64];

        if (shentsize > sizeof(buffer)) {
            printf("Section Header too large.\n");
            return;
        }

        fread(buffer, 1, shentsize, file);

        if (is_64_bit) {

            string_table_offset =
                read64(buffer + 24, little_endian);

            string_table_size =
                read64(buffer + 32, little_endian);
        }
    }


    for (uint16_t i = 0; i < shnum; i++) {

        uint64_t offset =
            shoff + ((uint64_t)i * shentsize);

        fseek(file, (long)offset, SEEK_SET);

        unsigned char buffer[64];

        if (shentsize > sizeof(buffer)) {
            printf("Section Header too large.\n");
            return;
        }

        if (fread(buffer, 1, shentsize, file) != shentsize) {
            printf("Failed to read Section Header.\n");
            return;
        }

        uint32_t sh_name;
        uint32_t sh_type;

        uint64_t sh_flags;
        uint64_t sh_addr;
        uint64_t sh_offset;
        uint64_t sh_size;

        if (is_64_bit) {

            sh_name   = read32(buffer, little_endian);
            sh_type   = read32(buffer + 4, little_endian);

            sh_flags  = read64(buffer + 8, little_endian);
            sh_addr   = read64(buffer + 16, little_endian);
            sh_offset = read64(buffer + 24, little_endian);
            sh_size   = read64(buffer + 32, little_endian);
        }
        else {
            continue;
        }


        char section_name[256] = "<unknown>";

        /*
         * sh_name is an offset inside the section-name string table.
         */

        if (string_table_size > 0 &&
            sh_name < string_table_size) {

            uint64_t name_position =
                string_table_offset + sh_name;

            fseek(file, (long)name_position, SEEK_SET);

            if (fgets(section_name,
                      sizeof(section_name),
                      file) != NULL) {

                /* fgets may read beyond the actual name */
                for (int j = 0; j < sizeof(section_name); j++) {
                    if (section_name[j] == '\n') {
                        section_name[j] = '\0';
                        break;
                    }
                }
            }
        }


        printf("[%2u] %-20s ", i, section_name);

        printf("Type: %-10s ",
               get_section_type(sh_type));

        printf("Addr: 0x%016lX ",
               sh_addr);

        printf("Offset: 0x%08lX ",
               sh_offset);

        printf("Size: 0x%08lX ",
               sh_size);

        printf("Flags: ");
        print_section_flags(sh_flags);

        printf("\n");
    }
}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <ELF file>\n", argv[0]);
        return 1;
    }


    FILE *file = fopen(argv[1], "rb");

    if (file == NULL) {
        printf("Couldn't open file\n");
        return 1;
    }


    /*
     * =========================
     * ELF IDENTIFICATION
     * =========================
     */

    unsigned char ident[16];

    if (fread(ident, 1, 16, file) != 16) {
        printf("Failed to read ELF identification.\n");
        fclose(file);
        return 1;
    }


    /* Check ELF magic */

    if (ident[0] != 0x7F ||
        ident[1] != 'E' ||
        ident[2] != 'L' ||
        ident[3] != 'F') {

        printf("Not an ELF file.\n");
        fclose(file);
        return 1;
    }


    unsigned char elf_class = ident[4];
    unsigned char endian = ident[5];

    int little_endian;

    if (endian == ELFDATA2LSB)
        little_endian = 1;
    else if (endian == ELFDATA2MSB)
        little_endian = 0;
    else {
        printf("Unknown endian format.\n");
        fclose(file);
        return 1;
    }


    int is_64_bit = (elf_class == ELFCLASS64);


    /*
     * =========================
     * ELF HEADER
     * =========================
     */

    fseek(file, 16, SEEK_SET);


    unsigned char type[2];
    unsigned char machine[2];
    unsigned char version[4];
    unsigned char entry[8];
    unsigned char phoff[8];
    unsigned char shoff[8];
    unsigned char flags[4];

    unsigned char ehsize[2];
    unsigned char phentsize[2];
    unsigned char phnum[2];
    unsigned char shentsize[2];
    unsigned char shnum[2];
    unsigned char shstrndx[2];


    fread(type, 1, 2, file);
    fread(machine, 1, 2, file);
    fread(version, 1, 4, file);
    fread(entry, 1, 8, file);
    fread(phoff, 1, 8, file);
    fread(shoff, 1, 8, file);
    fread(flags, 1, 4, file);

    fread(ehsize, 1, 2, file);
    fread(phentsize, 1, 2, file);
    fread(phnum, 1, 2, file);
    fread(shentsize, 1, 2, file);
    fread(shnum, 1, 2, file);
    fread(shstrndx, 1, 2, file);


    uint16_t type_value =
        read16(type, little_endian);

    uint16_t machine_value =
        read16(machine, little_endian);

    uint32_t version_value =
        read32(version, little_endian);

    uint64_t entry_value =
        read64(entry, little_endian);

    uint64_t phoff_value =
        read64(phoff, little_endian);

    uint64_t shoff_value =
        read64(shoff, little_endian);

    uint32_t flags_value =
        read32(flags, little_endian);

    uint16_t ehsize_value =
        read16(ehsize, little_endian);

    uint16_t phentsize_value =
        read16(phentsize, little_endian);

    uint16_t phnum_value =
        read16(phnum, little_endian);

    uint16_t shentsize_value =
        read16(shentsize, little_endian);

    uint16_t shnum_value =
        read16(shnum, little_endian);

    uint16_t shstrndx_value =
        read16(shstrndx, little_endian);


    /*
     * =========================
     * PRINT ELF INFORMATION
     * =========================
     */

    printf("\n========== ELF HEADER ==========\n");

    printf("Magic:       %02X %02X %02X %02X\n",
           ident[0], ident[1], ident[2], ident[3]);

    printf("Class:       %s\n",
           get_elf_class(elf_class));

    printf("Endianness:  %s\n",
           get_endianness(endian));

    printf("Version:     %u\n",
           ident[6]);

    printf("OS ABI:      %u\n",
           ident[7]);

    printf("ABI Version: %u\n",
           ident[8]);

    printf("Type:        %s (%u)\n",
           get_type(type_value),
           type_value);

    printf("Machine:     %s (%u)\n",
           get_machine(machine_value),
           machine_value);

    printf("ELF Version: %u\n",
           version_value);

    printf("Entry:       0x%lX\n",
           entry_value);

    printf("PH Offset:   0x%lX\n",
           phoff_value);

    printf("SH Offset:   0x%lX\n",
           shoff_value);

    printf("Flags:       0x%X\n",
           flags_value);

    printf("ELF Header:  %u bytes\n",
           ehsize_value);

    printf("PH Size:     %u bytes\n",
           phentsize_value);

    printf("PH Count:    %u\n",
           phnum_value);

    printf("SH Size:     %u bytes\n",
           shentsize_value);

    printf("SH Count:    %u\n",
           shnum_value);

    printf("SH String:   %u\n",
           shstrndx_value);


    /*
     * =========================
     * PROGRAM HEADERS
     * =========================
     */

    print_program_headers(
        file,
        phoff_value,
        phentsize_value,
        phnum_value,
        little_endian,
        is_64_bit
    );


    /*
     * =========================
     * SECTION HEADERS
     * =========================
     */

    print_section_headers(
        file,
        shoff_value,
        shentsize_value,
        shnum_value,
        shstrndx_value,
        little_endian,
        is_64_bit
    );


    fclose(file);

    return 0;
}