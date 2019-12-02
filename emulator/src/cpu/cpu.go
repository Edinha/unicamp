package cpu

type Flag struct {
	Negative bool
	Overflow bool
	Unused bool
	Brk bool
	Decimal bool
	Interrupt bool
	Zero bool
	Carry bool
}

type CPU struct {
	A byte
	X byte
	Y byte
	SP byte
	PC uint16
	Cycles uint16
	Status Flag
}

func (status Flag) Init(value uint16) {

}

func (status Flag) CarryAdd() (byte) {
	if status.Carry {
		return 1
	}

	return 0
}

func (status Flag) Value() (byte) {
	flags := []bool {status.Carry, status.Zero, status.Interrupt, status.Decimal, status.Brk, status.Unused, status.Overflow, status.Negative}

	value := 0
	for i := 0; i < len(flags); i++ {
		if flags[i] {
			value += 1 << i
		}
	}

	return byte(value)
}