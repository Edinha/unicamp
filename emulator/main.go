package main

import (
	"fmt"
	"flag"
	"memory"
	"io/ioutil"
	"cartridge"
	"instruction"
)

func readRom() ([]byte) {
	fptr := flag.String("fpath", "test.txt", "file path to read from")
	flag.Parse()

	data, err := ioutil.ReadFile(*fptr)
    if err != nil {
        fmt.Println("File reading error", err)
        return []byte {}
	}

	return data
}

func main() {
	bytes := readRom()
	fmt.Println("BYTES: ", len(bytes))

	c := cartridge.New(bytes)
	fmt.Printf("ROM BYTES: 0x%X 0x%X \n", len(c.PRGROM()), len(c.CHRROM()))

	mem := memory.New(c)
	fmt.Printf("MEMORY INFO: %X %X \n", mem.Read(0x8000), mem.Read(0xC000))

	instruction.Run(mem)
}