Each core computes it's number based on it's row/col and then saves the result to the shared memory (sdram). In the end,
the host will eventually iterate through results and prints the result.

to run :
`./build.sh && ./main.elf`

expected outcome :

```
Result from core n°00 is 0x0000
Result from core n°01 is 0x0001
Result from core n°02 is 0x0002
Result from core n°03 is 0x0003
Result from core n°04 is 0x0004
Result from core n°05 is 0x0005
Result from core n°06 is 0x0006
Result from core n°07 is 0x0007
Result from core n°08 is 0x0008
Result from core n°09 is 0x0009
Result from core n°10 is 0x000a
Result from core n°11 is 0x000b
Result from core n°12 is 0x000c
Result from core n°13 is 0x000d
Result from core n°14 is 0x000e
Result from core n°15 is 0x000f
```
