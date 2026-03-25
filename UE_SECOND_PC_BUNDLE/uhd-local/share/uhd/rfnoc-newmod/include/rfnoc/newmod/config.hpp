//
// Copyright 2025 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <uhd/config.hpp>

// See uhd/config.hpp for more information on these macros
#ifdef RFNOC_NEWMOD_STATIC_LIB
#    define RFNOC_NEWMOD_API
#    define RFNOC_NEWMOD_API_HEADER
#else
#    ifdef RFNOC_NEWMOD_DLL_EXPORTS
#        define RFNOC_NEWMOD_API        UHD_EXPORT
#        define RFNOC_NEWMOD_API_HEADER UHD_EXPORT_HEADER
#    else
#        define RFNOC_NEWMOD_API        UHD_IMPORT
#        define RFNOC_NEWMOD_API_HEADER UHD_IMPORT_HEADER
#    endif // RFNOC_NEWMOD_DLL_EXPORTS
#endif // RFNOC_NEWMOD_STATIC_LIB
