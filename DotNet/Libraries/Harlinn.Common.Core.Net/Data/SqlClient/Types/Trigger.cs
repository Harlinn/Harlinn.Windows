/*
   Copyright 2024-2025 Espen Harlinn

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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

/// <summary>
/// Represents metadata information about a database trigger, including its name, type, parent object, and status flags.
/// </summary>
/// <remarks>
/// A trigger is a special type of stored procedure that automatically executes in response to certain
/// events on a database table or view. This class provides read-only access to key properties describing the trigger's
/// identity, type, parent object, creation and modification dates, and various status indicators. Instances of this
/// class are typically used to inspect or display trigger metadata retrieved from a database system catalog.
/// </remarks>
public class Trigger
{
    readonly string _name = string.Empty;
    readonly int _objectId = 0;
    readonly byte _parentClass = 0;
    readonly string? _parentClassDesc;
    readonly int _parentId = 0;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly bool _isMsShipped = false;
    readonly bool _isDisabled = false;
    readonly bool _isNotForReplication = false;
    readonly bool _isInsteadOfTrigger = false;

    public Trigger( )
    {
    }

    public Trigger(string name,
        int objectId,
        byte parentClass,
        string? parentClassDesc,
        int parentId,
        string type,
        string? typeDesc,
        DateTime createDate,
        DateTime modifyDate,
        bool isMsShipped,
        bool isDisabled,
        bool isNotForReplication,
        bool isInsteadOfTrigger)
    {
        _name = name;
        _objectId = objectId;
        _parentClass = parentClass;
        _parentClassDesc = parentClassDesc;
        _parentId = parentId;
        _type = type;
        _typeDesc = typeDesc;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _isMsShipped = isMsShipped;
        _isDisabled = isDisabled;
        _isNotForReplication = isNotForReplication;
        _isInsteadOfTrigger = isInsteadOfTrigger;
    }

    /// <summary>
    /// Trigger name. DML trigger names are schema-scoped. DDL trigger 
    /// names are scoped with respect to the parent entity.
    /// </summary>
    public string Name => _name;
    /// <summary>
    /// Object identification number. Is unique within a database.
    /// </summary>
    public int ObjectId => _objectId;
    /// <summary>
    /// Class of the parent of the trigger.
    /// <para>
    /// 0 = Database, for the DDL triggers.
    /// </para>
    /// <para>
    /// 1 = Object or column for the DML triggers.
    /// </para>
    /// </summary>
    public byte ParentClass => _parentClass;
    /// <summary>
    /// Description of the parent class of the trigger.
    /// <para>
    /// DATABASE
    /// </para>
    /// <para>
    /// OBJECT_OR_COLUMN
    /// </para>
    /// </summary>
    public string? ParentClassDesc => _parentClassDesc;
    /// <summary>
    /// ID of the parent of the trigger, as follows:
    /// <para>
    /// 0 = Triggers that are database-parented triggers.
    /// </para>
    /// <para>
    /// For DML triggers, this is the object_id of the table or view on which the DML trigger is defined.
    /// </para>
    /// </summary>
    public int ParentId => _parentId;
    /// <summary>
    /// Object type:
    /// <para>
    /// TA = Assembly (CLR) trigger
    /// </para>
    /// <para>
    /// TR = SQL trigger
    /// </para>
    /// </summary>
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public bool IsMsShipped => _isMsShipped;
    public bool IsDisabled => _isDisabled;
    public bool IsNotForReplication => _isNotForReplication;
    /// <summary>
    /// Gets a value indicating whether the trigger is defined as an INSTEAD OF trigger.
    /// </summary>
    /// <remarks>
    /// INSTEAD OF triggers override the default action for the triggering event, allowing custom
    /// logic to be executed instead. This property distinguishes between INSTEAD OF and AFTER
    /// triggers when handling database events.
    /// </remarks>
    public bool IsInsteadOfTrigger => _isInsteadOfTrigger;
}
