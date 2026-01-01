# Compensated arithmetic

[Optimized basic math functions](Readme.md)

Compensated arithmetic is a technique used to improve the accuracy of 
floating-point calculations by keeping track of small errors that occur 
during arithmetic operations. This method is particularly useful in scenarios 
where high precision is required, such as numerical simulations, 
scientific computing, and financial calculations.

Core types and compensated arithmetic

- [CompensatedFloat](./CompensatedFloat.md): pair `{v, err}` representing a value and its rounding error.
- [CompensatedSum](./CompensatedSum.md): Kahan/compensated summation helper for accurate accumulation.
- [TwoProd](./TwoProd.md) (see also `TwoSum` in code): compute product and exact rounding error (implemented as `TwoProd` in header).
- [InnerProduct](./InnerProduct.md): compensated inner-product helpers and accurate dot-product methods.

Interval arithmetic and related helpers

- [Interval](./Interval.md): documentation for `Interval<T>` and examples of converting compensated results to intervals.
- [Sqr](./Sqr.md): square of an interval.
- [Sqrt](./Sqrt.md) / [SafeSqrt](./SafeSqrt.md): interval-aware square root helpers and safe variants.
- [FMA](./FMA.md): fused multiply-add with interval overloads documented in `Interval.md`.

Directed rounding and adjust helpers

- [NextUp](./NextUp.md) / [NextDown](./NextDown.md) / [NextAfter](./NextAfter.md): obtain next representable floats (directed ulp adjustments).
- [AddAdjustUp](./AddAdjustUp.md) / [AddAdjustDown](./AddAdjustDown.md)
- [SubAdjustUp](./SubAdjustUp.md) / [SubAdjustDown](./SubAdjustDown.md)
- [MulAdjustUp](./MulAdjustUp.md) / [MulAdjustDown](./MulAdjustDown.md)
- [DivAdjustUp](./DivAdjustUp.md) / [DivAdjustDown](./DivAdjustDown.md)
- [FMAAdjustUp](./FMAAdjustUp.md) / [FMAAdjustDown](./FMAAdjustDown.md)
- [SqrtAdjustUp](./SqrtAdjustUp.md) / [SqrtAdjustDown](./SqrtAdjustDown.md)
