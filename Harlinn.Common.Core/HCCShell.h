#pragma once
#ifndef __HCCSHELL_H__
#define __HCCSHELL_H__
/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HCCPropSys.h>

namespace Harlinn::Common::Core
{
    struct FilterSpecification
    {
        WideString name;
        WideString specification;
    };


    class ShellItem : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ShellItem, Unknown, IShellItem2, IUnknown )

        template <typename T>
        T BindToHandler( IBindCtx* pbc, REFGUID bhid )
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result = nullptr;
            auto hr = pInterface->BindToHandler( pbc, bhid, __uuidof( T::InterfaceType ), &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        ShellItem GetParent( )
        {
            auto pInterface = GetInterface( );
            IShellItem* shellItem = nullptr;
            auto hr = pInterface->GetParent( &shellItem );
            if ( FAILED( hr ) )
            {
                //CheckHRESULT(hr);
                return ShellItem( ); // 
            }
            IShellItem2* result = nullptr;
            hr = shellItem->QueryInterface( &result );
            shellItem->Release( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }

            return ShellItem( result );
        }

        WideString GetDisplayName( SIGDN sigdnName = SIGDN_NORMALDISPLAY )
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetDisplayName( sigdnName, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            WideString s( result );
            CoTaskMemFree( result );
            return s;
        }

        SFGAOF GetAttributes( SFGAOF sfgaoMask )
        {
            auto pInterface = GetInterface( );
            SFGAOF result;
            auto hr = pInterface->GetAttributes( sfgaoMask, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        int Compare( IShellItem* psi, SICHINTF hint = SICHINT_DISPLAY )
        {
            auto pInterface = GetInterface( );
            int result;
            auto hr = pInterface->Compare( psi, hint, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }


        PropertyStore GetPropertyStore( GETPROPERTYSTOREFLAGS flags = GPS_DEFAULT )
        {
            auto pInterface = GetInterface( );
            IPropertyStore* result = nullptr;
            auto hr = pInterface->GetPropertyStore( flags, __uuidof( IPropertyStore ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return PropertyStore( result );
        }

        PropertyStore GetPropertyStoreWithCreateObject( IUnknown* punkCreateObject, GETPROPERTYSTOREFLAGS flags = GPS_DEFAULT )
        {
            auto pInterface = GetInterface( );
            IPropertyStore* result = nullptr;
            auto hr = pInterface->GetPropertyStoreWithCreateObject( flags, punkCreateObject, __uuidof( IPropertyStore ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return PropertyStore( result );
        }
        PropertyStore GetPropertyStoreForKeys( const PROPERTYKEY* rgKeys, UINT cKeys, GETPROPERTYSTOREFLAGS flags = GPS_DEFAULT )
        {
            auto pInterface = GetInterface( );
            IPropertyStore* result = nullptr;
            auto hr = pInterface->GetPropertyStoreForKeys( rgKeys, cKeys, flags, __uuidof( IPropertyStore ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return PropertyStore( result );
        }
        PropertyDescriptionList GetPropertyDescriptionList( REFPROPERTYKEY keyType )
        {
            auto pInterface = GetInterface( );
            IPropertyDescriptionList* result = nullptr;
            auto hr = pInterface->GetPropertyDescriptionList( keyType, __uuidof( IPropertyDescriptionList ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return PropertyDescriptionList( result );
        }

        ShellItem& Update( IBindCtx* pbc )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Update( pbc );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }
        PropertyVariant GetProperty( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            PropertyVariant result;
            auto hr = pInterface->GetProperty( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        CLSID GetCLSID( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            CLSID result = { 0, };
            auto hr = pInterface->GetCLSID( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        DateTime GetFileTime( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            long long ft = { 0, };
            auto hr = pInterface->GetFileTime( key, (FILETIME*)&ft );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            DateTime result = DateTime::FromFileTime( ft );
            return result;
        }
        int GetInt32( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            int result = 0;
            auto hr = pInterface->GetInt32( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        WideString GetString( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            LPWSTR result = nullptr;
            auto hr = pInterface->GetString( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            WideString s( result );
            CoTaskMemFree( result );
            return s;
        }
        ULONG GetUInt32( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->GetUInt32( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        ULONGLONG GetUInt64( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            ULONGLONG result = 0;
            auto hr = pInterface->GetUInt64( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        bool GetBool( REFPROPERTYKEY key )
        {
            auto pInterface = GetInterface( );
            BOOL result = 0;
            auto hr = pInterface->GetBool( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result != FALSE;
        }
    };


    class EnumShellItems : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumShellItems, Unknown, IEnumShellItems, IUnknown )

        bool Next( ShellItem& theResult )
        {
            auto pInterface = GetInterface( );
            IShellItem* pElement = nullptr;
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &pElement, &actual );
            if ( actual )
            {
                IShellItem2* pShellItem = nullptr;
                hr = pElement->QueryInterface( &pShellItem );
                pElement->Release( );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
                theResult.ResetPtr( pShellItem );
                return true;
            }
            return false;
        }

        bool Next( ULONG requestedNumberOfElements, std::vector<Unknown>& result )
        {
            auto pInterface = GetInterface( );
            IShellItem** pElements = (IShellItem**)alloca( requestedNumberOfElements * sizeof( IShellItem* ) );
            memset( pElements, 0, requestedNumberOfElements * sizeof( IShellItem* ) );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, pElements, &actual );
            if ( actual )
            {
                result.clear( );
                for ( ULONG i = 0; i < actual; i++ )
                {
                    IShellItem* pElement = pElements[i];
                    IShellItem2* pShellItem = nullptr;
                    hr = pElement->QueryInterface( &pShellItem );
                    pElement->Release( );
                    if ( FAILED( hr ) )
                    {
                        for ( ULONG ii = i + 1; ii < actual; ii++ )
                        {
                            pElements[ii]->Release( );
                        }
                        CheckHRESULT( hr );
                    }
                    result.push_back( ShellItem( pShellItem ) );
                }
                return true;
            }
            return false;
        }
        EnumShellItems& Skip( ULONG numberOfElements )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        EnumShellItems& Reset( )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return *this;
        }

        EnumShellItems Clone( )
        {
            auto pInterface = GetInterface( );
            IEnumShellItems* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return EnumShellItems( pClone );
        }

    };


    class ShellItemArray : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ShellItemArray, Unknown, IShellItemArray, IUnknown )

        template <typename T>
        T BindToHandler( IBindCtx* pbc, REFGUID bhid )
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result = nullptr;
            auto hr = pInterface->BindToHandler( pbc, bhid, __uuidof( T::InterfaceType ), &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyStore GetPropertyStore( GETPROPERTYSTOREFLAGS flags = GPS_DEFAULT )
        {
            auto pInterface = GetInterface( );
            IPropertyStore* result = nullptr;
            auto hr = pInterface->GetPropertyStore( flags, __uuidof( IPropertyStore ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return PropertyStore( result );
        }

        PropertyDescriptionList GetPropertyDescriptionList( REFPROPERTYKEY keyType )
        {
            auto pInterface = GetInterface( );
            IPropertyDescriptionList* result = nullptr;
            auto hr = pInterface->GetPropertyDescriptionList( keyType, __uuidof( IPropertyDescriptionList ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return PropertyDescriptionList( result );
        }


        SFGAOF GetAttributes( SIATTRIBFLAGS AttribFlags, SFGAOF sfgaoMask )
        {
            auto pInterface = GetInterface( );
            SFGAOF result;
            auto hr = pInterface->GetAttributes( AttribFlags, sfgaoMask, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        DWORD GetCount( )
        {
            auto pInterface = GetInterface( );
            DWORD result;
            auto hr = pInterface->GetCount( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        ShellItem GetItemAt( DWORD dwIndex )
        {
            auto pInterface = GetInterface( );
            IShellItem* pElement = nullptr;
            auto hr = pInterface->GetItemAt( dwIndex, &pElement );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }

            IShellItem2* pShellItem = nullptr;
            hr = pElement->QueryInterface( &pShellItem );
            pElement->Release( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ShellItem( pShellItem );
        }

        EnumShellItems EnumItems( )
        {
            auto pInterface = GetInterface( );
            IEnumShellItems* pEnumItems = nullptr;
            auto hr = pInterface->EnumItems( &pEnumItems );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return EnumShellItems( pEnumItems );
        }

    };

}


#endif
