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
      {"Mode", 0, 'M'},
      {"Prev", 0, 'P'},
      {"Next", 0, 'N'}
    };
    RegisterPage(mnu0, sizeof(mnu0) / sizeof(MFDBUTTONMENU));
    RegisterFunction("MOD", OAPI_KEY_M, &ModuleMessagingExtMFD::Button_MOD);
    RegisterFunction("PRV", OAPI_KEY_P, &ModuleMessagingExtMFD::Button_PRV);
    RegisterFunction("NXT", OAPI_KEY_N, &ModuleMessagingExtMFD::Button_NXT);


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