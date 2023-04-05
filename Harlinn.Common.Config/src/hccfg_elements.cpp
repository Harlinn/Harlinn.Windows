#include "pch.h"
#include <hccfg/hccfg_node.h>
#include "hccfg_pathutil.h"

namespace Harlinn::Common::Config
{
	using namespace Harlinn::Common::Core;
	Reference<Element> Elements::AddElement( const std::wstring_view& name )
	{
		Reference<Element> result;
		WriterLock lock( mutex_ );
		auto it = items_.find( name );
		if ( it == items_.end( ) )
		{
			result.reset( new Element( this, name ) );
			std::wstring_view sv = result->Name( );
			items_.emplace( sv, result );
		}
		else
		{
			auto result = it->second;
			if ( result->Type( ) != NodeType::Element )
			{
				HCC_THROW( Exception, L"Unexpected node type" );
			}
		}
		return result;
	}

	hcc::Reference<Node> Elements::FindByPath( const std::wstring_view& path ) const
	{
		return Internal::FindByPath( this, path );
	}

}