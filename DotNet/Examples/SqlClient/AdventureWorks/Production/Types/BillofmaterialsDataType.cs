using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class BillofmaterialsDataType
{
    int _billofmaterialsid = 0;
    int? _productassemblyid;
    int _componentid = 0;
    DateTime _startdate;
    DateTime? _enddate;
    string _unitmeasurecode = string.Empty;
    short _bomlevel = 0;
    decimal _perassemblyqty = 0m;
    DateTime _modifieddate;

    public BillofmaterialsDataType( )
    {
    }

    public BillofmaterialsDataType(int billofmaterialsid,
        int? productassemblyid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        _billofmaterialsid = billofmaterialsid;
        _productassemblyid = productassemblyid;
        _componentid = componentid;
        _startdate = startdate;
        _enddate = enddate;
        _unitmeasurecode = unitmeasurecode;
        _bomlevel = bomlevel;
        _perassemblyqty = perassemblyqty;
        _modifieddate = modifieddate;
    }

    public int Billofmaterialsid
    {
        get => _billofmaterialsid;
        set => _billofmaterialsid = value;
    }
    public int? Productassemblyid
    {
        get => _productassemblyid;
        set => _productassemblyid = value;
    }
    public int Componentid
    {
        get => _componentid;
        set => _componentid = value;
    }
    public DateTime Startdate
    {
        get => _startdate;
        set => _startdate = value;
    }
    public DateTime? Enddate
    {
        get => _enddate;
        set => _enddate = value;
    }
    public string Unitmeasurecode
    {
        get => _unitmeasurecode;
        set => _unitmeasurecode = value;
    }
    public short Bomlevel
    {
        get => _bomlevel;
        set => _bomlevel = value;
    }
    public decimal Perassemblyqty
    {
        get => _perassemblyqty;
        set => _perassemblyqty = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
