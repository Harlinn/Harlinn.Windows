#pragma once
#ifndef HARLINN_WINDOWS_HWMFOBJECTSTYPES_H_
#define HARLINN_WINDOWS_HWMFOBJECTSTYPES_H_
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

#include "HWDef.h"

namespace Harlinn::Windows
{
    class MFAttributes;
}

namespace Harlinn::Windows::MF
{
    template<typename T>
    class BlobValue
    {
    public:
        using DataType = T;
    private:
        size_t dataSize_ = 0;
        T* data_ = nullptr;
    public:

        constexpr BlobValue() noexcept
        { }
        explicit BlobValue(size_t dataSize)
            : dataSize_(dataSize), data_(dataSize? reinterpret_cast<DataType*>( new Byte[dataSize]):nullptr)
        {
        }
        BlobValue(size_t dataSize, DataType* data) noexcept
            : dataSize_(dataSize), data_(data)
        {
        }
        ~BlobValue()
        {
            if (data_)
            {
                Byte* ptr = reinterpret_cast<Byte*>(data_);
                delete[] ptr;
            }
        }

        BlobValue(const BlobValue& other) = delete;
        BlobValue& operator = (const BlobValue& other) = delete;

        BlobValue(BlobValue&& other) noexcept
            : dataSize_(other.dataSize_), data_(other.data_)
        {
            other.dataSize_ = 0;
            other.data_ = nullptr;
        }
        BlobValue& operator = (BlobValue&& other) noexcept
        {
            std::swap(dataSize_, other.dataSize_);
            std::swap(data_, other.data_);
            return *this;
        }

        constexpr explicit operator bool() const noexcept
        {
            return data_ != nullptr;
        }

        constexpr size_t DataSize() const noexcept
        {
            return dataSize_;
        }

        constexpr const DataType* data() const noexcept
        {
            return data_;
        }
        constexpr DataType* data() noexcept
        {
            return data_;
        }
    };

    class EncryptionSubSampleMappingSplit : public BlobValue<DWORD>
    {
    public:
        using Base = BlobValue<DWORD>;
        using Base::Base;

        constexpr size_t size() const noexcept
        {
            return DataSize()/sizeof(DWORD);
        }

        DWORD operator[](size_t index) const noexcept
        {
            return reinterpret_cast<const DWORD*>(data())[index];
        }
        DWORD& operator[](size_t index) noexcept
        {
            return reinterpret_cast<DWORD*>(data())[index];
        }
    };


    class PacketCrossOffsets : public BlobValue<DWORD>
    {
    public:
        using Base = BlobValue<DWORD>;
        using Base::Base;

        constexpr size_t size() const noexcept
        {
            return DataSize() / sizeof(DWORD);
        }

        DWORD operator[](size_t index) const noexcept
        {
            return reinterpret_cast<const DWORD*>(data())[index];
        }
        DWORD& operator[](size_t index) noexcept
        {
            return reinterpret_cast<DWORD*>(data())[index];
        }
    };



    class CameraExtrinsics
    {
        MFCameraExtrinsics* data_ = nullptr;
    public:
        static constexpr size_t CalibratedTransformSize = sizeof(MFCameraExtrinsic_CalibratedTransform);
        constexpr CameraExtrinsics() noexcept
        { }
        constexpr CameraExtrinsics(MFCameraExtrinsics* data) noexcept
            : data_(data)
        {
        }

        ~CameraExtrinsics()
        {
            if (data_)
            {
                Byte* ptr = reinterpret_cast<Byte*>(data_);
                delete[] ptr;
            }
        }


        CameraExtrinsics(const CameraExtrinsics& other) = delete;
        CameraExtrinsics& operator = (const CameraExtrinsics& other) = delete;

        CameraExtrinsics(CameraExtrinsics&& other) noexcept
            : data_(other.data_)
        {
            other.data_ = nullptr;
        }
        CameraExtrinsics& operator = (CameraExtrinsics&& other) noexcept
        {
            std::swap(data_, other.data_);
            return *this;
        }

        size_t size() const noexcept
        {
            data_ ? data_->TransformCount : 0;
        }
        size_t DataSize() const noexcept
        {
            return data_ ? (offsetof(MFCameraExtrinsics, CalibratedTransforms) + data_->TransformCount * CalibratedTransformSize) : 0;
        }


        constexpr MFCameraExtrinsics* data() const noexcept
        {
            return data_;
        }


        const MFCameraExtrinsic_CalibratedTransform& operator[](size_t index) const noexcept
        {
            return data_->CalibratedTransforms[index];
        }
    };


    class Attribute
    {
        Guid key_;
        UInt16 type_;
    protected:
        constexpr Attribute()
            : type_(static_cast<UInt16>(VT_EMPTY))
        {
        }
    protected:
        constexpr explicit Attribute(MF_ATTRIBUTE_TYPE variantType)
            : type_(static_cast<UInt16>(variantType))
        {
        }

        constexpr explicit Attribute(MF_ATTRIBUTE_TYPE variantType, const Guid& key)
            : type_(static_cast<UInt16>(variantType))
        {
        }
    public:
        virtual ~Attribute()
        { }
        constexpr const Guid& Key() const noexcept
        {
            return key_;
        }
    protected:
        void SetKey(const Guid& key)
        {
            key_ = key;
        }
    public:
        constexpr MF_ATTRIBUTE_TYPE Type() const noexcept
        {
            return static_cast<MF_ATTRIBUTE_TYPE>( type_ );
        }

        template<typename ReaderT>
        static MF_ATTRIBUTE_TYPE ReadAttributeType(ReaderT& reader)
        {
            UInt16 result = reader.Read<UInt16>();
            return static_cast<MF_ATTRIBUTE_TYPE>(result);
        }
        template<typename ReaderT>
        void Read(ReaderT& reader)
        {
            key_ = reader.Read<Guid>();
        }
        template<typename WriterT>
        void Write(WriterT& writer) const
        {
            writer.Write(type_);
            writer.Write(key_);
        }



    };

    namespace Internal
    {
        template<typename T, MF_ATTRIBUTE_TYPE attrType>
        class AttributeImpl : public Attribute
        {
        public:
            using Base = Attribute;
            static constexpr MF_ATTRIBUTE_TYPE ATTRIBUTE_TYPE = attrType;
            using value_type = T;
        private:
            value_type value_;
        public:
            AttributeImpl()
                : Base(ATTRIBUTE_TYPE), value_{}
            {
            }


            explicit AttributeImpl(const Guid& key, const value_type& value = {})
                : Base(ATTRIBUTE_TYPE, key), value_(value)
            {
            }

            ~AttributeImpl()
            { }

            const value_type& Value() const
            {
                return value_;
            }
            void SetrValue(const value_type& value)
            {
                value_ = value;
            }


            template<typename ReaderT>
            void Read(ReaderT& reader)
            {
                Base::Read(reader);
                value_ = reader.Read<value_type>();
            }
            template<typename WriterT>
            void Write(WriterT& writer) const
            {
                Base::Write(writer);
                writer.Write(value_);
            }
        };
    }
    using Int32Attribute = Internal::AttributeImpl<Int32, MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT32>;
    using Int64Attribute = Internal::AttributeImpl<Int64, MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT64>;
    using DoubleAttribute = Internal::AttributeImpl<double, MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_DOUBLE>;
    using GuidAttribute = Internal::AttributeImpl<Guid, MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_GUID>;
    using StringAttribute = Internal::AttributeImpl<WideString, MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_STRING>;
    using BlobAttribute = Internal::AttributeImpl<std::vector<Byte>, MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_BLOB>;
    using UnknownAttribute = Internal::AttributeImpl<Unknown, MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_IUNKNOWN>;


    class Attributes
    {
    public:
        using Container = std::unordered_map<Guid, std::shared_ptr<Attribute>>;
    private:
        Container container_;
        using iterator = typename Container::iterator;
        using const_iterator = typename Container::const_iterator;
    public:
        Attributes()
        { }

        HW_EXPORT Attributes(const MFAttributes& attributes);

        HW_EXPORT void Add(const MFAttributes& attributes);
        HW_EXPORT void Add(const MFAttributes& attributes, UInt32 index);

        HW_EXPORT void AssignTo(const MFAttributes& attributes) const;

        size_t size() const
        {
            return container_.size();
        }

        iterator begin()
        {
            return container_.begin();
        }
        iterator end()
        {
            return container_.end();
        }
        const_iterator begin() const
        {
            return container_.begin();
        }
        const_iterator end() const
        {
            return container_.end();
        }
        const_iterator cbegin() const
        {
            return container_.begin();
        }
        const_iterator cend() const
        {
            return container_.end();
        }


    private:
        HW_EXPORT void AddInt32(const MFAttributes& attributes, const Guid& key);
        HW_EXPORT void AddInt64(const MFAttributes& attributes, const Guid& key);
        HW_EXPORT void AddDouble(const MFAttributes& attributes, const Guid& key);
        HW_EXPORT void AddGuid(const MFAttributes& attributes, const Guid& key);
        HW_EXPORT void AddString(const MFAttributes& attributes, const Guid& key);
        HW_EXPORT void AddBlob(const MFAttributes& attributes, const Guid& key);
        HW_EXPORT void AddUnknown(const MFAttributes& attributes, const Guid& key);
        UInt32 CountSerializableAttributes() const
        {
            UInt32 result = 0;
            for (auto& entry : container_)
            {
                auto entryType = entry.second->Type();
                if (entryType != MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_IUNKNOWN)
                {
                    result++;
                }
            }
            return result;
        }

        HW_EXPORT static void AssignToInt32(const Int32Attribute* attribute, const MFAttributes& attributes);
        HW_EXPORT static void AssignToInt64(const Int64Attribute* attribute, const MFAttributes& attributes);
        HW_EXPORT static void AssignToDouble(const DoubleAttribute* attribute, const MFAttributes& attributes);
        HW_EXPORT static void AssignToGuid(const GuidAttribute* attribute, const MFAttributes& attributes);
        HW_EXPORT static void AssignToString(const StringAttribute* attribute, const MFAttributes& attributes);
        HW_EXPORT static void AssignToBlob(const BlobAttribute* attribute, const MFAttributes& attributes);
        HW_EXPORT static void AssignToUnknown(const UnknownAttribute* attribute, const MFAttributes& attributes);

    public:
        template<typename WriterT>
        void Write(WriterT& writer) const
        {
            UInt32 count = CountSerializableAttributes();
            writer.Write(count);
            for (auto& entry : container_)
            {
                auto* attr = entry.second.get();
                auto entryType = attr->Type();
                switch (entryType)
                {
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT32:
                        Write(writer,static_cast<const Int32Attribute*>(attr));
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT64:
                        Write(writer, static_cast<const Int64Attribute*>(attr));
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_DOUBLE:
                        Write(writer, static_cast<const DoubleAttribute*>(attr));
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_GUID:
                        Write(writer, static_cast<const GuidAttribute*>(attr));
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_STRING:
                        Write(writer, static_cast<const StringAttribute*>(attr));
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_BLOB:
                        Write(writer, static_cast<const BlobAttribute*>(attr));
                        break;
                }
            }
        }
        template<typename ReaderT>
        void Read(ReaderT& reader)
        {
            container_.clear();
            auto count = reader.Read<UInt32>();
            for (UInt32 i = 0; i < count; i++)
            {
                auto attributeType = Attribute::ReadAttributeType<ReaderT>(reader);
                switch (attributeType)
                {
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT32:
                        ReadInt32Attribute<ReaderT>( reader );
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT64:
                        ReadInt64Attribute<ReaderT>(reader);
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_DOUBLE:
                        ReadDoubleAttribute<ReaderT>(reader);
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_GUID:
                        ReadGuidAttribute<ReaderT>(reader);
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_STRING:
                        ReadStringAttribute<ReaderT>(reader);
                        break;
                    case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_BLOB:
                        ReadBlobAttribute<ReaderT>(reader);
                        break;
                }
            }
        }
    private:
        template<typename WriterT>
        static void Write(WriterT& writer, const Int32Attribute* attr) { attr->Write(writer); }
        template<typename WriterT>
        static void Write(WriterT& writer, const Int64Attribute* attr) { attr->Write(writer); }
        template<typename WriterT>
        static void Write(WriterT& writer, const DoubleAttribute* attr) { attr->Write(writer); }
        template<typename WriterT>
        static void Write(WriterT& writer, const GuidAttribute* attr) { attr->Write(writer); }
        template<typename WriterT>
        static void Write(WriterT& writer, const StringAttribute* attr) { attr->Write(writer); }
        template<typename WriterT>
        static void Write(WriterT& writer, const BlobAttribute* attr) { attr->Write(writer); }

        template<typename ReaderT, typename AttributeT>
        void ReadAttribute(ReaderT& reader)
        {
            auto attr = std::make_shared<AttributeT>();
            attr->Read<ReaderT>(reader);
            auto key = attr->Key();
            container_.insert_or_assign(key, std::move(attr));
        }

        template<typename ReaderT>
        void ReadInt32Attribute(ReaderT& reader)
        {
            ReadAttribute<ReaderT, Int32Attribute>(reader);
        }
        template<typename ReaderT>
        void ReadInt64Attribute(ReaderT& reader)
        {
            ReadAttribute<ReaderT, Int64Attribute>(reader);
        }
        template<typename ReaderT>
        void ReadDoubleAttribute(ReaderT& reader)
        {
            ReadAttribute<ReaderT, DoubleAttribute>(reader);
        }
        template<typename ReaderT>
        void ReadGuidAttribute(ReaderT& reader)
        {
            ReadAttribute<ReaderT, GuidAttribute>(reader);
        }
        template<typename ReaderT>
        void ReadStringAttribute(ReaderT& reader)
        {
            ReadAttribute<ReaderT, StringAttribute>(reader);
        }
        template<typename ReaderT>
        void ReadBlobAttribute(ReaderT& reader)
        {
            ReadAttribute<ReaderT, BlobAttribute>(reader);
        }




    };




}

#endif
