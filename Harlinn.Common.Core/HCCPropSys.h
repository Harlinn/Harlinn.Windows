#pragma once
#ifndef __HCCPROPSYS_H__
#define __HCCPROPSYS_H__

#include <HCCCOM.h>
#include <HCCException.h>
#include <HCCVariant.h>
#include <HCCObj.h>

namespace Harlinn::Common::Core
{
    class InitializeWithFile : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( InitializeWithFile, Unknown, IInitializeWithFile, IUnknown )

        void Initialize( LPCWSTR pszFilePath, DWORD grfMode ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Initialize( pszFilePath, grfMode );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

    };

    class InitializeWithStream : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( InitializeWithStream, Unknown, IInitializeWithStream, IUnknown )

        void Initialize( IStream* pstream, DWORD grfMode ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Initialize( pstream, grfMode );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };

    class PropertyStore : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyStore, Unknown, IPropertyStore, IUnknown )
    public:
        
        /// <summary>
        /// Creates an in-memory property store.
        /// </summary>
        /// <returns>
        /// The newly created PropertyStore
        /// </returns>
        /// <remarks>
        /// <p>
        /// This function creates an in-memory property store object that implements 
        /// IPropertyStore, INamedPropertyStore, IPropertyStoreCache, IPersistStream, 
        /// IPropertyBag, and IPersistSerializedPropStorage.
        /// </p>
        /// <p>
        /// The memory property store does not correspond to a file and is designed for 
        /// use as a cache. Commit is a no-op, and the data stored in the object persists 
        /// only as long as the object does.
        /// </p>
        /// <p>
        /// The memory property store is thread safe. It aggregates the free-threaded 
        /// marshaller and uses critical sections to protect its data members.
        /// </p>
        /// </remarks>
        static PropertyStore Create()
        {
            IPropertyStore* itf = nullptr;
            auto hr = PSCreateMemoryPropertyStore(__uuidof(IPropertyStore), (void**)&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return PropertyStore(itf);
        }


        DWORD GetCount( ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->GetCount( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void GetAt( DWORD iProp, PROPERTYKEY* thekey ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAt( iProp, thekey );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        void GetAt( DWORD iProp, PROPERTYKEY& thekey ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAt( iProp, &thekey );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        PROPERTYKEY GetAt( DWORD iProp ) const
        {
            auto pInterface = GetInterface( );
            PROPERTYKEY result = { 0, };
            auto hr = pInterface->GetAt( iProp, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        PropertyVariant GetValue( REFPROPERTYKEY key ) const
        {
            auto pInterface = GetInterface( );
            PropertyVariant result;
            auto hr = pInterface->GetValue( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        PropertyVariant GetValue( DWORD iProp ) const
        {
            auto pInterface = GetInterface( );
            REFPROPERTYKEY key = GetAt( iProp );
            PropertyVariant result;
            auto hr = pInterface->GetValue( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void SetValue( REFPROPERTYKEY key, REFPROPVARIANT propvar ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetValue( key, propvar );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        void SetValue( REFPROPERTYKEY key, const PropertyVariant& propvar ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetValue( key, propvar );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Commit( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Commit( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    class NamedPropertyStore : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( NamedPropertyStore, Unknown, INamedPropertyStore, IUnknown )

        PropertyVariant GetNamedValue( LPCWSTR pszName ) const
        {
            auto pInterface = GetInterface( );
            PropertyVariant result;
            auto hr = pInterface->GetNamedValue( pszName, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void SetNamedValue( LPCWSTR pszName, REFPROPVARIANT propvar ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetNamedValue( pszName, propvar );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        DWORD GetNameCount( ) const
        {
            auto pInterface = GetInterface( );
            DWORD result = 0;
            auto hr = pInterface->GetNameCount( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        SysString GetNameAt( DWORD iProp ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = 0;
            auto hr = pInterface->GetNameAt( iProp, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return SysString( result, true );
        }

    };


    class ObjectWithPropertyKey : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( ObjectWithPropertyKey, Unknown, IObjectWithPropertyKey, IUnknown )

        void SetPropertyKey( REFPROPERTYKEY key ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetPropertyKey( key );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PROPERTYKEY GetPropertyKey( ) const
        {
            auto pInterface = GetInterface( );
            PROPERTYKEY result = { 0, };
            auto hr = pInterface->GetPropertyKey( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void GetPropertyKey( PROPERTYKEY* theKey ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyKey( theKey );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetPropertyKey( PROPERTYKEY& theKey ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyKey( &theKey );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    class PropertyChange : public ObjectWithPropertyKey
    {
    public:
        typedef ObjectWithPropertyKey Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyChange, ObjectWithPropertyKey, IPropertyChange, IObjectWithPropertyKey )

        void ApplyToPropVariant( REFPROPVARIANT propvarIn, PROPVARIANT* ppropvarOut ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ApplyToPropVariant( propvarIn, ppropvarOut );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        void ApplyToPropVariant( REFPROPVARIANT propvarIn, PROPVARIANT& propvarOut ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ApplyToPropVariant( propvarIn, &propvarOut );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

    };


    class PropertyChangeArray : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyChangeArray, Unknown, IPropertyChangeArray, IUnknown )

        UINT GetCount( ) const
        {
            auto pInterface = GetInterface( );
            UINT result = 0;
            auto hr = pInterface->GetCount( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        template< typename T>
        T GetAt( UINT iIndex ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result = nullptr;
            auto hr = pInterface->GetAt( iIndex, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void InsertAt( UINT iIndex, IPropertyChange* ppropChange ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InsertAt( iIndex, ppropChange );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Append( IPropertyChange* ppropChange ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Append( ppropChange );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void AppendOrReplace( IPropertyChange* ppropChange ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AppendOrReplace( ppropChange );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void RemoveAt( UINT iIndex ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveAt( iIndex );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        bool IsKeyInArray( REFPROPERTYKEY key ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsKeyInArray( key );

            return hr == S_OK;
        }

    };


    class PropertyStoreCapabilities : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyStoreCapabilities, Unknown, IPropertyStoreCapabilities, IUnknown )

        bool IsPropertyWritable( REFPROPERTYKEY key ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsPropertyWritable( key );

            return hr == S_OK;
        }
    };


    class PropertyStoreCache : public PropertyStore
    {
    public:
        typedef PropertyStore Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyStoreCache, PropertyStore, IPropertyStoreCache, IPropertyStore )

        PSC_STATE GetState( REFPROPERTYKEY key ) const
        {
            auto pInterface = GetInterface( );
            PSC_STATE result;
            auto hr = pInterface->GetState( key, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        void GetValueAndState( REFPROPERTYKEY key, PROPVARIANT* ppropvar, PSC_STATE* pstate ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetValueAndState( key, ppropvar, pstate );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetState( REFPROPERTYKEY key, PSC_STATE state ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetState( key, state );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetValueAndState( REFPROPERTYKEY key, const PROPVARIANT* ppropvar, PSC_STATE state ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetValueAndState( key, ppropvar, state );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

    };


    class PropertyEnumType : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyEnumType, Unknown, IPropertyEnumType, IUnknown )

        PROPENUMTYPE GetEnumType( ) const
        {
            auto pInterface = GetInterface( );
            PROPENUMTYPE result = PET_DISCRETEVALUE;
            auto hr = pInterface->GetEnumType( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        PropertyVariant GetValue( ) const
        {
            auto pInterface = GetInterface( );
            PropertyVariant result;
            auto hr = pInterface->GetValue( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        PropertyVariant GetRangeMinValue( ) const
        {
            auto pInterface = GetInterface( );
            PropertyVariant result;
            auto hr = pInterface->GetRangeMinValue( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        PropertyVariant GetRangeSetValue( ) const
        {
            auto pInterface = GetInterface( );
            PropertyVariant result;
            auto hr = pInterface->GetRangeSetValue( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        ComString GetDisplayText( ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetDisplayText( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }

    };


    class PropertyEnumType2 : public PropertyEnumType
    {
    public:
        typedef PropertyEnumType Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyEnumType2, PropertyEnumType, IPropertyEnumType2, IPropertyEnumType )

        ComString GetImageReference( ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetImageReference( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }
    };


    class PropertyEnumTypeList : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyEnumTypeList, Unknown, IPropertyEnumTypeList, IUnknown )

        UINT GetCount( ) const
        {
            UINT result;
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCount( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        template <typename T >
        T GetAt( UINT itype ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetAt( itype, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyEnumType GetAt( UINT itype ) const
        {
            return GetAt<PropertyEnumType>( itype );
        }


        UINT FindMatchingIndex( REFPROPVARIANT propvarCmp ) const
        {
            auto pInterface = GetInterface( );
            UINT result = 0;
            auto hr = pInterface->FindMatchingIndex( propvarCmp, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
    };


    class PropertyDescription : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyDescription, Unknown, IPropertyDescription, IUnknown )

        PROPERTYKEY GetPropertyKey( ) const
        {
            auto pInterface = GetInterface( );
            PROPERTYKEY result;
            auto hr = pInterface->GetPropertyKey( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        ComString GetCanonicalName( ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetCanonicalName( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString(result);
        }

        VariantType GetPropertyType( ) const
        {
            auto pInterface = GetInterface( );
            VARTYPE result;
            auto hr = pInterface->GetPropertyType( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return VariantType( result );
        }

        ComString GetDisplayName( ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetDisplayName( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }

        ComString GetEditInvitation( ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetEditInvitation( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }

        PROPDESC_TYPE_FLAGS GetTypeFlags( PROPDESC_TYPE_FLAGS mask ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_TYPE_FLAGS result;
            auto hr = pInterface->GetTypeFlags( mask, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        PROPDESC_VIEW_FLAGS GetViewFlags( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_VIEW_FLAGS result;
            auto hr = pInterface->GetViewFlags( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        UINT GetDefaultColumnWidth( ) const
        {
            auto pInterface = GetInterface( );
            UINT result;
            auto hr = pInterface->GetDefaultColumnWidth( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        PROPDESC_DISPLAYTYPE GetDisplayType( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_DISPLAYTYPE result;
            auto hr = pInterface->GetDisplayType( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        SHCOLSTATEF GetColumnState( ) const
        {
            auto pInterface = GetInterface( );
            SHCOLSTATEF result;
            auto hr = pInterface->GetColumnState( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        PROPDESC_GROUPING_RANGE GetGroupingRange( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_GROUPING_RANGE result;
            auto hr = pInterface->GetGroupingRange( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        PROPDESC_RELATIVEDESCRIPTION_TYPE GetRelativeDescriptionType( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_RELATIVEDESCRIPTION_TYPE result;
            auto hr = pInterface->GetRelativeDescriptionType( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void GetRelativeDescription( REFPROPVARIANT propvar1, REFPROPVARIANT propvar2, ComString& desc1, ComString& desc2 ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR pDesc1, pDesc2;
            auto hr = pInterface->GetRelativeDescription( propvar1, propvar2, &pDesc1, &pDesc2 );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            desc1 = ComString( pDesc1 );
            desc2 = ComString( pDesc2 );
        }

        PROPDESC_SORTDESCRIPTION GetSortDescription( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_SORTDESCRIPTION result;
            auto hr = pInterface->GetSortDescription( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        ComString GetSortDescriptionLabel( bool descending ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetSortDescriptionLabel( descending, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }

        PROPDESC_AGGREGATION_TYPE GetAggregationType( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_AGGREGATION_TYPE result;
            auto hr = pInterface->GetAggregationType( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void GetConditionType( PROPDESC_CONDITION_TYPE* pcontype, CONDITION_OPERATION* popDefault ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetConditionType( pcontype, popDefault );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetConditionType( PROPDESC_CONDITION_TYPE& contype, CONDITION_OPERATION& opDefault ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetConditionType( &contype, &opDefault );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        template < typename T >
        T GetEnumTypeList( ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetEnumTypeList( __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyEnumTypeList GetEnumTypeList( ) const
        {
            return GetEnumTypeList<PropertyEnumTypeList>( );
        }


        PropertyVariant CoerceToCanonicalValue( ) const
        {
            auto pInterface = GetInterface( );
            PropertyVariant result;
            auto hr = pInterface->CoerceToCanonicalValue( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        ComString FormatForDisplay( REFPROPVARIANT propvar, PROPDESC_FORMAT_FLAGS pdfFlags ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->FormatForDisplay( propvar, pdfFlags, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }

        bool IsValueCanonical( REFPROPVARIANT propvar ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsValueCanonical( propvar );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return hr == S_OK;
        }
    };

    class PropertyDescriptionList : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyDescriptionList, Unknown, IPropertyDescriptionList, IUnknown )

        UInt32 GetCount( ) const
        {
            UINT result;
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCount( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        template<typename T >
        T GetAt( UINT iElem ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetAt( iElem, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescription GetAt( UINT iElem ) const
        {
            return GetAt<PropertyDescription>( iElem );
        }

    };


    class PropertyDescription2 : public PropertyDescription
    {
    public:
        typedef PropertyDescription Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyDescription2, PropertyDescription, IPropertyDescription2, IPropertyDescription )

        ComString GetImageReferenceForValue( REFPROPVARIANT propvar ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetImageReferenceForValue( propvar, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }
    };

    class PropertyDescriptionAliasInfo : public PropertyDescription
    {
    public:
        typedef PropertyDescription Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyDescriptionAliasInfo, PropertyDescription, IPropertyDescriptionAliasInfo, IPropertyDescription )

        template <typename T >
        T GetSortByAlias( ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetSortByAlias( __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescription GetSortByAlias( ) const
        {
            return GetSortByAlias<PropertyDescription>( );
        }

        template <typename T >
        T GetAdditionalSortByAliases( ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetAdditionalSortByAliases( __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescriptionList GetAdditionalSortByAliases( ) const
        {
            return GetAdditionalSortByAliases<PropertyDescriptionList>( );
        }

    };


    class PropertyDescriptionSearchInfo : public PropertyDescription
    {
    public:
        typedef PropertyDescription Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyDescriptionSearchInfo, PropertyDescription, IPropertyDescriptionSearchInfo, IPropertyDescription )

        PROPDESC_SEARCHINFO_FLAGS GetSearchInfoFlags( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_SEARCHINFO_FLAGS result;
            auto hr = pInterface->GetSearchInfoFlags( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        PROPDESC_COLUMNINDEX_TYPE GetColumnIndexType( ) const
        {
            auto pInterface = GetInterface( );
            PROPDESC_COLUMNINDEX_TYPE result;
            auto hr = pInterface->GetColumnIndexType( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        ComString GetProjectionString( ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result;
            auto hr = pInterface->GetProjectionString( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }

        UINT GetMaxSize( ) const
        {
            auto pInterface = GetInterface( );
            UINT result;
            auto hr = pInterface->GetMaxSize( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

    };


    class PropertyDescriptionRelatedPropertyInfo : public PropertyDescription
    {
    public:
        typedef PropertyDescription Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyDescriptionRelatedPropertyInfo, PropertyDescription, IPropertyDescriptionRelatedPropertyInfo, IPropertyDescription )

        template <typename T >
        T GetRelatedProperty( LPCWSTR pszRelationshipName ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetRelatedProperty( pszRelationshipName, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescription GetRelatedProperty( LPCWSTR pszRelationshipName ) const
        {
            return GetRelatedProperty<PropertyDescription>( pszRelationshipName );
        }

    };


    class PropertySystem : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertySystem, Unknown, IPropertySystem, IUnknown )

        template <typename T >
        T GetPropertyDescription( REFPROPERTYKEY propkey ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetPropertyDescription( propkey, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescription GetPropertyDescription( REFPROPERTYKEY propkey ) const
        {
            return GetPropertyDescription<PropertyDescription>( propkey );
        }


        template <typename T >
        T GetPropertyDescriptionByName( LPCWSTR pszCanonicalName ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetPropertyDescriptionByName( pszCanonicalName, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescription GetPropertyDescriptionByName( LPCWSTR pszCanonicalName ) const
        {
            return GetPropertyDescriptionByName<PropertyDescription>( pszCanonicalName );
        }


        template <typename T >
        T GetPropertyDescriptionListFromString( LPCWSTR pszPropList ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetPropertyDescriptionListFromString( pszPropList, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescriptionList GetPropertyDescriptionListFromString( LPCWSTR pszPropList ) const
        {
            return GetPropertyDescriptionListFromString<PropertyDescriptionList>( pszPropList );
        }

        template <typename T >
        T EnumeratePropertyDescriptions( PROPDESC_ENUMFILTER filterOn ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->EnumeratePropertyDescriptions( filterOn, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyDescriptionList EnumeratePropertyDescriptions( PROPDESC_ENUMFILTER filterOn ) const
        {
            return EnumeratePropertyDescriptions<PropertyDescriptionList>( filterOn );
        }


        void FormatForDisplay( REFPROPERTYKEY key, REFPROPVARIANT propvar, PROPDESC_FORMAT_FLAGS pdff, LPWSTR pszText, DWORD cchText ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->FormatForDisplay( key, propvar, pdff, pszText, cchText );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        ComString FormatForDisplayAlloc( REFPROPERTYKEY key, REFPROPVARIANT propvar, PROPDESC_FORMAT_FLAGS pdff ) const
        {
            auto pInterface = GetInterface( );
            LPWSTR result = 0;
            auto hr = pInterface->FormatForDisplayAlloc( key, propvar, pdff, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return ComString( result );
        }

        void RegisterPropertySchema( LPCWSTR pszPath ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->RegisterPropertySchema( pszPath );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void UnregisterPropertySchema( LPCWSTR pszPath ) const
        {
            auto pInterface = GetInterface( );

            auto hr = pInterface->UnregisterPropertySchema( pszPath );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void RefreshPropertySchema( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RefreshPropertySchema( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    class PropertyStoreFactory : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertyStoreFactory, Unknown, IPropertyStoreFactory, IUnknown )

        template <typename T >
        T GetPropertyStore( GETPROPERTYSTOREFLAGS flags, IUnknown* pUnkFactory ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetPropertyStore( flags, pUnkFactory, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyStore GetPropertyStore( GETPROPERTYSTOREFLAGS flags, IUnknown* pUnkFactory ) const
        {
            return GetPropertyStore<PropertyStore>( flags, pUnkFactory );
        }

        template <typename T >
        T GetPropertyStoreForKeys( const PROPERTYKEY* rgKeys, UINT cKeys, GETPROPERTYSTOREFLAGS flags ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetPropertyStoreForKeys( rgKeys, cKeys, flags, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }
        PropertyStore GetPropertyStoreForKeys( const PROPERTYKEY* rgKeys, UINT cKeys, GETPROPERTYSTOREFLAGS flags ) const
        {
            return GetPropertyStoreForKeys<PropertyStore>( rgKeys, cKeys, flags );
        }


    };


    class DelayedPropertyStoreFactory : public PropertyStoreFactory
    {
    public:
        typedef PropertyStoreFactory Base;
        HCC_COM_STANDARD_METHODS_IMPL( DelayedPropertyStoreFactory, PropertyStoreFactory, IDelayedPropertyStoreFactory, IPropertyStoreFactory )

        template <typename T >
        T GetDelayedPropertyStore( GETPROPERTYSTOREFLAGS flags, DWORD dwStoreId ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->GetDelayedPropertyStore( flags, dwStoreId, __uuidof( T::InterfaceType ), (void**)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

        PropertyStore GetDelayedPropertyStore( GETPROPERTYSTOREFLAGS flags, DWORD dwStoreId ) const
        {
            return GetDelayedPropertyStore<PropertyStore>( flags, dwStoreId );
        }
    };


    class PersistSerializedPropStorage : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PersistSerializedPropStorage, Unknown, IPersistSerializedPropStorage, IUnknown )

        void SetFlags( PERSIST_SPROPSTORE_FLAGS flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFlags( flags );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetPropertyStorage( PCUSERIALIZEDPROPSTORAGE psps, DWORD cb ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetPropertyStorage( psps, cb );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetPropertyStorage( SERIALIZEDPROPSTORAGE** ppsps, DWORD* pcb ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyStorage( ppsps, pcb );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    class PersistSerializedPropStorage2 : public PersistSerializedPropStorage
    {
    public:
        typedef PersistSerializedPropStorage Base;
        HCC_COM_STANDARD_METHODS_IMPL( PersistSerializedPropStorage2, PersistSerializedPropStorage, IPersistSerializedPropStorage2, IPersistSerializedPropStorage )

        DWORD GetPropertyStorageSize( ) const
        {
            auto pInterface = GetInterface( );
            DWORD result;
            auto hr = pInterface->GetPropertyStorageSize( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        DWORD GetPropertyStorageBuffer( SERIALIZEDPROPSTORAGE* psps, DWORD cb ) const
        {
            auto pInterface = GetInterface( );
            DWORD result;
            auto hr = pInterface->GetPropertyStorageBuffer( psps, cb, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
    };


    class PropertySystemChangeNotify : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PropertySystemChangeNotify, Unknown, IPropertySystemChangeNotify, IUnknown )

        void SchemaRefreshed( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SchemaRefreshed( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    class CreateObject_ : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( CreateObject_, Unknown, ICreateObject, IUnknown )

        template <typename T >
        T CreateObject( REFCLSID clsid, IUnknown* pUnkOuter = nullptr ) const
        {
            auto pInterface = GetInterface( );
            typename T::InterfaceType* result;
            auto hr = pInterface->CreateObject( clsid, pUnkOuter, __uuidof( T::InterfaceType ), &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return T( result );
        }

    };


}
#endif
