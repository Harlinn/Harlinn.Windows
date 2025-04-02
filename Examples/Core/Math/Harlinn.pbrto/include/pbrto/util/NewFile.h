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
    std::string ReadFileContents( const std::string& filename );
    std::string ReadDecompressedFileContents( const std::string& filename );
    bool WriteFileContents( const std::string& filename, const std::string& contents );

    std::vector<Float> ReadFloatFile( const std::string& filename );

    bool FileExists( const std::string& filename );
    bool RemoveFile( const std::string& filename );

    std::string ResolveFilename( const std::string& filename );
    void SetSearchDirectory( const std::string& filename );

    bool HasExtension( const std::string& filename, const std::string& ext );
    std::string RemoveExtension( const std::string& filename );

    std::vector<std::string> MatchingFilenames( const std::string& filename );

    FILE* FOpenRead( const std::string& filename );
    FILE* FOpenWrite( const std::string& filename );

};

#endif
