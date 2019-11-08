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
		log(&cpu)

		opcode := mem.Read(cpu.PC)
		inst := getOperation(opcode)
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

func getOperation(opcode byte) (Instruction) {
	// TODO ARRAY WITH ALL

	return AddInstructionImmediateAddr()

	// return func(params []byte, *cpu.CPU, *memory.Memory) {
	// 	return
	// }
}