#pragma once
#ifndef HARLINN_COMMON_CORE_HCCCOMIMPL_H_
#define HARLINN_COMMON_CORE_HCCCOMIMPL_H_
/*
   Copyright 2024-2026 Espen Harlinn

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

#include <HCCObj.h>
#include <HCCSync.h>

namespace Harlinn::Common::Core::Com
{
    template<typename T>
    concept InterfaceQueryable = requires( T t, REFIID riid, void** ppvObject, bool addRef )
    {
        { t.QueryInterfaceImpl( riid, ppvObject, addRef ) }->std::same_as<HRESULT>;
    };

    template<typename T>
    concept IUnknownImplLike = InterfaceQueryable<T> && requires( T t, REFIID riid, void** ppvObject, bool addRef )
    {
        { t.AddRefImpl( ) }->std::same_as<ULONG>;
        { t.ReleaseImpl( ) }->std::same_as<ULONG>;
    };

    
    namespace Internal
    {
        /// <summary>
        /// Base class for COM object implementations, it implements
        /// <code>
        /// void* QueryItf( const Guid& iid );
        /// </code>
        /// which returns a pointer to the requested interface identified by 
        /// the iid parameter, or nullptr if the requested interface is not 
        /// supported by the type.
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
        /// </typeparam>
        template<typename DerivedT, typename ... InterfaceTypes >
        class __declspec( novtable ) Interfaces : public InterfaceTypes...
        {
        public:
            using DerivedType = DerivedT;
        private:
            template<typename InterfaceType, typename ...RemainingInterfaceTypes>
            void* QueryItf_( const Guid& iid ) const
            {
                using Itf = Com::Interfaces::Interface<InterfaceType>;
                const DerivedType* self = static_cast< const DerivedType* >( this );
                auto* ptr = Itf::QueryInterface( iid, static_cast< const InterfaceType* >( self ) );
                if ( !ptr )
                {
                    if constexpr ( sizeof...( RemainingInterfaceTypes ) > 0 )
                    {
                        ptr = QueryItf_<RemainingInterfaceTypes...>( iid );
                    }
                }
                return ptr;
            }
        protected:
            /// <summary>
            /// <para>
            /// Retrieves a pointer to the interface if it's among the interfaces 
            /// specified by the InterfaceTypes... parameter pack, otherwise nullptr.
            /// </para>
            /// <para>
            /// Used by derived classes to implement the <c>virtual HRESULT __stdcall QueryInterface( const IID& iid, void** result )</c> function.
            /// </para>
            /// </summary>
            /// <param name="iid"></param>
            /// <returns>A void* pointer to the requested interface, or nullptr if it is not supported.</returns>
            void* QueryItf( const Guid& iid ) const
            {
                return QueryItf_<InterfaceTypes...>( iid );
            }

        public:
            
        };
    }

    /// <summary>
    /// <para>
    /// Use this template to implement COM objects that will be instantiated using either
    /// <code>
    /// template&lt;typename BaseT&gt;
    /// class HeapObject {...}
    /// </code>
    /// or
    /// <code>
    /// template&lt;typename BaseT&gt;
    /// class StackObject {...}
    /// </code>
    /// </para>
    /// <para>
    /// HeapObject and StackObject provides the implementation of the IUnknown
    /// interface, while the remaining functions specified by the interfaces
    /// given in the InterfaceTypes parameter pack must be implemented
    /// by the class derived from ObjectBase.
    /// </para>
    /// </summary>
    /// <typeparam name="...InterfaceTypes"></typeparam>
    /// <typeparam name="DerivedT"></typeparam>
    template<typename DerivedT, typename ... InterfaceTypes>
    class __declspec( novtable ) ObjectBase : public Internal::Interfaces<DerivedT, InterfaceTypes...>
    {
    public:
        using Base = Internal::Interfaces<DerivedT, InterfaceTypes...>;
        using DerivedType = DerivedT;
        ObjectBase( ) = default;
    };

    namespace Internal
    {
        template<typename BaseT>
        class __declspec( novtable ) StackObjectImpl : public BaseT
        {
            ULONG referenceCount_ = 1;
        public:
            using Base = BaseT;
            template<typename ...Args>
            explicit StackObjectImpl( Args&&... args )
                : Base( std::forward<Args>( args )... )
            {
            }

            virtual ULONG AddRef( ) override
            {
                ULONG result = InterlockedIncrement( &referenceCount_ );
                return result;
            }

            virtual ULONG Release( ) override
            {
                ULONG result = InterlockedDecrement( &referenceCount_ );
                return result;
            }
        protected:
            HRESULT QueryInterfaceImpl( const IID& iid, void** result, bool addRef = true )
            {
                if ( !result )
                {
                    return E_POINTER;
                }
                void* ptr = Base::QueryItf( iid );
                if ( ptr )
                {
                    *result = ptr;
                    if ( addRef )
                    {
                        AddRef( );
                    }
                    return S_OK;
                }
                else
                {
                    *result = nullptr;
                    return E_NOINTERFACE;
                }
            }
        public:
            virtual HRESULT __stdcall QueryInterface( const IID& iid, void** result ) override
            {
                return QueryInterfaceImpl( iid, result );
            }
        };

        template<typename BaseT>
        class __declspec( novtable ) HeapObjectImpl : public BaseT
        {
            ULONG referenceCount_ = 1;
        public:
            using Base = BaseT;
            template<typename ...Args>
            explicit HeapObjectImpl( Args&&... args )
                : Base( std::forward<Args>( args )... )
            { }

            ULONG AddRef( )
            {
                ULONG result = InterlockedIncrement( &referenceCount_ );
                return result;
            }

            ULONG Release( )
            {
                ULONG result = InterlockedDecrement( &referenceCount_ );
                if ( result == 0 )
                {
                    delete this;
                }
                return result;
            }
        protected:
            HRESULT QueryInterfaceImpl( const IID& iid, void** result, bool addRef = true )
            {
                if ( !result )
                {
                    return E_POINTER;
                }
                void* ptr = Base::QueryItf( iid );
                if ( ptr )
                {
                    *result = ptr;
                    if ( addRef )
                    {
                        AddRef( );
                    }
                    return S_OK;
                }
                else
                {
                    *result = nullptr;
                    return E_NOINTERFACE;
                }
            }
        public:
            virtual HRESULT __stdcall QueryInterface( const IID& iid, void** result ) override
            {
                return QueryInterfaceImpl( iid, result );
            }

            
        };
    }

    /// <summary>
    /// Use this template to instantiate an object with a non-destructive
    /// implementation of <c>IUnknown::Release()</c>. COM objects instantiated using
    /// this template can be allocated on the stack.
    /// </summary>
    /// <typeparam name="BaseT">
    /// A type that implements one or more COM interfaces, but not IUnknown.
    /// </typeparam>
    template<typename BaseT>
    class StackObject : public Internal::StackObjectImpl<BaseT>
    {
    public:
        using Base = Internal::StackObjectImpl<BaseT>;
        template<typename ...Args>
        explicit StackObject( Args&&... args )
            : Base( std::forward<Args>( args )... )
        {
        }
    };

    /// <summary>
    /// Use this template to instantiate an object with an implementation of 
    /// <c>IUnknown::Release()</c> that calls the <c>delete</c> operator on itself
    /// when its reference count becomes 0. COM objects instantiated using this
    /// template must be allocated using the <c>new</c> operator. 
    /// </summary>
    /// <typeparam name="BaseT">
    /// A type that implements one or more COM interfaces, but not IUnknown.
    /// </typeparam>
    template<typename BaseT>
    class HeapObject : public Internal::HeapObjectImpl<BaseT>
    {
    public:
        using Base = Internal::HeapObjectImpl<BaseT>;
        template<typename ...Args>
        explicit HeapObject( Args&&... args )
            : Base( std::forward<Args>( args )... )
        {
        }


        template<typename ...Args>
        static auto CreateObject( Args&&... args )
        {
            ComPtr ptr( new HeapObject<BaseT>( std::forward<Args>( args )... ), false );
            return ptr;
        }

        template<typename ...Args>
        static HRESULT CreateInstance( void** result, Args&&... args )
        {
            if ( !result )
            {
                return E_POINTER;
            }
            ComPtr ptr( new HeapObject<BaseT>( std::forward<Args>( args )... ), false );
            *result = ptr.Detach( );
        }

        template<typename ...Args>
        static HRESULT CreateInstance(const Guid& riid, void** result, Args&&... args )
        {
            if ( !result )
            {
                return E_POINTER;
            }
            ComPtr ptr( new HeapObject<BaseT>( std::forward<Args>( args )... ), false );
            auto hr = ptr->QueryInterface( riid, result );
            return hr;
        }

    };

    /// <summary>
    /// Provides an implementation of IDispatch
    /// </summary>
    /// <typeparam name="...InterfaceTypes">
    /// The list of COM interfaces that is implemented by DerivedT that DerivedT can be 
    /// unambiguously be cast to. This means that no interface can be derived from any
    /// other interface that is part of this parameter pack.
    /// </typeparam>
    /// <typeparam name="DerivedT">
    /// The type of the derived class.
    /// </typeparam>
    template<typename DerivedT, typename ... InterfaceTypes>
    class __declspec( novtable ) IDispatchImpl : public ObjectBase<DerivedT, InterfaceTypes...>
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
        virtual HRESULT __stdcall GetTypeInfoCount( UINT* result ) override
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
        virtual HRESULT __stdcall GetTypeInfo( UINT typeInfoIndex, LCID localeId, ITypeInfo** typeInfo ) override
        {
            auto itf = typeInfo_.GetInterfacePointer<ITypeInfo>( );
            return itf->QueryInterface( typeInfo );
        }

        TypeInfo GetTypeInfo( ) const
        {
            return typeInfo_;
        }


        virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId ) override
        {
            auto itf = typeInfo_.GetInterfacePointer<ITypeInfo>( );
            return itf->GetIDsOfNames( rgszNames, cNames, rgDispId );
        }

        virtual HRESULT __stdcall Invoke( DISPID memberId, REFIID riid, LCID lcid, WORD flags, DISPPARAMS* parameters, VARIANT* result, EXCEPINFO* exceptionInfo, UINT* argumentError ) override
        {
            auto itf = typeInfo_.GetInterfacePointer<ITypeInfo>( );
            DerivedType* self = static_cast<DerivedType*>( this );
            IDispatch* disp = self;
            return itf->Invoke( disp, memberId, flags, parameters, result, exceptionInfo, argumentError );
        }

    };

    
    /*
    template<typename ConnectionPointT, typename ObjectBaseT>
    class EnumConnectionsImpl;

    template<typename DerivedT, typename ObjectBaseT, typename ConnectionInterfaceT, typename InterfaceT>
    class __declspec( novtable ) IConnectionPointImpl : public ObjectBase<DerivedT, InterfaceT>
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
    class EnumConnectionsImpl : public ObjectBaseT, public ObjectBase<EnumConnectionsImpl<ConnectionPointT, ObjectBaseT>, IEnumConnections>
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
    */

}

#endif
