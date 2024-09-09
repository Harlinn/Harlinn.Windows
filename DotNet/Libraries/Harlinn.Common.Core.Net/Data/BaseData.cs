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

using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.IO;

using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Common.Core.Net.Data
{
    public enum ObjectState : byte
    {
        Unknown,
        New,
        Stored,
        Changed,
        Deleted,
        ConcurrencyConflict
    }

    public abstract class BaseData<TEnum> : IEquatable<BaseData<TEnum>> where TEnum : struct, System.Enum
    {
        ObjectState objectState_ = ObjectState.Unknown;

        public BaseData()
        { }

        public BaseData(ObjectState objectState)
        {
            objectState_ = ObjectState;
        }

        protected void OnPropertyChanged()
        {
            if (objectState_ == Data.ObjectState.Stored || objectState_ == Data.ObjectState.ConcurrencyConflict)
            {
                objectState_ = Data.ObjectState.Changed;
            }
        }

        public abstract TEnum GetObjectType();

        public virtual bool IsOfType(TEnum objectType)
        {
            return objectType.Equals(default(TEnum));
        }

        
        public Data.ObjectState ObjectState { get => objectState_; set => objectState_ = value; }

        public virtual void WriteTo([DisallowNull] BinaryWriter destination)
        {
            var objectType = GetObjectType();
            destination.Write(objectType);
            destination.Write(objectState_);
        }

        public virtual void ReadFrom([DisallowNull] BinaryReader source)
        {
            objectState_ = source.ReadEnum<ObjectState>();
        }

        public abstract BaseData<TEnum> Create();

        public virtual void AssignTo([DisallowNull] BaseData<TEnum> target)
        {
            target.objectState_ = objectState_;
        }

        public BaseData<TEnum> Clone()
        {
            var result = Create();
            AssignTo(result);
            return result;
        }

        public virtual bool Equals(Data.BaseData<TEnum>? other)
        {
            if (ReferenceEquals(null, other))
            {
                return false;
            }
            else
            {
                return GetObjectType().Equals( other.GetObjectType() );
            }
        }
    }

    public abstract class BaseDataInt64<TEnum> : BaseData<TEnum> where TEnum : struct, System.Enum
    {
        long _id = default;

        public BaseDataInt64()
        { }

        public BaseDataInt64(ObjectState objectState, long id)
            : base(objectState) 
        {
            _id = id;
        }


        public long Id { get => _id; set => _id = value; }

        public override void WriteTo([DisallowNull] BinaryWriter destination)
        {
            base.WriteTo(destination);
            destination.Write(_id);
        }

        public override void ReadFrom([DisallowNull] BinaryReader source)
        {
            base.ReadFrom(source);
            _id = source.ReadInt64();
        }


        public override void AssignTo([DisallowNull] BaseData<TEnum> target)
        {
            base.AssignTo(target);
            var other = (BaseDataInt64<TEnum>)target;
            other._id = _id;
        }

        public override bool Equals(Data.BaseData<TEnum>? other)
        {
            if (base.Equals(other))
            {
                var obj = (BaseDataInt64<TEnum>)other;
                if (obj._id != _id)
                {
                    return false;
                }
                return true;
            }
            return false;
        }
    }

    public abstract class BaseDataGuid<TEnum> : BaseData<TEnum> where TEnum : struct, System.Enum
    {
        Guid _id = default;

        public BaseDataGuid()
        { }

        public BaseDataGuid(ObjectState objectState, Guid id)
            : base(objectState) 
        {
            _id = id;
        }


        public Guid Id { get => _id; set => _id = value; }

        public override void WriteTo([DisallowNull] BinaryWriter destination)
        {
            base.WriteTo(destination);
            destination.Write(_id);
        }

        public override void ReadFrom([DisallowNull] BinaryReader source)
        {
            base.ReadFrom(source);
            _id = source.ReadGuid();
        }


        public override void AssignTo([DisallowNull] BaseData<TEnum> target)
        {
            base.AssignTo(target);
            var other = (BaseDataGuid<TEnum>)target;
            other._id = _id;
        }

        public override bool Equals(Data.BaseData<TEnum>? other)
        {
            if (base.Equals(other))
            {
                var obj = (BaseDataGuid<TEnum>)other;
                if (obj._id != _id)
                {
                    return false;
                }
                return true;
            }
            return false;
        }
    }
}
