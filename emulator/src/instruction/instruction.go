package instruction

import (
	"cpu"
	"memory"
)

type Instruction struct {
	opcode byte
	cycles byte
	paramsCount byte
	Execute func([]byte, *cpu.CPU, *memory.Memory)
}

func (i Instruction) Info() (byte, byte, byte) {
	return i.opcode, i.cycles, i.paramsCount
}