package main

import (
	"fmt"
	"flag"
	"io/ioutil"
	"cartridge"
)

func read_rom() ([]byte) {
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
	bytes := read_rom()
	fmt.Println("BYTES: ", len(bytes))

	c := cartridge.New(bytes)
	fmt.Println("ROM BYTES: ", len(c.PRG_ROM()), len(c.CHR_ROM()))
}