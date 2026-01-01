# Interval

Description

`Interval<T>` represents a conservative enclosure \([l, u]\) of a real value where the exact mathematical value is guaranteed to lie within the bounds. Interval arithmetic propagates rounding and approximation error through directed rounding helpers such as `NextDown`, `NextUp`, `AddAdjustDown`, `AddAdjustUp`, `MulAdjustDown` and `MulAdjustUp` so results remain conservative.

Mathematical summary

- An interval is a closed set \([l, u]\) with \(l \le u\).
- Replace a scalar result \(x\) by an interval: \(x \rightsquigarrow [x_{\min}, x_{\max}]\).
- Given a compensated product \((p, \varepsilon)\) from `TwoProd(a,b)`, convert to an interval as

$$
[p - \varepsilon^{-},\; p + \varepsilon^{+}] \approx [\mathrm{SubAdjustDown}(p,\varepsilon),\; \mathrm{AddAdjustUp}(p,\varepsilon)],
$$

where directed-adjust helpers produce conservative lower and upper endpoints.

Design and guarantees

- Conservatism: every operation widens bounds as necessary so the true mathematical result is enclosed.
- Directed rounding: lower endpoints use downward rounding, upper endpoints use upward rounding.
- Failure detection: intervals that straddle critical values (for example zero) reveal sign-uncertainty or cancellation.
- Tightness: combine interval arithmetic with compensated operations (`TwoProd`, `TwoSum`, `FMA`) to keep enclosures tight.

## API reference

The following documents the public members of `Interval<T>` and shows short usage examples. Replace `T` with `float` or `double` in examples.

Constructors and creation

- `Interval()`
  - Default constructs an interval equal to `[0, 0]`.

  Example:
  ```cpp
  Interval<double> i; // [0,0]
  ```

- `Interval(value_type v)`
  - Constructs the degenerate interval `[v, v]`.

  Example:
  ```cpp
  Interval<double> i(1.5); // [1.5, 1.5]
  ```

- `Interval(value_type low, value_type high)`
  - Constructs an interval from the two endpoints. The endpoints are ordered so the lower bound is always <= upper bound.

  Example:
  ```cpp
  Interval<double> i(2.0, -1.0); // becomes [-1.0, 2.0]
  ```

- `static Interval FromValueAndError(value_type v, value_type err)`
  - Create a tight interval from a compensated value `v` and an associated error `err`.

  Example:
  ```cpp
  auto p = TwoProd(1e16 + 1.0, 1e-16); // {v, err}
  auto i = Interval<double>::FromValueAndError(p.v, p.err);
  ```

Accessors and conversions

- `value_type LowerBound() const` : returns lower endpoint.
- `value_type UpperBound() const` : returns upper endpoint.
- `value_type Midpoint() const` : returns midpoint \((l+u)/2\).
- `value_type Width() const` : returns width \(u-l\).
- `explicit operator value_type() const` : converts to the midpoint.
- `value_type operator[](size_t i) const` : `i==0` -> lower, otherwise upper.

Example:
```cpp
Interval<double> i(-1.0, 2.0);
double low = i.LowerBound(); // -1.0
double mid = static_cast<double>(i); // 0.5
double width = i.Width(); // 3.0
```

Predicates and tests

- `bool Exactly(value_type v) const` : true if interval is exactly `[v,v]`.
- `bool operator==(value_type v) const` : same as `Exactly`.
- `bool operator==(const Interval& i) const` : compare endpoints.
- `bool operator!=(value_type v) const` : true if `v` is not in the interval.

Example:
```cpp
Interval<double> i(1.0);
if (i.Exactly(1.0)) { /* degenerate */ }
if (i != 2.0) { /* 2.0 not contained */ }
```

Arithmetic operators

All arithmetic results are conservative intervals; lower endpoints use downward-adjust helpers and upper endpoints use upward-adjust helpers.

- `operator+`, `operator-`, `operator*`, `operator/` with another `Interval`.
- Scalar operators: `operator+(Interval, f)`, `operator*(Interval, f)`, and symmetric free-function overloads.
- Compound assignment: `+=`, `-=`, `*=`, `/=` for intervals and scalars.

Example: add and multiply intervals
```cpp
Interval<double> a(1.0, 2.0);
Interval<double> b(0.1, 0.2);
Interval<double> s = a + b; // conservative sum
Interval<double> p = a * b; // conservative product
```

Division notes

- Division by an interval that straddles zero returns an unbounded interval `[-inf, +inf]` to indicate absence of a finite guaranteed quotient.

Example:
```cpp
Interval<double> denom(-1.0, 1.0);
Interval<double> result = Interval<double>(1.0) / denom; // [-inf, +inf]
```

Unary and helper operations

- Unary negation: `-i` returns `[-u, -l]`.
- `Sqr(i)`, `Sqrt(i)`, `Abs(i)` provide interval-aware versions of these operations.
- `FMA(a,b,c)` for interval fused multiply-add.

Example: sqrt and square
```cpp
Interval<double> i(0.5, 4.0);
Interval<double> r = Sqrt(i); // [sqrt(0.5) conservative down, sqrt(4.0) conservative up]
Interval<double> sq = Sqr(i);
```

Trigonometric and transcendental functions

Interval-aware versions exist for `Sin`, `Cos`, `ACos`, and `SinCos`. They account for monotonic ranges and wrap-around where needed.

Example: sine interval
```cpp
Interval<double> ang(0.0, Constants<double>::PiOver2);
Interval<double> s = Sin(ang); // [0, 1] with conservative endpoints
```

Conversion from compensated results

- Typical flow: compute a compensated result with `TwoProd` or `TwoSum`, then call `FromValueAndError` to obtain a tight interval.

Example: converting product
```cpp
auto p = TwoProd(1e16 + 1.0, 1e-16);
auto prodInterval = Interval<double>::FromValueAndError(p.v, p.err);
```

Decision-making with intervals

- Use interval endpoints to make robust decisions. For instance, to decide if a quadratic has real roots compute the discriminant as an interval and test its lower bound:

$$\Delta = b^2 - 4ac,\quad\text{real roots exist if }\Delta \ge 0.
$$

Example:
```cpp
Interval<double> a(1.0), b(-3.0), c(2.0);
auto discrim = DifferenceOfProducts(b, b, MulPow2(4.0, a), c);
if (discrim.LowerBound() >= 0.0) {
    Interval<double> r0, r1;
    if (Quadratic(a, b, c, &r0, &r1)) {
        // intervals r0 and r1 enclose roots
    }
}
```

Best practices

- Prefer `FromValueAndError` when you have compensated arithmetic results to obtain tighter bounds.
- Use intervals to validate numerical decisions and detect cancellation: if an interval straddles zero, handle that case explicitly rather than assuming sign.
- If intervals grow too wide, consider increasing precision, subdividing the domain or using compensated arithmetic earlier in the computation.

See also

- `TwoProd`, `TwoSum`, `CompensatedFloat`, `Quadratic`, `NewtonBisection`.
