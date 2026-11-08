#include "main.hpp"
#include "ModConfig.hpp"
#include "FovController.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML-Lite.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/ViewController.hpp"

static void DidActivate(HMUI::ViewController* self, bool firstActivation,
                        bool addedToHierarchy, bool screenSystemDisabling) {
    if (!firstActivation) return;

    auto container = BSML::Lite::CreateScrollableSettingsContainer(self->get_transform());

    BSML::Lite::CreateToggle(container->get_transform(), "Enable FOV Override",
        getModConfig().Enabled.GetValue(),
        [](bool value) {
            getModConfig().Enabled.SetValue(value);
            if (value) FovMod::ApplyToMainCamera();
        });

    auto slider = BSML::Lite::CreateSliderSetting(
        container->get_transform(), "Field of View", 1.0f,
        FovMod::ClampFov(getModConfig().FieldOfView.GetValue()),
        FovMod::Constants::kMinFov, FovMod::Constants::kMaxFov,
        [](float value) {
            getModConfig().FieldOfView.SetValue(FovMod::ClampFov(value));
            FovMod::ApplyToMainCamera();
        });

    BSML::Lite::AddHoverHint(slider->get_gameObject(),
        "Camera field of view in degrees (60 - 120). Default: 90.");
}

void RegisterUI() {
    BSML::Init();
    BSML::Register::RegisterSettingsMenu("FOV", DidActivate);
}
