# Benchmark Results for BasicString

The benchmark results showcases both benefits and drawbacks of using `WideString`, the 
specialization of the `BasicString` template for `wchar_t`,  compared to the standard 
`std::wstring` implementation:

- **Construction**: Default construction of `WideString` is comparable to `std::wstring`, and 
  for C-string construction, `WideString` outperforms `std::wstring`.
- **Append Operations**: `WideString` shows mixed results in append operations. It is 
  generally slower than `std::wstring` for single character appends, but it performs 
  better for appending C-style strings.
- **Copy Operations**: `WideString` excels in copy and move operations, as can be 
  expected from a reference counted string implementation.
- **Argument Passing**: `WideString` consistently outperforms `std::wstring` in argument passing scenarios, 
  especially when returning by value. Verifying that `WideString` is more efficient in function calls.
- **Substring**: `WideString` is faster than `std::wstring` for substring extraction.
- **Comparison**: `WideString` is faster in equality checks when compared against itself, and 
  performs comparable to `std::wstring` when comparing against other strings.
- **Formatting**: `std::wstring` is generally faster in formatting operations, but not always.
- **Find Operations**: `WideString` performs comparable to `std::wstring` for find operations.
- **Case Conversion**: `WideString` implements `WideString ToUpper()`, a convenience method for converting 
  strings to uppercase, which performs well.
  - `BenchmarkWideStringToUpper1A` is implemented using `WideString::ToUpper()`.
  - `BenchmarkStdWStringToUpper1` and `BenchmarkWideStringToUpper1B` are implemented 
	using `std::towupper` in a loop.

While definitely not an exhaustive benchmark suite, the results shows that `BasicString` 
is a good alternative to `std::basic_string`, particularly when passing strings as function 
arguments and returning them by value. 

This is the primary use case for `BasicString` in the Harlinn.Common.Core, Harlinn.Windows, 
Harlinn.ODBC, Harlinn.OCI and Harlinn.OCI libraries.

```
2026-01-13T15:25:31+01:00
Running BasicStringBenchmarks.exe
Run on (20 X 1996 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1024 KiB (x10)
  L3 Unified 16384 KiB (x2)
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
BenchmarkStdWStringDefaultConstructor       1.66 ns         1.65 ns    407272727
BenchmarkWideStringDefaultConstructor       1.64 ns         1.65 ns    407272727
BenchmarkStdWStringCStringConstructor       23.0 ns         23.0 ns     29866667
BenchmarkWideStringCStringConstructor       14.9 ns         14.6 ns     44800000
BenchmarkStdWStringAppendChar1               145 ns          144 ns      4977778
BenchmarkWideStringAppendChar1               190 ns          188 ns      3733333
BenchmarkStdWStringAppendChar2              22.7 ns         22.9 ns     32000000
BenchmarkWideStringAppendChar2              23.9 ns         24.0 ns     28000000
BenchmarkStdWStringAppendString1            46.9 ns         47.1 ns     14933333
BenchmarkWideStringAppendString1            25.6 ns         25.1 ns     28000000
BenchmarkStdWStringCopy                     3012 ns         3048 ns       235789
BenchmarkWideStringCopy                      959 ns          952 ns       640000
BenchmarkStdWStringArgCopyReturn            23.6 ns         23.5 ns     29866667
BenchmarkWideStringArgCopyReturn            9.11 ns         9.21 ns     74666667
BenchmarkStdWStringArgCopyReturn2           32.1 ns         32.2 ns     21333333
BenchmarkWideStringArgCopyReturn2           18.0 ns         18.0 ns     40727273
BenchmarkStdWStringArgCopyReturn3           2943 ns         2888 ns       248889
BenchmarkWideStringArgCopyReturn3           1845 ns         1842 ns       373333
BenchmarkStdWStringArgCopyReturn4           31.9 ns         32.1 ns     22400000
BenchmarkWideStringArgCopyReturn4           15.5 ns         15.7 ns     44800000
BenchmarkStdWStringFind1                    2.81 ns         2.76 ns    248888889
BenchmarkWideStringFind1                    2.60 ns         2.61 ns    263529412
BenchmarkStdWStringFind2                    7.96 ns         7.85 ns     89600000
BenchmarkWideStringFind2                    8.06 ns         8.02 ns     89600000
BenchmarkStdWStringFind3                    24.1 ns         24.0 ns     28000000
BenchmarkWideStringFind3                    23.0 ns         22.9 ns     32000000
BenchmarkStdWStringSubstr1                  23.3 ns         23.0 ns     29866667
BenchmarkWideStringSubstr1                  15.1 ns         15.1 ns     49777778
BenchmarkStdWStringAreEqual1                4.21 ns         4.26 ns    172307692
BenchmarkWideStringAreEqual1                1.68 ns         1.65 ns    407272727
BenchmarkStdWStringAreEqual2                1.65 ns         1.60 ns    448000000
BenchmarkWideStringAreEqual2                1.65 ns         1.67 ns    448000000
BenchmarkStdWStringToUpper1                 79.5 ns         78.5 ns      8960000
BenchmarkWideStringToUpper1A                42.2 ns         42.4 ns     16592593
BenchmarkWideStringToUpper1B                65.1 ns         65.6 ns     11200000
BenchmarkStdWStringFormat1                   223 ns          220 ns      3200000
BenchmarkWideStringFormat1                   308 ns          311 ns      2357895
BenchmarkStdWStringFormat2                  85.8 ns         85.8 ns      7466667
BenchmarkWideStringFormat2                  66.2 ns         65.6 ns     11200000
BenchmarkStdWStringFormat3                  68.9 ns         67.0 ns     11200000
BenchmarkWideStringFormat3                  80.7 ns         82.0 ns      8960000
```