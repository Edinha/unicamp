package cpu

type Flag struct {
	negative bool
	overflow bool
	unused bool
	brk bool
	decimal bool
	interrupt bool
	zero bool
	carry bool
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

func (status Flag) Value() (byte) {
	return 0
}