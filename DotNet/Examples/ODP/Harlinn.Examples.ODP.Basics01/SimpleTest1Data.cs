using System;

namespace Harlinn.Examples.ODP.Basics01
{
    class SimpleTest1Data : ICloneable, IEquatable<SimpleTest1Data>
    {
        long _id;
        long _optimisticLock;
        string _name;
        string _description;
        public SimpleTest1Data(long id, string name, string description = null)
        {
            _id = id;
            _name = name;
            _description = description;
        }
        public SimpleTest1Data(long id, long optimisticLock, string name, string description)
        {
            _id = id;
            _optimisticLock = optimisticLock;
            _name = name;
            _description = description;
        }

        public long Id { get => _id; }
        public long OptimisticLock { get => _optimisticLock; set => _optimisticLock = value; }
        public string Name { get => _name; set => _name = value; }
        public string Description { get => _description; set => _description = value; }

        public SimpleTest1Data Clone()
        {
            return new SimpleTest1Data(Id, OptimisticLock, Name, Description);
        }

        object ICloneable.Clone()
        {
            throw new NotImplementedException();
        }

        public override string ToString()
        {
            return $"Id:{Id}, OptimisticLock:{OptimisticLock}, Name:{Name}, Description:{Description}";
        }

        public bool Equals(SimpleTest1Data other)
        {
            return Id == other.Id &&
                OptimisticLock == other.OptimisticLock &&
                Name == other.Name &&
                Description == other.Description;
        }
    }
}
