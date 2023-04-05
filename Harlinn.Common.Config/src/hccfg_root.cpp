#include "pch.h"
#include <hccfg/hccfg_node.h>
#include "hccfg_pathutil.h"

namespace Harlinn::Common::Config
{
	using namespace Harlinn::Common::Core;
	namespace
	{
		CriticalSection rootCriticalSection;
		Reference<Root> root;
	}

	Root::~Root( ) = default;

	Reference<Root> Root::Instance( )
	{
		if ( !root )
		{
			std::unique_lock lock( rootCriticalSection );
			if ( !root )
			{
				root.reset( new Root() );
			}
		}
		return root;
	}

	void Root::Reset( )
	{
		std::unique_lock lock( rootCriticalSection );
		root.reset( );
	}

	const Reference<Config::Elements>& Root::Elements( ) const
	{
		if ( !elements_ )
		{
			std::unique_lock lock( rootCriticalSection );
			if ( !elements_ )
			{
				elements_.reset( new Config::Elements( const_cast<Root*>( this ) ) );
			}
		}
		return elements_;
	}

	const Reference<Config::Environment>& Root::Environment( ) const
	{
		if ( !environment_ )
		{
			std::unique_lock lock( rootCriticalSection );
			if ( !environment_ )
			{
				environment_.reset( new Config::Environment( const_cast<Root*>( this ) ) );
			}
		}
		return environment_;
	}

	hcc::Reference<Node> Root::Find( const std::wstring_view& name ) const
	{
		static std::wstring_view environmentName = L"Environment";
		static std::wstring_view elementsName = L"Elements";
		if ( name == elementsName )
		{
			return Elements( );
		}
		else if ( name == environmentName )
		{
			return Environment( );
		}
		else
		{
			return Base::Find( name );
		}
	}


	hcc::Reference<Node> Root::FindByPath( const std::wstring_view& path ) const
	{
		if ( path.length( ) )
		{
			std::wstring_view sv = path;
			if ( sv.starts_with( L'/' ) )
			{
				sv.remove_prefix( 1 );
			}
			if ( sv.length( ) )
			{
				static std::wstring_view environmentName = L"Environment";
				static std::wstring_view elementsName = L"Elements";
				auto firstComponent = Internal::FirstPathComponent( sv );
				if ( firstComponent == elementsName )
				{
					auto remainingPath = Internal::RemainingPath( sv, firstComponent );
					const auto& elements = Elements( );
					if ( remainingPath.length( ) )
					{
						hcc::Reference<Node> result( elements->FindByPath( remainingPath ) );
						return result;
					}
					else
					{
						return elements;
					}
				}
				else if ( firstComponent == environmentName )
				{
					auto remainingPath = Internal::RemainingPath( sv, firstComponent );
					const auto& environment = Environment( );
					if ( remainingPath.length( ) )
					{
						hcc::Reference<Node> result( environment->FindByPath( remainingPath ) );
						return result;
					}
					else
					{
						return environment;
					}
				}
				else
				{
					return {};
				}
			}
			return hcc::Reference<Node>( const_cast<Root*>( this ), true );
		}
		return {};
	}

}
