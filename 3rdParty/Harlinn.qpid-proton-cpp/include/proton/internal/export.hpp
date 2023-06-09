#ifndef PROTON_INTERNAL_EXPORT_HPP
#define PROTON_INTERNAL_EXPORT_HPP

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#ifdef BUILDING_HARLINN_QPIDPROTONCPP
#define qpid_proton_cpp_EXPORTS 1
#else
#pragma comment(lib,"Harlinn.qpid-proton-cpp.lib")
#endif


/// @cond INTERNAL

/// import/export macros
#if defined(_WIN32) && !defined(PN_CPP_DECLARE_STATIC)
  //
  // Import and Export definitions for Windows:
  //
#  define PN_CPP_EXPORT __declspec(dllexport)
#  define PN_CPP_IMPORT __declspec(dllimport)
#  define PN_CPP_CLASS_EXPORT
#  define PN_CPP_CLASS_IMPORT
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#  define PN_CPP_EXPORT __global
#  define PN_CPP_IMPORT
#  define PN_CPP_CLASS_EXPORT __global
#  define PN_CPP_CLASS_IMPORT
#else
  //
  // Non-Windows (Linux, etc.) definitions:
  //
#  define PN_CPP_EXPORT __attribute__((visibility("default")))
#  define PN_CPP_IMPORT
#  define PN_CPP_CLASS_EXPORT __attribute__((visibility("default")))
#  define PN_CPP_CLASS_IMPORT
#endif

// For qpid-proton-cpp library symbols
#ifdef qpid_proton_cpp_EXPORTS
#  define PN_CPP_EXTERN PN_CPP_EXPORT
#  define PN_CPP_CLASS_EXTERN PN_CPP_CLASS_EXPORT
#else
#  define PN_CPP_EXTERN PN_CPP_IMPORT
#  define PN_CPP_CLASS_EXTERN PN_CPP_CLASS_IMPORT
#endif

#if defined(PN_CPP_USE_DEPRECATED_API)
#  define PN_CPP_DEPRECATED(message)
#else
#  if defined(PN_COMPILER_CXX_ATTRIBUTE_DEPRECATED) && PN_COMPILER_CXX_ATTRIBUTE_DEPRECATED
#    define PN_CPP_DEPRECATED(message) [[deprecated(message)]]
#  elif defined(_WIN32)
#    define PN_CPP_DEPRECATED(message) __declspec(deprecated(message))
#  elif (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 40500
#    define PN_CPP_DEPRECATED(message) __attribute__((deprecated))
#  else
#    define PN_CPP_DEPRECATED(message) __attribute__((deprecated(message)))
#  endif
#endif

/// @endcond

#endif // PROTON_INTERNAL_EXPORT_HPP
