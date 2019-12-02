package memory

import (
	"cartridge"
)

const ROM_ADDR = 0x8000
const MEMORY_SIZE = 0xFFFF + 1

type Memory struct {
	data [MEMORY_SIZE]byte
	banks uint16
}

func New(c *cartridge.Cartridge) (*Memory) {
	rom := c.PRGROM()

	data := [MEMORY_SIZE]byte {}
	for i := 0; i < len(rom); i++ {
		data[ROM_ADDR + i] = rom[i]
	}

	return &Memory{ data, uint16(len(rom) / 0x4000) }
}

func (memory *Memory) Read(address uint16) (byte) {
	return memory.data[memory.mirroring(address)]
}

func (memory *Memory) Write(address uint16, value byte) {
	addr := memory.mirroring(address)
	if addr >= ROM_ADDR {
		return
	}

	memory.data[addr] = value
}

func (memory *Memory) mirroring(addr uint16) (uint16) {
	if addr <= 0x2000 {
		return addr % 0x0800
	}

	if addr >= 0xC000 {
		return ROM_ADDR + ((memory.banks - 1) * 0x4000 + (addr - 0xC000))
	}

	return addr
}