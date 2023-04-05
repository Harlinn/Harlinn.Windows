/* ======= =============================================================== */
/*  STATENS KARTVERK  -  FYSAK-PC                                         */
/*  Fil: gm.c                                                             */
/*  Ansvarlig: Andreas Røstad                                             */
/*  Innhold: Geometrirutiner fysak-pc                                     */
/* ====================================================================== */

#include "fyut.h"

#include <math.h>
#include <stdlib.h>
#include <memory.h>



#include "fygm.h"

/* --- Konstanter -- */
#define ACCY  1.0E-6
#define GM_ACCY  1.0E-8

/* --- Makroer -- */
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))


/*
AR-890723
CH GM_wtstBue                               Sjekk om en bue berører et vindu
CD ==========================================================================
CD Formål:
CD Sjekker om en bue berører et vindu.
CD                                    wmax
CD                       !--------------!
CD                       !   ......     !
CD                      .!...      .....!
CD                  .... !              !...
CD               ...     !              !   x (p2)
CD        (p1)  x        !--------------!
CD                     wmin
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   as       i    Koordinat i sentrumspunktet
CD double   ns       i
CD double   radius   i    Buens radius
CD double   fi       i    "Retning" fra sentrum til buens startpunkt.
CD double   dfi      i    Vinkel mellom fi og retning sentrum - sluttpkt.
CD double   wmina    i    -!
CD double   wminn    i     ! Vindu
CD double   wmaxa    i     !
CD double   wmaxn    i    -!
CD short    kryss    r    0=ikke skjæring, 1=skjæring eller inni
CD
CD Bruk:
CD kryss = GM_wtstBue(as,ns,radius,fi,dfi,wmina,wminn,wmaxa,wmaxn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_wtstBue(double as,double ns,double radius,double fi,double dfi,
                           double wmina,double wminn,double wmaxa,double wmaxn)
{
   double nva,nvn,oha,ohn,as1,ns1,as2,ns2;
   double r = fabs(radius);

                                    /* Omskrevet rektangel */
   GM_buebox(as,ns,r,fi,dfi,&nva,&nvn,&oha,&ohn);

                               /* Er  hele buen inni? */
   if (wmaxn >= ohn  &&  wmaxa >= oha  &&  wminn <= nvn  &&  wmina <= nva){
      return 1;
   }

               /* Overlapp mellom rektangel og vindu?, må teste videre */
   if (wmaxn >= nvn  &&  wmaxa >= nva  &&  wminn <= ohn  &&  wmina <= oha){
                                             /* Min N */
      if (GM_sLinBue(as,ns,r,fi,dfi,wmina,wminn,wmaxa,wminn,
         &as1,&ns1,&as2,&ns2)){
         return 1;
      }
                                             /* Min A */
      if (GM_sLinBue(as,ns,r,fi,dfi,wmina,wminn,wmina,wmaxn,
         &as1,&ns1,&as2,&ns2)){
         return 1;
      }
                                          /* Max N */
      if (GM_sLinBue(as,ns,r,fi,dfi,wmina,wmaxn,wmaxa,wmaxn,
         &as1,&ns1,&as2,&ns2)){
         return 1;
      }
                                          /* Max a */
      if (GM_sLinBue(as,ns,r,fi,dfi,wmaxa,wminn,wmaxa,wmaxn,
         &as1,&ns1,&as2,&ns2)){
         return 1;
      }
   }

   return 0;
}


/*
AR-881018
CH GM_wtst                                Sjekk om en linje berører et vindu
CD ==========================================================================
CD Formål:
CD Sjekker om en linje berører et vindu.
CD                                    wmax
CD                       !--------------!
CD                       !      ........!.........
CD                   ....!......        !        p2
CD          .........    !              !
CD        p1             !              !
CD                       !--------------!
CD                     wmin
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   p1a      i    Koordinat i første punkt
CD double   p1n      i
CD double   p2a      i    Koordinat i andre punkt
CD double   p2n      i
CD double   wmina    i    -!
CD double   wminn    i     ! Vindu
CD double   wmaxa    i     !
CD double   wmaxn    i    -!
CD short    kryss    r    0=ikke skjæring, 1=skjæring eller inni
CD
CD Bruk:
CD kryss = GM_wtst(pa1,p1n,p2a,p2n,wmina,wminn,wmaxa,wmaxn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_wtst(double p1a, double p1n, double p2a, double p2n,
                        double wmina, double wminn, double wmaxa, double wmaxn)
{
   unsigned int visa,visb,heltute,inni,kryss;
   double sn,sa;

   visa = 0;
   if (p1a < wmina)  visa |= (unsigned int)0x1;
   if (p1a > wmaxa)  visa |= (unsigned int)0x2;
   if (p1n < wminn)  visa |= (unsigned int)0x4;
   if (p1n > wmaxn)  visa |= (unsigned int)0x8;
   inni = (unsigned int)(visa == 0);
                               /* Tester videre når første pkt. er utenfor */
   if (! inni){
       visb = 0;
       if (p2a < wmina)  visb |= (unsigned int)0x1;
       if (p2a > wmaxa)  visb |= (unsigned int)0x2;
       if (p2n < wminn)  visb |= (unsigned int)0x4;
       if (p2n > wmaxn)  visb |= (unsigned int)0x8;

       inni = (unsigned int)(visb == 0);
       if (! inni){
                               /* Når pkt B også er utenfor */
           heltute = visa & visb;
           if (! heltute){
                               /* Når det er mulig skjæring med vinduet */
                                                   /* Min N */
               kryss = (unsigned int)GM_shor(p1a,p1n,p2a,p2n,
                               wmina,wminn,wmaxa,wminn,&sa,&sn);
               if (! kryss){                       /* Min A */
                   kryss = (unsigned int)GM_sver(p1a,p1n,p2a,p2n,
                                   wmina,wminn,wmina,wmaxn,&sa,&sn);
               }
               if (! kryss){                       /* Max N */
                   kryss = (unsigned int)GM_shor(p1a,p1n,p2a,p2n,
                                   wmina,wmaxn,wmaxa,wmaxn,&sa,&sn);
               }
               if (! kryss){                      /* Max a */
                   kryss = (unsigned int)GM_sver(p1a,p1n,p2a,p2n,
                                   wmaxa,wminn,wmaxa,wmaxn,&sa,&sn);
               }
               if (kryss)  inni = 1;
           }
       }
   }
   return (short)inni;
}

/*
PG-030815
CH GM_wtstPunkt       Sjekker om et punkt ligger inni  - eller i kanten av - vindu
CD ===============================================================================
CD Formål:
CD Sjekker om et punkt ligger inni et vindu - gjerne rotert vindu.
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD -------------------------------------------------------------------------------
CD PktA      double       i   Øst-koordinat for sjekkpunkt
CD PktN      double       i   Nord-koordinat for sjekkpunkt
CD wa1       double       i   Øst-koordinat for 1.pkt i vindu
CD wn1       double       i   Nord-koordinat for 1.pkt i vindu
CD wa2       double       i   Øst-koordinat for 2.pkt i vindu
CD wn2       double       i   Nord-koordinat for 2.pkt i vindu
CD wa3       double       i   Øst-koordinat for 3.pkt i vindu
CD wn3       double       i   Nord-koordinat for 3.pkt i vindu
CD wa4       double       i   Øst-koordinat for 4.pkt i vindu
CD wn4       double       i   Nord-koordinat for 4.pkt i vindu
CD inni      short        r   Er punktet innenfor vinduet
CD 
CD Bruk:  inni = GM_wtstPunkt(PktA, PktN, wa1, wn1, wa2, wn2, wa3, wn3, wa4, wn4);
   ===============================================================================
*/
SK_EntPnt_GM short GM_wtstPunkt(double PktA, double PktN, double wa1, double wn1, double wa2, double wn2, double wa3, double wn3,
                                double wa4, double wn4)
{
   
   double dPolyMaxA,dPolyMaxN,dPolyMinA,dPolyMinN;
   double maxA = 99999999999.9;           // "Uendelig" øst
   double as,ns;
   short sAntSkjaer;
   
   // Sjekk 1: Ligger punktet utenfor omskrevet rektangel - så ligger det utenfor vinduet
   dPolyMaxA=max(wa1,wa2); dPolyMaxA=max(dPolyMaxA,wa3); dPolyMaxA=max(dPolyMaxA,wa4);
   dPolyMaxN=max(wn1,wn2); dPolyMaxN=max(dPolyMaxN,wn3); dPolyMaxN=max(dPolyMaxN,wn4);
   dPolyMinA=min(wa1,wa2); dPolyMinA=min(dPolyMinA,wa3); dPolyMinA=min(dPolyMinA,wa4);
   dPolyMinN=min(wn1,wn2); dPolyMinN=min(dPolyMinN,wn3); dPolyMinN=min(dPolyMinN,wn4);
   if((PktA>dPolyMaxA) || (PktA<dPolyMinA) || (PktN>dPolyMaxN) || (PktN<dPolyMinN))
      return 0;

   // Sjekk 2: // Ligger punktet innenfor vinduet? 

   // Pluss på et lite tillegg for å unngå treff på node
   PktN += 0.000001;

   // Beregn skjæring med alle sidene
   sAntSkjaer = GM_shor(wa1,wn1,wa2,wn2,PktA,PktN,maxA,PktN,&as,&ns);
   sAntSkjaer += GM_shor(wa2,wn2,wa3,wn3,PktA,PktN,maxA,PktN,&as,&ns);
   sAntSkjaer += GM_shor(wa3,wn3,wa4,wn4,PktA,PktN,maxA,PktN,&as,&ns);
   sAntSkjaer += GM_shor(wa4,wn4,wa1,wn1,PktA,PktN,maxA,PktN,&as,&ns);

   // Sjekk om punktet er innenfor
   return  ((sAntSkjaer % 2) == 1)?  1 : 0;
}

/*
AR-881018
CH GM_sver                            Skjæring mellom vertikal- og skrålinje
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom en vertikal linje (M-N) og en skrålinje (K-L)
CD
CD                               M*     *L
CD                                !   /
CD                                ! /
CD                                *S
CD                              / !
CD                            /   !
CD                         K*     *N
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   ka       i    Koordinat i K
CD double   kn       i
CD double   la       i    Koordinat i L
CD double   ln       i
CD double   na       i    Koordinat i N
CD double   nn       i
CD double   ma       i    Koordinat i M
CD double   mn       i
CD double  *sa       u    Koordinat i S
CD double  *sn       u
CD short    kryss    r    0=ikke skjæring, 1=skjæring
CD
CD Bruk:
CD kryss = GM_sver(ka,kn,la,ln,na,nn,ma,mn,&sa,&sn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_sver(double ka,double kn,double la,double ln,double na,double nn,
                        double ma,double mn,double *sa,double *sn)
{
   unsigned int kryss = 0;
   double mini,maxi;

   mini = min(ka,la);
   maxi = max(ka,la);

   if (na >= mini  &&  ma <= maxi){        /* (ma er lik na) */
       if (fabs(la-ka) > 0.0001){
                                               /* Beregn skjæringspunktet */
           *sa = ma;
           *sn = kn + ((*sa-ka)*(ln-kn))/(la-ka);
           mini = min(mn,nn) - ACCY;
           maxi = max(mn,nn) + ACCY;
                                               /* Sjekk om det er skjæring */
           kryss = (unsigned int)(*sn >= mini  &&  *sn <= maxi);
       }
   }
   return (short)kryss;
}


/*
AR-881018
CH GM_shor                          Skjæring mellom horisontal- og skrålinje
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom en horisontal linje (M-N)
CD og en skrålinje (K-L)
CD
CD                                     *L
CD                                   /
CD                                 /
CD                     M*--------*S--------*N
CD                             /
CD                           /
CD                        K*
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   ka       i    Koordinat i K
CD double   kn       i
CD double   la       i    Koordinat i L
CD double   ln       i
CD double   na       i    Koordinat i N
CD double   nn       i
CD double   ma       i    Koordinat i M
CD double   mn       i
CD double  *sa       u    Koordinat i S
CD double  *sn       u
CD short    kryss    r    0=ikke skjæring, 1=skjæring
CD
CD Bruk:
CD kryss = GM_shor(ka,kn,la,ln,na,nn,ma,mn,&sa,&sn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_shor(double ka,double kn,double la,double ln,double na,double nn,
                        double ma,double mn,double *sa,double *sn)
{
   unsigned int kryss = 0;
   double mini,maxi;

   mini = min(kn,ln);
   maxi = max(kn,ln);

   if (mn >= mini  &&  nn <= maxi){        /* (mn er lik nn) */
       if (fabs(ln-kn) > 0.0001){
                                               /* Beregn skjæringspunktet */
           *sn = mn;
           *sa = ka + ((*sn-kn)*(la-ka))/(ln-kn);
           mini = min(ma,na) - ACCY;
           maxi = max(ma,na) + ACCY;
                                               /* Sjekk om det er skjæring */
           kryss = (unsigned int)(*sa >= mini  &&  *sa <= maxi);
       }
   }
   return (short)kryss;
}


/*
AR-901209
CH GM_sLinLin                                 Skjæringspunkt mellom 2 linjer
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom 2 linjer (M-N) og (K-L)
CD
CD                         M*           *L
CD                            \       /
CD                              \   /
CD                               *S          
CD                             /   \
CD                           /       \
CD                        K*           *N
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   ka       i    Koordinat i K
CD double   kn       i
CD double   la       i    Koordinat i L
CD double   ln       i
CD double   ma       i    Koordinat i M
CD double   mn       i
CD double   na       i    Koordinat i N
CD double   nn       i
CD double  *sa       u    Koordinat i S
CD double  *sn       u
CD short    kryss    r    0=ikke skjæring, 1=skjæring
CD
CD Bruk:
CD kryss = GM_sLinLin(ka,kn,la,ln,ma,mn,na,nn,&sa,&sn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_sLinLin(double ka,double kn,double la,double ln,double ma,double mn,
                           double na,double nn,double *sa,double *sn)
{
   double det,detinv,s,t;

   double alk = la - ka;
   double nlk = ln - kn;
   double anm = na - ma;
   double nnm = nn - mn;
   double amk = ma - ka;
   double nmk = mn - kn;


   /* Sorterer først ut åpenbare tilfeller der det ikke er skjæring */ 
   if (max(ka,la) < min(ma,na))  return 0;
   if (min(ka,la) > max(ma,na))  return 0;
   if (max(kn,ln) < min(mn,nn))  return 0;
   if (min(kn,ln) > max(mn,nn))  return 0;

   det = anm * nlk - nnm * alk;

   /* Parallelle linjer */
   if (fabs(det) < ACCY)   return 0;

   detinv = 1.0 / det;
   s = (anm*nmk - nnm*amk) * detinv;
   t = (alk*nmk - nlk*amk) * detinv;

   if (s < 0.0  ||  s > 1.0  ||  t < 0.0  || t > 1.0)  return 0;

   *sa = ka + alk*s;
   *sn = kn + nlk*s;

   return 1;

#ifdef UTGAAR

   /*
    * Beregner skjæring mellom to uendelige vektorer.
    *  Sjekker etterpå om skjæringspunktet ligger på linjebitene.
    */
   if (GM_sVektVekt(ka,kn,la,ln,ma,mn,na,nn,sa,sn)){
      if (*sn <= max(kn,ln)+ACCY  &&  *sn >= min(kn,ln)-ACCY  &&
          *sa <= max(ka,la)+ACCY  &&  *sa >= min(ka,la)-ACCY  &&
          *sn <= max(mn,nn)+ACCY  &&  *sn >= min(mn,nn)-ACCY  &&
          *sa <= max(ma,na)+ACCY  &&  *sa >= min(ma,na)-ACCY) {

         return 1;     /* Skjæring funnet ==> returnerer */
      }
   }

   return 0;     /* Ingen skjæring funnet ==> returnerer */
#endif
}



/*
AR-901209
CH GM_Overlapp                                      Overlapp mellom 2 linjer
CD ==========================================================================
CD Formål:
CD Sjekker om to linjer overlapper hverandre helt eller delevis.
CD
CD                         M*     
CD                           \  
CD                            \  
CD                             \ *K         
CD                              \ \
CD                               \ \
CD                                *N\
CD                                   \
CD                                    \
CD                                     *L
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   ka       i    Koordinat i K
CD double   kn       i
CD double   la       i    Koordinat i L
CD double   ln       i
CD double   ma       i    Koordinat i M
CD double   mn       i
CD double   na       i    Koordinat i N
CD double   nn       i
CD double  *sa       u    Koordinat i S
CD double  *sn       u
CD short    overlapp r    0=ikke overlapp
CD                        1=tangerer (likt endepunkt)
CD                        2=delevis overlapp
CD                        3=linjene er like
CD Bruk:
CD kryss = GM_Overlapp(ka,kn,la,ln,ma,mn,na,nn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_Overlapp(double ka,double kn,double la,double ln,double ma,double mn,double na,double nn)
{
   // Sorterer først ut åpenbare tilfeller der det ikke er skjæring
   if (max(ka,la) < min(ma,na))  return 0;
   if (min(ka,la) > max(ma,na))  return 0;
   if (max(kn,ln) < min(mn,nn))  return 0;
   if (min(kn,ln) > max(mn,nn))  return 0;


   // Linjene er like
   if (fabs((min(ka,la) - min(ma,na))) < GM_ACCY &&
       fabs((max(ka,la) - max(ma,na))) < GM_ACCY &&
       fabs((min(kn,ln) - min(mn,nn))) < GM_ACCY &&
       fabs((max(kn,ln) - max(mn,nn))) < GM_ACCY)
   {
      return 3;
   }

   // Linjene tangerer i enden
   if ((fabs(ka-ma)<GM_ACCY && fabs(kn-mn)<GM_ACCY) ||
       (fabs(la-ma)<GM_ACCY && fabs(ln-mn)<GM_ACCY) ||
       (fabs(ka-na)<GM_ACCY && fabs(kn-nn)<GM_ACCY) ||
       (fabs(la-na)<GM_ACCY && fabs(ln-nn)<GM_ACCY))
   {
      return 1;
   }

   double alk = la - ka;
   double nlk = ln - kn;
   double anm = na - ma;
   double nnm = nn - mn;
   //double amk = ma - ka;
   //double nmk = mn - kn;
   double det = anm * nlk - nnm * alk;

   // Parallelle linjer
   if (fabs(det) < ACCY)
   {
      double a,n;
      if (GM_fotp(ka,kn,la,ln,ma,mn,&a,&n) == 2)
      {
         if (fabs(ma-a)<GM_ACCY && fabs(mn-n)<GM_ACCY)  return 2;
      }

      if (GM_fotp(ka,kn,la,ln,na,nn,&a,&n) == 2)
      {
         if (fabs(na-a)<GM_ACCY && fabs(nn-n)<GM_ACCY)  return 2;
      }

      if (GM_fotp(ma,mn,na,nn,ka,kn,&a,&n) == 2)
      {
         if (fabs(ka-a)<GM_ACCY && fabs(kn-n)<GM_ACCY)  return 2;
      }
      if (GM_fotp(ma,mn,na,nn,la,ln,&a,&n) == 2) {
         if (fabs(la-a)<GM_ACCY && fabs(ln-n)<GM_ACCY)  return 2;
      }
   }
   
   // Ikke parallelle
   return 0;
}


/*
AR-901209
CH GM_sVektVekt                     Skjæringspunkt mellom 2 uendelige linjer
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom uendelige 2 linjer (M-N) og (K-L)
CD   
CD                         M*           *L
CD                            \       /
CD                              \   /
CD                               *S          
CD                             /   \
CD                           /       \
CD                        K*           *N
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   ka       i    Koordinat i K
CD double   kn       i
CD double   la       i    Koordinat i L
CD double   ln       i
CD double   ma       i    Koordinat i M
CD double   mn       i
CD double   na       i    Koordinat i N
CD double   nn       i
CD double  *sa       u    Koordinat i S
CD double  *sn       u
CD short    kryss    r    0=ikke skjæring, 1=skjæring
CD
CD Bruk:
CD kryss = GM_sVektVekt(ka,kn,la,ln,ma,mn,na,nn,&sa,&sn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_sVektVekt(double ka,double kn,double la,double ln,double ma,double mn,
                             double na,double nn,double *sa,double *sn)
{
   double det,detinv,s,t;

   double alk = la - ka;
   double nlk = ln - kn;
   double anm = na - ma;
   double nnm = nn - mn;
   double amk = ma - ka;
   double nmk = mn - kn;


   /* Sorterer først ut åpenbare tilfeller der det ikke er skjæring */ 
   //if (max(ka,la) < min(ma,na))  return 0;
   //if (min(ka,la) > max(ma,na))  return 0;
   //if (max(kn,ln) < min(mn,nn))  return 0;
   //if (min(kn,ln) > max(mn,nn))  return 0;

   det = anm * nlk - nnm * alk;

   /* Parallelle linjer */
   if (fabs(det) < ACCY)   return 0;

   detinv = 1.0 / det;
   s = (anm*nmk - nnm*amk) * detinv;
   t = (alk*nmk - nlk*amk) * detinv;

   //if (s < 0.0  ||  s > 1.0  ||  t < 0.0  || t > 1.0)  return 0;

   *sa = ka + alk*s;
   *sn = kn + nlk*s;

   return 1;



#ifdef UTGAAR

   double pa1,pb1,pc1,pa2,pb2,pc2;

   /*
    * Beregner skjæring mellom to uendelige vektorer.
    */
   if (GM_bepa(ka,kn,la,ln,&pa1,&pb1,&pc1)) {
      if (GM_bepa(ma,mn,na,nn,&pa2,&pb2,&pc2)) {
         if (GM_cint(pa1,pb1,pc1,pa2,pb2,pc2,sa,sn)) {
            return 1;     /* Skjæring funnet ==> returnerer */
         }
      }  
   }

   return 0;     /* Ingen skjæring funnet ==> returnerer */

#endif
}


/*
AR-890722
CH GM_sLinBue                                   Skjæring mellom linje og bue
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom en linje (K-L) og en bue.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   sa       i    Koordinat i buens sentrum.
CD double   sn       i
CD double   radius   i    Buens radius.
CD double   fi       i    Retning fra sentrum til buens startpunkt
CD double   dfi      i    Vinkel mellom retning til buens startpunkt og sluttpunkt
CD double   ka       i    Koordinat i K.
CD double   kn       i
CD double   la       i    Koordinat i L.
CD double   ln       i
CD double  *a1       u    Koordinat i skjæringspunkt 1
CD double  *n1       u
CD double  *a2       u    Koordinat i skjæringspunkt 2
CD double  *n2       u
CD short    kryss    r    Antall skjæringspunkter (0, 1 eller 2)
CD
CD Bruk:
CD kryss = GM_sLinBue(sa,sn,radius,fi,dfi,ka,kn,la,ln,&a1,&n1,&a2,&n2);
   ==========================================================================
*/
SK_EntPnt_GM short GM_sLinBue(double sa,double sn,double radius,double fi,double dfi,
                           double ka,double kn,double la,double ln,
                           double *a1,double *n1,double *a2,double *n2)
{
   short kryss;
   double mina,minn,maxa,maxn;

            /* Beregn først skjæring mellom uendelig vektor og hele sirkelen */
   kryss = GM_sVektSirk(sa,sn,radius,ka,kn,la,ln,a1,n1,a2,n2);

                        /* Sjekk om punktene ligger på linjen */
   if (kryss > 0){
       minn = min(kn,ln) - ACCY;
       mina = min(ka,la) - ACCY;
       maxn = max(kn,ln) + ACCY;
       maxa = max(ka,la) + ACCY;

       if (kryss == 2){
           if (! (*a2 <= maxa  &&  *a2 >= mina  &&
                  *n2 <= maxn  &&  *n2 >= minn)){
               kryss = 1;            /* Utenfor linjen */
           }
       }

       if (! (*a1 <= maxa && *a1 >= mina  &&  *n1 <= maxn && *n1 >= minn)){
                                 /* Utenfor linjen */
           if (kryss == 2){      /* Flytt ned forrige skjæringspunkt */
               kryss = 1;
               *a1 = *a2;
               *n1 = *n2;
           } else{
               kryss = 0;        /* Ikke noe skjæringspunkt */
           }
       }
   }

                        /* Sjekk om punktene ligger på buen */
   if (kryss > 0){
      if (kryss == 2){
         if ( ! GM_TestPktBue(sa,sn,fi,dfi,*a2,*n2)){
            kryss = 1;            /* Utenfor buen */
         }
      }

      if ( ! GM_TestPktBue(sa,sn,fi,dfi,*a1,*n1)){
         if (kryss == 2){      /* Flytt ned forrige skjæringspunkt */
            kryss = 1;
            *a1 = *a2;
            *n1 = *n2;
         } else{
            kryss = 0;        /* Ikke noe skjæringspunkt */
         }
      }
   }

   return kryss;
}


/*
AR-901209
CH GM_sVektSirk                     Skjæring mellom uendelig linje og sirkel
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom en uendelig linje (K-L) og en sirkel.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   sa       i    Koordinat i sirkelens sentrum.
CD double   sn       i
CD double   radius   i    Sirkelens radius.
CD double   ka       i    Koordinat i K.
CD double   kn       i
CD double   la       i    Koordinat i L.
CD double   ln       i
CD double  *a1       u    Koordinat i skjæringspunkt 1
CD double  *n1       u
CD double  *a2       u    Koordinat i skjæringspunkt 2
CD double  *n2       u
CD short    kryss    r    Antall skjæringspunkter (0, 1 eller 2)
CD
CD Bruk:
CD kryss = GM_sVektSirk(sa,sn,radius,ka,kn,la,ln,&a1,&n1,&a2,&n2);
   ==========================================================================
*/
SK_EntPnt_GM short GM_sVektSirk(double sa,double sn,double radius,
                             double ka,double kn,double la,double ln,
                             double *a1,double *n1,double *a2,double *n2)
{
   short kryss = 0;
   double f,g,root,fsq,gsq,fgsq,xj0,yj0,fygx,fxgy,t,fginv,t1,t2;

            /* Beregn skjæring mellom uendelig vektor og sirkelen */
                                       /* Parametre for K-L */
   f = la - ka;
   g = ln - kn;
                                             /* Beregn skjæring */
   fsq = f * f;
   gsq = g * g;
   fgsq = fsq + gsq;
   if (fgsq > ACCY){                       /* Linjen er ok */
       xj0 = sa - ka;
       yj0 = sn - kn;
       fygx = f*yj0 - g*xj0;
       root = radius*radius*fgsq - fygx*fygx;
       if (root > -ACCY){             /* Linjen berører sirkelen */
           fxgy = f*xj0 + g*yj0;
           if (root < ACCY){             /* Linjen tangerer sirkelen */
               kryss = 1;
               t = fxgy / fgsq;
               *a1 = ka + f*t;
               *n1 = kn + g*t;

           } else{                       /* Linjen skjærer sirkelen */
               kryss = 2;
               root = sqrt(root);
               fginv = 1.0 / fgsq;
               t1 = (fxgy - root) * fginv;
               t2 = (fxgy + root) * fginv;
               *a1 = ka + f*t1;
               *n1 = kn + g*t1;
               *a2 = ka + f*t2;
               *n2 = kn + g*t2;
           }
       }
   }

   return kryss;
}


/*
AR-901209
CH GM_sBueBue                                   Skjæringspunkt mellom 2 buer
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom 2 buer.
CD NB! Retningen oppgis i radianer, med retning 0 i øst-aksen, og med positiv
CD omløpsretning mot urviseren. Alle vinkler er i området 0 - 2PI.
CD Metode: Se Bowyer and Woodwark: AProgrammer's Geometry, side 27-28.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   sa1      i    Koordinat i buens sentrum.
CD double   sn1      i
CD double   radius1  i    Buens radius.
CD double   fi1      i    Retning fra sentrum til buens startpunkt
CD double   dfi1     i    Vinkel mellom retning til buens startpunkt og sluttpunkt
CD double   sa2      i    Koordinat i buens sentrum.
CD double   sn2      i
CD double   radius2  i    Buens radius.
CD double   fi2      i    Retning fra sentrum til buens startpunkt
CD double   dfi2     i    Vinkel mellom retning til buens startpunkt og sluttpunkt
CD double  *a1       u    Koordinat i skjæringspunkt 1
CD double  *n1       u
CD double  *a2       u    Koordinat i skjæringspunkt 2
CD double  *n2       u
CD short    kryss    r    Antall skjæringspunkter (0, 1 eller 2)
CD
CD Bruk:
CD kryss = GM_sBueBue(as1,ns1,fi1,dfi1,as2,ns2,fi2,dfi2,&a1,&n1,&a2,&n2);
   ==========================================================================
*/
SK_EntPnt_GM short GM_sBueBue(double as1,double ns1,double radius1,double fi1,double dfi1,
                           double as2,double ns2,double radius2,double fi2,double dfi2,
                           double *a1,double *n1,double *a2,double *n2)
{
   short kryss;

   /*
    * Beregner først skjæring mellom to sirkler.
    * Sjekker etterpå om skjæringspunktene ligger på buene.
    */

   kryss = GM_sSirkSirk(as1,ns1,radius1,as2,ns2,radius2,a1,n1,a2,n2);

   /* Sjekk om punktene ligger inne på de aktuelle buene */
   if (kryss > 0){
      /* Sjekk om skjæringspunkt 2 ligger på bue 1 */
      if (kryss == 2){
         if ( ! GM_TestPktBue(as1,ns1,fi1,dfi1,*a2,*n2)){
            kryss = 1;            /* Utenfor buen */
         }

         /* Sjekk om skjæringspunkt 2 også ligger på bue 2 */
         if (kryss == 2){
            if ( ! GM_TestPktBue(as2,ns2,fi2,dfi2,*a2,*n2)){
               kryss = 1;            /* Utenfor buen */
            }
         }
      }

      /* Sjekk om skjæringspunkt 1 ligger på bue 1 */
      if ( ! GM_TestPktBue(as1,ns1,fi1,dfi1,*a1,*n1)){
         if (kryss == 2){      /* Flytt ned forrige skjæringspunkt */
            kryss = 1;
            *a1 = *a2;
            *n1 = *n2;
         } else {
            kryss = 0;        /* Ikke noe skjæringspunkt */
         }
      }

      if (kryss > 0){
      /* Sjekk om skjæringspunkt 1 også ligger på bue 2 */
         if ( ! GM_TestPktBue(as2,ns2,fi2,dfi2,*a1,*n1)){
            if (kryss == 2){      /* Flytt ned forrige skjæringspunkt */
               kryss = 1;
               *a1 = *a2;
               *n1 = *n2;
            } else{
               kryss = 0;        /* Ikke noe skjæringspunkt */
            }
         }
      }
   }

   return kryss;
}


/*
AR-901209
CH GM_sSirkSirk                              Skjæringspunkt mellom 2 sirkler
CD ==========================================================================
CD Formål:
CD Beregner skjæringspunkt mellom 2 sirkler.
CD Metode: Se Bowyer and Woodwark: AProgrammer's Geometry, side 27-28.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   sa1      i    Koordinat i sirklens sentrum.
CD double   sn1      i
CD double   radius1  i    Sirklens radius.
CD double   sa2      i    Koordinat i sirklens sentrum.
CD double   sn2      i
CD double   radius2  i    Sirklens radius.
CD double  *a1       u    Koordinat i skjæringspunkt 1
CD double  *n1       u
CD double  *a2       u    Koordinat i skjæringspunkt 2
CD double  *n2       u
CD short    kryss    r    Antall skjæringspunkter (0, 1 eller 2)
CD
CD Bruk:
CD kryss = GM_sSirkSirk(as1,ns1,as2,ns2,&a1,&n1,&a2,&n2);
   ==========================================================================
*/
SK_EntPnt_GM short GM_sSirkSirk(double as1,double ns1,double radius1,
                             double as2,double ns2,double radius2,
                             double *a1,double *n1,double *a2,double *n2)
{
   double r1sq,r2sq,a21,n21,distsq,dstinv,sumrsq,root,a,n,afac,nfac;
   double scl,delrsq;
   short kryss = 0;

   /*
    * Beregner skjæring mellom to sirkler.
    */

   r1sq = radius1 * radius1;
   r2sq = radius2 * radius2;
   a21 = as2 - as1;
   n21 = ns2 - ns1;

                                       /* Beregn kvadrert lengden L-K */
   distsq = a21*a21 + n21*n21;

   if (distsq > ACCY){    /* Ikke sammenfallende punkt */
      delrsq = r2sq - r1sq;
      sumrsq = r1sq + r2sq;
      root = 2.0*sumrsq*distsq - distsq*distsq - delrsq*delrsq;

      if (root > -ACCY){              /* Sirklene skjærer */
         dstinv = 0.5 / distsq;
         scl = 0.5 - delrsq*dstinv;
         a = as1 + a21*scl;
         n = ns1 + n21*scl;

         if (root < ACCY){        /* 1 tangeringspunkt */
            *a1 = a;
            *n1 = n;
            kryss = 1;

         } else{        /* 2 skjæringspunkter */
            root = dstinv * sqrt(root);
            afac = a21 * root;
            nfac = n21 * root;

            *a1 = a - nfac;
            *n1 = n + afac;
            *a2 = a + nfac;
            *n2 = n - afac;
            kryss = 2;
         }
      }
   }

   return kryss;
}


/*
AR-890904
JAØ-1999-02-03
CH GM_fotp                                       Fotpunkt på linje fra punkt
CD ==========================================================================
CD Formål:
CD Beregner fotpunktet  på linjen 1-2 fra punktet P.
CD
CD                               *P
CD                               !
CD                               !
CD                     1*--------*---------*2
CD                               F
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   a1       i    Koordinat i 1
CD double   n1       i
CD double   a2       i    Koordinat i 2
CD double   n2       i
CD double   ap       i    Koordinat i P
CD double   np       i
CD double  *af       u    Koordinat i fotpunktet
CD double  *nf       u
CD short    kryss    r    0=ikke beregnet (brukes ikke)
CD                        1=beregnet, men punktet er utenfor linjen
CD                        2=bregnet, ok
CD
CD Bruk:
CD kryss = GM_fotp(a1,n1,a2,n2,ap,np,&af,&nf);
   ==========================================================================
*/
SK_EntPnt_GM short GM_fotp(double a1,double n1,double a2,double n2,double ap,double np,
                        double *af,double *nf)
{
   //double pa1,pb1,pc1,pa2,pb2,pc2;
   double ap1,np1,ap2,np2,retning,a1u,n1u,a2u,n2u;
   short beregnet = 0;


   if (fabs(a2-a1) < ACCY) {
      /* Punkt 1 og 2 er sammenfallende */
      if (fabs(n2-n1) < ACCY) {
         *af = a1;
         *nf = n1;

      /* Vertikal linje */
      } else { 
         *af = a1;
         *nf = np;
      }

      /* Sjekk at fotpunktet er på linjen */
      //if ( (*nf <= max(n1,n2)+ACCY)  &&  (*nf >= min(n1,n2)-ACCY) ) {
      if ( (*nf <= max(n1,n2))  &&  (*nf >= min(n1,n2)) ) {
         beregnet = 2;
      } else {
         beregnet = 1;
      }

   /* Horisontal linje */
   } else if (fabs(n2-n1) < ACCY) {
      *af = ap;
      *nf = n1;

      /* Sjekk at fotpunktet er på linjen */
      //if ( (*af <= max(a1,a2)+ACCY)  &&  (*af >= min(a1,a2)-ACCY) ) {
      if ( (*af <= max(a1,a2))  &&  (*af >= min(a1,a2)) ) {
         beregnet = 2;
      } else {
         beregnet = 1;
      }
   }

   /* ---------- Skrå linje */
   if ( ! beregnet) {
      //JAØ-20001205 Prøver ny metode å beregne fotpunkt, pga avrundingsproblemer ved små verdier.
      retning = GM_RetnGon(a1,n1,a2,n2);
      //Utvider linjene "uendelig" for å være sikker på å få kryssing
      a1u = a1; a2u = a2; n1u = n1; n2u = n2;
      GM_PolRettv(&a1u,&n1u,retning+200.0,100000000);
      GM_PolRettv(&a2u,&n2u,retning,100000000);
      ap1 = ap; ap2 = ap; np1 = np; np2 = np;
      GM_PolRettv(&ap1,&np1,retning+100.0,100000000);
      GM_PolRettv(&ap2,&np2,retning-100.0,100000000);
      GM_sLinLin(a1u,n1u,a2u,n2u,ap1,np1,ap2,np2,af,nf); //Da gikk det bedre!

      //JAØ-20001205 Fjernet gammel måte å beregne fotpunkt, pga avrundingsproblemer ved små verdier.
      /*
      // Parametre for 1-2
      if (GM_bepa(a1,n1,a2,n2,&pa1,&pb1,&pc1)){
         // Parametre for P-F 
         pa2=pb1;
         pb2=-pa1;
         pc2=pa1*np-pb1*ap;
         // Fotpunktet 
         GM_cint(pa1,pb1,pc1,pa2,pb2,pc2,af,nf);
      }
     */

      /* Sjekk at fotpunktet er på linjen */
      //if (*nf <= (max(n1,n2)+ACCY)  &&  *nf >= (min(n1,n2)-ACCY)  &&
      //   *af <= (max(a1,a2)+ACCY)  &&  *af >= (min(a1,a2)-ACCY)){
      if (*nf <= (max(n1,n2))  &&  *nf >= (min(n1,n2))  &&
         *af <= (max(a1,a2))  &&  *af >= (min(a1,a2))){
         beregnet = 2;                     /* På linjen */
      } else {
         beregnet = 1;            /* Utenfor linjen */
      }
   }

   return beregnet;                
}

/*
IR-2011-05-05
CH GM_fotp                                       Fotpunkt på line frå punkt
CD ==========================================================================
CD Formål:
CD Bereknar fotpunktet  på lina 1-2 frå punktet P (i 2D).
CD (Ein kan bruke same metoden i 3D, ved å ta med z-koordinatane i tillegg.)
CD Sjå http://paulbourke.net/geometry/sphereline  for dokumentasjon.
CD
CD                               *P
CD                               !
CD                               !
CD                     1*--------*---------*2
CD                               F
CD
CD Parametrar:
CD Type     Namn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   a1       i    Koordinat i 1
CD double   n1       i
CD double   a2       i    Koordinat i 2
CD double   n2       i
CD double   ap       i    Koordinat i P
CD double   np       i
CD double  *af       u    Koordinat i fotpunktet
CD double  *nf       u
CD short    kryss    r    0=ikkje berekna (blir ikkje brukt)
CD                        1=berekna, men punktet er utanfor lina
CD                        2=berekna, ok
CD
CD Bruk:
CD kryss = GM_fotp(a1,n1,a2,n2,ap,np,&af,&nf);
   ==========================================================================
*/
// SK_EntPnt_GM short GM_fotp_ny(double a1,double n1,double a2,double n2,double ap,double np,
//                         double *af,double *nf)



SK_EntPnt_GM short GM_fotp_ny(double a1, double n1, double a2, double n2, double ap, double np,
                        double *af, double *nf)
{
	double da12, dn12, da1p, dn1p, teljar, nemnar, u;
	short godfot;
	
	da12 = a2 - a1;
	dn12 = n2 - n1;
	da1p = ap - a1;
	dn1p = np - n1;
	teljar = da1p * da12 + dn1p * dn12;
	nemnar = da12 * da12 + dn12  * dn12;
	
	if (nemnar == 0) // lina 1-2 er nullvektor
	{	 
	  *af = a1;
	  *nf = n1;
	  godfot = 2;
	}
	else 
	{
	  u = teljar / nemnar;
	  *af = a1 + u * da12;
	  *nf = n1 + u * dn12;
	  if ( (u >= 0) && (u <= 1)) 
	  {
		 godfot = 2;
	  }
	  else 
	  {
		 godfot = 1;
	  }
	}
	
	return godfot;
}

#ifdef TEST
{
   //double pa1,pb1,pc1,pa2,pb2,pc2;
   double retning;

   double ap1=ap;
   double np1=np;
   short beregnet = 0;
   double dn=fabs(n2-n1);
   double da=fabs(a2-a1);

   if (da < ACCY) {
      /* Punkt 1 og 2 er sammenfallende */
      if (dn < ACCY) {
         *af = a1;
         *nf = n1;

      /* Vertikal linje */
      } else { 
         *af = a1;
         *nf = np;
      }

      /* Sjekk at fotpunktet er på linjen */
      if ( (*nf <= max(n1,n2)+ACCY)  &&  (*nf >= min(n1,n2)-ACCY) ) {
         beregnet = 2;
      } else {
         beregnet = 1;
      }

   /* Horisontal linje */
   } else if (dn < ACCY) {
      *af = ap;
      *nf = n1;

      /* Sjekk at fotpunktet er på linjen */
      if ( (*af <= max(a1,a2)+ACCY)  &&  (*af >= min(a1,a2)-ACCY) ) {
         beregnet = 2;
      } else {
         beregnet = 1;
      }
   }

   /* ---------- Skrå linje */
   if ( ! beregnet) {

      // AR 2000-12-10
      // Forslag til ny metode for fotpunktberegning. Endrer ikke de opprinnelige punktene,
      // og det blir da mulig å gi korrekt tilbakemelding om punktet ligger inne på den gitte linjen.
      retning = GM_RetnGon(a1,n1,a2,n2);
      GM_PolRettv(&ap1, &np1, retning+100.0, max(da,dn));
      GM_sVektVekt(a1,n1,a2,n2,ap,np,ap1,np1,af,nf);
      
      /* Sjekk at fotpunktet er på linjen */
      if (*nf <= (max(n1,n2)+ACCY)  &&  *nf >= (min(n1,n2)-ACCY)  &&
         *af <= (max(a1,a2)+ACCY)  &&  *af >= (min(a1,a2)-ACCY)){
         beregnet = 2;                     /* På linjen */
      } else {
         beregnet = 1;            /* Utenfor linjen */
      }
   }

   return beregnet;                
}
#endif


/*
AR-991012
CH GM_Parallell                                       Parallellforskyver linje
CD ==========================================================================
CD Formål:
CD  Parallellforskyver linjen K-L gitt avstand normalt til siden. 
CD
CD
CD                     L1        L         L1
CD                      *- - - - * - - - - *
CD                               !
CD                      !        !         !
CD                               !
CD                      !        !         !
CD                               !
CD                      !        !         !
CD                               !
CD                      *- - - - * - - - - *
CD                     K1        K         K1
CD
CD
CD               avstand < 0            avstand > 0
CD
CD
CD
CD Parametre:
CD Type     Navn       I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   ka          i    Koordinat i K
CD double   kn          i
CD double   la          i    Koordinat i L
CD double   ln          i
CD double   avstand     i    Forskyving (>0 = til høyre(K2-L2), <0 = til venstre(K1-L1))
CD double  *ka1         u    Koordinat i K1
CD double  *kn1         u
CD double  *la1         u    Koordinat i L1
CD double  *ln1         u
CD bool     status s    r    UT_FALSE = ikke beregnet (K og L har like koordinater)
CD                           UT_TRUE = bregnet, ok
CD
CD Bruk:
CD status = GM_Parallell(ka,kn,la,ln,avstand,&ka1,&kn1,&la1,&ln1);
   ==========================================================================
*/
SK_EntPnt_GM short GM_Parallell(double ka,double kn,double la,double ln,double avstand,
                               double *ka1,double *kn1,double *la1,double *ln1)
{
   double fi, da, dn;


   /* Punkt 1 og 2 er sammenfallende, klarer ikke å beregne */
   if (fabs(ka-la) < ACCY  &&  fabs(kn-ln) < ACCY) {
      *ka1 = ka;
      *kn1 = kn;
      *la1 = la;
      *ln1 = ln;
      return UT_FALSE;
   }

   /* Ingen forskyving */
   if (fabs(avstand) <= ACCY) {
      *ka1 = ka;
      *kn1 = kn;
      *la1 = la;
      *ln1 = ln;
      return UT_TRUE;
   }

   /* Beregner retninger fra K til L */
   fi = GM_retning(ka,kn,la,ln);

   /* Forskyvingsretning */
   if ( avstand < ACCY ) {   /* Forskyving til venstre */            
      fi += PI/2;
   } else {                     /* Forskyving til høyre */
      fi -= PI/2;
   }

   /* Beregner nye koordinater */
   avstand = fabs (avstand);
   da = avstand * cos(fi);
   dn = avstand * sin(fi);
   *ka1 = ka + da;
   *kn1 = kn + dn;
   *la1 = la + da;
   *ln1 = ln + dn;

   return UT_TRUE;                
}

 
/*
AR-890723
CH GM_KonvBue                             Omregning til intern bue-angivelse
CD ==========================================================================
CD Formål:
CD Omregning til intern bue-angivelse med sirkelsentrum, radius og retning
CD til buens start samt delta for sluttpunktet.
CD NB! Retningen oppgis i radianer, med retning 0 i øst-aksen, og med positiv
CD omløpsretning mot urviseren. Alle vinkler er i området 0 - 2PI.
CD Metode: Se Bowyer and Woodwark: AProgrammer's Geometry,
CD         side 27-28 og 35-36.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   a1       i    Koordinat i P1
CD double   n1       i
CD double   a2       i    Koordinat i P2
CD double   n2       i
CD double   radius   i    Buens radius (med fortegn)
CD short    storbue  i    Storbue (1=storbue, 0=ikke storbue)
CD double  *as       u    Koordinat i sentrumspunktet
CD double  *ns       u
CD double  *fi       u    "Retning" sentrum - punkt 1.
CD double  *dfi      u    Vinkel mellom fi og retning  sentrum - punkt 2.
CD short    beregnet r    0=kan ikke beregne,  1=bregnet ok.
CD
CD Bruk:
CD ok = GM_KonvBue(a1,n1,a2,n2,radius,storbue,&as,&ns,&fi,&dfi);
   ==========================================================================
*/
SK_EntPnt_GM short GM_KonvBue(double a1,double n1,double a2,double n2,double radius,
                           short storbue,double *as,double *ns,double *fi,double *dfi)
{
   double rsq,a21,n21,distsq,dstinv,sumrsq,root,a,n,afac,nfac,fi2,f1;
   short beregnet = 0;

   rsq = radius * radius;
   a21 = a2 - a1;
   n21 = n2 - n1;

                                       /* Beregn kvadrert lengden L-K */
   distsq = a21*a21 + n21*n21;

   if (distsq > ACCY) {    /* Ikke sammenfallende punkt */
      sumrsq = rsq + rsq;
      root = 2.0*sumrsq*distsq - distsq*distsq;

      if (root > -ACCY) {        /* Sirklene skjærer eller tangerer */
         beregnet = 1;
         dstinv = 0.5 / distsq;
         a = a21 * 0.5 + a1;
         n = n21 * 0.5 + n1;

         if (root > ACCY) {        /* 2 skjæringspunkter */
            root = dstinv * sqrt(root);
            afac = a21 * root;
            nfac = n21 * root;
            if ((radius < 0.0  && storbue == 0) ||
                (radius > 0.0  && storbue == 1) )
            {
               *as = a - nfac;             /* Bruker 1. skjæringspunkt */
               *ns = n + afac;
            } else {
               *as = a + nfac;             /* Bruker 2. skjæringspunkt */
               *ns = n - afac;
            }

         } else {        /* Tangering */
            *as = a;
            *ns = n;
         }

         /* Beregn retninger fra sentrum til start og sluttpunkt */
         *fi = GM_retning(*as,*ns,a1,n1);    /* S - K */
         f1 = *fi;
         fi2 = GM_retning(*as,*ns,a2,n2);    /* S - L */

                           /* Beregner retningsavvik */
         if (radius < 0.0)
         {
            if (fi2 < f1)  fi2 += (PI*2.0);
         } else {
            if (f1 < fi2)  f1 += (PI*2.0);
         }
         *dfi = fi2 - f1;
      }
   }

   return beregnet;
}


/*
AR-890723
CH GM_KonvBuep                            Omregning til intern bue-angivelse
CD ==========================================================================
CD Formål:
CD Omregning til intern bue-angivelse med sirkelsentrum, radius og retning
CD til buens start samt delta for sluttpunktet.
CD NB! Retningen oppgis i radianer, med retning 0 i øst-aksen, og med positiv
CD omløpsretning mot urviseren. Alle vinkler er i området 0 - 2PI.
CD Metode: Se Bowyer and Woodwark: AProgrammer's Geometry,
CD         side 27-28 og 35-36.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   a1       i    Koordinat i P1  (startpunkt)
CD double   n1       i
CD double   a2       i    Koordinat i P2  (punkt på buen)
CD double   n2       i
CD double   a3       i    Koordinat i P3  (sluttpunkt)
CD double   n3       i
CD double  *as       u    Koordinat i sentrumspunktet
CD double  *ns       u
CD double  *radius   u    Buens radius
CD double  *fi       u    "Retning" sentrum - punkt 1.
CD double  *dfi      u    Vinkel mellom fi og retning  sentrum - punkt 3.
CD short    beregnet r    0=kan ikke beregne,  1=bregnet ok.
CD
CD Bruk:
CD ok = GM_KonvBuep(a1,n1,a2,n2,a3,n3,&as,&ns,&radius,&fi,&dfi);
   ==========================================================================
*/
SK_EntPnt_GM short GM_KonvBuep(double a1,double n1,double a2,double n2,double a3,double n3,
                            double *as,double *ns,double *radius,double *fi,double *dfi)
{
   double ap,np,fi2,fi3,dfi2,dfi3;
   double pa1,pb1,pc1,pa2,pb2,pc2,pa3,pb3,pc3;
   short beregnet = 0;

   /* Parametre for linjen 1 - 3 */
   if(GM_bepa(a1,n1,a3,n3,&pa1,&pb1,&pc1)){
      /* Midtpunktet mellom 1 og 3 */
      ap = a1 +  (a3-a1) / 2.0;
      np = n1 +  (n3-n1) / 2.0;

      /* Parametre for midtlinjen mellom 1 og 3 */
      pa3=pb1;
      pb3=-pa1;
      pc3=pa1*np-pb1*ap;

      /* Parametre for linjen 1 - 2 */
      if(GM_bepa(a1,n1,a2,n2,&pa1,&pb1,&pc1)){
         /* Midtpunktet mellom 1 og 2 */
         ap = a1  +  (a2-a1) / 2.0;
         np = n1  +  (n2-n1) / 2.0;

         /* Parametre for midtlinjen mellom 1 og 2 */
         pa2=pb1;
         pb2=-pa1;
         pc2=pa1*np-pb1*ap;

         /* Sentrum er skjæringspunktet mellom de to linjene */
         if (GM_cint(pa3,pb3,pc3,pa2,pb2,pc2,as,ns)){
            *radius = sqrt((*as-a1)*(*as-a1) + (*ns-n1)*(*ns-n1));

                  /* Beregn retninger fra sentrum til start og sluttpunkt */
            *fi = GM_retning(*as,*ns,a1,n1);    /* S - P1 */
            fi2 = GM_retning(*as,*ns,a2,n2);    /* S - P2 */
            fi3 = GM_retning(*as,*ns,a3,n3);    /* S - P3 */

                              /* Beregner retningsavvik */
            dfi2 = fi2 - *fi;
            dfi3 = fi3 - *fi;

            /* Positiv delta ? */
            if (dfi2 < 0.0)  dfi2 += (PI*2.0);
            if (dfi3 < 0.0)  dfi3 += (PI*2.0);
            if (dfi2 <= dfi3){
               *dfi = dfi3;
            } else{
               /* Negativ delta */
               if (dfi3 > 0.0)  dfi3 -= (PI*2.0);
               *dfi = dfi3;
            }

            beregnet = 1;
         }
      }
   }

   return beregnet;
}


/*
AR-911029
CH GM_KonvSirkel                         Omregning til intern bue-angivelse
CD ==========================================================================
CD Formål:
CD Omregning til intern bue-angivelse med sirkelsentrum, radius og retning
CD til buens start samt delta for sluttpunktet.
CD NB! Retningen oppgis i radianer, med retning 0 i øst-aksen, og med positiv
CD omløpsretning mot urviseren. Alle vinkler er i området 0 - 2PI.
CD Metode: Se Bowyer and Woodwark: AProgrammer's Geometry,
CD         side 27-28 og 35-36.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  *as       iu   Koordinat i sentrumspunktet
CD double  *ns       iu
CD double  *radius   iu   Buens radius
CD double  *fi       u    "Startretning"  sentrum - punkt 1.
CD double  *dfi      u    "Åpningsvinkel" (2PI).
CD short    ist      r    1 = OK, 0 = ikke beregnet.
CD
CD Bruk:
CD ist = GM_KonvSirkel(&as,&ns,&radius,&fi,&dfi);
   ==========================================================================
*/
SK_EntPnt_GM short GM_KonvSirkel(double *fi,double *dfi)
{

   *fi = 0.0;
   *dfi = 2.0 * PI;

   return 1;
}


/*
AR-911029
CH GM_KonvSirkelp                         Omregning til intern bue-angivelse
CD ==========================================================================
CD Formål:
CD Omregning til intern bue-angivelse med sirkelsentrum, radius og retning
CD til buens start samt delta for sluttpunktet.
CD NB! Retningen oppgis i radianer, med retning 0 i øst-aksen, og med positiv
CD omløpsretning mot urviseren. Alle vinkler er i området 0 - 2PI.
CD Metode: Se Bowyer and Woodwark: AProgrammer's Geometry,
CD         side 27-28 og 35-36.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   a1       i    Koordinat i P1  (punkt på buen)
CD double   n1       i
CD double   a2       i    Koordinat i P2  (punkt på buen)
CD double   n2       i
CD double   a3       i    Koordinat i P3  (punkt på buen)
CD double   n3       i
CD double  *as       u    Koordinat i sentrumspunktet
CD double  *ns       u
CD double  *radius   u    Buens radius
CD double  *fi       u    "Retning" sentrum - start av buen (0)
CD double  *dfi      u    Åpningsvinkel (2*PI)
CD short    beregnet r    1 = OK; 0 = kan ikke beregne.
CD
CD Bruk:
CD ist = GM_KonvSirkelp(a1,n1,a2,n2,a3,n3,&as,&ns,&radius,&fi,&dfi);
   ==========================================================================
*/
SK_EntPnt_GM short GM_KonvSirkelp(double a1,double n1,double a2,double n2,double a3,double n3,
                               double *as,double *ns,double *radius,double *fi,double *dfi)
{
   double ap,np;
   double pa1,pb1,pc1,pa2,pb2,pc2,pa3,pb3,pc3;
   short beregnet = 0;

   /* Parametre for linjen 1 - 3 */
   if(GM_bepa(a1,n1,a3,n3,&pa1,&pb1,&pc1)){
      /* Midtpunktet mellom 1 og 3 */
      ap = a1 + (a3-a1)/2.0;
      np = n1 + (n3-n1)/2.0;

      /* Parametre for midtlinjen mellom 1 og 3 */
      pa3=pb1;
      pb3=-pa1;
      pc3=pa1*np-pb1*ap;

      /* Parametre for linjen 1 - 2 */
      if(GM_bepa(a1,n1,a2,n2,&pa1,&pb1,&pc1)){
         /* Midtpunktet mellom 1 og 2 */
         ap = a1 + (a2-a1)/2.0;
         np = n1 + (n2-n1)/2.0;

         /* Parametre for midtlinjen mellom 1 og 2 */
         pa2=pb1;
         pb2=-pa1;
         pc2=pa1*np-pb1*ap;

         /* Sentrum er skjæringspunktet mellom de to linjene */
         if (GM_cint(pa3,pb3,pc3,pa2,pb2,pc2,as,ns)){
            *radius = sqrt((*as-a1)*(*as-a1) + (*ns-n1)*(*ns-n1));

            /* Beregn retninger fra sentrum til start og sluttpunkt */
            *fi = GM_retning(*as,*ns,a1,n1);
            *dfi = 2.0 * PI;

            beregnet = 1;
         }
      }
   }

   return beregnet;
}


/*
AR-881018
CH GM_bepa                                                    Linjeparametre
CD ==========================================================================
CD Formål:
CD Beregner parametrene for linjen gjennom 1 og 2.
CD Ligningen for linjen er: (AX+BY+C=0).
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   a1       i    Koordinat i 1
CD double   n1       i
CD double   a2       i    Koordinat i 2
CD double   n2       i
CD double  *pa       u    Parametre for linjen
CD double  *pb       u
CD double  *pc       u
CD short    ist      r    1=beregnet, 0=ikke beregnet (1 og 2 er samme punkt)
CD
CD Bruk:
CD ist = GM_bepa(a1,n1,a2,n2,&pa,&pb,&pc);
   ==========================================================================
*/
SK_EntPnt_GM short GM_bepa(double a1, double n1, double a2, double n2,
                        double *pa, double *pb, double *pc)
{
   double ndif,adif,rinv,atmp,ntmp,dmn,dmx,div;

   adif = a2-a1;
   atmp = fabs(adif);
   ndif = n2-n1;
   ntmp = fabs(ndif);


   if(atmp > ACCY  ||  ntmp > ACCY) {
   
      dmx = max(atmp,ntmp);
      dmn = min(atmp,ntmp);
      div = dmn / dmx;

      rinv = 1.0 / (dmx * sqrt(1.0+div*div));
      *pa = -ndif*rinv;
      *pb =  adif*rinv;
      //*pc = (a1*n2 - a2*n1) * rinv;
      {
         double d1 = a1*n2;
         double d2 = a2*n1;
         double d3 = d1 - d2;
         *pc = d3 * rinv;
      }

      // -56430.600006104

      return (1);
   } else {
      *pa = *pb = *pc = 0.0;
      return (0);
   }
}


/*
AR-940522
CH GM_bepa3                                                3D-Linjeparametre
CD ==========================================================================
CD Formål:
CD Beregner 3D parametrene for linjen gjennom 1 og 2.
CD Ligningen for linjen er: (AX+BY+C=0).
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   a1       i    Koordinat i 1
CD double   n1       i
CD double   h1       i
CD double   a2       i    Koordinat i 2
CD double   n2       i
CD double   h2       i
CD double  *pf       u    Parametre for linjen
CD double  *pg       u
CD double  *ph       u
CD short    ist      r    1=beregnet, 0=ikke beregnet (1 og 2 er samme punkt)
CD
CD Bruk:
CD ist = GM_bepa3(a1,n1,h1,a2,n2,h2,&pa,&pb,&pc);
   ==========================================================================
*/
SK_EntPnt_GM short GM_bepa3(double a1, double n1, double h1,
                         double a2, double n2, double h2,
                         double *pf, double *pg, double *ph)
{
   double ndif,adif,hdif,rsq,rinv;

   ndif = n2-n1;
   adif = a2-a1;
   hdif = h2-h1;
   rsq = ndif*ndif + adif*adif + hdif*hdif;
   if(rsq > ACCY){
       rinv = 1.0 / sqrt(rsq);
       *pf = adif * rinv;
       *pg = ndif * rinv;
       *ph = hdif * rinv;
       return (1);
   } else{
       *pf = *pg = *ph = 0.0;
       return (0);
   }
}


/*
AR-890717
CH GM_cint                                         Skjæring mellom to linjer
CD ==========================================================================
CD Formål:
CD Beregner kryssingspunktet mellom to linjer.
CD Linjene er gitt på implisitt form.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   pa1      i    Parametre for linje 1
CD double   pb1      i
CD double   pc1      i
CD double   pa2      i    Parametre for linje 2
CD double   pb2      i
CD double   pc2      i
CD double  *as       u    Koordinat i skjæringspunktet
CD double  *ns       u
CD short    kryss    r    1=beregnet, 0=ikke beregnet (pralelle linjer)
CD
CD Bruk:
CD kryss = GM_cint(pa1,pb1,pc1,pa2,pb2,pc2,&as,&ns);
   ==========================================================================
*/
SK_EntPnt_GM short GM_cint(double pa1, double pb1, double pc1, double pa2, double pb2,
                        double pc2, double *as, double *ns)
{
   double det,dinv;

                /* Beregner skjæringspunktet mellom linjene på implicit form */
   det = pa1*pb2 - pa2*pb1;
   if (fabs(det) > ACCY){
       dinv = 1.0/det;
       *as = (pb1*pc2 - pb2*pc1) * dinv;
       *ns = (pa2*pc1 - pa1*pc2) * dinv;
       return(1);
   } else{
       *ns = *as = 0.0;
       return(0);
   }
}



/*
JEK-920514
CH GM_Vinkel                     Beregner vinkel mellom to retninger
CD ==================================================================
CD Formål:
CD Beregner positiv vinkel mellom to retninger fi1 og fi2.
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD ------------------------------------------------------------------
CD fi1       double       i   Retningsvinkel 1
CD fi2       double       i   retningsvinkel 2
CD vinkel    double       r   Positiv vinkel i rad. mellom fi1 og fi2
CD                            Alltid i området 0 - 2PI.
CD
CD Bruk : vinkel = GM_Vinkel(fi1,fi2);
   ==================================================================
*/
SK_EntPnt_GM double GM_Vinkel(double fi1, double fi2)
{
   return GM_RedVinkel(fi2 - fi1);
}


/*
JEK-920514
CH GM_RedVinkel                Beregner en retn.vinkel i omr. 0-2*PI
CD ==================================================================
CD Formål:
CD Redusere en retningsvinkel til å ligge i området 0 - 2*PI.
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD ------------------------------------------------------------------
CD fi       double       i   Retningsvinkel 
CD vinkel   double       r   Redusert vinkel
CD
CD Bruk:  red_vinkel = GM_RedVinkel(fi);
   ==================================================================
*/
SK_EntPnt_GM double GM_RedVinkel(double dFi)
{
   double topi = 2.0*PI;            
   double vinkel = dFi;

   while ( vinkel < 0.0  ||  vinkel > topi ) {
      if ( vinkel < 0.0 ) {
         vinkel += topi;
      }
      if ( vinkel > topi ) {
         vinkel -= topi;
      }
   }

   return vinkel;
}


/*
AR-901021
CH GM_retning                                        Retning mellom to punkt
CD ==========================================================================
CD Formål:
CD Beregner retning fra et punkt til et annet (K-L).
CD (Rutinen er spesiellt beregnet for å beregne retningsvinkler for buer.)
CD NB! Retningen oppgis i radianer, med retning 0 i øst-aksen, og med positiv
CD omløpsretning mot urviseren.
CD
CD                             *L
CD                           /
CD                         /
CD                       /
CD                    K*
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   ak       i    Koordinat i K.
CD double   nk       i
CD double   al       i    Koordinat i L.
CD double   nl       i
CD double   retning  r    Retning K-L.
CD
CD Bruk:
CD retning = GM_retning(ak,nk,al,nl);
   ==========================================================================
*/
SK_EntPnt_GM double GM_retning(double ak,double nk,double al,double nl)
{
   double retning;
   double da = al - ak;
   double dn = nl - nk;
   
   // Beregner retning
   if (fabs(da) < ACCY  &&  fabs(dn) < ACCY) {
      retning = 0.0;
   } else {
      retning = atan2(dn,da);
   }

   // Juster til positiv retningen
   if (retning < 0.0) {
      retning += PI * 2.0; 
   }

   return retning;
}


/*
GL-910709
CH GM_RetnGon                       Beregner retningsvinkel mellom 2 punkt
CD ==========================================================================
CD Bruk   : r = GM_RetnGon(a1,n1,a2,n2)
CD ==========================================================================
*/
SK_EntPnt_GM double GM_RetnGon(double a1 , double n1, double a2, double n2)
{
   double r;
   double da = a2 - a1;
   double dn = n2 - n1;

                                       /* Beregner retning */
   if (fabs(da) < ACCY  &&  fabs(dn) < ACCY) {
      r = 0.0;
   } else {
      r = atan2(da,dn);
   }

   r = Rad2Gon(r);
   if (r < 0.0)  r += 400.0;

   return r;
}


/*
GL-910709
CH GM_RettvPol               Beregner polare koord.(retnvinkel og avstand)
CD ==========================================================================
CD Bruk   : GM_RettvPol(a1,n1,a2,n2,&gon,&avst)
CD ==========================================================================
*/
SK_EntPnt_GM void GM_RettvPol(double a1 , double n1, double a2, double n2,
                         double *gon, double *avst)
{
   *gon =GM_RetnGon(a1,n1,a2,n2);
   *avst=sqrt((a2-a1)*(a2-a1)+(n2-n1)*(n2-n1));
}


/*
CH GM_Areal                                      Beregner areal av polygon
CD ==========================================================================
CD Formål:
CD Beregner areal av polygon.
CD Forutsetter at polygonet er lukket. (Første og siste punkt er like.)
CD
CD PARAMETERLISTE:
CD Navn    Type    I/U Merknad
CD --------------------------------------------------------------------------
CD pA     *double   i   Øst-koordinater
CD pN     *double   i   Nord-koordinater
CD sNko    short    i   Antall koordinater
CD dAreal  double   r   Areal m^2
CD
CD Bruk:  areal = GM_Areal ( pA, pN, sAnt );
   ==========================================================================
*/
SK_EntPnt_GM double GM_Areal(double *pA, double *pN, short sAnt)
{
   double dAreal = 0.0;
   double a_forrige,n_forrige;
   short s = 1;

   if (sAnt > 2) {
      a_forrige = *pA;
      n_forrige = *pN;

      for ( ; s<sAnt; ++s) {
         dAreal += (a_forrige - pA[s]) * (n_forrige + pN[s]);
         a_forrige = pA[s];
         n_forrige = pN[s];
      }
   }

   return fabs(dAreal / 2.0);
}


/*
GL-910704
CH GM_PolRettv            Beregner nye rettvinkla koordinater fra gon+avst
CD ==========================================================================
CD Bruk   : GM_PolRettv(&a,&n,gon,avst)
CD ==========================================================================
*/
SK_EntPnt_GM void GM_PolRettv(double *a , double *n, double gon, double avst)
{
   *n = *n + avst * (double)cos(Gon2Rad(gon));
   *a = *a + avst * (double)sin(Gon2Rad(gon));
}


/*
AR-890919
CH GM_buebox                                          Omskreven boks for bue
CD ==========================================================================
CD Formål:
CD Beregner omskrevet rektangel for bue.
CD Buen går mot urviseren fra P1 til P2 rundt sirkelen.
CD NB! Retningen oppgis i radianer, med retning 0 i øst-aksen, og med positiv
CD omløpsretning mot urviseren.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   as       i    Koordinat i sirkelsentrum.
CD double   ns       i
CD double   radius   i    Aavstand fra senterpunkt til P1 og P2.
CD                        (Fortegn blir ignorert.)
CD double   fi       i    Retning sentrum - P1
CD double   dfi      i    Delta retning p1 og p2
CD double   nva      u    Nedre venstre hjørne  av omskrevet rektangel.
CD double   nvn      u
CD double   oha      u    Øvre høyre hjørne  av omskrevet rektangel.
CD double   ohn      u
CD
CD Bruk:
CD GM_buebox(as,ns,radius,fi,dfi,&nva,&nvn,&oha,&ohn);
   ==========================================================================
*/
SK_EntPnt_GM void GM_buebox(double as,double ns,double radius,double fi,double dfi,
                         double *nva,double *nvn,double *oha,double *ohn)
{
   double r = fabs(radius);
   double a1,n1,a2,n2;


   // ----- Hel sirkel
   if (fabs(dfi) > ((2.0*PI)-ACCY))
   {
      *nva = as - r;
      *nvn = ns - r;
      *oha = as + r;
      *ohn = ns + r;

      return;     // ==>
   }

   // ----- Andre buer

   // Starter med omskrevet boks for endepunktene
   a1 = as + r*cos(fi);
   n1 = ns + r*sin(fi);
   a2 = as + r*cos(fi+dfi);
   n2 = ns + r*sin(fi+dfi);

   *nva = min(a1,a2);
   *nvn = min(n1,n2);
   *oha = max(a1,a2);
   *ohn = max(n1,n2);

   // For hver akse (fra sentrumspunktet) som krysses utvides omskrevet boks
   radius = fabs(radius);
   if (GM_TestPktBue(as, ns, fi, dfi, as+radius, ns))  *oha = as+radius;
   if (GM_TestPktBue(as, ns, fi, dfi, as-radius, ns))  *nva = as-radius;

   if (GM_TestPktBue(as, ns, fi, dfi, as, ns+radius))  *ohn = ns+radius;
   if (GM_TestPktBue(as, ns, fi, dfi, as, ns-radius))  *nvn = ns-radius;
}



/* Gammel versjon

   double r2;
   double r = fabs(radius);
   double a1,n1,a2,n2;


   // ----- Hel sirkel
   if (fabs(dfi) > ((2.0*PI)-ACCY))
   {
      *nva = as - r;
      *nvn = ns - r;
      *oha = as + r;
      *ohn = ns + r;

      return;     // ==>
   }

   // ----- Andre buer

   a1 = as + r*cos(fi);
   n1 = ns + r*sin(fi);
   a2 = as + r*cos(fi+dfi);
   n2 = ns + r*sin(fi+dfi);

   // Beregn sorterte retninger
   if (dfi < 0.0){
      r2 = fi;
      fi += dfi;
   } else{
      r2 = fi + dfi;
   }

   // Sørg for at alle vinkler ligger i området 0 - 2*PI
   while (fi < 0.0){                       // fi
      fi +=  (2.0*PI);
   }
   while (fi > (2.0*PI)){
      fi -=  (2.0*PI);
   }
   while (r2 < 0.0){                       // r2
      r2 +=  (2.0*PI);
   }
   while (r2 > (2.0*PI)){
      r2 -=  (2.0*PI);
   }

   // Beregner omskreven firkant for buen
                                           // Start i 1. kvadrant
   if (fi >= 0.0 && fi < PI/2.0){
                                              // Slutt i 1. kvadrant
      if (r2 >= 0.0 && r2 < PI/2.0){
         *nva = min(a1,a2);
         *nvn = min(n1,n2);
         *oha = max(a1,a2);
         *ohn = max(n1,n2);
                           // Slutt i 2. kvadrant
      } else if (r2 >= PI/2.0L && r2 < PI){
         *nva = min(a1,a2);
         *nvn = min(n1,n2);
         *oha = max(a1,a2);
         *ohn = ns + r;
                           // Slutt i 3. kvadrant
      } else if (r2 >=PI && r2 < PI*3.0L/2.0L){
         *nva = as - r;
         *nvn = min(n1,n2);
         *oha = max(a1,a2);
         *ohn = ns + r;
                           // Slutt i 4. kvadrant
      } else{
         *nva = as - r;
         *nvn = ns - r;
         *oha = max(a1,a2);
         *ohn = ns + r;
      }

                           // Start i 2. kvadrant
   } else if (fi >= PI/2.0L && fi < PI){
                           // Slutt i 1. kvadrant
      if (r2 >= 0.0 && r2 < PI/2.0){
         *nva = as - r;
         *nvn = ns - r;
         *oha = as + r;
         *ohn = max(n1,n2);
                           // Slutt i 2. kvadrant
      } else if (r2 >= PI/2.0L && r2 < PI){
         *nva = min(a1,a2);
         *nvn = min(n1,n2);
         *oha = max(a1,a2);
         *ohn = max(n1,n2);
                           // Slutt i 3. kvadrant 
      } else if (r2 >=PI && r2 < PI*3.0L/2.0L){
         *nva = as - r;
         *nvn = min(n1,n2);
         *oha = max(a1,a2);
         *ohn = max(n1,n2);
                           // Slutt i 4. kvadrant 
      } else{
         *nva = as - r;
         *nvn = ns - r;
         *oha = max(a1,a2);
         *ohn = max(n1,n2);
      }

                           // Start i 3. kvadrant 
   } else if (fi >=PI && fi < PI*3.0L/2.0L){
                           // Slutt i 1. kvadrant 
      if (r2 >= 0.0 && r2 < PI/2.0){
         *nva = min(a1,a2);
         *nvn = ns - r;
         *oha = as + r;
         *ohn = max(n1,n2);
                           // Slutt i 2. kvadrant 
      } else if (r2 >= PI/2.0L && r2 < PI){
         *nva = min(a1,a2);
         *nvn = ns - r;
         *oha = as + r;
         *ohn = ns + r;
                           // Slutt i 3. kvadrant 
      } else if (r2 >=PI && r2 < PI*3.0L/2.0L){
         *nva = min(a1,a2);
         *nvn = min(n1,n2);
         *oha = max(a1,a2);
         *ohn = max(n1,n2);
      } else{
                           // Slutt i 4. kvadrant 
         *nva = min(a1,a2);
         *nvn = ns - r;
         *oha = max(a1,a2);
         *ohn = max(n1,n2);
      }

                           // Start i 4. kvadrant 
   } else {
                           // Slutt i 1. kvadrant 
      if (r2 >= 0.0 && r2 < PI/2.0) {
         *nva = min(a1,a2);
         *nvn = min(n1,n2);
         *oha = as + r;
         *ohn = max(n1,n2);
                           // Slutt i 2. kvadrant 
      } else if (r2 >= PI/2.0L && r2 < PI) {
         *nva = min(a1,a2);
         *nvn = min(n1,n2);
         *oha = as + r;
         *ohn = ns + r;

                           // Slutt i 3. kvadrant 
      } else if (r2 >=PI && r2 < PI*3.0L/2.0L) {
         *nva = as - r;
         *nvn = min(n1,n2);
         *oha = as + r;
         *ohn = ns + r;
                           // Slutt i 4. kvadrant 
      } else {
         *nva = min(a1,a2);
         *nvn = min(n1,n2);
         *oha = max(a1,a2);
         *ohn = max(n1,n2);
      }
   }
}
*/


// ++----------------------------------------------------------------------
// FILE: Arc.cpp - Implementation for class QdiArc
// ++----------------------------------------------------------------------

// For å finne minste omsluttende rektangel til en bue må en først finne sentrum
//til buen. Koden for å gjøre dette fantes allerede i geometryutility.dll, men for å 
//unngå gjensidige avhengigheter mellom modellen og geometryutility.dll, kopierte jeg
//og skrev om koden her. 
//
//Etter at sentrum er funnet, finner jeg hvor mange akser som buen skjærer. For hver akse
//buen skjærer, hentes en ekstremalverdi fra minste omsluttende rektangel til en 
//SIRKEL som har sentrum samme sted som buen.
//
//Buen kan skjære 0, en, to, tre eller fire akser.

//
//                 |
//	                |
//               --|-
//             /   |  \        -
//           1     |   \       -
//   ----------2---|-------
//                 |    |
//                 |   3/
//                 |
//
//
//På eksempelfiguren ovenfor skjæres 2 akser (y-aksen en gang og x-aksen en gang.
//Her vil minste omsluttende rektangel hente LLX fra 1, LLY fra 3, URX fra sirkel
//og URY fra sirkel. (Med sirkel menes sirkelens senter +/- radius eller minste omsluttende
//rektangel til en sirkel med samme senter og radius)
//

/*
void QdiArc::computeBbox( QdiRectangle *pRectangle ) 
{
//Regner først ut senter av sirkelen
	bool bMajor = isMajor();

	QdiPosition *pStart= dynamic_cast <QdiPosition*> (getStartPosition()->clone());
	QdiPosition *pEnd= dynamic_cast <QdiPosition*> (getEndPosition()->clone());
	double dRadius= getRadius();
	double dMin= 0.0009;
	
	QdiPosition2D center1, center2, trueCenter;
	double dH = 0;
	double dRadi1= dRadius;
	double dRadi2= dRadius;
	
	double dX= pEnd->getX()- pStart->getX();
	double dY= pEnd->getY()- pStart->getY();
	double dDist= sqrt((dX*dX) + (dY*dY));
	
	double dInterX1= (((dRadi1*dRadi1) - (dRadi2*dRadi2))/(dDist*2)) + (dDist/2);
	double dInterX1Abs= fabs(dInterX1);
	
	if ( fabs(dInterX1Abs-fabs(dRadi1)) < dMin )
		dH= 0.0; // Only one intersection point.
	else 
		dH= sqrt( fabs((dRadi1*dRadi1)- (dInterX1*dInterX1)) );
	
	double dAspectX= dX/dDist;
	double dAspectY= dY/dDist;
	
	center1.setX(pStart->getX() + (dAspectX*dInterX1) + (dAspectY*dH));
	center1.setY(pStart->getY() + (dAspectY*dInterX1) - (dAspectX*dH));
	center2.setX(pStart->getX() + (dAspectX*dInterX1) - (dAspectY*dH));
	center2.setY(pStart->getY() + (dAspectY*dInterX1) + (dAspectX*dH));
	
	
	if (!bMajor) 
	{
		if ( dRadi1>= 0 ) 
		{
			trueCenter.setX(center1.getX());
			trueCenter.setY(center1.getY());
		}
		else if ( dRadi1< 0) 
		{
			trueCenter.setX(center2.getX());
			trueCenter.setY(center2.getY());
		}
	}
	// Use the "big/major arc" center
	else 
	{
		if ( dRadi1< 0 ) 
		{
			trueCenter.setX(center1.getX());
			trueCenter.setY(center1.getY());
		}
		else if ( dRadi1>= 0) 
		{
			trueCenter.setX(center2.getX());
			trueCenter.setY(center2.getY());
		}
	}
// Regner ut hvor mange akser som krysses

//	1 startPos
//	2 trueCenter	
//  3 endPos
	
	int nStartQuadrant = 0;
	int nEndQuadrant = 0;

	double dMostLeft;
	double dMostRight;
	double dHighest;
	double dLowest;

//	Finner ekstremalverdiene.

	dMostLeft = pStart->getX();
	if (dMostLeft > pEnd->getX())
	{
		dMostLeft = pEnd->getX();
	}

	dMostRight = pStart->getX();
	if (dMostRight < pEnd->getX())
	{
		dMostRight = pEnd->getX();
	}

	dHighest = pStart->getY();
	if (dHighest < pEnd->getY())
	{
		dHighest = pEnd->getY();
	}

	dLowest = pStart->getY();
	if (dLowest > pEnd->getY())
	{
		dLowest = pEnd->getY();
	}

// Om radius er negativ, byttes start og sluttpunkt

	if (dRadius < 0)
	{
		QdiPosition2D midlPos;
		midlPos.setX(pStart->getX());
		midlPos.setY(pStart->getY());

		pStart->setX(pEnd->getX());
		pStart->setY(pEnd->getY());

		pEnd->setX(midlPos.getX());
		pEnd->setY(midlPos.getY());
	}



// Finner hvor mange akser som krysses og hvilke kvadranter punktene ligger i

	if (pStart->getX() > trueCenter.getX())
	{
		if (pStart->getY() > trueCenter.getY())
		{
			// Kvadrant 4
			nStartQuadrant = 4;
		}
		else
		{
			// Kvadrant 1
			nStartQuadrant = 1;
		}
	}
	else
	{
		if (pStart->getY() > trueCenter.getY())
		{
			// Kvadrant 3
			nStartQuadrant = 3;
		}
		else
		{
			// Kvadrant 2
			nStartQuadrant = 2;
		}
	}


	if (pEnd->getX() > trueCenter.getX())
	{
		if (pEnd->getY() > trueCenter.getY())
		{
			// Kvadrant 4
			nEndQuadrant = 4;
		}
		else
		{
			// Kvadrant 1
			nEndQuadrant = 1;
		}
	}
	else
	{
		if (pEnd->getY() > trueCenter.getY())
		{
			// Kvadrant 3
			nEndQuadrant = 3;
		}
		else
		{
			// Kvadrant 2
			nEndQuadrant = 2;
		}
	}

	int nQuadrants = 0;


	if (nStartQuadrant > nEndQuadrant)
	{
		nQuadrants = 4 + (nEndQuadrant - nStartQuadrant);
	}
	else
	{
		nQuadrants = nEndQuadrant - nStartQuadrant;
	}
	

	if (bMajor)
	{
		// Hvis bMajor er sant, så går buen over 4 kvadranter om start og endepunkt er
		// i samme kvadrant.
		if (nQuadrants == 0)
		{
			nQuadrants = 4;
		}
	}

	// Lager først en bounding box av en sirkel.

	QdiPosition2D* llPos = new QdiPosition2D;
	QdiPosition2D* urPos = new QdiPosition2D;

	llPos->setX(trueCenter.getX() - abs(dRadius));
	llPos->setY(trueCenter.getY() - abs(dRadius));

	urPos->setX(trueCenter.getX() + abs(dRadius));
	urPos->setY(trueCenter.getY() + abs(dRadius));

	if (nQuadrants == 4)
	{

	}
	else if (nQuadrants == 3)
	{
		if (nStartQuadrant == 1)
		{
			urPos->setX(dMostRight);
		}
		else if (nStartQuadrant == 2)
		{
			llPos->setY(dLowest);
		}
		else if (nStartQuadrant == 3)
		{
			llPos->setX(dMostLeft);
		}
		else if (nStartQuadrant == 4)
		{
			urPos->setY(dHighest);
		}
	}
	else if (nQuadrants == 2)
	{
		if (nStartQuadrant == 1)
		{
			urPos->setX(dMostRight);
			urPos->setY(dHighest);
		}
		else if (nStartQuadrant == 2)
		{
			llPos->setY(dLowest);
			urPos->setX(dMostRight);
		}
		else if (nStartQuadrant == 3)
		{
			llPos->setX(dMostLeft);
			llPos->setY(dLowest);
		}
		else if (nStartQuadrant == 4)
		{
			llPos->setX(dMostLeft);
			urPos->setY(dHighest);
		}
	}
	else if (nQuadrants == 1)
	{
		if (nStartQuadrant == 1)
		{
			urPos->setX(dMostRight);
			urPos->setY(dHighest);
			llPos->setX(dMostLeft);
		}
		else if (nStartQuadrant == 2)
		{
			llPos->setY(dLowest);
			urPos->setX(dMostRight);
			urPos->setY(dHighest);
		}
		else if (nStartQuadrant == 3)
		{
			llPos->setX(dMostLeft);
			llPos->setY(dLowest);
			urPos->setX(dMostRight);
		}
		else if (nStartQuadrant == 4)
		{
			llPos->setX(dMostLeft);
			urPos->setY(dHighest);
			llPos->setY(dLowest);
		}
	}
	else if (nQuadrants == 0)
	{
		urPos->setX(dMostRight);
		urPos->setY(dHighest);
		llPos->setX(dMostLeft);
		llPos->setY(dLowest);
	}

	//pRectangle->setLowerLeft(llPos);
	pRectangle->expand( llPos );
	//pRectangle->setUpperRight(urPos);
	pRectangle->expand( urPos );
	
	delete pStart;
	delete pEnd;

	return;
}

// Get implicitly defined startPosition
//const QdiPosition* QdiArc::getStartPosition() const { return NULL; } // Dummy

// Get implicitly defined endPosition
//const QdiPosition* QdiArc::getEndPosition() const { return NULL; } // Dummy

// -------------------------- End of file ---------------------------------

*/







/*
AR-890903
CH GM_NormVindu                                   Normaliser vindusangivelse
CD ==========================================================================
CD Formål:
CD Bytter om koordinatene slik at vindusangivelsen blir riktig.
CD Sjekker også at vinduet har lengde > 0.0001 i både øst og nord retning.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  *nva        iu   Avgrensing av vinduet
CD double  *nvn        iu
CD double  *oha        iu
CD double  *ohn        iu
CD short    ist        r    status: 1 = Vinduet er OK
CD                                  0 = Vinduet er feil definert.
CD                                      (Lengde 0.0 i en retning.)
CD
CD Bruk:
CD ist = GM_NormVindu(&nva,&nvn,&oha,&ohn);
   ==========================================================================
*/
SK_EntPnt_GM short GM_NormVindu(double *nva,double *nvn,double *oha,double *ohn)
{
   double temp;

   if (*nva > *oha){         /* Eventuell ombytting av hjørnekoordinater */
       temp = *nva;
       *nva = *oha;
       *oha = temp;
   }
   if (*nvn > *ohn){
       temp = *nvn;
       *nvn = *ohn;
       *ohn = temp;
   }
                  /* Sjekk at lengden av vinduet er > 0.0 i begge retninger */
   return (short)((*oha-*nva) > ACCY   &&  (*ohn - *nvn) > ACCY);
}


/*
AR-890903
CH GM_TestPktBue                  Sjekk om punkt ligger i sektor gitt av bue 
CD ==========================================================================
CD Formål:
CD Sjekk om punkt ligger i sektor gitt av bue. 
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   as       i    Koordinat i sirkelsenter
CD double   ns       i
CD double   fi       i    "Retning" sentrum - buens startpunkt.
CD double   dfi      i    Vinkel mellom fi og retning buens sluttpunkt
CD double   a        i    Koordinat som skal testes
CD double   n        i
CD short    ok       r    1=ligger i buens sektor, 0=ikke i buens sektor
CD
CD Bruk:
CD ok = GM_TestPktBue(as,ns,fi,dfi,a,n);
   ==========================================================================
*/
SK_EntPnt_GM short GM_TestPktBue(double as,double ns,double fi,double dfi,
                              double a,double n)
{
   double fi1,d;
   short ok = 1;

   // Sjekk om punktene ligger på buen
   fi1 = GM_retning(as,ns,a,n);
   d = fi1 - fi;
   if (dfi < 0.0){
      if (d > 0.0)  d -= (PI * 2.0);
      //if (d < dfi)  ok = 0;            /* Utenfor buen */
      if ((d+GM_ACCY) < dfi)  ok = 0;            /* Utenfor buen */

   } else{
      if (d < 0.0)  d += (PI * 2.0);
      //if (d > dfi)  ok = 0;            /* Utenfor buen */
      if ((d-GM_ACCY) > dfi)  ok = 0;            /* Utenfor buen */
   }

   return ok;
}


/*
AR-890903
CH GM_PktBue                  Beregner vinkel til punkt i sektor gitt av bue 
CD ==========================================================================
CD Formål:
CD Beregner vinkel til punkt som ligger i sektor gitt av bue. 
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   as       i    Koordinat i sirkelsenter
CD double   ns       i
CD double   fi       i    "Retning" sentrum - buens startpunkt.
CD double   dfi      i    Vinkel mellom fi og retning buens sluttpunkt
CD double   a        i    Punkt som skal testes
CD double   n        i
CD double  *dfiPkt   u    Vinkel mellom fi og retning til testpunktet
CD short    ok       r    1=ligger i buens sektor, 0=ikke i buens sektor
CD
CD Bruk:
CD ok = GM_PktBue(as,ns,fi,dfi,a,n,&dfiPkt);
   ==========================================================================
*/
SK_EntPnt_GM short GM_PktBue(double as,double ns,double fi,double dfi,
                              double a,double n,double *dfiPkt)
{
   double fi1;
   short ok = 1;

//UT_FPRINTF(stderr,"\r\n I GM_PktBue: ns=%.12g, as=%.12g, fi=%.12g, dfi=%.12g",ns,as,fi,dfi);
//UT_FPRINTF(stderr,"\n I GM_PktBue: n=%.12g, a=%.12g",n,a);


   // Sjekk om punktene ligger på buen
   fi1 = GM_retning(as,ns,a,n);

//UT_FPRINTF(stderr,"\n I GM_PktBue: fi1=%.12g",fi1);

   *dfiPkt = fi1 - fi;

   // Spesialtilfelle for å handtere problemer når vinkelen blir tilnærmet 0.0
   if (fabs(*dfiPkt) < GM_ACCY)
   {
      *dfiPkt = 0.0;
      return 1;  // ==> 
   }

   if (dfi < 0.0){
      if (*dfiPkt > 0.0)  *dfiPkt -= (PI * 2.0);
      if ((*dfiPkt+GM_ACCY) < dfi)  ok = 0;            /* Utenfor buen */
   }
   else
   {
      if (*dfiPkt < 0.0)  *dfiPkt += (PI * 2.0);
      if ((*dfiPkt-GM_ACCY) > dfi)  ok = 0;            /* Utenfor buen */
   }

   return ok;
}


/*
JEK-920520
CH GM_Avstand            Beregner avstand mellom to punkt
CD ==================================================================
CD Formål:
CD Beregner avstand mellom to punkt.
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD ------------------------------------------------------------------
CD a1        double       i   Øst-koordinat for startpunkt
CD n1        double       i   Nord-koordinat for startpunkt
CD a2        double       i   Øst-koordinat for endepunkt
CD n2        double       i   Nord-koordinat for endepunkt
CD avstand   double       r   Avstand mellom punktene
CD
CD Bruk:  avstand = GM_Avstand ( a1, n1, a2, n2 );
   ==================================================================
*/
SK_EntPnt_GM double GM_Avstand(double a1, double n1, double a2, double n2 )
{
      double a,n;

      a = a2 - a1;
      n = n2 - n1;
      return  sqrt( a*a + n*n );
}


/*
TOU/AR-080521
CH GM_Avstand            Beregner kvadrert avstand mellom to punkt
CD ==================================================================
CD Formål:
CD Beregner kvadrert avstand mellom to punkt.
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD ------------------------------------------------------------------
CD a1        double       i   Øst-koordinat for startpunkt
CD n1        double       i   Nord-koordinat for startpunkt
CD a2        double       i   Øst-koordinat for endepunkt
CD n2        double       i   Nord-koordinat for endepunkt
CD avstand2   double      r   Kvadrert avstand mellom punktene
CD
CD Bruk:  avstand2 = GM_Avstand2 ( a1, n1, a2, n2 );
==================================================================
*/
SK_EntPnt_GM double GM_Avstand2(double a1, double n1, double a2, double n2 )
{
   double a,n;

   a = a2 - a1;
   n = n2 - n1;
   return ( a*a + n*n );
}


/*
JEK-920520
CH GM_BueTangent       Retnv. for tangent til punkt på bue
CD ==================================================================
CD Formål:
CD Beregner retningsvinkel til tangent til punkt på en sirkelbue.
CD
CD PARAMETERLISTE:
CD Navn     Type     I/U  Merknad
CD -----------------------------------------------------------------
CD as       double    i   Øst-koordinat for sirkelsentrum
CD an       double    i   Nord-koordinat for sirkelsentrum
CD fi       double    i   Retningsvinkel til start bue
CD dfi      double    i   Retn.endring i radianer.
CD                          + = mot klokka, - =med klokka
CD radius   double    i   radius med fortegn
CD                          +  =  med klokka,  -  = mot klokka
CD a        double    i   Øst-koordinat for tangeringspunkt
CD n        double    i   Nord-koordinat for tangeringspunkt
CD *buetan  double    u   Retning i radianer(0-2PI) for buetangent
CD ist      short     r   status:  1 = Beregning ok                 
CD                                 0 = Punkt ikke på buesegment     
CD                                     NB! Tangent beregnes uansett!
CD
CD Bruk:  ist = GM_BueTangent(as,ns,fi,dfi,radius,a,s,&buetan);
   ==================================================================
*/
SK_EntPnt_GM short GM_BueTangent ( double as, double ns, double fi, double dfi,
                                double radius, double a, double n, double *buetan)
{     
      short ist;
      
      ist = 0;
      if ( GM_TestPktBue ( as, ns, fi, dfi, a, n ) ) {
         if ( (fabs(radius) - GM_Avstand (as,ns,a,n)) < 0.01 ) ist=1;
      }

      if ( dfi > 0.0 ){        /* Mot klokka */        
         *buetan = GM_RedVinkel ( GM_retning(as,ns,a,n) + PI/2 );
      } else {                 /* Med klokka */                         
         *buetan = GM_RedVinkel ( GM_retning(as,ns,a,n) - PI/2 );
      }
      return ist;
}


/*
LS-900607
AR-921001
CH GM_BueTilKorder                        Tilnærm ein sirkelboge med korder
CD =========================================================================
CD Formål:
CD   Tilnærm ein sirkelboge med korder.
CD
CD PARAMETERLISTE:
CD Type    Navn   I/U  Merknad
CD ------------------------------------------------------------------
CD double  as      i  Øst-koordinat for sirkelsentrum
CD double  an      i  Nord-koordinat for sirkelsentrum
CD double  r       i  Radius i sirkelen
CD double  fi      i  Retningsvinkel til start bue
CD double  dfi     i  Retn.endring i radianer.
CD                      + = mot klokka, - =med klokka
CD double  delta   i  Vinkeltoleranse (max vinkel mellom korder i radianer)
CD short   mpu     i  Max tal på punkt i a_arr og n_arr
CD double *a_arr   u  Knekkpunkt før, mellom og etter kordene
CD double *n_arr   u  
CD short   npu     r  Tal på punkt i a_arr og n_arr
CD
CD Bruk:
CD npu = GM_BueTilKorder(as,ns,r,fi,dfi,delta,mpu,a_arr,n_arr);
CD =========================================================================
*/
SK_EntPnt_GM short GM_BueTilKorder (double as,double ns,double r,double fi,double dfi,
                                 double delta,short mpu,double *a_arr,double *n_arr)
{
   double intdel;
   short nk,npu;

   r = fabs(r);
                              /* Bestem presisjon (tal på korder) */
   if (dfi < 0.0) delta = -delta;
   modf (dfi/delta, &intdel);
   nk = (short)(UT_RoundDS(intdel) + 1);
   if (nk >= mpu) {            /* For mange korder - reduser kravet */
      nk = (short)(mpu - 1);
      delta = dfi/(double)nk;
   }
   npu = (short)(nk + 1);
   
   /* Startpunktet */
    *a_arr = as + r*cos(fi);
    *n_arr = ns + r*sin(fi);

   /* Sluttpunkt */
    *(a_arr+nk) = as + r*cos(fi+dfi);
    *(n_arr+nk) = ns + r*sin(fi+dfi);

                                /* Korde-løkke */
    for (nk--,a_arr++,n_arr++,fi+=delta; nk; nk--,a_arr++,n_arr++,fi+=delta) {
      *a_arr = as + r*cos(fi);
      *n_arr = ns + r*sin(fi);
    }

    return npu;
}


/*
LS-900607
AR-921001
CH GM_PktTilOktagon                  Beregner en åttekant rundt gitt punkt.
CD =========================================================================
CD Formål:
CD   Beregner en åttekant med gitt areal rundt gitt punkt.
CD
CD PARAMETERLISTE:
CD Type    Navn   I/U  Merknad
CD ------------------------------------------------------------------
CD double  dAs     i  Øst-koordinat for sentrum
CD double  dNns    i  Nord-koordinat for sentrum
CD double  dAreal  i  Ønsket areal
CD double *a_arr   u  Hjørnepunkt (Må ha plass til 8 punkt.)
CD double *n_arr   u  
CD
CD Bruk:
CD GM_PktTilOktagon(dAs,dNs,dAreal,a_arr,n_arr);
CD =========================================================================
*/
SK_EntPnt_GM void GM_PktTilOktagon (double dAs,double dNs,double dAreal,double *a_arr,double *n_arr)
{
   double dS,dS2,dX;
   double d2Rot = sqrt(2.0);

   //            1            2
   //            +------------+ - - - -   -
   //          /                \      |
   //        /                    \       dX
   //      /                        \  |
   //    /                            \   _
   //  8+                              +3
   //   |                              |
   //   |                              |
   //   |               +              |  dS
   //   |                s             |
   //   |                              |
   //  7+                              +4 _
   //    \                            /
   //      \                        / 
   //        \                    /  
   //          \                /   
   //            +------------+
   //            6            5

   // Beregner sidelengde mm.
   dS = sqrt( dAreal / ( (2.0 * d2Rot) + 2.0));
   dS2 = dS / 2.0;
   dX = dS2 * d2Rot;

   // Beregner koordineter
   // 1
   *a_arr++ = dAs - dS2;
   *n_arr++ = dNs + dS2 + dX;
   // 2
   *a_arr++ = dAs + dS2;
   *n_arr++ = dNs + dS2 + dX;
   // 3
   *a_arr++ = dAs + dS2 + dX;
   *n_arr++ = dNs + dS2;
   // 4
   *a_arr++ = dAs + dS2 + dX;
   *n_arr++ = dNs - dS2;
   // 5
   *a_arr++ = dAs + dS2;
   *n_arr++ = dNs - dS2 - dX;
   // 6
   *a_arr++ = dAs - dS2;
   *n_arr++ = dNs - dS2 - dX;
   // 7
   *a_arr++ = dAs - dS2 - dX;
   *n_arr++ = dNs - dS2;
   // 8
   *a_arr = dAs - dS2 - dX;
   *n_arr = dNs + dS2;
}


/*
AR:2008-08-12
CH GM_TynnDared
CD ==========================================================================
CD Formål:
CD Tynning med pilhøyde og maks avstand.
CD Samme som SiTynnDared, men noe forenklet:
CD - Koordinatene kommer inn i NØ buffer.
CD - Handterer ikke høyde
CD - Tar ikke hensyn til knutepunkt
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD double   dMaxAvst     i   Max distanse mellom punkta
CD double   dMaxPil      i   Max pilhøyde
CD long    *nko         iu   Antall koordinater
CD double  *pA          iu   Øst-koordinater
CD double  *pN          iu   Nord-koordinater
CD bool     bBeregnet    r   Status.
CD Bruk:
CD bBeregnet = GM_TynnDared(dMaxAvst,dPilhoyde,&nko,pA,pN);
==========================================================================
*/
SK_EntPnt_GM void GM_TynnDared(double dMaxAvst,double dMaxPil,long *nko, double *pA,double *pN)
{
   long lTeller,lStorPnr=0;
   bool bNyttFastpunktFunnet;
   double a,n,a1,n1,a2,n2,ap,np,da,dn,dAvst2;
   double pa,pb,pc;
   double dPil,dStorPil;
   long lLagre  = 2;  // Peker for lagring av punkt (første ledig)
   long lForste = 1;  // Starten av aktuelt segment
   long lSiste;       // Siste punkt i segmentet
   double dMaxAvst2 = dMaxAvst * dMaxAvst;
   double dPil2 = dMaxPil * dMaxPil;
   bool bBeregnet = true;


   // Ta kopi av opprinnelige koordinater
   double *pdAust = (double*) malloc((sizeof(double))*(*nko));
   UT_memcpy(pdAust, (sizeof(double))*(*nko), pA, (sizeof(double))*(*nko));

   double *pdNord = (double*) malloc((sizeof(double))*(*nko));      
   UT_memcpy(pdNord, (sizeof(double))*(*nko), pN, (sizeof(double))*(*nko));

   // UT_FPRINTF(stderr,"\n\nTynner: %s",LC_GetGi(1));

   while (lForste < *nko)
   {
      // Sjekk ett segment. Segmentet avsluttes når:
      // - pilhøyden overskrider gitt verdi
      //   (Det punktet som hadde størst pilhøyde blir neste fastpunkt)
      // - lengden overskrider gitt verdi

      //LC_GetTK(lForste,&a1,&n1);
      a1 = *(pA+lForste-1);
      n1 = *(pN+lForste-1);
      // UT_FPRINTF(stderr,"\n%hd  a: %.1f n: %.1f",lForste,a1,n1);

      bNyttFastpunktFunnet = false;
      for (lSiste=lForste+1; !bNyttFastpunktFunnet && lSiste<=*nko; lSiste++)
      {
         // UT_FPRINTF(stderr,"\n\nSegment %hd - %hd",lForste,siste);

         //LC_GetTK(lSiste,&a2,&n2);
         a2 = *(pA+lSiste-1);
         n2 = *(pN+lSiste-1);
         // UT_FPRINTF(stderr,"\n%hd  a: %.1f n: %.1f",lSiste,a2,n2);

         // Beregn største pilhøyde
         dStorPil = 0.0;
         for (lTeller=lForste+1; lTeller<lSiste; lTeller++)
         {
            //LC_GetTK(lTeller,&ap,&np);
            ap = *(pA+lTeller-1);
            np = *(pN+lTeller-1);
            dPil = 0.0;
            // UT_FPRINTF(stderr,"\n%hd  a: %.1f n: %.1f h: %.1f",s,ap,np,hp);

            if (GM_bepa(a1,n1,a2,n2,&pa,&pb,&pc))
            {
               // UT_FPRINTF(stderr,"\n%hd  pa: %.5f pb: %.5f pc: %.5f",s,pa,pb,pc);
               dPil = fabs(pa*ap + pb*np + pc);
               // UT_FPRINTF(stderr,"\n%hd  2D ph: %.4f",s,dPil);
            }

            // Husker største pilhøyde
            if (dPil > dStorPil) {
               lStorPnr = lTeller;
               dStorPil = dPil;
            }
         }

         // Max pilhøyde er overskredet, nytt fastpunkt er funnet

         // UT_FPRINTF(stderr,"\nMax pilhøyde %hd  : %.4f",sStorPnr,dStorPil);

         if (dStorPil > dMaxPil)
         {
            //LC_GetTK(lStorPnr,&ap,&np);
            ap = *(pA+lStorPnr-1);
            np = *(pN+lStorPnr-1);
            //LC_PutTK(lLagre,ap,np);
            *(pA+lLagre-1) = ap;
            *(pN+lLagre-1) = np;
            // UT_FPRINTF(stderr,"\nLagres som punkt nr %hd",lagre);

            lLagre++;
            lForste = lStorPnr; 
            bNyttFastpunktFunnet = true;
         }

         // Sjekk om max avstand er overskredet
         if ( ! bNyttFastpunktFunnet)
         {
            da = a2 - a1;
            dn = n2 - n1;
            dAvst2 = da*da + dn*dn;
            // UT_FPRINTF(stderr,"\nAvst %hd %hd : %.4f",forste,siste,sqrt(dAvst2));

            if (dAvst2 > dMaxAvst2)
            {
               if (lSiste == lForste+1)
               {
                  //LC_PutTK(lLagre,a2,n2);
                  *(pA+lLagre-1) = a2;
                  *(pN+lLagre-1) = n2;

                  // UT_FPRINTF(stderr,"\nMax avst. overskredet, lagres som punkt nr %hd",lagre);

                  lLagre++;
                  lForste = lSiste;
                  bNyttFastpunktFunnet = true;
               }

               else
               {
                  //LC_GetTK(lSiste-1,&ap,&np);
                  ap = *(pA+lSiste-1-1);
                  np = *(pN+lSiste-1-1);
                  //LC_PutTK(lLagre,ap,np);
                  *(pA+lLagre-1) = ap;
                  *(pN+lLagre-1) = np;

                  // UT_FPRINTF(stderr,"\nMax avst. overskredet, lagres som punkt nr %hd",lagre);

                  lLagre++;
                  lForste = lSiste-1;
                  bNyttFastpunktFunnet = true;
               }
            }

            // Siste punkt i gruppen er alltid fastpunkt
            if (lSiste == *nko)
            {
               // Sjekk at koordinatene er forskjellige fra forrige punkt
               if (lLagre > 1) 
               {
                  //LC_GetTK((short)(lLagre-1),&a,&n);
                  a = *(pA+lLagre-1-1);
                  n = *(pN+lLagre-1-1);

                  if (fabs(a2-a) < ACCY  &&  fabs(n2-n) < ACCY) 
                  {
                     // Samme koordinater som forrige punkt, kutt ut dette
                     lLagre--;
                  }
               }

               //LC_PutTK(lLagre,a2,n2);
               *(pA+lLagre-1) = a2;
               *(pN+lLagre-1) = n2;
               // UT_FPRINTF(stderr,"\nSiste pkt., lagres som punkt nr %hd",lagre);

               lLagre++;
               lForste = lSiste;
               bNyttFastpunktFunnet = true;
            }
         }
      }
   }

   // ----- Sjekk at gruppen ikke har klappet sammen til en kort liten strek

   if (lLagre <= 3)
   {
      // Har 2 koordinater etter tynning,
      // legg tilbake opprinnelige koordinater
      bBeregnet = false;
      UT_memcpy(pA, (sizeof(double))*(*nko), pdAust, (sizeof(double))*(*nko));
      UT_memcpy(pN, (sizeof(double))*(*nko), pdNord, (sizeof(double))*(*nko));
   }

   else if (lLagre == 4)
   {  
      // Har 3 koordinater etter tynning, og
      // avstand fra første til siste punkt er mindre enn pilhøyden
      da = (*(pA+lLagre-2)) - (*(pA));
      dn = (*(pN+lLagre-2)) - (*(pN));

      if ((da*da + dn*dn) < dPil2)
      {
         // Gruppen har blitt feil, legg tilbake opprinnelige koordinater
         bBeregnet = false;
         UT_memcpy(pA, (sizeof(double))*(*nko), pdAust, (sizeof(double))*(*nko));
         UT_memcpy(pN, (sizeof(double))*(*nko), pdNord, (sizeof(double))*(*nko));
      }
   }

   free(pdAust);
   free(pdNord);

   // Legg ut antall koordinater i resultatet
   if (bBeregnet)  *nko = lLagre-1;
}


/*
CH GM_BeregnHjelpepunkt
CD ==============================================================
CD Formål: 
CD Beskriv funksjonaliteten her ...
CD
CD
CD
CD                        *3             *2
CD                       /             /
CD                           n1*     /
CD                     /           /
CD                               /
CD                   /    n2*  /
CD                           /   
CD                 /   n3* /    
CD                       /
CD               /     /
CD                   /       
CD             /   /
CD               /
CD           / /  
CD           *1    
CD
CD Parameterliste:
CD Type    Navn         I/U   Merknad
CD -------------------------------------------------------------
CD double  dA1           i    Koordinater punkt 1
CD double  dN1           i
CD double  dA2           i    Koordinater punkt 2
CD double  dN2           i
CD double  dA3           i    Koordinater punkt 3
CD double  dN3           i
CD double  dEnhet        i    Enhet som styrer avrunding og beregning
CD short   sMaxAntPkt    i    Max antall punkt i pdAustArr og pdNordArr
CD double *pdAustArr     u    Peker til array som mottar beregnede koordinater(  n1 -nx
CD double *pdNordArr     u    Peker til array som mottar beregnede koordinater
CD short   sAntPkt       u    Antall punkt beregnet
CD bool    bBeregnet     r    Status: true = beregnet OK
CD                                    false = ikke beregnet. (ikke nok plass i resultat-array, og andre feil?)
CD
CD  Bruk:
CD  bStatus = GM_BeregnHjelpepunkt(dA1,dN1,dA2,dN2,dA3,dN3,dEnhet,sMaxAntPkt,&dAustArr,&pdNordArr,&sAntPkt);
CD  ==============================================================
*/

/*
bool GM_BeregnHjelpepunkt(double dA1,double dN1,double dA2,double dN2,double dA3,double dN3,double dEnhet,
                          short sMaxAntPkt,double *pdAustArr,double *pdNordArr,short *psAntPkt)
{
   // Beskriv algoritme som brukes her ...
   // (Eventuelt med henvisning til bok med detaljbeskrivelse)


   bool bStatus = true;

   // Legg inn funksjonaliteten her ...

   return bStatus;
}
*/

