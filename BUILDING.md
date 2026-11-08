# Build from source

This repository branch includes the production source for **Road Rash: 30th Anniversary Edition Widescreen Mod** under `src/`. It does not include original game code, game assets, translations, or diagnostic tools.

## Requirements

- Windows
- Visual Studio x86 C++ build tools and Windows SDK
- PowerShell

## Build

From a repository checkout or an extracted source ZIP, run:

```powershell
powershell -File scripts/build.ps1
```

The default toolchain path is Visual Studio 18 Community. For another installation, provide the path to its x86 environment script:

```powershell
powershell -File scripts/build.ps1 -Vcvars32 "C:/path/to/VC/Auxiliary/Build/vcvars32.bat"
```

The resulting DLL and compiler dependency list are written to `build/`. This does not overwrite the validated `ddraw.dll` in the repository root or any installed game files. No game files or other project repositories are needed for compilation.

The four source files are `src/common.hpp`, `src/mod.cpp`, `src/proxy.cpp`, and `src/proxy.def`. The source snapshot matches the 0.2.2 implementation. Tests and internal audit records are maintained on the `develop` branch.

The root DLL is the rebuilt 0.2.2 artifact. Independent tests passed; real-game confirmation is pending. A local rebuild may have a different hash because of build metadata or compiler differences; a successful build alone does not establish real-game acceptance of that new binary.

For normal installation, use the included root DLL and follow `README.md`. A ZIP of the release branch includes that DLL along with the source and build instructions; compilation is optional.
