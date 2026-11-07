#include "main.hpp"
#include "ModConfig.hpp"
#include "FovController.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/ViewController.hpp"

using namespace QuestUI;

static void DidActivate(HMUI::ViewController* self, bool firstActivation,
                        bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    auto parent = BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

    BeatSaberUI::CreateToggle(parent->get_transform(), "Enable FOV Override",
        getModConfig().Enabled.GetValue(),
        [](bool value) {
            getModConfig().Enabled.SetValue(value);
            if (value) FovMod::ApplyToMainCamera();
        });

    auto slider = BeatSaberUI::CreateSliderSetting(
        parent->get_transform(), "Field of View", 1.0f,
        FovMod::ClampFov(getModConfig().FieldOfView.GetValue()),
        FovMod::Constants::kMinFov, FovMod::Constants::kMaxFov,
        [](float value) {
            getModConfig().FieldOfView.SetValue(FovMod::ClampFov(value));
            FovMod::ApplyToMainCamera();
        });

    BeatSaberUI::AddHoverHint(slider->get_gameObject(),
        "Camera field of view in degrees (60 - 120). Default: 90.");

    BeatSaberUI::CreateUIButton(parent->get_transform(), "Reset to 90",
        [slider]() {
            getModConfig().FieldOfView.SetValue(FovMod::Constants::kDefaultFov);
            slider->set_Value(FovMod::Constants::kDefaultFov);
            FovMod::ApplyToMainCamera();
        });
}

void RegisterUI() {
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController(
        ModInfo{MOD_ID, VERSION}, "FOV", DidActivate);
}
