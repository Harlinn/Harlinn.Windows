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
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class WorkorderroutingDataType
{
    int _workorderid = 0;
    int _productid = 0;
    short _operationsequence = 0;
    short _locationid = 0;
    DateTime _scheduledstartdate;
    DateTime _scheduledenddate;
    DateTime? _actualstartdate;
    DateTime? _actualenddate;
    decimal? _actualresourcehrs;
    decimal _plannedcost = 0m;
    decimal? _actualcost;
    DateTime _modifieddate;

    public WorkorderroutingDataType( )
    {
    }

    public WorkorderroutingDataType(int workorderid,
        int productid,
        short operationsequence,
        short locationid,
        DateTime scheduledstartdate,
        DateTime scheduledenddate,
        DateTime? actualstartdate,
        DateTime? actualenddate,
        decimal? actualresourcehrs,
        decimal plannedcost,
        decimal? actualcost,
        DateTime modifieddate)
    {
        _workorderid = workorderid;
        _productid = productid;
        _operationsequence = operationsequence;
        _locationid = locationid;
        _scheduledstartdate = scheduledstartdate;
        _scheduledenddate = scheduledenddate;
        _actualstartdate = actualstartdate;
        _actualenddate = actualenddate;
        _actualresourcehrs = actualresourcehrs;
        _plannedcost = plannedcost;
        _actualcost = actualcost;
        _modifieddate = modifieddate;
    }

    public int Workorderid
    {
        get => _workorderid;
        set => _workorderid = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public short Operationsequence
    {
        get => _operationsequence;
        set => _operationsequence = value;
    }
    public short Locationid
    {
        get => _locationid;
        set => _locationid = value;
    }
    public DateTime Scheduledstartdate
    {
        get => _scheduledstartdate;
        set => _scheduledstartdate = value;
    }
    public DateTime Scheduledenddate
    {
        get => _scheduledenddate;
        set => _scheduledenddate = value;
    }
    public DateTime? Actualstartdate
    {
        get => _actualstartdate;
        set => _actualstartdate = value;
    }
    public DateTime? Actualenddate
    {
        get => _actualenddate;
        set => _actualenddate = value;
    }
    public decimal? Actualresourcehrs
    {
        get => _actualresourcehrs;
        set => _actualresourcehrs = value;
    }
    public decimal Plannedcost
    {
        get => _plannedcost;
        set => _plannedcost = value;
    }
    public decimal? Actualcost
    {
        get => _actualcost;
        set => _actualcost = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
