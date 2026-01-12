Sample program to show how to use the `gprof` feature with C++.

The requirements are quite easy, just adding `-g -pg` flags to the `CFLAGS` and `LDFLAGS` is enough to make things work out of the box. For C++ programs, you also need to link with `-lstdc++`.

This example demonstrates:
- Object-oriented programming with a `PrimeCalculator` class
- C++ standard library features (`std::vector`, `std::cout`)
- Profiling C++ code with gprof

Firstly execute your program, then once program ends it will automatically generate a `gmon.out` file at CWD level.

In order to inspect the content of the generated file you need to use the `psp-gprof` binary.

For instance, following the next syntax:
```
psp-gprof -b {binary.elf} gmon.out
```

like:
```
psp-gprof -b gprofbasic_cpp.elf gmon.out
```


It will show something like:
```
Flat profile:

Each sample counts as 0.001 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 95.98      0.17     0.17   104728     0.00     0.00  PrimeCalculator::isPrime(int) const
  4.02      0.17     0.01        1     7.00     7.00  dummyFunction()
  0.00      0.17     0.00        1     0.00   174.00  main
  0.00      0.17     0.00        1     0.00   167.00  PrimeCalculator::sumOfSquareRoots(int) const


                        Call graph


granularity: each sample hit covers 2 byte(s) for 0.57% of 0.17 seconds

index % time    self  children    called     name
                0.00    0.17       1/1           _main [2]
[1]    100.0    0.00    0.17       1         main [1]
                0.00    0.17       1/1           PrimeCalculator::sumOfSquareRoots(int) const [4]
                0.01    0.00       1/1           dummyFunction() [5]
-----------------------------------------------
                                                 <spontaneous>
[2]    100.0    0.00    0.17                 _main [2]
                0.00    0.17       1/1           main [1]
-----------------------------------------------
                0.17    0.00  104728/104728      PrimeCalculator::sumOfSquareRoots(int) const [4]
[3]     96.0    0.17    0.00  104728         PrimeCalculator::isPrime(int) const [3]
-----------------------------------------------
                0.00    0.17       1/1           main [1]
[4]     96.0    0.00    0.17       1         PrimeCalculator::sumOfSquareRoots(int) const [4]
                0.17    0.00  104728/104728      PrimeCalculator::isPrime(int) const [3]
-----------------------------------------------
                0.01    0.00       1/1           main [1]
[5]      4.0    0.01    0.00       1         dummyFunction() [5]
-----------------------------------------------


Index by function name

   [5] dummyFunction()          [1] main
   [3] PrimeCalculator::isPrime(int) const
   [4] PrimeCalculator::sumOfSquareRoots(int) const
```

Cheers
