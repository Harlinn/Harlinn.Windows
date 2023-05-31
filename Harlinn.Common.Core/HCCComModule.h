#pragma once
#ifndef HCCCOMMODULE_H_
#define HCCCOMMODULE_H_

#include <HCCDef.h>
#include <HCCGuid.h>
#include <HCCSync.h>
#include <HCCHandle.h>
#include <HCCRegistry.h>
#include <HCCComImpl.h>

namespace Harlinn::Common::Core::Com
{
    class Module;
}

namespace Harlinn::Common::Core::Com::Registry
{
    inline void RegisterModule( const Module& module );
    inline void UnregisterModule( const Module& module );
}


namespace Harlinn::Common::Core::Com
{
    class Module;

    class ModuleClassFactoryBase : public IClassFactory
    {
        Module* module_ = nullptr;
        unsigned long referenceCount_ = 1;
        Guid classId_;
        mutable TypeInfo typeInfo_;
    public:
        ModuleClassFactoryBase( Module* module, const Guid& classId )
            : module_( module ), classId_( classId )
        { }
        virtual ~ModuleClassFactoryBase( )
        {

        }

        const Module& Module( ) const
        {
            return *module_;
        }

        const Guid& ClassId( ) const
        {
            return classId_;
        }

        inline TypeInfo GetTypeInfo( ) const;
        

        virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** result ) override
        {
            try
            {
                if ( result )
                {
                    if ( riid == __uuidof( IClassFactory ) )
                    {
                        AddRef( );
                        *result = static_cast< IClassFactory* >( this );
                    }
                    else if ( riid == __uuidof( IUnknown ) )
                    {
                        AddRef( );
                        *result = static_cast< IUnknown* >( this );
                    }
                    else
                    {
                        return E_NOINTERFACE;
                    }
                }
                else
                {
                    return E_POINTER;
                }
                return S_OK;
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual ULONG STDMETHODCALLTYPE AddRef( ) override
        {
            return InterlockedIncrement( &referenceCount_ );
        }

        virtual ULONG STDMETHODCALLTYPE Release( ) override
        {
            // This will not destroy the object when the reference count reaches 0,
            // as the lifetime of this object is controlled by the ModuleClassFactoryPointer
            // defined below.
            return InterlockedDecrement( &referenceCount_ );
        }

        //virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject ) = 0;

        inline virtual HRESULT STDMETHODCALLTYPE LockServer( BOOL lock );

        virtual Guid GetIID( ) = 0;
        std::wstring ComponentName( ) const
        {
            auto typeInfo = GetTypeInfo( );
            auto name = typeInfo.GetName( );
            return name.ToString( );
        }

        std::pair<UInt16, UInt16> ComponentVersion( ) const
        {
            auto typeInfo = GetTypeInfo( );
            auto attributes = typeInfo.GetTypeAttributes( );
            auto version = attributes.Version( );
            if ( version.first == 0 )
            {
                version.first = 1;
            }
            return version;
        }


    };

    using ModuleClassFactoryPointer = std::unique_ptr<ModuleClassFactoryBase>;



    // Expects ImplementationT to implement:
    // 
    // 1:
    //      using InterfaceType = <the type of the interface>;
    // 
    //  For instance:
    // 
    //      using InterfaceType = IString;
    //
    template<typename ImplementationT>
    class ModuleClassFactoryT : public ModuleClassFactoryBase
    {
    public:
        using Base = ModuleClassFactoryBase;
        using ImplementationType = ImplementationT;
        using InterfaceType = typename ImplementationT::InterfaceType;

        ModuleClassFactoryT( Com::Module* module, const Guid& classId )
            : Base( module, classId )
        {
        }

        virtual Guid GetIID( ) override
        {
            return __uuidof( InterfaceType );
        }
    };


    // Expects ImplementationT to implement:
    // 
    //   static HRESULT Create( IUnknown* outerInterface, REFIID interfaceId, void** result )
    //
    template<typename ImplementationT>
    class ModuleClassFactory : public ModuleClassFactoryT<ImplementationT>
    {
    public:
        using Base = ModuleClassFactoryT<ImplementationT>;
        using ImplementationType = ImplementationT;

        ModuleClassFactory( Com::Module* module, const Guid& classId )
            : Base( module, classId )
        {
        }

        HRESULT STDMETHODCALLTYPE CreateInstance( IUnknown* outerInterface, REFIID interfaceId, void** result ) override
        {
            try
            {
                return ImplementationT::Create( outerInterface, interfaceId, result );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }
    };


    // Expects ImplementationT to implement:
    // 
    //   static HRESULT Create( const TypeInfo& typeInfo, IUnknown* outerInterface, REFIID interfaceId, void** result )
    //
    template<typename ImplementationT>
    class ModuleDispatchClassFactory : public ModuleClassFactoryT<ImplementationT>
    {
    public:
        using Base = ModuleClassFactoryT<ImplementationT>;
        using ImplementationType = ImplementationT;

        ModuleDispatchClassFactory( Com::Module* module, const Guid& classId )
            : Base( module, classId )
        {
        }

        HRESULT STDMETHODCALLTYPE CreateInstance( IUnknown* outerInterface, REFIID interfaceId, void** result ) override
        {
            try
            {
                auto typeInfo = Base::GetTypeInfo( );
                return ImplementationT::Create( typeInfo, outerInterface, interfaceId, result );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }
    };

#ifndef HCC_COM_MODULE_EXPORT
#define HCC_COM_MODULE_EXPORT __declspec(dllimport)
#endif
    
    class Module
    {
    public:
        using FactoryMap = std::unordered_map<Guid, ModuleClassFactoryPointer>;
        using iterator = FactoryMap::iterator;
        using const_iterator = FactoryMap::const_iterator;
        using size_type = FactoryMap::size_type;
        using value_type = FactoryMap::value_type;
        using key_type = FactoryMap::key_type;
        using mapped_type = FactoryMap::mapped_type;
    private:
        // This must be placed in the exe/dll implementing the module
        HCC_COM_MODULE_EXPORT static Module* instance_;

        std::wstring applicationName_;
        Guid libId_;
        ModuleHandle moduleHandle_;
        unsigned long referenceCount_ = 0;
        CriticalSection criticalSection_;
        FactoryMap classFactories_;
        mutable TypeLib2 typeLibrary_;
        bool registering_ = false;
        bool unregistering_ = false;
    public:
        Module(const wchar_t* applicationName, const Guid& libId )
            : applicationName_( applicationName ), libId_( libId )
        { }

        [[nodiscard]] static Module* Instance( )
        {
            return instance_;
        }

        [[nodiscard]] bool Registering( ) const
        {
            return registering_;
        }
        void SetRegistering( bool value )
        {
            registering_ = value;
        }

        [[nodiscard]] bool Unregistering( ) const
        {
            return unregistering_;
        }
        void SetUnregistering( bool value )
        {
            unregistering_ = value;
        }

        // Called by the ModuleObjectBase constructor and 
        // ModuleClassFactoryBase::LockServer
        ULONG AddReference( )
        {
            ULONG result = InterlockedIncrement( &referenceCount_ );
            return result;
        }

        // Called by the ModuleObjectBase destructor and 
        // ModuleClassFactoryBase::LockServer
        ULONG ReleaseReference( )
        {
            ULONG result = InterlockedDecrement( &referenceCount_ );
            return result;
        }

        [[nodiscard]] ULONG ReferenceCount( ) const
        {
            return referenceCount_;
        }


        [[nodiscard]] iterator begin( )
        {
            return classFactories_.begin( );
        }
        [[nodiscard]] iterator end( )
        {
            return classFactories_.end( );
        }
        [[nodiscard]] const_iterator begin( ) const
        {
            return classFactories_.begin( );
        }
        [[nodiscard]] const_iterator end( ) const
        {
            return classFactories_.end( );
        }
        [[nodiscard]] const_iterator cbegin( ) const
        {
            return classFactories_.cbegin( );
        }
        [[nodiscard]] const_iterator cend( ) const
        {
            return classFactories_.cend( );
        }
        [[nodiscard]] size_type size( ) const
        {
            return classFactories_.size( );
        }
        [[nodiscard]] bool constains( const Guid& classId ) const
        {
            return classFactories_.contains( classId );
        }

        [[nodiscard]] iterator find( const Guid& classId )
        {
            return classFactories_.find( classId );
        }
        [[nodiscard]] const_iterator find( const Guid& classId ) const
        {
            return classFactories_.find( classId );
        }
        

        [[nodiscard]] const std::wstring& ApplicationName() const
        {
            return applicationName_;
        }

        void SetModuleHandle( HMODULE moduleHandle )
        {
            moduleHandle_.SetValue( moduleHandle, false );
        }

        [[nodiscard]] std::wstring ModuleFileName( ) const
        {
            return moduleHandle_.ModuleFileName( );
        }

        [[nodiscard]] TypeLib2 TypeLibrary( ) const
        {
            if ( !typeLibrary_ )
            {
                std::unique_lock lock( criticalSection_ );
                if ( !typeLibrary_ )
                {
                    auto filename = ModuleFileName( );
                    if ( Registering( ) )
                    {
                        typeLibrary_ = TypeLib2::LoadTypeLib( filename, REGKIND::REGKIND_REGISTER );
                    }
                    else
                    {
                        typeLibrary_ = TypeLib2::LoadTypeLib( filename );
                    }
                }
            }
            return typeLibrary_;
        }

        [[nodiscard]] TypeInfo GetTypeInfo( const Guid& id ) const
        {
            auto tlb = TypeLibrary( );
            return tlb.GetTypeInfoOfGuid( id );
        }

        [[nodiscard]] TypeInfo GetTypeInfo( const Guid& id, TYPEKIND expectedTypeKind ) const
        {
            auto tlb = TypeLibrary( );
            return tlb.GetTypeInfoOfGuid( id, expectedTypeKind );
        }

        template<typename ImplementationT>
        void RegisterUnknown( const Guid& classId )
        {
            auto factory = std::make_unique< ModuleClassFactory<ImplementationT> >( this, classId );
            classFactories_.emplace( classId, std::move( factory ) );
        }

        template<typename ImplementationT>
        void RegisterDispatch( const Guid& classId )
        {
            auto factory = std::make_unique< ModuleDispatchClassFactory<ImplementationT> >( this, classId );
            classFactories_.emplace( classId, std::move( factory ) );
        }

        template<typename ImplementationT>
        void Register( const Guid& classId )
        {
            if constexpr ( std::is_base_of_v<IDispatch, std::remove_cvref_t<ImplementationT> > )
            {
                RegisterDispatch<ImplementationT>( classId );
            }
            else
            {
                RegisterUnknown<ImplementationT>( classId );
            }
        }

        [[nodiscard]] HRESULT RegisterServer( )
        {
            try
            {
                SetRegistering( true );
                Registry::RegisterModule( *this );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        [[nodiscard]] HRESULT UnregisterServer( )
        {
            try
            {
                SetUnregistering( true );
                Registry::UnregisterModule( *this );

                auto typeLibrary = TypeLibrary( );
                typeLibrary.Unregister( );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        [[nodiscard]] HRESULT GetClassObject( REFCLSID rclsid, REFIID riid, void** result )
        {
            try
            {
                auto it = find( rclsid );
                if ( it != end( ) )
                {
                    auto& factoryPtr = it->second;
                    return factoryPtr->QueryInterface( riid, result );
                }
                else
                {
                    return CLASS_E_CLASSNOTAVAILABLE;
                }
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        [[nodiscard]] HRESULT CanUnloadNow( )
        {
            try
            {
                return ReferenceCount() == 0? S_OK : S_FALSE;
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }


    };

    inline TypeInfo ModuleClassFactoryBase::GetTypeInfo( ) const
    {
        if ( !typeInfo_ )
        {
            typeInfo_ = module_->GetTypeInfo( classId_ );
        }
        return typeInfo_;
    }

    inline HRESULT STDMETHODCALLTYPE ModuleClassFactoryBase::LockServer( BOOL lock )
    {
        try
        {
            auto module = Module::Instance( );
            if ( lock )
            {
                module->AddReference( );
            }
            else
            {
                module->ReleaseReference( );
            }
        }
        HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
    }


    template<typename DerivedT, typename ... InterfaceTypes>
    class ModuleObjectBase : public Interfaces<DerivedT, InterfaceTypes...>
    {
        ULONG referenceCount_ = 1;
    public:
        using DerivedType = DerivedT;
        ModuleObjectBase( )
        {
            auto module = Module::Instance( );
            module->AddReference( );
        }

        virtual ~ModuleObjectBase( )
        {
            auto module = Module::Instance( );
            module->ReleaseReference( );
        }

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

    


    class ExeModule : public Module
    {
    public:
        using Base = Module;

        ExeModule( const wchar_t* applicationName, const Guid& libId )
            : Base( applicationName, libId )
        { }
    };

    class ServiceModule : public Module
    {
    public:
        using Base = Module;

        ServiceModule( const wchar_t* applicationName, const Guid& libId )
            : Base( applicationName, libId )
        {
        }
    };

    class DllModule : public Module
    {
    public:
        using Base = Module;

        DllModule( const wchar_t* applicationName, const Guid& libId )
            : Base( applicationName, libId )
        {
        }
    };


}

namespace Harlinn::Common::Core::Com::Registry
{
    namespace Internal
    {
        inline void WriteValue( const std::wstring& nameOfSubKey, const std::wstring& nameOfRegistryValue, const std::wstring& value )
        {
            auto rootKey = RegistryHandle::ClassesRoot( );
            auto subKey = rootKey.CreateKey( nameOfSubKey );
            subKey.SetValue( nameOfRegistryValue, value );
        }

        inline void WriteKey( const std::wstring& nameOfSubKey, const std::wstring& value )
        {
            auto rootKey = RegistryHandle::ClassesRoot( );
            auto subKey = rootKey.CreateKey( nameOfSubKey );
            subKey.SetValue( value );
        }

        inline void DeleteKey( const std::wstring& nameOfSubKey )
        {
            auto rootKey = RegistryHandle::ClassesRoot( );
            rootKey.DeleteKey( nameOfSubKey );
        }
    }


    inline void RegisterModuleClass( const ModuleClassFactoryBase& classFactory )
    {
        using Internal::WriteKey;
        auto& module = classFactory.Module( );
        auto classId = classFactory.ClassId( ).ToString();
        auto moduleName = module.ModuleFileName( );

        auto applicationName = module.ApplicationName( );
        auto componentName = classFactory.ComponentName( );
        auto componentVersion = classFactory.ComponentVersion( );

        auto clsidSubKey = Format( L"CLSID\\%s", classId.c_str( ) );
        auto clsidInprocServer32SubKey = clsidSubKey + L"\\InprocServer32";
        auto clsidProgIdSubKey = clsidSubKey + L"\\ProgId";

        //
        auto progId = Format( L"%s.%s.%d.%d", applicationName.c_str( ), componentName.c_str( ), componentVersion.first, componentVersion.second );
        auto progIdClsidSubkey = progId + L"\\CLSID";


        auto versionIndependentProgId = Format( L"%s.%s", applicationName.c_str( ), componentName.c_str( ) );
        auto versionIndependentProgIdClsidSubkey = versionIndependentProgId + L"\\CLSID";
        auto versionIndependentProgIdCurVerSubkey = versionIndependentProgId + L"\\CurVer";

        WriteKey( clsidSubKey, versionIndependentProgId );
        WriteKey( clsidInprocServer32SubKey, moduleName );
        WriteKey( clsidProgIdSubKey, progId );

        WriteKey( progId, versionIndependentProgId );
        WriteKey( progIdClsidSubkey, classId );

        WriteKey( versionIndependentProgId, versionIndependentProgId );
        WriteKey( versionIndependentProgIdClsidSubkey, classId );
        WriteKey( versionIndependentProgIdCurVerSubkey, progId );



    }

    inline void UnregisterModuleClass( const ModuleClassFactoryBase& classFactory )
    {
        using Internal::DeleteKey;
        auto& module = classFactory.Module( );
        auto classId = classFactory.ClassId( ).ToString( );
        auto moduleName = module.ModuleFileName( );

        auto applicationName = module.ApplicationName( );
        auto componentName = classFactory.ComponentName( );
        auto componentVersion = classFactory.ComponentVersion( );

        auto clsidSubKey = Format( L"CLSID\\%s", classId.c_str( ) );
        auto clsidInprocServer32SubKey = clsidSubKey + L"\\InprocServer32";
        auto clsidProgIdSubKey = clsidSubKey + L"\\ProgId";

        //
        auto progId = Format( L"%s.%s.%d.%d", applicationName.c_str( ), componentName.c_str( ), componentVersion.first, componentVersion.second );
        auto progIdClsidSubkey = progId + L"\\CLSID";


        auto versionIndependentProgId = Format( L"%s.%s", applicationName.c_str( ), componentName.c_str( ) );
        auto versionIndependentProgIdClsidSubkey = versionIndependentProgId + L"\\CLSID";
        auto versionIndependentProgIdCurVerSubkey = versionIndependentProgId + L"\\CurVer";

        DeleteKey( versionIndependentProgIdCurVerSubkey );
        DeleteKey( versionIndependentProgIdClsidSubkey );
        DeleteKey( versionIndependentProgId );

        DeleteKey( progIdClsidSubkey );
        DeleteKey( progId );

        DeleteKey( clsidProgIdSubKey );
        DeleteKey( clsidInprocServer32SubKey );
        DeleteKey( clsidSubKey );
    }


    inline void RegisterModule( const Module& module )
    {
        for ( auto& entry : module )
        {
            const ModuleClassFactoryBase& classFactory = *entry.second;
            RegisterModuleClass( classFactory );
        }
    }
    inline void UnregisterModule( const Module& module )
    {
        for ( auto& entry : module )
        {
            const ModuleClassFactoryBase& classFactory = *entry.second;
            RegisterModuleClass( classFactory );
        }
    }

}


#endif
