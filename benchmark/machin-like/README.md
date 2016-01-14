This program aims to compute machin-like approximation of pi and measure
performance between host only implementation and host with epiphany implementation.

This example only uses host. To print in a stat way, provide `-D STAT`.

to run

```
./build.sh && ./main.elf
```

It is possible to passes as arguments the main number of iteration and the sub
number of iteration :

```
./main.elf [main number] [sub number]
```

Expected output :

```
PI = 3.141584	time spent 7.880000s
```

With stat option :

```
(10000,1000,7.880000)
```

