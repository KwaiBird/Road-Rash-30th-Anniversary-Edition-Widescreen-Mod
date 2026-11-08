# Road Rash: 30th Anniversary Edition Widescreen Mod

Version: 0.2.2

An unofficial widescreen mod for **Road Rash: 30th Anniversary Edition on Steam (Windows)**. It expands the horizontal view in single-player races while keeping the original vertical view and object proportions.

https://store.steampowered.com/app/2448570/

You must own and install the game separately.

## Install

1. Download a ZIP of the **release** branch. You can use **Code > Download ZIP** with the release branch selected, or **Source code (zip)** for a release/tag that includes `ddraw.dll`.
2. **Extract the ZIP** to a folder on your computer.
3. Close the game.
4. Open the game's installation folder from your Steam library: **Manage > Browse local files**.
5. Open the extracted folder and copy **the included `ddraw.dll`** into the same folder as **`RoadRash95.exe`**. You do not need to copy the source files or build scripts.
6. Start the game normally through Steam. No custom launcher or launch options are needed.
7. Select the game's **high-resolution (640x480)** display mode and start a single-player race.

`ddraw.dll` is the only additional file required to run the mod. The mod does not replace or patch the game EXE file on disk.

**If a `ddraw.dll` already exists, do not overwrite it without identifying it first.** This mod does not chain with other DirectDraw wrappers. Do not combine this mod with other launchers, including the old widescreen/diagnostic launcher, a 3D conversion launcher, or a translation launcher. Use normal Steam launch for this standalone version.

## What changes

- Race rendering expands from 640x480 to **852x480**, adding 106 pixels of scenery on each side.
- The HUD stays centered.
- Menus, videos, low-resolution mode, and network races retain the original display.
- The aspect ratio is fixed at 852:480. Small borders may remain on a 16:9 display; arbitrary ultrawide aspect ratios are not supported.
- A 4:3 window will have borders above and below the race image. Maximize the window or use fullscreen for a wider display.

## Compatibility and known limitations

The tested target is the Steam 30th Anniversary Edition. Other game versions are not supported. If the EXE or required hook locations do not match, the mod leaves widescreen disabled and forwards normal system DirectDraw calls.

Version 0.2.1 has been confirmed to initialize and render an 852x480 frame when launched normally through Steam. The renderer has also had limited play checks across several stages. This does not establish long-term stability across every course, mode, or system.

- Coarse textures on nearby slopes and occasional black terrain seams were also seen in the original game. The wider view may make them more noticeable.
- An occasional 4:3 screenshot and a hang when leaving a stage with Esc were reported during earlier testing. They did not recur in a later monitored session; their causes remain unresolved.
- Steam Overlay (**Shift+Tab**) and Steam screenshots (**F12**) also failed in a test with this mod removed. This mod does not add or restore those features.

## Check whether it loaded

The mod creates `Widescreen.log` in the game folder at runtime. No log file is included in the download.

These entries indicate successful initialization and the first widescreen frame:

```text
Widescreen 0.2.2 initialized
first Hor+ frame complete: 852x480, centred HUD
```

`unsupported EXE` means the game EXE did not match the supported build. `branch fingerprint mismatch` means a required hook location differed, for example because another mod changed it. The log includes the mismatched location and branch target.

For troubleshooting, the supported game EXE's SHA-256 is:

```text
9e40e25737149ab095061b7154797a35495faea97644fafc5a1e616f1400c968
```

## Uninstall

Close the game and remove **this mod's `ddraw.dll`** from the game folder. You may also remove `Widescreen.log` if you no longer need it. The mod does not change saves or settings.

## Build from source

The release branch includes both the source code and a ready-to-use DLL. For normal installation, use the included DLL; compilation is not required. If you want to build it yourself from a checkout or extracted source archive, see [BUILDING.md](BUILDING.md).

## Development and verification

OpenAI Codex was used to assist development. The mod author reviewed the changes and verification results, performed in-game testing, and is responsible for final release verification.

This package contains no game assets, extracted or decompiled game code, translations, fonts, launchers, or diagnostic tools.

## License

This mod is licensed under **0BSD (Zero-Clause BSD)**. See [LICENSE](LICENSE).

Game and third-party rights remain with their respective rights holders. Original game files, copied or decompiled game code, game assets, and separate third-party library binaries are not distributed here. Third-party components retain their own licenses.
