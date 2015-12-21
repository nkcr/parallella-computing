That file is a first attempt to run the benchmark using the epiphany. The
method `dmxpy` actually implements computation using eCores, without setting
any results. That chage does not increase the flops result. After profilling the
code, method `dmxpy` is not important enought to influence the performance result.
Another test will be created to optimize the most used method. That test is leaving
in this state to provide an example of how to involve eCores in the process.


run with

```
cc -DSP -DROLL -O4 clinpack.c -lm && ./a.out
```

-DDP for double precision  
-DUNROLL to unroll (faster)

Outcome:

```
Rolled Single Precision Linpack

Rolled Single Precision Linpack

[info] Status of sharedy writing: 800
[info] Status of sharedx writing: 800
[info] Status of sharedm writing: 160800
     norm. resid      resid           machep         x[0]-1        x[n-1]-1
  1200511.9        2.86035442e+01  1.19209290e-07 -1.38282776e-05 -7.51018524e-06
    times are reported for matrices of order   100
      dgefa      dgesl      total       kflops     unit      ratio
 times for array with leading dimension of  201
       0.01       0.00       0.01      68667       0.03       0.18
       0.00       0.00       0.00        inf       0.00       0.00
       0.01       0.00       0.01      68667       0.03       0.18
       0.01       0.00       0.01     112568       0.02       0.11
 times for array with leading dimension of 200
       0.00       0.00       0.00        inf       0.00       0.00
       0.01       0.00       0.01      68666       0.03       0.18
       0.00       0.00       0.00        inf       0.00       0.00
       0.01       0.00       0.01     112568       0.02       0.11
Rolled Single  Precision 112568 Kflops ; 100 Reps
```

http://www.netlib.org/utk/people/JackDongarra/faq-linpack.html#_Toc27885709

**Profiling with gprof**

To profile, compile with `-pg` option and change `-04` to `-0s`. It will output
a file `gmon.out`. Convert that file to statistics with `gprof clinpack.elf gmon.out`.

**Profiling each line with gcov**

Add `-fprofile-arcs -ftest-coverage` as compilation params and change `-04` to `-0s.
Compile and run. Then run `gcov clinpack.c` the file `clinpack.c.gcov` is generated.
That file contains number of executions of each lines.

**Error putting it directly on the epiphany**
```
parallella@parallella:~/parallella-computing/benchmark$ ./build.sh/opt/adapteva/
esdk.2015.1/tools/e-gnu.armv7l/bin/../lib/gcc/epiphany-elf/4.8.2/../../../../
epiphany-elf/bin/ld: clinpack.elf section `.bss' will not fit in region `INTERNAL_RAM'
opt/adapteva/esdk.2015.1/tools/e-gnu.armv7l/bin/../lib/gcc/epiphany-elf/4.8.2/
../../../../epiphany-elf/bin/ld: region `INTERNAL_RAM' overflowed by 318544 bytes
```
