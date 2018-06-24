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
void ModuleMessagingExtMFD::Button_MOD() {    // mode 0 = vars, 1 = avtivity, 2 = data
  if (++LC->mode == 3) LC->mode = 0;
  LC->entPerPage = (LC->mode == 2 ? 6 : 10);
  return;
};

// PRV = Last Page (Vars)
void ModuleMessagingExtMFD::Button_PRV() {
  int *p = (int*) (LC->mode == 1 ? &(GC->ofsA) : &(GC->ofsV));
  const vector<string> *vec = (LC->mode == 1 ? &(GC->mmActL1)  : &(GC->mmDumpVesTyp));
  if (*p > 0) *p -= LC->entPerPage;
  while (*p >= (int) vec->size()) {
    *p -= LC->entPerPage;
  }
  if (*p < 0) *p = 0;
  return;
};

// NXT = Next Page (Vars)
void ModuleMessagingExtMFD::Button_NXT() {
  int *p = (int*) (LC->mode == 1 ? &(GC->ofsA) : &(GC->ofsV));
  const vector<string> *vec = (LC->mode == 1 ? &(GC->mmActL1) : &(GC->mmDumpVesTyp));
  *p += LC->entPerPage;
  while (*p >= (int)vec->size()) {
    *p -= LC->entPerPage;
  }
  if (*p < 0) *p = 0;
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
