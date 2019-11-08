package instruction

import (
	"fmt"
	"cpu"
	"memory"
)

var instructions [256]Instruction

func init() {
	instructions = AllInstructions()
}

func Run(mem *memory.Memory) {
	cpu := cpu.CPU{}
	cpu.PC = getResetPos(mem)

	for ;; {
		log(&cpu)

		opcode := mem.Read(cpu.PC)
		inst := getInstruction(opcode)
		_, cycles, count := inst.Info()

		var params []byte
		for i := 0; i < int(count); i++ {
			cpu.PC++
			params = append(params, mem.Read(cpu.PC))
		}

		inst.Execute(params, &cpu, mem)

		cpu.PC++
		cpu.Cycles += uint16(cycles)
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

func AllInstructions() ([256]Instruction) {
	all := []Instruction {}
	all = append(all, AddInstructions()...)
	all = append(all, BrkInstructions()...)

	result := [256] Instruction {}
	for i := 0; i < len(all); i++ {
		inst := all[i]
		_, opcode, _ := inst.Info()
		result[opcode] = inst
	}

	return result
}

func getInstruction(opcode byte) (Instruction) {
	return instructions[opcode]
}