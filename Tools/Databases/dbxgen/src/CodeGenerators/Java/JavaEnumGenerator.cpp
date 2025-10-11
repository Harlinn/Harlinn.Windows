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
    void JavaEnumGenerator::Run()
    {
        auto nspace = Options().Namespace(L".");
        WriteLine(L"package {};", nspace);
        WriteLine();

        WideString enumName(enumInfo_.Name());

        auto underlyingType = JavaHelper::GetUnderlyingType(enumInfo_);
        auto toIntMethodName = JavaHelper::GetToIntMethodName( enumInfo_ );
        const auto& enumValues = enumInfo_.Values();
        auto valueCount = enumValues.size();

        WriteLine(L"public class {} {{", enumName);
        for (size_t i = 0; i < valueCount; i++)
        {
            const auto& enumValue = *enumValues[i];
            WriteLine(L"    public final static {} {} = {};", underlyingType, enumValue.Name(), enumValue.Value());
        }
        WriteLine();

        WriteLine( L"    public final static String toString({} value) {{", underlyingType );
        WriteLine( L"    	switch(value) {" );

        std::set<Int64> switchConstants;
        for ( size_t i = 0; i < valueCount; i++ )
        {
            const auto& enumValue = *enumValues[ i ];
            if ( switchConstants.contains( enumValue.Value( ) ) == false )
            {
                switchConstants.insert( enumValue.Value( ) );
                WriteLine( L"    	    case {}:", enumValue.Name( ) );
                WriteLine( L"    	        return \"{}\";", enumValue.Name( ) );
            }
        }
        WriteLine( L"    	    default:" );
        WriteLine( L"    	        throw new IllegalArgumentException( \"Unknown {} constant:\" + Integer.toUnsignedString(value, 10) );", enumName );
        WriteLine( L"    	}" );
        WriteLine( L"    }" );
        WriteLine( );

        WriteLine( L"    public final static {} {}(String value) {{", underlyingType, toIntMethodName );
        WriteLine( L"    	switch(value) {" );
        for ( size_t i = 0; i < valueCount; i++ )
        {
            const auto& enumValue = *enumValues[ i ];
            WriteLine( L"    	    case \"{}\":", enumValue.Name( ) );
            WriteLine( L"    	        return {};", enumValue.Name( ) );
        }
        WriteLine( L"    	    default:" );
        WriteLine( L"    	        throw new IllegalArgumentException( \"Unknown {} constant name:\" + value );", enumName );
        WriteLine( L"    	}" );
        WriteLine( L"    }" );
        WriteLine( );

        WriteLine(L"}");
        WriteLine();

        Flush();
    }
}