More advance example about how to use the `gprof` feature.

The requiremnts are quite easy, just adding `-g -pg` flags to the `CFLAGS` and `LDFLAGS` is enough to make things to work out of the box.

This example shows how to enable profiling just around some specific piece of code.
How `gprof` by default start profiling from the very beginning of the app we must discard that result, this is why we do `gprof_stop(NULL, false);`.
Then we just need to call `gprof_start();` whenever we want to start meassuring our piece of code and `gprof_stop("gmon_custom.out", true);` whenver we want to stop the profiling.

Firstly execute your program, then once program ends it will automatically generates the output with the given names.

In order to inspect the content of the generated file you need to use the `psp-gprof` binary.

For instance, following the next syntax:
```
psp-gprof -b {binary.elf} {gmon_custom.out}
```
like:
```
psp-gprof -b gprofcustom.elf gmon_custom.out
```

Output in this example:
```
Flat profile:

Each sample counts as 0.001 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 89.78      5.60     5.60        1     5.60     5.60  heavy_operation_3
 10.22      6.24     0.64        1     0.64     0.64  heavy_operation_2


                        Call graph


granularity: each sample hit covers 2 byte(s) for 0.02% of 6.24 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00    6.24                 main [1]
                5.60    0.00       1/1           heavy_operation_3 [2]
                0.64    0.00       1/1           heavy_operation_2 [3]
-----------------------------------------------
                5.60    0.00       1/1           main [1]
[2]     89.8    5.60    0.00       1         heavy_operation_3 [2]
-----------------------------------------------
                0.64    0.00       1/1           main [1]
[3]     10.2    0.64    0.00       1         heavy_operation_2 [3]
-----------------------------------------------


Index by function name

   [3] heavy_operation_2       [2] heavy_operation_3
```

Cheers.