A simple test case to see if concurrent e_read can lead to a deadlock.

To run :

```
gcc main.c -o main.elf -O4 -L $EPIPHANY_HOME/tools/host/lib
-I $EPIPHANY_HOME/tools/host/include -le-hal -le-loader -lpthread && ./main.elf
```
