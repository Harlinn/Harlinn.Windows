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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/Java/JavaHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    void JavaKindGenerator::Run()
    {
        const auto& model = Model();
        const auto& classes = model.Classes();

        auto nspace = Options().Namespace(L".");
        WriteLine(L"package {};", nspace);
        WriteLine();


        WideString enumName(L"Kind");


        WriteLine(L"public class {} {{", enumName);
        WriteLine(L"    public final static int Unknown = 0;");
        auto classCount = classes.size();
        for (size_t i = 0; i < classCount; i++)
        {
            const auto& classInfo = *classes[i];
            WriteLine(L"    public final static int {} = {};", classInfo.Name(), classInfo.Id());
        }
        WriteLine();
        WriteLine(L"    public final static String toString(int value) {");
        WriteLine(L"    	switch(value) {");
        WriteLine(L"    	    case Unknown:");
        WriteLine(L"    	        return \"Unknown\";");
        for (size_t i = 0; i < classCount; i++)
        {
            const auto& classInfo = *classes[i];
            WriteLine(L"    	    case {}:", classInfo.Name());
            WriteLine(L"    	        return \"{}\";", classInfo.Name());
        }
        WriteLine(L"    	    default:");
        WriteLine(L"    	        return \"Unknown(\" + Integer.toUnsignedString(value, 10) + \")\";");
        WriteLine(L"    	}");
        WriteLine(L"    }");
        WriteLine();
        WriteLine(L"    public final static int toInt(String value) {");
        WriteLine(L"    	switch(value) {");
        WriteLine(L"    	    case \"Unknown\":");
        WriteLine(L"    	        return Unknown;");
        for (size_t i = 0; i < classCount; i++)
        {
            const auto& classInfo = *classes[i];
            WriteLine(L"    	    case \"{}\":", classInfo.Name());
            WriteLine(L"    	        return {};", classInfo.Name());
        }
        WriteLine(L"    	    default:");
        WriteLine(L"    	        return Unknown;");
        WriteLine(L"    	}");
        WriteLine(L"    }");
        WriteLine();
        WriteLine(L"}");
        WriteLine();

        Flush();
    }
}