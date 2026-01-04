using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class IllustrationDataType
{
    int _illustrationid = 0;
    SqlXml? _diagram;
    DateTime _modifieddate;

    public IllustrationDataType( )
    {
    }

    public IllustrationDataType(int illustrationid,
        SqlXml? diagram,
        DateTime modifieddate)
    {
        _illustrationid = illustrationid;
        _diagram = diagram;
        _modifieddate = modifieddate;
    }

    public int Illustrationid
    {
        get => _illustrationid;
        set => _illustrationid = value;
    }
    public SqlXml? Diagram
    {
        get => _diagram;
        set => _diagram = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
