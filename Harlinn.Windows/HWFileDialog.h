#pragma once
#ifndef __HWFILEDIALOG_H__
#define __HWFILEDIALOG_H__

#include <HWDef.h>
#include <HCCCOM.h>
#include <HCCException.h>
#include <HCCVariant.h>
#include <HCCObj.h>
#include <HCCShell.h>

namespace Harlinn::Windows
{
    class Control;
    class ModalWindow : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ModalWindow, Unknown, IModalWindow, IUnknown )

        HW_EXPORT virtual bool Show( HWND theOwner );
        HW_EXPORT bool Show( const Control& theOwner );

    };


    class FileDialogEvents : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( FileDialogEvents, Unknown, IFileDialogEvents, IUnknown )

            HW_EXPORT FileDialogEvents& OnFileOk( IFileDialog* pfd )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnFileOk( pfd );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }


        HW_EXPORT FileDialogEvents& OnFolderChanging( IFileDialog* pfd, IShellItem* psiFolder )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnFolderChanging( pfd, psiFolder );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        HW_EXPORT FileDialogEvents& OnFolderChange( IFileDialog* pfd )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnFolderChange( pfd );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        HW_EXPORT FileDialogEvents& OnSelectionChange( IFileDialog* pfd )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnSelectionChange( pfd );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        HW_EXPORT FileDialogEvents& OnShareViolation( IFileDialog* pfd, IShellItem* psi, FDE_SHAREVIOLATION_RESPONSE* pResponse )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnShareViolation( pfd, psi, pResponse );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        HW_EXPORT FileDialogEvents& OnTypeChange( IFileDialog* pfd )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnTypeChange( pfd );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        HW_EXPORT FileDialogEvents& OnOverwrite( IFileDialog* pfd, IShellItem* psi, FDE_OVERWRITE_RESPONSE* pResponse )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OnOverwrite( pfd, psi, pResponse );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

    };





    class FileDialog;
    class FileDialogEventsImplementation : public IUnknownImplementation<FileDialogEventsImplementation,IFileDialogEvents>
    {
        FileDialog* fileDialog;
    public:
        typedef IUnknownImplementation<FileDialogEventsImplementation, IFileDialogEvents> Base;

        HW_EXPORT FileDialogEventsImplementation( FileDialog* theFileDialog );

        HW_EXPORT virtual HRESULT STDMETHODCALLTYPE OnFileOk( IFileDialog* pfd );

        HW_EXPORT virtual HRESULT STDMETHODCALLTYPE OnFolderChanging( IFileDialog* pfd, IShellItem* psiFolder );

        HW_EXPORT virtual HRESULT STDMETHODCALLTYPE OnFolderChange( IFileDialog* pfd );

        HW_EXPORT virtual HRESULT STDMETHODCALLTYPE OnSelectionChange( IFileDialog* pfd );

        HW_EXPORT virtual HRESULT STDMETHODCALLTYPE OnShareViolation( IFileDialog* pfd, IShellItem* psi, FDE_SHAREVIOLATION_RESPONSE* pResponse );

        HW_EXPORT virtual HRESULT STDMETHODCALLTYPE OnTypeChange( IFileDialog* pfd );

        HW_EXPORT virtual HRESULT STDMETHODCALLTYPE OnOverwrite( IFileDialog* pfd, IShellItem* psi, FDE_OVERWRITE_RESPONSE* pResponse );
    };

    class FileDialog : public ModalWindow
    {
        friend class FileDialogEventsImplementation;
    public:
        typedef ModalWindow Base;
        HCC_COM_STANDARD_METHODS_IMPL( FileDialog, ModalWindow, IFileDialog, IModalWindow )

        HW_EXPORT virtual bool Show( HWND owner = 0 );


        FileDialog& SetFileTypes( UINT cFileTypes, const COMDLG_FILTERSPEC* rgFilterSpec )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFileTypes( cFileTypes, rgFilterSpec );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& SetFileTypeIndex( UINT iFileType )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFileTypeIndex( iFileType );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        UINT GetFileTypeIndex( )
        {
            auto pInterface = GetInterface( );
            UINT result = 0;
            auto hr = pInterface->GetFileTypeIndex( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        DWORD Advise( IFileDialogEvents* pfde )
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->Advise( pfde, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        FileDialog& Unadvise( DWORD dwCookie )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unadvise( dwCookie );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& SetOptions( FILEOPENDIALOGOPTIONS fos )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetOptions( fos );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FILEOPENDIALOGOPTIONS GetOptions( )
        {
            auto pInterface = GetInterface( );
            FILEOPENDIALOGOPTIONS result = 0;
            auto hr = pInterface->GetOptions( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        FileDialog& SetDefaultFolder( IShellItem* psi )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetDefaultFolder( psi );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& SetFolder( IShellItem* psi )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFolder( psi );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        ShellItem GetFolder( )
        {
            auto pInterface = GetInterface( );
            IShellItem* pShellItem = nullptr;
            auto hr = pInterface->GetFolder( &pShellItem );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            IShellItem2* result = nullptr;
            hr = pShellItem->QueryInterface( &result );
            pShellItem->Release( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ShellItem( result );
        }

        ShellItem GetCurrentSelection( )
        {
            auto pInterface = GetInterface( );
            IShellItem* pShellItem = nullptr;
            auto hr = pInterface->GetCurrentSelection( &pShellItem );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            IShellItem2* result = nullptr;
            hr = pShellItem->QueryInterface( &result );
            pShellItem->Release( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ShellItem( result );
        }

        FileDialog& SetFileName( LPCWSTR pszName )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFileName( pszName );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }


        std::wstring GetFileName( )
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetFileName( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            std::wstring s( result );
            CoTaskMemFree( result );
            return s;
        }
        FileDialog& SetTitle( LPCWSTR pszTitle )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetTitle( pszTitle );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& SetOkButtonLabel( LPCWSTR pszText )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetOkButtonLabel( pszText );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& SetFileNameLabel( LPCWSTR pszLabel )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFileNameLabel( pszLabel );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        ShellItem GetResult( )
        {
            auto pInterface = GetInterface( );
            IShellItem* pShellItem = nullptr;
            auto hr = pInterface->GetResult( &pShellItem );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            IShellItem2* result = nullptr;
            hr = pShellItem->QueryInterface( &result );
            pShellItem->Release( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ShellItem( result );
        }

        FileDialog& AddPlace( IShellItem* psi, FDAP fdap = FDAP_BOTTOM )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddPlace( psi, fdap );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& SetDefaultExtension( LPCWSTR pszDefaultExtension )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetDefaultExtension( pszDefaultExtension );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& Close( HRESULT hr )
        {
            auto pInterface = GetInterface( );
            auto hres = pInterface->Close( hr );
            if ( FAILED( hres ) )
            {
                CheckHRESULT( hres );
            }
            return *this;
        }

        FileDialog& SetClientGuid( REFGUID guid )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetClientGuid( guid );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& ClearClientData( )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ClearClientData( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileDialog& SetFilter( IShellItemFilter* pFilter )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFilter( pFilter );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }


        boost::signals2::signal<void( FileDialog* sender, bool& accept ) > OnFileOk;

        boost::signals2::signal<void( FileDialog* sender, const ShellItem& newFolder, bool& allow ) > OnFolderChanging;

        boost::signals2::signal<void( FileDialog* sender ) > OnFolderChange;

        boost::signals2::signal<void( FileDialog* sender ) > OnSelectionChange;

        boost::signals2::signal<void( FileDialog* sender, const ShellItem& shellItem, FDE_SHAREVIOLATION_RESPONSE& response ) > OnShareViolation;

        boost::signals2::signal<void( FileDialog* sender ) > OnTypeChange;

        boost::signals2::signal<void( FileDialog* sender, const ShellItem& shellItem, FDE_OVERWRITE_RESPONSE& response ) > OnOverwrite;

    protected:
        HW_EXPORT virtual void DoOnFileOk( bool& accept );

        HW_EXPORT virtual void DoOnFolderChanging( const ShellItem& newFolder, bool& allow );

        HW_EXPORT virtual void DoOnFolderChange( );

        HW_EXPORT virtual void DoOnSelectionChange( );

        HW_EXPORT virtual void DoOnShareViolation( const ShellItem& shellItem, FDE_SHAREVIOLATION_RESPONSE& response );

        HW_EXPORT virtual void DoOnTypeChange( );

        HW_EXPORT virtual void DoOnOverwrite( const ShellItem& shellItem, FDE_OVERWRITE_RESPONSE& response );

    };


    class FileOpenDialog : public FileDialog
    {
    public:
        typedef FileDialog Base;
        HCC_COM_STANDARD_METHODS_IMPL( FileOpenDialog, FileDialog, IFileOpenDialog, IFileDialog )

            HW_EXPORT static std::shared_ptr<FileOpenDialog> Create( );

        ShellItemArray GetResults( )
        {
            auto pInterface = GetInterface( );
            IShellItemArray* pResult = nullptr;
            auto hr = pInterface->GetResults( &pResult );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ShellItemArray( pResult );
        }

        ShellItemArray GetSelectedItems( )
        {
            auto pInterface = GetInterface( );
            IShellItemArray* pResult = nullptr;
            auto hr = pInterface->GetSelectedItems( &pResult );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ShellItemArray( pResult );
        }


    };


    class FileSaveDialog : public FileDialog
    {
    public:
        typedef FileDialog Base;
        HCC_COM_STANDARD_METHODS_IMPL( FileSaveDialog, FileDialog, IFileSaveDialog, IFileDialog )

            HW_EXPORT static std::shared_ptr<FileSaveDialog> Create( );

        FileSaveDialog& SetSaveAsItem( IShellItem* psi )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSaveAsItem( psi );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileSaveDialog& SetProperties( IPropertyStore* pStore )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetProperties( pStore );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        FileSaveDialog& SetCollectedProperties( IPropertyDescriptionList* pList, bool appendDefault )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetCollectedProperties( pList, appendDefault );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        PropertyStore GetProperties( )
        {
            auto pInterface = GetInterface( );
            IPropertyStore* pResult = nullptr;
            auto hr = pInterface->GetProperties( &pResult );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return PropertyStore( pResult );
        }

        FileSaveDialog& ApplyProperties( IShellItem* psi, IPropertyStore* pStore, HWND hwnd, IFileOperationProgressSink* pSink )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ApplyProperties( psi, pStore, hwnd, pSink );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

    };
}

#endif
