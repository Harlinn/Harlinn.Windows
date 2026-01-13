/*
    Copyright 2024-2026 Espen Harlinn
 
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
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_UTIL_FILE_H
#define PBRT_UTIL_FILE_H

#include <pbrto/pbrt.h>

#include <pbrto/util/pstd.h>

#include <string>
#include <vector>

namespace pbrt {

// File and Filename Function Declarations
std::string ReadFileContents(std::string filename);
std::string ReadDecompressedFileContents(std::string filename);
bool WriteFileContents(std::string filename, const std::string &contents);

std::vector<Float> ReadFloatFile(std::string filename);

bool FileExists(std::string filename);
bool RemoveFile(std::string filename);

std::string ResolveFilename(std::string filename);
void SetSearchDirectory(std::string filename);

bool HasExtension(std::string filename, std::string ext);
std::string RemoveExtension(std::string filename);

std::vector<std::string> MatchingFilenames(std::string filename);

FILE *FOpenRead(std::string filename);
FILE *FOpenWrite(std::string filename);

}  // namespace pbrt

#endif  // PBRT_UTIL_FILE_H
