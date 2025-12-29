using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class SpecialofferDataType
{
    int _specialofferid = 0;
    string _description = string.Empty;
    decimal _discountpct = 0m;
    string _type = string.Empty;
    string _category = string.Empty;
    DateTime _startdate;
    DateTime _enddate;
    int _minqty = 0;
    int? _maxqty;
    Guid _rowguid;
    DateTime _modifieddate;

    public SpecialofferDataType( )
    {
    }

    public SpecialofferDataType(int specialofferid,
        string description,
        decimal discountpct,
        string type,
        string category,
        DateTime startdate,
        DateTime enddate,
        int minqty,
        int? maxqty,
        Guid rowguid,
        DateTime modifieddate)
    {
        _specialofferid = specialofferid;
        _description = description;
        _discountpct = discountpct;
        _type = type;
        _category = category;
        _startdate = startdate;
        _enddate = enddate;
        _minqty = minqty;
        _maxqty = maxqty;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Specialofferid
    {
        get => _specialofferid;
        set => _specialofferid = value;
    }
    public string Description
    {
        get => _description;
        set => _description = value;
    }
    public decimal Discountpct
    {
        get => _discountpct;
        set => _discountpct = value;
    }
    public string Type
    {
        get => _type;
        set => _type = value;
    }
    public string Category
    {
        get => _category;
        set => _category = value;
    }
    public DateTime Startdate
    {
        get => _startdate;
        set => _startdate = value;
    }
    public DateTime Enddate
    {
        get => _enddate;
        set => _enddate = value;
    }
    public int Minqty
    {
        get => _minqty;
        set => _minqty = value;
    }
    public int? Maxqty
    {
        get => _maxqty;
        set => _maxqty = value;
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
