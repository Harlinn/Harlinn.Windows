using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class DocumentDataType
{
    SqlHierarchyId _documentnode;
    short? _documentlevel;
    string _title = string.Empty;
    int _owner = 0;
    bool _folderflag = false;
    string _filename = string.Empty;
    string _fileextension = string.Empty;
    string _revision = string.Empty;
    int _changenumber = 0;
    byte _status = 0;
    string? _documentsummary;
    byte[]? _document;
    Guid _rowguid;
    DateTime _modifieddate;

    public DocumentDataType( )
    {
    }

    public DocumentDataType(SqlHierarchyId documentnode,
        short? documentlevel,
        string title,
        int owner,
        bool folderflag,
        string filename,
        string fileextension,
        string revision,
        int changenumber,
        byte status,
        string? documentsummary,
        byte[]? document,
        Guid rowguid,
        DateTime modifieddate)
    {
        _documentnode = documentnode;
        _documentlevel = documentlevel;
        _title = title;
        _owner = owner;
        _folderflag = folderflag;
        _filename = filename;
        _fileextension = fileextension;
        _revision = revision;
        _changenumber = changenumber;
        _status = status;
        _documentsummary = documentsummary;
        _document = document;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public SqlHierarchyId Documentnode
    {
        get => _documentnode;
        set => _documentnode = value;
    }
    public short? Documentlevel
    {
        get => _documentlevel;
        set => _documentlevel = value;
    }
    public string Title
    {
        get => _title;
        set => _title = value;
    }
    public int Owner
    {
        get => _owner;
        set => _owner = value;
    }
    public bool Folderflag
    {
        get => _folderflag;
        set => _folderflag = value;
    }
    public string Filename
    {
        get => _filename;
        set => _filename = value;
    }
    public string Fileextension
    {
        get => _fileextension;
        set => _fileextension = value;
    }
    public string Revision
    {
        get => _revision;
        set => _revision = value;
    }
    public int Changenumber
    {
        get => _changenumber;
        set => _changenumber = value;
    }
    public byte Status
    {
        get => _status;
        set => _status = value;
    }
    public string? Documentsummary
    {
        get => _documentsummary;
        set => _documentsummary = value;
    }
    public byte[]? Document
    {
        get => _document;
        set => _document = value;
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
