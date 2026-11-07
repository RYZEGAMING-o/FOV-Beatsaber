#pragma once

#include "scotland2/shared/loader.hpp"
#include "paper2_scotland2/shared/logger.hpp"

inline constexpr auto PaperLogger = Paper::ConstLoggerContext(MOD_ID);

#define FOV_LOG_INFO(...)  PaperLogger.info(__VA_ARGS__)
#define FOV_LOG_ERROR(...) PaperLogger.error(__VA_ARGS__)
