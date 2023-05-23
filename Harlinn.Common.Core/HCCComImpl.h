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
    class __declspec( novtable ) Interfaces : public InterfaceTypes...
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
        HRESULT QueryInterfaceImpl( const IID& iid, void** result )
        {
            if ( !result )
            {
                return E_POINTER;
            }
            void* ptr = QueryItf<InterfaceTypes...>( iid );
            if ( ptr )
            {
                *result = ptr;
                DerivedType* self = static_cast< DerivedType* >( this );
                self->AddRef( );
                return S_OK;
            }
            else
            {
                *result = nullptr;
                return E_NOINTERFACE;
            }
        }

        virtual HRESULT __stdcall QueryInterface( const IID& iid, void** result ) override
        {
            auto& self = *static_cast< DerivedType* >( this );
            return self.QueryInterfaceImpl( iid, result );
        }
    };

    template<typename DerivedT>
    class ObjectBase
    {
        ULONG referenceCount_ = 1;
    public:
        using DerivedType = DerivedT;

        virtual ~ObjectBase( ) = default;


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
                DerivedType* self = static_cast<DerivedType*>( this );
                delete self;
            }
            return result;
        }
    };







    template<typename DerivedT, typename ... InterfaceTypes>
    class __declspec( novtable ) IUknownImpl : public Interfaces<DerivedT, InterfaceTypes...>
    {
    public:
        using DerivedType = DerivedT;
        using InterfaceType = IUnknown;

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


    template<typename DerivedT, typename ... InterfaceTypes>
    class __declspec( novtable ) IDispatchImpl : public IUknownImpl<DerivedT, InterfaceTypes...>
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

    
    template<typename T>
    concept ModuleType = requires(T t)
    {
        { t.AddRef() } -> std::convertible_to<long>;
        { t.Release() } -> std::convertible_to<long>;
        { t.CanUnloadNow() } -> std::convertible_to<bool>;
    };
    


    template<typename DerivedT, typename ClassT, typename ... InterfaceTypes>
    class __declspec(novtable) IClassFactoryImpl : public IUknownImpl<DerivedT, InterfaceTypes...>
    {
    public:
        using ClassType = ClassT;
        virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override
        {
            try
            {

            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock) override
        {
            try
            {

            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }
    };




}

#endif
