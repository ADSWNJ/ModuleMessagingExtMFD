// ==============================================================
//
//	ModuleMessagingExtMFD (Button Handling Code)
//	============================================
//
//	Copyright (C) 2016-2018	Andrew (ADSWNJ) Stokes
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

// MOD = Mode Select
void ModuleMessagingExtMFD::Button_MOD() {
  LC->mode = 1 - LC->mode;
  return;
};

// PRV = Last Page (Vars)
void ModuleMessagingExtMFD::Button_PRV() {
  unsigned int *p = (LC->mode == 0 ? &(GC->ofsV) : &(GC->ofsA));
  const vector<string> *vec = (LC->mode == 0 ? &(GC->mmDumpVesTyp) : &(GC->mmActL1));
  if (*p > 0) *p -= 10;
  while (*p >= vec->size()) *p -= 10;
  return;
};

// NXT = Next Page (Vars)
void ModuleMessagingExtMFD::Button_NXT() {
  unsigned int *p = (LC->mode == 0 ? &(GC->ofsV) : &(GC->ofsA));
  const vector<string> *vec = (LC->mode == 0 ? &(GC->mmDumpVesTyp) : &(GC->mmActL1));
  *p += 10;
  while (*p >= vec->size()) *p -= 10;
  return;
};

// RST = Reset Activity log
void ModuleMessagingExtMFD::Button_RST() {
  GC->mm.RstLog();
  return;
};

// FNT = Toggle Font Size
void ModuleMessagingExtMFD::Button_FNT() {
  LC->fontsize = 1 - LC->fontsize;
  return;
};
