package cartridge

struct Cartridge {
	chr_rom []byte
	prg_rom []byte
}

func New(data []byte) (Cartridge*) {
	header := data[:0x10]
	vrom_banks := header[5]

	rom := data[0x10:]

	var cartridge Cartridge
	cartridge.prg_rom = rom[:0x4000]
	cartridge.chr_rom = rom[0x4000:(0x4000 + vrom_banks * 0x2000)]

	return &cartridge
}

func (c Cartridge*) get_prg_rom() ([] byte) {
	return c.prg_rom
}

func (c Cartridge*) get_chr_rom() ([] byte) {
	return c.chr_rom
}