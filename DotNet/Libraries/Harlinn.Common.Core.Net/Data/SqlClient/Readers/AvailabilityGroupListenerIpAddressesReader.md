# AvailabilityGroupListenerIpAddressesReader — reference

Overview

`AvailabilityGroupListenerIpAddressesReader` wraps [`sys.availability_group_listener_ip_addresses`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-availability-group-listener-ip-addresses-transact-sql) and exposes IP address configuration for availability group listeners.

Reader SQL

```
SELECT
  aglia.[listener_id],
  aglia.[ip_address],
  aglia.[ip_subnet_mask],
  aglia.[is_dhcp],
  aglia.[network_subnet_ip],
  aglia.[network_subnet_prefix_length],
  aglia.[network_subnet_ipv4_mask],
  aglia.[State],
  aglia.[state_desc]
FROM
  [sys].[availability_group_listener_ip_addresses] aglia
```

Selected columns (property mapping and brief meaning)

- `listener_id` ? property: `ListenerId` (string?)
  - Identifier for the AG listener.

- `ip_address` ? property: `IpAddress` (string?)
  - IP address assigned to the listener.

- `ip_subnet_mask` ? property: `IpSubnetMask` (string?)
  - Subnet mask for the IP address.

- `is_dhcp` ? property: `IsDhcp` (bool)
  - Whether the IP was assigned via DHCP.

- `network_subnet_ip` ? property: `NetworkSubnetIp` (string?)
  - Network subnet IP.

- `network_subnet_prefix_length` ? property: `NetworkSubnetPrefixLength` (int?)
  - Prefix length for the network subnet.

- `network_subnet_ipv4_mask` ? property: `NetworkSubnetIpv4Mask` (string?)
  - IPv4 subnet mask in dotted format.

- `State` ? property: `State` (byte?)
  - Numeric state code (listener IP state).

- `state_desc` ? property: `StateDesc` (string?)
  - Textual description of the state.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AvailabilityGroupListenerIpAddressesDataType` objects.
