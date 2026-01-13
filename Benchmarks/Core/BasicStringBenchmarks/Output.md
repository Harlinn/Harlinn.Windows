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
  performs comparable to `std::wstring` when compared against other strings.
- **Formatting**: `std::wstring` is generally faster in formatting operations, but not always.
- **Find Operations**: `std::wstring` outperforms `WideString` in find operations.
- **Case Conversion**: `WideString` implements `WideString ToUpper()`, a convenience method for converting 
  strings to uppercase, which performs well.
  - `BenchmarkWideStringToUpper1A` is implemented using `WideString::ToUpper()`.
  - `BenchmarkStdWStringToUpper1` and `BenchmarkWideStringToUpper1B` are implemented 
	using `std::towupper` in a loop.

While definitely not an exhaustive benchmark suite, the results indicate that `BasicString` 
is a good alternative to `std::wstring`, particularly when passing strings as function 
arguments and returning them by value. 

This is the primary use case for `BasicString` in the Harlinn.Common.Core, Harlinn.Windows, 
Harlinn.ODBC, Harlinn.OCI and Harlinn.OCI libraries.

```
2026-01-13T12:49:55+01:00
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
BenchmarkStdWStringDefaultConstructor       1.65 ns         1.65 ns    407272727
BenchmarkWideStringDefaultConstructor       1.63 ns         1.63 ns    497777778
BenchmarkStdWStringCStringConstructor       23.1 ns         23.0 ns     29866667
BenchmarkWideStringCStringConstructor       14.9 ns         15.1 ns     49777778
BenchmarkStdWStringAppendChar1               154 ns          153 ns      4480000
BenchmarkWideStringAppendChar1               192 ns          193 ns      3733333
BenchmarkStdWStringAppendChar2              22.8 ns         23.0 ns     29866667
BenchmarkWideStringAppendChar2              23.8 ns         23.4 ns     28000000
BenchmarkStdWStringAppendString1            45.8 ns         45.5 ns     15448276
BenchmarkWideStringAppendString1            25.6 ns         25.5 ns     26352941
BenchmarkStdWStringCopy                     3125 ns         3139 ns       224000
BenchmarkWideStringCopy                      956 ns          963 ns       746667
BenchmarkStdWStringArgCopyReturn            23.6 ns         23.5 ns     29866667
BenchmarkWideStringArgCopyReturn            9.15 ns         9.00 ns     74666667
BenchmarkStdWStringArgCopyReturn2           32.9 ns         33.0 ns     21333333
BenchmarkWideStringArgCopyReturn2           26.7 ns         26.7 ns     26352941
BenchmarkStdWStringArgCopyReturn3           2925 ns         2916 ns       235789
BenchmarkWideStringArgCopyReturn3           1824 ns         1842 ns       407273
BenchmarkStdWStringArgCopyReturn4           32.1 ns         32.2 ns     21333333
BenchmarkWideStringArgCopyReturn4           15.3 ns         15.3 ns     44800000
BenchmarkStdWStringFind1                    2.74 ns         2.70 ns    248888889
BenchmarkWideStringFind1                    3.36 ns         3.38 ns    203636364
BenchmarkStdWStringFind2                    8.70 ns         8.58 ns     74666667
BenchmarkWideStringFind2                    6.30 ns         6.28 ns    112000000
BenchmarkStdWStringFind3                    24.4 ns         24.6 ns     28000000
BenchmarkWideStringFind3                    59.5 ns         60.0 ns     11200000
BenchmarkStdWStringSubstr1                  23.4 ns         23.5 ns     29866667
BenchmarkWideStringSubstr1                  15.2 ns         15.0 ns     44800000
BenchmarkStdWStringAreEqual1                4.00 ns         4.01 ns    179200000
BenchmarkWideStringAreEqual1                1.86 ns         1.88 ns    373333333
BenchmarkStdWStringAreEqual2                1.64 ns         1.61 ns    407272727
BenchmarkWideStringAreEqual2                1.64 ns         1.64 ns    448000000
BenchmarkStdWStringToUpper1                 80.6 ns         80.2 ns      8960000
BenchmarkWideStringToUpper1A                42.1 ns         42.0 ns     16000000
BenchmarkWideStringToUpper1B                65.6 ns         65.6 ns     11200000
BenchmarkStdWStringFormat1                   225 ns          225 ns      3200000
BenchmarkWideStringFormat1                   306 ns          300 ns      2240000
BenchmarkStdWStringFormat2                  84.4 ns         83.7 ns      7466667
BenchmarkWideStringFormat2                  67.3 ns         67.0 ns     11200000
BenchmarkStdWStringFormat3                  70.2 ns         71.1 ns     11200000
BenchmarkWideStringFormat3                  82.5 ns         81.6 ns      7466667
```