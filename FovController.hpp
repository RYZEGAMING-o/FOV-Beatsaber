#pragma once

namespace FovMod {
    float ClampFov(float value);
    float GetTargetFov();
    void ApplyToMainCamera();
    void InstallHooks();
}
