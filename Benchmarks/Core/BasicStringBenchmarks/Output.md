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
- **iterators/`begin()`/`end()`**: `std::ranges::search` performs equally well with `WideString` and `std::wstring`.
- **Case Conversion**: `WideString` implements `WideString ToUpper()`, a convenience method for converting 
  strings to uppercase, which performs well.
  - `BenchmarkWideStringToUpper1A` is implemented using `WideString::ToUpper()`.
  - `BenchmarkStdWStringToUpper1` and `BenchmarkWideStringToUpper1B` are implemented 
	using `std::towupper` in a loop.
- **`std::hash`**: `std::hash` is significantly faster for `WideString` compared to `std::wstring`,
  regardless of whether the string is small, mid-sized or large.
	 
While definitely not an exhaustive benchmark suite, the results shows that `BasicString` 
is a good alternative to `std::basic_string`, particularly when passing strings as function 
arguments and returning them by value. 

This is the primary use case for `BasicString` in the Harlinn.Common.Core, Harlinn.Windows, 
Harlinn.ODBC, Harlinn.OCI and Harlinn.OCI libraries.

```
2026-01-13T17:09:12+01:00
Running BasicStringBenchmarks.exe
Run on (20 X 1996 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1024 KiB (x10)
  L3 Unified 16384 KiB (x2)
------------------------------------------------------------------------------------------------
Benchmark                                                      Time             CPU   Iterations
------------------------------------------------------------------------------------------------
BenchmarkStdWStringDefaultConstructor                       1.66 ns         1.65 ns    407272727
BenchmarkWideStringDefaultConstructor                       1.64 ns         1.65 ns    407272727
BenchmarkStdWStringCStringConstructor                       23.1 ns         23.0 ns     29866667
BenchmarkWideStringCStringConstructor                       14.8 ns         15.1 ns     49777778
BenchmarkStdWStringFromTwoCStyleStringsConstructor          54.8 ns         54.7 ns     10000000
BenchmarkWideStringFromTwoCStyleStringsConstructor          20.7 ns         20.9 ns     34461538
BenchmarkStdWStringFromCharAndCStyleStringConstructor       35.5 ns         35.3 ns     20363636
BenchmarkWideStringFromCharAndCStyleStringConstructor       15.7 ns         15.7 ns     44800000
BenchmarkStdWStringAppendChar1                               146 ns          143 ns      4480000
BenchmarkWideStringAppendChar1                               193 ns          190 ns      3446154
BenchmarkStdWStringAppendChar2                              22.7 ns         22.5 ns     29866667
BenchmarkWideStringAppendChar2                              25.5 ns         25.7 ns     28000000
BenchmarkStdWStringAppendString1                            47.7 ns         47.1 ns     14933333
BenchmarkWideStringAppendString1                            26.3 ns         26.1 ns     26352941
BenchmarkStdWStringCopy                                     3035 ns         3069 ns       224000
BenchmarkWideStringCopy                                      960 ns          928 ns       640000
BenchmarkStdWStringArgCopyReturn                            23.7 ns         23.5 ns     29866667
BenchmarkWideStringArgCopyReturn                            9.06 ns         9.00 ns     74666667
BenchmarkStdWStringArgCopyReturn2                           33.0 ns         32.2 ns     20363636
BenchmarkWideStringArgCopyReturn2                           18.3 ns         18.4 ns     40727273
BenchmarkStdWStringArgCopyReturn3                           3133 ns         3139 ns       224000
BenchmarkWideStringArgCopyReturn3                           1823 ns         1842 ns       407273
BenchmarkStdWStringArgCopyReturn4                           32.2 ns         32.2 ns     21333333
BenchmarkWideStringArgCopyReturn4                           15.3 ns         14.6 ns     44800000
BenchmarkStdWStringFind1                                    2.74 ns         2.67 ns    263529412
BenchmarkWideStringFind1                                    2.58 ns         2.49 ns    263529412
BenchmarkStdWStringFind2                                    7.96 ns         8.02 ns     89600000
BenchmarkWideStringFind2                                    8.20 ns         7.95 ns     74666667
BenchmarkStdWStringFind3                                    22.0 ns         21.5 ns     32000000
BenchmarkWideStringFind3                                    21.9 ns         22.0 ns     32000000
BenchmarkStdWStringSubstr1                                  23.5 ns         23.5 ns     29866667
BenchmarkWideStringSubstr1                                  15.4 ns         15.0 ns     44800000
BenchmarkStdWStringAreEqual1                                4.13 ns         4.17 ns    172307692
BenchmarkWideStringAreEqual1                                1.88 ns         1.88 ns    373333333
BenchmarkStdWStringAreEqual2                                1.65 ns         1.65 ns    407272727
BenchmarkWideStringAreEqual2                                1.66 ns         1.65 ns    407272727
BenchmarkStdWStringToUpper1                                 80.9 ns         80.2 ns      8960000
BenchmarkWideStringToUpper1A                                40.8 ns         40.5 ns     16592593
BenchmarkWideStringToUpper1B                                66.3 ns         67.0 ns     11200000
BenchmarkStdWStringFormat1                                   229 ns          230 ns      2986667
BenchmarkWideStringFormat1                                   316 ns          321 ns      2240000
BenchmarkStdWStringFormat2                                  86.3 ns         85.8 ns      7466667
BenchmarkWideStringFormat2                                  67.9 ns         68.4 ns     11200000
BenchmarkStdWStringFormat3                                  70.3 ns         69.8 ns      8960000
BenchmarkWideStringFormat3                                  81.7 ns         82.0 ns      8960000
BenchmarkStdWStringCStringAssign                            61.5 ns         62.5 ns     10000000
BenchmarkWideStringCStringAssign                            37.8 ns         37.7 ns     18666667
BenchmarkStdWStringSpanAssign                               38.8 ns         39.3 ns     18666667
BenchmarkWideStringSpanAssign                               20.3 ns         20.4 ns     34461538
BenchmarkStdWStringHash1                                    17.3 ns         16.9 ns     40727273
BenchmarkWideStringHash1                                    3.01 ns         3.05 ns    235789474
BenchmarkStdWStringHash2                                    1642 ns         1639 ns       448000
BenchmarkWideStringHash2                                    43.4 ns         43.3 ns     16592593
BenchmarkStdWStringHash3                                 1692351 ns      1689189 ns          407
BenchmarkWideStringHash3                                   36446 ns        36830 ns        18667
BenchmarkStdWStringRangesSearchHttps                        21.6 ns         21.5 ns     32000000
BenchmarkWideStringRangesSearchHttps                        21.8 ns         22.0 ns     32000000
```