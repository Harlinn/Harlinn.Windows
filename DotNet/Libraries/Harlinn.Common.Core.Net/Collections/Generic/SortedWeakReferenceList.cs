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


using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;


namespace Harlinn.Common.Core.Net.Collections.Generic
{
    public class SortedWeakReferenceList<TKey,TValue> : IDictionary<TKey, WeakReference<TValue>>, IDictionary, IReadOnlyDictionary<TKey, WeakReference<TValue>> where TKey : notnull where TValue : class
    {
        readonly SortedListEx<TKey, WeakReference<TValue>> _entries = new SortedListEx<TKey, WeakReference<TValue>>();
        List<TKey> _emptyKeys = new List<TKey>();

        public SortedWeakReferenceList()
        {
        }


        void RemoveEmptyKeys()
        {
            var emptyKeyCount = _emptyKeys.Count;
            for(int i = 0; i < emptyKeyCount; i++)
            {
                _entries.Remove(_emptyKeys[i]);
            }
            _emptyKeys.Clear();
        }
        public bool From(TKey key, [DisallowNull] IList<TValue> result)
        {
            var index = _entries.IndexOfKeyEx(key);
            if(index < 0)
            {
                index = ~index;
                index++;
            }
            var values = _entries.Values;
            var keys = _entries.Keys;
            var count = _entries.Count;
            for(int i = index; i < count; i++ )
            {
                var weakReference = values[i];
                if(weakReference.TryGetTarget(out var target))
                {
                    result.Add(target);
                }
                else
                {
                    _emptyKeys.Add(keys[i]);
                }
            }
            RemoveEmptyKeys();
            return _entries.Count > 0;
        }

        public bool Until(TKey key, [DisallowNull] IList<TValue> result)
        {
            var index = _entries.IndexOfKeyEx(key);
            if (index < 0)
            {
                index = ~index;
                index++;
            }
            var values = _entries.Values;
            var keys = _entries.Keys;
            for (int i = 0; i < index; i++)
            {
                var weakReference = values[i];
                if (weakReference.TryGetTarget(out var target))
                {
                    result.Add(target);
                }
                else
                {
                    _emptyKeys.Add(keys[i]);
                }
            }

            RemoveEmptyKeys();
            return _entries.Count > 0;
        }


        public bool Over(TKey firstKey, TKey lastKey, [DisallowNull] IList<TValue> result)
        {
            var firstIndex = _entries.IndexOfKeyEx(firstKey);
            if (firstIndex < 0)
            {
                firstIndex = ~firstIndex;
                firstIndex++;
            }
            var lastIndex = _entries.IndexOfKeyEx(lastKey);
            if (lastIndex < 0)
            {
                lastIndex = ~lastIndex;
                lastIndex++;
            }
            var values = _entries.Values;
            var keys = _entries.Keys;
            var count = _entries.Count;
            for (int i = firstIndex; i < lastIndex; i++)
            {
                var weakReference = values[i];
                if (weakReference.TryGetTarget(out var target))
                {
                    result.Add(target);
                }
                else
                {
                    _emptyKeys.Add(keys[i]);
                }
            }

            RemoveEmptyKeys();
            return _entries.Count > 0;
        }


        public bool All([DisallowNull] IList<TValue> result)
        {
            var values = _entries.Values;
            var keys = _entries.Keys;
            var count = _entries.Count;
            for (int i = 0; i < count; i++)
            {
                var weakReference = values[i];
                if (weakReference.TryGetTarget(out var target))
                {
                    result.Add(target);
                }
                else
                {
                    _emptyKeys.Add(keys[i]);
                }
            }
            RemoveEmptyKeys();
            return _entries.Count > 0;
        }


        public WeakReference<TValue> this[TKey key] { get => ((IDictionary<TKey, WeakReference<TValue>>)_entries)[key]; set => ((IDictionary<TKey, WeakReference<TValue>>)_entries)[key] = value; }
        object? IDictionary.this[object key] { get => ((IDictionary<TKey, WeakReference<TValue>>)_entries)[(TKey)key]; set => ((IDictionary<TKey, WeakReference<TValue>>)_entries)[(TKey)key] = (WeakReference<TValue>)value; }

        public ICollection<TKey> Keys => ((IDictionary<TKey, WeakReference<TValue>>)_entries).Keys;

        public ICollection<WeakReference<TValue>> Values => ((IDictionary<TKey, WeakReference<TValue>>)_entries).Values;

        public int Count => ((ICollection<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).Count;

        public bool IsReadOnly => ((ICollection<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).IsReadOnly;

        bool IDictionary.IsFixedSize => ((IDictionary)_entries).IsFixedSize;

        ICollection IDictionary.Keys => ((IDictionary)_entries).Keys;

        IEnumerable<TKey> IReadOnlyDictionary<TKey, WeakReference<TValue>>.Keys => ((IReadOnlyDictionary<TKey, WeakReference<TValue>>)_entries).Keys;

        ICollection IDictionary.Values => ((IDictionary)_entries).Values;

        IEnumerable<WeakReference<TValue>> IReadOnlyDictionary<TKey, WeakReference<TValue>>.Values => ((IReadOnlyDictionary<TKey, WeakReference<TValue>>)_entries).Values;

        bool ICollection.IsSynchronized => ((IDictionary)_entries).IsSynchronized;

        object ICollection.SyncRoot => ((IDictionary)_entries).SyncRoot;

        public void Add(TKey key, WeakReference<TValue> value)
        {
            ((IDictionary<TKey, WeakReference<TValue>>)_entries).Add(key, value);
        }

        public void Add(TKey key, TValue value)
        {
            ((IDictionary<TKey, WeakReference<TValue>>)_entries).Add(key, new WeakReference<TValue>(value));
        }

        public void Add(KeyValuePair<TKey, WeakReference<TValue>> item)
        {
            ((ICollection<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).Add(item);
        }

        public void Clear()
        {
            ((ICollection<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).Clear();
        }

        public bool Contains(KeyValuePair<TKey, WeakReference<TValue>> item)
        {
            return ((ICollection<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).Contains(item);
        }

        public bool ContainsKey(TKey key)
        {
            return ((IDictionary<TKey, WeakReference<TValue>>)_entries).ContainsKey(key);
        }

        public void CopyTo(KeyValuePair<TKey, WeakReference<TValue>>[] array, int arrayIndex)
        {
            ((ICollection<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).CopyTo(array, arrayIndex);
        }

        public IEnumerator<KeyValuePair<TKey, WeakReference<TValue>>> GetEnumerator()
        {
            return ((IEnumerable<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).GetEnumerator();
        }

        public bool Remove(TKey key)
        {
            return ((IDictionary<TKey, WeakReference<TValue>>)_entries).Remove(key);
        }

        public bool Remove(KeyValuePair<TKey, WeakReference<TValue>> item)
        {
            return ((ICollection<KeyValuePair<TKey, WeakReference<TValue>>>)_entries).Remove(item);
        }

        public bool TryGetValue(TKey key, [MaybeNullWhen(false)] out WeakReference<TValue> value)
        {
            return ((IDictionary<TKey, WeakReference<TValue>>)_entries).TryGetValue(key, out value);
        }

        void IDictionary.Add(object key, object? value)
        {
            ((IDictionary)_entries).Add(key, value);
        }

        bool IDictionary.Contains(object key)
        {
            return ((IDictionary)_entries).Contains(key);
        }

        void ICollection.CopyTo(Array array, int index)
        {
            ((IDictionary)_entries).CopyTo(array, index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)_entries).GetEnumerator();
        }

        IDictionaryEnumerator IDictionary.GetEnumerator()
        {
            return ((IDictionary)_entries).GetEnumerator();
        }

        void IDictionary.Remove(object key)
        {
            ((IDictionary)_entries).Remove(key);
        }



    }
}
