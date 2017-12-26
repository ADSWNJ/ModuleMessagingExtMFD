// =====================================================================//
//	ModuleMessagingExtMFD
//	=====================
//
//	Copyright (C) 2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	Description:
//
//	This MFD monitors activity inside MMExt2. It does not need to run
//  to allow other modules to communicate ... it is purely monitoring. 
//
//	Copyright Notice: 
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	For full licencing terms, pleaserefer to the GNU General Public License
//	(gpl-3_0.txt) distributed with this release, or see
//	http://www.gnu.org/licenses/.
//
//
//	Credits:
//	
//	Orbiter Simulator	(c) 2003-2017 Martin (Martins) Schweiger
// 	MFDButtonPage		(c) 2012-2017 Szymon (Enjo) Ender
//	
//
//	Release History:
//
//  V1.00	Initial Release
// ======================================================================

#define STRICT
#define ORBITER_MODULE

#include "windows.h"
#include "orbitersdk.h"
#include "ModuleMessagingExtMFD.hpp"
#include "ModuleMessagingExtMFD_GCore.hpp"
#include "ModuleMessagingExtMFD_VCore.hpp"
#include "ModuleMessagingExtMFD_LCore.hpp"
#include "MFDPersist.hpp"

// ====================================================================================================================
// Global variables

ModuleMessagingExtMFD_GCore *g_SC = nullptr;    // points to the static persistence core

// ====================================================================================================================
// MFD class implementation

// Constructor executes on any F8, any resize of an ExtMFD, or any vessel switch
ModuleMessagingExtMFD::ModuleMessagingExtMFD (DWORD w, DWORD h, VESSEL *vessel, UINT mfd)
: MFD2 (w, h, vessel)
{
  if (g_SC == nullptr) {
    g_SC = new ModuleMessagingExtMFD_GCore();
    GC = g_SC;
  }
  GC = g_SC;


  VC = (ModuleMessagingExtMFD_VCore*) GC->P.findVC(vessel);		  // Locate our vessel core
  if (!VC) {
    VC = new ModuleMessagingExtMFD_VCore(vessel, GC);				    // ... if missing, initialize it.
    GC->P.addVC(vessel, VC);
  }

  LC = (ModuleMessagingExtMFD_LCore*) GC->P.findLC(vessel, mfd);	// Locate our local (vessl+MFD position) core
  if (!LC) {
    LC = new ModuleMessagingExtMFD_LCore(vessel, mfd, GC);			  // ... if missing, initialize it.
    GC->P.addLC(vessel, mfd, LC);
  }

  // Any construction for the display side of this MFD instance
  font = oapiCreateFont (h/25, true, "Fixed", FONT_NORMAL, 0);

  return;
}

ModuleMessagingExtMFD::~ModuleMessagingExtMFD ()
{
  oapiReleaseFont(font);
  return;
}





// ====================================================================================================================
// Save/load from .scn functions
void ModuleMessagingExtMFD::ReadStatus(FILEHANDLE scn) {

  return;
}

void ModuleMessagingExtMFD::WriteStatus(FILEHANDLE scn) const {

  return;
}
