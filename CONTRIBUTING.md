# Contributing to Windhawk mods

Thanks for helping. Bug reports, ideas and pull requests are all welcome.

## Reporting a bug

[Open an issue](https://github.com/DavidHiFi/davids-windhawk-mods/issues/new) and include:

- what you did, what you expected and what happened instead
- your Windows build and your Windhawk version
- the mod's name and version, from the top of its `.wh.cpp` file
- a screenshot, if the problem is visual

## Suggesting a feature

Open an issue that describes what you want the mod to do and why. A screenshot or a mock-up helps.

## Sending a pull request

1. Fork the repo and create a branch from `main`.
2. Set up: install [Windhawk](https://windhawk.net), then choose **Create a new mod**, paste the mod's `.wh.cpp` file and click **Compile** to test your change. Windhawk compiles the mod on your PC, so there is no separate build step.
3. Before you push, check that the mod compiles in Windhawk with no errors. Check the metadata block too: each `// @...` line sits on its own line between `// ==WindhawkMod==` and `// ==/WindhawkMod==`.
4. Keep each pull request to one change, and say in the description how you tested it.

## Style

- Match the naming and layout of the mod you change.
- Update the mod's readme block (`// ==WindhawkModReadme==`) when its behavior changes.

## License

By contributing, you agree that your work is released under the license of the mod you change. Most mods here are [MIT](LICENSE). Mods that inherit a GPL or LGPL license keep it, as their README lists.
