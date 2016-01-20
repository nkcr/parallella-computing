This program aims to compute machin-like approximation of pi and measure
performance between host only implementation and host with epiphany implementation.

#### Running

This example only uses host and epiphany. To print csv data, provide `-D STAT`.

to run

```
./build.sh && ./main.elf
```

It is possible to passes as arguments the main number of iteration and the sub
number of iterations :

```
./main.elf [main number] [sub number]
```

Expected output :

```
PI = 3.141584	time spent 7.880000s
```

With stat option (gcc with `-D STAT`) :

```
10000,  1000, 7.880000, 3.1415
```

#### Stats

A bash script is provided and aims to outputs performance stats as csv files. Be sure first to enable csv output in the main script (with `-D STAT`).

The first script (stats.sh) takes no parameter and produces data in rows :

`./stats.sh`

And will produce output `stats.csv`.

#### Tips

Tips to run on different screen, type `screen` to start a new session. Then
leave it with `CTRL-A CTRL-D`, come back with `screen -r`.
That step is useful to launch stats from ssh without ending it on leaving ssh
session.
