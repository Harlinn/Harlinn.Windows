```
Run on (20 X 1996 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1024 KiB (x10)
  L3 Unified 16384 KiB (x2)
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
BenchmarkStdWStringDefaultConstructor       1.66 ns         1.64 ns    448000000
BenchmarkWideStringDefaultConstructor       1.66 ns         1.67 ns    448000000
BenchmarkStdWStringCStringConstructor       21.8 ns         22.0 ns     32000000
BenchmarkWideStringCStringConstructor       15.0 ns         15.1 ns     49777778
BenchmarkStdWStringAppendChar                145 ns          143 ns      4480000
BenchmarkWideStringAppendChar                210 ns          213 ns      3446154
BenchmarkStdWStringCopy                     3065 ns         3115 ns       235789
BenchmarkWideStringCopy                      974 ns          952 ns       640000
BenchmarkStdWStringArgCopyReturn            23.6 ns         24.1 ns     29866667
BenchmarkWideStringArgCopyReturn            9.19 ns         9.21 ns     74666667
BenchmarkStdWStringArgCopyReturn2           32.2 ns         32.1 ns     22400000
BenchmarkWideStringArgCopyReturn2           18.1 ns         18.0 ns     37333333
BenchmarkStdWStringArgCopyReturn3           3029 ns         2982 ns       235789
BenchmarkWideStringArgCopyReturn3           1835 ns         1842 ns       373333
```