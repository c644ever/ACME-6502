# ACME 6502 Breadboard Computer

## The Ultimate 8-Bit Learning Journey

**ACME 6502** is not just another breadboard computer - it's a comprehensive educational system that teaches computer architecture from the ground up. Our unique approach combines vintage computing with modern development methods.

### Revolutionary Features
- **FRAM-based address decoding** - Programmable hardware logic instead of fixed 74-series chips
- **Serial EEPROM mass storage** - I²C-based file system for program storage
- **CLI-only development** - Authentic 1980s development experience on Raspberry Pi
- **Progressive learning path** - From basic electronics to complex computer architecture

### The Ultimate Vision
While ambitious, our goal is to build a 6502 system so advanced it could theoretically run a simplified UNIX-like operating system, featuring:
- Dynamic memory management with bank switching
- File system with serial EEPROM storage
- Multi-tasking capabilities through interrupt handling

### Learning Path
**Phase 1:** CLI & Electronics Foundation  
**Phase 2:** Arduino Control System  
**Phase 3:** 6502 Processor Integration  
**Phase 4:** EEPROM Address Logic & Memory  
**Phase 5:** Advanced System Software  
**Phase 6:** Innovative Applications

Software Toolchain Overview
Development Environment
    Raspberry Pi OS Lite - Minimal Linux for CLI-only development
    Arduino CLI - Command-line Arduino development without IDE
    CC65 - 6502 C compiler and assembler suite
    AVR-GCC - Cross-compiler for Arduino Mega programming
    AVRDUDE - Firmware uploader for AVR microcontrollers

Programming Languages & Tools
    C/C++ - Arduino sketches and system utilities
    6502 Assembly - Low-level system programming
    Bash - Automation scripts and toolchain management
    Git - Version control and project management
    Make - Build automation for cross-compilation

Communication & Monitoring
    Minicom/Picocom - Serial terminal for hardware communication
    Screen/Tmux - Terminal multiplexing for session management
    Vim/Nano - Text editors for code development
Specialized Tools
    Custom EEPROM Programmer - Our own Arduino-based ROM burner
    FRAM Configuration Tools - Utilities for programmable address decoding
    Serial EEPROM Manager - I²C mass storage system utilities
    Bus Monitor - Arduino-based bus analysis and debugging

Cross-Development Workflow

All development happens on the Pi Zero, targeting:
    Arduino Mega 2560 (AVR architecture)
    W65C02 (6502 architecture)

This toolchain provides a complete development environment while maintaining the authentic retro computing experience.


### Why ACME 6502?
This project bridges eras - using contemporary tools to master vintage technology while implementing forward-thinking concepts like programmable hardware and software-defined architecture. You're not just building a computer; you're understanding the fundamental principles that power all modern computing systems.

Acknowledgments

This project stands on the shoulders of giants. We are deeply grateful to:
The 6502 Pioneers - Chuck Peddle, Bill Mensch, and the MOS Technology team for creating the processor that powered the personal computing revolution.
The Commodore 64 Visionaries - Robert Russell, Robert Yannes, and the team at Commodore who created the most successful home computer in history.
Ben Eater - For his incredible 6502 breadboard computer tutorials that have inspired thousands to understand computer architecture at the deepest level.
The Arduino Team - Massimo Banzi, David Cuartielles, Tom Igoe, Gianluca Martino, and David Mellis for creating the platform that democratized microcontroller programming.
The Raspberry Pi Foundation - Eben Upton and the team for bringing affordable Linux computing to makers and educators worldwide.
The Retro Computing Community - For preserving knowledge, sharing passion, and keeping the 6502 ecosystem alive decades after its introduction.
Your innovations continue to inspire new generations to understand, build, and create. This project is our humble tribute to your legacy.

Start with a blinking LED, finish with architectural mastery.
If it works? We will see ...
