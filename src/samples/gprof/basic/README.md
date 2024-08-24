Sample program to show how to use the `gprof` feature.

The requiremnts are quite easy, just adding `-g -pg` flags to the `CFLAGS` and `LDFLAGS` is enough to make things to work out of the box.

Firstly execute your program, then once program ends it will automatically generates a `gmon.out` file at CWD level.

In order to inspect the content of the generated file you need to use the `psp-gprof` binary.

For instance, following the next syntax:
```
psp-gprof -b {binary.elf} gmon.out
```

like:
```
psp-gprof -b gprofbasic.elf gmon.out
```


It will show something like:
```
Flat profile:

Each sample counts as 0.001 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 95.98      0.17     0.17   104728     0.00     0.00  is_prime
  4.02      0.17     0.01        1     7.00     7.00  dummy_function
  0.00      0.17     0.00        1     0.00   174.00  main
  0.00      0.17     0.00        1     0.00   167.00  sum_of_square_roots


                        Call graph


granularity: each sample hit covers 2 byte(s) for 0.57% of 0.17 seconds

index % time    self  children    called     name
                0.00    0.17       1/1           _main [2]
[1]    100.0    0.00    0.17       1         main [1]
                0.00    0.17       1/1           sum_of_square_roots [4]
                0.01    0.00       1/1           dummy_function [5]
-----------------------------------------------
                                                 <spontaneous>
[2]    100.0    0.00    0.17                 _main [2]
                0.00    0.17       1/1           main [1]
-----------------------------------------------
                0.17    0.00  104728/104728      sum_of_square_roots [4]
[3]     96.0    0.17    0.00  104728         is_prime [3]
-----------------------------------------------
                0.00    0.17       1/1           main [1]
[4]     96.0    0.00    0.17       1         sum_of_square_roots [4]
                0.17    0.00  104728/104728      is_prime [3]
-----------------------------------------------
                0.01    0.00       1/1           main [1]
[5]      4.0    0.01    0.00       1         dummy_function [5]
-----------------------------------------------


Index by function name

   [5] dummy_function          [1] main
   [3] is_prime                [4] sum_of_square_roots
```

Cheers