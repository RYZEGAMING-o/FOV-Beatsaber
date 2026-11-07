#!/usr/bin/env bash
# One-command build: produces FovMod.qmod in the project root.
# Requires: qpm, cmake, ninja, Android NDK r26+ (ANDROID_NDK_HOME set).
set -euo pipefail
cd "$(dirname "$0")/.."

qpm restore
cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -B build
cmake --build ./build

qpm qmod build
qpm qmod zip FovMod.qmod
echo "Done: $(pwd)/FovMod.qmod"
