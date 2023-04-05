#include "pch.h"
#include <hccfg/hccfg_node.h>

namespace Harlinn::Common::Config
{
	using namespace Harlinn::Common::Core;

	Node::~Node( ) = default;

	Reference<Node> Node::Find( const std::wstring_view& name ) const
	{
		return {};
	}
	Reference<Node> Node::FindByPath( const std::wstring_view& path ) const
	{
		if ( path.length( ) )
		{
			std::wstring_view sv = path;
			if ( sv.starts_with( L'/' ) )
			{
				sv.remove_prefix( 1 );
				auto root = Root( );
				if ( root )
				{
					return root->FindByPath( sv );
				}
			}
			else if ( sv.starts_with( L"../" ) )
			{
				sv.remove_prefix( 3 );
				if ( owner_ )
				{
					return owner_->FindByPath( sv );
				}
			}
			else if ( sv.starts_with( L"./" ) )
			{
				sv.remove_prefix( 2 );
				return this->FindByPath( sv );
			}
		}
		return {};
	}

}
