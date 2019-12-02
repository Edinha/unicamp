package cartridge

type Cartridge struct {
	chrRom []byte
	prgRom []byte
}

func New(data []byte) (*Cartridge) {
	header := data[:0x10]
	rom_banks := header[4]
	//vrom_banks := header[5]

	rom := data[0x10:]
	rom_end := 0x4000 * int(rom_banks)

	// var cartridge Cartridge
	// cartridge.prgRom = rom[:rom_end]
	//print("DATA: ", vrom_banks, "  ", rom_banks, " len ", len(rom))
	//print("\nCOMPARE: ", len(rom), "  ", rom_end + int(vrom_banks) * 0x2000)
	// cartridge.chrRom = rom[rom_end:(rom_end + int(vrom_banks) * 0x2000)]

	return &Cartridge{ rom, rom[:rom_end] }
}

func (c *Cartridge) PRGROM() ([] byte) {
	return c.prgRom
}

func (c *Cartridge) CHRROM() ([] byte) {
	return c.chrRom
}