# Contributing to David's Windhawk mods

Thanks for helping. Bug reports, ideas and pull requests are all welcome.

## Reporting a bug

[Open an issue](https://github.com/DavidHiFi/davids-windhawk-mods/issues/new) and include:

- what you did, what you expected and what happened instead
- the mod's name and version, your Windhawk version and your Windows build (`winver`)
- a screenshot of the problem, and any error Windhawk shows when it compiles or loads the mod

Mods that break after a Windows or Windhawk update are the most useful reports.

## Suggesting a feature

Open an issue that describes what you want the mod to do and why. A screenshot or a mock-up helps.

## Sending a pull request

All changes go through pull requests against `main`.

1. Fork the repo and create a branch from `main`.
2. Install [Windhawk](https://windhawk.net). Edit the mod's `.wh.cpp` in `mods/local/<mod>/`.
3. Compile it in Windhawk: choose **Create a new mod**, paste the source and click **Compile**. Folders with a `Build.ps1` also build offline with Windhawk's bundled compiler:

   ```powershell
   powershell -ExecutionPolicy Bypass -File mods\local\<mod>\Build.ps1
   ```

   Shell Font Changer runs its regression tests with `Build.ps1 -Test`.
4. Test the change on your own PC, and keep every setting the mod's readme documents.
5. Bump `@version` in the mod header, and update the mod's readme if behavior changed.
6. Keep each pull request to one mod and one change, and say in the description how you tested it.

Leave `mods/catalog/`, `settings/` and `manifest.json` alone unless the change is about the snapshot itself. `tools\Build-Repo.ps1` regenerates them from a live install.

## License

By contributing, you agree that your work is released under the license of the mod you change: MIT ([LICENSE](LICENSE)) unless that mod's folder or `@license` header says otherwise.
