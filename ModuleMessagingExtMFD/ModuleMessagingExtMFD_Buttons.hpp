// ==============================================================
//
//	ModuleMessagingExtMFD (Button Handling Headers)
//	==================================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================



#ifndef _SCRAM_ATT_BUTTON_CLASS
#define _SCRAM_ATT_BUTTON_CLASS
#include "MFDButtonPage.hpp"

class ModuleMessagingExtMFD;

class ModuleMessagingExtMFD_Buttons : public MFDButtonPage<ModuleMessagingExtMFD>
{
  public:
    ModuleMessagingExtMFD_Buttons();
  protected:
    bool SearchForKeysInOtherPages() const;
  private:
};
#endif // _SCRAM_ATT_BUTTON_CLASS

