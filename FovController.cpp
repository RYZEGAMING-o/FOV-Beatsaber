#include "main.hpp"
#include "ModConfig.hpp"
#include "FovController.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "UnityEngine/Camera.hpp"

#include <cmath>

using namespace FovMod;

namespace {
    thread_local bool g_inHook = false;
}

float FovMod::ClampFov(float v) {
    if (std::isnan(v) || std::isinf(v)) return Constants::kDefaultFov;
    return std::fmin(Constants::kMaxFov, std::fmax(Constants::kMinFov, v));
}

float FovMod::GetTargetFov() {
    return ClampFov(getModConfig().FieldOfView.GetValue());
}

void FovMod::ApplyToMainCamera() {
    if (!getModConfig().Enabled.GetValue()) return;

    auto cam = UnityEngine::Camera::get_main();
    if (!cam) return;

    g_inHook = true;
    cam->set_fieldOfView(GetTargetFov());
    g_inHook = false;
}

MAKE_HOOK_MATCH(Camera_set_fieldOfView,
                &UnityEngine::Camera::set_fieldOfView,
                void,
                UnityEngine::Camera* self, float value) {
    if (!g_inHook && getModConfig().Enabled.GetValue()) {
        auto main = UnityEngine::Camera::get_main();
        if (main && self == main) {
            value = GetTargetFov();
        }
    }
    Camera_set_fieldOfView(self, value);
}

void FovMod::InstallHooks() {
    INSTALL_HOOK(PaperLogger, Camera_set_fieldOfView);
}
