// ==============================================================
//
//	ModuleMessagingExtMFD (MFD Button Management)
//	================================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
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
      {"AP On/Off", 0, 'A'},
      {"Tgt DP Down", 0, 'D'},
      {"Tgt DP Up", 0, 'U'}
    };
    RegisterPage(mnu0, sizeof(mnu0) / sizeof(MFDBUTTONMENU));
    RegisterFunction("AP", OAPI_KEY_M, &ModuleMessagingExtMFD::Button_AP);
    RegisterFunction("DN", OAPI_KEY_T, &ModuleMessagingExtMFD::Button_DN);
    RegisterFunction("UP", OAPI_KEY_R, &ModuleMessagingExtMFD::Button_UP);


    // LP Mode
    //static const MFDBUTTONMENU mnu1[] =
    //{
    //  { "Mode Select", 0, 'M' }
    //};
    //RegisterPage(mnu1, sizeof(mnu1) / sizeof(MFDBUTTONMENU));
    //RegisterFunction("MOD", OAPI_KEY_M, &ModuleMessagingExtMFD::Button_MOD);

    return;
}

bool ModuleMessagingExtMFD_Buttons::SearchForKeysInOtherPages() const
{
    return false;
}