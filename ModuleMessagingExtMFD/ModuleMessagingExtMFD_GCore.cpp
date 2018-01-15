// ==============================================================
//
//	ModuleMessagingExtMFD (Core Persistence)
//	========================================
//
//	Copyright (C) 2016-2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "ModuleMessagingExtMFD_GCore.hpp"
#include "ModuleMessagingExtMFD_VCore.hpp"

ModuleMessagingExtMFD_GCore::ModuleMessagingExtMFD_GCore() : mm("MMExtMFD") {
  string ver;
  mmVer = "";
  coreFound = mm.GetVersion(&ver);
  if (coreFound) mmVer = string() + "Core: " + ver;
  return;
}

ModuleMessagingExtMFD_GCore::~ModuleMessagingExtMFD_GCore() {
  return;
}


void ModuleMessagingExtMFD_GCore::corePreStep(double simT,double simDT,double mjd) {
  if (coreSimT == 0.0) {
    coreSimT = -3.0;
  }

  if (simT - coreSimT > 2.0) {
    coreSimT = simT;
    int ix = 0;
    char typ;
    string mod, var, vesName, msg;
    OBJHANDLE ovh;
    list<string> mmListVesTyp, mmListModVar;
    while (mm.Find(&typ, &mod, &var, &ovh, &ix, "*", "*", NULL, false)) {
      msg = string() + oapiGetVesselInterface(ovh)->GetName() + " (" + typ + ")";
      mmListVesTyp.push_back(msg);
      mmListModVar.push_back(mod + ":" + var);
    }

    int siz;
    siz = mmListVesTyp.size();
    mmDumpVesTyp.resize(mmListVesTyp.size());
    mmDumpModVar.resize(mmListVesTyp.size());
    int i = 0;
    for (auto& e : mmListVesTyp) {
      mmDumpVesTyp[i++] = e;
    }
    i = 0;
    for (auto& e : mmListModVar) {
      mmDumpModVar[i++] = e;
    }
    mmActL1.clear();
    mmActL2.clear();
    ix = 0;
    string rcli, rmod, rvar, rves, act;
    char rfunc;
    bool rsucc;

    while (mm.GetLog(&rfunc, &rcli, &rmod, &rvar, &rves, &rsucc, &ix)) {
      switch (rfunc) {
      case 'P': act = "Put"; break;
      case 'G': act = "Get"; break;
      case 'D': act = "Del"; break;
      case 'L': act = "Log"; break;
      case 'V': act = "Ver"; break;
      case 'F': act = "Fnd"; break;
      default: act = string() + rfunc; 
      }
      act = act + " " + rves;
      if (!rsucc) act = act + " (f)";
      mmActL1.push_back(rcli + " " + act);
      mmActL2.push_back(rmod + ":" + rvar);
    }
  }
}
