/*
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
*/

// Original comment:

// Pharos Demangler
//
// Copyright 2017 Carnegie Mellon University. All Rights Reserved.
//
// NO WARRANTY. THIS CARNEGIE MELLON UNIVERSITY AND SOFTWARE ENGINEERING
// INSTITUTE MATERIAL IS FURNISHED ON AN "AS-IS" BASIS. CARNEGIE MELLON
// UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER EXPRESSED OR
// IMPLIED, AS TO ANY MATTER INCLUDING, BUT NOT LIMITED TO, WARRANTY OF
// FITNESS FOR PURPOSE OR MERCHANTABILITY, EXCLUSIVITY, OR RESULTS
// OBTAINED FROM USE OF THE MATERIAL. CARNEGIE MELLON UNIVERSITY DOES NOT
// MAKE ANY WARRANTY OF ANY KIND WITH RESPECT TO FREEDOM FROM PATENT,
// TRADEMARK, OR COPYRIGHT INFRINGEMENT.
//
// Released under a BSD-style license, please see license.txt or contact
// permission@sei.cmu.edu for full terms.
//
// [DISTRIBUTION STATEMENT A] This material has been approved for public
// release and unlimited distribution.  Please see Copyright notice for
// non-US Government use and distribution.
//
// DM17-0949

// This file is meant to be included after setting X(enum_symbol,
// enum_string) to an appropriate macro.  The X macro will be
// undefined at the end of this file.

#ifndef X
#  error "X() has not been defined"
#endif

X(Undefined,                         ""),

X(Boolean,                              "bool"),
X(SByte,                       "signed char"),
X(CHAR,                              "char"),
X(UNSIGNED_CHAR,                     "unsigned char"),
X(SHORT,                             "short"),
X(UNSIGNED_SHORT,                    "unsigned short"),
X(INT,                               "int"),
X(UNSIGNED_INT,                      "unsigned int"),
X(LONG,                              "long"),
X(UNSIGNED_LONG,                     "unsigned long"),
X(FLOAT,                             "float"),
X(DOUBLE,                            "double"),
X(LONG_DOUBLE,                       "long double"),

X(INT8,                              "int8_t"),
X(UINT8,                             "uint8_t"),
X(INT16,                             "int16_t"),
X(UINT16,                            "uint16_t"),
X(INT32,                             "int32_t"),
X(UINT32,                            "uint32_t"),
X(INT64,                             "int64_t"),
X(UINT64,                            "uint64_t"),
X(CHAR16,                            "char16_t"),
X(CHAR32,                            "char32_t"),
X(WCHAR,                             "wchar_t"),

X(INT128,                            "__int128"),
X(UINT128,                           "unsigned __int128"),

X(Void,                              "void"),
X(ELLIPSIS,                          "..."),

X(UNION,                             "union"),
X(CLASS,                             "class"),
X(STRUCT,                            "struct"),
X(ENUM,                              "enum"),

X(CTOR,                              "`constructor'"),
X(DTOR,                              "`destructor'"),
X(OP_NEW,                            "operator new"),
X(OP_DELETE,                         "operator delete"),
X(OP_ASSIGN,                         "operator="),
X(OP_RSHIFT,                         "operator>>"),
X(OP_LSHIFT,                         "operator<<"),
X(OP_NOT,                            "operator!"),
X(OP_EQUAL,                          "operator=="),
X(OP_NOTEQUAL,                       "operator!="),
X(OP_INDEX,                          "operator[]"),
X(OP_TYPE,                           "operator `type'"),
X(OP_INDIRECT,                       "operator->"),
X(OP_STAR,                           "operator*"),
X(OP_PLUSPLUS,                       "operator++"),
X(OP_MINUSMINUS,                     "operator--"),
X(OP_MINUS,                          "operator-"),
X(OP_PLUS,                           "operator+"),
X(OP_AMP,                            "operator&"),
X(OP_INDIRECT_METHOD,                "operator->*"),
X(OP_DIV,                            "operator/"),
X(OP_MOD,                            "operator%"),
X(OP_LESS,                           "operator<"),
X(OP_LESSEQ,                         "operator<="),
X(OP_GREATER,                        "operator>"),
X(OP_GREATEREQ,                      "operator>="),
X(OP_COMMA,                          "operator,"),
X(OP_CALL,                           "operator()"),
X(OP_BNOT,                           "operator~"),
X(OP_BXOR,                           "operator^"),
X(OP_BOR,                            "operator|"),
X(OP_AND,                            "operator&&"),
X(OP_OR,                             "operator||"),
X(OP_STAR_ASSIGN,                    "operator*="),
X(OP_PLUS_ASSIGN,                    "operator+="),
X(OP_MINUS_ASSIGN,                   "operator-="),
X(OP_DIV_ASSIGN,                     "operator/="),
X(OP_MOD_ASSIGN,                     "operator%="),
X(OP_RSHIFT_ASSIGN,                  "operator>>="),
X(OP_LSHIFT_ASSIGN,                  "operator<<="),
X(OP_AMP_ASSIGN,                     "operator&="),
X(OP_BOR_ASSIGN,                     "operator|="),
X(OP_BXOR_ASSIGN,                    "operator^="),
X(VFTABLE,                           "`vftable'"),
X(VBTABLE,                           "`vbtable'"),
X(VCALL,                             "`vcall'"),
X(TYPEOF,                            "`typeof'"),
X(LOCAL_STATIC_GUARD,                "`local static guard'"),
X(VBASE_DTOR,                        "`vbase destructor'"),
X(VECTOR_DELETING_DTOR,              "`vector deleting destructor'"),
X(DEFAULT_CTOR_CLOSURE,              "`default constructor closure'"),
X(SCALAR_DELETING_DTOR,              "`scalar deleting destructor'"),
X(VECTOR_CTOR_ITER,                  "`vector constructor iterator'"),
X(VECTOR_DTOR_ITER,                  "`vector destructor iterator'"),
X(VECTOR_VBASE_CTOR_ITER,            "`vector vbase constructor iterator'"),
X(VIRTUAL_DISPLACEMENT_MAP,          "`virtual displacement map'"),
X(EH_VECTOR_CTOR_ITER,               "`eh vector constructor iterator'"),
X(EH_VECTOR_DTOR_ITER,               "`eh vector destructor iterator'"),
X(EH_VECTOR_VBASE_CTOR_ITER,         "`eh vector vbase constructor iterator'"),
X(COPY_CTOR_CLOSURE,                 "`copy constructor closure'"),
X(UDT_RETURNING,                     "`udt returning'"),
X(LOCAL_VFTABLE,                     "`local vftable'"),
X(LOCAL_VFTABLE_CTOR_CLOSURE,        "`local vftable constructor closure'"),
X(OP_NEW_ARRAY,                      "operator new[]"),
X(OP_DELETE_ARRAY,                   "operator delete[]"),
X(PLACEMENT_DELETE_CLOSURE,          "`placement delete closure'"),
X(PLACEMENT_DELETE_ARRAY_CLOSURE,    "`placement delete[] closure'"),
X(MANAGED_VECTOR_CTOR_ITER,          "`managed vector constructor iterator'"),
X(MANAGED_VECTOR_DTOR_ITER,          "`managed vector destructor iterator'"),
X(EH_VECTOR_COPY_CTOR_ITER,          "`eh vector copy constructor iterator'"),
X(EH_VECTOR_VBASE_COPY_CTOR_ITER,    "`eh vector vbase copy constructor iterator'"),
X(DYNAMIC_INITIALIZER,               "`dynamic initializer'"),
X(DYNAMIC_ATEXIT_DTOR,               "`dynamic atexit destructor'"),
X(VECTOR_COPY_CTOR_ITER,             "`vector copy constructor iterator'"),
X(VECTOR_VBASE_COPY_CTOR_ITER,       "`vector vbase copy constructor iterator'"),
X(MANAGED_VECTOR_COPY_CTOR_ITER,     "`managed vector copy constructor iterator'"),
X(LOCAL_STATIC_THREAD_GUARD,         "`local static thread guard'"),
X(OP_DQUOTE,                         "operator\"\""),

X(RTTI_TYPE_DESC,                    "`RTTI Type Descriptor'"),
X(RTTI_BASE_CLASS_DESC,              "`RTTI Base Class Descriptor'"),
X(RTTI_BASE_CLASS_ARRAY,             "`RTTI Base Class Array'"),
X(RTTI_CLASS_HEIRARCHY_DESC,         "`RTTI Class Hierarchy Descriptor'"),
X(RTTI_COMPLETE_OBJ_LOCATOR,         "`RTTI Complete Object Locator'")

