/******************************************************************************
*
* STATENS KARTVERK  -  FYSAK
*
* Filename: fygm.h
* 
* Content: Prototyper for generelle geometrirutiner.
*
* Copyright (c) 1990-2011 Statens kartverk
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
******************************************************************************/

#pragma once

#ifndef SK_EntPnt_GM
#  define SK_EntPnt_GM
#endif


/* --- Konstanter -- */
//#define PI  3.14159265358979324
#define PI  3.14159265358979323846
#define PIHALV (PI/2.0)
#define TOPI   (PI*2.0)

/* --- Makroer -- */
#define Rad2Deg(Rad) ((Rad/PI)*180)
#define Rad2Gon(Rad) ((Rad/PI)*200)

#define Deg2Rad(Deg) ((Deg/180)*PI)
#define Gon2Rad(Gon) ((Gon/200)*PI)


/* ---- Funksjonsdefinisjoner for fygm.c -- */
SK_EntPnt_GM short GM_sver(double ka,double kn,double la,double ln,double na,double nn,
                        double ma,double mn,double *sa,double *sn);
SK_EntPnt_GM short GM_shor(double ka,double kn,double la,double ln,double na,double nn,
                        double ma,double mn,double *sa,double *sn);
SK_EntPnt_GM short GM_sLinLin(double ka,double kn,double la,double ln,double ma,double mn,
                           double na,double nn,double *sa,double *sn);
SK_EntPnt_GM short GM_Overlapp(double ka,double kn,double la,double ln,double ma,double mn,double na,double nn);
SK_EntPnt_GM short GM_sVektVekt(double ka,double kn,double la,double ln,double ma,double mn,
                             double na,double nn,double *sa,double *sn);
SK_EntPnt_GM short GM_sLinBue(double sa,double sn,double radius,double fi,double dfi,
                           double ka,double kn,double la,double ln,
                           double *a1,double *n1,double *a2,double *n2);
SK_EntPnt_GM short GM_sVektSirk(double sa,double sn,double radius,
                             double ka,double kn,double la,double ln,
                             double *a1,double *n1,double *a2,double *n2);
SK_EntPnt_GM short GM_sBueBue(double as1,double ns1,double radius1,double fi1,double dfi1,
                           double as2,double ns2,double radius2,double fi2,double dfi2,
                           double *a1,double *n1,double *a2,double *n2);
SK_EntPnt_GM short GM_sSirkSirk(double as1,double ns1,double radius1,
                             double as2,double ns2,double radius2,
                             double *a1,double *n1,double *a2,double *n2);
SK_EntPnt_GM short GM_fotp(double a1,double n1,double a2,double n2,double ap,double np,
                        double *af,double *nf);
SK_EntPnt_GM short GM_fotp_ny(double a1, double n1, double a2, double n2, double ap, double np,
								double *af, double *nf);
SK_EntPnt_GM short GM_KonvBue(double a1,double n1,double a2,double n2,double radius,
                           short storbue,double *as,double *ns,double *fi,double *dfi);
SK_EntPnt_GM short GM_KonvBuep(double a1,double n1,double a2,double n2,double a3,double n3,
                            double *as,double *ns,double *radius,double *fi,double *dfi);
SK_EntPnt_GM short GM_KonvSirkel(double *fi,double *dfi);
SK_EntPnt_GM short GM_KonvSirkelp(double a1,double n1,double a2,double n2,double a3,double n3,
                               double *as,double *ns,double *radius,double *fi,double *dfi);
SK_EntPnt_GM short GM_bepa(double a1,double n1,double a2,double n2,
                        double *pa,double *pb,double *pc);
SK_EntPnt_GM short GM_bepa3(double a1, double n1, double h1,
                         double a2, double n2, double h2,
                         double *pf, double *pg, double *ph);
SK_EntPnt_GM short GM_cint(double pa1,double pb1,double pc1,double pa2,double pb2,
                        double pc2,double *as,double *ns);
SK_EntPnt_GM short GM_wtst(double p1a,double p1n,double p2a,double p2n,
                        double wmina,double wminn,double wmaxa,double wmaxn);
SK_EntPnt_GM short GM_wtstBue(double as,double ns,double radius,double fi,double dfi, 
                           double wmina,double wminn,double wmaxa,double wmaxn);
SK_EntPnt_GM short GM_wtstPunkt(double PktA, double PktN, double wa1, double wn1, double wa2, double wn2, double wa3, double wn3,
                               double wa4, double wn4);
SK_EntPnt_GM short GM_Parallell(double ka,double kn,double la,double ln,double avstand,
                               double *ka1,double *kn1,double *la1,double *ln1);
SK_EntPnt_GM double GM_Avstand(double as, double ns, double a, double n);
SK_EntPnt_GM double GM_Avstand2(double a1, double n1, double a2, double n2);
SK_EntPnt_GM double GM_Areal(double *pA, double *pN, short sNko);
SK_EntPnt_GM double GM_retning(double ak,double nk,double al,double nl);
SK_EntPnt_GM double GM_RetnGon(double a1, double n1, double a2, double n2);
SK_EntPnt_GM double GM_Vinkel(double fi1, double fi2 );
SK_EntPnt_GM double GM_RedVinkel(double fi );
SK_EntPnt_GM void   GM_RettvPol(double a1 , double n1, double a2, double n2,
                             double *gon, double *avst);
SK_EntPnt_GM void  GM_PolRettv(double *a , double *n, double gon, double avst);
SK_EntPnt_GM void  GM_buebox(double as,double ns,double radius,double fi,double dfi,
                          double *nva,double *nvn,double *oha,double *ohn);
SK_EntPnt_GM short GM_NormVindu(double *nva,double *nvn,double *oha,double *ohn);
SK_EntPnt_GM short GM_PktBue(double as,double ns,double fi,double dfi,
                             double a,double n,double *dfiPkt);
SK_EntPnt_GM short GM_TestPktBue(double as,double ns,double fi,double dfi,
                              double a,double n);
SK_EntPnt_GM short  GM_BueTangent(double as, double ns, double fi, double dfi,
                               double radius, double a, double n, double *buetan);
SK_EntPnt_GM short GM_BueTilKorder (double as,double ns,double r,double fi,double dfi,
                                 double delta,short mpu,double *a_arr,double *n_arr);
SK_EntPnt_GM void GM_PktTilOktagon (double dAs,double dNs,double dAreal,double *a_arr,double *n_arr);
SK_EntPnt_GM void GM_TynnDared(double dMaxAvst,double dMaxPil,long *nko, double *pA,double *pN);
