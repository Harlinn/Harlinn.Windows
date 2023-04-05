#pragma once
#ifndef HARLINN_COMMON_CONFIG_HCCFG_PATHUTIL_H_
#define HARLINN_COMMON_CONFIG_HCCFG_PATHUTIL_H_

#include <hccfg/hccfg_node.h>

namespace Harlinn::Common::Config::Internal
{
    using namespace Harlinn::Common::Core;
    inline std::wstring_view FirstPathComponent( const std::wstring_view& path )
    {
        auto index = path.find( L'/' );
        if ( index != std::wstring_view::npos )
        {
            return std::wstring_view( path.data( ), index );
        }
        return path;
    }

    inline std::wstring_view RemainingPath( const std::wstring_view& path, const std::wstring_view& firstPathComponent )
    {
        if ( firstPathComponent.length( ) < path.length( ) )
        {
            auto remainingLength = path.length( ) - firstPathComponent.length( );
            const std::wstring_view::value_type* ptr = path.data( ) + firstPathComponent.length( );
            if ( *ptr == L'/' )
            {
                ptr++;
                --remainingLength;
            }
            return std::wstring_view( ptr, remainingLength );
        }
        return {};
    }

    inline hcc::Reference<Node> FindByPath(const Node* nodePtr, const std::wstring_view& path )
    {
        if ( nodePtr && path.length( ) )
        {
            std::wstring_view sv = path;
            if ( sv.length( ) )
            {
                auto firstComponent = FirstPathComponent( sv );
                auto remainingPath = RemainingPath( sv, firstComponent );
                if ( firstComponent == L".." )
                {
                    auto owner = nodePtr->Owner( );
                    if ( owner )
                    {
                        if ( remainingPath.length( ) == 0 )
                        {
                            return hcc::Reference<Node>( owner, true );
                        }
                        else
                        {
                            return owner->FindByPath( remainingPath );
                        }
                    }
                }
                else
                {
                    Reference<Node> childNode = nodePtr->Find( firstComponent );
                    if ( childNode )
                    {
                        if ( remainingPath.length( ) == 0 )
                        {
                            return childNode;
                        }
                        else
                        {
                            return childNode->FindByPath( remainingPath );
                        }
                    }
                }
            }
        }
        return {};
    }

}

#endif
