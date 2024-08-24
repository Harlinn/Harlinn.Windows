#pragma once
#ifndef HARLINN_COMMON_CORE_HCCDATA_H_
#define HARLINN_COMMON_CORE_HCCDATA_H_

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

#include "HCCDef.h"
#include "HCCBinaryReader.h"
#include "HCCBinaryWriter.h"

namespace Harlinn::Common::Core::Data
{
    enum class ObjectState : Byte
    {
        Unknown,
        New,
        Stored,
        Changed,
        Deleted,
        ConcurrencyConflict
    };

    template<typename ObjectT,typename KeyT>
        requires std::is_enum_v<ObjectT>
    class BaseData : public std::enable_shared_from_this<BaseData<ObjectT, KeyT>>
    {
    public:
        using Base = std::enable_shared_from_this<BaseData<ObjectT, KeyT>>;
        using ObjectType = ObjectT;
        using KeyType = KeyT;
        static constexpr ObjectType KIND = {};
    private:
        KeyType id_;
        ObjectState objectState_ = ObjectState::Unknown;
    public:
        constexpr BaseData( ) = default;
        virtual ~BaseData( ) = default;
    protected:
        void OnPropertyChanged( )
        {
            if ( objectState_ == ObjectState::Stored || objectState_ == ObjectState::ConcurrencyConflict )
            {
                objectState_ = ObjectState::Changed;
            }
        }
    public:
        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            auto typeCode = GetObjectType( );
            destination.Write( typeCode );
            destination.Write( objectState_ );
            destination.Write( id_ );
        }

        template<IO::StreamReader StreamT>
        static ObjectType ReadObjectType( IO::BinaryReader<StreamT>& source )
        {
            return source.Read<ObjectType>( );
        }

        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            objectState_ = source.Read<ObjectState>( );
            id_ = source.Read<KeyType>( );
        }


        virtual [[nodiscard]] ObjectType GetObjectType( ) const noexcept = 0;

        virtual [[nodiscard]] bool IsOfType( ObjectType objectType ) const noexcept
        {
            return objectType == KIND;
        }

        constexpr [[nodiscard]] Data::ObjectState ObjectState( ) const noexcept
        {
            return objectState_;
        }

        constexpr void SetObjectState( Data::ObjectState value ) noexcept
        {
            if ( objectState_ != value )
            {
                objectState_ = value;
            }
        }


        constexpr [[nodiscard]] const KeyType& Id( ) const noexcept
        {
            return id_;
        }
        void SetId( const KeyType& value ) noexcept
        {
            if ( id_ != value )
            {
                id_ = value;
            }
        }

        virtual [[nodiscard]] std::shared_ptr<BaseData> Create( ) const = 0;

        virtual [[nodiscard]] std::shared_ptr<BaseData> Clone( ) const
        {
            auto result = this->Create( );
            this->AssignTo( *result );
            return result;
        }

        virtual void AssignTo( BaseData& target ) const
        {
            target.objectState_ = objectState_;
            target.id_ = id_;
        }

        virtual [[nodiscard]] bool IsEqualTo( const BaseData& other ) const
        {
            return other.id_ == id_;
        }
    };

#define HCC_BOOLEAN_DATA_PROPERTY(propertyName,backingField) \
    bool propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( bool value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_SBYTE_DATA_PROPERTY(propertyName,backingField) \
    SByte propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( SByte value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_BYTE_DATA_PROPERTY(propertyName,backingField) \
    Byte propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Byte value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_INT16_DATA_PROPERTY(propertyName,backingField) \
    Int16 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int16 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_UINT16_DATA_PROPERTY(propertyName,backingField) \
    UInt16 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( UInt16 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_INT32_DATA_PROPERTY(propertyName,backingField) \
    Int32 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int32 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_UINT32_DATA_PROPERTY(propertyName,backingField) \
    UInt32 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( UInt32 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_INT64_DATA_PROPERTY(propertyName,backingField) \
    Int64 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int64 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_UINT64_DATA_PROPERTY(propertyName,backingField) \
    UInt64 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( UInt64 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_ENUM_DATA_PROPERTY(propertyName,backingField) \
    decltype(backingField) propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( decltype(backingField) value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_SINGLE_DATA_PROPERTY(propertyName,backingField) \
    float propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( float value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_DOUBLE_DATA_PROPERTY(propertyName,backingField) \
    double propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( double value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_CURRENCY_DATA_PROPERTY(propertyName,backingField) \
    const Currency& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Currency& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_DATETIME_DATA_PROPERTY(propertyName,backingField) \
    const DateTime& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const DateTime& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_TIMESPAN_DATA_PROPERTY(propertyName,backingField) \
    const TimeSpan& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const TimeSpan& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_GUID_DATA_PROPERTY(propertyName,backingField) \
    const Guid& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Guid& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_STRING_DATA_PROPERTY(propertyName,backingField) \
    const WideString& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const WideString& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_BINARY_DATA_PROPERTY(propertyName,backingField) \
    const std::vector<Byte>& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const std::vector<Byte>& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_ROWVERSION_DATA_PROPERTY(propertyName,backingField) \
    Int64 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int64 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_REFERENCE_DATA_PROPERTY(propertyName,backingField) \
    const Guid& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Guid& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_TIMESERIES_DATA_PROPERTY(propertyName,backingField) \
    const Guid& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Guid& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }



}


#endif
