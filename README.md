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

## Build Requirements

* GCC cross-compiler for i386
* NASM assembler
* QEMU or Bochs for emulation
* Make

## Building

```bash
make clean
make all
```

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
