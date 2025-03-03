#pragma once
#ifndef DBXGEN_METADATA_MODELINFO_H_
#define DBXGEN_METADATA_MODELINFO_H_
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

#include "EnumInfo.h"
#include "ClassInfo.h"

namespace Harlinn::Tools::DbXGen::Metadata
{
    class ModelInfo : public std::enable_shared_from_this<ModelInfo>
    {
        WideString name_{ L"Model" };
        WideString discriminatorName_{ L"Kind" };
        std::unordered_map<WideString, std::shared_ptr<EnumInfo>> enums_;
        std::unordered_map<WideString, std::shared_ptr<TypeInfo>> types_;
        std::unordered_map<WideString, std::shared_ptr<ClassInfo>> classes_;
        std::vector<std::shared_ptr<ClassInfo>> classList_;
    public:
        ModelInfo()
        { }


        const WideString& Name( ) const
        {
            return name_;
        }

        std::shared_ptr<EnumInfo> FindEnum( const WideString& enumName ) const;
        std::shared_ptr<TypeInfo> FindType( const WideString& typeName ) const;
        std::shared_ptr<ClassInfo> FindClass( const WideString& className ) const;

        const std::unordered_map<WideString, std::shared_ptr<EnumInfo>>& Enums( ) const
        {
            return enums_;
        }
        const std::unordered_map<WideString, std::shared_ptr<TypeInfo>>& Types( ) const
        {
            return types_;
        }

        const std::vector<std::shared_ptr<ClassInfo>>& Classes( ) const
        {
            return classList_;
        }

        


        void Load( const XmlElement& xmlElement );

        static std::shared_ptr<ModelInfo> LoadFromFile( const WideString& filename );

        void Validate( ) const;


    };

}

#endif
