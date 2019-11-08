package cartridge

type Cartridge struct {
	chrRom []byte
	prgRom []byte
}

func New(data []byte) (*Cartridge) {
	header := data[:0x10]
	vrom_banks := header[5]

	rom := data[0x10:]

	var cartridge Cartridge
	cartridge.prgRom = rom[:0x4000]
	cartridge.chrRom = rom[0x4000:(0x4000 + int(vrom_banks) * 0x2000)]

	return &cartridge
}

func (c *Cartridge) PRGROM() ([] byte) {
	return c.prgRom
}

func (c *Cartridge) CHRROM() ([] byte) {
	return c.chrRom
}