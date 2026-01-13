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
#include "CodeGenerators/Cpp/CppHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void CppDataTypesTestGenerator::Run( )
    {
        const auto& cppOptions = Options( ).Owner( ).Owner( ).Owner( ).Cpp( );
        const auto& cppDataTypesOptions = cppOptions.Data( ).DataTypes( );
        auto cppOptionsNamespace = cppOptions.Namespace( L"::" );
        auto cppDataTypesOptionsNamespace = cppDataTypesOptions.Namespace( L"::" );
        WriteLine( L"#include <HCCIO.h>" );
        WriteLine( L"#include \"Types/DataTypes.h\"" );
        WriteLine( );
        WriteLine( L"#define BOOST_TEST_DYN_LINK" );
        WriteLine( L"#include <boost/test/unit_test.hpp>" );
        WriteLine( );
        WriteLine( L"using namespace Harlinn::Common;");
        WriteLine( L"using namespace Harlinn::ODBC;");
        WriteLine( L"using namespace Harlinn;" );
        WriteLine( L"using namespace {};", cppOptionsNamespace );
        WriteLine( L"using namespace {};", cppDataTypesOptionsNamespace );
        WriteLine( );
        WriteLine( L"class DataTypesLocalFixture");
        WriteLine( L"{");
        WriteLine( L"public:");
        WriteLine( L"    DataTypesLocalFixture( ) = default;");
        WriteLine( L"    ~DataTypesLocalFixture( ) = default;");
        WriteLine( L"};" );
        WriteLine( );

        WriteLine( L"BOOST_FIXTURE_TEST_SUITE( DataTypesTests, DataTypesLocalFixture )" );
        WriteLine( );
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                CreateSerializationTest( classInfo );
            }
        }
        WriteLine( L"BOOST_AUTO_TEST_SUITE_END( )" );

        Flush( );
    }

    void CppDataTypesTestGenerator::CreateSerializationTest( const ClassInfo& classInfo )
    {
        auto dataClassTypeName = CppHelper::GetDataType( classInfo );
        auto dataClassVariable1Name = dataClassTypeName.FirstToLower( ) + L"1";
        auto dataClassVariable2Name = dataClassTypeName.FirstToLower( ) + L"2";
        auto testName = dataClassTypeName + L"SerializationTest";

        auto members = classInfo.PersistentMembers( );

        
        WriteLine( L"// --run_test=DataTypesTests/{}", testName );
        WriteLine( L"BOOST_AUTO_TEST_CASE( {} )", testName );
        WriteLine( L"{" );
        WriteLine( L"    auto {} = std::make_shared<{}>( );", dataClassVariable1Name, dataClassTypeName );
        for ( const auto& member : members )
        {
            auto setterName = CppHelper::GetMemberSetterName( *member );
            auto value = CppHelper::GetSimpleTestValue( classInfo, *member );
            WriteLine( L"    {}->{}( {} );", dataClassVariable1Name, setterName, value );
        }
        WriteLine( );
        WriteLine( L"    IO::MemoryStream stream;");
        WriteLine( L"    IO::BinaryWriter destination( stream );");
        WriteLine( L"    WriteDataTo( *{}, destination );", dataClassVariable1Name );
        WriteLine( L"    stream.SetPosition( 0 );");
        WriteLine( L"    IO::BinaryReader source( stream );");
        WriteLine( );
        WriteLine( L"    auto {} = std::reinterpret_pointer_cast<{}>( ReadDataFrom( source ) );", dataClassVariable2Name, dataClassTypeName );
        WriteLine( L"    bool equal = {}->IsEqualTo( *{} );", dataClassVariable2Name, dataClassVariable1Name );
        WriteLine( L"    BOOST_CHECK( equal );" );

        WriteLine( L"}" );
        WriteLine( );
    }
}