package instruction

import (
	"cpu"
	"memory"
)

func LoadInstructions() ([]Instruction) {
	return []Instruction {
		LDXImmediate(),
		LDXZeroPage(),
		LDAImmediate(),
		LDAZeroPage(),
	}
}

func LDXBaseInstruction(value byte, cpu *cpu.CPU) {
	cpu.X = value
	cpu.Status.Zero = (value == 0)
	cpu.Status.Negative = (value > 127)
}

func LDABaseInstruction(value byte, cpu *cpu.CPU) {
	cpu.A = value
	cpu.Status.Zero = (value == 0)
	cpu.Status.Negative = (value > 127)
}

func LDXImmediate() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		_, value := Immediate().Resolve(params, cpu, memory)
		LDXBaseInstruction(value, cpu)
	}

	return Instruction { 0xA2, 2, 1, execute }
}

func LDXZeroPage() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		_, value := ZeroPage().Resolve(params, cpu, memory)
		LDXBaseInstruction(value, cpu)
	}

	return Instruction { 0xA6, 3, 1, execute }
}

func LDAImmediate() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		_, value := Immediate().Resolve(params, cpu, memory)
		LDABaseInstruction(value, cpu)
	}

	return Instruction { 0xA9, 2, 1, execute }
}

func LDAZeroPage() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		_, value := ZeroPage().Resolve(params, cpu, memory)
		LDABaseInstruction(value, cpu)
	}

	return Instruction { 0xA5, 3, 1, execute }
}
