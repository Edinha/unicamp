package instruction

import (
	"fmt"
	"cpu"
	"memory"
)

func AddInstructionImmediateAddr() (Instruction) {
	execute := func(params []byte, cpu *cpu.CPU, memory *memory.Memory) {
		address := Immediate().Resolve(params, cpu, memory)
		fmt.Println("ADDRESS: ", address)
	}

	return Instruction { 0x69, 2, 1, execute }
}

func AddInstructionZeroPageAddr(cpu *cpu.CPU, mem *memory.Memory) {

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
