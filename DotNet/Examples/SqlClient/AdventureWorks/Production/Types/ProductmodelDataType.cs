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

public class ProductmodelDataType
{
    int _productmodelid = 0;
    string _name = string.Empty;
    SqlXml? _catalogdescription;
    SqlXml? _instructions;
    Guid _rowguid;
    DateTime _modifieddate;

    public ProductmodelDataType( )
    {
    }

    public ProductmodelDataType(int productmodelid,
        string name,
        SqlXml? catalogdescription,
        SqlXml? instructions,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productmodelid = productmodelid;
        _name = name;
        _catalogdescription = catalogdescription;
        _instructions = instructions;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productmodelid
    {
        get => _productmodelid;
        set => _productmodelid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public SqlXml? Catalogdescription
    {
        get => _catalogdescription;
        set => _catalogdescription = value;
    }
    public SqlXml? Instructions
    {
        get => _instructions;
        set => _instructions = value;
    }
    public Guid Rowguid
    {
        get => _rowguid;
        set => _rowguid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
