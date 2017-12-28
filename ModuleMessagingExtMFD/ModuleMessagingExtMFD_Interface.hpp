// ==============================================================
//
//	ModuleMessagingExtMFD (Orbiter Interface)
//	=========================================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
//

#ifndef MMExt2MFD_INTERFACE
#define MMExt2MFD_INTERFACE

#include "windows.h"
#include "orbitersdk.h"
#include "ModuleMessagingExtMFD.hpp"


class ModuleMessagingExtMFD_Interface : public oapi::Module {
public:
  ModuleMessagingExtMFD_Interface(HINSTANCE hDLL);
  ~ModuleMessagingExtMFD_Interface();
  void clbkSimulationStart(RenderMode mode);
  void clbkSimulationEnd();
  void clbkPreStep (double simt, double simdt, double mjd);
  //void clbkPostStep (double simt, double simdt, double mjd);
  void clbkDeleteVessel (OBJHANDLE hVessel);
  static int MsgProc (UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam);

};
#endif // MMExt2MFD_INTERFACE