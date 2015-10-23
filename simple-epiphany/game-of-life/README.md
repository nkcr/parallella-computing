Each core acts as an autonomous cell in Conway's game of life. The program doesn't show every changes since each core are autonomous. It simply repeatedly prints the state a fixed number of time.

to run :
```
./build.sh && ./main.elf
```

The expected outcome may differ every time! Here is an example :

```
X	X	X	X	X	X
X	O	X	X	O	X	
X	O	O	O	O	X	
X	O	O	O	X	X	
X	O	X	O	O	X	
X	X	X	X	X	X

X	X	X	X	X	X
X	O	X	X	O	X	
X	X	O	O	O	X	
X	O	O	O	X	X	
X	O	X	O	O	X	
X	X	X	X	X	X

X	X	X	X	X	X
X	O	O	O	O	X	
X	O	O	X	O	X	
X	X	O	X	O	X	
X	O	O	O	O	X	
X	X	X	X	X	X
```
