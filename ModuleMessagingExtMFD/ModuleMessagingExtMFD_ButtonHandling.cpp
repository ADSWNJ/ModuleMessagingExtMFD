// ==============================================================
//
//	ModuleMessagingExtMFD (Button Handling Code)
//	===============================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "ModuleMessagingExtMFD.hpp"
#include <math.h>

// ==============================================================
// MFD button hooks to Button Page library
//
char* ModuleMessagingExtMFD::ButtonLabel (int bt)
{
	return LC->B.ButtonLabel(bt);
}

// Return button menus
int ModuleMessagingExtMFD::ButtonMenu (const MFDBUTTONMENU **menu) const
{
	return LC->B.ButtonMenu(menu);
}

// Return clicked button
bool ModuleMessagingExtMFD::ConsumeButton (int bt, int event) {
  return LC->B.ConsumeButton(this, bt, event);
}

// Return pressed keystroke
bool ModuleMessagingExtMFD::ConsumeKeyBuffered (DWORD key) {
  return LC->B.ConsumeKeyBuffered(this, key);
}



// ==============================================================
// MFD Button Handler Callbacks
//

// AP = AutoPilot On/Off
void ModuleMessagingExtMFD::Button_AP() {

  return;
};

// DN = Reduce Dyn Pressure Target
void ModuleMessagingExtMFD::Button_DN() {

  return;
};

// UP = Increase Dyn Pressure Target
void ModuleMessagingExtMFD::Button_UP() {

  return;
};
