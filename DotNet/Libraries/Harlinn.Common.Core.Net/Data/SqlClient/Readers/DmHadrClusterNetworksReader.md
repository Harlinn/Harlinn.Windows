# DmHadrClusterNetworksReader — reference

Overview

`DmHadrClusterNetworksReader` wraps `sys.dm_hadr_cluster_networks` and reports cluster network subnets, masks and whether they are public or IPv4.

Reader SQL

```
SELECT
  dhcn.[member_name],
  dhcn.[network_subnet_ip],
  dhcn.[network_subnet_ipv4_mask],
  dhcn.[network_subnet_prefix_length],
  dhcn.[is_public],
  dhcn.[is_ipv4]
FROM
  [sys].[dm_hadr_cluster_networks] dhcn
```

Columns and interpretation

- `member_name` ? cluster member name.
- `network_subnet_ip` ? subnet IP string.
- `network_subnet_ipv4_mask` ? IPv4 mask string (nullable).
- `network_subnet_prefix_length` ? prefix length for subnet.
- `is_public` ? whether the network is public.
- `is_ipv4` ? whether the network is IPv4.

How to interpret

- Use subnet information to map networking topologies used by the cluster and AG communication.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrClusterNetworksReader.Sql;
using var rdr = cmd.ExecuteReader();
var n = new DmHadrClusterNetworksReader(rdr, ownsReader:false);
while (n.Read())
{
    Console.WriteLine($"Member:{n.MemberName} Subnet:{n.NetworkSubnetIp}/{n.NetworkSubnetPrefixLength} Public:{n.IsPublic} IPv4:{n.IsIpv4}");
}
```

See also:

- [sys.dm_hadr_cluster_networks](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-cluster-networks)
