#pragma once
#ifndef __HCCOBJ_H__
#define __HCCOBJ_H__

#include <HCCObjBase.h>
#include <HCCDatetime.h>


namespace Harlinn::Common::Core
{
    /// <summary>
    /// Wrapper for the IPersist interface.
    /// IPersist provides the CLSID of an object that can be stored persistently in the system. 
    /// Allows the object to specify which object handler to use in the client process, 
    /// as it is used in the default implementation of marshaling.
    /// </summary>
    /// <remarks>
    /// IPersist is the base interface for three other interfaces: IPersistStorage, 
    /// IPersistStream, and IPersistFile. Each of these interfaces, therefore, 
    /// includes the GetClassID method, and the appropriate one of these three interfaces 
    /// is implemented on objects that can be serialized to a storage, a stream, or a file. 
    /// The methods of these interfaces allow the state of these objects to be saved for 
    /// later instantiations, and load the object using the saved state. Typically, 
    /// the persistence interfaces are implemented by an embedded or linked object, and 
    /// are called by the container application or the default object handler.
    /// </remarks>
    class Persist : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( Persist, Unknown, IPersist, IUnknown )

        CLSID GetClassID( ) const
        {
            auto pInterface = GetInterface( );
            CLSID result;
            auto hr = pInterface->GetClassID( &result );
            HCC_COM_CHECK_HRESULT2(hr, pInterface );
            return result;
        }
    };

    /// <summary>
    /// Wrapper for the IPersistStream interface.
    /// IPersistStream enables the saving and loading of objects that use a 
    /// simple serial stream for their storage needs.
    /// </summary>
    class PersistStream : public Persist
    {
    public:
        typedef Persist Base;
        HCC_COM_STANDARD_METHODS_IMPL( PersistStream, Persist, IPersistStream, IPersist )

        /// <summary>
        /// Determines whether an object has changed since it was last saved to its stream.
        /// </summary>
        /// <returns>
        /// This method returns true to indicate that the object has changed. Otherwise, it returns false.
        /// </returns>
        bool IsDirty( ) const
        {
            auto pInterface = GetInterface( );
            return pInterface->IsDirty( ) == S_OK ? true : false;
        }

        /// <summary>
        /// Initializes an object from the stream where it was saved previously.
        /// </summary>
        /// <param name="pStm">
        /// An IStream pointer to the stream from which the object should be loaded.
        /// </param>
        void Load( IStream* pStm ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( pStm );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Saves an object to the specified stream.
        /// </summary>
        /// <param name="pStm">
        /// An IStream pointer to the stream into which the object should be saved.
        /// </param>
        /// <param name="clearDirty">
        /// Indicates whether to clear the dirty flag after the save is complete. 
        /// If true, the flag should be cleared. If false, the flag should be left unchanged.
        /// </param>
        void Save( IStream* pStm, bool clearDirty ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Save( pStm, clearDirty ? TRUE : FALSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the size of the stream needed to save the object.
        /// </summary>
        /// <returns>
        /// The size in bytes of the stream needed to save this object, in bytes.
        /// </returns>
        unsigned long long GetSizeMax( ) const
        {
            auto pInterface = GetInterface( );
            ULARGE_INTEGER result;
            auto hr = pInterface->GetSizeMax( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result.QuadPart;
        }
    };


    class Moniker;
    /// <summary>
    /// Enumerates the components of a moniker or the monikers in a table of monikers.
    /// </summary>
    class EnumMoniker : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumMoniker, Unknown, IEnumMoniker, IUnknown )

        bool Next( Moniker& theResult ) const;

        bool Next( ULONG requestedNumberOfElements, std::vector<Moniker>& result ) const;

        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumMoniker Clone( ) const 
        {
            auto pInterface = GetInterface( );
            IEnumMoniker* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumMoniker( pClone );
        }

    };

    /// <summary>
    /// <p>
    /// Enables you to use a moniker object, which contains information 
    /// that uniquely identifies a COM object. An object that has a pointer 
    /// to the moniker object's IMoniker interface can locate, activate, 
    /// and get access to the identified object without having any other 
    /// specific information on where the object is actually located in a 
    /// distributed system.
    /// </p>
    /// <p>
    /// Monikers are used as the basis for linking in COM. A linked object 
    /// contains a moniker that identifies its source. When the user 
    /// activates the linked object to edit it, the moniker is bound; this 
    /// loads the link source into memory.
    /// </p>
    /// </summary>
    class Moniker : public PersistStream
    {
    public:
        typedef PersistStream Base;
        HCC_COM_STANDARD_METHODS_IMPL( Moniker, PersistStream, IMoniker, IPersistStream )

        template <typename T>
        T BindToObject( IBindCtx* pbc, IMoniker* pmkToLeft = nullptr ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->BindToObject( pbc, pmkToLeft, __uuidof( T::InterfaceType ), (void**)&result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return T( result );
        }

        template <typename T>
        T BindToStorage( IBindCtx* pbc, IMoniker* pmkToLeft = nullptr ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->BindToStorage( pbc, pmkToLeft, __uuidof( T::InterfaceType ), (void**)&result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return T( result );
        }

        Moniker Reduce( IBindCtx* pbc, DWORD dwReduceHowFar = MKRREDUCE_THROUGHUSER, IMoniker** ppmkToLeft = nullptr ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result;
            auto hr = pInterface->Reduce( pbc, dwReduceHowFar, ppmkToLeft, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }

        Moniker ComposeWith( IMoniker* pmkRight, bool onlyIfNotGeneric ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result;
            auto hr = pInterface->ComposeWith( pmkRight, onlyIfNotGeneric, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }

        EnumMoniker Enum( bool forward ) const
        {
            auto pInterface = GetInterface( );
            IEnumMoniker* result;
            auto hr = pInterface->Enum( forward, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumMoniker( result );
        }

        bool IsEqual( IMoniker* otherMoniker ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsEqual( otherMoniker );
            if ( hr == S_OK )
            {
                return true;
            }
            else if ( hr == S_FALSE )
            {
                return false;
            }
            else 
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return false;
        }

        DWORD Hash( ) const
        {
            auto pInterface = GetInterface( );
            DWORD result;
            auto hr = pInterface->Hash( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        bool IsRunning( IBindCtx* pbc, IMoniker* pmkNewlyRunning = nullptr, IMoniker* pmkToLeft = nullptr ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsRunning( pbc, pmkToLeft, pmkNewlyRunning );
            if ( hr == S_OK )
            {
                return true;
            }
            else if ( hr == S_FALSE )
            {
                return false;
            }
            else 
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return false;
        }

        DateTime GetTimeOfLastChange( IBindCtx* pbc, IMoniker* pmkToLeft = nullptr ) const
        {
            auto pInterface = GetInterface( );
            FILETIME result;
            auto hr = pInterface->GetTimeOfLastChange( pbc, pmkToLeft, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return DateTime::FromFileTime( *(long long*)&result );
        }

        Moniker Inverse( ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result;
            auto hr = pInterface->Inverse( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }
        Moniker CommonPrefixWith( IMoniker* pmkOther ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result;
            auto hr = pInterface->CommonPrefixWith( pmkOther, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }

        Moniker RelativePathTo( IMoniker* pmkOther ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result;
            auto hr = pInterface->RelativePathTo( pmkOther, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }
        std::wstring GetDisplayName( IBindCtx* pbc, IMoniker* pmkToLeft = nullptr ) const
        {
            auto pInterface = GetInterface( );
            Malloc malloc = Malloc::GetMalloc( );
            LPOLESTR result = nullptr;
            auto hr = pInterface->GetDisplayName( pbc, pmkToLeft, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            std::wstring s( result );
            malloc.Free( result );
            return s;
        }
        Moniker ParseDisplayName( IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR pszDisplayName, ULONG* pchEaten ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result;
            auto hr = pInterface->ParseDisplayName( pbc, pmkToLeft, pszDisplayName, pchEaten, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }
        MKSYS IsSystemMoniker( ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->IsSystemMoniker( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return MKSYS( result );
        }

    };


    inline bool EnumMoniker::Next( Moniker& theResult ) const
    {
        auto pInterface = GetInterface( );
        IMoniker* pElement = nullptr;
        ULONG actual = 0;
        auto hr = pInterface->Next( 1, &pElement, &actual );
        if ( actual )
        {
            theResult.ResetPtr( pElement );
            return true;
        }
        return false;
    }

    inline bool EnumMoniker::Next( ULONG requestedNumberOfElements, std::vector<Moniker>& result ) const
    {
        auto pInterface = GetInterface( );
        IMoniker** pElements = (IMoniker**)alloca( requestedNumberOfElements * sizeof( IMoniker* ) );
        memset( pElements, 0, requestedNumberOfElements * sizeof( IMoniker* ) );
        ULONG actual = 0;

        auto hr = pInterface->Next( 1, pElements, &actual );
        if ( actual )
        {
            result.clear( );
            for ( ULONG i = 0; i < actual; i++ )
            {
                result.push_back( Moniker( pElements[i] ) );
            }
            return true;
        }
        return false;
    }


    /// <summary>
    /// Manages access to the running object table (ROT), a globally 
    /// accessible look-up table on each workstation. A workstation's 
    /// ROT keeps track of those objects that can be identified by a 
    /// moniker and that are currently running on the workstation. 
    /// When a client tries to bind a moniker to an object, the moniker 
    /// checks the ROT to see if the object is already running; this 
    /// allows the moniker to bind to the current instance instead of 
    /// loading a new one.
    /// </summary>
    class RunningObjectTable : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( RunningObjectTable, Unknown, IRunningObjectTable, IUnknown )

        DWORD Register( DWORD flags, IUnknown* object, IMoniker* objectName ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->Register( flags, object, objectName, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void Revoke( DWORD dwRegister ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->Revoke( dwRegister );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsRunning( IMoniker* objectName ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->IsRunning( objectName );
            if ( hr == S_OK )
            {
                return true;
            }
            else if ( hr == S_FALSE )
            {
                return false;
            }
            else 
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return false;
        }

        Unknown GetObject( IMoniker* pmkObjectName ) const
        {
            auto pInterface = GetInterface( );
            IUnknown* result = 0;
            auto hr = pInterface->GetObject( pmkObjectName, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Unknown( result );
        }

        void NoteChangeTime( DWORD dwRegister, const DateTime& time ) const
        {
            auto pInterface = GetInterface( );
            long long filetime = time.ToFileTime( );
            auto hr = pInterface->NoteChangeTime( dwRegister, ( (FILETIME*)&filetime ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DateTime GetTimeOfLastChange( IMoniker* pmkObjectName ) const
        {
            auto pInterface = GetInterface( );
            FILETIME result;
            auto hr = pInterface->GetTimeOfLastChange( pmkObjectName, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return DateTime::FromFileTime( *(long long*)&result );
        }

        EnumMoniker EnumRunning( ) const
        {
            auto pInterface = GetInterface( );
            IEnumMoniker* result = 0;
            auto hr = pInterface->EnumRunning( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumMoniker( result );
        }

    };


    /// <summary>
    /// Provides access to a bind context, which is an object that 
    /// stores information about a particular moniker binding operation.
    /// </summary>
    class BindCtx : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( BindCtx, Unknown, IBindCtx, IUnknown )


        static BindCtx Create( )
        {
            IBindCtx* result = nullptr;
            auto hr = CreateBindCtx( 0, &result );
            HCC_COM_CHECK_HRESULT( hr );
            return BindCtx( result );
        }

        void RegisterObjectBound( IUnknown* punk ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RegisterObjectBound( punk );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RevokeObjectBound( IUnknown* punk ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RevokeObjectBound( punk );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReleaseBoundObjects( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReleaseBoundObjects( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetBindOptions( BIND_OPTS* pbindopts ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetBindOptions( pbindopts );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBindOptions( BIND_OPTS* pbindopts ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetBindOptions( pbindopts );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        RunningObjectTable GetRunningObjectTable( ) const
        {
            auto pInterface = GetInterface( );
            IRunningObjectTable* result = 0;
            auto hr = pInterface->GetRunningObjectTable( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return RunningObjectTable( result );
        }

        void RegisterObjectParam( LPOLESTR pszKey, IUnknown* punk ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RegisterObjectParam( pszKey, punk );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Unknown GetObjectParam( LPOLESTR pszKey ) const
        {
            auto pInterface = GetInterface( );
            IUnknown* result = 0;
            auto hr = pInterface->GetObjectParam( pszKey, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Unknown( result );
        }

        EnumString EnumObjectParam( ) const
        {
            auto pInterface = GetInterface( );
            IEnumString* result = 0;
            auto hr = pInterface->EnumObjectParam( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumString( result );
        }

        void RevokeObjectParam( LPOLESTR pszKey ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RevokeObjectParam( pszKey );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Enables a container to control the running of its embedded 
    /// objects. In the case of an object implemented with a local 
    /// server, calling the Run method launches the server's .EXE 
    /// file. In the case of an object implemented with an in-process 
    /// server, calling Run causes the object .DLL file to transition 
    /// into the running state.
    /// </summary>
    class RunnableObject : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( RunnableObject, Unknown, IRunnableObject, IUnknown )

        CLSID GetRunningClass( ) const
        {
            auto pInterface = GetInterface( );
            CLSID result;
            auto hr = pInterface->GetRunningClass( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }


        void Run( LPBINDCTX pbc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Run( pbc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsRunning( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsRunning( );
            if ( hr == TRUE )
            {
                return true;
            }
            return false;
        }

        void LockRunning( bool lock, bool lastUnlockCloses ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->LockRunning( lock, lastUnlockCloses );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetContainedObject( bool contained ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetContainedObject( contained );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Implemented by monikers to enable the running object table 
    /// (ROT) to compare monikers against each other.
    /// </summary>
    class ROTData : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ROTData, Unknown, IROTData, IUnknown )

        std::vector<BYTE> GetComparisonData( ) const
        {
            auto pInterface = GetInterface( );
            BYTE buffer[2048];
            ULONG actual = 0;
            auto hr = pInterface->GetComparisonData( buffer, 2048, &actual );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            std::vector<BYTE> result( buffer, buffer + actual );
            return result;
        }
    };


    /// <summary>
    /// The IEnumSTATSTG interface enumerates an array of STATSTG structures. 
    /// These structures contain statistical data about open storage, stream, 
    /// or byte array objects.
    /// </summary>
    class EnumSTATSTG : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumSTATSTG, Unknown, IEnumSTATSTG, IUnknown )

        bool Next( STATSTG& theResult ) const
        {
            auto pInterface = GetInterface( );
            IUnknown* pElement = nullptr;
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &theResult, &actual );
            if ( actual )
            {
                return true;
            }
            return false;
        }

        bool Next( ULONG requestedNumberOfElements, std::vector<STATSTG>& result ) const
        {
            auto pInterface = GetInterface( );
            STATSTG* pElements = (STATSTG*)alloca( requestedNumberOfElements * sizeof( STATSTG ) );
            memset( pElements, 0, requestedNumberOfElements * sizeof( STATSTG ) );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, pElements, &actual );
            if ( actual )
            {
                result.clear( );
                for ( ULONG i = 0; i < actual; i++ )
                {
                    result.push_back( pElements[i] );
                }
                return true;
            }
            return false;
        }

        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumSTATSTG Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATSTG* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATSTG( pClone );
        }

    };



    /// <summary>
    /// <p>
    /// The IStorage interface supports the creation and management of structured 
    /// storage objects. Structured storage allows hierarchical storage of information 
    /// within a single file, and is often referred to as "a file system within a file". 
    /// Elements of a structured storage object are storages and streams. Storages 
    /// are analogous to directories, and streams are analogous to files. Within a 
    /// structured storage there will be a primary storage object that may contain 
    /// sub-storages, possibly nested, and streams. Storages provide the structure of 
    /// the object, and streams contain the data, which is manipulated through the 
    /// IStream interface.
    /// </p>
    /// <p>
    /// The IStorage interface provides methods for creating and managing the root 
    /// storage object, child storage objects, and stream objects. These methods can 
    /// create, open, enumerate, move, copy, rename, or delete the elements in the 
    /// storage object.
    /// </p>
    /// <p>
    /// An application must release its IStorage pointers when it is done with the 
    /// storage object to deallocate memory used. There are also methods for changing 
    /// the date and time of an element.
    /// </p>
    /// <p>
    /// There are a number of different modes in which a storage object and its 
    /// elements can be opened, determined by setting values from STGM Constants. 
    /// One aspect of this is how changes are committed. You can set direct mode, 
    /// in which changes to an object are immediately written to it, or transacted 
    /// mode, in which changes are written to a buffer until explicitly committed. 
    /// The IStorage interface provides methods for committing changes and reverting 
    /// to the last-committed version. For example, a stream can be opened in 
    /// read-only mode or read/write mode. For more information, see STGM Constants.
    /// </p>
    /// <p>
    /// Other methods provide access to information about a storage object and its 
    /// elements through the STATSTG structure.
    /// </p>
    /// </summary>
    class Storage : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( Storage, Unknown, IStorage, IUnknown )

        Stream CreateStream( const OLECHAR* pwcsName, DWORD grfMode ) const
        {
            auto pInterface = GetInterface( );
            IStream* pResult = nullptr;
            auto hr = pInterface->CreateStream( pwcsName, grfMode, 0, 0, &pResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Stream( pResult );
        }

        Stream OpenStream( const OLECHAR* pwcsName, DWORD grfMode ) const
        {
            auto pInterface = GetInterface( );
            IStream* pResult = nullptr;
            auto hr = pInterface->OpenStream( pwcsName, 0, grfMode, 0, &pResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Stream( pResult );
        }

        Storage CreateStorage( const OLECHAR* pwcsName, DWORD grfMode ) const
        {
            auto pInterface = GetInterface( );
            IStorage* pResult = nullptr;
            auto hr = pInterface->CreateStorage( pwcsName, grfMode, 0, 0, &pResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Storage( pResult );
        }

        Storage OpenStorage( const OLECHAR* pwcsName, DWORD grfMode ) const
        {
            auto pInterface = GetInterface( );
            IStorage* pResult = nullptr;
            auto hr = pInterface->OpenStorage( pwcsName, nullptr, grfMode, nullptr, 0, &pResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Storage( pResult );
        }

        void CopyTo( DWORD ciidExclude, const IID* rgiidExclude, SNB snbExclude, IStorage* pstgDest ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CopyTo( ciidExclude, rgiidExclude, snbExclude, pstgDest );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void MoveElementTo( const OLECHAR* pwcsName, IStorage* pstgDest, const OLECHAR* pwcsNewName, DWORD grfFlags = STGMOVE_MOVE ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->MoveElementTo( pwcsName, pstgDest, pwcsNewName, grfFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Commit( DWORD grfCommitFlags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Commit( grfCommitFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Revert( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Revert( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumSTATSTG EnumElements( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATSTG* pResult = nullptr;
            auto hr = pInterface->EnumElements( 0, 0, 0, &pResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATSTG( pResult );
        }

        void DestroyElement( const OLECHAR* pwcsName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DestroyElement( pwcsName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RenameElement( const OLECHAR* pwcsOldName, const OLECHAR* pwcsNewName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RenameElement( pwcsOldName, pwcsNewName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetElementTimes( const OLECHAR* pwcsName, const FILETIME* pctime, const FILETIME* patime, const FILETIME* pmtime ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetElementTimes( pwcsName, pctime, patime, pmtime );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetClass( REFCLSID clsid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetClass( clsid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStateBits( DWORD grfStateBits, DWORD grfMask ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetStateBits( grfStateBits, grfMask );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Stat( STATSTG* pstatstg, DWORD grfStatFlag ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Stat( pstatstg, grfStatFlag );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WriteClassId( REFCLSID rclsid ) const
        {
            auto hr = WriteClassStg( *this, rclsid );
            HCC_COM_CHECK_HRESULT( hr );
        }


        CLSID ReadClassId( ) const
        {
            CLSID result = { 0, };
            auto hr = ReadClassStg( *this, &result );
            HCC_COM_CHECK_HRESULT( hr );
            result;
        }

    };

    /// <summary>
    /// Enables an object to be loaded from or saved to a disk file, rather 
    /// than a storage object or stream. Because the information needed to 
    /// open a file varies greatly from one application to another, the 
    /// implementation of IPersistFile::Load on the object must also open its disk file.
    /// </summary>
    class PersistFile : public Persist
    {
    public:
        typedef Persist Base;
        HCC_COM_STANDARD_METHODS_IMPL( PersistFile, Persist, IPersistFile, IPersist )

        bool IsDirty( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsDirty( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            if ( hr == S_OK )
            {
                return true;
            }
            else 
            {
                return false;
            }
        }

        void Load( LPCOLESTR pszFileName, DWORD mode = 0 ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( pszFileName, mode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Save( LPCOLESTR pszFileName, BOOL remember ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( pszFileName, remember );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SaveCompleted( LPCOLESTR pszFileName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SaveCompleted( pszFileName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool GetCurFile( std::wstring& theFilename ) const
        {
            auto pInterface = GetInterface( );
            Malloc malloc = Malloc::GetMalloc( );
            LPOLESTR result = nullptr;
            auto hr = pInterface->GetCurFile( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            std::wstring s( result );
            malloc.Free( result );
            theFilename = s;
            return hr == S_OK;
        }
    };


    /// <summary>
    /// Enables a container application to pass a storage object to one of 
    /// its contained objects and to load and save the storage object. This 
    /// interface supports the structured storage model, in which each 
    /// contained object has its own storage that is nested within the 
    /// container's storage.
    /// </summary>
    class PersistStorage : public Persist
    {
    public:
        typedef Persist Base;
        HCC_COM_STANDARD_METHODS_IMPL( PersistStorage, Persist, IPersistStorage, IPersist )

        bool IsDirty( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsDirty( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            if ( hr == S_OK )
            {
                return true;
            }
            else 
            {
                return false;
            }
        }

        void InitNew( IStorage* pStg ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InitNew( pStg );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Load( IStorage* pStg ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( pStg );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Save( IStorage* pStgSave, bool sameAsLoad ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Save( pStgSave, sameAsLoad );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SaveCompleted( IStorage* pStgNew ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SaveCompleted( pStgNew );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void HandsOffStorage( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->HandsOffStorage( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// The ILockBytes interface is implemented on a byte array object 
    /// that is backed by some physical storage, such as a disk file, 
    /// global memory, or a database. It is used by a COM compound file 
    /// storage object to give its root storage access to the physical 
    /// device, while isolating the root storage from the details of 
    /// accessing the physical storage.
    /// </summary>
    class LockBytes : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( LockBytes, Unknown, ILockBytes, IUnknown )

        ULONG ReadAt( unsigned long long ulOffset, void* pv, ULONG cb ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->ReadAt( *( (ULARGE_INTEGER*)&ulOffset ), pv, cb, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        ULONG WriteAt( unsigned long long ulOffset, const void* pv, ULONG cb ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->WriteAt( *( (ULARGE_INTEGER*)&ulOffset ), pv, cb, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void Flush( ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->Flush( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetSize( unsigned long long cb ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->SetSize( *( (ULARGE_INTEGER*)&cb ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void LockRegion( unsigned long long libOffset, unsigned long long cb, DWORD dwLockType ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->LockRegion( *( (ULARGE_INTEGER*)&libOffset ), *( (ULARGE_INTEGER*)&cb ), dwLockType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void UnlockRegion( unsigned long long libOffset, unsigned long long cb, DWORD dwLockType ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->UnlockRegion( *( (ULARGE_INTEGER*)&libOffset ), *( (ULARGE_INTEGER*)&cb ), dwLockType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Stat( STATSTG* pstatstg, DWORD grfStatFlag ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->Stat( pstatstg, grfStatFlag );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Enumerates the FORMATETC structures that define the formats and 
    /// media supported by a given data object.
    /// </summary>
    class EnumFORMATETC : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumFORMATETC, Unknown, IEnumFORMATETC, IUnknown )


        static EnumFORMATETC Create( const std::vector<FORMATETC>& elements )
        {
            UINT numberOfElements = UINT( elements.size( ) );
            const FORMATETC* data = elements.data( );
            IEnumFORMATETC* pResult;

            auto hr = CreateFormatEnumerator( numberOfElements, const_cast<FORMATETC*>( data ), &pResult );
            HCC_COM_CHECK_HRESULT( hr );
            return EnumFORMATETC( pResult );
        }

        static EnumFORMATETC Create( const FORMATETC* elements, UINT numberOfElements )
        {
            IEnumFORMATETC* pResult;

            auto hr = CreateFormatEnumerator( numberOfElements, const_cast<FORMATETC*>( elements ), &pResult );
            HCC_COM_CHECK_HRESULT( hr );
            return EnumFORMATETC( pResult );
        }


        bool Next( FORMATETC& theResult ) const
        {
            auto pInterface = GetInterface( );
            IUnknown* pElement = nullptr;
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &theResult, &actual );
            if ( actual )
            {
                return true;
            }
            return false;
        }
        bool Next( ULONG requestedNumberOfElements, std::vector<FORMATETC>& result ) const
        {
            auto pInterface = GetInterface( );
            FORMATETC* pElements = (FORMATETC*)alloca( requestedNumberOfElements * sizeof( FORMATETC ) );
            memset( pElements, 0, requestedNumberOfElements * sizeof( FORMATETC ) );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, pElements, &actual );
            if ( actual )
            {
                result.clear( );
                for ( ULONG i = 0; i < actual; i++ )
                {
                    result.push_back( pElements[i] );
                }
                return true;
            }
            return false;
        }
        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumFORMATETC Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumFORMATETC* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumFORMATETC( pClone );
        }

    };


    /// <summary>
    /// Enumerates the advisory connection information for a data object.
    /// </summary>
    class EnumSTATDATA : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumSTATDATA, Unknown, IEnumSTATDATA, IUnknown )

        bool Next( STATDATA& result ) const
        {
            auto pInterface = GetInterface( );
            IUnknown* pElement = nullptr;
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &result, &actual );
            if ( actual )
            {
                return true;
            }
            return false;
        }
        bool Next( ULONG requestedNumberOfElements, std::vector<STATDATA>& result ) const
        {
            auto pInterface = GetInterface( );
            STATDATA* pElements = (STATDATA*)alloca( requestedNumberOfElements * sizeof( STATDATA ) );
            memset( pElements, 0, requestedNumberOfElements * sizeof( STATDATA ) );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, pElements, &actual );
            if ( actual )
            {
                result.clear( );
                for ( ULONG i = 0; i < actual; i++ )
                {
                    result.push_back( pElements[i] );
                }
                return true;
            }
            return false;
        }
        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumSTATDATA Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATDATA* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATDATA( pClone );
        }

    };


    /// <summary>
    /// The IRootStorage interface contains a single method that switches a 
    /// storage object to a different underlying file and saves the storage 
    /// object to that file. The save operation occurs even with low-memory 
    /// conditions and uncommitted changes to the storage object. A subsequent 
    /// call to IStorage::Commit is guaranteed to not consume additional memory.
    /// </summary>
    class RootStorage : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( RootStorage, Unknown, IRootStorage, IUnknown )

        void SwitchToFile( LPOLESTR pszFile ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SwitchToFile( pszFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// <p>
    /// Enables containers and other objects to receive notifications of data changes, 
    /// view changes, and compound-document changes occurring in objects of interest. 
    /// Container applications, for example, require such notifications to keep cached 
    /// presentations of their linked and embedded objects up-to-date. Calls to IAdviseSink 
    /// methods are asynchronous, so the call is sent and then the next instruction is 
    /// executed without waiting for the call's return.
    /// </p>
    /// <p>
    /// For an advisory connection to exist, the object that is to receive notifications 
    /// must implement IAdviseSink, and the objects in which it is interested must 
    /// implement IOleObject::Advise and IDataObject::DAdvise. In-process objects and 
    /// handlers may also implement IViewObject::SetAdvise. Objects implementing 
    /// IOleObject must support all reasonable advisory methods. To simplify advisory 
    /// notifications, OLE supplies implementations of the IDataAdviseHolder and 
    /// IOleAdviseHolder, which keep track of advisory connections and send notifications 
    /// to the proper sinks through pointers to their IAdviseSink interfaces. 
    /// IViewObject (and its advisory methods) is implemented in the default handler.
    /// </p>
    /// <p>
    /// As shown in the following table, an object that has implemented an advise 
    /// sink registers its interest in receiving certain types of notifications 
    /// by calling the appropriate method.
    /// </p>
    /// <table>
    ///     <tr>
    ///         <th>Call This Method</th><th>To Register for These Notifications</th>
    ///     </tr>
    ///     <tr>
    ///         <td>IOleObject::Advise</td><td>When a document is saved, closed, or renamed.</td>
    ///     </tr>
    ///     <tr>
    ///         <td>IDataObject::DAdvise</td><td>When a document's data changes.</td>
    ///     </tr>
    ///     <tr>
    ///         <td>IViewObject::SetAdvise</td><td>When a document's presentation changes.</td>
    ///     </tr>
    /// </table>
    /// <p>
    /// When an event occurs that applies to a registered notification type, the object 
    /// application calls the appropriate IAdviseSink method. For example, when an 
    /// embedded object closes, it calls the IAdviseSink::OnClose method to notify its 
    /// container. These notifications are asynchronous, occurring after the events 
    /// that trigger them.
    /// </p>
    /// </summary>
    class AdviseSink : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( AdviseSink, Unknown, IAdviseSink, IUnknown )

        void OnDataChange( FORMATETC* pFormatetc, STGMEDIUM* pStgmed ) const
        {
            auto pInterface = GetInterface( );
            pInterface->OnDataChange( pFormatetc, pStgmed );
        }

        void OnViewChange( DWORD dwAspect, LONG lindex ) const
        {
            auto pInterface = GetInterface( );
            pInterface->OnViewChange( dwAspect, lindex );
        }
        void OnRename( IMoniker* pmk ) const
        {
            auto pInterface = GetInterface( );
            pInterface->OnRename( pmk );
        }
        void OnSave( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->OnSave( );
        }
        void OnClose( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->OnClose( );
        }
    };

    /// <summary>
    /// Asynchronous implementation of IAdviseSink
    /// </summary>
    class AsyncAdviseSink : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( AsyncAdviseSink, Unknown, AsyncIAdviseSink, IUnknown )

        void Begin_OnDataChange( FORMATETC* pFormatetc, STGMEDIUM* pStgmed ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Begin_OnDataChange( pFormatetc, pStgmed );
        }
        void Finish_OnDataChange( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Finish_OnDataChange( );
        }
        void Begin_OnViewChange( DWORD dwAspect, LONG lindex ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Begin_OnViewChange( dwAspect, lindex );
        }
        void Finish_OnViewChange( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Finish_OnViewChange( );
        }
        void Begin_OnRename( IMoniker* pmk ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Begin_OnRename( pmk );
        }
        void Finish_OnRename( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Finish_OnRename( );
        }
        void Begin_OnSave( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Begin_OnSave( );
        }
        void Finish_OnSave( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Finish_OnSave( );
        }
        void Begin_OnClose( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Begin_OnClose( );
        }
        void Finish_OnClose( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Finish_OnClose( );
        }
    };


    /// <summary>
    /// The IAdviseSink2 interface is an extension of the IAdviseSink interface, 
    /// adding the method OnLinkSrcChange to the contract to handle a change in 
    /// the moniker of a linked object. This avoids overloading the implementation 
    /// IAdviseSink::OnRename to handle the renaming of both embedded objects and 
    /// linked objects. In applications where different blocks of code might execute 
    /// depending on which of these two similar events has occurred, using the same 
    /// method for both events complicates testing and debugging.
    /// </summary>
    class AdviseSink2 : public AdviseSink
    {
    public:
        typedef AdviseSink Base;
        HCC_COM_STANDARD_METHODS_IMPL( AdviseSink2, AdviseSink, IAdviseSink2, IAdviseSink )

        void OnLinkSrcChange( IMoniker* pmk ) const
        {
            auto pInterface = GetInterface( );
            pInterface->OnLinkSrcChange( pmk );
        }

    };


    /// <summary>
    /// Asynchronous implementation of IAdviseSink2
    /// </summary>
    class AsyncAdviseSink2 : public AsyncAdviseSink
    {
    public:
        typedef AsyncAdviseSink Base;
        HCC_COM_STANDARD_METHODS_IMPL( AsyncAdviseSink2, AsyncAdviseSink, AsyncIAdviseSink2, AsyncIAdviseSink )

        void Begin_OnLinkSrcChange( IMoniker* pmk ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Begin_OnLinkSrcChange( pmk );
        }

        void Finish_OnLinkSrcChange( ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Finish_OnLinkSrcChange( );
        }

    };

    /// <summary>
    /// Represents a generalized global memory handle used for data transfer 
    /// operations by the IAdviseSink, IDataObject, and IOleCache interfaces.
    /// </summary>
    /// 
    class StgMedium
    {
        STGMEDIUM* data;

        StgMedium( const StgMedium& other )
            : data( 0 )
        {
        }

        StgMedium& operator = ( const StgMedium& other )
        {
        }
    public:

        StgMedium( bool allocate = false )
            : data( 0 )
        {
            if ( allocate )
            {
                data = new STGMEDIUM;
                memset( data, 0, sizeof( STGMEDIUM ) );
            }
        }

        StgMedium( StgMedium&& other )
            : data( other.data )
        {
            other.data = nullptr;
        }

        explicit StgMedium( STGMEDIUM* theData )
            : data( theData )
        {
        }

        ~StgMedium( )
        {
            if ( data )
            {
                ReleaseStgMedium( data );
            }
        }

        StgMedium& operator = ( StgMedium&& other )
        {
            data = other.data;
            other.data = nullptr;
        }

        StgMedium& operator = ( STGMEDIUM* theData )
        {
            if ( theData != data )
            {
                if ( data )
                {
                    ReleaseStgMedium( data );
                    delete data;
                    data = nullptr;
                }
                data = theData;
            }
        }

        STGMEDIUM* Data( ) const
        {
            return data;
        }
        STGMEDIUM* get( ) const
        {
            return data;
        }

    };


    enum class DropEffect : DWORD
    {
        None = DROPEFFECT_NONE,
        Copy = DROPEFFECT_COPY,
        Move = DROPEFFECT_MOVE,
        Link = DROPEFFECT_LINK,
        Scroll = DROPEFFECT_SCROLL
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DropEffect, DWORD );


    /// <summary>
    /// <p>
    /// Enables data transfer and notification of changes in data. Data transfer 
    /// methods specify the format of the transferred data along with the medium 
    /// through which the data is to be transferred. Optionally, the data can be 
    /// rendered for a specific target device. In addition to methods for retrieving 
    /// and storing data, the IDataObject interface specifies methods for enumerating 
    /// available formats and managing connections to advisory sinks for handling 
    /// change notifications.
    /// </p>
    /// <p>
    /// The term data object is used to mean any object that supports an implementation 
    /// of the IDataObject interface. Implementations vary, depending on what the data 
    /// object is required to do; in some data objects, the implementation of certain 
    /// methods not supported by the object could simply be the return of E_NOTIMPL. 
    /// For example, some data objects do not allow callers to send them data. Other 
    /// data objects do not support advisory connections and change notifications. However, 
    /// for those data objects that do support change notifications, OLE provides an 
    /// object called a data advise holder. An interface pointer to this holder is 
    /// available through a call to the helper function CreateDataAdviseHolder. A data 
    /// object can have multiple connections, each with its own set of attributes. 
    /// The OLE data advise holder simplifies the task of managing these connections 
    /// and sending the appropriate notifications.
    /// </p>
    /// </summary>
    class DataObject : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( DataObject, Unknown, IDataObject, IUnknown )

        DropEffect DoDragDrop( LPDROPSOURCE pDropSource, DropEffect dropEffect = DropEffect::Copy | DropEffect::Move | DropEffect::Link ) const
        {
            auto pInterface = GetInterface( );

            DWORD result = 0;
            DWORD dwOKEffects = DWORD( dropEffect );
            auto hr = ::DoDragDrop( pInterface, pDropSource, dwOKEffects, &result );

            HCC_COM_CHECK_HRESULT2( hr, pInterface );

            return DropEffect( result );
        }

        StgMedium GetData( FORMATETC* pformatetcIn ) const
        {
            auto pInterface = GetInterface( );
            StgMedium medium( true );
            auto hr = pInterface->GetData( pformatetcIn, medium.Data( ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return medium;
        }
        StgMedium GetDataHere( FORMATETC* pformatetc ) const
        {
            auto pInterface = GetInterface( );
            StgMedium medium( true );
            auto hr = pInterface->GetDataHere( pformatetc, medium.Data( ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return medium;
        }
        bool QueryGetData( FORMATETC* pformatetc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryGetData( pformatetc );
            return hr == S_OK;
        }

        // returns false if DATA_S_SAMEFORMATETC
        bool GetCanonicalFormatEtc( FORMATETC* pformatectIn, FORMATETC* pformatetcOut ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCanonicalFormatEtc( pformatectIn, pformatetcOut );
            if ( hr == S_OK )
            {
                return true;
            }
            else if ( hr == DATA_S_SAMEFORMATETC )
            {
                return false;
            }
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return false;
        }

        void SetData( FORMATETC* pformatetc, STGMEDIUM* pmedium, BOOL fRelease ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetData( pformatetc, pmedium, fRelease );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumFORMATETC EnumFormatEtc( DWORD dwDirection ) const
        {
            auto pInterface = GetInterface( );
            IEnumFORMATETC* pEnum = nullptr;
            auto hr = pInterface->EnumFormatEtc( dwDirection, &pEnum );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumFORMATETC( pEnum );
        }

        DWORD DAdvise( FORMATETC* pformatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->DAdvise( pformatetc, advf, pAdvSink, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void DUnadvise( DWORD dwConnection ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DUnadvise( dwConnection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumSTATDATA EnumDAdvise( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATDATA* pEnum = nullptr;
            auto hr = pInterface->EnumDAdvise( &pEnum );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATDATA( pEnum );
        }
    };


    /// <summary>
    /// <p>
    /// Creates and manages advisory connections between a data object and 
    /// one or more advise sinks. Its methods are intended to be used to 
    /// implement the advisory methods of IDataObject. IDataAdviseHolder is 
    /// implemented on an advise holder object. Its methods establish and 
    /// delete data advisory connections and send notification of change in 
    /// data from a data object to an object that requires this notification, 
    /// such as an OLE container, which must contain an advise sink.
    /// </p>
    /// <p>
    /// Advise sinks are objects that require notification of change in the 
    /// data the object contains and implement the IAdviseSink interface. 
    /// Advise sinks are also usually associated with OLE compound document 
    /// containers.
    /// </p>
    /// </summary>
    class DataAdviseHolder : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( DataAdviseHolder, Unknown, IDataAdviseHolder, IUnknown )

        static DataAdviseHolder Create( )
        {
            IDataAdviseHolder* pResult = nullptr;
            auto hr = CreateDataAdviseHolder( &pResult );
            HCC_COM_CHECK_HRESULT( hr );
            return DataAdviseHolder( pResult );
        }

        DWORD Advise( IDataObject* pDataObject, FORMATETC* pFetc, DWORD advf, IAdviseSink* pAdvise ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->Advise( pDataObject, pFetc, advf, pAdvise, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void Unadvise( DWORD dwConnection ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unadvise( dwConnection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumSTATDATA EnumAdvise( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATDATA* pEnum = nullptr;
            auto hr = pInterface->EnumAdvise( &pEnum );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATDATA( pEnum );
        }

        void SendOnDataChange( IDataObject* pDataObject, DWORD advf ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SendOnDataChange( pDataObject, 0, advf );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// Provides COM servers and applications with the ability to selectively 
    /// handle incoming and outgoing COM messages while waiting for responses 
    /// from synchronous calls. Filtering messages helps to ensure that calls 
    /// are handled in a manner that improves performance and avoids deadlocks. 
    /// COM messages can be synchronous, asynchronous, or input-synchronized; 
    /// the majority of interface calls are synchronous.
    /// </summary>
    class MessageFilter : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( MessageFilter, Unknown, IMessageFilter, IUnknown )

        DWORD HandleInComingCall( DWORD dwCallType, HTASK htaskCaller, DWORD dwTickCount, LPINTERFACEINFO lpInterfaceInfo ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->HandleInComingCall( dwCallType, htaskCaller, dwTickCount, lpInterfaceInfo );
            return result;
        }

        DWORD RetryRejectedCall( HTASK htaskCallee, DWORD dwTickCount, DWORD dwRejectType ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->RetryRejectedCall( htaskCallee, dwTickCount, dwRejectType );
            return result;
        }

        DWORD MessagePending( HTASK htaskCallee, DWORD dwTickCount, DWORD dwPendingType ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->MessagePending( htaskCallee, dwTickCount, dwPendingType );
            return result;
        }
    };

    /// <summary>
    /// Specifies a method that retrieves a class object.
    /// </summary>
    class ClassActivator : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ClassActivator, Unknown, IClassActivator, IUnknown )

        template<typename T>
        T GetClassObject( REFCLSID rclsid, DWORD dwClassContext, LCID locale ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* pRequestedInterface = nullptr;
            auto hr = pInterface->GetClassObject( rclsid, dwClassContext, locale, __uuidof( T::InterfaceType ), (void**)&pRequestedInterface );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return T( pRequestedInterface );
        }
    };


    /// <summary>
    /// The IFillLockBytes interface enables downloading code to write data 
    /// asynchronously to a structured storage byte array. When the downloading 
    /// code has new data available, it calls IFillLockBytes::FillAppend or 
    /// IFillLockBytes::FillAt to write the data to the byte array. An application 
    /// attempting to access this data, through calls to the ILockBytes interface, 
    /// can do so even as the downloader continues to make calls to IFillLockBytes. 
    /// If the application attempts to access data that has not already been downloaded 
    /// through a call to IFillLockBytes, then ILockBytes returns a new error, E_PENDING.
    /// </summary>
    class FillLockBytes : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( FillLockBytes, Unknown, IFillLockBytes, IUnknown )

        ULONG FillAppend( const void* pv, ULONG cb ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->FillAppend( pv, cb, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        ULONG FillAt( unsigned long long ulOffset, const void* pv, ULONG cb ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->FillAt( *( (ULARGE_INTEGER*)&ulOffset ), pv, cb, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void SetFillSize( unsigned long long ulSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFillSize( *( (ULARGE_INTEGER*)&ulSize ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Terminate( bool bCanceled ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Terminate( bCanceled );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// Enables applications and other objects to receive notifications 
    /// of changes in the progress of a downloading operation.
    /// </summary>
    class ProgressNotify : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ProgressNotify, Unknown, IProgressNotify, IUnknown )

        DWORD OnProgress( DWORD dwProgressCurrent, DWORD dwProgressMaximum, bool fAccurate, bool fOwner ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnProgress( dwProgressCurrent, dwProgressMaximum, fAccurate, fOwner );
            if ( ( hr != E_PENDING ) &&
                ( hr != STG_S_RETRYNOW ) &&
                ( hr != STG_S_BLOCK ) &&
                ( hr != STG_S_MONITORING ) &&
                ( FAILED( hr ) ) )
            {
                CheckHRESULT( hr, pInterface );
            }
            return hr;
        }
    };

    /// <summary>
    /// <p>
    /// The ILayoutStorage interface enables an application to optimize the 
    /// layout of its compound files for efficient downloading across a slow 
    /// link. The goal is to enable a browser or other application to download 
    /// data in the order in which it will actually be required.
    /// </p>
    /// <p>
    /// To optimize a compound file, an application calls CopyTo to layout a 
    /// doc-file, thus improving performance in most scenarios.
    /// </p>
    /// </summary>
    class LayoutStorage : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( LayoutStorage, Unknown, ILayoutStorage, IUnknown )

        void LayoutScript( StorageLayout* pStorageLayout, DWORD nEntries ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->LayoutScript( pStorageLayout, nEntries, 0 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BeginMonitor( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->BeginMonitor( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EndMonitor( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EndMonitor( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReLayoutDocfile( OLECHAR* pwcsNewDfName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReLayoutDocfile( pwcsNewDfName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReLayoutDocfileOnILockBytes( ILockBytes* pILockBytes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReLayoutDocfileOnILockBytes( pILockBytes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Provides a semaphore that can be used to provide temporarily exclusive 
    /// access to a shared resource such as a file.
    /// </summary>
    class BlockingLock : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( BlockingLock, Unknown, IBlockingLock, IUnknown )

        void Lock( DWORD timeout ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Lock( timeout );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Lock( const TimeSpan& timeout ) const
        {
            auto pInterface = GetInterface( );
            DWORD to = (DWORD)timeout.TotalMilliseconds( );
            auto hr = pInterface->Lock( to );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Unlock( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unlock( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// The IDirectWriterLock interface enables a single writer to obtain 
    /// exclusive write access to a root storage object opened in direct 
    /// mode while allowing concurrent access by multiple readers. This 
    /// single-writer, multiple-reader mode does not require the overhead 
    /// of making a snapshot copy of the storage for the readers.
    /// </summary>
    class DirectWriterLock : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( DirectWriterLock, Unknown, IDirectWriterLock, IUnknown )

        void WaitForWriteAccess( DWORD dwTimeout ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WaitForWriteAccess( dwTimeout );
            if ( hr == STG_E_INUSE )
            {
                throw TimeoutException( L"Timeout in WaitForWriteAccess" );
            }
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReleaseWriteAccess( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReleaseWriteAccess( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool HaveWriteAccess( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->HaveWriteAccess( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            if ( hr == S_OK )
            {
                return true;
            }
            else 
            {
                return false;
            }
        }
    };


    /// <summary>
    /// Transfers the foreground window to the process hosting the COM server.
    /// </summary>
    class ForegroundTransfer : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ForegroundTransfer, Unknown, IForegroundTransfer, IUnknown )

        void AllowForegroundTransfer( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AllowForegroundTransfer( nullptr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Used by ISurrogateService to prevent the process from terminating 
    /// due to a time-out.
    /// </summary>
    class ProcessLock : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ProcessLock, Unknown, IProcessLock, IUnknown )

        ULONG AddRefOnProcess( ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->AddRefOnProcess( );
            return result;
        }

        ULONG ReleaseRefOnProcess( ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->ReleaseRefOnProcess( );
            return result;
        }
    };


    /// <summary>
    /// Used to initialize, launch, and release a COM+ application. 
    /// You can also refresh the catalog and shut down the process.
    /// </summary>
    class SurrogateService : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( SurrogateService, Unknown, ISurrogateService, IUnknown )

        bool Init( REFGUID rguidProcessID, IProcessLock* pProcessLock ) const
        {
            auto pInterface = GetInterface( );
            BOOL applicationAware = FALSE;
            auto hr = pInterface->Init( rguidProcessID, pProcessLock, &applicationAware );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return applicationAware != FALSE;
        }

        void ApplicationLaunch( REFGUID rguidApplID, ApplicationType appType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ApplicationLaunch( rguidApplID, appType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void ApplicationFree( REFGUID rguidApplID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ApplicationFree( rguidApplID );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CatalogRefresh( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CatalogRefresh( 0 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ProcessShutdown( ShutdownType shutdownType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ProcessShutdown( shutdownType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// The ITypeComp interface provides a fast way to access information 
    /// that compilers need when binding to and instantiating structures and 
    /// interfaces. Binding is the process of mapping names to types and type 
    /// members.
    /// </summary>
    class TypeComp : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( TypeComp, Unknown, ITypeComp, IUnknown )

        void Bind( LPOLESTR szName, ULONG lHashVal, WORD wFlags, ITypeInfo** ppTInfo, DESCKIND* pDescKind, BINDPTR* pBindPtr ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Bind( szName, lHashVal, wFlags, ppTInfo, pDescKind, pBindPtr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BindType( LPOLESTR szName, ULONG lHashVal, ITypeInfo** ppTInfo, ITypeComp** ppTComp ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->BindType( szName, lHashVal, ppTInfo, ppTComp );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    
    


    class TypeAttributes;
    class TypeLibEntry;
    class TypeLib;
    /// <summary>
    /// ITypeInfo is an interface used for reading information about objects. 
    /// For example, an object browser tool can use ITypeInfo to extract information 
    /// about the characteristics and capabilities of objects from type libraries.
    /// </summary>
    class TypeInfo : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( TypeInfo, Unknown, ITypeInfo, IUnknown )

        void GetTypeAttr( TYPEATTR** ppTypeAttr ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetTypeAttr( ppTypeAttr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline TypeAttributes GetTypeAttributes( ) const;


        TypeComp GetTypeComp( ) const
        {
            auto pInterface = GetInterface( );
            ITypeComp* result = nullptr;
            auto hr = pInterface->GetTypeComp( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return TypeComp( result );
        }

        void GetFuncDesc( UINT index, FUNCDESC** ppFuncDesc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFuncDesc( index, ppFuncDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetVarDesc( UINT index, VARDESC** ppVarDesc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetVarDesc( index, ppVarDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetNames( MEMBERID memid, BSTR* rgBstrNames, UINT cMaxNames, UINT* pcNames ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNames( memid, rgBstrNames, cMaxNames, pcNames );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRefTypeOfImplType( UINT index, HREFTYPE* pRefType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetRefTypeOfImplType( index, pRefType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        INT GetImplTypeFlags( UINT index ) const
        {
            auto pInterface = GetInterface( );
            int result = 0;
            auto hr = pInterface->GetImplTypeFlags( index, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void GetIDsOfNames( LPOLESTR* rgszNames, UINT cNames, MEMBERID* pMemId ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIDsOfNames( rgszNames, cNames, pMemId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HRESULT Invoke( PVOID pvInstance, MEMBERID memid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Invoke( pvInstance, memid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr );
            return hr;
        }

        void GetDocumentation( MEMBERID memid, SysString& theName, SysString& theDocString, DWORD& pdwHelpContext, SysString& theHelpFile ) const
        {
            auto pInterface = GetInterface( );
            BSTR bstrName;
            BSTR bstrDocString;
            BSTR bstrHelpFile;
            auto hr = pInterface->GetDocumentation( memid, &bstrName, &bstrDocString, &pdwHelpContext, &bstrHelpFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            theName.Attach( bstrName );
            theDocString.Attach( bstrDocString );
            theHelpFile.Attach( bstrHelpFile );
        }

        SysString GetName( )
        {
            auto pInterface = GetInterface( );
            BSTR bstrName;
            auto hr = pInterface->GetDocumentation( MEMBERID_NIL, &bstrName, nullptr, nullptr, nullptr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            SysString result( bstrName, true );
            return result;
        }



        void GetDllEntry( MEMBERID memid, INVOKEKIND invKind, SysString& theDllName, SysString& theName, WORD& pwOrdinal ) const
        {
            auto pInterface = GetInterface( );
            BSTR bstrName;
            BSTR bstrDllName;
            auto hr = pInterface->GetDllEntry( memid, invKind, &bstrDllName, &bstrName, &pwOrdinal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            theName.Attach( bstrName );
            theDllName.Attach( bstrDllName );
        }

        TypeInfo GetRefTypeInfo( HREFTYPE hRefType ) const
        {
            auto pInterface = GetInterface( );
            ITypeInfo* result;
            auto hr = pInterface->GetRefTypeInfo( hRefType, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return TypeInfo( result );
        }

        void AddressOfMember( MEMBERID memid, INVOKEKIND invKind, PVOID* ppv ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddressOfMember( memid, invKind, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateInstance( IUnknown* pUnkOuter, REFIID riid, PVOID* ppvObj ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateInstance( pUnkOuter, riid, ppvObj );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
        T CreateInstance( REFIID riid, IUnknown* pUnkOuter = nullptr ) const
        {
            auto pInterface = GetInterface( );
            IUnknown* pUnknown = nullptr;
            auto hr = pInterface->CreateInstance( pUnkOuter, riid, (void**)&pUnknown );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );

            typename T::InterfaceType* result;
            hr = pUnknown->QueryInterface( __uuidof( T::InterfaceType ), (void**)&result );
            pUnknown->Release( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );

            return T( result );
        }


        void GetMops( MEMBERID memid, BSTR* pBstrMops ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMops( memid, pBstrMops );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline TypeLib GetContainingTypeLib( UINT& pIndex ) const;
        inline TypeLibEntry GetContainingTypeLib( ) const;

        void ReleaseTypeAttr( TYPEATTR* pTypeAttr ) const
        {
            auto pInterface = GetInterface( );
            pInterface->ReleaseTypeAttr( pTypeAttr );
        }

        void ReleaseFuncDesc( FUNCDESC* pFuncDesc ) const
        {
            auto pInterface = GetInterface( );
            pInterface->ReleaseFuncDesc( pFuncDesc );
        }
        void ReleaseVarDesc( VARDESC* pVarDesc ) const
        {
            auto pInterface = GetInterface( );
            pInterface->ReleaseVarDesc( pVarDesc );
        }

        inline RecordInfo GetRecordInfo( ) const;
        

    };

    class TypeAttributes
    {
        TypeInfo typeInfo_;
        TYPEATTR* typeAttr_ = nullptr;
    public:
        TypeAttributes( const TypeInfo& typeInfo )
            : typeInfo_( typeInfo )
        { 
            typeInfo_.GetTypeAttr( &typeAttr_ );
        }

        TypeAttributes( const TypeAttributes& other ) = delete;
        TypeAttributes& operator = ( const TypeAttributes& other ) = delete;

        TypeAttributes( TypeAttributes&& other ) noexcept
            : typeInfo_( std::move( other.typeInfo_ ) ), typeAttr_( other.typeAttr_ )
        {
            other.typeAttr_ = nullptr;
        }
        TypeAttributes& operator = ( TypeAttributes&& other ) noexcept
        {
            std::swap( typeInfo_, other.typeInfo_ );
            std::swap( typeAttr_, other.typeAttr_ );
            return *this;
        }


        ~TypeAttributes( )
        {
            if ( typeAttr_ )
            {
                typeInfo_.ReleaseTypeAttr( typeAttr_ );
            }
        }

        explicit operator bool( ) const noexcept
        {
            return typeAttr_ != nullptr;
        }

        Guid Id( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->guid;
            }
            return {};
        }

        LCID LocaleId( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->lcid;
            }
            return {};
        }

        MEMBERID Constructor( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->memidConstructor;
            }
            return {};
        }

        MEMBERID Destructor( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->memidDestructor;
            }
            return {};
        }

        size_t InstanceSize( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->cbSizeInstance;
            }
            return {};
        }

        TYPEKIND TypeKind( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->typekind;
            }
            return {};
        }

        size_t NumberOfFunctions( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->cFuncs;
            }
            return {};
        }

        size_t NumberOfFields( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->cVars;
            }
            return {};
        }

        size_t NumberOfImplementedInterfaces( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->cImplTypes;
            }
            return {};
        }

        size_t SizeOfVirtualFunctionTable( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->cbSizeVft;
            }
            return {};
        }

        size_t Alignment( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->cbAlignment == 0? static_cast<size_t>(MaxUInt16) + 1 : typeAttr_->cbAlignment;
            }
            return {};
        }

        TYPEFLAGS TypeFlags( ) const
        {
            if ( typeAttr_ )
            {
                return static_cast< TYPEFLAGS >( typeAttr_->wTypeFlags );
            }
            return {};
        }

        size_t MajorVersion( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->wMajorVerNum;
            }
            return {};
        }

        size_t MinorVersion( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->wMinorVerNum;
            }
            return {};
        }

        std::pair<UInt16, UInt16> Version( ) const
        {
            if ( typeAttr_ )
            {
                return std::make_pair( typeAttr_->wMajorVerNum, typeAttr_->wMinorVerNum);
            }
            return {};
        }

        const TYPEDESC* AliasedTypeDescriptor( ) const
        {
            if ( typeAttr_ )
            {
                if ( typeAttr_->typekind == TKIND_ALIAS )
                {
                    return &typeAttr_->tdescAlias;
                }
            }
            return {};
        }

        USHORT IDLFlags( ) const
        {
            if ( typeAttr_ )
            {
                return typeAttr_->idldescType.wIDLFlags;
            }
            return {};
        }
    };

    inline TypeAttributes TypeInfo::GetTypeAttributes( ) const
    {
        return TypeAttributes( *this );
    }

    class TypeLibAttributes;
    /// <summary>
    /// Represents a type library, the data that describes a set of objects. 
    /// A type library can be a stand-alone binary file (.TLB), a resource 
    /// in a dynamic link library or executable file (.DLL, .OLB, or .EXE).
    /// </summary>
    class TypeLib : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( TypeLib, Unknown, ITypeLib, IUnknown )




        UINT GetTypeInfoCount( ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->GetTypeInfoCount( );
            return result;
        }

        TypeInfo GetTypeInfo( UINT index ) const
        {
            auto pInterface = GetInterface( );
            ITypeInfo* result;
            auto hr = pInterface->GetTypeInfo( index, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return TypeInfo( result );
        }

        TYPEKIND GetTypeInfoType( UINT index ) const
        {
            auto pInterface = GetInterface( );
            TYPEKIND result;
            auto hr = pInterface->GetTypeInfoType( index, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        TypeInfo GetTypeInfoOfGuid( REFGUID guid ) const
        {
            auto pInterface = GetInterface( );
            ITypeInfo* result;
            auto hr = pInterface->GetTypeInfoOfGuid( guid, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return TypeInfo( result );
        }

        TypeInfo GetTypeInfoOfGuid( REFGUID guid, TYPEKIND expectedTypeKind ) const
        {
            auto typeInfo = GetTypeInfoOfGuid( guid );
            auto attributes = typeInfo.GetTypeAttributes( );
            auto typeKind = attributes.TypeKind( );
            if ( typeKind != expectedTypeKind && typeKind == TKIND_ALIAS)
            {
                auto hreftype = attributes.AliasedTypeDescriptor( )->hreftype;
                auto aliasedTypeInfo = typeInfo.GetRefTypeInfo( hreftype );
                return aliasedTypeInfo;
            }
            return typeInfo;
        }


        void GetLibAttr( TLIBATTR** ppTLibAttr ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLibAttr( ppTLibAttr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline TypeLibAttributes GetLibAttributes( ) const;

        TypeComp GetTypeComp( ) const
        {
            auto pInterface = GetInterface( );
            ITypeComp* result;
            auto hr = pInterface->GetTypeComp( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return TypeComp( result );
        }

        void GetDocumentation( INT index, BSTR* pBstrName, BSTR* pBstrDocString, DWORD* pdwHelpContext, BSTR* pBstrHelpFile ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDocumentation( index, pBstrName, pBstrDocString, pdwHelpContext, pBstrHelpFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsName( LPOLESTR szNameBuf, ULONG lHashVal ) const
        {
            auto pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->IsName( szNameBuf, lHashVal, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result != FALSE;
        }

        void FindName( LPOLESTR szNameBuf, ULONG lHashVal, ITypeInfo** ppTInfo, MEMBERID* rgMemId, USHORT* pcFound ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->FindName( szNameBuf, lHashVal, ppTInfo, rgMemId, pcFound );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReleaseTLibAttr( TLIBATTR* pTLibAttr ) const
        {
            auto pInterface = GetInterface( );
            pInterface->ReleaseTLibAttr( pTLibAttr );
        }

        void Unregister( ) const
        {
            TLIBATTR* tlibAttrPtr = nullptr;
            GetLibAttr( &tlibAttrPtr );
            TLIBATTR tlibAttr = *tlibAttrPtr;
            ReleaseTLibAttr( tlibAttrPtr );
            auto hr = UnRegisterTypeLib( tlibAttr.guid, tlibAttr.wMajorVerNum, tlibAttr.wMinorVerNum, tlibAttr.lcid, tlibAttr.syskind );
            if ( FAILED( hr ) )
            {
                auto pInterface = GetInterface( );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        }

    };

    inline TypeLib TypeInfo::GetContainingTypeLib( UINT& index ) const
    {
        ITypeLib* ptr = nullptr;
        auto pInterface = GetInterface( );
        auto hr = pInterface->GetContainingTypeLib( &ptr,&index );
        HCC_COM_CHECK_HRESULT2( hr, pInterface );
        return TypeLib( ptr );
    }

    class TypeLibAttributes
    {
        TypeLib typeLib_;
        TLIBATTR* tlibAttr_ = nullptr;
    public:
        TypeLibAttributes( const TypeLib& typeLib )
            : typeLib_( typeLib )
        {
            typeLib_.GetLibAttr( &tlibAttr_ );
        }

        TypeLibAttributes( const TypeLibAttributes& other ) = delete;
        TypeLibAttributes& operator = ( const TypeLibAttributes& other ) = delete;

        TypeLibAttributes( TypeLibAttributes&& other ) noexcept
            : typeLib_( std::move( other.typeLib_ ) ), tlibAttr_(other.tlibAttr_)
        {
            other.tlibAttr_ = nullptr;
        }
        TypeLibAttributes& operator = ( TypeLibAttributes&& other ) noexcept
        {
            std::swap( typeLib_, other.typeLib_ );
            std::swap( tlibAttr_, other.tlibAttr_ );
            return *this;
        }


        ~TypeLibAttributes( )
        {
            if ( tlibAttr_ )
            {
                typeLib_.ReleaseTLibAttr( tlibAttr_ );
            }
        }

        explicit operator bool( ) const
        {
            return tlibAttr_ != nullptr;
        }


        Guid Id( ) const
        {
            if ( tlibAttr_ )
            {
                return tlibAttr_->guid;
            }
            return {};
        }

        LCID LocaleId( ) const
        {
            if ( tlibAttr_ )
            {
                return tlibAttr_->lcid;
            }
            return {};
        }

        SYSKIND SysKind( ) const
        {
            if ( tlibAttr_ )
            {
                return tlibAttr_->syskind;
            }
            return {};
        }

        size_t MajorVersion( ) const
        {
            if ( tlibAttr_ )
            {
                return tlibAttr_->wMajorVerNum;
            }
            return {};
        }

        size_t MinorVersion( ) const
        {
            if ( tlibAttr_ )
            {
                return tlibAttr_->wMinorVerNum;
            }
            return {};
        }

        std::pair<UInt16, UInt16> Version( ) const
        {
            if ( tlibAttr_ )
            {
                return std::make_pair(tlibAttr_->wMajorVerNum, tlibAttr_->wMinorVerNum);
            }
            return {};
        }

        UInt16 Flags( ) const
        {
            if ( tlibAttr_ )
            {
                return tlibAttr_->wLibFlags;
            }
            return {};
        }

        bool IsRestricted( ) const
        {
            if ( tlibAttr_ )
            {
                return (tlibAttr_->wLibFlags & LIBFLAG_FRESTRICTED) != 0;
            }
            return false;
        }

        bool IsControl( ) const
        {
            if ( tlibAttr_ )
            {
                return ( tlibAttr_->wLibFlags & LIBFLAG_FCONTROL ) != 0;
            }
            return false;
        }

        bool IsHidden( ) const
        {
            if ( tlibAttr_ )
            {
                return ( tlibAttr_->wLibFlags & LIBFLAG_FHIDDEN ) != 0;
            }
            return false;
        }

        bool HasDiskImage( ) const
        {
            if ( tlibAttr_ )
            {
                return ( tlibAttr_->wLibFlags & LIBFLAG_FHASDISKIMAGE ) != 0;
            }
            return false;
        }
    };

    inline TypeLibAttributes TypeLib::GetLibAttributes( ) const
    {
        return TypeLibAttributes( *this );
    }


    class TypeLibEntry
    {
        TypeLib typeLib_;
        UInt32 index_ = 0;
    public:
        TypeLibEntry( ) = default;

        TypeLibEntry( const TypeLib& typeLib, UInt32 index )
            : typeLib_( typeLib ), index_( index )
        { }

        const TypeLib& TypeLib( ) const
        {
            return typeLib_;
        }
        UInt32 Index( ) const
        {
            return index_;
        }
    };

    inline TypeLibEntry TypeInfo::GetContainingTypeLib( ) const
    {
        UINT index = 0;
        ITypeLib* ptr = nullptr;
        auto pInterface = GetInterface( );
        auto hr = pInterface->GetContainingTypeLib( &ptr, &index );
        HCC_COM_CHECK_HRESULT2( hr, pInterface );
        return TypeLibEntry(TypeLib( ptr ), index );
    }
    

    /// <summary>
    /// Represents a type library, the data that describes a set of objects.
    /// </summary>
    class TypeLib2 : public TypeLib
    {
    public:
        using Base = TypeLib;
        HCC_COM_STANDARD_METHODS_IMPL( TypeLib2, TypeLib, ITypeLib2, ITypeLib )


        static TypeLib2 LoadTypeLib( const std::wstring& filename, REGKIND registrationkind = REGKIND::REGKIND_NONE )
        {
            ITypeLib* tlib = nullptr;
            auto hr = LoadTypeLibEx( filename.c_str( ), registrationkind, &tlib );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            ITypeLib2* itf = nullptr;
            hr = tlib->QueryInterface( &itf );
            if ( FAILED( hr ) )
            {
                tlib->Release( );
                CheckHRESULT( hr );
            }
            TypeLib2 result( itf );
            tlib->Release( );
            return result;
        }

        void GetCustData( __RPC__in REFGUID guid, __RPC__out VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCustData( guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Variant GetCustData( __RPC__in REFGUID guid ) const
        {
            Variant result;
            GetCustData( guid, &result );
            return result;
        }

        
        void GetLibStatistics( ULONG* pcUniqueNames, ULONG* pcchUniqueNames ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLibStatistics( pcUniqueNames, pcchUniqueNames );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void GetDocumentation2( INT index, LCID lcid, _Outptr_opt_  BSTR* pbstrHelpString, DWORD* pdwHelpStringContext, _Outptr_opt_  BSTR* pbstrHelpStringDll ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDocumentation2( index, lcid, pbstrHelpString, pdwHelpStringContext, pbstrHelpStringDll );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void GetAllCustData( __RPC__out CUSTDATA* pCustData ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAllCustData( pCustData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


    };

    /// <summary>
    /// Exposes objects, methods and properties to programming tools and 
    /// other applications that support Automation. COM components implement 
    /// the IDispatch interface to enable access by Automation clients.
    /// </summary>
    class Dispatch : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( Dispatch, Unknown, IDispatch, IUnknown )


        UINT GetTypeInfoCount( ) const
        {
            auto pInterface = GetInterface( );
            UINT result = 0;
            auto hr = pInterface->GetTypeInfoCount( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        TypeInfo GetTypeInfo( UINT iTInfo, LCID lcid = LOCALE_SYSTEM_DEFAULT ) const
        {
            auto pInterface = GetInterface( );
            ITypeInfo* result;
            auto hr = pInterface->GetTypeInfo( iTInfo, lcid, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return TypeInfo( result );
        }

        void GetIDsOfNames( LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIDsOfNames( IID_NULL, rgszNames, cNames, lcid, rgDispId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        std::shared_ptr< std::vector< DISPID > > GetIDsOfNames( const std::shared_ptr< std::vector <std::wstring> > names, LCID lcid = LOCALE_SYSTEM_DEFAULT ) const
        {
            auto pInterface = GetInterface( );

            std::shared_ptr< std::vector< DISPID > > result = std::make_shared< std::vector< DISPID > >( names->size( ) );

            std::vector< const wchar_t* > nms;
            nms.reserve( names->size( ) );

            for ( auto it = names->begin( ); it != names->end( ); it++ )
            {
                const std::wstring& s = *it;
                const wchar_t* ptr = s.c_str( );
                nms.push_back( ptr );
            }

            UINT cNames = UINT( nms.size( ) );
            auto hr = pInterface->GetIDsOfNames( IID_NULL, (LPOLESTR*)nms.data( ), cNames, lcid, result->data( ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }


        void Invoke( DISPID dispIdMember, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Invoke( dispIdMember, IID_NULL, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Extends Dispatch with enhanced support for dynamic scripting languages.
    /// </summary>
    class DispatchEx : public Dispatch
    {
    public:
        typedef Dispatch Base;
        HCC_COM_STANDARD_METHODS_IMPL( DispatchEx, Dispatch, IDispatchEx, IDispatch )

        void GetDispID( BSTR bstrName, DWORD grfdex, DISPID* pid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDispID( bstrName, grfdex, pid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DISPID GetDispID( BSTR bstrName, DWORD grfdex ) const
        {
            DISPID result = 0;
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDispID( bstrName, grfdex, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void InvokeEx( DISPID id, LCID lcid, WORD wFlags, DISPPARAMS* pdp, VARIANT* pvarRes, EXCEPINFO* pei, IServiceProvider* pspCaller ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InvokeEx( id, lcid, wFlags, pdp, pvarRes, pei, pspCaller );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteMemberByName( BSTR bstrName, DWORD grfdex ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteMemberByName( bstrName, grfdex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteMemberByDispID( DISPID id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteMemberByDispID( id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetMemberProperties( DISPID id, DWORD grfdexFetch, DWORD* pgrfdex ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMemberProperties( id, grfdexFetch, pgrfdex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DWORD GetMemberProperties( DISPID id, DWORD grfdexFetch ) const
        {
            DWORD result = 0;
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMemberProperties( id, grfdexFetch, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void GetMemberName( DISPID id, BSTR* pbstrName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMemberName( id, pbstrName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        std::wstring GetMemberName( DISPID id ) const
        {
            BSTR bstrName = nullptr;
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMemberName( id, &bstrName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            auto length = SysStringLen( bstrName );
            auto result = std::wstring( (const wchar_t*)bstrName, std::wstring::size_type( length ) );
            SysFreeString( bstrName );
            return result;
        }


        void GetNextDispID( DWORD grfdex, DISPID id, DISPID* pid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNextDispID( grfdex, id, pid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DISPID GetNextDispID( DWORD grfdex, DISPID id ) const
        {
            DISPID result = 0;
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNextDispID( grfdex, id, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }


        void GetNameSpaceParent( IUnknown** ppunk ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNameSpaceParent( ppunk );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Unknown GetNameSpaceParent( ) const
        {
            IUnknown* result = nullptr;
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNameSpaceParent( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Unknown( result );
        }
    };

    /// <summary>
    /// Ensures that error information can be propagated up the call 
    /// chain correctly. Automation objects that use the error handling 
    /// interfaces must implement ISupportErrorInfo.
    /// </summary>
    class SupportErrorInfo : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( SupportErrorInfo, Unknown, ISupportErrorInfo, IUnknown )

        bool InterfaceSupportsErrorInfo( REFIID riid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InterfaceSupportsErrorInfo( riid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            if ( hr == S_OK )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };


    /// <summary>
    /// Provides detailed contextual error information.
    /// </summary>
    class ErrorInfo : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ErrorInfo, Unknown, IErrorInfo, IUnknown )


        static ErrorInfo GetErrorInfo( )
        {
            IErrorInfo* pErrorInfo = nullptr;
            auto hr = ::GetErrorInfo( 0, &pErrorInfo );
            if ( hr == S_OK )
            {
                return ErrorInfo( pErrorInfo );
            }
            return ErrorInfo( );
        }

        GUID GetGUID( ) const
        {
            auto pInterface = GetInterface( );
            GUID result = { 0, };
            auto hr = pInterface->GetGUID( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        SysString GetSource( ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = nullptr;
            auto hr = pInterface->GetSource( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return SysString( result, true );
        }

        SysString GetDescription( ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = nullptr;
            auto hr = pInterface->GetDescription( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return SysString( result, true );
        }

        SysString GetHelpFile( ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = nullptr;
            auto hr = pInterface->GetHelpFile( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return SysString( result, true );
        }

        DWORD GetHelpContext( DWORD* pdwHelpContext ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->GetHelpContext( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }
    };


    /// <summary>
    /// Returns error information.
    /// </summary>
    class CreateErrorInfo : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( CreateErrorInfo, Unknown, ICreateErrorInfo, IUnknown )

        void SetGUID( REFGUID rguid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetGUID( rguid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetSource( LPOLESTR szSource ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSource( szSource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDescription( LPOLESTR szDescription ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetDescription( szDescription );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpFile( LPOLESTR szHelpFile ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpFile( szHelpFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpContext( DWORD dwHelpContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpContext( dwHelpContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        static CreateErrorInfo Create( )
        {
            ICreateErrorInfo* pCreateErrorInfo = nullptr;
            auto hr = ::CreateErrorInfo( &pCreateErrorInfo );
            HCC_COM_CHECK_HRESULT( hr );
            return CreateErrorInfo( pCreateErrorInfo );
        }


        static void SetErrorInfo( REFGUID rguid, LPOLESTR szSource, LPOLESTR szDescription = nullptr, LPOLESTR szHelpFile = nullptr, DWORD dwHelpContext = 0 )
        {
            ICreateErrorInfo* pCreateErrorInfo = nullptr;
            auto hr = ::CreateErrorInfo( &pCreateErrorInfo );
            HCC_COM_CHECK_HRESULT( hr );
            CreateErrorInfo cei( pCreateErrorInfo );
            cei.SetGUID( rguid );
            if ( szSource )
            {
                cei.SetSource( szSource );
            }
            if ( szDescription )
            {
                cei.SetDescription( szDescription );
            }
            if ( szHelpFile )
            {
                cei.SetHelpFile( szHelpFile );
            }
            cei.SetHelpContext( dwHelpContext );

            ErrorInfo ei = cei.As<ErrorInfo>( );
            hr = ::SetErrorInfo( 0, ei );
            HCC_COM_CHECK_HRESULT( hr );
        }
    };

    /// <summary>
    /// Provides access to the type information for an object's 
    /// coclass entry in its type library.
    /// </summary>
    class ProvideClassInfo : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ProvideClassInfo, Unknown, IProvideClassInfo, IUnknown )

        TypeInfo GetClassInfo( ) const
        {
            auto pInterface = GetInterface( );
            ITypeInfo* result = nullptr;
            auto hr = pInterface->GetClassInfo( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return TypeInfo( result );
        }


        GUID GetGUID( ) const
        {
            GUID result = { 0, };

            auto pInterface = GetInterface( );

            IProvideClassInfo2* pProvideClassInfo2 = nullptr;
            auto hr = pInterface->QueryInterface( &pProvideClassInfo2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            UnknownPtr<IProvideClassInfo2> provideClassInfo2( pProvideClassInfo2 );
            hr = pProvideClassInfo2->GetGUID( GUIDKIND_DEFAULT_SOURCE_DISP_IID, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

    };

    /// <summary>
    /// Manages advisory connections and compound document notifications in an 
    /// object server. Its methods are intended to be used to implement the 
    /// advisory methods of IOleObject. IOleAdviseHolder is implemented on an 
    /// advise holder object. Its methods establish and delete advisory 
    /// connections from the object managed by the server to the object's 
    /// container, which must contain an advise sink (support the IAdviseSink 
    /// interface). The advise holder object must also keep track of which 
    /// advise sinks are interested in which notifications and pass along the 
    /// notifications as appropriate.
    /// </summary>
    class OleAdviseHolder : public Unknown
    {

    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( OleAdviseHolder, Unknown, IOleAdviseHolder, IUnknown )


        static OleAdviseHolder Create( )
        {
            IOleAdviseHolder* result = nullptr;
            auto hr = CreateOleAdviseHolder( &result );
            HCC_COM_CHECK_HRESULT( hr );
            return OleAdviseHolder( result );
        }

        DWORD Advise( IAdviseSink* pAdvise ) const
        {
            DWORD result = 0;
            auto pInterface = GetInterface( );
            auto hr = pInterface->Advise( pAdvise, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void Unadvise( DWORD dwConnection ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unadvise( dwConnection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumSTATDATA EnumAdvise( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATDATA* result = nullptr;
            auto hr = pInterface->EnumAdvise( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATDATA( result );
        }

        void SendOnRename( IMoniker* pmk ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SendOnRename( pmk );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SendOnSave( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SendOnSave( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SendOnClose( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SendOnClose( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Provides control of the presentation data that gets cached 
    /// inside of an object. Cached presentation data is available 
    /// to the container of the object even when the server application 
    /// is not running or is unavailable.
    /// </summary>
    class OleCache : public Unknown
    {

    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( OleCache, Unknown, IOleCache, IUnknown )


        static OleCache Create( REFIID refIID = __uuidof( IOleCache ), LPUNKNOWN pUnkOuter = nullptr, REFCLSID rclsid = CLSID_NULL )
        {
            IOleCache* pResult = nullptr;
            auto hr = CreateDataCache( pUnkOuter, rclsid, refIID, (LPVOID*)&pResult );
            HCC_COM_CHECK_HRESULT( hr );
            return OleCache( pResult );
        }

        DWORD Cache( FORMATETC* pformatetc, DWORD advf ) const
        {
            DWORD result = 0;
            auto pInterface = GetInterface( );
            auto hr = pInterface->Cache( pformatetc, advf, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void Uncache( DWORD dwConnection ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Uncache( dwConnection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        EnumSTATDATA EnumCache( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATDATA* result = nullptr;
            auto hr = pInterface->EnumCache( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATDATA( result );
        }



        void InitCache( IDataObject* pDataObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InitCache( pDataObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetData( FORMATETC* pformatetc, STGMEDIUM* pmedium, BOOL fRelease ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetData( pformatetc, pmedium, fRelease );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Enables object clients to selectively update each cache that was 
    /// created with IOleCache::Cache.
    /// </summary>
    class OleCache2 : public OleCache
    {

    public:
        typedef OleCache Base;
        HCC_COM_STANDARD_METHODS_IMPL( OleCache2, OleCache, IOleCache2, IOleCache )


        static OleCache2 Create( REFIID refIID = __uuidof( IOleCache2 ), LPUNKNOWN pUnkOuter = nullptr, REFCLSID rclsid = CLSID_NULL )
        {
            IOleCache2* pResult = nullptr;
            auto hr = CreateDataCache( pUnkOuter, rclsid, refIID, (LPVOID*)&pResult );
            HCC_COM_CHECK_HRESULT( hr );
            return OleCache2( pResult );
        }

        void UpdateCache( LPDATAOBJECT pDataObject, DWORD grfUpdf ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UpdateCache( pDataObject, grfUpdf, nullptr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DiscardCache( DWORD dwDiscardOptions ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DiscardCache( dwDiscardOptions );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Provides proper maintenance of caches. It maintains the caches 
    /// by connecting the running object's IDataObject implementation 
    /// to the cache, allowing the cache to receive notifications from the running object.
    /// </summary>
    class OleCacheControl : public Unknown
    {

    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( OleCacheControl, Unknown, IOleCacheControl, IUnknown )

        void OnRun( LPDATAOBJECT pDataObject ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->OnRun( pDataObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnStop( ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->OnStop( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Parses a displayable name string to convert it into a 
    /// moniker for custom moniker implementations.
    /// </summary>
    class ParseDisplayName : public Unknown
    {

    public:
        HCC_COM_STANDARD_METHODS_IMPL( ParseDisplayName, Unknown, IParseDisplayName, IUnknown )

        Moniker ParseDisplayName_( IBindCtx* pbc, LPOLESTR pszDisplayName, ULONG* pchEaten ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result = nullptr;

            auto hr = pInterface->ParseDisplayName( pbc, pszDisplayName, pchEaten, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }

    };

    /// <summary>
    /// Enumerates objects in a compound document or lock a container in the running state. 
    /// Container and object applications both implement this interface.
    /// </summary>
    class OleContainer : public ParseDisplayName
    {

    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleContainer, ParseDisplayName, IOleContainer, IParseDisplayName )

        EnumUnknown EnumObjects( DWORD grfFlags ) const
        {
            auto pInterface = GetInterface( );
            IEnumUnknown* result = nullptr;

            auto hr = pInterface->EnumObjects( grfFlags, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumUnknown( result );
        }

        void LockContainer( bool fLock ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->LockContainer( fLock ? TRUE : FALSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Provides the primary means by which an embedded object 
    /// obtains information about the location and extent of its 
    /// display site, its moniker, its user interface, and other 
    /// resources provided by its container. An object server calls 
    /// IOleClientSite to request services from the container. 
    /// A container must provide one instance of IOleClientSite 
    /// for every compound-document object it contains.
    /// </summary>
    class OleClientSite : public Unknown
    {

    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( OleClientSite, Unknown, IOleClientSite, IUnknown )

        void SaveObject( ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->SaveObject( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Moniker GetMoniker( DWORD dwAssign, DWORD dwWhichMoniker ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result = nullptr;

            auto hr = pInterface->GetMoniker( dwAssign, dwWhichMoniker, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }

        OleContainer GetContainer( ) const
        {
            auto pInterface = GetInterface( );
            IOleContainer* result = nullptr;

            auto hr = pInterface->GetContainer( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return OleContainer( result );
        }

        void ShowObject( ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->ShowObject( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnShowWindow( bool fShow ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->OnShowWindow( fShow ? TRUE : FALSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RequestNewObjectLayout( ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->RequestNewObjectLayout( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Enumerates the different verbs available for an object in 
    /// order of ascending verb number. An enumerator that implements 
    /// the IEnumOLEVERB interface is returned by IOleObject::EnumVerbs.
    /// </summary>
    class EnumOLEVERB : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumOLEVERB, Unknown, IEnumOLEVERB, IUnknown )

        bool Next( OLEVERB& theResult ) const
        {
            auto pInterface = GetInterface( );
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &theResult, &actual );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            if ( actual )
            {
                return true;
            }
            return false;
        }

        bool Next( ULONG requestedNumberOfElements, std::vector<OLEVERB>& result ) const
        {
            auto pInterface = GetInterface( );
            result.clear( );
            result.resize( requestedNumberOfElements );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, result.data( ), &actual );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            if ( actual )
            {
                if ( result.size( ) != actual )
                {
                    result.resize( actual );
                }
                return true;
            }
            return false;
        }

        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        EnumOLEVERB Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumOLEVERB* pEnum = nullptr;
            auto hr = pInterface->Clone( &pEnum );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return EnumOLEVERB( pEnum );
        }

    };



    /// <summary>
    /// Serves as the principal means by which an embedded object 
    /// provides basic functionality to, and communicates with, its container.
    /// </summary>
    class OleObject : public Unknown
    {

    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( OleObject, Unknown, IOleObject, IUnknown )

        void SetClientSite( IOleClientSite* pClientSite ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetClientSite( pClientSite );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        OleClientSite GetClientSite( ) const
        {
            auto pInterface = GetInterface( );
            IOleClientSite* result = nullptr;
            auto hr = pInterface->GetClientSite( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return OleClientSite( result );
        }

        void SetHostNames( LPCOLESTR szContainerApp, LPCOLESTR szContainerObj ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHostNames( szContainerApp, szContainerObj );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Close( DWORD dwSaveOption ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Close( dwSaveOption );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetMoniker( DWORD dwWhichMoniker, IMoniker* pmk ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetMoniker( dwWhichMoniker, pmk );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Moniker GetMoniker( DWORD dwAssign, DWORD dwWhichMoniker ) const
        {
            auto pInterface = GetInterface( );
            IMoniker* result = nullptr;
            auto hr = pInterface->GetMoniker( dwAssign, dwWhichMoniker, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Moniker( result );
        }

        void InitFromData( IDataObject* pDataObject, bool fCreation ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InitFromData( pDataObject, fCreation, 0 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DataObject GetClipboardData( ) const
        {
            auto pInterface = GetInterface( );
            IDataObject* result = nullptr;
            auto hr = pInterface->GetClipboardData( 0, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return DataObject( result );
        }

        void DoVerb( LONG iVerb, LPMSG lpmsg, IOleClientSite* pActiveSite, LONG lindex, HWND hwndParent, LPCRECT lprcPosRect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DoVerb( iVerb, lpmsg, pActiveSite, lindex, hwndParent, lprcPosRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumOLEVERB EnumVerbs( ) const
        {
            auto pInterface = GetInterface( );
            IEnumOLEVERB* result = nullptr;
            auto hr = pInterface->EnumVerbs( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumOLEVERB( result );
        }

        void Update( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Update( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsUpToDate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsUpToDate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            if ( hr == S_OK )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        CLSID GetUserClassID( ) const
        {
            auto pInterface = GetInterface( );
            CLSID result = { 0, };
            auto hr = pInterface->GetUserClassID( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        std::wstring GetUserType( DWORD dwFormOfType ) const
        {
            auto pInterface = GetInterface( );
            LPOLESTR result = nullptr;
            auto hr = pInterface->GetUserType( dwFormOfType, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            std::wstring s( result );
            CoTaskMemFree( result );
            return s;
        }

        void SetExtent( DWORD dwDrawAspect, SIZEL* psizel ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetExtent( dwDrawAspect, psizel );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        SIZEL GetExtent( DWORD dwDrawAspect ) const
        {
            auto pInterface = GetInterface( );
            SIZEL result = { 0, };
            auto hr = pInterface->GetExtent( dwDrawAspect, &result );

            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        DWORD Advise( IAdviseSink* pAdvSink ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->Advise( pAdvSink, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void Unadvise( DWORD dwConnection ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unadvise( dwConnection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumSTATDATA EnumAdvise( ) const
        {
            auto pInterface = GetInterface( );
            IEnumSTATDATA* result = nullptr;
            auto hr = pInterface->EnumAdvise( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumSTATDATA( result );
        }

        DWORD GetMiscStatus( DWORD dwAspect ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->GetMiscStatus( dwAspect, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void SetColorScheme( LOGPALETTE* pLogpal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetColorScheme( pLogpal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// The IOleWindow interface provides methods that allow an 
    /// application to obtain the handle to the various windows 
    /// that participate in in-place activation, and also to 
    /// enter and exit context-sensitive help mode.
    /// </summary>
    class OleWindow : public Unknown
    {

    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( OleWindow, Unknown, IOleWindow, IUnknown )

        HWND GetWindow( ) const
        {
            auto pInterface = GetInterface( );
            HWND result = 0;
            auto hr = pInterface->GetWindow( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void ContextSensitiveHelp( bool fEnterMode ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ContextSensitiveHelp( fEnterMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// <p>
    /// Enables a linked object to provide its container with functions pertaining to 
    /// linking. The most important of these functions is binding to the link source, 
    /// that is, activating the connection to the document that stores the linked 
    /// object's native data. IOleLink also defines functions for managing information 
    /// about the linked object, such as the location of the link source and the 
    /// cached presentation data for the linked object.
    /// </p>
    /// <p>
    /// A container application can distinguish between embedded objects and linked 
    /// objects by querying for IOleLink; only linked objects implement IOleLink.
    /// </p>
    /// </summary>
    class OleLink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleLink, Unknown, IOleLink, IUnknown )

        void SetUpdateOptions( DWORD updateOptions ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetUpdateOptions( updateOptions );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetUpdateOptions( __RPC__out DWORD* updateOptions ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetUpdateOptions( updateOptions );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetSourceMoniker( __RPC__in_opt IMoniker* moniker, __RPC__in REFCLSID rclsid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSourceMoniker( moniker, rclsid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSourceMoniker( __RPC__deref_out_opt IMoniker** moniker ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSourceMoniker( moniker );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetSourceDisplayName( __RPC__in LPCOLESTR statusText ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSourceDisplayName( statusText );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSourceDisplayName( __RPC__deref_out_opt LPOLESTR* displayName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSourceDisplayName( displayName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BindToSource( DWORD bindflags, __RPC__in_opt IBindCtx* bindCtx ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->BindToSource( bindflags, bindCtx );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BindIfRunning( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->BindIfRunning( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBoundSource( __RPC__deref_out_opt IUnknown** boundSource ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetBoundSource( boundSource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void UnbindSource( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UnbindSource( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Update( __RPC__in_opt IBindCtx* bindCtx ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Update( bindCtx );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// <p>
    /// Used by item monikers when they are bound to the objects they identify.
    /// </p>
    /// <p>
    /// When any container of objects uses item monikers to identify its objects, 
    /// it must define a naming scheme for those objects. The container's 
    /// IOleItemContainer implementation uses knowledge of that naming scheme to 
    /// retrieve an object given a particular name. Item monikers use the container's 
    /// IOleItemContainer implementation during binding.
    /// </p>
    /// </summary>
    class OleItemContainer : public OleContainer
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleItemContainer, OleContainer, IOleItemContainer, IOleContainer )

        void GetObject( __RPC__in LPOLESTR pszItem, DWORD dwSpeedNeeded, __RPC__in_opt IBindCtx* pbc, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppvObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetObject( pszItem, dwSpeedNeeded, pbc, riid, ppvObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetObjectStorage( __RPC__in LPOLESTR pszItem, __RPC__in_opt IBindCtx* pbc, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppvStorage ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetObjectStorage( pszItem, pbc, riid, ppvStorage );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsRunning( __RPC__in LPOLESTR pszItem ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsRunning( pszItem );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }
    };

    /// <summary>
    /// Implemented by container applications and used by object applications 
    /// to negotiate border space on the document or frame window. The container 
    /// provides a RECT structure in which the object can place toolbars and 
    /// other similar controls, determines if tools can in fact be installed 
    /// around the object's window frame, allocates space for the border, and 
    /// establishes a communication channel between the object and each frame 
    /// and document window.
    /// </summary>
    class OleInPlaceUIWindow : public OleWindow
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceUIWindow, OleWindow, IOleInPlaceUIWindow, IOleWindow )

        void GetBorder( __RPC__out LPRECT borderRect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetBorder( borderRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RequestBorderSpace( __RPC__in_opt LPCBORDERWIDTHS borderWidths ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestBorderSpace( borderWidths );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetBorderSpace( __RPC__in_opt LPCBORDERWIDTHS borderWidths ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetBorderSpace( borderWidths );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetActiveObject( __RPC__in_opt IOleInPlaceActiveObject* activeObject, __RPC__in_opt_string LPCOLESTR objectName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetActiveObject( activeObject, objectName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Provides a direct channel of communication between an in-place 
    /// object and the associated application's outer-most frame window 
    /// and the document window within the application that contains the 
    /// embedded object. The communication involves the translation of 
    /// messages, the state of the frame window (activated or deactivated), 
    /// and the state of the document window (activated or deactivated). 
    /// Also, it informs the object when it needs to resize its borders, 
    /// and manages modeless dialog boxes.
    /// </summary>
    class OleInPlaceActiveObject : public OleWindow
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceActiveObject, OleWindow, IOleInPlaceActiveObject, IOleWindow )

        /// <summary>
        /// Processes menu accelerator-key messages from the container's 
        /// message queue. This method should only be used for objects 
        /// created by a DLL object application.
        /// </summary>
        /// <param name="msg">
        /// A pointer to an MSG structure for the message that might 
        /// need to be translated.
        /// </param>
        /// <returns>
        /// true if the message was processed by this function, false otherwise.
        /// </returns>
        bool TranslateAccelerator( _In_opt_ LPMSG msg ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->TranslateAccelerator( msg );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == S_OK;
        }

        void OnFrameWindowActivate( bool activate ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnFrameWindowActivate( activate );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnDocWindowActivate( bool activate ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnDocWindowActivate( activate );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ResizeBorder( _In_  LPCRECT borderRect, _In_  IOleInPlaceUIWindow* inPlaceUIWindow, _In_  bool frameWindow ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ResizeBorder( borderRect, inPlaceUIWindow, frameWindow );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EnableModeless( bool enable ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EnableModeless( enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Controls the container's top-level frame window. This control involves 
    /// allowing the container to insert its menu group into the composite menu, 
    /// install the composite menu into the appropriate window frame, and remove 
    /// the container's menu elements from the composite menu. It sets and displays 
    /// status text relevant to the in-place object. It also enables or disables 
    /// the frame's modeless dialog boxes, and translates accelerator keystrokes 
    /// intended for the container's frame.
    /// </summary>
    class OleInPlaceFrame : public OleInPlaceUIWindow
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceFrame, OleInPlaceUIWindow, IOleInPlaceFrame, IOleInPlaceUIWindow )

        void InsertMenus( __RPC__in HMENU hmenuShared, __RPC__inout LPOLEMENUGROUPWIDTHS menuWidths ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InsertMenus( hmenuShared, menuWidths );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetMenu( __RPC__in HMENU hmenuShared, __RPC__in HOLEMENU holemenu, __RPC__in HWND hwndActiveObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetMenu( hmenuShared, holemenu, hwndActiveObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveMenus( __RPC__in HMENU hmenuShared ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveMenus( hmenuShared );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStatusText( __RPC__in_opt LPCOLESTR statusText ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetStatusText( statusText );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EnableModeless( bool enable ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EnableModeless( enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool TranslateAccelerator( __RPC__in LPMSG msg, WORD id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->TranslateAccelerator( msg, id );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == S_OK;
        }
    };

    /// <summary>
    /// Indicates whether or not to continue an operation. Used with remote procedure calls.
    /// </summary>
    class Continue : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Continue, Unknown, IContinue, IUnknown )

        void FContinue( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->FContinue( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// <p>
    /// The IDropSource interface is one of the interfaces you implement to 
    /// provide drag-and-drop operations in your application. It contains methods 
    /// used in any application used as a data source in a drag-and-drop operation. 
    /// The data source application in a drag-and-drop operation is responsible for:
    /// </p>
    /// <ul>
    /// <li>
    /// Determining the data being dragged based on the user's selection.
    /// </li>
    /// <li>
    /// Initiating the drag-and-drop operation based on the user's mouse actions.
    /// </li>
    /// <li>
    /// Generating some of the visual feedback during the drag-and-drop operation, 
    /// such as setting the cursor and highlighting the data selected for the 
    /// drag-and-drop operation.
    /// </li>
    /// <li>
    /// Canceling or completing the drag-and-drop operation based on the user's 
    /// mouse actions.
    /// </li>
    /// <li>
    /// Performing any action on the original data caused by the drop operation, such 
    /// as deleting the data on a drag move.
    /// </li>
    /// </ul>
    /// <p>
    /// IDropSource contains the methods for generating visual feedback to the end 
    /// user and for canceling or completing the drag-and-drop operation. You also 
    /// need to call the DoDragDrop, RegisterDragDrop, and RevokeDragDrop functions 
    /// in drag-and-drop operations.
    /// </p>
    /// </summary>
    class DropSource : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DropSource, Unknown, IDropSource, IUnknown )

        void QueryContinueDrag( _In_  bool escapePressed, _In_  DWORD keyState ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryContinueDrag( escapePressed, keyState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GiveFeedback( _In_  DWORD effect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GiveFeedback( effect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// <p>
    /// The IDropTarget interface is one of the interfaces you implement to 
    /// provide drag-and-drop operations in your application. It contains 
    /// methods used in any application that can be a target for data during 
    /// a drag-and-drop operation. A drop-target application is responsible for:
    /// </p>
    /// <ul>
    /// <li>
    /// Determining the effect of the drop on the target application.
    /// </li>
    /// <li>
    /// Incorporating any valid dropped data when the drop occurs.
    /// </li>
    /// <li>
    /// Communicating target feedback to the source so the source application 
    /// can provide appropriate visual feedback such as setting the cursor.
    /// </li>
    /// <li>
    /// Implementing drag scrolling.
    /// </li>
    /// <li>
    /// Registering and revoking its application windows as drop targets.
    /// </li>
    /// </ul>
    /// <p>
    /// The IDropTarget interface contains methods that handle all these 
    /// responsibilities except registering and revoking the application 
    /// window as a drop target, for which you must call the RegisterDragDrop 
    /// and the RevokeDragDrop functions.
    /// </p>
    /// </summary>
    class DropTarget : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DropTarget, Unknown, IDropTarget, IUnknown )

        void DragEnter( __RPC__in_opt IDataObject* dataObject, DWORD keyState, POINTL pt, __RPC__inout DWORD* effect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DragEnter( dataObject, keyState, pt, effect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DragOver( DWORD keyState, POINTL pt, __RPC__inout DWORD* effect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DragOver( keyState, pt, effect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DragLeave( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DragLeave( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Drop( IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Drop( pDataObj, grfKeyState, pt, pdwEffect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// The IDropSourceNotify interface is implemented on an IDropSource object 
    /// to receive notifications from OLE when a user drags the mouse into or out 
    /// of a potential drop target window.
    /// </summary>
    class DropSourceNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DropSourceNotify, Unknown, IDropSourceNotify, IUnknown )

        void DragEnterTarget( HWND hwndTarget ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DragEnterTarget( hwndTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DragLeaveTarget( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DragLeaveTarget( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// When implemented by the drop target application, this interface gives the 
    /// OLE drag and drop engine the ability to determine whether the drop target 
    /// application intends to evaluate enterprise protection policy and gives the 
    /// OLE drag and drop engine a way to provide the enterprise ID of the drop 
    /// source application to the drop target application.
    /// </summary>
    class EnterpriseDropTarget : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( EnterpriseDropTarget, Unknown, IEnterpriseDropTarget, IUnknown )

        void SetDropSourceEnterpriseId( __RPC__in LPCWSTR identity ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetDropSourceEnterpriseId( identity );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void IsEvaluatingEdpPolicy( __RPC__out BOOL* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsEvaluatingEdpPolicy( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Provides the tools for creating and administering the type information 
    /// defined through the type description.
    /// </summary>
    class CreateTypeInfo : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( CreateTypeInfo, Unknown, ICreateTypeInfo, IUnknown )

        void SetGuid( REFGUID guid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetGuid( guid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTypeFlags( UINT typeFlags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetTypeFlags( typeFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDocString( __RPC__in  LPOLESTR docStr ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetDocString( docStr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpContext( DWORD helpContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpContext( helpContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetVersion( WORD majorVerNum, WORD minorVerNum ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetVersion( majorVerNum, minorVerNum );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddRefTypeInfo( ITypeInfo* typeInfo, HREFTYPE* refType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddRefTypeInfo( typeInfo, refType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddFuncDesc( UINT index, FUNCDESC* funcDesc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddFuncDesc( index, funcDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddImplType( UINT index, HREFTYPE refType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddImplType( index, refType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetImplTypeFlags( UINT index, INT implTypeFlags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetImplTypeFlags( index, implTypeFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetAlignment( WORD byteAlignment ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetAlignment( byteAlignment );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetSchema( __RPC__in  LPOLESTR schemaName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSchema( schemaName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddVarDesc( UINT index, VARDESC* varDesc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddVarDesc( index, varDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFuncAndParamNames( UINT index, LPOLESTR* names, UINT namesCount ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFuncAndParamNames( index, names, namesCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetVarName( UINT index, __RPC__in  LPOLESTR name ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetVarName( index, name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTypeDescAlias( TYPEDESC* typeDesc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetTypeDescAlias( typeDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DefineFuncAsDllEntry( UINT index, __RPC__in  LPOLESTR dllName, __RPC__in  LPOLESTR procName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DefineFuncAsDllEntry( index, dllName, procName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFuncDocString( UINT index, __RPC__in  LPOLESTR docString ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFuncDocString( index, docString );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetVarDocString( UINT index, __RPC__in  LPOLESTR docString ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetVarDocString( index, docString );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFuncHelpContext( UINT index, DWORD helpContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFuncHelpContext( index, helpContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetVarHelpContext( UINT index, DWORD helpContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetVarHelpContext( index, helpContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetMops( UINT index, _In_  BSTR bstrMops ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetMops( index, bstrMops );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTypeIdldesc( IDLDESC* idlDesc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetTypeIdldesc( idlDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void LayOut( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->LayOut( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// <p>
    /// Provides the tools for creating and administering the type information 
    /// defined through the type description. Derives from ICreateTypeInfo, and 
    /// adds methods for deleting items that have been added through ICreateTypeInfo.
    /// </p>
    /// <p>
    /// The ICreateTypeInfo::LayOut method provides a way for the creator of the 
    /// type information to check for any errors. A call to QueryInterface can be 
    /// made to the ICreateTypeInfo instance at any time for its ITypeInfo interface. 
    /// Calling any of the methods in the ITypeInfointerface that require layout 
    /// information lays out the type information automatically.
    /// </p>
    /// </summary>
    class CreateTypeInfo2 : public CreateTypeInfo
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( CreateTypeInfo2, CreateTypeInfo, ICreateTypeInfo2, ICreateTypeInfo )

        void DeleteFuncDesc( UINT index ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteFuncDesc( index );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteFuncDescByMemId( MEMBERID memid, INVOKEKIND invKind ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteFuncDescByMemId( memid, invKind );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteVarDesc( UINT index ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteVarDesc( index );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteVarDescByMemId( MEMBERID memid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteVarDescByMemId( memid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteImplType( UINT index ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteImplType( index );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetCustData( REFGUID guid, VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetCustData( guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFuncCustData( UINT index, REFGUID guid, VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFuncCustData( index, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetParamCustData( UINT indexFunc, UINT indexParam, REFGUID guid, VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetParamCustData( indexFunc, indexParam, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetVarCustData( UINT index, REFGUID guid, VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetVarCustData( index, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetImplTypeCustData( UINT index, REFGUID guid, VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetImplTypeCustData( index, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpStringContext( ULONG dwHelpStringContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpStringContext( dwHelpStringContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFuncHelpStringContext( UINT index, ULONG dwHelpStringContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFuncHelpStringContext( index, dwHelpStringContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetVarHelpStringContext( UINT index, ULONG dwHelpStringContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetVarHelpStringContext( index, dwHelpStringContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Invalidate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Invalidate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetName( __RPC__in  LPOLESTR szName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetName( szName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// Provides the methods for creating and managing the component or file that 
    /// contains type information. Type libraries are created from type descriptions 
    /// using the MIDL compiler. These type libraries are accessed through the 
    /// ITypeLib interface.
    /// </summary>
    class CreateTypeLib : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( CreateTypeLib, Unknown, ICreateTypeLib, IUnknown )

        void CreateTypeInfo( __RPC__in  LPOLESTR szName, TYPEKIND tkind, ICreateTypeInfo** ppCTInfo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateTypeInfo( szName, tkind, ppCTInfo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetName( __RPC__in  LPOLESTR szName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetName( szName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetVersion( WORD wMajorVerNum, WORD wMinorVerNum ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetVersion( wMajorVerNum, wMinorVerNum );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetGuid( REFGUID guid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetGuid( guid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDocString( __RPC__in  LPOLESTR szDoc ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetDocString( szDoc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpFileName( __RPC__in  LPOLESTR szHelpFileName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpFileName( szHelpFileName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpContext( DWORD dwHelpContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpContext( dwHelpContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetLcid( LCID lcid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetLcid( lcid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetLibFlags( UINT uLibFlags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetLibFlags( uLibFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SaveAllChanges( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SaveAllChanges( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Provides the methods for creating and managing the component or file that 
    /// contains type information. Derives from ICreateTypeLib. The ICreateTypeInfo 
    /// instance returned from ICreateTypeLib can be accessed through a 
    /// QueryInterface call to ICreateTypeInfo2.
    /// </summary>
    class CreateTypeLib2 : public CreateTypeLib
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( CreateTypeLib2, CreateTypeLib, ICreateTypeLib2, ICreateTypeLib )

        void DeleteTypeInfo( __RPC__in  LPOLESTR szName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteTypeInfo( szName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetCustData( REFGUID guid, VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetCustData( guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpStringContext( ULONG dwHelpStringContext ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpStringContext( dwHelpStringContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHelpStringDll( __RPC__in  LPOLESTR szFileName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHelpStringDll( szFileName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Used for reading information about objects. Can be cast to an ITypeInfo 
    /// instead of using the calls QueryInterface and Release to allow quick 
    /// opens and allocs. This only works for in-process cases.
    /// </summary>
    class TypeInfo2 : public TypeInfo
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( TypeInfo2, TypeInfo, ITypeInfo2, ITypeInfo )

        void GetTypeKind( __RPC__out TYPEKIND* pTypeKind ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetTypeKind( pTypeKind );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTypeFlags( __RPC__out ULONG* pTypeFlags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetTypeFlags( pTypeFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFuncIndexOfMemId( MEMBERID memid, INVOKEKIND invKind, __RPC__out UINT* pFuncIndex ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFuncIndexOfMemId( memid, invKind, pFuncIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetVarIndexOfMemId( MEMBERID memid, __RPC__out UINT* pVarIndex ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetVarIndexOfMemId( memid, pVarIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCustData( __RPC__in REFGUID guid, __RPC__out VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCustData( guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFuncCustData( UINT index, __RPC__in REFGUID guid, __RPC__out VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFuncCustData( index, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetParamCustData( UINT indexFunc, UINT indexParam, __RPC__in REFGUID guid, __RPC__out VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetParamCustData( indexFunc, indexParam, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetVarCustData( UINT index, __RPC__in REFGUID guid, __RPC__out VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetVarCustData( index, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetImplTypeCustData( UINT index, __RPC__in REFGUID guid, __RPC__out VARIANT* pVarVal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetImplTypeCustData( index, guid, pVarVal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDocumentation2( MEMBERID memid, LCID lcid, _Outptr_opt_  BSTR* pbstrHelpString, DWORD* pdwHelpStringContext, _Outptr_opt_  BSTR* pbstrHelpStringDll ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDocumentation2( memid, lcid, pbstrHelpString, pdwHelpStringContext, pbstrHelpStringDll );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAllCustData( __RPC__out CUSTDATA* pCustData ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAllCustData( pCustData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAllFuncCustData( UINT index, __RPC__out CUSTDATA* pCustData ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAllFuncCustData( index, pCustData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAllParamCustData( UINT indexFunc, UINT indexParam, __RPC__out CUSTDATA* pCustData ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAllParamCustData( indexFunc, indexParam, pCustData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAllVarCustData( UINT index, __RPC__out CUSTDATA* pCustData ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAllVarCustData( index, pCustData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAllImplTypeCustData( UINT index, __RPC__out CUSTDATA* pCustData ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAllImplTypeCustData( index, pCustData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// Enables clients to subscribe to type change notifications on objects 
    /// that implement the ITypeInfo, ITypeInfo2, ICreateTypeInfo, and ICreateTypeInfo2 
    /// interfaces. When ITypeChangeEvents is implemented on an object, it acts as an 
    /// incoming interface that enables the object to receive calls from external 
    /// clients and engage in bidirectional communication with those clients.
    /// </summary>
    class TypeChangeEvents : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( TypeChangeEvents, Unknown, ITypeChangeEvents, IUnknown )

        void RequestTypeChange( CHANGEKIND changeKind, ITypeInfo* pTInfoBefore, __RPC__in  LPOLESTR pStrName, INT* pfCancel ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestTypeChange( changeKind, pTInfoBefore, pStrName, pfCancel );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AfterTypeChange( CHANGEKIND changeKind, ITypeInfo* pTInfoAfter, __RPC__in  LPOLESTR pStrName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AfterTypeChange( changeKind, pTInfoAfter, pStrName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// 
    /// </summary>
    class TypeFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( TypeFactory, Unknown, ITypeFactory, IUnknown )

        void CreateFromTypeInfo( __RPC__in_opt ITypeInfo* pTypeInfo, __RPC__in REFIID riid, __RPC__deref_out_opt IUnknown** ppv ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateFromTypeInfo( pTypeInfo, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    
    class TypeMarshal : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( TypeMarshal, Unknown, ITypeMarshal, IUnknown )

        void Size( PVOID pvType, DWORD dwDestContext, PVOID pvDestContext, ULONG* pSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Size( pvType, dwDestContext, pvDestContext, pSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Marshal( PVOID pvType, DWORD dwDestContext, PVOID pvDestContext, ULONG cbBufferLength, BYTE* pBuffer, _Out_  ULONG* pcbWritten ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Marshal( pvType, dwDestContext, pvDestContext, cbBufferLength, pBuffer, pcbWritten );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Unmarshal( PVOID pvType, DWORD dwFlags, ULONG cbBufferLength, BYTE* pBuffer, _Out_  ULONG* pcbRead ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unmarshal( pvType, dwFlags, cbBufferLength, pBuffer, pcbRead );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Free( PVOID pvType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Free( pvType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// Describes the structure of a particular UDT. You can use IRecordInfo any 
    /// time you need to access the description of UDTs contained in type libraries. 
    /// IRecordInfo can be reused as needed; there can be many instances of the UDT 
    /// for a single IRecordInfo pointer.
    /// </summary>
    class RecordInfo : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( RecordInfo, Unknown, IRecordInfo, IUnknown )

        void RecordInit( PVOID pvNew ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RecordInit( pvNew );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RecordClear( PVOID pvExisting ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RecordClear( pvExisting );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RecordCopy( PVOID pvExisting, PVOID pvNew ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RecordCopy( pvExisting, pvNew );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetGuid( GUID* pguid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetGuid( pguid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetName( __RPC__deref_out_opt  BSTR* pbstrName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetName( pbstrName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSize( ULONG* pcbSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSize( pcbSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTypeInfo( ITypeInfo** ppTypeInfo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetTypeInfo( ppTypeInfo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetField( PVOID pvData, LPCOLESTR szFieldName, VARIANT* pvarField ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetField( pvData, szFieldName, pvarField );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFieldNoCopy( PVOID pvData, LPCOLESTR szFieldName, VARIANT* pvarField, PVOID* ppvDataCArray ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFieldNoCopy( pvData, szFieldName, pvarField, ppvDataCArray );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutField( ULONG wFlags, PVOID pvData, LPCOLESTR szFieldName, VARIANT* pvarField ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutField( wFlags, pvData, szFieldName, pvarField );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutFieldNoCopy( ULONG wFlags, PVOID pvData, LPCOLESTR szFieldName, VARIANT* pvarField ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutFieldNoCopy( wFlags, pvData, szFieldName, pvarField );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFieldNames( ULONG* pcNames, BSTR* rgBstrNames ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFieldNames( pcNames, rgBstrNames );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsMatchingType( IRecordInfo* pRecordInfo ) const
        {
            auto pInterface = GetInterface( );
            return pInterface->IsMatchingType( pRecordInfo );
        }

        void* RecordCreate( ) const
        {
            auto pInterface = GetInterface( );
            return pInterface->RecordCreate( );
        }

        void RecordCreateCopy( PVOID pvSource, PVOID* ppvDest ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RecordCreateCopy( pvSource, ppvDest );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RecordDestroy( PVOID pvRecord ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RecordDestroy( pvRecord );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    inline RecordInfo SafeArray::GetRecordInfo( ) const
    {
        if ( ptr_ )
        {
            RecordInfo result;
            auto hr = SafeArrayGetRecordInfo( ptr_, reinterpret_cast< IRecordInfo** >( &result ) );
            CheckHRESULT( hr );
            return result;
        }
        return RecordInfo( );
    }

    inline RecordInfo TypeInfo::GetRecordInfo( ) const
    {
        auto pInterface = GetInterface( );
        if ( pInterface )
        {
            RecordInfo result;
            auto hr = GetRecordInfoFromTypeInfo( pInterface, reinterpret_cast< IRecordInfo** >( &result ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }
        return {};
    }



    /// <summary>
    /// Communicates detailed error information between a client and an object.
    /// </summary>
    class ErrorLog : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ErrorLog, Unknown, IErrorLog, IUnknown )

        void AddError( __RPC__in LPCOLESTR pszPropName, __RPC__in EXCEPINFO* pExcepInfo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddError( pszPropName, pExcepInfo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// 
    /// </summary>
    class TypeLibRegistrationReader : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( TypeLibRegistrationReader, Unknown, ITypeLibRegistrationReader, IUnknown )

        void EnumTypeLibRegistrations( IEnumUnknown** ppEnumUnknown ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EnumTypeLibRegistrations( ppEnumUnknown );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// 
    /// </summary>
    class TypeLibRegistration : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( TypeLibRegistration, Unknown, ITypeLibRegistration, IUnknown )

        void GetGuid( GUID* pGuid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetGuid( pGuid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetVersion( BSTR* pVersion ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetVersion( pVersion );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetLcid( LCID* pLcid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLcid( pLcid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetWin32Path( BSTR* pWin32Path ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetWin32Path( pWin32Path );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetWin64Path( BSTR* pWin64Path ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetWin64Path( pWin64Path );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDisplayName( BSTR* pDisplayName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDisplayName( pDisplayName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFlags( DWORD* pFlags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFlags( pFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetHelpDir( BSTR* pHelpDir ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetHelpDir( pHelpDir );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


    };




    /// <summary>
    /// Describes a connection that exists to a given connection point.
    /// </summary>
    class ConnectData
    {
    public:
    private:
        struct Data : CONNECTDATA
        {
            long referenceCount;
            Data( )
                : referenceCount( 1 )
            {
                pUnk = nullptr;
                dwCookie = 0;
            }

            Data( const CONNECTDATA& other, bool addref = false )
                : referenceCount( 1 )
            {
                pUnk = other.pUnk;
                dwCookie = other.dwCookie;
                if ( pUnk && addref )
                {
                    pUnk->AddRef( );
                }
            }

            Data( const CONNECTDATA* other, bool addref = false )
                : referenceCount( 1 )
            {
                if ( other )
                {
                    pUnk = other->pUnk;
                    dwCookie = other->dwCookie;
                    if ( pUnk && addref )
                    {
                        pUnk->AddRef( );
                    }
                }
                else
                {
                    pUnk = nullptr;
                    dwCookie = 0;
                }
            }

            ~Data( )
            {
                if ( pUnk )
                {
                    pUnk->Release( );
                    pUnk = nullptr;
                }
            }
        };
        Data* data;

        void Clear( )
        {
            if ( data )
            {
                auto res = InterlockedDecrement( &data->referenceCount );
                if ( res == 0 )
                {
                    delete data;
                    data = 0;
                }
            }
        }
    public:
        ConnectData( )
            : data( )
        {
        }

        ConnectData( const CONNECTDATA& other, bool addref = false )
            : data( new Data( other, addref ) )
        {
        }

        ConnectData( const CONNECTDATA* other, bool addref = false )
            : data( new Data( other, addref ) )
        {
        }

        ConnectData( const ConnectData& other )
            : data( other.data )
        {
            if ( data )
            {
                InterlockedIncrement( &data->referenceCount );
            }
        }

        ConnectData( ConnectData&& other )
            : data( other.data )
        {
            other.data = nullptr;
        }

        ~ConnectData( )
        {
            Clear( );
        }


        ConnectData& operator = ( const ConnectData& other )
        {
            if ( data != other.data )
            {
                Clear( );
                data = other.data;
                if ( data )
                {
                    InterlockedIncrement( &data->referenceCount );
                }
            }
            return *this;
        }

        ConnectData& operator = ( ConnectData&& other )
        {
            if ( data != other.data )
            {
                Clear( );
                data = other.data;
                other.data = nullptr;
            }
            return *this;
        }

        operator bool( ) const
        {
            return data != nullptr;
        }


        const CONNECTDATA* Get( ) const
        {
            return data;
        }

        CONNECTDATA* Get( )
        {
            if ( !data )
            {
                data = new Data( );
            }
            return data;
        }

        IUnknown* Unknown( ) const
        {
            if ( data )
            {
                return data->pUnk;
            }
            return nullptr;
        }

        ConnectData& SetUnknown( IUnknown* pUnk, bool addref = false )
        {
            auto d = Get( );
            d->pUnk = pUnk;
            if ( pUnk && addref )
            {
                pUnk->AddRef( );
            }
            return *this;
        }

        DWORD Cookie( ) const
        {
            if ( data )
            {
                return data->dwCookie;
            }
            return 0;
        }

        ConnectData& SetCookie( DWORD cookie )
        {
            auto d = Get( );
            d->dwCookie = cookie;
            return *this;
        }

        ConnectData& Set( DWORD cookie, IUnknown* pUnk, bool addref = false )
        {
            auto d = Get( );
            d->dwCookie = cookie;
            d->pUnk = pUnk;
            if ( pUnk && addref )
            {
                pUnk->AddRef( );
            }
            return *this;
        }

        ConnectData& Set( const CONNECTDATA& theCONNECTDATA, bool addref = false )
        {
            auto d = Get( );
            d->dwCookie = theCONNECTDATA.dwCookie;
            d->pUnk = theCONNECTDATA.pUnk;
            if ( d->pUnk && addref )
            {
                d->pUnk->AddRef( );
            }
            return *this;
        }

        HRESULT AssignTo( CONNECTDATA& theCONNECTDATA ) const
        {
            HRESULT result = S_OK;
            if ( theCONNECTDATA.pUnk )
            {
                theCONNECTDATA.pUnk->Release( );
                theCONNECTDATA.pUnk = nullptr;
            }
            theCONNECTDATA.dwCookie = 0;
            auto d = Get( );
            if ( d )
            {
                theCONNECTDATA.dwCookie = d->dwCookie;
                theCONNECTDATA.pUnk = d->pUnk;
                theCONNECTDATA.pUnk->AddRef( );
            }
            return result;
        }



    };

    /// <summary>
    /// Enumerates the current connections for a connectable object.
    /// </summary>
    class EnumConnections : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumConnections, Unknown, IEnumConnections, IUnknown )

        bool Next( ConnectData& theResult ) const
        {
            auto pInterface = GetInterface( );
            CONNECTDATA element = { 0, };
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &element, &actual );
            if ( actual )
            {
                theResult.Set( element );
                return true;
            }
            return false;
        }
        bool Next( ULONG requestedNumberOfElements, std::vector<ConnectData>& result ) const
        {
            auto pInterface = GetInterface( );
            CONNECTDATA* elements = (CONNECTDATA*)alloca( requestedNumberOfElements * sizeof( CONNECTDATA ) );
            memset( elements, 0, requestedNumberOfElements * sizeof( CONNECTDATA ) );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, elements, &actual );
            if ( actual )
            {
                result.clear( );
                for ( ULONG i = 0; i < actual; i++ )
                {
                    result.push_back( ConnectData( elements[i] ) );
                }
                return true;
            }
            return false;
        }
        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumConnections Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumConnections* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumConnections( pClone );
        }

    };

    class ConnectionPointContainer;
    /// <summary>
    /// Supports connection points for connectable objects.
    /// </summary>
    class ConnectionPoint : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ConnectionPoint, Unknown, IConnectionPoint, IUnknown )

        IID GetConnectionInterface( ) const
        {
            auto pInterface = GetInterface( );
            IID result = { 0, };
            auto hr = pInterface->GetConnectionInterface( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        ConnectionPointContainer GetConnectionPointContainer( ) const;

        DWORD Advise( IUnknown* pUnkSink ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->Advise( pUnkSink, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        ConnectionPoint& Unadvise( DWORD dwCookie ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unadvise( dwCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumConnections EnumConnections( ) const
        {
            auto pInterface = GetInterface( );
            IEnumConnections* pEnum = nullptr;
            auto hr = pInterface->EnumConnections( &pEnum );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Core::EnumConnections( pEnum );
        }

    };


    /// <summary>
    /// Enumerates connection points.
    /// </summary>
    class EnumConnectionPoints : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumConnectionPoints, Unknown, IEnumConnectionPoints, IUnknown )

        bool Next( ConnectionPoint& theResult ) const
        {
            auto pInterface = GetInterface( );
            IConnectionPoint* pElement = nullptr;
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &pElement, &actual );
            if ( actual )
            {
                theResult.ResetPtr( pElement );
                return true;
            }
            return false;
        }
        bool Next( ULONG requestedNumberOfElements, std::vector<ConnectionPoint>& result ) const
        {
            auto pInterface = GetInterface( );
            IConnectionPoint** pElements = (IConnectionPoint**)alloca( requestedNumberOfElements * sizeof( IConnectionPoint* ) );
            memset( pElements, 0, requestedNumberOfElements * sizeof( IConnectionPoint* ) );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, pElements, &actual );
            if ( actual )
            {
                result.clear( );
                for ( ULONG i = 0; i < actual; i++ )
                {
                    result.push_back( ConnectionPoint( pElements[i] ) );
                }
                return true;
            }
            return false;
        }
        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        EnumConnectionPoints Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumConnectionPoints* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return EnumConnectionPoints( pClone );
        }

    };

    /// <summary>
    /// Supports connection points for connectable objects.
    /// </summary>
    class ConnectionPointContainer : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ConnectionPointContainer, Unknown, IConnectionPointContainer, IUnknown )

        EnumConnectionPoints EnumConnectionPoints( ) const
        {
            auto pInterface = GetInterface( );
            IEnumConnectionPoints* pResult = nullptr;
            auto hr = pInterface->EnumConnectionPoints( &pResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return Core::EnumConnectionPoints( pResult );
        }

        ConnectionPoint FindConnectionPoint( REFIID riid ) const
        {
            auto pInterface = GetInterface( );
            IConnectionPoint* pResult = nullptr;
            auto hr = pInterface->FindConnectionPoint( riid, &pResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return ConnectionPoint( pResult );
        }

    };

    inline ConnectionPointContainer ConnectionPoint::GetConnectionPointContainer( ) const
    {
        auto pInterface = GetInterface( );
        IConnectionPointContainer* pResult = nullptr;
        auto hr = pInterface->GetConnectionPointContainer( &pResult );
        HCC_COM_CHECK_HRESULT2( hr, pInterface );
        return ConnectionPointContainer( pResult );
    }

    /// <summary>
    /// <p>
    /// Enables a class factory object, in any sort of object 
    /// server, to control object creation through licensing.
    /// </p>
    /// <p>
    /// This interface is an extension to IClassFactory. This extension enables a 
    /// class factory executing on a licensed machine to provide a license key that 
    /// can be used later to create an object instance on an unlicensed machine. Such 
    /// considerations are important for objects like controls that are used to build 
    /// applications on a licensed machine. Subsequently, the application built must 
    /// be able to run on an unlicensed machine. The license key gives only that one 
    /// client application the right to instantiate objects through IClassFactory2 
    /// when a full machine license does not exist.
    /// </p>
    /// </summary>
    class ClassFactory2 : public ClassFactory
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ClassFactory2, ClassFactory, IClassFactory2, IClassFactory )

        /// <summary>
        /// Retrieves information about the licensing capabilities 
        /// of this class factory.
        /// </summary>
        /// <param name="licenseInfo">
        /// A pointer to the caller-allocated LICINFO structure to be filled on output.
        /// </param>
        /// <remarks>
        /// E_NOTIMPL is not allowed as a return value because this method provides 
        /// critical information for the client of a licensed class factory.
        /// </remarks>
        void GetLicInfo( LICINFO* licenseInfo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLicInfo( licenseInfo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Creates a license key that the caller can save and use 
        /// later to create an instance of the licensed object.
        /// </summary>
        /// <param name="reserved">
        /// This parameter is reserved and must be zero.
        /// </param>
        /// <param name="bstrKey">
        /// A pointer to the caller-allocated variable that receives the 
        /// callee-allocated license key on successful return from this 
        /// method. This parameter is set to NULL on any failure.
        /// </param>
        /// <remarks>
        /// <p>
        /// The caller can save the license key for subsequent calls to 
        /// CreateInstanceLic to create objects on an otherwise unlicensed 
        /// machine.
        /// </p>
        /// <h4>Notes to Callers</h4>
        /// <p>
        /// The caller must free the BSTR with the SysFreeString function 
        /// when the key is no longer needed. The value of fRuntimeKeyAvail 
        /// is returned through a previous call to GetLicInfo.
        /// </p>
        /// <h4>Notes to Implementers</h4>
        /// <p>
        /// This method allocates the BSTR key with SysAllocString or 
        /// SysAllocStringLen, and the caller becomes responsible for 
        /// this BSTR after this method returns successfully.
        /// </p>
        /// <p>
        /// This method need not be implemented when a class factory 
        /// does not support run-time license keys.
        /// </p>
        /// </remarks>
        void RequestLicKey( DWORD reserved, BSTR* bstrKey ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestLicKey( reserved, bstrKey );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void RequestLicKey( BSTR* bstrKey ) const
        {
            RequestLicKey( 0, bstrKey );
        }
        SysString RequestLicKey( ) const
        {
            BSTR bstr = nullptr;
            RequestLicKey( &bstr );
            return SysString( bstr, true );
        }
        

        /// <summary>
        /// Creates an instance of the licensed object for the specified 
        /// license key. This method is the only possible means to create 
        /// an object on an otherwise unlicensed machine.
        /// </summary>
        /// <param name="outerUnknown">
        /// A pointer to the controlling IUnknown interface on the outer 
        /// unknown if this object is being created as part of an aggregate. 
        /// If the object is not part of an aggregate, this parameter must 
        /// be NULL.
        /// </param>
        /// <param name="reservedUnknown">
        /// This parameter is unused and must be NULL.
        /// </param>
        /// <param name="riid">
        /// A reference to the identifier of the interface to be used to 
        /// communicate with the newly created object.
        /// </param>
        /// <param name="bstrKey">
        /// Run-time license key previously obtained from RequestLicKey 
        /// that is required to create an object.
        /// </param>
        /// <param name="result">
        /// Address of pointer variable that receives the interface pointer 
        /// requested in riid. Upon successful return, *result contains the 
        /// requested interface pointer. If an error occurs, the implementation 
        /// must set *result to nullptr.
        /// </param>
        void CreateInstanceLic( IUnknown* outerUnknown, IUnknown* reservedUnknown, REFIID riid, BSTR bstrKey, void** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateInstanceLic( outerUnknown, reservedUnknown, riid, bstrKey, result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateInstanceLic( const Unknown& outerUnknown, const Unknown& reservedUnknown, REFIID riid, BSTR bstrKey, void** result ) const
        {
            CreateInstanceLic( outerUnknown.GetInterfacePointer(), reservedUnknown.GetInterfacePointer( ), riid, bstrKey, result );
        }
        void CreateInstanceLic( IUnknown* outerUnknown, REFIID riid, BSTR bstrKey, void** result ) const
        {
            CreateInstanceLic( outerUnknown, nullptr, riid, bstrKey, result );
        }
        void CreateInstanceLic( const Unknown& outerUnknown, REFIID riid, BSTR bstrKey, void** result ) const
        {
            CreateInstanceLic( outerUnknown.GetInterfacePointer( ), nullptr, riid, bstrKey, result );
        }

        template<typename T>
            requires std::is_base_of_v<IUnknown,T>
        void CreateInstanceLic( IUnknown* outerUnknown, IUnknown* reservedUnknown, BSTR bstrKey, T** result ) const
        {
            CreateInstanceLic( outerUnknown, reservedUnknown, __uuidof( T ), bstrKey, reinterpret_cast<void**>(result) );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstanceLic( IUnknown* outerUnknown, BSTR bstrKey, T** result ) const
        {
            CreateInstanceLic( outerUnknown, nullptr, __uuidof( T ), bstrKey, reinterpret_cast<void**>( result ) );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstanceLic( const Unknown& outerUnknown, BSTR bstrKey, T** result ) const
        {
            CreateInstanceLic( outerUnknown.GetInterfacePointer( ), nullptr, __uuidof( T ), bstrKey, reinterpret_cast<void**>( result ) );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstanceLic( const Unknown& outerUnknown, const SysString& bstrKey, T** result ) const
        {
            CreateInstanceLic( outerUnknown.GetInterfacePointer( ), nullptr, __uuidof( T ), bstrKey.c_str( ), reinterpret_cast<void**>( result ) );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstanceLic( BSTR bstrKey, T** result ) const
        {
            CreateInstanceLic( nullptr, nullptr, __uuidof( T ), bstrKey, reinterpret_cast<void**>( result ) );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstanceLic( const SysString& bstrKey, T** result ) const
        {
            CreateInstanceLic( nullptr, nullptr, __uuidof( T ), bstrKey.c_str( ), reinterpret_cast<void**>( result ) );
        }

        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        void CreateInstanceLic( IUnknown* outerUnknown, BSTR bstrKey ) const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* ptr = nullptr;
            CreateInstanceLic( outerUnknown, bstrKey, &ptr );
            return T( ptr );
        }
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        void CreateInstanceLic( const Unknown& outerUnknown, BSTR bstrKey ) const
        {
            return CreateInstanceLic( outerUnknown.GetInterfacePointer(), bstrKey );
        }
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        void CreateInstanceLic( IUnknown* outerUnknown, const SysString& bstrKey ) const
        {
            return CreateInstanceLic( outerUnknown.GetInterfacePointer( ), bstrKey.c_str( ) );
        }
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        void CreateInstanceLic( const Unknown& outerUnknown, const SysString& bstrKey ) const
        {
            return CreateInstanceLic( outerUnknown.GetInterfacePointer( ), bstrKey.c_str( ) );
        }

        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        void CreateInstanceLic( BSTR bstrKey ) const
        {
            return CreateInstanceLic( nullptr, bstrKey );
        }
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        void CreateInstanceLic( const SysString& bstrKey ) const
        {
            return CreateInstanceLic( nullptr, bstrKey.c_str( ) );
        }
    };

    /// <summary>
    /// An extension to ProvideClassInfo (IProvideClassInfo) that makes is 
    /// faster and easier to retrieve an object's outgoing interface IID 
    /// for its default event set.
    /// </summary>
    class ProvideClassInfo2 : public ProvideClassInfo
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ProvideClassInfo2, ProvideClassInfo, IProvideClassInfo2, IProvideClassInfo )

        /// <summary>
        /// Retrieves the specified GUID for the object.
        /// </summary>
        /// <param name="guidKind">
        /// The GUID type. Currently only GUIDKIND_DEFAULT_SOURCE_DISP_IID is
        /// supported. GUIDKIND_DEFAULT_SOURCE_DISP_IID is the interface identifier 
        /// (IID) of the object's outgoing dispinterface, labeled [source, default]. 
        /// The outgoing interface in question must be derived from IDispatch.
        /// </param>
        /// <param name="result">
        /// A pointer to a variable that receives the GUID.
        /// </param>
        void GetGUID( DWORD guidKind, GUID* result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetGUID( guidKind, result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetGUID( GUID* result ) const
        {
            GetGUID( GUIDKIND_DEFAULT_SOURCE_DISP_IID, result );
        }
        Guid GetGUID( ) const
        {
            GUID result;
            GetGUID( &result );
            return result;
        }
    };

    /// <summary>
    /// An extension to IProvideClassInfo2 that makes it faster and 
    /// easier to retrieve type information from a component that may 
    /// have multiple coclasses that determine its behavior.
    /// </summary>
    class ProvideMultipleClassInfo : public ProvideClassInfo2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ProvideMultipleClassInfo, ProvideClassInfo2, IProvideMultipleClassInfo, IProvideClassInfo2 )

        void GetMultiTypeInfoCount( ULONG* result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMultiTypeInfoCount( result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        ULONG GetMultiTypeInfoCount( ) const
        {
            ULONG result;
            GetMultiTypeInfoCount( &result );
            return result;
        }

        void GetInfoOfIndex( ULONG iti, DWORD dwFlags, ITypeInfo** pptiCoClass, DWORD* pdwTIFlags, ULONG* pcdispidReserved, IID* piidPrimary, IID* piidSource ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetInfoOfIndex( iti, dwFlags, pptiCoClass, pdwTIFlags, pcdispidReserved, piidPrimary, piidSource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Provides the features for supporting keyboard mnemonics, 
    /// ambient properties, and events in control objects.
    /// </summary>
    class OleControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleControl, Unknown, IOleControl, IUnknown )

        void GetControlInfo( CONTROLINFO* controlInfo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetControlInfo( controlInfo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetControlInfo( CONTROLINFO& controlInfo ) const
        {
            GetControlInfo( &controlInfo );
        }

        void OnMnemonic( const MSG* msg ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnMnemonic( const_cast<MSG*>(msg) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void OnMnemonic( const MSG& msg ) const
        {
            OnMnemonic( msg );
        }

        void OnAmbientPropertyChange( DISPID dispID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnAmbientPropertyChange( dispID );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void FreezeEvents( BOOL freeze ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->FreezeEvents( freeze );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Provides the methods that enable a site object to manage each embedded 
    /// control within a container. A site object provides IOleControlSite as 
    /// well as other site interfaces such as IOleClientSite and IOleInPlaceSite. 
    /// When a control requires the services expressed through this interface, 
    /// it will query one of the other client site interfaces for IOleControlSite.
    /// </summary>
    class OleControlSite : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleControlSite, Unknown, IOleControlSite, IUnknown )

        void OnControlInfoChanged( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnControlInfoChanged( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void LockInPlaceActive( bool lock ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->LockInPlaceActive( lock? TRUE : FALSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetExtendedControl( IDispatch** dispatchResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetExtendedControl( dispatchResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void TransformCoords( POINTL* pPtlHimetric, POINTF* pPtfContainer, DWORD flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->TransformCoords( pPtlHimetric, pPtfContainer, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void TranslateAccelerator(MSG* msg, DWORD modifiers ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->TranslateAccelerator( msg, modifiers );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void TranslateAccelerator( MSG& msg, DWORD modifiers ) const
        {
            TranslateAccelerator( &msg, modifiers );
        }

        void OnFocus( bool gotFocus ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnFocus( gotFocus ? TRUE : FALSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ShowPropertyFrame( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ShowPropertyFrame( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// <p>
    /// Provides the main features of a property page object that manages a 
    /// particular page within a property sheet. A property page implements 
    /// at least IPropertyPage and can optionally implement IPropertyPage2 
    /// if selection of a specific property is supported. See 
    /// IPerPropertyBrowsing::MapPropertyToPage for more information on 
    /// specific property browsing. The methods of IPropertyPage2 enable 
    /// the property sheet or property frame to instruct the page when to 
    /// perform specific actions, mostly based on user input such as 
    /// switching between pages or pressing various buttons that the 
    /// frame itself manages in the dialog box.
    /// </p>
    /// <p>
    /// A property page manages a dialog box that contains only those controls 
    /// that should be displayed for that one page within the property sheet 
    /// itself. This means that the dialog box template used to define the 
    /// page should only carry the WS_CHILD style and no others. It should 
    /// not include any style related to a frame, caption, or system menus 
    /// or controls.
    /// </p>
    /// </summary>
    class PropertyPage : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PropertyPage, Unknown, IPropertyPage, IUnknown )

        void SetPageSite( IPropertyPageSite* pageSite ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetPageSite( pageSite );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Activate( HWND parentWindow, const RECT* rect, bool modal ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Activate( parentWindow, rect, modal ? TRUE : FALSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Activate( HWND parentWindow, const RECT& rect, bool modal ) const
        {
            Activate( parentWindow, &rect, modal );
        }

        void Deactivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Deactivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPageInfo( __RPC__out PROPPAGEINFO* pageInfo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPageInfo( pageInfo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetPageInfo( PROPPAGEINFO& pageInfo ) const
        {
            GetPageInfo( pageInfo );
        }

        void SetObjects( ULONG numberOfObjects, IUnknown** objectArray ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetObjects( numberOfObjects, objectArray );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Show( UINT showCommand ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Show( showCommand );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Move( const RECT* rect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Move( rect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsPageDirty( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsPageDirty( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }

        bool Apply( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Apply( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }

        bool Help( LPCOLESTR helpDirectory ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Help( helpDirectory );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == S_OK;
        }

        bool TranslateAccelerator( MSG* msg ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->TranslateAccelerator( msg );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == S_OK;
        }
        bool TranslateAccelerator( MSG& msg ) const
        {
            return TranslateAccelerator( &msg );
        }
    };


    /// <summary>
    /// <p>
    /// An extension to IPropertyPage to support initial selection 
    /// of a property on a page.
    /// </p>
    /// <p>
    /// This method works in conjunction with the implementation of 
    /// IPerPropertyBrowsing::MapPropertyToPage on an object that 
    /// supplies properties and specifies property pages through 
    /// ISpecifyPropertyPages. This interface has only one extra 
    /// method in addition to those in IPropertyPage. That method, 
    /// IPropertyPage2::EditProperty tells the page which property to highlight.
    /// </p>
    /// </summary>
    class PropertyPage2 : public PropertyPage
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PropertyPage2, PropertyPage, IPropertyPage2, IPropertyPage )

        void EditProperty( DISPID dispID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EditProperty( dispID );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Provides the main features for a property page site object.
    /// </summary>
    class PropertyPageSite : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PropertyPageSite, Unknown, IPropertyPageSite, IUnknown )

        void OnStatusChange( DWORD flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnStatusChange( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetLocaleID( __RPC__out LCID* localeID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLocaleID( localeID );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetLocaleID( LCID& localeID ) const
        {
            GetLocaleID( &localeID );
        }
        LCID GetLocaleID( ) const
        {
            LCID result = 0;
            GetLocaleID( &result );
            return result;
        }

        /// <summary>
        /// Retrieves a pointer to the object representing the entire property 
        /// frame dialog box that contains all the pages. Calling this method 
        /// could potentially allow one page to navigate to another.
        /// </summary>
        /// <param name="result">
        /// A pointer to an IUnknown pointer variable that receives the interface 
        /// pointer to the container object. If an error occurs, the implementation 
        /// must set *result to nullptr.
        /// </param>
        bool GetPageContainer( __RPC__deref_out_opt IUnknown** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPageContainer( result );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr != E_NOTIMPL;
        }
        template<typename T>
        requires std::is_base_of_v<Unknown,T>
        T GetPageContainer( ) const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* ptr = nullptr;
            if ( GetPageContainer( &ptr ) )
            {
                return T( ptr );
            }
            else
            {
                return T( );
            }
        }

        /// <summary>
        /// Passes a keystroke to the property frame for processing.
        /// </summary>
        /// <param name="msg">
        /// A pointer to the MSG structure to be processed.
        /// </param>
        /// <returns>
        /// true if the message was processed by the IPropertyPageSite.
        /// </returns>
        bool TranslateAccelerator( __RPC__in MSG* msg ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->TranslateAccelerator( msg );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == S_OK;
        }
        bool TranslateAccelerator( MSG& msg ) const
        {
            return TranslateAccelerator( &msg );
        }
    };


    /// <summary>
    /// <p>
    /// Implemented by a sink object to receive notifications about 
    /// property changes from an object that supports IPropertyNotifySink as 
    /// an outgoing interface. The client that needs to receive the 
    /// notifications in this interface (from a supporting connectable object) 
    /// creates a sink with this interface and connects it to the connectable 
    /// object through the connection point mechanism. 
    /// </p>
    /// </summary>
    /// <remarks>
    /// <p>
    /// The object is itself required to call the methods of IPropertyNotifySink 
    /// only for those properties marked with the [bindable] and [requestedit] 
    /// attributes in the object's type information. When the object changes a 
    /// [bindable] property, it is required to call IPropertyNotifySink::OnChanged. 
    /// When the object is about to change a [requestedit] property, it must call 
    /// IPropertyNotifySink::OnRequestEdit before changing the property and must 
    /// also honor the action specified by the sink on return from this call.
    /// </p>
    /// <p>
    /// The one exception to this rule is that no notifications are sent as a 
    /// result of an object's initialization or loading procedures. At initialization 
    /// time, it is assumed that all properties change and that all must be allowed 
    /// to change. Notifications to this interface are therefore meaningful only 
    /// in the context of a fully initialized/loaded object.
    /// </p>
    /// </remarks>
    class PropertyNotifySink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PropertyNotifySink, Unknown, IPropertyNotifySink, IUnknown )

        void OnChanged( DISPID dispID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnChanged( dispID );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        }

        void OnRequestEdit( DISPID dispID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnRequestEdit( dispID );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        }
    };


    using PropertyPageIds = std::vector<Guid>;


    /// <summary>
    /// Indicates that an object supports property pages. OLE property 
    /// pages enable an object to display its properties in a tabbed 
    /// dialog box known as a property sheet. An end user can then 
    /// view and change the object's properties. An object can display 
    /// its property pages independent of its client, or the client 
    /// can manage the display of property pages from a number of contained 
    /// objects in a single property sheet. Property pages also provide 
    /// a means for notifying a client of changes in an object's properties.
    /// </summary>
    /// <remarks>
    /// <p>
    /// A property page object manages a particular page within a property 
    /// sheet. A property page implements at least IPropertyPage and can 
    /// optionally implement IPropertyPage2 if selection of a specific 
    /// property is supported.
    /// </p>
    /// <p>
    /// An object specifies its support for property pages by implementing 
    /// ISpecifyPropertyPages. Through this interface the caller can obtain 
    /// a list of CLSIDs identifying the specific property pages that the 
    /// object supports. If the object specifies a property page CLSID, 
    /// the object must be able to receive property changes from the property page.
    /// </p>
    /// </remarks>
    class SpecifyPropertyPages : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( SpecifyPropertyPages, Unknown, ISpecifyPropertyPages, IUnknown )

        /// <summary>
        /// Retrieves a list of property pages that can be 
        /// displayed in this object's property sheet.
        /// </summary>
        /// <param name="pages">
        /// A pointer to a caller-allocated CAUUID structure that must be 
        /// initialized and filled before returning. The pElems member in 
        /// the structure is allocated by the callee with CoTaskMemAlloc 
        /// and freed by the caller with CoTaskMemFree.
        /// </param>
        void GetPages( __RPC__out CAUUID* pages ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPages( pages );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetPages( CAUUID& pages ) const
        {
            GetPages( &pages );
        }
        void GetPages( PropertyPageIds& result ) const
        {
            CAUUID pages{};
            GetPages( pages );
            
            if ( pages.cElems )
            {
                result.resize( static_cast<size_t>( pages.cElems ) );
                memcpy( result.data( ), pages.pElems, static_cast<size_t>( pages.cElems ) * sizeof( GUID ) );
                CoTaskMemFree( pages.pElems );
            }
            else
            {
                result.clear( );
            }
        }
        PropertyPageIds GetPages( ) const
        {
            PropertyPageIds result;
            GetPages( result );
            return result;
        }
    };


    /// <summary>
    /// Saves and loads objects from a stream.
    /// </summary>
    /// <remarks>
    /// <p>
    /// The IPersistMemory interface operates like IPersistStreamInit; except 
    /// that IPersistMemory allows the caller to provide a fixed-size memory 
    /// block, while IPersistStreamInit uses an arbitrarily expandable IStream.
    /// </p>
    /// </remarks>
    class PersistMemory : public Persist
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PersistMemory, Persist, IPersistMemory, IPersist )

        bool IsDirty( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsDirty( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }

        void Load( LPVOID buffer, ULONG bufferSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( buffer, bufferSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Save( LPVOID buffer, bool clearDirty, ULONG bufferSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Save( buffer, clearDirty, bufferSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSizeMax( __RPC__out ULONG* maxSizeInBytes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSizeMax( maxSizeInBytes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        ULONG GetSizeMax( ) const
        {
            ULONG result = 0;
            GetSizeMax( &result );
            return result;
        }

        void InitNew( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InitNew( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class PersistStreamInit : public Persist
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PersistStreamInit, Persist, IPersistStreamInit, IPersist )

        bool IsDirty( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsDirty( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }

        void Load( __RPC__in_opt LPSTREAM stream ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( stream );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Save( __RPC__in_opt LPSTREAM stream, bool clearDirty ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Save( stream, clearDirty );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSizeMax( __RPC__out UInt64* maxSizeInBytes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSizeMax( reinterpret_cast<ULARGE_INTEGER*>( maxSizeInBytes ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        UInt64 GetSizeMax( ) const
        {
            UInt64 result = 0;
            GetSizeMax( &result );
            return result;
        }

        void InitNew( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InitNew( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Works with IPropertyBag and IErrorlog to define an individual 
    /// property-based persistence mechanism.
    /// </summary>
    /// <remarks>
    /// IPersistPropertyBag provides an object with an IPropertyBag interface through 
    /// which it can save and load individual properties. The object that implements 
    /// IPropertyBag can then save those properties in various ways, such as name/value 
    /// pairs in a text file. Errors encountered in the process (on either side) are 
    /// recorded in an error log through IErrorlog. This error reporting mechanism 
    /// works on a per-property basis instead of on all properties at once.
    /// </remarks>
    class PersistPropertyBag : public Persist
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PersistPropertyBag, Persist, IPersistPropertyBag, IPersist )

        void InitNew( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InitNew( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Load(IPropertyBag* propertyBag, __RPC__in_opt IErrorLog* errorLog ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( propertyBag, errorLog );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Save(__RPC__in_opt IPropertyBag* propertyBag, bool clearDirty, bool saveAllProperties ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Save( propertyBag, clearDirty, saveAllProperties );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// <p>
    /// Provides simple frame controls that act as simple containers for other 
    /// nested controls. Some controls merely contain other controls. In such 
    /// cases, the simple control container, called a simple frame, need not 
    /// implement all container requirements. It can delegate most of the interface 
    /// calls from its contained controls to the outer container that manages the 
    /// simple frame. To support what are called simple frame controls, a container 
    /// implements this interface as well as other site interfaces such as IOleControlSite.
    /// </p>
    /// <p>
    /// An example of a simple frame control is a group box that only needs to capture 
    /// a few keystrokes for its contained controls to implement the correct tab or arrow 
    /// key behavior, but does not want to handle every other message. Through the two 
    /// methods of this interface, the simple frame control passes messages to its control 
    /// site both before and after its own processing. If that site is itself a simple 
    /// frame, it can continue to pass messages up the chain.
    /// </p>
    /// </summary>
    class SimpleFrameSite : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( SimpleFrameSite, Unknown, ISimpleFrameSite, IUnknown )

        /// <summary>
        /// Provides a site with the opportunity to process a message that is 
        /// received by a control's own window before the control itself does 
        /// any processing.
        /// </summary>
        /// <param name="hWnd">
        /// A handle of the control window receiving the message.
        /// </param>
        /// <param name="msg">
        /// The message received by the simple frame site.
        /// </param>
        /// <param name="wp">
        /// The WPARAM of the message.
        /// </param>
        /// <param name="lp">
        /// The LPARAM of the message.
        /// </param>
        /// <param name="result">
        /// A pointer to the variable that receives the result 
        /// of the message processing.
        /// </param>
        /// <param name="cookie">
        /// A pointer to the variable that will be passed to PostMessageFilter 
        /// if it is called later. This parameter should only contain allocated 
        /// data if this method returns S_OK so it will also receive a call to 
        /// PostMessageFilter which can free the allocation. The caller is not 
        /// in any way responsible for anything returned in this parameter.
        /// </param>
        /// <returns>
        /// true if the site processed the message, otherwise false.
        /// </returns>
        /// <remarks>
        /// Successful return values indicate whether the site wishes to allow 
        /// further processing. true indicates further processing, whereas false means 
        /// do not process further. true also indicates that the control must later 
        /// call PostMessageFilter.
        /// </remarks>
        bool PreMessageFilter( __RPC__in HWND hWnd, UINT msg, WPARAM wp, LPARAM lp, __RPC__out LRESULT* result, __RPC__out DWORD* cookie ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PreMessageFilter( hWnd, msg, wp, lp, result, cookie );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == S_OK;
        }

        /// <summary>
        /// Sends the simple frame site a message that is received by a control's own 
        /// window after the control has processed the message.
        /// </summary>
        /// <param name="hWnd">
        /// A handle of the control window receiving the message.
        /// </param>
        /// <param name="msg">
        /// The message received by the simple frame site.
        /// </param>
        /// <param name="wp">
        /// The WPARAM of the message.
        /// </param>
        /// <param name="lp">
        /// The LPARAM of the message.
        /// </param>
        /// <param name="result">
        /// A pointer to the variable that receives the result of the message processing.
        /// </param>
        /// <param name="cookie">
        /// The value that was returned by ISimpleFrameSite::PreMessageFilter 
        /// through its cookie parameter.
        /// </param>
        /// <returns>
        /// true if the site processed the message, otherwise false.
        /// </returns>
        bool PostMessageFilter( __RPC__in HWND hWnd, UINT msg, WPARAM wp, LPARAM lp, __RPC__out LRESULT* result, DWORD cookie ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PostMessageFilter( hWnd, msg, wp, lp, result, cookie );
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == S_OK;
        }
    };

    /// <summary>
    /// <p>
    /// Provides a wrapper around a Windows font object. The COM font object 
    /// supports a number of read/write properties as well as a set of methods 
    /// through its IFont interface. It supports the same set of properties 
    /// (but not the methods) through the dispatch interface IFontDisp, which is 
    /// derived from IDispatch to provide access to the font's properties through 
    /// Automation. The system provides a standard implementation of the font 
    /// object with both interfaces.
    /// </p>
    /// <p>
    /// The font object also supports the outgoing interface IPropertyNotifySink 
    /// so a client can determine when font properties change. Because the font 
    /// object supports at least one outgoing interface, it also implements 
    /// IConnectionPointContainer and related interfaces for this purpose.
    /// </p>
    /// <p>
    /// The font object provides an hFont property, which is a Windows font handle 
    /// that conforms to the other attributes specified for the font. The font object 
    /// delays realizing this hFont object when possible, so consecutively setting 
    /// two properties on a font will not cause an intermediate font to be realized. 
    /// In addition, as an optimization, the system-implemented font object maintains 
    /// a cache of font handles. Two font objects in the same process that have identical 
    /// properties will return the same font handle. The font object can remove font 
    /// handles from this cache at will, which introduces special considerations for 
    /// clients using the hFont property.
    /// </p>
    /// <p>
    /// The font object also supports IPersistStream so that it can save and load 
    /// itself from an instance of IStream. An object that uses a font object 
    /// internally would normally save and load the font as part of the object's 
    /// own persistence handling.
    /// </p>
    /// <p>
    /// In addition, the font object supports IDataObject, which can render a property 
    /// set containing the font's attributes, allowing a client to save these properties as text.
    /// </p>
    /// </summary>
    class Font : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Font, Unknown, IFont, IUnknown )

        void get_Name( __RPC__deref_out_opt BSTR* name ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Name( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Name( __RPC__in BSTR name ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Name( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Size( __RPC__out CY* size ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Size( size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Size(  CY size ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Size( size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Bold( __RPC__out BOOL* bold ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Bold( bold );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Bold( BOOL bold ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Bold( bold );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Italic( __RPC__out BOOL* italic ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Italic( italic );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Italic( BOOL italic ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Italic( italic );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Underline( __RPC__out BOOL* underline ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Underline( underline );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Underline( BOOL underline ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Underline( underline );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Strikethrough( __RPC__out BOOL* strikethrough ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Strikethrough( strikethrough );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Strikethrough( BOOL strikethrough ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Strikethrough( strikethrough );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Weight( __RPC__out SHORT* weight ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Weight( weight );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Weight( SHORT weight ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Weight( weight );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Charset( __RPC__out SHORT* charset ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Charset( charset );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_Charset( SHORT charset ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_Charset( charset );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_hFont( __RPC__deref_out_opt HFONT* fontHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_hFont( fontHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Clone( __RPC__deref_out_opt IFont** font ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clone( font );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void IsEqual( __RPC__in_opt IFont* otherFont ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsEqual( otherFont );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetRatio( LONG logicalSize, LONG himetricSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetRatio( logicalSize, himetricSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void QueryTextMetrics( __RPC__out TEXTMETRICOLE* textMetrics ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryTextMetrics( textMetrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddRefHfont( __RPC__in HFONT fontHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddRefHfont( fontHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReleaseHfont( __RPC__in HFONT fontHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReleaseHfont( fontHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetHdc( __RPC__in HDC deviceContrextHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetHdc( deviceContrextHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// <p>
    /// Manages a picture object and its properties. Picture objects provide 
    /// a language-neutral abstraction for bitmaps, icons, and metafiles. As 
    /// with the standard font object, the system provides a standard implementation 
    /// of the picture object. Its primary interfaces are IPicture and IPictureDisp, 
    /// the latter being derived from IDispatch to provide access to the picture's 
    /// properties through Automation. A picture object is created with 
    /// OleCreatePictureIndirect.
    /// </p>
    /// <p>
    /// The picture object also supports the outgoing interface IPropertyNotifySink, 
    /// so a client can determine when picture properties change. Because the picture 
    /// object supports at least one outgoing interface, it also implements 
    /// IConnectionPointContainer and its associated interfaces for this purpose.
    /// </p>
    /// <p>
    /// The picture object also supports IPersistStream so that it can save 
    /// and load itself from an instance of IStream. An object that uses a 
    /// picture object internally would normally save and load the picture 
    /// as part of the object's own persistence handling. The function 
    /// OleLoadPicture simplifies the creation of a picture object based on stream contents.
    /// </p>
    /// </summary>
    class Picture : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Picture, Unknown, IPicture, IUnknown )


        static Picture Create( LPPICTDESC pictDesc, bool own )
        {
            IPicture* ptr = nullptr;
            auto hr = OleCreatePictureIndirect( pictDesc, __uuidof( IPicture ), own, reinterpret_cast<void**>( &ptr ) );
            HCC_COM_CHECK_HRESULT( hr );
            return Picture( ptr );
        }

        static Picture Create( LPSTREAM stream, LONG byteSize, bool runmode )
        {
            IPicture* ptr = nullptr;
            auto hr = OleLoadPicture( stream, byteSize, runmode, __uuidof( IPicture ), reinterpret_cast<void**>( &ptr ) );
            HCC_COM_CHECK_HRESULT( hr );
            return Picture( ptr );
        }
        static Picture Create( LPSTREAM stream, LONG byteSize, bool runmode, DWORD desiredWidth, DWORD desiredHeight, DWORD flags )
        {
            IPicture* ptr = nullptr;
            auto hr = OleLoadPictureEx( stream, byteSize, runmode, __uuidof( IPicture ), desiredWidth, desiredHeight, flags, reinterpret_cast<void**>( &ptr ) );
            HCC_COM_CHECK_HRESULT( hr );
            return Picture( ptr );
        }


        void get_Handle( OLE_HANDLE* handle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Handle( handle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        OLE_HANDLE get_Handle( ) const
        {
            OLE_HANDLE result = 0;
            get_Handle( &result );
            return result;
        }

        void get_hPal( __RPC__out OLE_HANDLE* paletteHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_hPal( paletteHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        OLE_HANDLE get_hPal( ) const
        {
            OLE_HANDLE result = 0;
            get_hPal( &result );
            return result;
        }

        void get_Type( __RPC__out SHORT* type ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Type( type );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SHORT get_Type( ) const
        {
            SHORT result = 0;
            get_Type( &result );
            return result;
        }

        void get_Width( __RPC__out OLE_XSIZE_HIMETRIC* width ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Width( width );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        OLE_XSIZE_HIMETRIC get_Width( ) const
        {
            OLE_XSIZE_HIMETRIC result = 0;
            get_Width( &result );
            return result;
        }

        void get_Height( __RPC__out OLE_YSIZE_HIMETRIC* height ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Height( height );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        OLE_YSIZE_HIMETRIC get_Height( ) const
        {
            OLE_YSIZE_HIMETRIC result = 0;
            get_Height( &result );
            return result;
        }

        void Render( __RPC__in HDC hDC, LONG x, LONG y, LONG cx, LONG cy, OLE_XPOS_HIMETRIC xSrc, OLE_YPOS_HIMETRIC ySrc, OLE_XSIZE_HIMETRIC cxSrc, OLE_YSIZE_HIMETRIC cySrc, __RPC__in LPCRECT pRcWBounds ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Render( hDC, x, y, cx, cy, xSrc, ySrc, cxSrc, cySrc, pRcWBounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void set_hPal( OLE_HANDLE paletteHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->set_hPal( paletteHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_CurDC( __RPC__deref_out_opt HDC* deviceContextHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_CurDC( deviceContextHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SelectPicture( __RPC__in HDC deviceContextHandle, __RPC__deref_out_opt HDC* phDCOut, __RPC__out OLE_HANDLE* phBmpOut ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SelectPicture( deviceContextHandle, phDCOut, phBmpOut );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_KeepOriginalFormat( __RPC__out BOOL* keep ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_KeepOriginalFormat( keep );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_KeepOriginalFormat( BOOL keep ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_KeepOriginalFormat( keep );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PictureChanged( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PictureChanged( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SaveAsFile( __RPC__in_opt LPSTREAM stream, BOOL saveMemCopy, __RPC__out LONG* sizeInBytes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SaveAsFile( stream, saveMemCopy, sizeInBytes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Attributes( __RPC__out DWORD* attributes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Attributes( attributes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class Picture2 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Picture2, Unknown, IPicture2, IUnknown )


        static Picture2 Create( LPPICTDESC pictDesc, bool own )
        {
            IPicture2* ptr = nullptr;
            auto hr = OleCreatePictureIndirect( pictDesc, __uuidof( IPicture2 ), own, reinterpret_cast<void**>( &ptr ) );
            HCC_COM_CHECK_HRESULT( hr );
            return Picture2( ptr );
        }

        static Picture2 Create( LPSTREAM stream, LONG byteSize, bool runmode )
        {
            IPicture2* ptr = nullptr;
            auto hr = OleLoadPicture( stream, byteSize, runmode, __uuidof( IPicture2 ), reinterpret_cast<void**>( &ptr ) );
            HCC_COM_CHECK_HRESULT( hr );
            return Picture2( ptr );
        }
        static Picture2 Create( LPSTREAM stream, LONG byteSize, bool runmode, DWORD desiredWidth, DWORD desiredHeight, DWORD flags )
        {
            IPicture2* ptr = nullptr;
            auto hr = OleLoadPictureEx( stream, byteSize, runmode, __uuidof( IPicture2 ), desiredWidth, desiredHeight, flags, reinterpret_cast<void**>( &ptr ) );
            HCC_COM_CHECK_HRESULT( hr );
            return Picture2( ptr );
        }


        void get_Handle( HHANDLE* handle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Handle( handle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        HHANDLE get_Handle( ) const
        {
            HHANDLE result = 0;
            get_Handle( &result );
            return result;
        }

        void get_hPal( __RPC__out HHANDLE* paletteHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_hPal( paletteHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        HHANDLE get_hPal( ) const
        {
            HHANDLE result = 0;
            get_hPal( &result );
            return result;
        }

        void get_Type( __RPC__out SHORT* type ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Type( type );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SHORT get_Type( ) const
        {
            SHORT result = 0;
            get_Type( &result );
            return result;
        }

        void get_Width( __RPC__out OLE_XSIZE_HIMETRIC* width ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Width( width );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        OLE_XSIZE_HIMETRIC get_Width( ) const
        {
            OLE_XSIZE_HIMETRIC result = 0;
            get_Width( &result );
            return result;
        }

        void get_Height( __RPC__out OLE_YSIZE_HIMETRIC* height ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Height( height );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        OLE_YSIZE_HIMETRIC get_Height( ) const
        {
            OLE_YSIZE_HIMETRIC result = 0;
            get_Height( &result );
            return result;
        }

        void Render( __RPC__in HDC hDC, LONG x, LONG y, LONG cx, LONG cy, OLE_XPOS_HIMETRIC xSrc, OLE_YPOS_HIMETRIC ySrc, OLE_XSIZE_HIMETRIC cxSrc, OLE_YSIZE_HIMETRIC cySrc, __RPC__in LPCRECT pRcWBounds ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Render( hDC, x, y, cx, cy, xSrc, ySrc, cxSrc, cySrc, pRcWBounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void set_hPal( HHANDLE paletteHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->set_hPal( paletteHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_CurDC( __RPC__deref_out_opt HDC* deviceContextHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_CurDC( deviceContextHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SelectPicture( __RPC__in HDC deviceContextHandle, __RPC__deref_out_opt HDC* phDCOut, __RPC__out HHANDLE* phBmpOut ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SelectPicture( deviceContextHandle, phDCOut, phBmpOut );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_KeepOriginalFormat( __RPC__out BOOL* keep ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_KeepOriginalFormat( keep );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void put_KeepOriginalFormat( BOOL keep ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_KeepOriginalFormat( keep );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PictureChanged( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PictureChanged( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SaveAsFile( __RPC__in_opt LPSTREAM stream, BOOL saveMemCopy, __RPC__out LONG* sizeInBytes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SaveAsFile( stream, saveMemCopy, sizeInBytes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Attributes( __RPC__out DWORD* attributes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Attributes( attributes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class FontEventsDisp : public Dispatch
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( FontEventsDisp, Dispatch, IFontEventsDisp, IDispatch )
    };

    class FontDisp : public Dispatch
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( FontDisp, Dispatch, IFontDisp, IDispatch )
    };

    class PictureDisp : public Dispatch
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PictureDisp, Dispatch, IPictureDisp, IDispatch )
    };


    /// <summary>
    /// <p>
    /// Manages the activation and deactivation of in-place objects, and 
    /// determines how much of the in-place object should be visible.
    /// </p>
    /// <p>
    /// You can obtain a pointer to IOleInPlaceObject by calling 
    /// IUnknown::QueryInterface on IOleObject or an OleInPlaceObject
    /// by calling As&ltOleInPlaceObject&gt() on an OleObject.
    /// </p>
    /// </summary>
    class OleInPlaceObject : public OleWindow
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceObject, OleWindow, IOleInPlaceObject, IOleWindow )

        /// <summary>
        /// Deactivates an active in-place object and discards the object's undo state.
        /// </summary>
        void InPlaceDeactivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InPlaceDeactivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        /// <summary>
        /// Deactivates and removes the user interface of an active in-place object.
        /// </summary>
        void UIDeactivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UIDeactivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        /// <summary>
        /// Specifies how much of the in-place object is to be visible.
        /// </summary>
        /// <param name="positionRect">
        /// A pointer to the RECT structure containing the position of the in-place 
        /// object using the client coordinates of its parent window.
        /// </param>
        /// <param name="clipRect">
        /// A pointer to the outer rectangle containing the in-place object's position 
        /// rectangle (positionRect). This rectangle is relative to the client area of 
        /// the object's parent window.
        /// </param>
        void SetObjectRects(  LPCRECT positionRect, __RPC__in LPCRECT clipRect) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetObjectRects( positionRect, clipRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        /// <summary>
        /// Reactivates a previously deactivated object, undoing the last state of the object.
        /// </summary>
        /// <remarks>
        /// If the user chooses the Undo command before the undo state of the object is 
        /// lost, the object's immediate container calls ReactivateAndUndo to activate 
        /// the user interface, carry out the undo operation, and return the object to 
        /// the active state.
        /// </remarks>
        void ReactivateAndUndo( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReactivateAndUndo( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
    };


    /// <summary>
    /// <p>
    /// Enables a windowless object to process window messages and participate 
    /// in drag and drop operations. It is derived from and extends the 
    /// IOleInPlaceObject interface.
    /// </p>
    /// <p>
    /// A small object, such as a control, does not need a window of its own. 
    /// Instead, it can rely on its container to dispatch window messages and 
    /// help the object to participate in drag and drop operations. The 
    /// container must implement the IOleInPlaceSiteWindowless interface. 
    /// Otherwise, the object must act as a normal compound document object 
    /// and create a window when it is activated.
    /// </p>
    /// </summary>
    class OleInPlaceObjectWindowless : public OleInPlaceObject
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceObjectWindowless, OleInPlaceObject, IOleInPlaceObjectWindowless, IOleInPlaceObject )

        void OnWindowMessage( UINT msg, WPARAM wParam, LPARAM lParam, __RPC__out LRESULT* result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnWindowMessage( msg, wParam, lParam, result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDropTarget(IDropTarget** dropTarget ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDropTarget( dropTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };



    /// <summary>
    /// <p>
    /// Manages the interaction between the container and the object's 
    /// in-place client site. Recall that the client site is the display 
    /// site for embedded objects, and provides position and conceptual 
    /// information about the object.
    /// </p>
    /// <p>
    /// This interface provides methods that manage in-place objects. 
    /// With IOleInPlaceSite, you can determine if an object can be 
    /// activated and manage its activation and deactivation. You can 
    /// notify the container when one of its objects is being activated 
    /// and inform the container that a composite menu will replace the 
    /// container's regular menu. It provides methods that make it 
    /// possible for the in-place object to retrieve the window object 
    /// hierarchy, and the position in the parent window where the object 
    /// should place its in-place activation window. Finally, it 
    /// determines how the container scrolls the object, manages the 
    /// object undo state, and notifies the object when its borders have 
    /// changed.
    /// </p>
    /// </summary>
    class OleInPlaceSite : public OleWindow
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceSite, OleWindow, IOleInPlaceSite, IOleWindow )

        void CanInPlaceActivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CanInPlaceActivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnInPlaceActivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnInPlaceActivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnUIActivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnUIActivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetWindowContext( IOleInPlaceFrame** inPlaceFrame, IOleInPlaceUIWindow** inPlaceUIWindow, LPRECT positionRect, LPRECT clipRect, LPOLEINPLACEFRAMEINFO frameInfo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetWindowContext( inPlaceFrame, inPlaceUIWindow, positionRect, clipRect, frameInfo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Scroll( SIZE scrollExtant ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Scroll( scrollExtant );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnUIDeactivate( bool undoable ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnUIDeactivate( undoable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnInPlaceDeactivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnInPlaceDeactivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DiscardUndoState( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DiscardUndoState( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeactivateAndUndo( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeactivateAndUndo( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnPosRectChange( __RPC__in LPCRECT positionRect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnPosRectChange( positionRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// <p>
    /// Provides an additional set of activation and deactivation notification 
    /// methods that enable an object to avoid unnecessary flashing on the 
    /// screen when the object is activated and deactivated.
    /// </p>
    /// <p>
    /// When an object is activated, it does not know if its visual display 
    /// is already correct. When the object is deactivated, the container 
    /// does not know if the visual display is correct. To avoid a redraw 
    /// and the associated screen flicker in both cases, the container 
    /// can provide this extension to IOleInPlaceSite.
    /// </p>
    /// </summary>
    class OleInPlaceSiteEx : public OleInPlaceSite
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceSiteEx, OleInPlaceSite, IOleInPlaceSiteEx, IOleInPlaceSite )

        void OnInPlaceActivateEx( __RPC__out BOOL* noRedraw, DWORD flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnInPlaceActivateEx( noRedraw, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnInPlaceDeactivateEx( BOOL noRedraw ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnInPlaceDeactivateEx( noRedraw );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RequestUIActivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestUIActivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// <p>
    /// Extends the IOleInPlaceSiteEx interface. IOleInPlaceSiteWindowless works with 
    /// IOleInPlaceObjectWindowless which is implemented on the windowless object. 
    /// Together, these two interfaces provide services to a windowless object from 
    /// its container allowing the windowless object to:
    /// </p>
    /// <ul>
    /// <li>Process window messages</li>
    /// <li>Participate in drag and drop operations</li>
    /// <li>Perform drawing operations</li>
    /// </ul>
    /// <p>
    /// Having a window can place unnecessary burdens on small objects, such as controls. 
    /// It prevents an object from being non-rectangular. It prevents windows from being 
    /// transparent. It prevents the small instance size needed by many small controls.
    /// </p>
    /// <p>
    /// A windowless object can enter the in-place active state without requiring a window 
    /// or the resources associated with a window. Instead, the object's container provides 
    /// the object with many of the services associated with having a window.
    /// </p>
    /// </summary>
    class OleInPlaceSiteWindowless : public OleInPlaceSiteEx
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleInPlaceSiteWindowless, OleInPlaceSiteEx, IOleInPlaceSiteWindowless, IOleInPlaceSiteEx )

        void CanWindowlessActivate( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CanWindowlessActivate( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCapture( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCapture( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetCapture( bool capture ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetCapture( capture );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFocus( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFocus( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFocus( bool focus ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFocus( focus );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDC( __RPC__in_opt LPCRECT rect, DWORD flags, __RPC__deref_out_opt HDC* deviceContextHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDC( rect, flags, deviceContextHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReleaseDC( __RPC__in HDC deviceContextHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReleaseDC( deviceContextHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void InvalidateRect(__RPC__in_opt LPCRECT rect, BOOL erase ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InvalidateRect( rect, erase );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void InvalidateRgn( __RPC__in HRGN regionHandle, BOOL erase ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InvalidateRgn( regionHandle, erase );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ScrollRect( INT dx, INT dy, __RPC__in LPCRECT scrollRect, __RPC__in LPCRECT clipRect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ScrollRect( dx, dy, scrollRect, clipRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AdjustRect(__RPC__inout LPRECT rect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AdjustRect( rect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, __RPC__out LRESULT* result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnDefWindowMessage( msg, wParam, lParam, result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// <p>
    /// Enables an object to display itself directly without passing a 
    /// data object to the caller. In addition, this interface can create 
    /// and manage a connection with an advise sink so the caller can be 
    /// notified of changes in the view object.
    /// </p>
    /// <p>
    /// The caller can request specific representations and specific target 
    /// devices. For example, a caller can ask for either an object's content 
    /// or an iconic representation. Also, the caller can ask the object to 
    /// compose a picture for a target device that is independent of the 
    /// drawing device context. As a result, the picture can be composed 
    /// for one target device and drawn on another device context. For example, 
    /// to provide a print preview operation, you can compose the drawing for 
    /// a printer target device but actually draw the representation on 
    /// the display.
    /// </p>
    /// <p>
    /// The IViewObject interface is similar to IDataObject; except that 
    /// IViewObject places a representation of the data onto a device 
    /// context while IDataObject places the representation onto a transfer medium.
    /// </p>
    /// <p>
    /// Unlike most other interfaces, IViewObject cannot be marshaled to another 
    /// process. This is because device contexts are only effective in the context 
    /// of one process.
    /// </p>
    /// </summary>
    class ViewObject : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ViewObject, Unknown, IViewObject, IUnknown )

        void Draw(  _In_  DWORD drawAspect, _In_  LONG index, _Null_  void *aspect, _In_opt_  DVTARGETDEVICE *targetDevice, _In_opt_  HDC targetDeviceContext, _In_  HDC drawDeviceContext, _In_opt_  LPCRECTL drawBounds, _In_opt_  LPCRECTL windowBounds, _In_opt_  BOOL ( STDMETHODCALLTYPE *Continue )( ULONG_PTR continueDrawing ), _In_  ULONG_PTR continueDrawing ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Draw( drawAspect, index, aspect, targetDevice, targetDeviceContext, drawDeviceContext, drawBounds, windowBounds, Continue, continueDrawing );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void GetColorSet(  _In_  DWORD drawAspect, _In_  LONG index, _Null_  void *aspect, _In_opt_  DVTARGETDEVICE *targetDevice, _In_opt_  HDC targetDeviceContext, _Outptr_  LOGPALETTE **colorSet) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetColorSet( drawAspect, index, aspect, targetDevice, targetDeviceContext, colorSet );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void Freeze(  _In_  DWORD drawAspect, _In_  LONG index, _Null_  void *aspect, _Out_  DWORD *freeze) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Freeze( drawAspect, index, aspect, freeze );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void Unfreeze( DWORD freeze ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unfreeze( freeze );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void SetAdvise(  DWORD aspects, DWORD adviseFlags, __RPC__in_opt IAdviseSink* adviseSink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetAdvise( aspects, adviseFlags, adviseSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void GetAdvise(  _Out_opt_  DWORD *aspects, _Out_opt_  DWORD * adviseFlags, _Outptr_  IAdviseSink ** adviseSink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAdvise( aspects, adviseFlags, adviseSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
    };


    /// <summary>
    /// <p>
    /// An extension to the IViewObject interface which returns the size 
    /// of the drawing for a given view of an object. You can prevent the 
    /// object from being run if it isn't already running by calling this 
    /// method instead of IOleObject::GetExtent.
    /// </p>
    /// <p>
    /// Like the IViewObject interface, IViewObject2 cannot be marshaled 
    /// to another process. This is because device contexts are only 
    /// effective in the context of one process.
    /// </p>
    /// <p>
    /// The OLE-provided default implementation provides the size of the 
    /// object in the cache.
    /// </p>
    /// </summary>
    class ViewObject2 : public ViewObject
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ViewObject2, ViewObject, IViewObject2, IViewObject )

        void GetExtent( DWORD drawAspect, LONG index, __RPC__in_opt DVTARGETDEVICE* targetDevice, __RPC__out LPSIZEL size ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetExtent( drawAspect, index, targetDevice, size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// <p>
    /// An extension derived from IViewObject2 to provide support for:
    /// </p>
    /// <ul>
    /// <li>Enhanced, flicker-free drawing for non-rectangular objects and transparent objects</li>
    /// <li>Hit testing for non-rectangular objects</li>
    /// <li>Control sizing</li>
    /// </ul>
    /// </summary>
    class ViewObjectEx : public ViewObject2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ViewObjectEx, ViewObject2, IViewObjectEx, IViewObject2 )

        void GetRect( DWORD aspect, __RPC__out LPRECTL rect ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetRect( aspect, rect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetViewStatus( __RPC__out DWORD* status ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetViewStatus( status );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void QueryHitPoint( DWORD aspect, __RPC__in LPCRECT boundsRect, POINT location, LONG closeHint, __RPC__out DWORD* hitResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryHitPoint( aspect, boundsRect, location, closeHint, hitResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void QueryHitRect( DWORD aspect, __RPC__in LPCRECT boundsRect, __RPC__in LPCRECT locationRect, LONG closeHint, __RPC__out DWORD* hitResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryHitRect( aspect, boundsRect, locationRect, closeHint, hitResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetNaturalExtent( DWORD aspect, LONG index, __RPC__in DVTARGETDEVICE* targetDevice, __RPC__in HDC targetDeviceContext, __RPC__in DVEXTENTINFO* extentInfo, __RPC__out LPSIZEL size ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNaturalExtent( aspect, index, targetDevice, targetDeviceContext, extentInfo, size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// <p>
    /// Serves as the main interface on an undo unit. An undo unit 
    /// encapsulates the information necessary to undo or redo a 
    /// single action.
    /// </p>
    /// <p>
    /// When an object's state changes and it needs to create an 
    /// undo unit, it first needs to know what parent units are open. 
    /// It calls the IOleUndoManager::GetOpenParentState method to 
    /// determine this. If the call returns S_FALSE, then there is no 
    /// enabling parent. If the call returns S_OK but the UAS_NOPARENTENABLE 
    /// flag is set, then the open parent is a disabling parent. In 
    /// either of these cases, the object calls IOleUndoManager::DiscardFrom(nullptr) 
    /// on the undo manager and skips creating the undo unit.
    /// </p>
    /// <p>
    /// If the method returns S_OK, but the UAS_BLOCKED flag is set, 
    /// then the open parent is a blocking parent. The object does not 
    /// need to create an undo unit, since it would be immediately 
    /// discarded. If the return value is S_OK and neither of the bit 
    /// flags are set, then the object creates the undo unit and calls 
    /// IOleUndoManager::Add on the undo manager.
    /// </p>
    /// <p>
    /// The object should retain a pointer to the undo manager.
    /// </p>
    /// </summary>
    class OleUndoUnit : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleUndoUnit, Unknown, IOleUndoUnit, IUnknown )

        void Do( __RPC__in_opt IOleUndoManager* undoManager ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Do( undoManager );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDescription( __RPC__deref_out_opt BSTR* bstrDescription ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDescription( bstrDescription );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetUnitType( __RPC__out CLSID* clsid, __RPC__out LONG* id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetUnitType( clsid, id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OnNextAdd( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnNextAdd( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// <p>
    /// Enables undo units to contain child undo units. For example, a 
    /// complex action can be presented to the end user as a single undo 
    /// action even though a number of separate actions are involved. 
    /// All the subordinate undo actions are contained within the top-level, 
    /// parent undo unit.
    /// </p>
    /// <p>
    /// A parent undo unit is initially created using the IOleUndoManager::Open 
    /// method. The addition of undo units should always be done through the 
    /// undo manager. The IOleParentUndoUnit::Open and IOleParentUndoUnit::Close 
    /// methods on parent units will end up being called by the undo manager. 
    /// Having parent units call back into the undo manager will cause infinite 
    /// recursion.
    /// </p>
    /// <p>
    /// While a parent unit is open, the undo manager adds undo units to it by 
    /// calling IOleParentUndoUnit::Add. When the undo manager closes a top-level 
    /// parent, the entire undo unit with its nested subordinates is placed on 
    /// top of the undo stack.
    /// </p>
    /// <p>
    /// An enabling parent is required to be open on the stack before any other 
    /// undo units can be added. If one isn't open, the stack should be cleared 
    /// instead. This is to ensure that undo units only get added as a result of 
    /// user actions and not programmatic actions. For example, if your application 
    /// wants to make clicking a certain button undoable, but that same action 
    /// is also exposed through the object model. That action should be undoable 
    /// through the user interface but not the object model because you cannot 
    /// restore the state of the user's script code. Because the same code 
    /// implements the change in both cases, the UI code that handles the 
    /// button click should open an enabling parent on the stack, call the 
    /// appropriate code, and then close the parent unit. The object model 
    /// code would not open a parent unit, causing the undo stack to be cleared.
    /// </p>
    /// <p>
    /// A blocking parent is used when you do not want your code to call 
    /// other code that you know may try to add undo units to the stack. For 
    /// example, you should use a blocking parent if you call code that 
    /// creates undo units, that your outer code has already created that 
    /// will fully undo all the desired behavior.
    /// </p>
    /// <p>
    /// A non-enabling parent is used when you fire an event in response 
    /// to a user action. The stack would be cleared only if the event handler 
    /// did something that tried to create an undo unit, but if no handler exists 
    /// then the undo stack would be preserved.
    /// </p>
    /// <p>
    /// If an object needs to create a parent unit, there are several cases to consider:
    /// </p>
    /// <ul>
    /// <li>
    /// To create an enabling parent unit, the object calls IOleUndoManager::GetOpenParentState 
    /// on the undo manager and checks the return value. If the value is S_FALSE, then 
    /// the object creates the enabling parent and opens it. If the return value is S_OK,
    /// then there is a parent already open. If the open parent is blocked (UAS_BLOCKED 
    /// bit set), or an enabling parent (UAS_BLOCKED and UAS_NOPARENTENABLE bits not set), 
    /// then there is no need to create the enabling parent. If the currently open parent 
    /// is a disabling parent (UAS_NOPARENTENABLE bit set), then the enabling parent should 
    /// be created and opened to re-enable adding undo units. Note that UAS_NORMAL has 
    /// a value of zero, which means it is the absence of all other bits and is not 
    /// a bit flag that can be set. If comparing *state against UAS_NORMAL, mask out 
    /// unused bits from state with UAS_MASK to allow for future expansion.
    /// </li>
    /// <li>
    /// To create a blocked parent, the object calls IOleUndoManager::GetOpenParentState 
    /// and checks for an open parent that is already blocked. If one exists, then there 
    /// is no need to create the new blocking parent. Otherwise, the object creates it 
    /// and opens it on the stack.
    /// </li>
    /// <li>
    /// To create a disabling parent, the object calls IOleUndoManager::GetOpenParentState 
    /// and checks for an open parent that is blocked or disabling. If either one exists 
    /// it is unnecessary to create the new parent. Otherwise, the object creates the 
    /// parent and opens it on the stack.
    /// </li>
    /// </ul>
    /// <p>
    /// In the event that both the UAS_NOPARENTENABLE and UAS_BLOCKED flags are set, 
    /// the flag that is most relevant to the caller should be used with UAS_NOPARENTENABLE 
    /// taking precedence. For example, if an object is creating a simple undo unit, it 
    /// should pay attention to the UAS_NOPARENTENABLE flag and clear the undo stack. 
    /// If it is creating an enabling parent unit, then it should pay attention to the 
    /// UAS_BLOCKED flag and skip the creation.
    /// </p>
    /// <p>
    /// When the parent undo unit is marked blocked, it discards any undo units it receives.
    /// </p>
    /// </summary>
    class OleParentUndoUnit : public OleUndoUnit
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleParentUndoUnit, OleUndoUnit, IOleParentUndoUnit, IOleUndoUnit )

        void Open( __RPC__in_opt IOleParentUndoUnit* parentUndoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Open( parentUndoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Close( __RPC__in_opt IOleParentUndoUnit* parentUndoUnit, bool commit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Close( parentUndoUnit, commit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Add( __RPC__in_opt IOleUndoUnit* parentUndoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Add( parentUndoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void FindUnit( __RPC__in_opt IOleUndoUnit* undoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->FindUnit( undoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetParentState( __RPC__out DWORD* state ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetParentState( state );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Enumerates the undo units on the undo or redo stack.
    /// </summary>
    class EnumOleUndoUnits : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( EnumOleUndoUnits, Unknown, IEnumOleUndoUnits, IUnknown )

        bool Next( ULONG elementCount, IOleUndoUnit** elements, ULONG* fetchedElementCount ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Next( elementCount, elements, fetchedElementCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }

        void Skip( ULONG elementCount ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( elementCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Clone( __RPC__deref_out_opt IEnumOleUndoUnits** enumOleUndoUnits ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clone( enumOleUndoUnits );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// The IOleUndoManager interface enables containers to implement 
    /// multi-level undo and redo operations for actions that occur 
    /// within contained controls.
    /// </summary>
    /// <remarks>
    /// <p>
    /// The control must create an undo unit with the IOleUndoUnit interface 
    /// or a parent undo unit with the IOleParentUndoUnit interface derived 
    /// from IOleUndoUnit. Both of these interfaces perform the undo action 
    /// and the parent undo unit additionally can contain nested undo units.
    /// </p>
    /// <p>
    /// The undo manager provides a centralized undo and redo service. It 
    /// manages parent undo units and simple undo units on the undo and 
    /// redo stacks. Whether an object is UI-active or not, it can deposit 
    /// undo units on these stacks by calling methods in the undo manager.
    /// </p>
    /// <p>
    /// The centralized undo manager then has the data necessary to support 
    /// the undo and redo user interface for the host application and can 
    /// discard undo information gradually as the stack becomes full.
    /// </p>
    /// <p>
    /// The undo manager is implemented as a service and objects obtain a 
    /// pointer to IOleUndoManger from the IServiceProvider interface. It is 
    /// usually implemented by the container. The service manages two stacks, 
    /// the undo stack and the redo stack, each of which contains undo units 
    /// generated by embedded objects or by the container application itself.
    /// </p>
    /// <p>
    /// Undo units are typically generated in response to actions taken by 
    /// the end user. An object does not generate undo actions for programmatic 
    /// events. In fact, programmatic events should clear the undo stack since 
    /// the programmatic event can possibly invalidate assumptions made by the 
    /// undo units on the stack.
    /// </p>
    /// <p>
    /// When the object's state changes, it creates an undo unit encapsulating 
    /// all the information needed to undo that change. The object calls methods 
    /// in the undo manager to place its undo units on the stack. Then, when the 
    /// end user selects an Undo operation, the undo manager takes the top undo 
    /// unit off the stack, invokes its action by calling its IOleUndoUnit::Do 
    /// method, and then releases it. When an end user selects a Redo operation, 
    /// the undo manager takes the top redo unit off the stack, invokes its 
    /// action by calling its IOleUndoUnit::Do method, and then releases it.
    /// </p>
    /// <p>
    /// The undo manager has three states: the base state, the undo state, and 
    /// the redo state. It begins in the base state. To perform an action from 
    /// the undo stack, it puts itself into the undo state, calls IOleUndoUnit::Do 
    /// on the undo unit, and goes back to the base state. To perform an action 
    /// from the redo stack, it puts itself into the redo state, calls 
    /// IOleUndoUnit::Do on the undo unit, and goes back to the base state.
    /// </p>
    /// <p>
    /// If the undo manager receives a new undo unit while in the base state, it 
    /// places the unit on the undo stack and discards the entire redo stack. 
    /// While it is in the undo state, it puts incoming units on the redo stack. 
    /// While it is in the redo state, it places them on the undo stack without 
    /// flushing the redo stack.
    /// </p>
    /// <p>
    /// The undo manager also allows objects to discard the undo or redo stack 
    /// starting from any object in either stack.
    /// </p>
    /// <p>
    /// The host application determines the scope of an undo manager. For example, 
    /// in one application, the scope might be at the document level; a separate 
    /// undo manager is maintained for each document; and undo is managed independently 
    /// for each document. However, another application maintain one undo manager, and 
    /// therefore one undo scope, for the entire application.
    /// </p>
    /// <h4>Error Handling</h4>
    /// <p>
    /// Having an undo operation fail and leaving the document in an unstable state is 
    /// something the undo manager, undo units, and the application itself all have to 
    /// work together to avoid. As a result, there are certain requirements that undo 
    /// units, the undo manager, and the application or component using undo must conform to.
    /// </p>
    /// <p>
    /// To perform an undo, the undo manager calls IOleUndoUnit::Do on one or more undo 
    /// units which can, in turn, contain more units. If a unit somewhere in the hierarchy 
    /// fails, the error will eventually reach the undo manager, which is responsible 
    /// for making an attempt to roll back the state of the document to what it was 
    /// before the call to the last top-level unit. The undo manager performs the rollback 
    /// by calling IOleUndoUnit::Do on the unit that was added to the redo stack during 
    /// the undo attempt. If the rollback also fails, then the undo manager is forced 
    /// to abandon everything and return to the application. The undo manager indicates 
    /// whether the rollback succeeded, and the application can take different actions 
    /// based on this, such as reinitializing components so they're in a known state.
    /// </p>
    /// <p>
    /// All the steps in adding an undo unit to the stack should be performed atomically. 
    /// That is, all steps must succeed or none of them should succeed.
    /// </p>
    /// <p>
    /// The host application that provides the undo manager decides what action to take 
    /// when undo fails. At the very least, it should inform the user of the failure. 
    /// The host application will be told by the undo manager whether the undo succeeded 
    /// and whether the attempted rollback succeeded. In case both the undo and rollback 
    /// failed, the host application can present the user with several options, including 
    /// immediately shutting down the application.
    /// </p>
    /// <p>
    /// Simple undo units must not change the state of any object if they return failure. 
    /// This includes the state of the redo stack or undo stack if performing a redo. 
    /// They are also required to put a corresponding unit on the redo or undo stack if 
    /// they succeed. The application should be stable before and after the unit is called.
    /// </p>
    /// <p>
    /// Parent undo units have the same requirements as simple units, with one exception. 
    /// If one or more children succeeded prior to another child's failure, the parent 
    /// unit must commit its corresponding unit on the redo stack and return the failure 
    /// to its parent. If no children succeeded, the parent unit should commit its redo 
    /// unit only if it has made a state change that needs to be rolled back. For example, 
    /// suppose a parent unit contains three simple units. The first two succeed and added 
    /// units to the redo stack, but the third one failed. At this point, the parent unit 
    /// commits its redo unit and returns the failure.
    /// </p>
    /// <p>
    /// As a side effect, the parent unit should never make state changes that depend on 
    /// the success of their children. Doing this will cause the rollback behavior to 
    /// break. If a parent unit makes state changes, it should do them before calling 
    /// any children. Then, if the state change fails, it should not commit its redo 
    /// unit, it should not call any children, and it should return the failure to 
    /// its parent.
    /// </p>
    /// <p>
    /// The undo manager has one primary requirement for error handling: to attempt 
    /// rollback when an undo or redo fails.
    /// </p>
    /// <h4>Non-compliant Objects</h4>
    /// <p>
    /// Objects that do not support multi-level undo can cause serious problems for a 
    /// global undo service. Since the object cannot be relied on to properly update 
    /// the undo manager, any units submitted by other objects are also suspect, 
    /// because their units may rely on the state of the non-compliant object. 
    /// Attempting to undo a compliant object's units may not be successful, because 
    /// the state in the non-compliant object will not match.
    /// </p>
    /// <p>
    /// To detect objects that do not support multi-level undo, check for the 
    /// OLEMISC_SUPPORTSMULTILEVELUNDO value. An object that can participate in the 
    /// global undo service sets this value.
    /// </p>
    /// <p>
    /// When an object without this value is added to a user-visible undo context, 
    /// the best practice is to disable the undo user interface for this context. 
    /// Alternatively, a dialog could be presented to the user, asking them whether 
    /// to attempt to provide partial undo support, working around the non-compliance 
    /// of the new object.
    /// </p>
    /// <p>
    /// In addition, non-compliant objects may be added to nested containers. In 
    /// this case, the nested container needs to notify the undo manager that undo 
    /// can no longer be safely supported by calling IOleUndoManager::Enable with FALSE.
    /// </p>
    /// </remarks>
    class OleUndoManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( OleUndoManager, Unknown, IOleUndoManager, IUnknown )

        void Open( __RPC__in_opt IOleParentUndoUnit* parentUndoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Open( parentUndoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void Close( __RPC__in_opt IOleParentUndoUnit * parentUndoUnit, bool commit) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Close( parentUndoUnit, commit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void Add( __RPC__in_opt IOleUndoUnit * undoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Add( undoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void GetOpenParentState( __RPC__out DWORD *state) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetOpenParentState( state );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void DiscardFrom( __RPC__in_opt IOleUndoUnit * undoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DiscardFrom( undoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void UndoTo( __RPC__in_opt IOleUndoUnit * undoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UndoTo( undoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void RedoTo( __RPC__in_opt IOleUndoUnit * undoUnit ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RedoTo( undoUnit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void EnumUndoable( __RPC__deref_out_opt IEnumOleUndoUnits ** enumOleUndoUnits ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EnumUndoable( enumOleUndoUnits );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void EnumRedoable( __RPC__deref_out_opt IEnumOleUndoUnits ** enumOleUndoUnits ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EnumRedoable( enumOleUndoUnits );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void GetLastUndoDescription( __RPC__deref_out_opt BSTR * description ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLastUndoDescription( description );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void GetLastRedoDescription(  __RPC__deref_out_opt BSTR * description ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLastRedoDescription( description );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void Enable( bool enable ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Enable( enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
    };


    /// <summary>
    /// <p>
    /// Enables an object to remain inactive most of the time, yet still 
    /// participate in interaction with the mouse, including drag and drop.
    /// </p>
    /// <p>
    /// Objects can be active( in - place or UI active ) or they can be 
    /// inactive( loaded or running ).An active object creates a window 
    /// and can receive Windows mouse and keyboard messages. An inactive 
    /// object can render itself and provide a representation of its data 
    /// in a given format.While they provide more functionality, active 
    /// objects also consume more resources than inactive objects. Typically, 
    /// they are larger and slower than inactive objects. Thus, keeping 
    /// an object inactive can provide performance improvements.
    /// </p>
    /// <p>
    /// However, an object, such as a control, needs to be able to control 
    /// the mouse pointer, fire mouse events, and act as a drop target so 
    /// it can participate in the user interface of its container application.
    /// </p>
    /// </summary>
    class PointerInactive : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PointerInactive, Unknown, IPointerInactive, IUnknown )

        void GetActivationPolicy( __RPC__out DWORD* policy ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetActivationPolicy( policy );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void OnInactiveMouseMove(  __RPC__in LPCRECT boundsRect, LONG x, LONG y, DWORD keyState ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnInactiveMouseMove( boundsRect, x, y, keyState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void OnInactiveSetCursor(  __RPC__in LPCRECT boundsRect, LONG x, LONG y, DWORD mouseMsg, BOOL setAlways) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnInactiveSetCursor( boundsRect, x, y, mouseMsg, setAlways );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
    };


    /// <summary>
    /// <p>
    /// Provides a simple way to support communication between an 
    /// object and its site in the container.
    /// </p>
    /// <p>
    /// Often an object needs to communicate directly with a container site 
    /// object and, in effect, manage the site object itself. Outside of 
    /// IOleObject::SetClientSite, there is no generic means through which an 
    /// object becomes aware of its site. IObjectWithSite provides simple objects 
    /// with a simple siting mechanism (lighter than IOleObject) This interface 
    /// should only be used when IOleObject is not already in use.
    /// </p>
    /// <p>
    /// Through IObjectWithSite, a container can pass the IUnknown pointer of 
    /// its site to the object through IObjectWithSite::SetSite. Callers can 
    /// also retrieve the latest site passed to SetSite through IObjectWithSite::GetSite. 
    /// This latter method is included as a hooking mechanism, allowing a third party 
    /// to intercept calls from the object to the site.
    /// </p>
    /// </summary>
    class ObjectWithSite : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ObjectWithSite, Unknown, IObjectWithSite, IUnknown )

        void SetSite( __RPC__in_opt IUnknown* site ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSite( site );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSite( __RPC__in REFIID riid, __RPC__deref_out_opt void** site ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSite( riid, site );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Retrieves the information in the property pages 
    /// offered by an object.
    /// </summary>
    class PerPropertyBrowsing : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PerPropertyBrowsing, Unknown, IPerPropertyBrowsing, IUnknown )

        void GetDisplayString( DISPID dispID, __RPC__deref_out_opt BSTR* displayString ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDisplayString( dispID, displayString );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void MapPropertyToPage( DISPID dispID, __RPC__out CLSID* pageId ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->MapPropertyToPage( dispID, pageId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPredefinedStrings( DISPID dispID, __RPC__out CALPOLESTR* caStringsOut, __RPC__out CADWORD* caCookiesOut ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPredefinedStrings( dispID, caStringsOut, caCookiesOut );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPredefinedValue( DISPID dispID, DWORD cookie, __RPC__out VARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPredefinedValue( dispID, cookie, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class PropertyBag : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PropertyBag, Unknown, IPropertyBag, IUnknown )

        void Read(  LPCOLESTR pszPropName, VARIANT *pVar, IErrorLog *pErrorLog) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Read( pszPropName, pVar, pErrorLog );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        void Write( __RPC__in LPCOLESTR pszPropName, __RPC__in VARIANT *pVar) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Write( pszPropName, pVar );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Provides an object with a property bag in which the object can 
    /// save its properties persistently.
    /// </summary>
    class PropertyBag2 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PropertyBag2, Unknown, IPropertyBag2, IUnknown )

        void Read( ULONG cProperties, PROPBAG2* pPropBag, IErrorLog* pErrLog, VARIANT* pvarValue, HRESULT* phrError ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Read( cProperties, pPropBag, pErrLog, pvarValue, phrError );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Write( ULONG cProperties, PROPBAG2* pPropBag, VARIANT* pvarValue ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Write( cProperties, pPropBag, pvarValue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CountProperties( __RPC__out ULONG* pcProperties ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CountProperties( pcProperties );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPropertyInfo( ULONG iProperty, ULONG cProperties, PROPBAG2* pPropBag, ULONG* pcProperties ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyInfo( iProperty, cProperties, pPropBag, pcProperties );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void LoadObject( LPCOLESTR pstrName, DWORD dwHint, __RPC__in_opt IUnknown* pUnkObject, __RPC__in_opt IErrorLog* pErrLog ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->LoadObject( pstrName, dwHint, pUnkObject, pErrLog );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Works with the IPropertyBag2 interface and the IErrorlog 
    /// interface to define an individual property-based persistence mechanism.
    /// </summary>
    class PersistPropertyBag2 : public Persist
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( PersistPropertyBag2, Persist, IPersistPropertyBag2, IPersist )

        void InitNew( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InitNew(  );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Load( __RPC__in_opt IPropertyBag2* pPropBag, __RPC__in_opt IErrorLog* pErrLog ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Load( pPropBag, pErrLog );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Save( __RPC__in_opt IPropertyBag2* propBag, bool clearDirty, bool saveAllProperties ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Save( propBag, clearDirty, saveAllProperties );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsDirty( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsDirty( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }

    };


    /// <summary>
    /// This interface is derived from IAdviseSink to provide extensions 
    /// for notifying the sink of changes in an object's view status.
    /// </summary>
    class AdviseSinkEx : public AdviseSink
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( AdviseSinkEx, AdviseSink, IAdviseSinkEx, IAdviseSink )

        void STDMETHODCALLTYPE OnViewStatusChange( DWORD viewStatus ) const
        {
            auto pInterface = GetInterface( );
            pInterface->OnViewStatusChange( viewStatus );
        }
    };

    /// <summary>
    /// Enables controls and containers to avoid performance bottlenecks on 
    /// loading controls. It combines the load-time or initialization-time 
    /// handshaking between the control and its container into a single call.
    /// </summary>
    class QuickActivate : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( QuickActivate, Unknown, IQuickActivate, IUnknown )

        void QuickActivate_( QACONTAINER* qaContainer, QACONTROL* qaControl ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QuickActivate( qaContainer, qaControl );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetContentExtent( __RPC__in LPSIZEL size ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetContentExtent( size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetContentExtent( __RPC__out LPSIZEL size ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetContentExtent( size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Provides a generic access mechanism to locate a GUID-identified service.
    /// </summary>
    /// <remarks>
    /// <p>
    /// The IServiceProvider interface is a generic access mechanism to locate a 
    /// GUID-identified service that is provided through a control or any other 
    /// object that the service can communicate with. For example, an embedded 
    /// object (such as an OLE control) typically communicates only with its 
    /// associated client site object in the container through the IOleClientSite 
    /// interface that is supplied by using IOleObject::SetClientSite. The embedded 
    /// object must ask the client site for some other service that the container 
    /// supports when that service might not be implemented in the client site.
    /// </p>
    /// <p>
    /// The client site must provide a means by which the control that is managed 
    /// by the site can access the service when necessary. For example, the 
    /// IOleInPlaceSite::GetWindowContext function can be used by an in-place 
    /// object or control to access interface pointers for the document object 
    /// that contains the site and the frame object that contains the document. 
    /// Because these interface pointers exist on separate objects, the control 
    /// cannot call the site's QueryInterface to obtain those pointers. Instead, 
    /// use the IServiceProvider interface.
    /// </p>
    /// </remarks>
    class ServiceProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ServiceProvider, Unknown, IServiceProvider, IUnknown )

        /// <summary>
        /// Acts as the factory method for any services exposed through an 
        /// implementation of IServiceProvider.
        /// </summary>
        /// <param name="guidService">
        /// The unique identifier of the service.
        /// </param>
        /// <param name="riid">
        /// The unique identifier of the interface that the caller wants to 
        /// receive for the service.
        /// </param>
        /// <param name="service">
        /// The address of the caller-allocated variable to receive the interface 
        /// pointer of the service on successful return from this function. The 
        /// caller becomes responsible for calling Release through this interface 
        /// pointer when the service is no longer required.
        /// </param>
        /// <returns>
        /// true if the implementation of IServiceProvider could provide the 
        /// requested interface for the requested service, otherwise false.
        /// </returns>
        bool QueryService( _In_ REFGUID guidService, _In_ REFIID riid, _Outptr_ void** service ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryService( guidService, riid, service );
            return hr == S_OK;
        }

        template <typename T>
        requires std::is_base_of_v<IUnknown,T>
        bool QueryService( _In_ REFGUID guidService, _Outptr_ T** pp )
        {
            return QueryService( guidService, __uuidof( T ), reinterpret_cast<void**>( pp ) );
        }

        template <typename T>
            requires std::is_base_of_v<Unknown, T>
        T QueryService( _In_ REFGUID guidService )
        {
            using ItfT = typename T::InterfaceType;
            ItfT* ptr = nullptr;
            if ( QueryService( guidService, __uuidof( ItfT ), reinterpret_cast<void**>( &ptr ) ) )
            {
                return T( ptr );
            }
            else
            {
                return T( );
            }
        }

        template <typename T>
            requires std::is_base_of_v<IUnknown, T>
        UnknownPtr<T> QueryService( _In_ REFGUID guidService )
        {
            T* ptr = nullptr;
            if ( QueryService( guidService, __uuidof( T ), reinterpret_cast<void**>( &ptr ) ) )
            {
                return UnknownPtr<T>( ptr );
            }
            else
            {
                return UnknownPtr<T>( );
            }
        }

    };






}


#endif
