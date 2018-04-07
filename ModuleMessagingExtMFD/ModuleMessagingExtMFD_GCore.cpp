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
    string mod, var, vesName, msg, objdesc;
    OBJHANDLE ohv;
    list<string> mmListVesTyp, mmListModVar, mmListData;
    bool valB;
    int valI;
    double valD;
    string valS;
    VECTOR3 valV;
    MATRIX3 val3;
    MATRIX4 val4;
    OBJHANDLE valO;
    char ptrbuf[20];
    int ot;

    while (mm.Find(&typ, &mod, &var, &ohv, &ix, "*", "*", NULL, false)) {
      objdesc = typ;
      switch (typ) {
      case 'b':
        mm.Get(mod, var, &valB, ohv);
        mmListData.push_back(valB ? "true" : "false");
        break;
      case 'i':
        mm.Get(mod, var, &valI, ohv);
        mmListData.push_back(to_string(valI));
        break;
      case 'd':
        mm.Get(mod, var, &valD, ohv);
        mmListData.push_back(to_string(valD));
        break;
      case 's':
        mm.Get(mod, var, &valS, ohv);
        mmListData.push_back(valS);
        break;
      case 'v':
        mm.Get(mod, var, &valV, ohv);
        mmListData.push_back(to_string(valV.x) + "," +to_string(valV.y) + "," + to_string(valV.z));
        break;
      case '3':
        mm.Get(mod, var, &val3, ohv);
        mmListData.push_back(to_string(val3.m11) + "," + to_string(val3.m12) + "," + to_string(val3.m13) + "...");
        break;
      case '4':
        mm.Get(mod, var, &val4, ohv);
        mmListData.push_back(to_string(val4.m11) + "," + to_string(val4.m12) + "," + to_string(val4.m13) + "...");
        break;
      case 'o':
        mm.Get(mod, var, &valO, ohv);
        ot = mm.ObjType(valO);
        switch (ot) {
        case -1:             objdesc = "o-err"; break;
        case OBJTP_INVALID:  objdesc = "o-inv"; break;
        case OBJTP_GENERIC:  objdesc = "o-gen"; break;
        case OBJTP_CBODY:    objdesc = "o-cel"; break;
        case OBJTP_STAR:     objdesc = "o-star"; break;
        case OBJTP_PLANET:   objdesc = "o-planet"; break;
        case OBJTP_VESSEL:   objdesc = "o-ves"; break;
        case OBJTP_SURFBASE: objdesc = "o-base"; break;
        }
        sprintf(ptrbuf, "%p", valO);
        mmListData.push_back("0x" + string(ptrbuf));
        break;
      case 'x':
        objdesc = "struct";
        mmListData.push_back("");
        break;
      case 'y':
        objdesc = "old struct";
        mmListData.push_back("");
        break;
      }

      msg = string() + oapiGetVesselInterface(ohv)->GetName() + " (" + objdesc + ")";
      mmListVesTyp.push_back(msg);
      mmListModVar.push_back(mod + "::" + var);

    }

    int siz;
    siz = mmListVesTyp.size();
    mmDumpVesTyp.resize(mmListVesTyp.size());
    mmDumpModVar.resize(mmListModVar.size());
    mmDumpData.resize(mmListData.size());
    int i = 0;
    for (auto& e : mmListVesTyp) {
      mmDumpVesTyp[i++] = e;
    }
    i = 0;
    for (auto& e : mmListModVar) {
      mmDumpModVar[i++] = e;
    }
    i = 0;
    for (auto& e : mmListData) {
      mmDumpData[i++] = e;
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
      mmActL2.push_back(rmod + "::" + rvar);
    }
  }
}
