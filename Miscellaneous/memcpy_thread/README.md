A simple test case to see if concurrent memcpy can lead to a deadlock.

To run :

```
gcc -pthread main.c -o main.elf && ./main.elf
```
