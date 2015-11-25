The host sets two shared buffer, each containing an array of 200 float.  
The eCore are then launched separately. They read the shared buffer and compute a result to a result buffer.

to run :
`./build.sh && ./main.elf`

expected outcome :

```
Status of shared_matrix1 writing: 800
Status of shared_matrix2 writing: 800
Result from core n°00 is 0.000000
Result from core n°01 is 2.100000
Result from core n°02 is 4.200000
Result from core n°03 is 6.300000
Result from core n°04 is 8.400000
Result from core n°05 is 10.500000
Result from core n°06 is 12.600000
Result from core n°07 is 14.700000
Result from core n°08 is 16.799999
Result from core n°09 is 18.900000
Result from core n°10 is 21.000000
Result from core n°11 is 23.100000
Result from core n°12 is 25.200001
Result from core n°13 is 27.299999
Result from core n°14 is 29.400000
Result from core n°15 is 31.500000
```
