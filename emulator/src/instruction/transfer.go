package instruction

import (
	"cpu"
	"memory"
)

func TransferInstructions() ([]Instruction) {
	return []Instruction {
		TXAInstruction(),
		TYAInstruction(),
		TSXInstruction(),
		TXSInstruction(),
		TAXInstruction(),
		TAYInstruction(),
	}
}

func TXAInstruction() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		value := cpu.X
		cpu.A = value

		cpu.Status.Zero = (value == 0)
		cpu.Status.Negative = (value > 127)
	}

	return Instruction { 0x8A, 2, 0, execute }
}

func TYAInstruction() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		value := cpu.Y
		cpu.A = value

		cpu.Status.Zero = (value == 0)
		cpu.Status.Negative = (value > 127)
	}

	return Instruction { 0x98, 2, 0, execute }
}

func TSXInstruction() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		cpu.X = cpu.SP
	}

	return Instruction { 0xBA, 2, 0, execute }
}

func TXSInstruction() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		cpu.SP = cpu.X
	}

	return Instruction { 0x9A, 2, 0, execute }
}

func TAXInstruction() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		value := cpu.A
		cpu.X = value

		cpu.Status.Zero = (value == 0)
		cpu.Status.Negative = (value > 127)
	}

	return Instruction { 0xAA, 2, 0, execute }
}

func TAYInstruction() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		value := cpu.A
		cpu.Y = value

		cpu.Status.Zero = (value == 0)
		cpu.Status.Negative = (value > 127)
	}

	return Instruction { 0xA8, 2, 0, execute }
}
