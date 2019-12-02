package instruction

import (
	"cpu"
	"memory"
)

type AddressingMode struct {
	Resolve func(params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16, byte)
}

func fullAddress(params []byte) (uint16) {
	return uint16((params[1] << 8) + params[0])
}

func Immediate() (AddressingMode) {
	f := func (params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16, byte) {
		return uint16(params[0]), params[0]
	}

	return AddressingMode {	f }
}

func ZeroPage() (AddressingMode) {
	f := func (params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16, byte) {
		address := uint16(params[0])
		return address, mem.Read(address)
	}

	return AddressingMode {	f }
}

func AbsoluteAddr() (AddressingMode) {
	f := func (params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16, byte) {
		address := fullAddress(params)
		return address, mem.Read(address)
	}

	return AddressingMode {	f }
}

func ImpliedAddr() (AddressingMode) {
	f := func (params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16, byte) {
		return uint16(params[0]), params[0]
	}

	return AddressingMode {	f }
}

func AccumulatorAddr() (AddressingMode) {
	f := func (params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16, byte) {
		return uint16(params[0]), params[0]
	}

	return AddressingMode {	f }
}

func ZeroPgDirectIndexedRegXAddr() (AddressingMode) {
	f := func (params []byte, cpu *cpu.CPU, mem *memory.Memory) (uint16, byte) {
		return uint16(params[0]), params[0]
	}

	return AddressingMode {	f }
}

// ZeroPgDirectIndexedRegYAddr
// AbsDirectIndexedRegXAddr
// AbsDirectIndexedRegXAddrNoPageCross
// AbsDirectIndexedRegYAddr
// AbsDirectIndexedRegYAddrNoPageCross
// IndirectAddr
// IndirectPreIndexedAddr
// IndirectPostIndexedAddr
// IndirectPostIndexedAddrNoPageCross
// RelativeIndexedAddr