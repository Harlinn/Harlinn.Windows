#pragma once
#include "hccfg/hccfg_node.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common;


inline std::vector< Reference<Config::Element> > AddToElements( size_t num )
{
    std::vector< Reference<Config::Element> > result;
    auto root = Config::Root::Instance( );
    auto elements = root->Elements( );
    for ( size_t i = 0; i < num; ++i )
    {
        auto name = Format( L"R%zu", i );
        result.push_back( elements->AddElement( name ) );
    }
    return result;
}

inline void PopulateElement( Reference<Config::Element>& element, size_t recursionDepth, size_t sequenceSize = 10 );

inline void PopulateSequence( Reference<Config::Sequence>& sequence, size_t recursionDepth, size_t sequenceSize = 10 )
{
    for ( size_t i = 0; i < sequenceSize; ++i )
    {
        auto name = Format( L"S%zu", i );
        auto childSequence = sequence->AddSequence( name );
        childSequence->AddBoolean( L"Boolean" );
        childSequence->AddChar( L"Char" );
        childSequence->AddSByte( L"SByte" );
        childSequence->AddByte( L"Byte" );
        childSequence->AddWChar( L"WChar" );
        childSequence->AddInt16( L"Int16" );
        childSequence->AddUInt16( L"UInt16" );
        childSequence->AddInt32( L"Int32" );
        childSequence->AddUInt32( L"UInt32" );
        childSequence->AddInt64( L"Int64" );
        childSequence->AddUInt64( L"UInt64" );
        childSequence->AddSingle( L"Single" );
        childSequence->AddDouble( L"Double" );
        childSequence->AddTimeSpan( L"TimeSpan", TimeSpan::FromSeconds( 10 ) );
        childSequence->AddDateTime( L"DateTime", DateTime( 2021, 1, 1 ) );
        childSequence->AddCurrency( L"Currency" );
        childSequence->AddGuid( L"Guid", __uuidof( IPropertyBag ) );
        childSequence->AddString( L"String", "value" );
        childSequence->AddWideString( L"WideString", L"value" );
        if ( recursionDepth )
        {
            auto childElement = childSequence->AddElement( L"Element" );
            PopulateElement( childElement, recursionDepth - 1, sequenceSize );

            auto childSequence2 = childSequence->AddSequence( L"Sequence" );
            PopulateSequence( childSequence2, recursionDepth - 1, sequenceSize );
        }
    }
}


inline void PopulateElement( Reference<Config::Element>& element,  size_t recursionDepth, size_t sequenceSize )
{
    element->AddBoolean( L"Boolean" );
    element->AddChar( L"Char" );
    element->AddSByte( L"SByte" );
    element->AddByte( L"Byte" );
    element->AddWChar( L"WChar" );
    element->AddInt16( L"Int16" );
    element->AddUInt16( L"UInt16" );
    element->AddInt32( L"Int32" );
    element->AddUInt32( L"UInt32" );
    element->AddInt64( L"Int64" );
    element->AddUInt64( L"UInt64" );
    element->AddSingle( L"Single" );
    element->AddDouble( L"Double" );
    element->AddTimeSpan( L"TimeSpan", TimeSpan::FromSeconds(10) );
    element->AddDateTime( L"DateTime", DateTime(2021,1,1) );
    element->AddCurrency( L"Currency" );
    element->AddGuid( L"Guid", __uuidof( IPropertyBag ) );
    element->AddString( L"String", "value" );
    element->AddWideString( L"WideString", L"value" );
    if ( recursionDepth )
    {
        auto childElement = element->AddElement( L"Element" );
        PopulateElement( childElement, recursionDepth - 1, sequenceSize );

        auto childSequence = element->AddSequence( L"Sequence" );
        PopulateSequence( childSequence, recursionDepth - 1, sequenceSize );
    }
}


inline void GenerateTestData()
{
    auto elements = AddToElements( 10 );
    for ( auto& element : elements )
    {
        PopulateElement( element, 2, 10 );
    }
}



