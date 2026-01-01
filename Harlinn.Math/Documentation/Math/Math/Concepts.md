[Optimized basic math functions](Readme.md)

### BooleanType

```
template<typename T>
concept BooleanType = std::is_same_v<T, bool>;
```
`BooleanType` matches `bool` template arguments.


### FloatingPointType

```
template<typename T>
concept FloatingPointType = std::is_floating_point_v<T>;
```
`FloatingPointType` matches floating point template arguments.

### IntegerType

```
template<typename T>
concept IntegerType = std::is_integral_v<T> && 
                (std::is_same_v<T, bool> == false);
```
`IntegerType` matches integral type template arguments.

### SignedIntegerType

```
template<typename T>
concept SignedIntegerType = IntegerType<T> && 
                                std::is_signed_v<T>;
```
`SignedIntegerType` matches signed integral type template arguments.


### UnsignedIntegerType

```
template<typename T>
concept UnsignedIntegerType = IntegerType<T> && 
                                (std::is_signed_v<T> == false);
```
`UnsignedIntegerType` matches unsigned integral type template arguments.

### UnsignedIntegerOrBooleanType

```
template<typename T>
concept UnsignedIntegerOrBooleanType = UnsignedIntegerType<T> || BooleanType<T>;
```

`UnsignedIntegerOrBooleanType` matches unsigned integral type or `bool` type template arguments.

### ArithmeticType

```
template<typename T>
concept ArithmeticType = IntegerType<T> || FloatingPointType<T>;
```
`ArithmeticType` matches floating point or integral type template arguments.
