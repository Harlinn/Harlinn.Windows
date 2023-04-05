#include "pch.h"
#include <hccfg/hccfg_node.h>
#include "hccfg_pathutil.h"
#include <boost/container/small_vector.hpp>

namespace Harlinn::Common::Config
{
    using namespace Harlinn::Common::Core;

	Reference<Node> Sequence::Find( const std::wstring_view& name ) const
	{
		boost::container::small_vector<wchar_t, 32> buffer;
		buffer.resize( name.length() + 1 );
		wmemcpy( buffer.data( ), name.data( ), name.length( ) );
		buffer[name.length( )] = 0;
		wchar_t* endPtr = nullptr;
		auto value = wcstoull( buffer.data( ), &endPtr, 10 );
		if ( buffer.data( ) != endPtr )
		{
			if ( value < items_.size( ) )
			{
				return items_[value];
			}
		}
		return {};
	}

	Reference<Element> Sequence::AddElement( const std::wstring_view& name )
	{
		return Add<Element>( name );
	}

	Reference<Sequence> Sequence::AddSequence( const std::wstring_view& name )
	{
		return Add<Sequence>( name );
	}

	Reference<BooleanValue> Sequence::AddBoolean( const std::wstring_view& name, bool value )
	{
		return Add<BooleanValue>( name, value );
	}
	Reference<CharValue> Sequence::AddChar( const std::wstring_view& name, char value )
	{
		return Add<CharValue>( name, value );
	}
	Reference<SByteValue> Sequence::AddSByte( const std::wstring_view& name, SByte value )
	{
		return Add<SByteValue>( name, value );
	}
	Reference<ByteValue> Sequence::AddByte( const std::wstring_view& name, Byte value )
	{
		return Add<ByteValue>( name, value );
	}
	Reference<WCharValue> Sequence::AddWChar( const std::wstring_view& name, wchar_t value )
	{
		return Add<WCharValue>( name, value );
	}
	Reference<Int16Value> Sequence::AddInt16( const std::wstring_view& name, Int16 value )
	{
		return Add<Int16Value>( name, value );
	}
	Reference<UInt16Value> Sequence::AddUInt16( const std::wstring_view& name, UInt16 value )
	{
		return Add<UInt16Value>( name, value );
	}
	Reference<Int32Value> Sequence::AddInt32( const std::wstring_view& name, Int32 value )
	{
		return Add<Int32Value>( name, value );
	}
	Reference<UInt32Value> Sequence::AddUInt32( const std::wstring_view& name, UInt32 value )
	{
		return Add<UInt32Value>( name, value );
	}
	Reference<Int64Value> Sequence::AddInt64( const std::wstring_view& name, Int64 value )
	{
		return Add<Int64Value>( name, value );
	}
	Reference<UInt64Value> Sequence::AddUInt64( const std::wstring_view& name, UInt64 value )
	{
		return Add<UInt64Value>( name, value );
	}
	Reference<SingleValue> Sequence::AddSingle( const std::wstring_view& name, Single value )
	{
		return Add<SingleValue>( name, value );
	}
	Reference<DoubleValue> Sequence::AddDouble( const std::wstring_view& name, Double value )
	{
		return Add<DoubleValue>( name, value );
	}
	Reference<TimeSpanValue> Sequence::AddTimeSpan( const std::wstring_view& name, TimeSpan value )
	{
		return Add<TimeSpanValue>( name, value );
	}
	Reference<DateTimeValue> Sequence::AddDateTime( const std::wstring_view& name, DateTime value )
	{
		return Add<DateTimeValue>( name, value );
	}
	Reference<CurrencyValue> Sequence::AddCurrency( const std::wstring_view& name, Currency value )
	{
		return Add<CurrencyValue>( name, value );
	}
	Reference<GuidValue> Sequence::AddGuid( const std::wstring_view& name, Guid value )
	{
		return Add<GuidValue>( name, value );
	}
	Reference<StringValue> Sequence::AddString( const std::wstring_view& name, const std::string& value )
	{
		return Add<StringValue>( name, value );
	}
	Reference<WideStringValue> Sequence::AddWideString( const std::wstring_view& name, const std::wstring& value )
	{
		return Add<WideStringValue>( name, value );
	}

	hcc::Reference<Node> Sequence::FindByPath( const std::wstring_view& path ) const
	{
		return Internal::FindByPath( this, path );
	}

}