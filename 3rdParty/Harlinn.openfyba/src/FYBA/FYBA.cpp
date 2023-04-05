/*
CH  FYBA                                             FYsak-Basesystem
CD  ==================================================================
CD  Rutiner for å lese, endre og skrive SOSI-filer.
CD  ==================================================================
CD
CH  INSTALLERINGS- OG BRUKS-OPPLYSNINGER:
CD
CD  Bibliotek..: fybale.lib
CD  Kildefiler.: fyba.c, fylo.c, fyln.c, fylr.c, fyls.c, fylx.c, fyli.c
CD               fylh.c, fyho.c, fyle.c, fyba.h, fybax.h
CD  Versjon....: D01
CD  Eier.......: STATENS KARTVERK / FYSAK-prosjektet
CD  Ansvarlig..: Andreas Røstad, Georg Langerak
CD
CD  Kompilator.: Microsoft C versjon 6.0
CD  Optioner...: /c /AL /J /FPi /G2t /W4
CD  Memory-mod.: Large
CD  Floating-p.: Emulation
CD  Processor..: 80286
CD
CD  #include...: fyba.h
CD  Linkes med.: utle.lib    >=  versjon D
CD              +llibce.lib  >=  versjon 6.0
CD
CD  ==================================================================
*/

//#include "stdafx.h"
#include "fyut.h"
#include "fygm.h"

#include "fyba.h"
#include "fybax.h"


/*
CH LC_InqVer                                                   Identifikasjon
CD =============================================================================
CD Formål:
CD Henter versjons-identifikasjon for dette biblioteket.
   =============================================================================
*/
SK_EntPnt_FYBA const char *LC_InqVer(void)
{
   return FYBA_IDENT;
}
