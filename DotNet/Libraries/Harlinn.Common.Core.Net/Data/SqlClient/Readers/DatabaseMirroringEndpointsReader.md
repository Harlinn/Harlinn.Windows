# DatabaseMirroringEndpointsReader — reference

Overview

`DatabaseMirroringEndpointsReader` wraps `sys.database_mirroring_endpoints` and exposes endpoint configuration used for database mirroring.

Reader SQL

```
SELECT
  dme.[Name],
  dme.[endpoint_id],
  dme.[principal_id],
  dme.[Protocol],
  dme.[protocol_desc],
  dme.[Type],
  dme.[type_desc],
  dme.[State],
  dme.[state_desc],
  dme.[is_admin_endpoint],
  dme.[Role],
  dme.[role_desc],
  dme.[is_encryption_enabled],
  dme.[connection_auth],
  dme.[connection_auth_desc],
  dme.[certificate_id],
  dme.[encryption_algorithm],
  dme.[encryption_algorithm_desc]
FROM
  [sys].[database_mirroring_endpoints] dme
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string): Endpoint name.
- `endpoint_id` ? `EndpointId` (int): Endpoint identifier.
- `principal_id` ? `PrincipalId` (int?): Principal id associated with endpoint.
- `Protocol` / `protocol_desc` ? protocol code and description.
- `Type` / `type_desc` ? endpoint type code and description.
- `State` / `state_desc` ? operational state and description.
- `is_admin_endpoint` ? `IsAdminEndpoint` (bool): Whether endpoint is an admin endpoint.
- `Role` / `role_desc` ? mirroring role and description.
- `is_encryption_enabled` ? `IsEncryptionEnabled` (bool): Encryption enabled flag.
- `connection_auth` / `connection_auth_desc` ? connection authentication method and description.
- `certificate_id` ? `CertificateId` (int): Certificate id used for endpoint security.
- `encryption_algorithm` / `encryption_algorithm_desc` ? encryption algorithm code and description.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseMirroringEndpointsDataType` objects.
