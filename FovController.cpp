#include "main.hpp"
#include "ModConfig.hpp"
#include "FovController.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "UnityEngine/Camera.hpp"
#include "UnityEngine/Matrix4x4.hpp"

#include <cmath>

using namespace FovMod;

namespace {
    thread_local bool g_inHook = false;

    bool IsAlive(UnityEngine::Camera* cam) {
        return cam && cam->m_CachedPtr.m_value != nullptr;
    }

    bool IsMainCamera(UnityEngine::Camera* cam) {
        if (!IsAlive(cam)) return false;
        auto main = UnityEngine::Camera::get_main();
        return IsAlive(main) && main->m_CachedPtr.m_value == cam->m_CachedPtr.m_value;
    }
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
    if (!IsAlive(cam)) return;

    const float fov = GetTargetFov();

    g_inHook = true;
    cam->set_fieldOfView(fov);

    if (cam->get_stereoEnabled()) {
        auto proj = UnityEngine::Matrix4x4::Perspective(
            fov, cam->get_aspect(), cam->get_nearClipPlane(), cam->get_farClipPlane());
        cam->SetStereoProjectionMatrix(UnityEngine::Camera::StereoscopicEye::Left,  proj);
        cam->SetStereoProjectionMatrix(UnityEngine::Camera::StereoscopicEye::Right, proj);
    }
    g_inHook = false;
}

MAKE_HOOK_MATCH(Camera_set_fieldOfView,
                &UnityEngine::Camera::set_fieldOfView,
                void,
                UnityEngine::Camera* self, float value) {
    if (!g_inHook && getModConfig().Enabled.GetValue() && IsMainCamera(self)) {
        value = GetTargetFov();
    }
    Camera_set_fieldOfView(self, value);
}

void FovMod::InstallHooks() {
    INSTALL_HOOK(PaperLogger, Camera_set_fieldOfView);
}
