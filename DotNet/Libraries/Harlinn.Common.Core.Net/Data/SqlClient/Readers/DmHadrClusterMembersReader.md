# DmHadrClusterMembersReader — reference

Overview

`DmHadrClusterMembersReader` wraps `sys.dm_hadr_cluster_members` and lists cluster members with their types, states and quorum votes.

Reader SQL

```
SELECT
  dhcm.[member_name],
  dhcm.[member_type],
  dhcm.[member_type_desc],
  dhcm.[member_state],
  dhcm.[member_state_desc],
  dhcm.[number_of_quorum_votes]
FROM
  [sys].[dm_hadr_cluster_members] dhcm
```

Columns and interpretation

- `member_name` ? cluster member name.
- `member_type` / `member_type_desc` ? member type and description.
- `member_state` / `member_state_desc` ? current state and description.
- `number_of_quorum_votes` ? quorum votes assigned to the member.

How to interpret

- Use `member_state_desc` and quorum votes to assess cluster membership and quorum configuration.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrClusterMembersReader.Sql;
using var rdr = cmd.ExecuteReader();
var m = new DmHadrClusterMembersReader(rdr, ownsReader:false);
while (m.Read())
{
    Console.WriteLine($"Member:{m.MemberName} Type:{m.MemberTypeDesc} State:{m.MemberStateDesc} Votes:{m.NumberOfQuorumVotes}");
}
```

See also:

- [sys.dm_hadr_cluster_members](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-cluster-members)
