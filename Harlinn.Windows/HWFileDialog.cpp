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

#include "pch.h"
#include <HWFileDialog.h>
#include <HWControl.h>

namespace Harlinn::Windows
{
// ----------------------------------------------------------------------
// ModalWindow
// ----------------------------------------------------------------------
    bool ModalWindow::Show( HWND owner )
    {
        auto pInterface = GetInterface( );
        auto hr = pInterface->Show( owner );
        if ( hr == S_OK )
        {
            return true;
        }
        else if ( hr != HRESULT_FROM_WIN32( ERROR_CANCELLED ) )
        {
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        return false;
    }


    bool ModalWindow::Show( const Control& owner )
    {
        return this->Show( owner.GetHandle( ) );
    }

    // ----------------------------------------------------------------------
    // FileDialogEvents
    // ----------------------------------------------------------------------

    FileDialogEventsImplementation::FileDialogEventsImplementation( FileDialog* theFileDialog )
        : fileDialog( theFileDialog )
    {
    }

    HRESULT STDMETHODCALLTYPE FileDialogEventsImplementation::OnFileOk( IFileDialog* pfd )
    {
        if ( fileDialog )
        {
            bool accept = true;
            fileDialog->DoOnFileOk( accept );
            return accept ? S_OK : S_FALSE;
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE FileDialogEventsImplementation::OnFolderChanging( IFileDialog* pfd, IShellItem* psiFolder )
    {
        if ( fileDialog )
        {
            IShellItem2* pShellItem2 = nullptr;
            auto hr = psiFolder->QueryInterface( &pShellItem2 );
            if ( FAILED( hr ) )
            {
                return hr;
            }
            ShellItem shellItem( pShellItem2 );
            bool accept = true;
            fileDialog->DoOnFolderChanging( shellItem, accept );
            return accept ? S_OK : S_FALSE;
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE FileDialogEventsImplementation::OnFolderChange( IFileDialog* pfd )
    {
        if ( fileDialog )
        {
            fileDialog->DoOnFolderChange( );
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE FileDialogEventsImplementation::OnSelectionChange( IFileDialog* pfd )
    {
        if ( fileDialog )
        {
            fileDialog->DoOnSelectionChange( );
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE FileDialogEventsImplementation::OnShareViolation( IFileDialog* pfd, IShellItem* psi, FDE_SHAREVIOLATION_RESPONSE* pResponse )
    {
        if ( fileDialog )
        {
            IShellItem2* pShellItem2 = nullptr;
            auto hr = psi->QueryInterface( &pShellItem2 );
            if ( FAILED( hr ) )
            {
                return hr;
            }
            ShellItem shellItem( pShellItem2 );

            FDE_SHAREVIOLATION_RESPONSE response = FDESVR_DEFAULT;

            fileDialog->DoOnShareViolation( shellItem, response );
            if ( pResponse )
            {
                *pResponse = response;
            }
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE FileDialogEventsImplementation::OnTypeChange( IFileDialog* pfd )
    {
        if ( fileDialog )
        {
            fileDialog->DoOnTypeChange( );
        }
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE FileDialogEventsImplementation::OnOverwrite( IFileDialog* pfd, IShellItem* psi, FDE_OVERWRITE_RESPONSE* pResponse )
    {
        if ( fileDialog )
        {
            IShellItem2* pShellItem2 = nullptr;
            auto hr = psi->QueryInterface( &pShellItem2 );
            if ( FAILED( hr ) )
            {
                return hr;
            }
            ShellItem shellItem( pShellItem2 );

            FDE_OVERWRITE_RESPONSE response = FDEOR_DEFAULT;

            fileDialog->DoOnOverwrite( shellItem, response );
            if ( pResponse )
            {
                *pResponse = response;
            }
        }
        return S_OK;
    }

    // ----------------------------------------------------------------------
    // FileDialog
    // ----------------------------------------------------------------------

    bool FileDialog::Show( HWND owner )
    {
        bool result = false;
        FileDialogEvents fileDialogEvents( new FileDialogEventsImplementation( this ) );
        DWORD cookie = Advise( fileDialogEvents );
        try
        {
            result = Base::Show( owner );
            Unadvise( cookie );
        }
        catch ( ... )
        {
            Unadvise( cookie );
            throw;
        }
        return result;
    }

    void FileDialog::DoOnFileOk( bool& accept )
    {
        OnFileOk( this, accept );
    }

    void FileDialog::DoOnFolderChanging( const ShellItem& newFolder, bool& allow )
    {
        OnFolderChanging( this, newFolder, allow );
    }

    void FileDialog::DoOnFolderChange( )
    {
        OnFolderChange( this );
    }

    void FileDialog::DoOnSelectionChange( )
    {
        OnSelectionChange( this );
    }

    void FileDialog::DoOnShareViolation( const ShellItem& shellItem, FDE_SHAREVIOLATION_RESPONSE& response )
    {
        OnShareViolation( this, shellItem, response );
    }

    void FileDialog::DoOnTypeChange( )
    {
        OnTypeChange( this );
    }

    void FileDialog::DoOnOverwrite( const ShellItem& shellItem, FDE_OVERWRITE_RESPONSE& response )
    {
        OnOverwrite( this, shellItem, response );
    }


    // ----------------------------------------------------------------------
    // FileOpenDialog
    // ----------------------------------------------------------------------
    std::shared_ptr<FileOpenDialog> FileOpenDialog::Create( )
    {
        IFileOpenDialog* pDialog = nullptr;
        auto hr = CoCreateInstance( CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, __uuidof( IFileOpenDialog ), (void**)&pDialog );
        if ( FAILED( hr ) )
        {
            CheckHRESULT( hr );
        }

        auto result = std::make_shared<FileOpenDialog>( pDialog );
        return result;

    }

    // ----------------------------------------------------------------------
    // FileSaveDialog
    // ----------------------------------------------------------------------
    std::shared_ptr<FileSaveDialog> FileSaveDialog::Create( )
    {
        IFileSaveDialog* pDialog = nullptr;
        auto hr = CoCreateInstance( CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, __uuidof( IFileSaveDialog ), (void**)&pDialog );
        if ( FAILED( hr ) )
        {
            CheckHRESULT( hr );
        }

        auto result = std::make_shared<FileSaveDialog>( pDialog );
        return result;


    }
}