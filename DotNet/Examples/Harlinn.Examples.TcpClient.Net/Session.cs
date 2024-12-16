using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using Harlinn.Examples.Data.Net;
using Harlinn.Common.Core.Net.IO;

namespace Harlinn.Examples.TcpClient.Net
{
    public enum RequestReplyType : byte
    {
        Unknown = 0,
        CreateSession,
        CloseSession,
        Fault,
        GetCatalogItem,
        GetCatalogItems,
        GetAllCatalogItems,
        CreateOrRetrieveCatalog,
        CreateOrRetrieveAsset,
        DeleteCatalogItem,
        GetSensor,
        GetSensors,
        GetAllSensors,
        CreateOrRetrieveSensor,
        DeleteSensor,
        GetSensorPoints,
        GetAllSensorPoints,
        StoreSensorValue,
        StoreSensorPoints,
        ReplaceSensorPoints,
        GetAllSensorValues,
        SendSensorPoints,
        SendJSON
    }
    public class Session : Data.Net.IDataContext, IDisposable
    {
        const ulong InvalidId = ~0UL;

        ulong _sessionId = InvalidId;
        ulong _requestCounter;

        System.IO.BufferedStream _bufferedStream;
        BinaryReader _reader;
        BinaryWriter _writer;
        System.Net.Sockets.TcpClient _client;
        object _syncObj = new object();
        private bool _disposedValue;

        BinaryReader Reader { get => _reader;  }
        BinaryWriter Writer { get => _writer;  }

        public Session()
        {
            _client = new System.Net.Sockets.TcpClient();
        }

        public Session(IPEndPoint localEP)
        {
            _client = new System.Net.Sockets.TcpClient(localEP);
        }

        public Session(AddressFamily family)
        {
            _client = new System.Net.Sockets.TcpClient(family);
        }

        public Session(string hostname, int port)
        {
            _client = new System.Net.Sockets.TcpClient(hostname, port);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposedValue)
            {
                try { Close(); }
                catch { }
                if (disposing)
                {
                    _reader?.Dispose();
                    _writer?.Dispose();
                    _bufferedStream?.Dispose();
                    _client.Dispose();
                }
                _disposedValue = true;
            }
        }

        ~Session()
        {
            Dispose(disposing: false);
        }

        public void Dispose()
        {
            // Do not change this code. 
            // Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }


        public void Close()
        {
            lock (_syncObj)
            {
                Disconnect();
                _client.Close();
            }
        }

        NetworkStream GetNetworkStream()
        {
            return _client.GetStream();
        }


        void InitializeSession(ulong id)
        {
            _sessionId = id;
            var networkStream = GetNetworkStream();

            _bufferedStream = new System.IO.BufferedStream(networkStream, ushort.MaxValue / 2);
            _reader = new BinaryReader(_bufferedStream, System.Text.Encoding.Default, true);
            _writer = new BinaryWriter(_bufferedStream, System.Text.Encoding.Default, true);
        }

        public void Connect()
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.CreateSession;

                var writer = new BinaryWriter(GetNetworkStream(), System.Text.Encoding.UTF8, true);
                writer.Write((byte)requestReplyType);
                writer.Flush();

                var reader = new BinaryReader(GetNetworkStream(), System.Text.Encoding.UTF8, true);
                var replyType = (RequestReplyType)reader.ReadByte();
                if (replyType == RequestReplyType.Fault)
                {
                    HandleFault(reader);
                }
                else
                {
                    var sessionId = reader.ReadUInt64();
                    InitializeSession(sessionId);
                }
            }
        }

        public void Disconnect()
        {
            lock (_syncObj)
            {
                if (_sessionId != InvalidId)
                {
                    const RequestReplyType requestReplyType = RequestReplyType.CloseSession;
                    var requestId = WriteRequest(requestReplyType);
                    ReadAndValidateReplyHeader(requestReplyType, requestId);

                    _sessionId = InvalidId;
                }
            }
        }


        ulong NewRequest()
        {
            _requestCounter++;
            return _requestCounter;
        }

        ulong WriteSessionHeader(RequestReplyType requestReplyType)
        {
            RequireValidSession();
            var requestId = NewRequest();
            var writer = Writer;
            writer.Write((byte)requestReplyType);
            writer.Write(_sessionId);
            writer.Write(requestId);
            return requestId;
        }

        ulong WriteRequest(RequestReplyType requestReplyType)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            writer.Flush();
            return result;
        }
        ulong WriteRequest(RequestReplyType requestReplyType, Guid id)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            writer.Write(id);
            writer.Flush();
            return result;
        }
        ulong WriteRequest(RequestReplyType requestReplyType, string text)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            writer.Write(text);
            writer.Flush();
            return result;
        }

        ulong WriteRequest(RequestReplyType requestReplyType, IReadWrite readWriteable)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            readWriteable.Write(writer);
            writer.Flush();
            return result;
        }


        ulong WriteRequest(RequestReplyType requestReplyType, Guid id, string name)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            writer.Write(id);
            writer.Write(name);
            writer.Flush();
            return result;
        }

        ulong WriteRequest(RequestReplyType requestReplyType, Guid id, DateTime instervalStart, DateTime instervalEnd)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            writer.Write(id);
            writer.Write(instervalStart);
            writer.Write(instervalEnd);
            writer.Flush();
            return result;
        }

        ulong WriteRequest(RequestReplyType requestReplyType, Guid id, DateTime instervalStart, DateTime instervalEnd, SensorPoint[] sensorPoints)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            writer.Write(id);
            writer.Write(instervalStart);
            writer.Write(instervalEnd);
            int count = sensorPoints.Length;
            writer.Write(count);
            for (int i = 0; i < count; ++i)
            {
                sensorPoints[i].Write(writer);
            }
            writer.Flush();
            return result;
        }

        ulong WriteRequest(RequestReplyType requestReplyType, Guid id, SensorPoint[] sensorPoints)
        {
            var result = WriteSessionHeader(requestReplyType);
            var writer = Writer;
            writer.Write(id);
            int count = sensorPoints.Length;
            writer.Write(count);
            for (int i = 0; i < count; ++i)
            {
                sensorPoints[i].Write(writer);
            }
            writer.Flush();
            return result;
        }


        void ReadAndValidateReplyHeader(RequestReplyType requestReplyType, ulong expectedRequestId)
        {
            var reader = Reader;
            var replyType = (RequestReplyType)reader.ReadByte();
            if (replyType != requestReplyType)
            {
                HandleInvalidReplyType(replyType, requestReplyType);
            }
            else if (replyType == RequestReplyType.Fault)
            {
                HandleFault(reader);
            }
            ulong sessionId = reader.ReadUInt64();
            if (sessionId != _sessionId)
            {
                var message = string.Format("Invalid session id: {0}, expected:{1} ", 
                    sessionId, _sessionId);
                throw new Exception(message);
            }
            ulong requestId = reader.ReadUInt64();
            if (requestId != expectedRequestId)
            {
                var message = string.Format("Invalid request id: {0}, expected:{1} ", 
                    requestId, expectedRequestId);
                throw new Exception(message);
            }
        }



        void HandleFault(BinaryReader reader)
        {
            var faultReply = new Types.FaultReply();
            faultReply.Read(reader);
            throw new Exception(faultReply.Message);
        }

        void HandleInvalidReplyType(RequestReplyType actualReplyType, RequestReplyType expectedReplyType)
        {
            throw new Exception("Invalid reply type");
        }


        void RequireValidSession()
        {
            if (_sessionId == InvalidId)
            {
                throw new Exception("Invalid session id");
            }
        }

        public CatalogItem GetCatalogItem(Guid itemId)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetCatalogItem;
                CatalogItem result = null;
                
                var requestId = WriteRequest(requestReplyType, itemId);
                ReadAndValidateReplyHeader(requestReplyType, requestId);

                var reader = Reader;
                var found = reader.ReadBoolean();
                if (found)
                {
                    result = CatalogItemFactory.Read(reader);
                }
                return result;
            }
        }

        public Dictionary<Guid, CatalogItem> GetCatalogItems(Guid ownerId)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetCatalogItems;
                Dictionary<Guid, CatalogItem> result = null;
                var requestId = WriteRequest(requestReplyType, ownerId);
                ReadAndValidateReplyHeader(requestReplyType, requestId);

                var reader = Reader;
                result = CatalogItemFactory.ReadDictionary(reader);
                return result;
            }
        }
        public Dictionary<Guid, CatalogItem> GetAllCatalogItems()
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetAllCatalogItems;
                Dictionary<Guid, CatalogItem> result = null;
                var requestId = WriteRequest(requestReplyType);
                ReadAndValidateReplyHeader(requestReplyType, requestId);

                var reader = Reader;
                result = CatalogItemFactory.ReadDictionary(reader);
                return result;
            }
        }

        public Catalog CreateOrRetrieveCatalog(Guid ownerId, string catalogName)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.CreateOrRetrieveCatalog;
                var requestId = WriteRequest(requestReplyType, ownerId, catalogName);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                CatalogItem.ReadKind(reader);
                var result = new Catalog();
                result.Read(reader);

                return result;
            }
        }
        public Asset CreateOrRetrieveAsset(Guid ownerId, string assetName)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.CreateOrRetrieveAsset;
                var requestId = WriteRequest(requestReplyType, ownerId, assetName);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                CatalogItem.ReadKind(reader);
                var result = new Asset();
                result.Read(reader);

                return result;
            }
        }

        public bool DeleteCatalogItem(Guid itemId)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.DeleteCatalogItem;
                var requestId = WriteRequest(requestReplyType, itemId);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var result = reader.ReadBoolean();
                return result;
            }
        }

        public Sensor GetSensor(Guid sensorId)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetSensor;
                var requestId = WriteRequest(requestReplyType, sensorId);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var found = reader.ReadBoolean();
                if (found)
                {
                    var result = new Sensor();
                    result.Read(reader);
                    return result;
                }
                else
                {
                    return null;
                }

            }
        }

        public Dictionary<Guid, Sensor> GetSensors(Guid assetId)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetSensors;
                var requestId = WriteRequest(requestReplyType, assetId);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var count = reader.ReadInt32();
                var result = new Dictionary<Guid, Sensor>(count);
                for (int i = 0; i < count; ++i)
                {
                    var item = new Sensor();
                    item.Read(reader);
                    result.Add(item.Id, item);
                }
                return result;
            }
        }
        public Dictionary<Guid, Sensor> GetAllSensors()
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetAllSensors;
                var requestId = WriteRequest(requestReplyType);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var count = reader.ReadInt32();
                var result = new Dictionary<Guid, Sensor>(count);
                for (int i = 0; i < count; ++i)
                {
                    var item = new Sensor();
                    item.Read(reader);
                    result.Add(item.Id, item);
                }
                return result;
            }
        }

        public Sensor CreateOrRetrieveSensor(Guid assetId, string sensorName)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.CreateOrRetrieveSensor;
                var requestId = WriteRequest(requestReplyType, assetId, sensorName);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var result = new Sensor();
                result.Read(reader);

                return result;
            }
        }

        public bool DeleteSensor(Guid sensorId)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.DeleteSensor;
                var requestId = WriteRequest(requestReplyType, sensorId);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var result = reader.ReadBoolean();
                return result;
            }
        }

        public SensorPoint[] GetSensorPoints(Guid sensorId, DateTime intervalStart, DateTime intervalEnd)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetSensorPoints;
                var requestId = WriteRequest(requestReplyType, sensorId, intervalStart, intervalEnd);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var count = reader.ReadInt32();
                var result = new SensorPoint[count];
                for (int i = 0; i < count; i++)
                {
                    result[i].Read(reader);
                }
                return result;
            }
        }

        public SensorPoint[] GetAllSensorPoints(Guid sensorId)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetAllSensorPoints;
                var requestId = WriteRequest(requestReplyType, sensorId);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var count = reader.ReadInt32();
                var result = new SensorPoint[count];
                for (int i = 0; i < count; i++)
                {
                    result[i].Read(reader);
                }
                return result;
            }
        }
    

        public void StoreSensorValue(SensorValue sensorValue)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.StoreSensorValue;

                var requestId = WriteRequest(requestReplyType, sensorValue);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
            }
        }
        public void StoreSensorPoints(Guid sensorId, SensorPoint[] sensorPoints)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.StoreSensorPoints;
                var requestId = WriteRequest(requestReplyType, sensorId, sensorPoints);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
            }
        }


        public void ReplaceSensorPoints(Guid sensorId, DateTime intervalStart, DateTime intervalEnd, SensorPoint[] sensorPoints)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.ReplaceSensorPoints;
                var requestId = WriteRequest(requestReplyType, sensorId, intervalStart, intervalEnd, sensorPoints);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
            }
        }

        public SensorValue[] GetAllSensorValues()
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.GetAllSensorValues;
                var requestId = WriteRequest(requestReplyType);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
                var reader = Reader;
                var count = reader.ReadInt32();
                var result = new SensorValue[count];
                for (int i = 0; i < count; i++)
                {
                    result[i].Read(reader);
                }
                return result;
            }
        }


        public void SendSensorPoints(Guid sensorId, SensorPoint[] sensorPoints)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.SendSensorPoints;
                var requestId = WriteRequest(requestReplyType, sensorId, sensorPoints);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
            }
        }

        public void SendJSON(string json)
        {
            lock (_syncObj)
            {
                const RequestReplyType requestReplyType = RequestReplyType.SendJSON;
                var requestId = WriteRequest(requestReplyType, json);
                ReadAndValidateReplyHeader(requestReplyType, requestId);
            }
        }


    }
}
