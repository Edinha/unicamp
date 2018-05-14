arm-none-eabi-linux-as -o mounted $1
arm-none-eabi-linux-ld -o compiled mounted
armsim -l compiled -d devices.txt
