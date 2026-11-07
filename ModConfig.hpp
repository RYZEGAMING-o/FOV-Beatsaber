#pragma once

#include "config-utils/shared/config-utils.hpp"

namespace FovMod::Constants {
    constexpr float kMinFov     = 60.0f;
    constexpr float kMaxFov     = 120.0f;
    constexpr float kDefaultFov = 90.0f;
}

DECLARE_CONFIG(ModConfig) {
    CONFIG_VALUE(Enabled,     bool,  "Enabled",     true);
    CONFIG_VALUE(FieldOfView, float, "FieldOfView", FovMod::Constants::kDefaultFov);
};
