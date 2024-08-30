#pragma once
#ifndef CLASSINFO_H_
#define CLASSINFO_H_
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

#include "IndexInfo.h"

namespace Harlinn::ODBC::Tool
{


    class ClassInfo : public std::enable_shared_from_this<ClassInfo>
    {
        std::weak_ptr<ModelInfo> owner_;
        WideString name_;
        mutable WideString shortName_;
        int id_ = 0;
        bool abstract_ = false;
        ODBC::Guid guid_;
        WideString displayName_;
        WideString description_;
        std::weak_ptr<ClassInfo> baseClass_;
        std::vector<std::shared_ptr<MemberInfo>> ownMembers_;
        std::unordered_map<WideString,std::shared_ptr<MemberInfo>> ownMembersByName_;
        std::vector<std::shared_ptr<MemberInfo>> ownPersistentMembers_;
        std::unordered_map<WideString, std::shared_ptr<MemberInfo>> ownPersistentMembersByName_;

        std::vector<std::shared_ptr<MemberInfo>> members_;
        std::unordered_map<WideString, std::shared_ptr<MemberInfo>> membersByName_;
        std::vector<std::shared_ptr<MemberInfo>> persistentMembers_;
        std::unordered_map<WideString, std::shared_ptr<MemberInfo>> persistentMembersByName_;

        std::vector<std::shared_ptr<MemberInfo>> viewMembers_;

        std::vector<std::shared_ptr<ClassInfo>> derivedClasses_;
        std::shared_ptr<MemberInfo> primaryKey_;
        std::shared_ptr<RowVersionMemberInfo> rowVersion_;
        std::vector<std::shared_ptr<IndexInfo>> indexes_;
    public:
        ClassInfo( const std::shared_ptr<ModelInfo>& owner, const WideString& name )
            : owner_( owner ), name_(name)
        { }

        std::shared_ptr<ModelInfo> Owner( ) const
        {
            return owner_.lock( );
        }

        const WideString& Name( ) const
        {
            return name_;
        }

        const WideString& ShortName( ) const;

        int Id( ) const
        {
            return id_;
        }
        void SetId( int id )
        {
            id_ = id;
        }



        bool Abstract( ) const
        {
            return abstract_;
        }

        std::shared_ptr<ClassInfo> BaseClass( ) const
        {
            return baseClass_.lock( );
        }

        bool IsTopLevel( ) const
        {
            return baseClass_.lock( ) == nullptr;
        }

        bool IsValidType( ) const
        {
            if ( IsTopLevel( ) == false )
            {
                return false;
            }
            for ( const auto& member : ownMembers_ )
            {
                auto type = member->Type( );
                if ( type < MemberInfoType::Boolean || type > MemberInfoType::Type )
                {
                    return false;
                }
            }
            return true;
        }

        const WideString& DisplayName( ) const
        {
            return displayName_;
        }
        const WideString& Description( ) const
        {
            return description_;
        }

        const std::vector<std::shared_ptr<MemberInfo>>& OwnMembers( ) const
        {
            return ownMembers_;
        }

        std::shared_ptr<MemberInfo> FindOwnMember( const WideString& memberName ) const
        {
            auto it = ownMembersByName_.find( memberName );
            if ( it != ownMembersByName_.end( ) )
            {
                return it->second;
            }
            return {};
        }


        const std::vector<std::shared_ptr<MemberInfo>>& OwnPersistentMembers( ) const
        {
            return ownPersistentMembers_;
        }

        std::shared_ptr<MemberInfo> FindOwnPersistentMember( const WideString& memberName ) const
        {
            auto it = ownPersistentMembersByName_.find( memberName );
            if ( it != ownPersistentMembersByName_.end( ) )
            {
                return it->second;
            }
            return {};
        }


        const std::vector<std::shared_ptr<MemberInfo>>& Members( ) const
        {
            return members_;
        }
        const std::unordered_map<WideString, std::shared_ptr<MemberInfo>>& MembersByName( ) const
        {
            return membersByName_;
        }
        const std::vector<std::shared_ptr<MemberInfo>>& PersistentMembers( ) const
        {
            return persistentMembers_;
        }
        const std::unordered_map<WideString, std::shared_ptr<MemberInfo>>& PersistentMembersByName( ) const
        {
            return persistentMembersByName_;
        }


        const std::vector<std::shared_ptr<MemberInfo>> ViewMembers( ) const
        {
            return viewMembers_;
        }


        const std::vector<std::shared_ptr<ClassInfo>>& DerivedClasses( ) const
        {
            return derivedClasses_;
        }

        bool HasDescendants( ) const
        {
            return derivedClasses_.empty() == false;
        }


        const std::vector<std::shared_ptr<IndexInfo>>& Indexes( ) const
        {
            return indexes_;
        }

        const std::shared_ptr<MemberInfo> PrimaryKey( ) const
        {
            if ( primaryKey_ )
            {
                return primaryKey_;
            }
            auto baseClass = BaseClass( );
            if ( baseClass )
            {
                return baseClass->PrimaryKey( );
            }
            return {};
        }

        const std::shared_ptr<RowVersionMemberInfo> RowVersion( ) const
        {
            if ( rowVersion_ )
            {
                return rowVersion_;
            }
            auto baseClass = BaseClass( );
            if ( baseClass )
            {
                return baseClass->RowVersion( );
            }
            return {};
        }


        std::shared_ptr<ClassInfo> TopLevelClass( ) const;
        std::vector<std::shared_ptr<ClassInfo>> BaseClasses( ) const;
        std::vector<std::shared_ptr<ClassInfo>> BaseClassesAndSelf( ) const;
        std::vector<std::shared_ptr<ClassInfo>> AllDerivedClasses( ) const;
        std::vector<std::shared_ptr<ClassInfo>> AllDerivedClassesAndSelf( ) const;
        void Load( const XmlElement& classElement );
        void AfterLoad( );
        void AddDerivedClassesToClassList( std::vector<std::shared_ptr<ClassInfo>>& classList ) const;

        bool HasDerivedPersistentMembers( ) const;
        std::vector<std::shared_ptr<MemberInfo>> DerivedPersistentMembersUntil( const ClassInfo& classInfo ) const;
        void DerivedPersistentMembersUntil( const ClassInfo& classInfo, std::vector<std::shared_ptr<MemberInfo>>& result ) const;

        bool IsViewMember( const MemberInfo& member ) const
        {
            auto owner = member.Owner( );
            if ( owner->Id( ) == Id( ) )
            {
                return true;
            }
            auto baseClass = BaseClass( );
            if ( baseClass )
            {
                return baseClass->IsViewMember( member );
            }
            return false;
        }

    private:
        void LoadMembers( const XmlElement& membersElement );
        void AddDerivedClass( const std::shared_ptr<ClassInfo>& derivedClass );
        



    };
}


#endif
