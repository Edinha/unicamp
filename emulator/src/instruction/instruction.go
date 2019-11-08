package instruction

import (
	"fmt"
	"cpu"
	"memory"
)

func Run(mem *memory.Memory) {
	cpu := cpu.CPU{}
	cpu.PC = getResetPos(mem)

	for ;; {
		opcode := mem.Read(cpu.PC)
		inst := getOperation(opcode)

		inst(&cpu, mem)
		log(&cpu)
	}
}

func getResetPos(mem *memory.Memory) (uint16) {
	low := uint16(mem.Read(0xFFFC))
	high := uint16(mem.Read(0xFFFD))
	return (high << 8) + low
}

func log(cpu *cpu.CPU) {
	fmt.Printf("PC:%X A:%X X:%X Y:%X P:%X SP:%X CYC:%d\n", cpu.PC, cpu.A, cpu.X, cpu.Y, cpu.Status.Value(), cpu.SP, cpu.Cycles)
}

func getOperation(opcode byte) (func(*cpu.CPU, *memory.Memory)) {
	// TODO ARRAY WITH ALL

	return func(*cpu.CPU, *memory.Memory) {
		return
	}
}