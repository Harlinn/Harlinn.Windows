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
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Examples.Data.Net
{
    public interface IDataContext
    {
        CatalogItem GetCatalogItem(Guid itemId);
        Dictionary<Guid, CatalogItem> GetCatalogItems(Guid ownerId);
        Dictionary<Guid, CatalogItem> GetAllCatalogItems();

        Catalog CreateOrRetrieveCatalog(Guid ownerId, string catalogName);
        Asset CreateOrRetrieveAsset(Guid ownerId, string assetName);
        bool DeleteCatalogItem(Guid itemId);

        Sensor GetSensor(Guid sensorId);
        Dictionary<Guid, Sensor> GetSensors(Guid assetId);
        Dictionary<Guid, Sensor> GetAllSensors();

        Sensor CreateOrRetrieveSensor(Guid assetId, string sensorName);
        bool DeleteSensor(Guid sensorId);

        SensorPoint[] GetSensorPoints(Guid sensorId, DateTime intervalStart, DateTime intervalEnd);
        SensorPoint[] GetAllSensorPoints(Guid sensorId);

        void StoreSensorValue( SensorValue sensorValue );
        void StoreSensorPoints(Guid sensorId, SensorPoint[] sensorPoints );

        void ReplaceSensorPoints(Guid sensorId, DateTime intervalStart, DateTime intervalEnd, SensorPoint[] sensorPoints);

        SensorValue[] GetAllSensorValues();

    }
}
