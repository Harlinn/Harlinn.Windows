---
Copyright 2024 Espen Harlinn

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
---

Most of the files in this directory are modified versions
of the implementations provided by the [openlibm](https://github.com/JuliaMath/openlibm)
library. 

The modifications enable `constexpr `evaluation of the code and the functions are implemented
inside the `Harlinn::Math::Internal::OpenLibM` namespace. Usually the implementations
are unchanged.

The 80-bit `long double` type is not supported by Microsofts' C++ compiler, and functions 
taking `long double` arguments generally call their double precision counterparts.







