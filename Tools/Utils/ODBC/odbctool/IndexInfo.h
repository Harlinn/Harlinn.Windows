#pragma once
#ifndef INDEXINFO_H_
#define INDEXINFO_H_

/*
   Copyright 2024 Espen Harlinn

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

#include "MemberInfo.h"

namespace Harlinn::ODBC::Tool
{
    class IndexInfo : public std::enable_shared_from_this<IndexInfo>
    {
        std::weak_ptr<ClassInfo> owner_;
        WideString name_;
        bool unique_ = false;
        bool range_ = false;
        WideString fieldNames_;
        std::vector<std::shared_ptr<MemberInfo>> fields_;
    public:
        IndexInfo( const std::shared_ptr<ClassInfo>& owner, const WideString& name )
            : owner_( owner ), name_( name )
        {
        }

        std::shared_ptr<Tool::ClassInfo> Owner( ) const
        {
            return owner_.lock( );
        }
        const WideString& Name( ) const
        {
            return name_;
        }

        bool Unique( ) const
        {
            return unique_;
        }
        bool Range( ) const
        {
            return range_;
        }

        const std::vector<std::shared_ptr<MemberInfo>>& Fields( ) const
        {
            return fields_;
        }


        void Load( const XmlElement& indexElement );
        void AfterLoad( );

    };

}

#endif
