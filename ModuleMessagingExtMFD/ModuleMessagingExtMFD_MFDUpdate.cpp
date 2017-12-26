// ==============================================================
//
//	ModuleMessagingExtMFD (MFD Update)
//	=====================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "ModuleMessagingExtMFD.hpp"
#include "DisplayEngUnitFunctions.h"
#include <math.h>
#include <stdarg.h>


bool ModuleMessagingExtMFD::Update(oapi::Sketchpad *skp)
{
  LC->skp = skp;

  //LC->skp->SetTextColor(CLR_DEF);

  if (LC->showMessage) return DisplayMessageMode();

  int l = 3;
  return true;

/*  if (vdata->burnArmed) {
    skpTitle("ModuleMessagingExtMFD: ORBIT (PLAN)");
  } else {
    skpTitle("ModuleMessagingExtMFD: ORBIT (LIVE)");
  }

  int circrad = (int)(W / 120);
  int enc_x, enc_y;

  ModuleMessagingExtMFDUniverse* LU = GC->LU;
  ModuleMessagingExtMFDUniverse::ModuleMessagingExtMFDUniverse_LP* LP = &LU->LP;
  ModuleMessagingExtMFD_vdata *lvd = &LU->vdata[GC->LU->act][VC->vix];
  ModuleMessagingExtMFD_orb_disp *lod = &LU->l_orb[GC->LU->act];
  if (LU->orbScale[LU->orbProj] == 0.0) return true;

  skpFormatText(0, l, "LP: %s", LP->name);
  skpFormatText(4, l++, "FRM: %s", LU->body[lvd->refEnt].name);
  skpFmtEngText(0, l++, "SC: %.0f", "m", LU->orbScale[LU->orbProj], 1);

  char *PrjTxt[3] = { "Std X-Z", "X-Y", "Z-Y" };
  char FocTxt[7][32] = { "", "", "Ves Orbit", "Ves Enc", "Ves Burn", "LP", "Rot"};
  strcpy(FocTxt[0], LU->body[LP->maj].name);
  strcpy(FocTxt[1], LU->body[LP->min].name);
  char locked[6] = "";
  if (LU->orbFocRot || LU->orbFocLock || LU->orbFocCtr || LU->orbFocSca) {
    strcat(locked, "(");
    if (LU->orbFocRot) strcat(locked, "R");
    if (LU->orbFocLock) strcat(locked, "L");
    if (LU->orbFocCtr) strcat(locked, "C");
    if (LU->orbFocSca) strcat(locked, "S");
    strcat(locked, ")");
  }
  skpFormatText(0, 24, "FOC: %s %s", FocTxt[LU->orbFocus], locked);
  skpFormatText(4, 24, "PRJ: %s", PrjTxt[LU->orbProj]);
  if (lvd->alarm_state == 0) {
    skpFormatText(0, 25, "ZM: %d", -LU->orbZoom);
    skpFmtEngText(2, 25, "H: %.0f", "m", LU->orbPanHoriz[LU->orbProj] * pow(1.1, (double)LU->orbZoom), 1);
    skpFmtEngText(4, 25, "V: %.0f", "m", LU->orbPanVert[LU->orbProj] * pow(1.1, (double)LU->orbZoom), 1);
  } else   if (lvd->alarm_state == 2) {
    char buf2[256];
    skpColor(CLR_WARN);
    if (lvd->alarm_body == 1) {
      sprintf(buf2, "ALARM: %s reentry in %%.1f", LU->body[lvd->alarm_body].name);
    } else {
      sprintf(buf2, "ALARM: %s impact in %%.1f", LU->body[lvd->alarm_body].name);
    }
    skpFmtEngText(0, 25, buf2, "s", LU->s4i[GC->LU->act][lvd->alarm_ix].sec - oapiGetSimTime());
    skpColor(CLR_DEF);
  } else if (lvd->alarm_state == 1) {
    char buf2[256];
    skpColor(CLR_HI);
    sprintf(buf2, "WARN: %s proximity in %%.1f", LU->body[lvd->alarm_body].name);
    skpFmtEngText(0, 25, buf2, "s", LU->s4i[GC->LU->act][lvd->alarm_ix].sec - oapiGetSimTime());
    skpColor(CLR_DEF);
  }

  if (!GC->LU->s4i_valid) return true;
  if (lvd->orb_plot.size() != GC->LU->orbPlotCount[GC->LU->act]) return true;




  for (int s = 0; s < ORB_MAX_LINES; s++) {
    if (LP->plotix[s] == -1) break;
    for (unsigned int i = 0; i < GC->LU->orbPlotCount[GC->LU->act]; i++) {
      iv[i].x = (long)((double)W * lod->orb_plot[s][i].x);
      iv[i].y = (long)((double)H * lod->orb_plot[s][i].y);
    }
    if (LP->plotix[s] != -2) {
      LC->skp->SetPen(GC->LU->draw->GetPen(LU->body[LP->plotix[s]].name));

    } else {
      LC->skp->SetPen(GC->LU->draw->GetPen("LP"));
    }

    LC->skp->MoveTo((int)((double)W * lod->orb_plot[s][1].x), (int)((double)H * lod->orb_plot[s][1].y));
    LC->skp->Polyline(iv, GC->LU->orbPlotCount[GC->LU->act]);

    if (LP->plotix[s] != -2) {
      LC->skp->SetPen(GC->LU->draw->GetPen(LU->body[LP->plotix[s]].name, true));

    } else {
      LC->skp->SetPen(GC->LU->draw->GetPen("LP", true));
    }

    if (lvd->enc_ix >= 0) {
      if (abs(lvd->orb_plot_body_enc[s].x - lvd->orb_plot_origin.x) >= 0.00 ||
        abs(lvd->orb_plot_body_enc[s].y - lvd->orb_plot_origin.y) >= 0.00) {

        enc_x = (int)((double)W * lvd->orb_plot_body_enc[s].x);
        enc_y = (int)((double)H * lvd->orb_plot_body_enc[s].y);
        LC->skp->Ellipse(enc_x - circrad, enc_y - circrad, enc_x + circrad, enc_y + circrad);

        if (LP->plotix[s] != -2) {
          // Determine Body PROX limit and IMPACT LIMIT
          double proxLim = GC->LU->body[LP->plotix[s]].proxWarnDist;
          double impactLim = GC->LU->body[LP->plotix[s]].impactWarnDist;
          double circradKM = (double)circrad / (double)W * GC->LU->orbScale[GC->LU->orbProj];
          if (circradKM < impactLim) {
            int bodyRadPx = (int)((double)W * impactLim / GC->LU->orbScale[GC->LU->orbProj] + 0.5);
            double rf = bodyRadPx;
            for (int xscan = 0; xscan <= bodyRadPx; xscan++) {
              double xf = (double) xscan;
              double ang = asin(xf / rf);
              double yf = rf * cos(ang) + 0.5;
              int yof = (int) yf;
              LC->skp->Line(enc_x + xscan, enc_y + yof, enc_x + xscan, enc_y - yof);
              LC->skp->Line(enc_x - xscan, enc_y + yof, enc_x - xscan, enc_y - yof);
            }
          }
        }
      }
    }     
  }

  for (unsigned int i = 0; i < GC->LU->orbPlotCount[GC->LU->act]; i++) {
    iv[i].x = (long)((double)W * lvd->orb_plot[i].x);
    iv[i].y = (long)((double)H * lvd->orb_plot[i].y);
  }

  if (vdata->burnArmed) {
    LC->skp->SetPen(GC->LU->draw->GetPen("VP"));
  } else {
    LC->skp->SetPen(GC->LU->draw->GetPen("VL"));
  }

  LC->skp->MoveTo((long)((double)W * lvd->orb_plot[0].x), (long)((double)H * lvd->orb_plot[0].y));
  LC->skp->Polyline(iv, GC->LU->orbPlotCount[GC->LU->act]);
  //LC->skp->Line((int)((double)W * lvd->orb_plot_origin.x), (int)((double)H *lvd->orb_plot_origin.y), (int)((double)W * lvd->orb_plot[0].x), (long)((double)H * lvd->orb_plot[0].y));

  if (vdata->burnArmed) {
    LC->skp->SetPen(GC->LU->draw->GetPen("VP", true));
  } else {
    LC->skp->SetPen(GC->LU->draw->GetPen("VL", true));
  }
  if (lvd->enc_ix >= 0) {
    enc_x = (int)((double)W * lvd->orb_plot_ves_enc.x);
    enc_y = (int)((double)H * lvd->orb_plot_ves_enc.y);
    LC->skp->Ellipse(enc_x - circrad, enc_y - circrad, enc_x + circrad, enc_y + circrad);
  }

  return true; */

};


bool ModuleMessagingExtMFD::DisplayMessageMode() {
  skpTitle("ModuleMessagingExtMFD");
  showMessage();
  return true;
};


// MFD Line formatting helper
void ModuleMessagingExtMFD::showMessage() {

  char localMsg[750];
  strcpy_s(localMsg,750, LC->Message.c_str());
  char *bp = localMsg;
  char *bp2 = localMsg;
  char *bp3 = localMsg;
  char c1, c2;
  int i = 0;
  int j;
  int l = 4;
  bool eol = false;

  do {
    if ((*bp2 == '\n') || (*bp2 == '\0')) {     // Look for user newline or end of buffer
      eol = true;
      c1 = *bp2;
      *bp2 = '\0';
    } else {
      if (i==34) {                              // 34 chars no newline ... need to break the line
        eol=true;
        bp3 = bp2;
        for (j=34; j>20; j--) {                 // look for a space from 21 to 34
          if (*bp3==' ') break;
          bp3--;
        }
        if (j>20) {                             // space found
          bp2 = bp3;
          c1 = *bp2;
          *bp2 = '\0';
        } else {                                // no space ... insert hyphen
          bp3 = bp2 + 1;
          c1 = *bp2;
          c2 = *bp3;
          *bp2 = '-';
          *bp3 = '\0';
        }
      } else {                                  // Scan forward      
        i++;
        bp2++;
      }
    }

    if (eol) {                                  // EOL flag ... write out buffer from bp to bp2.
  	  LC->skp->Text (_Col(0), _Line(l++), bp, strlen(bp));
      eol = false;
      if (c1 == '\0') {
        bp = bp2;     // End of buffer
      } else if ((c1 == '\n') || (c1 == ' ')) {
        bp = bp2+1;   // Reset for next line of the buffer
        bp2++;
        i=0;
      } else {
        bp = bp2;     // Put back the chars we stomped
        *bp2 = c1;
        *bp3 = c2;
        i=0;
      }
    }
  } while (*bp);

  return;
}

