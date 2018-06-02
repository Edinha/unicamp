arm-none-eabi-linux-as -o mounted $1
arm-none-eabi-linux-ld -o compiled mounted
armsim -c -l compiled -d devices.txt
