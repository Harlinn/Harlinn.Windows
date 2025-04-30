#pragma once
#ifndef PBRTO_UTIL_NEWFILE_H_
#define PBRTO_UTIL_NEWFILE_H_

/*
   Copyright 2024-2025 Espen Harlinn

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

#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewPStd.h>

#include <string>
#include <vector>

namespace pbrto
{

    // File and Filename Function Declarations
    PBRTO_EXPORT std::string ReadFileContents( std::string filename );
    PBRTO_EXPORT std::string ReadDecompressedFileContents( std::string filename );
    PBRTO_EXPORT bool WriteFileContents( std::string filename, const std::string& contents );

    PBRTO_EXPORT std::vector<Float> ReadFloatFile( std::string filename );

    PBRTO_EXPORT bool FileExists( std::string filename );
    PBRTO_EXPORT bool RemoveFile( std::string filename );

    PBRTO_EXPORT std::string ResolveFilename( std::string filename );
    PBRTO_EXPORT void SetSearchDirectory( std::string filename );

    PBRTO_EXPORT bool HasExtension( std::string filename, std::string ext );
    PBRTO_EXPORT std::string RemoveExtension( std::string filename );

    PBRTO_EXPORT std::vector<std::string> MatchingFilenames( std::string filename );

    PBRTO_EXPORT FILE* FOpenRead( std::string filename );
    PBRTO_EXPORT FILE* FOpenWrite( std::string filename );

}

#endif
