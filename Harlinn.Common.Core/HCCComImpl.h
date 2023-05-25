#pragma once
#ifndef HARLINN_COMMON_CORE_HCCCOMIMPL_H_
#define HARLINN_COMMON_CORE_HCCCOMIMPL_H_

#include <HCCObj.h>
#include <HCCSync.h>

namespace Harlinn::Common::Core::Com
{
    

    /// <summary>
    /// Base class for COM object implementations, it implements
    /// <code>
    /// virtual HRESULT __stdcall QueryInterface( const IID& iid, void** result ) override;
    /// </code>
    /// on behalf of derived templates.
    /// </summary>
    /// <typeparam name="DerivedT">
    /// The type that gets instantiated.
    /// </typeparam>
    /// <typeparam name="...InterfaceTypes">
    /// <p>
    /// The list of COM interfaces that is implemented by DerivedT that DerivedT can be 
    /// unambiguously be cast to. This means that no interface can be derived from any
    /// other interface that is part of this parameter pack.
    /// </p>
    /// <p>
    /// Interface inheritance is implemented through specializations of
    /// 
    /// </p>
    /// </typeparam>
    template<typename DerivedT, typename ... InterfaceTypes >
    class __declspec( novtable ) Interfaces //: public InterfaceTypes...
    {
    public:
        using DerivedType = DerivedT;
    private:
        template<typename InterfaceType, typename ...RemainingInterfaceTypes>
        void* QueryItf( const Guid& iid ) const
        {
            using Itf = Com::Interface<InterfaceType>;
            const DerivedType* self = static_cast<const DerivedType*>( this );
            auto* ptr = Itf::QueryInterface( iid, static_cast<const InterfaceType*>(self) );
            if ( !ptr )
            {
                if constexpr ( sizeof...( RemainingInterfaceTypes ) > 0 )
                {
                    ptr = QueryItf<RemainingInterfaceTypes...>( iid );
                }
            }
            return ptr;
        }
    public:
        HRESULT QueryInterfaceImpl( const IID& iid, void** result, bool addRef = true )
        {
            if ( !result )
            {
                return E_POINTER;
            }
            void* ptr = QueryItf<InterfaceTypes...>( iid );
            if ( ptr )
            {
                *result = ptr;
                if ( addRef )
                {
                    DerivedType* self = static_cast< DerivedType* >( this );
                    self->AddRef( );
                }
                return S_OK;
            }
            else
            {
                *result = nullptr;
                return E_NOINTERFACE;
            }
        }
    };


    template<typename DerivedT, typename ... InterfaceTypes>
    class ObjectBase : public Interfaces<DerivedT, InterfaceTypes...>
    {
        ULONG referenceCount_ = 1;
    public:
        using Base = Interfaces<DerivedT, InterfaceTypes...>;
        using DerivedType = DerivedT;

        virtual ~ObjectBase( ) = default;

        HRESULT __stdcall QueryInterface( const IID& iid, void** result )
        {
            auto& self = *static_cast< DerivedType* >( this );
            return self.QueryInterfaceImpl( iid, result );
        }

        ULONG __stdcall AddRef( )
        {
            auto& self = *static_cast< DerivedType* >( this );
            return self.AddRefImpl( );
        }

        ULONG __stdcall Release( )
        {
            auto& self = *static_cast< DerivedType* >( this );
            return self.ReleaseImpl( );
        }

        ULONG AddRefImpl( )
        {
            ULONG result = InterlockedIncrement( &referenceCount_ );
            return result;
        }

        ULONG ReleaseImpl( )
        {
            ULONG result = InterlockedDecrement( &referenceCount_ );
            if ( result == 0 )
            {
                delete this;
            }
            return result;
        }
    };







    template<typename DerivedT, typename InterfaceT>
    class __declspec( novtable ) IUknownImpl : public InterfaceT
    {
    public:
        using DerivedType = DerivedT;
        using InterfaceType = IUnknown;

        virtual HRESULT __stdcall QueryInterface( const IID& iid, void** result ) override
        {
            auto& self = *static_cast< DerivedType* >( this );
            return self.QueryInterfaceImpl( iid, result );
        }

        virtual ULONG __stdcall AddRef( ) override
        {
            auto& self = *static_cast< DerivedType* >( this );
            return self.AddRefImpl( );
        }

        virtual ULONG __stdcall Release( ) override
        {
            auto& self = *static_cast< DerivedType* >( this );
            return self.ReleaseImpl( );
        }

    };


    template<typename DerivedT, typename InterfaceT>
    class __declspec( novtable ) IDispatchImpl : public IUknownImpl<DerivedT, InterfaceT>
    {
        TypeInfo typeInfo_;
    public:
        using DerivedType = DerivedT;
        using InterfaceType = IDispatch;

        IDispatchImpl( const TypeInfo& typeInfo )
            : typeInfo_( typeInfo )
        { }
        IDispatchImpl( TypeInfo&& typeInfo )
            : typeInfo_( std::move(typeInfo) )
        { }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="pctinfo">
        /// The number of type information interfaces provided by the object. 
        /// If the object provides type information, this number is 1; otherwise 
        /// the number is 0.
        /// </param>
        /// <returns></returns>
        virtual HRESULT __stdcall GetTypeInfoCount( UINT* result )
        {
            if ( result )
            {
                if ( typeInfo_ )
                {
                    *result = 1;
                }
                else
                {
                    *result = 0;
                }
                return S_OK;
            }
            else
            {
                return E_POINTER;
            }
        }

        /// <summary>
        /// Retrieves the type information for an object, 
        /// which can then be used to get the type information 
        /// for an interface.
        /// </summary>
        /// <param name="typeInfoIndex">
        /// The type information to return. Pass 0 to retrieve type 
        /// information for the IDispatch implementation.
        /// </param>
        /// <param name="localeId">
        /// The locale identifier for the type information. An object may be 
        /// able to return different type information for different languages. 
        /// This is important for classes that support localized member names. 
        /// For classes that do not support localized member names, this 
        /// parameter can be ignored.
        /// </param>
        /// <param name="typeInfo">
        /// The requested type information object.
        /// </param>
        /// <returns></returns>
        virtual HRESULT __stdcall GetTypeInfo( UINT typeInfoIndex, LCID localeId, ITypeInfo** typeInfo )
        {
            auto itf = typeInfo_.GetInterfacePointer<ITypeInfo>( );
            return itf->QueryInterface( typeInfo );
        }

        TypeInfo GetTypeInfo( ) const
        {
            return typeInfo_;
        }


        virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId )
        {
            auto itf = typeInfo_.GetInterfacePointer<ITypeInfo>( );
            return itf->GetIDsOfNames( rgszNames, cNames, rgDispId );
        }

        virtual HRESULT __stdcall Invoke( DISPID memberId, REFIID riid, LCID lcid, WORD flags, DISPPARAMS* parameters, VARIANT* result, EXCEPINFO* exceptionInfo, UINT* argumentError )
        {
            auto itf = typeInfo_.GetInterfacePointer<ITypeInfo>( );
            DerivedType* self = static_cast<DerivedType*>( this );
            IDispatch* disp = self;
            return itf->Invoke( disp, memberId, flags, parameters, result, exceptionInfo, argumentError );
        }

    };

    

    template<typename ConnectionPointT, typename ObjectBaseT>
    class EnumConnectionsImpl;

    template<typename DerivedT, typename ObjectBaseT, typename ConnectionInterfaceT, typename InterfaceT>
    class __declspec( novtable ) IConnectionPointImpl : public IUknownImpl<DerivedT, InterfaceT>
    {
    public:
        using DerivedType = DerivedT;
        using ObjectBaseType = ObjectBaseT;
        using InterfaceType = IConnectionPoint;
        using ConnectionInterfaceType = ConnectionInterfaceT;
        using ConnectionContainer = std::vector<ConnectionInterfaceType*>;
        using size_type = typename ConnectionContainer::size_type;
        using iterator = typename ConnectionContainer::iterator;
        using const_iterator = typename ConnectionContainer::const_iterator;
        using reference = typename ConnectionContainer::reference;
        using const_reference = typename ConnectionContainer::const_reference;
    private:
        IConnectionPointContainer* connectionPointContainer_ = nullptr;
        ConnectionContainer connections_;
    public:
        IConnectionPointImpl( IConnectionPointContainer* connectionPointContainer )
            : connectionPointContainer_( connectionPointContainer )
        {
        }

        bool empty( ) const
        {
            return connections_.empty( );
        }

        size_type size( ) const
        {
            return connections_.size( );
        }

        iterator begin( )
        {
            return connections_.begin( );
        }
        iterator end( )
        {
            return connections_.end( );
        }

        const_iterator begin( ) const
        {
            return connections_.begin( );
        }
        const_iterator end( ) const
        {
            return connections_.end( );
        }
        
        reference operator[]( size_type index )
        {
            return connections_[ index ];
        }
        const_reference operator[]( size_type index ) const
        {
            return connections_[ index ];
        }

        virtual HRESULT STDMETHODCALLTYPE GetConnectionInterface( IID* pIID ) override
        {
            try
            {
                if ( pIID )
                {
                    *pIID = __uuidof( ConnectionInterfaceType );
                }
                else
                {
                    return E_POINTER;
                }
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDMETHODCALLTYPE GetConnectionPointContainer( IConnectionPointContainer** result ) override
        {
            try
            {
                return connectionPointContainer_->QueryInterface( result );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDMETHODCALLTYPE Advise( IUnknown* sink, DWORD* cookie ) override
        {
            try
            {
                if ( cookie )
                {
                    if ( sink )
                    {
                        auto count = connections_.size( );
                        for ( size_t i = 0; i < count; i++ )
                        {
                            if ( connections_[ i ] == nullptr )
                            {
                                connections_[ i ] = static_cast< ConnectionInterfaceType* >( sink );
                                sink->AddRef( );
                                *cookie = static_cast<DWORD>( i );
                                return S_OK;
                            }
                        }
                        *cookie = static_cast< DWORD >( connections_.size() );
                        connections_.push_back( sink );
                        sink->AddRef( );
                        return S_OK;
                    }
                    else
                    {
                        return E_INVALIDARG;
                    }
                }
                else
                {
                    return E_POINTER;
                }
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDMETHODCALLTYPE Unadvise( DWORD cookie ) override
        {
            try
            {
                if ( cookie < connections_.size( ) )
                {
                    auto connection = connections_[ cookie ];
                    connections_[ cookie ] = nullptr;
                    connection->Release( );
                    return S_OK;
                }
                else
                {
                    return E_POINTER;
                }
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDMETHODCALLTYPE EnumConnections( IEnumConnections** result ) override;

    };

    template<typename ConnectionPointT, typename ObjectBaseT>
    class EnumConnectionsImpl : public ObjectBaseT, public IUknownImpl<EnumConnectionsImpl<ConnectionPointT, ObjectBaseT>, IEnumConnections>
    {
    public:
        using ConnectionPointType = ConnectionPointT;
        using ObjectBaseType = ObjectBaseT;
        using InterfaceType = IEnumConnections;
        using size_type = typename ConnectionPointType::size_type;
        using ConnectionInterfaceType = typename ConnectionPointType::ConnectionInterfaceType;
    private:
        ConnectionPointType* connectionPoint_;
        size_type position_ = 0;
    public:
        EnumConnectionsImpl( ConnectionPointType* connectionPoint )
            : connectionPoint_( connectionPoint )
        {
            connectionPoint_->AddRef( );
        }
        ~EnumConnectionsImpl( )
        {
            connectionPoint_->Release( );
        }

        virtual HRESULT STDMETHODCALLTYPE Next( ULONG connectDataSize, LPCONNECTDATA connectData, ULONG* fetched ) override
        {
            try
            {
                if ( connectData && fetched )
                {
                    auto& connectionPoint = *connectionPoint_;
                    auto size = connectionPoint.size( );
                    if ( position_ < size )
                    {
                        size_type count = 0;
                        size_type maxCount = size - position_;
                        for ( size_t i = 0; i < maxCount && count < connectDataSize; i++ )
                        {
                            auto connection = connectionPoint[ position_ ];
                            if ( connection )
                            {
                                auto& element = connectData[ count ];
                                element.pUnk = connection;
                                connection->AddRef( );
                                element.dwCookie = static_cast< DWORD >( position_ );
                                count++;
                            }
                            position_++;
                        }
                        *fetched = static_cast< ULONG >( count );
                        return count == connectDataSize ? S_OK : S_FALSE;
                    }
                    else
                    {
                        *fetched = 0;
                        return connectDataSize == 0 ? S_OK : S_FALSE;
                    }
                }
                else
                {
                    return E_POINTER;
                }
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDMETHODCALLTYPE Skip( ULONG numberOfConnectionsToSkip ) override
        {
            try
            {
                auto& connectionPoint = *connectionPoint_;
                auto size = connectionPoint.size( );
                if ( position_ < size )
                {
                    // Free slots doesn't count, which is why we need to iterate over the connections
                    size_type count = 0;
                    size_type maxCount = size - position_;
                    for ( size_t i = 0; i < maxCount && count < numberOfConnectionsToSkip; i++ )
                    {
                        auto connection = connectionPoint[ position_ ];
                        if ( connection )
                        {
                            count++;
                        }
                        position_++;
                    }
                    return count == numberOfConnectionsToSkip ? S_OK : S_FALSE;
                }
                else
                {
                    return numberOfConnectionsToSkip == 0 ? S_OK : S_FALSE;
                }
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDMETHODCALLTYPE Reset( ) override
        {
            try
            {
                position_ = 0;
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDMETHODCALLTYPE Clone( IEnumConnections** result ) override
        {
            try
            {
                if ( result )
                {
                    auto ptr = new EnumConnectionsImpl<ConnectionPointType, ObjectBaseType>( connectionPoint_ );
                    ptr->position_ = position_;
                    *result = static_cast< IEnumConnections* >( ptr );
                    return S_OK;
                }
                else
                {
                    return E_POINTER;
                }
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

    };

    template<typename DerivedT, typename ObjectBaseT, typename ConnectionInterfaceT, typename InterfaceT>
    HRESULT STDMETHODCALLTYPE IConnectionPointImpl<DerivedT, ObjectBaseT, ConnectionInterfaceT, InterfaceT>::EnumConnections( IEnumConnections** result )
    {
        try
        {
            if ( result )
            {
                using ConnectionPointType = IConnectionPointImpl<DerivedT, ObjectBaseT, ConnectionInterfaceT, InterfaceT>;
                auto ptr = new EnumConnectionsImpl<ConnectionPointType, ObjectBaseType>( this );
                *result = static_cast< IEnumConnections* >( ptr );
                return S_OK;
            }
            else
            {
                return E_POINTER;
            }
        }
        HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
    }


}

#endif
