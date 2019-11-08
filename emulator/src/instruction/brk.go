package instruction

import (
	"os"
	"cpu"
	"memory"
)

func BrkInstructions() []Instruction {
	return []Instruction { BrkInstruction() }
}

func BrkInstruction() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		os.Exit(0)
	}

	return Instruction{ 0x00, 0, 0, execute }
}