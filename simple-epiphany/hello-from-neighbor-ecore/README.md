Each core saves it's id in it's local memory. Then it writes a ready status, waits for it's neighbor to be ready, then read it's
neighbor id. Finally writes the result in shared memory. The host then prints the result. 

Uses `e_write` and `e_read` to perform data transfert.

to run :
```
./build.sh && ./main.elf
```

expected outcome :

```
The result is 0x0001
The result is 0x0002
The result is 0x0003
The result is 0x0004
The result is 0x0005
The result is 0x0006
The result is 0x0007
The result is 0x0008
The result is 0x0009
The result is 0x000a
The result is 0x000b
The result is 0x000c
The result is 0x000d
The result is 0x000e
The result is 0x000f
The result is 0x0000
```
