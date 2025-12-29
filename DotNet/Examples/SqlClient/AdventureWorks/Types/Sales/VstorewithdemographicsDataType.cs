using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class VstorewithdemographicsDataType
{
    readonly int _businessentityid = 0;
    readonly string _name = string.Empty;
    readonly decimal? _annualsales;
    readonly decimal? _annualrevenue;
    readonly string? _bankname;
    readonly string? _businesstype;
    readonly int? _yearopened;
    readonly string? _specialty;
    readonly int? _squarefeet;
    readonly string? _brands;
    readonly string? _internet;
    readonly int? _numberemployees;

    public VstorewithdemographicsDataType( )
    {
    }

    public VstorewithdemographicsDataType(int businessentityid,
        string name,
        decimal? annualsales,
        decimal? annualrevenue,
        string? bankname,
        string? businesstype,
        int? yearopened,
        string? specialty,
        int? squarefeet,
        string? brands,
        string? internet,
        int? numberemployees)
    {
        _businessentityid = businessentityid;
        _name = name;
        _annualsales = annualsales;
        _annualrevenue = annualrevenue;
        _bankname = bankname;
        _businesstype = businesstype;
        _yearopened = yearopened;
        _specialty = specialty;
        _squarefeet = squarefeet;
        _brands = brands;
        _internet = internet;
        _numberemployees = numberemployees;
    }

    public int Businessentityid => _businessentityid;
    public string Name => _name;
    public decimal? Annualsales => _annualsales;
    public decimal? Annualrevenue => _annualrevenue;
    public string? Bankname => _bankname;
    public string? Businesstype => _businesstype;
    public int? Yearopened => _yearopened;
    public string? Specialty => _specialty;
    public int? Squarefeet => _squarefeet;
    public string? Brands => _brands;
    public string? Internet => _internet;
    public int? Numberemployees => _numberemployees;
}
