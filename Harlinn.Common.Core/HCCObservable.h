#pragma once
#ifndef HARLINN_COMMON_CORE_HCCOBSERVABLE_H_
#define HARLINN_COMMON_CORE_HCCOBSERVABLE_H_
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

#include <HCCDef.h>
#include <xxhash_cx.h>
#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    using namespace xxhash::literals;

#define HCC_OBSERVABLE_IMPLEMENT_PROPERTY(_propertyType_, _propertyName_, _propertyMemberVariableName_) \
public: \
    const _propertyType_& _propertyName_() const { return _propertyMemberVariableName_; } \
    void Set##_propertyName_(const _propertyType_& v) \
    { \
        if (_propertyMemberVariableName_ != v) \
        { \
            auto _oldValue_ = _propertyMemberVariableName_; \
            _propertyMemberVariableName_ = v; \
            this->DoOn##_propertyName_##Changed( _oldValue_, _propertyMemberVariableName_); \
        } \
    } \
    void Set##_propertyName_(_propertyType_&& v) \
    { \
        if (_propertyMemberVariableName_ != v) \
        { \
            auto _oldValue_ = _propertyMemberVariableName_; \
            _propertyMemberVariableName_ = std::move( v ); \
            this->DoOn##_propertyName_##Changed( _oldValue_, _propertyMemberVariableName_ ); \
        } \
    } \
protected: \
    virtual void DoOn##_propertyName_##Changed( const _propertyType_& oldValue, const _propertyType_& newValue ) \
    { \
        this->DoOnChanged( _propertyName_##PropertyId ); \
    } \
public: \
    static constexpr uint64_t _propertyName_##PropertyId = #_propertyName_##_xxh64

#define HCC_OBSERVABLE_IMPLEMENT_POINTER_PROPERTY(_propertyType_, _propertyName_, _propertyMemberVariableName_) \
public: \
    const _propertyType_* _propertyName_() const { return _propertyMemberVariableName_; } \
    void Set##_propertyName_(_propertyType_* v) \
    { \
        if (_propertyMemberVariableName_ != v) \
        { \
            auto _oldValue_ = _propertyMemberVariableName_; \
            _propertyMemberVariableName_ = v; \
            this->DoOn##_propertyName_##Changed( _oldValue_, _propertyMemberVariableName_); \
        } \
    } \
protected: \
    virtual void DoOn##_propertyName_##Changed( _propertyType_* oldValue, _propertyType_* newValue ) \
    { \
        this->DoOnChanged( _propertyName_##PropertyId ); \
    } \
public: \
    static constexpr uint64_t _propertyName_##PropertyId = #_propertyName_##_xxh64


    template<typename DerivedT>
    class Observable : public ReferenceCounted
    {
    public:
        using Base = ReferenceCounted;
    private:
        using DerivedType = DerivedT;
    public:
        boost::signals2::signal<void( DerivedT* sender, uint64_t key, void* data )> OnChanged;
    protected:
        constexpr Observable( ) = default;
    public:
        virtual ~Observable( ) override = default;
    protected:
        virtual void DoOnChanged( uint64_t propertyId = 0, void* data = nullptr )
        {
            OnChanged( static_cast<DerivedT*>( this ), propertyId, data );
        }
    };




}

#endif
