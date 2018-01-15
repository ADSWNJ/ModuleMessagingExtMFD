// ==========================================================================
//
//	ModuleMessagingExtMFD (Local (Vessel+MFD Panel) Core Persistence)
//	================================================
//
//	Copyright (C) 2016-2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==========================================================================

#include "ModuleMessagingExtMFD_GCore.hpp"
#include "ModuleMessagingExtMFD_VCore.hpp"
#include "ModuleMessagingExtMFD_LCore.hpp"

ModuleMessagingExtMFD_LCore::ModuleMessagingExtMFD_LCore(VESSEL *vin, UINT mfdin, ModuleMessagingExtMFD_GCore* gcin) {
  GC = gcin;
  v = vin;
  m = mfdin;

  VC = (ModuleMessagingExtMFD_VCore*) GC->P.findVC(v);

  showMessage = false;
  okMessagePage = true;
  mode = 0;
  return;
}
