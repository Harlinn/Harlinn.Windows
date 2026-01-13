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
#include "HCCStringBuilder.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    using namespace Metadata;
    namespace
    {
        std::vector<std::shared_ptr<Metadata::ClassInfo>> SortClassesByRequiredDependencies( const std::vector<std::shared_ptr<Metadata::ClassInfo>>& classes )
        {
            std::map<WideString, int> inDegree; // Number of incoming dependencies for each class
            std::map<WideString, std::set<std::shared_ptr<Metadata::ClassInfo>>> adjList; // Adjacency list for dependencies

            // Initialize in-degrees and build adjacency list
            for ( const auto& entry : classes )
            {
                // Initialize all in-degrees to 0
                inDegree[ entry->Name( ) ] = 0;
            }
            for ( const auto& entry : classes )
            {
                const auto& dependencies = entry->RequiredDependencies( );
                for ( const auto& dep : dependencies )
                {
                    // If cls depends on dep, then dep has an edge to cls
                    adjList[ dep->Name( ) ].insert( entry );
                    inDegree[ entry->Name( ) ]++;
                }
            }

            std::vector<std::shared_ptr<Metadata::ClassInfo>> sortedClasses;
            std::vector<std::shared_ptr<Metadata::ClassInfo>> queue; // Classes with no incoming dependencies

            // Add classes with in-degree 0 to the queue
            for ( const auto& cls : classes )
            {
                if ( inDegree[ cls->Name() ] == 0 )
                {
                    queue.push_back( cls );
                }
            }

            while ( !queue.empty( ) )
            {
                auto currentClass = queue.front( );
                queue.erase( queue.begin( ) ); // Dequeue
                auto it = std::ranges::find_if( sortedClasses, [&currentClass ]( const auto& element )
                                                {
                                                    return element->Name( ) == currentClass->Name( );
                                                } );
                if ( it == sortedClasses.end( ) )
                {
                    sortedClasses.push_back( currentClass );
                }

                /*
                // Partial handling of circular dependencies
                if ( it != sortedClasses.end( ) )
                {
                    sortedClasses.erase( it );
                }
                sortedClasses.push_back( currentClass );
                */

                // For each class that depends on currentClass
                if ( adjList.count( currentClass->Name( ) ) )
                {
                    for ( const auto& dependentClass : adjList[ currentClass->Name( ) ] )
                    {
                        inDegree[ dependentClass->Name( ) ]--;
                        if ( inDegree[ dependentClass->Name( ) ] == 0 )
                        {
                            queue.push_back( dependentClass );
                        }
                    }
                }
            }

            std::vector<std::shared_ptr<Metadata::ClassInfo>> missing;
            for ( const auto& cls : classes )
            {
                auto it = std::ranges::find_if( sortedClasses, [ &cls ]( const auto& element )
                                                {
                                                    return element->Name( ) == cls->Name( );
                                                } );
                if ( it == sortedClasses.end( ) )
                {
                    missing.push_back( cls );
                }
            }

            sortedClasses.insert_range( sortedClasses.end( ), missing );



            // Check for cycles (if sortedClasses.size() != classes.size(), there's a cycle)
            if ( sortedClasses.size( ) != classes.size( ) )
            {
                std::cerr << "Error: Circular dependency detected!" << std::endl;
                return {}; // Return empty or handle error appropriately
            }

            return sortedClasses;
        }
    }

    void JavaTestDataObjectFactoryGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"package {};", nspace );
        WriteLine( );
        WriteLine( L"import com.harlinn.common.types.*;" );
        WriteLine( L"import com.harlinn.common.util.*;" );
        WriteLine( );
        auto className = JavaHelper::GetTestDataObjectFactory( );
        WriteLine( L"public class {} {{", className );
        WriteLine( );

        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                const auto& name = classInfo->Name( );
                WriteLine( L"    public final static Guid {}PrimaryKey = new Guid(Kind.{},(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);", name, name );
            }
        }
        WriteLine( );

        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                const auto& name = classInfo->Name( );
                const auto dataObjectClassName = JavaHelper::GetDataType( *classInfo );
                WriteLine( L"    private {} _{} = null;", dataObjectClassName, name.FirstToLower() );
            }
        }

        WriteLine( );

        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                const auto& name = classInfo->Name( );
                const auto dataObjectClassName = JavaHelper::GetDataType( *classInfo );
                WriteLine( L"    public {} get{}() {{", dataObjectClassName, name );
                WriteLine( L"        if (_{} == null) {{", name.FirstToLower( ) );
                const auto& members = classInfo->PersistentMembers( );
                auto memberCount = members.size( );
                StringBuilder<wchar_t> sb;
                sb.Append(L"ObjectState.New, {}PrimaryKey", name );
                for ( size_t i = 0; i < memberCount; i++ )
                {
                    const auto& member = members[ i ];
                    if ( member->PrimaryKey( ) == false )
                    {
                        auto typeName = JavaHelper::GetMemberFieldType( *member );
                        auto variableName = JavaHelper::GetInputArgumentName( *member );
                        auto defaultValue = JavaHelper::JavaHelper::GetDefaultValue( *member );
                        if ( member->Nullable( ) == false )
                        {
                            auto memberType = member->Type( );
                            if ( memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries )
                            {
                                const ReferenceMemberInfo& reference = static_cast<const ReferenceMemberInfo&>( *member );
                                std::shared_ptr<ClassInfo> referencedType = reference.ReferencedType( )->ConcreteClass( );
                                defaultValue = Format( L"{}PrimaryKey", referencedType->Name( ) );
                            }
                            else if ( memberType == MemberInfoType::String )
                            {
                                const StringMemberInfo& stringMemberInfo = static_cast<const StringMemberInfo&>( *member );
                                defaultValue = Format( L"\"{}{}UnitTest\"", member->Name(), name );
                                if ( stringMemberInfo.Size( ) && defaultValue.length( ) > stringMemberInfo.Size( ) )
                                {
                                    defaultValue = defaultValue.substr(0, stringMemberInfo.Size( ) - 1 ) + '\"';
                                }
                            }
                            else if ( memberType == MemberInfoType::DateTime )
                            {
                                defaultValue = L"new DateTime(2025,10,18,9,0,0)";
                            }
                        }
                        WriteLine( L"            {} {} = {};", typeName, variableName, defaultValue );

                        sb.Append( L", {}", variableName );
                    }
                }
                WriteLine( );
                WriteLine( L"            _{} = new {}( {} );", name.FirstToLower( ), dataObjectClassName, sb.ToString( ) );
                WriteLine( L"        }" );
                WriteLine( L"        return _{};", name.FirstToLower( ) );
                WriteLine( L"    }" );
                WriteLine( );
            }
        }

        WriteLine( );

        auto sortedClasses = SortClassesByRequiredDependencies( classes );

        StringBuilder<wchar_t> sb;
        bool isFirst = true;
        for ( const auto& classInfo : sortedClasses )
        {
            if ( classInfo->Abstract( ) == false )
            {
                const auto& name = classInfo->Name( );
                if ( isFirst )
                {
                    isFirst = false;
                }
                else
                {
                    sb.AppendLine( L"," );
                }
                sb.Append( L"            get{}( )", name );
            }
        }
        sb.AppendLine( );



        WriteLine( L"    public AbstractDataObjectWithGuidKey[] getDataObjects() {" );
        WriteLine( L"        AbstractDataObjectWithGuidKey[] result = {" );
        WriteLine( sb.ToString( ) );
        WriteLine( L"        };" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );

        WriteLine( L"/*" );
        for ( const auto& classInfo : sortedClasses )
        {
            if ( classInfo->Abstract( ) )
            {
                WriteLine( L"{} is abstract", classInfo->Name( ) );
            }
            else
            {
                WriteLine( classInfo->Name( ) );
            }
            const auto& dependencies = classInfo->RequiredDependencies( );
            if ( dependencies.empty( ) )
            {
                WriteLine(L"    <no dependencies>");
            }
            else
            {
                for ( const auto& dep : dependencies )
                {
                    WriteLine( L"    {}", dep->Name() );
                }
            }
        }
        WriteLine( L"*/" );



        WriteLine( L"}");
        Flush( );

    }
}