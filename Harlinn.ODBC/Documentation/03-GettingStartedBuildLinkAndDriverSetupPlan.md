# Chapter 3 — Getting Started: Build, Link, and Driver Setup (Development Plan)

Goal
- Provide step-by-step instructions to configure the development environment, build and link `Harlinn.ODBC`, and install/configure the Microsoft ODBC Driver for SQL Server so readers can compile and run examples.

Learning outcomes
- Configure Visual Studio projects to include and link `Harlinn.ODBC` headers and libraries.
- Choose and install the correct Microsoft ODBC driver for the target SQL Server and platform.
- Create and test DSNs and connection strings, including secure patterns (environment variables, config files).
- Build example projects (MSVC x64, C++23) and validate runtime connectivity to SQL Server.

Target audience and prerequisites
- Audience: C++ developers following Chapters 1–2 who need a working build and runtime environment.
- Prerequisites:
  - Visual Studio (recommended) and MSVC x64 toolset.
  - C++23 compiler support.
  - Administrative access for driver installation (when required).
  - Access to a SQL Server instance for testing (local or remote).

Chapter outline
1. Overview and goals — quick checklist.
2. Supported toolchains and target platforms.
   - MSVC x64 on Windows 10/11 (primary). Note other toolchains only if examples provided.
3. Project integration options
   - Direct Visual Studio solution integration (linking `Harlinn.ODBC` project).
   - Using prebuilt static/dynamic libs.
   - CMake guidance (brief) for those using CMake to drive MSVC builds.
4. Include and linker settings
   - Header include paths, preprocessor macros, required libraries (odbc32.lib, odbccp32.lib if needed), library search paths.
   - Debug vs Release differences.
5. Runtime dependencies
   - ODBC driver DLLs and driver manager provided by Windows (ODBC32). Pick correct Microsoft ODBC Driver for SQL Server (e.g., `ODBC Driver 18 for SQL Server`).
6. Installing Microsoft ODBC Driver for SQL Server
   - Link to download pages and brief install steps.
   - Choosing driver version: match SQL Server features (e.g., TLS, Time2 support).
7. DSN vs DSN-less connection strings
   - Examples of DSN and DSN-less strings; recommended secure practices.
   - Env var and config-file examples.
8. Connection string templates and common parameters
   - Server, Database, Authentication modes, Encrypt, TrustServerCertificate, MultiSubnetFailover, ApplicationIntent.
   - Example strings for SQL auth and integrated auth.
9. Testing connectivity
   - ODBCTest or `odbcad32.exe` DSN creation steps.
   - Minimal program to open connection and run `SELECT 1` (example skeleton).
10. Troubleshooting and common errors
   - Driver not found, architecture mismatch (x86 vs x64), TLS handshake failures, login failures.
11. Deliverables and artifact locations
   - Chapter markdown: `Harlinn.ODBC\Documentation\Chapters\03_GettingStartedBuildLinkAndDriverSetup.md`.
   - Example: `Examples\ODBC\DocsExamples\GettingStarted\BuildAndConnect\BuildAndConnect.cpp` and `README.md`.
   - CI/Local build script snippets for MSVC, optional CMake toolchain file.

MathJax formulas
- Compute wide-character bind size in bytes (reminder):

$$\text{bytes} = (\text{maxChars} + 1) \times \mathrm{sizeof}(\texttt{wchar\_t})$$

- SQLLEN size on platform (informational):

$$\text{SQLLEN\_size} = \mathrm{sizeof}(\texttt{SQLLEN}) = \begin{cases}4,&\text{32-bit}\\\n8,&\text{64-bit}\end{cases}$$

Mermaid diagrams

Build and link flow

```mermaid
flowchart TD
  A[Checkout repo] --> B[Open solution in Visual Studio]
  B --> C[Add project dependency: Harlinn.ODBC]
  C --> D[Set include paths and linker libs]
  D --> E[Build (MSVC x64, C++23)]
  E --> F[Run examples]
```

Driver selection and runtime check

```mermaid
flowchart LR
  G[Choose driver version] --> H[Install driver]
  H --> I[Verify architecture: x64]
  I --> J[Create DSN or DSN-less connection string]
  J --> K[Test connectivity: SELECT 1]
```

Implementation tasks (step-by-step)
1. Draft chapter markdown `Chapters\03_GettingStartedBuildLinkAndDriverSetup.md` with platform-specific instructions and screenshots placeholders.
2. Create example folder and files:
   - `Examples\ODBC\DocsExamples\GettingStarted\BuildAndConnect\BuildAndConnect.cpp` (reads `HODBC_TEST_CONN` env var, opens connection, executes `SELECT 1`).
   - `README.md` with step-by-step build and driver installation instructions.
3. Add Visual Studio project file for the example (use same settings as other examples) or provide CMakeLists.txt snippet.
4. Validate build on MSVC x64 and run the example using a valid connection string supplied via `HODBC_TEST_CONN` environment variable.
5. Add troubleshooting subsection with common errors and resolution steps.
6. Peer review and finalize the chapter; link it from `Harlinn.ODBC\Documentation\Readme.md`.

Key content snippets to include
- Typical DSN-less connection string examples (SQL auth and integrated auth):

  - SQL auth:

```
Driver={ODBC Driver 18 for SQL Server};Server=tcp:your_server,1433;Database=YourDb;UID=YourUser;PWD=YourPassword;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;
```

  - Integrated auth (Windows):

```
Driver={ODBC Driver 18 for SQL Server};Server=your_server;Database=YourDb;Trusted_Connection=yes;Encrypt=yes;TrustServerCertificate=no;
```

- MSVC linker libs:
  - `odbc32.lib`
  - optionally `odbccp32.lib` for legacy features

Troubleshooting checklist
- Ensure driver architecture matches binary (x64 app ? x64 driver).
- If `SQLDriverConnect` fails, check connection string quoting and semicolons.
- For TLS issues, check driver version and OS support for required TLS level.

Acceptance criteria
- Chapter file exists at `Chapters\03_GettingStartedBuildLinkAndDriverSetup.md` and is linked from the TOC.
- Example `BuildAndConnect.cpp` builds with MSVC x64 / C++23 and opens a connection when `HODBC_TEST_CONN` is set.
- Chapter includes downloadable driver link references, DSN and DSN-less examples, and troubleshooting guidance.

Estimated effort
- Draft chapter: 2–4 hours.
- Create example and validate: 1–2 hours (DB availability affects time).
- Review and polish: 1 hour.
- Total: 4–7 hours.

Repo rules and style
- Use C++23 for example code; follow XML-style `///` for public API snippets.
- Follow naming conventions and run `clang-format`/`clang-tidy` before committing.
- Use Boost.Test for any included tests and gate integration tests with `HODBC_TEST_CONN`.

Next steps
- If approved, create the chapter file and example code now.