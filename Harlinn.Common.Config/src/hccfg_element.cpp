#include "pch.h"
#include <hccfg/hccfg_node.h>
#include "hccfg_pathutil.h"
namespace Harlinn::Common::Config
{
	using namespace Harlinn::Common::Core;

	Reference<Element> Element::AddElement( const std::wstring_view& name )
	{
		return Add<Element>( name );
	}

	Reference<Sequence> Element::AddSequence( const std::wstring_view& name )
	{
		return Add<Sequence>( name );
	}

	Reference<BooleanValue> Element::AddBoolean( const std::wstring_view& name, bool value )
	{ 
		return Add<BooleanValue>( name, value );
	}
	Reference<CharValue> Element::AddChar( const std::wstring_view& name, char value )
	{
		return Add<CharValue>( name, value );
	}
	Reference<SByteValue> Element::AddSByte( const std::wstring_view& name, SByte value )
	{
		return Add<SByteValue>( name, value );
	}
	Reference<ByteValue> Element::AddByte( const std::wstring_view& name, Byte value )
	{
		return Add<ByteValue>( name, value );
	}
	Reference<WCharValue> Element::AddWChar( const std::wstring_view& name, wchar_t value )
	{
		return Add<WCharValue>( name, value );
	}
	Reference<Int16Value> Element::AddInt16( const std::wstring_view& name, Int16 value )
	{
		return Add<Int16Value>( name, value );
	}
	Reference<UInt16Value> Element::AddUInt16( const std::wstring_view& name, UInt16 value )
	{
		return Add<UInt16Value>( name, value );
	}
	Reference<Int32Value> Element::AddInt32( const std::wstring_view& name, Int32 value )
	{
		return Add<Int32Value>( name, value );
	}
	Reference<UInt32Value> Element::AddUInt32( const std::wstring_view& name, UInt32 value )
	{
		return Add<UInt32Value>( name, value );
	}
	Reference<Int64Value> Element::AddInt64( const std::wstring_view& name, Int64 value )
	{
		return Add<Int64Value>( name, value );
	}
	Reference<UInt64Value> Element::AddUInt64( const std::wstring_view& name, UInt64 value )
	{
		return Add<UInt64Value>( name, value );
	}
	Reference<SingleValue> Element::AddSingle( const std::wstring_view& name, Single value )
	{
		return Add<SingleValue>( name, value );
	}
	Reference<DoubleValue> Element::AddDouble( const std::wstring_view& name, Double value )
	{
		return Add<DoubleValue>( name, value );
	}
	Reference<TimeSpanValue> Element::AddTimeSpan( const std::wstring_view& name, TimeSpan value )
	{
		return Add<TimeSpanValue>( name, value );
	}
	Reference<DateTimeValue> Element::AddDateTime( const std::wstring_view& name, DateTime value )
	{
		return Add<DateTimeValue>( name, value );
	}
	Reference<CurrencyValue> Element::AddCurrency( const std::wstring_view& name, Currency value )
	{
		return Add<CurrencyValue>( name, value );
	}
	Reference<GuidValue> Element::AddGuid( const std::wstring_view& name, Guid value )
	{
		return Add<GuidValue>( name, value );
	}
	Reference<StringValue> Element::AddString( const std::wstring_view& name, const std::string& value )
	{
		return Add<StringValue>( name, value );
	}
	Reference<WideStringValue> Element::AddWideString( const std::wstring_view& name, const std::wstring& value )
	{
		return Add<WideStringValue>( name, value );
	}

	hcc::Reference<Node> Element::FindByPath( const std::wstring_view& path ) const
	{
		return Internal::FindByPath( this, path );
	}

}