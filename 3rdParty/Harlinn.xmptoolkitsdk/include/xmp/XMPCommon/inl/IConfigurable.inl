#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_ICONFIGURABLE_INL_
#define HARLINN_XMP_ICONFIGURABLE_INL_


#include <assert.h>

namespace AdobeXMPCommon {

	HXMP_INLINE IConfigurableProxy::IConfigurableProxy( pIConfigurable configurable )
		: mConfigurableRawPtr( configurable ) { }

	HXMP_INLINE void IConfigurableProxy::SetParameter( const uint64 & key, bool value ) {
		CombinedDataValue combinedValue;
		combinedValue.uint32Value = value ? 1 : 0;
		CallSafeFunctionReturningVoid< IConfigurable, const uint64 &, uint32, const CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::setParameter, key, static_cast< uint32 >( IConfigurable::kDTBool ), combinedValue
		);
	}

	HXMP_INLINE void IConfigurableProxy::setParameter( const uint64 & key, uint32 dataType, const CombinedDataValue & dataValue, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mConfigurableRawPtr->setParameter( key, dataType, dataValue, error );
	}

	HXMP_INLINE bool IConfigurableProxy::RemoveParameter( const uint64 & key ) {
		return CallSafeFunction< IConfigurable, bool, uint32, const uint64 & >(
			mConfigurableRawPtr, &IConfigurable::removeParameter, key );
	}

	HXMP_INLINE uint32 IConfigurableProxy::removeParameter( const uint64 & key, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mConfigurableRawPtr->removeParameter( key, error );
	}

	HXMP_INLINE bool IConfigurableProxy::GetParameter( const uint64 & key, bool & value ) const {
		CombinedDataValue combinedValue;
		bool returnValue = CallConstSafeFunction< IConfigurable, bool, uint32, const uint64 &, uint32, CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::getParameter, key, static_cast< uint32 >( IConfigurable::kDTBool ), combinedValue
		);
		value = combinedValue.uint32Value != 0 ? 1 : 0;
		return returnValue;
	}

	HXMP_INLINE uint32 IConfigurableProxy::getParameter( const uint64 & key, uint32 dataType, CombinedDataValue & value, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mConfigurableRawPtr->getParameter( key, dataType, value, error );
	}

	HXMP_INLINE std::vector< uint64 > IConfigurableProxy::GetAllParameters() const {
		sizet nElements = mConfigurableRawPtr->Size();
		std::vector< uint64 > vec( nElements );
		if ( nElements > 0 )
			mConfigurableRawPtr->getAllParameters( vec.data(), nElements );
		return vec;
	}

	HXMP_INLINE void IConfigurableProxy::getAllParameters( uint64 * array, sizet count ) const __NOTHROW__ {
		assert( false );
		return mConfigurableRawPtr->getAllParameters( array, count );
	}

	HXMP_INLINE sizet IConfigurableProxy::Size() const __NOTHROW__ {
		return mConfigurableRawPtr->Size();
	}

	HXMP_INLINE IConfigurable::eDataType IConfigurableProxy::GetDataType( const uint64 & key ) const {
		return CallConstSafeFunction< IConfigurable, eDataType, uint32, const uint64 & >(
			mConfigurableRawPtr, &IConfigurable::getDataType, key );
	}

	HXMP_INLINE uint32 IConfigurableProxy::getDataType( const uint64 & key, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mConfigurableRawPtr->getDataType( key, error );
	}

	HXMP_INLINE bool IConfigurableProxy::GetParameter( const uint64 & key, const void * & value ) const {
		CombinedDataValue combinedValue;
		bool returnValue = CallConstSafeFunction< IConfigurable, bool, uint32, const uint64 &, uint32, CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::getParameter, key, static_cast< uint32 >( IConfigurable::kDTConstVoidPtr ), combinedValue
		);
		value = combinedValue.constVoidPtrValue;
		return returnValue;
	}

	HXMP_INLINE bool IConfigurableProxy::GetParameter( const uint64 & key, const char * & value ) const {
		CombinedDataValue combinedValue;
		bool returnValue = CallConstSafeFunction< IConfigurable, bool, uint32, const uint64 &, uint32, CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::getParameter, key, static_cast< uint32 >( IConfigurable::kDTConstCharBuffer ), combinedValue
		);
		value = combinedValue.constCharPtrValue;
		return returnValue;
	}

	HXMP_INLINE bool IConfigurableProxy::GetParameter( const uint64 & key, char & value ) const {
		CombinedDataValue combinedValue;
		bool returnValue = CallConstSafeFunction< IConfigurable, bool, uint32, const uint64 &, uint32, CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::getParameter, key, static_cast< uint32 >( IConfigurable::kDTChar ), combinedValue
		);
		value = combinedValue.charValue;
		return returnValue;
	}

	HXMP_INLINE bool IConfigurableProxy::GetParameter( const uint64 & key, double & value ) const {
		CombinedDataValue combinedValue;
		bool returnValue = CallConstSafeFunction< IConfigurable, bool, uint32, const uint64 &, uint32, CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::getParameter, key, static_cast< uint32 >( IConfigurable::kDTDouble ), combinedValue
		);
		value = combinedValue.doubleValue;
		return returnValue;
	}

	HXMP_INLINE bool IConfigurableProxy::GetParameter( const uint64 & key, int64 & value ) const {
		CombinedDataValue combinedValue;
		bool returnValue = CallConstSafeFunction< IConfigurable, bool, uint32, const uint64 &, uint32, CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::getParameter, key, static_cast< uint32 >( IConfigurable::kDTInt64 ), combinedValue
		);
		value = combinedValue.int64Value;
		return returnValue;
	}

	HXMP_INLINE bool IConfigurableProxy::GetParameter( const uint64 & key, uint64 & value ) const {
		CombinedDataValue combinedValue;
		bool returnValue = CallConstSafeFunction< IConfigurable, bool, uint32, const uint64 &, uint32, CombinedDataValue &
		>(
		mConfigurableRawPtr, &IConfigurable::getParameter, key, static_cast< uint32 >( IConfigurable::kDTUint64 ), combinedValue
		);
		value = combinedValue.uint64Value;
		return returnValue;
	}

	HXMP_INLINE void IConfigurableProxy::SetParameter( const uint64 & key, const void * value ) {
		CombinedDataValue combinedValue;
		combinedValue.constVoidPtrValue= value;
		return CallSafeFunctionReturningVoid< IConfigurable, const uint64 &, uint32, const CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::setParameter, key, static_cast< uint32 >( IConfigurable::kDTConstVoidPtr ), combinedValue
		);
	}

	HXMP_INLINE void IConfigurableProxy::SetParameter( const uint64 & key, const char * value ) {
		CombinedDataValue combinedValue;
		combinedValue.constCharPtrValue = value;
		return CallSafeFunctionReturningVoid< IConfigurable, const uint64 &, uint32, const CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::setParameter, key, static_cast< uint32 >( IConfigurable::kDTConstCharBuffer ), combinedValue
		);
	}

	HXMP_INLINE void IConfigurableProxy::SetParameter( const uint64 & key, char value ) {
		CombinedDataValue combinedValue;
		combinedValue.charValue = value;
		return CallSafeFunctionReturningVoid< IConfigurable, const uint64 &, uint32, const CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::setParameter, key, static_cast< uint32 >( IConfigurable::kDTChar ), combinedValue
		);
	}

	HXMP_INLINE void IConfigurableProxy::SetParameter( const uint64 & key, double value ) {
		CombinedDataValue combinedValue;
		combinedValue.doubleValue = value;
		return CallSafeFunctionReturningVoid< IConfigurable, const uint64 &, uint32, const CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::setParameter, key, static_cast< uint32 >( IConfigurable::kDTDouble ), combinedValue
		);
	}

	HXMP_INLINE void IConfigurableProxy::SetParameter( const uint64 & key, int64 value ) {
		CombinedDataValue combinedValue;
		combinedValue.int64Value = value;
		return CallSafeFunctionReturningVoid< IConfigurable, const uint64 &, uint32, const CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::setParameter, key, static_cast< uint32 >( IConfigurable::kDTInt64 ), combinedValue
		);
	}

	HXMP_INLINE void IConfigurableProxy::SetParameter( const uint64 & key, uint64 value ) {
		CombinedDataValue combinedValue;
		combinedValue.uint64Value = value;
		return CallSafeFunctionReturningVoid< IConfigurable, const uint64 &, uint32, const CombinedDataValue &
		>(
			mConfigurableRawPtr, &IConfigurable::setParameter, key, static_cast< uint32 >( IConfigurable::kDTUint64 ), combinedValue
		);
	}

}

#endif
