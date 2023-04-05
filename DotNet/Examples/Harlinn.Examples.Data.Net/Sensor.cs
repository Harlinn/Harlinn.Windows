using System;

namespace Harlinn.Examples.Data.Net
{
    public class Sensor : Owned
    {
        public Sensor()
        {
        }

        public Sensor(Guid id, string name) 
            : base(id, name)
        {
        }

        public Sensor(Guid id, string name, Guid owner) 
            : base(id, name, owner)
        {
        }
    }






}
