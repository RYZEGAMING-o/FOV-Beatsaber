# FovMod (Beat Saber 1.40.8, Quest)

1. Edit `packageVersion` in `mod.template.json` to the exact 1.40.8 build tag (`qpm package list`).
2. Set ANDROID_NDK_HOME (r26+); install qpm, cmake, ninja.
3. Run `bash scripts/build.sh` -> produces `FovMod.qmod`.
4. Install the .qmod via QuestPatcher / ScoreSaber modding tool.

In game: Settings > Mods > FOV.

Note: on Quest the HMD projection comes from the XR runtime; the mod overrides the
main camera FOV and stereo projection, but the in-headset effect can be subtle.
If questui does not resolve for 1.40.8, switch UI.cpp to BSML.

## No local setup: build on GitHub
Push this folder to a new GitHub repo -> Actions tab -> "Build qmod" -> download the
`FovMod.qmod` artifact (unzip it once; the .qmod inside is what MBF wants).
