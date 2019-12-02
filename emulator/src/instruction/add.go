package instruction

import (
	"cpu"
	"memory"
)

func AddInstructions() ([]Instruction) {
	return []Instruction {
		AddInstructionImmediateAddr(),
		AddInstructionZeroPageAddr(),
	}
}

func overflow(src byte, register byte, temp int) (bool) {
	return false
    // return (!(register ^ src) & 0x80) && ((register ^ temp) & 0x80 != 0)
}

func AddInstructionBase(params []byte, cpu *cpu.CPU, memory *memory.Memory, mode AddressingMode) {
	_, value := mode.Resolve(params, cpu, memory)

	carry := cpu.Status.CarryAdd()
	old_value := cpu.A

	new_calculated_value := int(cpu.A + value + carry)
	cpu.A = byte(new_calculated_value % 256)

	cpu.Status.Zero = (cpu.A == 0)
	cpu.Status.Carry = (new_calculated_value > 255)
	cpu.Status.Negative = (cpu.A > 127)
	cpu.Status.Overflow = overflow(value, old_value, new_calculated_value)
}

func AddInstructionImmediateAddr() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		AddInstructionBase(params, cpu, memory, Immediate())
	}

	return Instruction { 0x69, 2, 1, execute }
}

func AddInstructionZeroPageAddr() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		AddInstructionBase(params, cpu, memory, ZeroPage())
	}

	return Instruction { 0x65, 3, 1, execute }
}


func AddInstructionZeroPgDirectIndexedRegXAddr(cpu *cpu.CPU, mem *memory.Memory) {

}


func AddInstructionAbsoluteAddr(cpu *cpu.CPU, mem *memory.Memory) {

}


func AddInstructionAbsDirectIndexedRegXAddr(cpu *cpu.CPU, mem *memory.Memory) {

}


func AddInstructionAbsDirectIndexedRegYAddr(cpu *cpu.CPU, mem *memory.Memory) {

}


func AddInstructionIndirectPreIndexedAddr(cpu *cpu.CPU, mem *memory.Memory) {

}


func AddInstructionIndirectPostIndexedAddr(cpu *cpu.CPU, mem *memory.Memory) {

}
