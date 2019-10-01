#!/bin/bash
gcc cliente.c -o cliente
for i in {0..10}
do
konsole -e ./cliente 127.0.0.1 22217 &
done
