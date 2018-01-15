// ==============================================================
//
//	ModuleMessagingExtMFD (MFD Button Management)
//	================================
//
//	Copyright (C) 2016-2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "MFDButtonPage.hpp"
#include "ModuleMessagingExtMFD_Buttons.hpp"
#include "ModuleMessagingExtMFD.hpp"


ModuleMessagingExtMFD_Buttons::ModuleMessagingExtMFD_Buttons() 
{
    // Orbit Mode
    static const MFDBUTTONMENU mnu0[] =
    {
      {"Mode Select", 0, 'M'},
      {"Prev Page", 0, 'P'},
      {"Next Page", 0, 'N'},
      {"Reset Activity Log", 0, 'R'}
    };
    RegisterPage(mnu0, sizeof(mnu0) / sizeof(MFDBUTTONMENU));
    RegisterFunction("MOD", OAPI_KEY_M, &ModuleMessagingExtMFD::Button_MOD);
    RegisterFunction("PRV", OAPI_KEY_P, &ModuleMessagingExtMFD::Button_PRV);
    RegisterFunction("NXT", OAPI_KEY_N, &ModuleMessagingExtMFD::Button_NXT);
    RegisterFunction("RST", OAPI_KEY_N, &ModuleMessagingExtMFD::Button_RST);

    return;
}

bool ModuleMessagingExtMFD_Buttons::SearchForKeysInOtherPages() const
{
    return false;
}