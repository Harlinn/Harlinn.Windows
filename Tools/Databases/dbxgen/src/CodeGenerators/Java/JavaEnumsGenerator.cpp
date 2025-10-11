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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/Java/JavaHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void JavaEnumsGenerator::Run()
    {
        const auto& model = Model();
        const auto& enumMap = model.Enums();

        CreateKind();

        std::vector<std::shared_ptr<EnumInfo>> enums;
        for (const auto& entry : enumMap)
        {
            enums.emplace_back(entry.second);
        }

        std::sort(enums.begin(), enums.end(), [](const auto& first, const auto& second) { return first->Name() < second->Name(); });

        for (const auto& enumInfo : enums)
        {
            CreateEnum(*enumInfo);
        }
    }

    void JavaEnumsGenerator::CreateEnum(const Metadata::EnumInfo& enumInfo)
    {
        JavaEnumGenerator enumGenerator(*this, enumInfo);
        enumGenerator.Run();
    }
    void JavaEnumsGenerator::CreateKind()
    {
        JavaKindGenerator kindGenerator(*this);
        kindGenerator.Run();
    }

}