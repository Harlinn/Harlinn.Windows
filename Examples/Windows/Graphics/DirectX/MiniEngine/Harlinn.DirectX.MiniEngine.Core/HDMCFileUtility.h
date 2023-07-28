//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

#include "HDMCDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Utility
    {
        

        typedef std::shared_ptr<std::vector<Byte> > ByteArray;
        HDMC_EXPORT extern ByteArray NullFile;

        // Reads the entire contents of a binary file.  If the file with the same name except with an additional
        // ".gz" suffix exists, it will be loaded and decompressed instead.
        // This operation blocks until the entire file is read.
        HDMC_EXPORT ByteArray ReadFileSync( const std::wstring& fileName );

        // Same as previous except that it does not block but instead returns a task.
        HDMC_EXPORT concurrency::task<ByteArray> ReadFileAsync( const std::wstring& fileName );

    } // namespace Utility
}