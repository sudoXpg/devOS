# devOS

devOS is a 32-bit hobby operating system under development, written in C with minimal assembly. It is intended as a minimal, modular kernel to understand low-level systems, including memory management, interrupts, and hardware interfaces.

## Overview

The kernel entry point is `kernel_start()` defined in `main.c`, which performs the following:

- Initializes the VGA terminal
- Sets up the Interrupt Descriptor Table (IDT)
- Initializes the kernel heap
- Configures and enables paging (4GB address space)
- Initializes disk lookup routines
- Enables hardware interrupts

```c
#include "headers/kernel.h"

static struct paging_4gb *kernel_paging = 0;

void kernel_start() {
    terminal_init();
    idt_init();
    start();  // Additional early setup
    kheap_init();

    kernel_paging = paging_new_4gb(
        PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL
    );
    paging_switch(kernel_paging->directory_entry);
    enable_paging();

    disk_lookup_init();
    __asm__("sti;");
}
````

## Directory Structure

```
devOS/
├── headers/               # Header files
│   └── kernel.h
├── kernel/
│   └── main.c             # Kernel entry point
├── memory/
│   ├── paging.c
│   └── kheap.c
├── interrupts/
│   └── idt.c
├── drivers/
│   └── disk.c
├── boot/
│   └── bootloader.asm     # Optional bootloader code
```

## Build Requirements

* GCC cross-compiler for i386
* NASM assembler
* QEMU or Bochs for emulation
* Make

## Building and Running

```bash
make clean
make all
qemu-system-i386 -hda ./bin/os.bin
```

This assumes a valid `Makefile` and that `os.bin` is a bootable binary image.

## Development Status

The project is at an early stage. Current components include:

* Basic terminal output
* IDT and paging setup
* Kernel heap
* Disk interface stubs

Planned features:

* Filesystem support
* Keyboard input and interrupt handling
* Syscalls and user-mode support
* Multitasking
