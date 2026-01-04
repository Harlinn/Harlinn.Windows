using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class WorkorderDataType
{
    int _workorderid = 0;
    int _productid = 0;
    int _orderqty = 0;
    int _stockedqty = 0;
    short _scrappedqty = 0;
    DateTime _startdate;
    DateTime? _enddate;
    DateTime _duedate;
    short? _scrapreasonid;
    DateTime _modifieddate;

    public WorkorderDataType( )
    {
    }

    public WorkorderDataType(int workorderid,
        int productid,
        int orderqty,
        int stockedqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        short? scrapreasonid,
        DateTime modifieddate)
    {
        _workorderid = workorderid;
        _productid = productid;
        _orderqty = orderqty;
        _stockedqty = stockedqty;
        _scrappedqty = scrappedqty;
        _startdate = startdate;
        _enddate = enddate;
        _duedate = duedate;
        _scrapreasonid = scrapreasonid;
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
    public int Orderqty
    {
        get => _orderqty;
        set => _orderqty = value;
    }
    public int Stockedqty
    {
        get => _stockedqty;
        set => _stockedqty = value;
    }
    public short Scrappedqty
    {
        get => _scrappedqty;
        set => _scrappedqty = value;
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
    public DateTime Duedate
    {
        get => _duedate;
        set => _duedate = value;
    }
    public short? Scrapreasonid
    {
        get => _scrapreasonid;
        set => _scrapreasonid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
