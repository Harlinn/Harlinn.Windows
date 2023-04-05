#include "fyba.h"
#include "fyba_strings.h"

/*
AR-940110
CH LC_StrError                                             Feilmeldingstekst
CD ==========================================================================
CD Formål:
CD Henter feilmeldingstekst og nivå for et feilmeldingsnummer.
CD Strengen legges i en egen feilmeldingsstruktur for feil-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "feil-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk UT_StrCopy).
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD short    feil_nr      i   Feilmeldingsnummer
CD char   **feilmelding  u   Peker til feilmeldingstekst avslutta med '\0'.
CD short   *strategi     r   Feilnivå (0-4)
CD                           0 = Ikke i bruk. (Utkoblet, testmeldinger mm.)
CD                           1 = Lite alvorlig. Vises kort.
CD                           2 = Normal feilmelding. Vises ca. 1 sekund.
CD                           3 = Alvorlig. Krev tastetrykk for å fortsette.
CD                           4 = Svært alvorlig. Programmet bør avbrytes.
CD
CD Bruk:
CD strategi = LC_StrError(ckap,feil_nr,&feilmeldingspeker);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_StrError(short feil_nr,char **feilmelding)
{
#define MAX_FEIL_LEN  200
   static char feil[MAX_FEIL_LEN];      /* Feilmeldings-streng */
   short strategi = 0;


   switch(feil_nr) {                           /* Finn riktig melding */
/* --------------------- LO --------------------------- */
      case 1:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_BASE_UNKNOWN_TYPE,MAX_FEIL_LEN);
         break;
      case 2:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_BASE_TOO_MANY_GROUPS,MAX_FEIL_LEN);
         break;
      case 3:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_NOT_FOUND,MAX_FEIL_LEN);
         break;
      case 4:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_BASE_FYBA_NOT_INITD,MAX_FEIL_LEN);
         break;
      case 5:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_BASE_NOT_OPEN,MAX_FEIL_LEN);
         break;
      case 6:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_FILE_OPEN_FAILED,MAX_FEIL_LEN);
         break;
      case 7:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_OMRAADE_MISSING,MAX_FEIL_LEN);
         break;
      case 8:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_MIN_NOE_MISSING,MAX_FEIL_LEN);
         break;
      case 9:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_MAX_NOE_MISSING,MAX_FEIL_LEN);
         break;
      case 10:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_BASE_INDEX_ABORTED,MAX_FEIL_LEN);
         break;
      case 13:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_PERM_DENIED,MAX_FEIL_LEN);
         break;
      case 101:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_BASE_OPEN_FAILED,MAX_FEIL_LEN);
         break;
      case 102:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_NEW_HEADER,MAX_FEIL_LEN);
         break;
      case 103:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_NOT_SOSI,MAX_FEIL_LEN);
         break;
      case 104:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_FILE_OMRAADE_INVALID,MAX_FEIL_LEN);
         break;

      case 105:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_SAVE_INVALID_FILEPTR,MAX_FEIL_LEN);
         break;

      case 106:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_OPEN_BASE_IS_KLADDE,MAX_FEIL_LEN);
         break;

/* --------------------- HO --------------------------- */
      case 12:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_FILE_READ_ERROR_HODE,MAX_FEIL_LEN);
         break;
      case 14:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_FILE_TRANSPAR_MISSING,MAX_FEIL_LEN);
         break;
      case 15:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_FILE_KOORDSYS_MISSING,MAX_FEIL_LEN);
         break;
      case 16:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_FILE_ORIGO_MISSING,MAX_FEIL_LEN);
         break;
      case 17:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_FILE_ENHET_MISSING,MAX_FEIL_LEN);
         break;
/* --------------------- LN --------------------------- */
      case 21:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_NAME_TABLE_FULL,MAX_FEIL_LEN);
         break;

      case 22:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_INVALID_GROUP_NAME,MAX_FEIL_LEN);
         break;

/* --------------------- LB --------------------------- */
      case 31:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_FILE_NO_CURRENT_GROUP,MAX_FEIL_LEN);
         break;
      case 32:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_OPEN_INVALID_EXTERN,MAX_FEIL_LEN);
         break;
      case 33:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_SAVE_INVALID_EXTERN,MAX_FEIL_LEN);
         break;
      case 34:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_SAVE_NO_WRITE_ACCESS,MAX_FEIL_LEN);
         break;
      case 35:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_GROUP_DELETED,MAX_FEIL_LEN);
         break;
      case 36:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_FILE_INVALID_GROUP_NR,MAX_FEIL_LEN);
         break;
      case 37:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_NEW_INVALID_FILE,MAX_FEIL_LEN);
         break;
      case 38:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_NEW_NO_WRITE_ACCESS,MAX_FEIL_LEN);
         break;
      case 39:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_NEW_TOO_MANY_GROUPS,MAX_FEIL_LEN);
         break;
      case 40:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_NEW_INVALID_LINE_GI,MAX_FEIL_LEN);
         break;
      case 41:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_NEW_INVALID_LINE_COO,MAX_FEIL_LEN);
         break;
      case 42:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_SLUTT_MISSING,MAX_FEIL_LEN);
         break;
      case 43:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_READ_ERROR,MAX_FEIL_LEN);
         break;
      case 44:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_GROUP_REFERRED_TO,MAX_FEIL_LEN);
         break;
      case 47:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_INVALID_GI_LINE_1,MAX_FEIL_LEN);
         break;
      case 48:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_CANT_REMOVE_HEADER,MAX_FEIL_LEN);
         break;
      case 49:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_NO_CURRENT_GROUP,MAX_FEIL_LEN);
         break;
      case 50:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_DEL_UNKNOWN_FLAG,MAX_FEIL_LEN);
         break;
      case 91:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_DEL_NO_WRITE_ACCESS,MAX_FEIL_LEN);
         break;
      case 92:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_ERR_FILESIZE_CHANGE,MAX_FEIL_LEN);
         break;
      case 93:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_DISK_SOON_FULL,MAX_FEIL_LEN);
         break;
      case 94:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_NOT_A_HEADER,MAX_FEIL_LEN);
         break;
      case 95:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_DEL_NOT_SEQUENTIAL,MAX_FEIL_LEN);
         break;
      case 96:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_NO_CHANGE_HEADERS,MAX_FEIL_LEN);
         break;
      case 97:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_CANT_REWRITE_HEADER,MAX_FEIL_LEN);
         break;
      case 98:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_SAVE_NOT_A_HEADER,MAX_FEIL_LEN);
         break;
      case 99:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_CANT_COPY_COORD,MAX_FEIL_LEN);
         break;
      case 100:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_CANT_COPY_COORD_ROOM,MAX_FEIL_LEN);
         break;
      case 141:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_ENHET_NOT_SET,MAX_FEIL_LEN);
         break;
      case 142:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_CANT_READ_FILE_SIZE,MAX_FEIL_LEN);
         break;
      case 143:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_PINFO_LONG_OR_NO_NOE,MAX_FEIL_LEN);
         break;
      case 144:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_LOGIC_FAIL,MAX_FEIL_LEN);
         break;
      case 145:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_MAX_1_KP_OR_NO_NOE,MAX_FEIL_LEN);
         break;
      case 146:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_NO_ROOM_IN_HEADER,MAX_FEIL_LEN);
         break;
      case 147:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_INVALID_GAP,MAX_FEIL_LEN);
         break;
      case 148:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_TOO_MANY_COORDINATES,MAX_FEIL_LEN);
         break;
      case 149:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_TOO_MANY_GINFO,MAX_FEIL_LEN);
         break;
      case 150:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_TOO_MUCH_GINFO,MAX_FEIL_LEN);
         break;
      case 161:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_TOO_MUCH_PINFO,MAX_FEIL_LEN);
         break;
      case 162:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_CANT_EXTEND_GROUP,MAX_FEIL_LEN);
         break;
      case 163:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_READ_NO_WRITE_ACCESS,MAX_FEIL_LEN);
      case 164:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_READ_LINE_TOO_LONG,MAX_FEIL_LEN);
         break;


/* --------------------- LX --------------------------- */
      case 51:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_INVALID_POINT,MAX_FEIL_LEN);
         break;
      case 52:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_INVALID_GINFO,MAX_FEIL_LEN);
         break;
      case 53:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_INVALID_NODE,MAX_FEIL_LEN);
         break;
      case 54:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_INVALID_GROUP_NAME,MAX_FEIL_LEN);
         break;
      case 55:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_PINFO_TOO_LONG,MAX_FEIL_LEN);
         break;
      case 56:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_INVALID_REF,MAX_FEIL_LEN);
         break;
      case 57:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_CANT_CHANGE_ENHET ,MAX_FEIL_LEN);
         break;
      case 58:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_CANT_CHANGE_NGIS_LAG,MAX_FEIL_LEN);
         break;
      case 59:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_INVALID_BUE,MAX_FEIL_LEN);
         break;
      case 60:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_CANT_CHANGE_ORIGO_NOE,MAX_FEIL_LEN);
         break;
      case 131:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_PROB_TOO_LONG_PINFO,MAX_FEIL_LEN);
         break;
      case 132:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_NO_HOEYDE_WITH_NAD,MAX_FEIL_LEN);
         break;
      case 133:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_NO_HOEYDE_WITH_NAH,MAX_FEIL_LEN);
         break;
      case 134:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_LINE_TOO_LONG,MAX_FEIL_LEN);
         break;

 
/* --------------------- LS --------------------------- */
      case 61:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_INVALID_SERIAL,MAX_FEIL_LEN);
         break;

/* --------------------- LI --------------------------- */
      case 71:
         strategi = 2;
         UT_StrCopy(feil,FYBA_STRING_INVALID_LINE_NR,MAX_FEIL_LEN);
         break;
      case 72:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_INVALID_GROUP_NR,MAX_FEIL_LEN);
         break;
      case 73:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_READING_BUFFER,MAX_FEIL_LEN);
         break;
      case 74:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_WRITING_BUFFER,MAX_FEIL_LEN);
         break;
      case 75:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_MUST_INIT_INDEX,MAX_FEIL_LEN);
         break;
      case 79:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_READING_SEARCHT,MAX_FEIL_LEN);
         break;
      case 80:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_WRITING_SEARCHT,MAX_FEIL_LEN);
         break;
      case 111:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_READING_GROUPT,MAX_FEIL_LEN);
         break;
      case 112:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_WRITING_GROUPT,MAX_FEIL_LEN);
         break;
      case 113:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_READING_SERIALT,MAX_FEIL_LEN);
         break;
      case 114:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_WRITING_SERIALT,MAX_FEIL_LEN);
         break;
      case 115:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_READING_INFOT,MAX_FEIL_LEN);
         break;
      case 116:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_WRITING_INFOT,MAX_FEIL_LEN);
         break;
      case 117:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_INFOT_FULL,MAX_FEIL_LEN);
         break;
      case 118:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_READING_BRUKT,MAX_FEIL_LEN);
         break;
      case 119:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_ERR_WRITING_BRUKT,MAX_FEIL_LEN);
         break;
      case 120:
         strategi = 4;
         UT_StrCopy(feil,FYBA_STRING_NO_BLANKS_FILENAME,MAX_FEIL_LEN);
         break;


/* --------------------- LR --------------------------- */

/* --------------------- LU --------------------------- */
      case 121:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_TOO_MANY_CHOICES,MAX_FEIL_LEN);
         break;
      case 122:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_MISPLACED_CHOICE,MAX_FEIL_LEN);
         break;
      case 123:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_GROUP_CHOICE_MISSING,MAX_FEIL_LEN);
         break;
      case 124:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_INVALID_CHOICE,MAX_FEIL_LEN);
         break;
      case 125:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_NO_COMPLEX_CHOICE,MAX_FEIL_LEN);
         break;
      case 126:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_GAP_IN_LEVEL,MAX_FEIL_LEN);
         break;
      case 127:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_TOO_MANY_PRIORITIES,MAX_FEIL_LEN);
         break;
      case 128:
         strategi = 3;
         UT_StrCopy(feil,FYBA_STRING_DUPLICATE_DEFINITION,MAX_FEIL_LEN);
         break;

/* --------- Standard melding ved ukjent nr. ------------------- */
      default:
         strategi = 3;
         UT_SNPRINTF(feil,MAX_FEIL_LEN,FYBA_STRING_UNKNOWN_ERROR,feil_nr);
         break;
   }

   *feilmelding = feil;

   return strategi;
}
