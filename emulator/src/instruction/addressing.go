package instruction

import (
	"cpu"
	"memory"
)

type AddressingMode struct {
	Resolve func(params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16)
}

func Immediate() (AddressingMode) {
	f := func (params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16) {
		return uint16(params[0])
	}

	return AddressingMode {	f }
}