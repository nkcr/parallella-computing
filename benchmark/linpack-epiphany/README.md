run with

```
cc -DSP -DROLL -O4 clinpack.c -lm && ./a.out
```

-DDP for double precision  
-DUNROLL to unroll (faster)


http://www.netlib.org/utk/people/JackDongarra/faq-linpack.html#_Toc27885709

**Profiling with gprof**

To profile, compile with `-pg` option and chage `-04` to `-0s`. It will output
a file `gmon.out`. Convert that file to statistics with `gprof clinpack.elf gmon.out`.
