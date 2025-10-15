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
    void JavaDataTypeFactoryGenerator::Run( )
    {
        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"package {};", nspace );
        WriteLine( );

        WriteLine( L"import java.util.List;" );
        WriteLine( L"import java.util.ArrayList;" );
        WriteLine( L"import com.harlinn.common.io.BinaryReader;" );
        WriteLine( L"import com.harlinn.common.io.BinaryWriter;" );
        WriteLine( L"import com.harlinn.common.types.AbstractDataObject;" );
        WriteLine( );

        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );


        WriteLine( L"public class DataObjectFactory implements com.harlinn.common.types.DataObjectFactory {" );
        WriteLine( L"    public AbstractDataObject create( int kind ) {" );
        WriteLine( L"        switch( kind ) {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto dataTypeName = JavaHelper::GetDataType( classInfo );

                WriteLine( L"            case Kind.{}:", classInfo.Name( ) );
                WriteLine( L"                return new {}( );", dataTypeName );
            }
        }
        WriteLine( L"            default:" );
        WriteLine( L"                throw new IllegalArgumentException( \"Cannot create an object for kind:\" + kind );" );
        WriteLine( L"        }" );
        WriteLine( L"    }" );
        WriteLine( L"    public AbstractDataObject readFrom(BinaryReader source) {" );
        WriteLine( L"        var kind = source.readInt32( );" );
        WriteLine( L"        var result = create( kind );" );
        WriteLine( L"        result.readFrom( source );" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( L"    public List<AbstractDataObject> readStreamFrom(BinaryReader source) {" );
        WriteLine( L"        var result = new ArrayList<AbstractDataObject>( );" );
        WriteLine( L"        while( source.readBoolean( ) ) {" );
        WriteLine( L"            var dataObject = readFrom( source );" );
        WriteLine( L"            result.add( dataObject );" );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( L"    public List<AbstractDataObject> readListFrom(BinaryReader source) {" );
        WriteLine( L"        var count = source.readInt32( );" );
        WriteLine( L"        var result = new ArrayList<AbstractDataObject>( count );" );
        WriteLine( L"        for( int i = 0; i < count; i++ ) {" );
        WriteLine( L"            var dataObject = readFrom( source );" );
        WriteLine( L"            result.add( dataObject );" );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( L"}" );
        WriteLine( );

        Flush( );
    }
}