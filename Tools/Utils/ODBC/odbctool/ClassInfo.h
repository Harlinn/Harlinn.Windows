#pragma once
#ifndef CLASSINFO_H_
#define CLASSINFO_H_

#include "MemberInfo.h"

namespace Harlinn::ODBC::Tool
{

    class ClassInfo : public std::enable_shared_from_this<ClassInfo>
    {
        std::weak_ptr<StorageInfo> owner_;
        WideString name_;
        std::weak_ptr<ClassInfo> baseClass_;
        std::vector<std::shared_ptr<MemberInfo>> members_;
    public:
        ClassInfo( const std::shared_ptr<StorageInfo>& owner, const WideString& name )
            : owner_( owner ), name_(name)
        { }

        std::shared_ptr<StorageInfo> Owner( ) const
        {
            return owner_.lock( );
        }

        const WideString& Name( ) const
        {
            return name_;
        }




    };
}


#endif
