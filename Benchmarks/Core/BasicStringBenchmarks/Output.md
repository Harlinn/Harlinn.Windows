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
- **iterators/`begin()`/`end()`**: 
  - `std::ranges::search` performs equally well with `WideString` and `std::wstring`.
  - Range for loops, and basic iteration using iterators, to access the contents of a string
	performs equally well with `WideString` and `std::wstring`.
- **Case Conversion**: `WideString` implements `WideString ToUpper()`, a convenience method for converting 
  strings to uppercase, which performs well.
  - `BenchmarkWideStringToUpper1A` is implemented using `WideString::ToUpper()`.
  - `BenchmarkStdWStringToUpper1` and `BenchmarkWideStringToUpper1B` are implemented 
	using `std::towupper` in a loop.
- **`std::hash`**: `std::hash` is significantly faster for `WideString` compared to `std::wstring`,
  regardless of whether the string is small, mid-sized or large.
- **`operator [](offset)`**: is slightly faster with `std::wstring` compared to `WideString`.
- **`operator +(lhs, rhs)`**: is faster, and more flexible, with `WideString` compared to `std::wstring`.
	 
While definitely not an exhaustive benchmark suite, the results shows that `BasicString` 
is a good alternative to `std::basic_string`, particularly when passing strings as function 
arguments and returning them by value. 

This is the primary use case for `BasicString` in the Harlinn.Common.Core, Harlinn.Windows, 
Harlinn.ODBC, Harlinn.OCI and Harlinn.OCI libraries.

```
2026-01-13T17:52:12+01:00
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
BenchmarkWideStringDefaultConstructor                       1.66 ns         1.65 ns    407272727
BenchmarkStdWStringCStringConstructor                       24.3 ns         24.0 ns     28000000
BenchmarkWideStringCStringConstructor                       14.8 ns         14.0 ns     44800000
BenchmarkStdWStringFromTwoCStyleStringsConstructor          55.2 ns         54.4 ns     11200000
BenchmarkWideStringFromTwoCStyleStringsConstructor          21.3 ns         21.3 ns     34461538
BenchmarkStdWStringFromCharAndCStyleStringConstructor       36.0 ns         36.1 ns     19478261
BenchmarkWideStringFromCharAndCStyleStringConstructor       14.9 ns         15.1 ns     49777778
BenchmarkStdWStringAppendChar1                               155 ns          153 ns      4480000
BenchmarkWideStringAppendChar1                               210 ns          209 ns      3733333
BenchmarkStdWStringAppendChar2                              23.1 ns         23.0 ns     29866667
BenchmarkWideStringAppendChar2                              25.4 ns         25.1 ns     28000000
BenchmarkStdWStringAppendString1                            47.8 ns         47.6 ns     14451613
BenchmarkWideStringAppendString1                            26.4 ns         26.8 ns     28000000
BenchmarkStdWStringCopy                                     3042 ns         3048 ns       235789
BenchmarkWideStringCopy                                      965 ns          921 ns       746667
BenchmarkStdWStringArgCopyReturn                            24.1 ns         24.0 ns     28000000
BenchmarkWideStringArgCopyReturn                            9.16 ns         9.00 ns     74666667
BenchmarkStdWStringArgCopyReturn2                           32.5 ns         31.5 ns     21333333
BenchmarkWideStringArgCopyReturn2                           18.1 ns         18.0 ns     40727273
BenchmarkStdWStringArgCopyReturn3                           3024 ns         3048 ns       235789
BenchmarkWideStringArgCopyReturn3                           1829 ns         1842 ns       373333
BenchmarkStdWStringArgCopyReturn4                           30.2 ns         30.0 ns     22400000
BenchmarkWideStringArgCopyReturn4                           15.3 ns         15.0 ns     44800000
BenchmarkStdWStringFind1                                    2.75 ns         2.79 ns    263529412
BenchmarkWideStringFind1                                    2.56 ns         2.57 ns    280000000
BenchmarkStdWStringFind2                                    8.59 ns         8.58 ns     74666667
BenchmarkWideStringFind2                                    8.59 ns         8.54 ns     89600000
BenchmarkStdWStringFind3                                    25.0 ns         25.1 ns     29866667
BenchmarkWideStringFind3                                    24.6 ns         24.6 ns     28000000
BenchmarkStdWStringSubstr1                                  23.5 ns         23.5 ns     29866667
BenchmarkWideStringSubstr1                                  15.3 ns         15.3 ns     44800000
BenchmarkStdWStringAreEqual1                                4.08 ns         4.08 ns    172307692
BenchmarkWideStringAreEqual1                                1.66 ns         1.65 ns    407272727
BenchmarkStdWStringAreEqual2                                1.65 ns         1.65 ns    407272727
BenchmarkWideStringAreEqual2                                1.65 ns         1.53 ns    407272727
BenchmarkStdWStringToUpper1                                 79.9 ns         80.2 ns      8960000
BenchmarkWideStringToUpper1A                                40.4 ns         39.9 ns     17230769
BenchmarkWideStringToUpper1B                                66.7 ns         67.0 ns     11200000
BenchmarkStdWStringFormat1                                   227 ns          220 ns      2986667
BenchmarkWideStringFormat1                                   318 ns          321 ns      2240000
BenchmarkStdWStringFormat2                                  83.2 ns         83.7 ns      7466667
BenchmarkWideStringFormat2                                  68.5 ns         67.0 ns     11200000
BenchmarkStdWStringFormat3                                  70.7 ns         69.8 ns      8960000
BenchmarkWideStringFormat3                                  85.6 ns         85.4 ns      8960000
BenchmarkStdWStringCStringAssign                            61.6 ns         61.4 ns     11200000
BenchmarkWideStringCStringAssign                            37.3 ns         36.0 ns     18666667
BenchmarkStdWStringSpanAssign                               41.0 ns         40.5 ns     16592593
BenchmarkWideStringSpanAssign                               21.3 ns         21.0 ns     32000000
BenchmarkStdWStringHash1                                    17.2 ns         17.3 ns     40727273
BenchmarkWideStringHash1                                    3.02 ns         2.98 ns    235789474
BenchmarkStdWStringHash2                                    1629 ns         1639 ns       448000
BenchmarkWideStringHash2                                    43.4 ns         44.3 ns     16592593
BenchmarkStdWStringHash3                                 1691623 ns      1674107 ns          448
BenchmarkWideStringHash3                                   36267 ns        35156 ns        18667
BenchmarkStdWStringRangesSearchHttps                        24.5 ns         24.0 ns     28000000
BenchmarkWideStringRangesSearchHttps                        24.9 ns         24.0 ns     28000000
BenchmarkStdWStringIndexOperatorAccess                       225 ns          225 ns      3200000
BenchmarkWideStringIndexOperatorAccess                       238 ns          241 ns      2986667
BenchmarkStdWstringOperatorPlusMix                          86.2 ns         85.8 ns      7466667
BenchmarkWideStringOperatorPlusMix                          48.6 ns         48.7 ns     14451613
BenchmarkStdWStringIteratorAccess                            399 ns          399 ns      1723077
BenchmarkWideStringIteratorAccess                            368 ns          368 ns      1866667
BenchmarkStdWStringRangeForAccess                            237 ns          235 ns      2986667
BenchmarkWideStringRangeForAccess                            238 ns          241 ns      2986667
```