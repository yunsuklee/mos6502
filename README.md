# MOS6502 Emulator

A cycle-accurate educational emulator for the MOS 6502 processor, built to understand how CPUs work at a fundamental level.

## Features

- **Complete 6502 instruction set** - All 56 official instructions with accurate cycle timing
- **Multiple addressing modes** - Immediate, absolute, zero page, indexed, and indirect variants
- **Memory-mapped I/O** - Character output and program halt capabilities
- **Minimal test suite** - Cover core functionality and provide a runnable example

## Quick Start

```bash
# Build the emulator
make

# Run the Hello World example
./bin/mos6502 examples/hello.rom

# Run tests
make test
```

## Building and Running

**Prerequisites:** GCC, Make

```bash
git clone <repository>
cd mos6502
make
./bin/mos6502 examples/hello.rom
```

**Output:**
```
Starting MOS 6502 emulation...
ROM file: examples/hello.rom
Execution mode: Run until program halts

Hello, World!
Program requested halt (exit code: 0)
Execution completed!
```

## CLI Usage

```bash
./bin/mos6502 <rom_file> [options]

Options:
  -cycles <count>      Stop after specified CPU cycles
  -halt <address>      Stop at hexadecimal address (e.g. 8010)
  -log <file>          Log CPU state (default: logs/log.txt)
  -nolog               Disable logging

# Examples
./bin/mos6502 examples/hello.rom           # Run until program halts
./bin/mos6502 game.rom -cycles 1000        # Run for 1000 cycles
./bin/mos6502 debug.rom -halt 8010 -nolog  # Stop at address $8010 without logging
```

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make` or `make all` | Build the emulator executable |
| `make test` | Run the complete test suite |
| `make clean` | Clean build artifacts |

## Programming the Emulator

### Memory Map
- `$0000-$FFFF` - 64K RAM
- `$E000` - Character output port (write ASCII to print)
- `$E001` - Halt port (write any value to exit with code)

## Testing Strategy

Aims to provide a minimal but effective test suite to cover:

- **CPU Core** - Creation, reset, memory access
- **Status Flags** - All flag operations and edge cases  
- **Instructions** - Critical operations (LDA, STA, ADC, SBC)
- **Addressing** - Key addressing modes with boundary conditions
- **Memory-Mapped I/O** - Character output and halt functionality

## Project Structure

```
src/core/           # Core emulator components
├── cpu.c/h         # CPU state and execution loop
├── instructions.c/h # All 56 6502 instructions  
├── addressing.c/h   # 12 addressing modes
├── opcodes.c/h      # Opcode → function mapping
└── status.c/h       # Status register operations

tests/              # Test framework and test cases
examples/           # Sample ROM programs
```

## Educational Goals

This project demonstrates:
- CPU instruction fetch/decode/execute cycles
- Memory management and addressing schemes
- Flag register operations and arithmetic
- I/O through memory-mapped ports
- Cycle-accurate timing simulation

Perfect for understanding computer architecture fundamentals!

## License

Educational use - see source code for implementation details!
