run with

```
cc -DSP -DROLL -O4 clinpack.c -lm && ./a.out
```

-DDP for double precision  
-DUNROLL to unroll (faster)

Result :

```
norm. resid      resid           machep         x[0]-1        x[n-1]-1
  1.6        3.80277634e-05  1.19209290e-07 -1.38282776e-05 -7.51018524e-06
times are reported for matrices of order   100
 dgefa      dgesl      total       kflops     unit      ratio
times for array with leading dimension of  201
  0.01       0.00       0.01      68667       0.03       0.18
  0.00       0.00       0.00        inf       0.00       0.00
  0.01       0.00       0.01      68667       0.03       0.18
  0.01       0.00       0.01     114444       0.02       0.11
times for array with leading dimension of 200
  0.01       0.00       0.01      68667       0.03       0.18
  0.00       0.00       0.00        inf       0.00       0.00
  0.01       0.00       0.01      68667       0.03       0.18
  0.01       0.00       0.01     118391       0.02       0.10
Rolled Single  Precision 114444 Kflops ; 100 Reps
```


http://www.netlib.org/utk/people/JackDongarra/faq-linpack.html#_Toc27885709
