using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class VsalespersonsalesbyfiscalyearsDataType
{
    readonly int? _salespersonid;
    readonly string? _fullname;
    readonly string _jobtitle = string.Empty;
    readonly string _salesterritory = string.Empty;
    readonly decimal? _2002;
    readonly decimal? _2003;
    readonly decimal? _2004;

    public VsalespersonsalesbyfiscalyearsDataType( )
    {
    }

    public VsalespersonsalesbyfiscalyearsDataType(int? salespersonid,
        string? fullname,
        string jobtitle,
        string salesterritory,
        decimal? d_2002,
        decimal? d_2003,
        decimal? d_2004)
    {
        _salespersonid = salespersonid;
        _fullname = fullname;
        _jobtitle = jobtitle;
        _salesterritory = salesterritory;
        _2002 = d_2002;
        _2003 = d_2003;
        _2004 = d_2004;
    }

    public int? Salespersonid => _salespersonid;
    public string? Fullname => _fullname;
    public string Jobtitle => _jobtitle;
    public string Salesterritory => _salesterritory;
    public decimal? D_2002 => _2002;
    public decimal? D_2003 => _2003;
    public decimal? D_2004 => _2004;
}
