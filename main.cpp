#include "main.hpp"
#include "ModConfig.hpp"
#include "FovController.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

DEFINE_CONFIG(ModConfig);

void RegisterUI();

MOD_EXPORT_FUNC void setup(CModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo.assign(info);

    getModConfig().Init(modInfo);
    FOV_LOG_INFO("FovMod setup complete");
}

MOD_EXPORT_FUNC void late_load() {
    il2cpp_functions::Init();
    RegisterUI();
    FovMod::InstallHooks();
    FOV_LOG_INFO("FovMod loaded, target FOV {}", FovMod::GetTargetFov());
}
