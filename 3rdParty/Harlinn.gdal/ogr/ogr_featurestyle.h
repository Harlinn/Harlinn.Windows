#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  OpenGIS Simple Features Reference Implementation
 * Purpose:  Define of Feature Representation
 * Author:   Stephane Villeneuve, stephane.v@videtron.ca
 *
 ******************************************************************************
 * Copyright (c) 1999, Frank Warmerdam
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
 ****************************************************************************/

#ifndef OGR_FEATURESTYLE_INCLUDE
#define OGR_FEATURESTYLE_INCLUDE

#include "../port/cpl_conv.h"
#include "../port/cpl_string.h"
#include <ogr/ogr_core.h>

class OGRFeature;

/**
 * \file ogr_featurestyle.h
 *
 * Simple feature style classes.
 */

/*
 * All OGRStyleTool param lists are defined in ogr_core.h.
 */

/** OGR Style type */
typedef enum ogr_style_type
{
    OGRSTypeUnused = -1,
    OGRSTypeString,
    OGRSTypeDouble,
    OGRSTypeInteger,
    OGRSTypeBoolean
}  OGRSType;

//! @cond Doxygen_Suppress
typedef struct ogr_style_param
{
    int              eParam;
    const char       *pszToken;
    GBool            bGeoref;
    OGRSType         eType;
} OGRStyleParamId;

typedef struct ogr_style_value
{
    char            *pszValue;
    double           dfValue;
    int              nValue; // Used for both integer and boolean types
    GBool            bValid;
    OGRSTUnitId      eUnit;
} OGRStyleValue;
//! @endcond

// Every time a pszStyleString given in parameter is NULL,
// the StyleString defined in the Mgr will be use.

/**
 * This class represents a style table
 */
class OGRStyleTable
{
  private:
    char **m_papszStyleTable = nullptr;

    CPLString osLastRequestedStyleName{};
    int iNextStyle = 0;

    CPL_DISALLOW_COPY_ASSIGN(OGRStyleTable)

  public:
    HGDAL_EXPORT OGRStyleTable();
    HGDAL_EXPORT ~OGRStyleTable();
    HGDAL_EXPORT GBool AddStyle(const char *pszName,const char *pszStyleString);
    HGDAL_EXPORT GBool RemoveStyle(const char *pszName);
    HGDAL_EXPORT GBool ModifyStyle(const char *pszName, const char *pszStyleString);

    HGDAL_EXPORT GBool SaveStyleTable(const char *pszFilename);
    HGDAL_EXPORT GBool LoadStyleTable(const char *pszFilename);
    HGDAL_EXPORT const char *Find(const char *pszStyleString);
    HGDAL_EXPORT GBool IsExist(const char *pszName);
    HGDAL_EXPORT const char *GetStyleName(const char *pszName);
    HGDAL_EXPORT void  Print(FILE *fpOut);
    HGDAL_EXPORT void  Clear();
    HGDAL_EXPORT OGRStyleTable   *Clone();
    HGDAL_EXPORT void ResetStyleStringReading();
    HGDAL_EXPORT const char *GetNextStyle();
    HGDAL_EXPORT const char *GetLastStyleName();
};

class OGRStyleTool;

/**
 * This class represents a style manager
 */
class OGRStyleMgr
{
  private:
    OGRStyleTable   *m_poDataSetStyleTable = nullptr;
    char            *m_pszStyleString = nullptr;

    CPL_DISALLOW_COPY_ASSIGN(OGRStyleMgr)

  public:
    HGDAL_EXPORT explicit OGRStyleMgr(OGRStyleTable *poDataSetStyleTable = nullptr);
    HGDAL_EXPORT ~OGRStyleMgr();

    HGDAL_EXPORT GBool SetFeatureStyleString(OGRFeature *,const char *pszStyleString=nullptr,
                                GBool bNoMatching = FALSE);
    /* It will set in the given feature the pszStyleString with
            the style or will set the style name found in
            dataset StyleTable (if bNoMatching == FALSE). */

    HGDAL_EXPORT const char *InitFromFeature(OGRFeature *);
    HGDAL_EXPORT GBool InitStyleString(const char *pszStyleString = nullptr);

    HGDAL_EXPORT const char *GetStyleName(const char *pszStyleString= nullptr);
    HGDAL_EXPORT const char *GetStyleByName(const char *pszStyleName);

    HGDAL_EXPORT GBool AddStyle(const char *pszStyleName, const char *pszStyleString=nullptr);

    HGDAL_EXPORT const char *GetStyleString(OGRFeature * = nullptr);

    HGDAL_EXPORT GBool AddPart(OGRStyleTool *);
    HGDAL_EXPORT GBool AddPart(const char *);

    HGDAL_EXPORT int GetPartCount(const char *pszStyleString = nullptr);
    HGDAL_EXPORT OGRStyleTool *GetPart(int hPartId, const char *pszStyleString = nullptr);

    /* It could have a reference counting process us for the OGRStyleTable, if
      needed. */
//! @cond Doxygen_Suppress
    OGRStyleTable *GetDataSetStyleTable(){return m_poDataSetStyleTable;}

    HGDAL_EXPORT OGRStyleTool *CreateStyleToolFromStyleString(const char *pszStyleString);
//! @endcond
};

/**
 * This class represents a style tool
 */
class OGRStyleTool
{
  private:
    GBool m_bModified = false;
    GBool m_bParsed = false;
    double m_dfScale = 1.0;
    OGRSTUnitId m_eUnit = OGRSTUMM;
    OGRSTClassId m_eClassId = OGRSTCNone;
    char *m_pszStyleString = nullptr;

    virtual GBool Parse() = 0;

    CPL_DISALLOW_COPY_ASSIGN(OGRStyleTool)

  protected:
#ifndef DOXYGEN_SKIP
    HGDAL_EXPORT GBool Parse(const OGRStyleParamId* pasStyle,
                OGRStyleValue* pasValue,
                int nCount);
#endif

  public:

    HGDAL_EXPORT OGRStyleTool() :
        m_bModified(FALSE),
        m_bParsed(FALSE),
        m_dfScale(0.0),
        m_eUnit(OGRSTUGround),
        m_eClassId(OGRSTCNone),
        m_pszStyleString(nullptr)
        {}
    HGDAL_EXPORT explicit OGRStyleTool(OGRSTClassId eClassId);
    HGDAL_EXPORT virtual ~OGRStyleTool();

    HGDAL_EXPORT static GBool GetRGBFromString(const char *pszColor, int &nRed, int &nGreen,
                           int &nBlue, int &nTransparence);
    HGDAL_EXPORT static int   GetSpecificId(const char *pszId, const char *pszWanted);

#ifndef DOXYGEN_SKIP
    GBool IsStyleModified() {return m_bModified;}
    void  StyleModified() {m_bModified = TRUE;}

    GBool IsStyleParsed() {return m_bParsed;}
    void  StyleParsed() {m_bParsed = TRUE;}
#endif

    HGDAL_EXPORT OGRSTClassId GetType();

#ifndef DOXYGEN_SKIP
    HGDAL_EXPORT void SetInternalInputUnitFromParam(char *pszString);
#endif

    HGDAL_EXPORT void SetUnit(OGRSTUnitId,double dfScale = 1.0); //the dfScale will be
         //used if we are working with Ground Unit ( ground = paper * scale);

    OGRSTUnitId GetUnit(){return m_eUnit;}

    // There are two way to set the parameters in the Style, with generic
    // methods (using a defined enumeration) or with the reel method specific
    // for Each style tools.

    virtual const char *GetStyleString() = 0;
    HGDAL_EXPORT void SetStyleString(const char *pszStyleString);
    HGDAL_EXPORT const char *GetStyleString(const OGRStyleParamId *pasStyleParam ,
                            OGRStyleValue *pasStyleValue, int nSize);

    HGDAL_EXPORT const char *GetParamStr(const OGRStyleParamId &sStyleParam ,
                            OGRStyleValue &sStyleValue,
                            GBool &bValueIsNull);

    HGDAL_EXPORT int GetParamNum(const OGRStyleParamId &sStyleParam ,
                    OGRStyleValue &sStyleValue,
                    GBool &bValueIsNull);

    HGDAL_EXPORT double GetParamDbl(const OGRStyleParamId &sStyleParam ,
                       OGRStyleValue &sStyleValue,
                       GBool &bValueIsNull);

    HGDAL_EXPORT void SetParamStr(const OGRStyleParamId &sStyleParam ,
                     OGRStyleValue &sStyleValue,
                     const char *pszParamString);

    HGDAL_EXPORT void SetParamNum(const OGRStyleParamId &sStyleParam ,
                     OGRStyleValue &sStyleValue,
                     int nParam);

    HGDAL_EXPORT void SetParamDbl(const OGRStyleParamId &sStyleParam ,
                     OGRStyleValue &sStyleValue,
                     double dfParam);
#ifndef DOXYGEN_SKIP
    HGDAL_EXPORT double ComputeWithUnit(double, OGRSTUnitId);
    HGDAL_EXPORT int    ComputeWithUnit(int , OGRSTUnitId);
#endif
};

//! @cond Doxygen_Suppress

/**
 * This class represents a style pen
 */
class OGRStylePen : public OGRStyleTool
{
  private:

    OGRStyleValue    *m_pasStyleValue;

    GBool Parse() override;

    CPL_DISALLOW_COPY_ASSIGN(OGRStylePen)

  public:

    HGDAL_EXPORT OGRStylePen();
    HGDAL_EXPORT ~OGRStylePen() override;

    /**********************************************************************/
    /* Explicit fct for all parameters defined in the Drawing tools  Pen  */
    /**********************************************************************/

    const char *Color(GBool &bDefault){return GetParamStr(OGRSTPenColor,bDefault);}
    void SetColor(const char *pszColor){SetParamStr(OGRSTPenColor,pszColor);}
    double Width(GBool &bDefault){return GetParamDbl(OGRSTPenWidth,bDefault);}
    void SetWidth(double dfWidth){SetParamDbl(OGRSTPenWidth,dfWidth);}
    const char *Pattern(GBool &bDefault){return GetParamStr(OGRSTPenPattern,bDefault);}
    void SetPattern(const char *pszPattern){SetParamStr(OGRSTPenPattern,pszPattern);}
    const char *Id(GBool &bDefault){return GetParamStr(OGRSTPenId,bDefault);}
    void SetId(const char *pszId){SetParamStr(OGRSTPenId,pszId);}
    double PerpendicularOffset(GBool &bDefault){return GetParamDbl(OGRSTPenPerOffset,bDefault);}
    void SetPerpendicularOffset(double dfPerp){SetParamDbl(OGRSTPenPerOffset,dfPerp);}
    const char *Cap(GBool &bDefault){return GetParamStr(OGRSTPenCap,bDefault);}
    void SetCap(const char *pszCap){SetParamStr(OGRSTPenCap,pszCap);}
    const char *Join(GBool &bDefault){return GetParamStr(OGRSTPenJoin,bDefault);}
    void SetJoin(const char *pszJoin){SetParamStr(OGRSTPenJoin,pszJoin);}
    int  Priority(GBool &bDefault){return GetParamNum(OGRSTPenPriority,bDefault);}
    void SetPriority(int nPriority){SetParamNum(OGRSTPenPriority,nPriority);}

    /*****************************************************************/

    HGDAL_EXPORT const char *GetParamStr(OGRSTPenParam eParam, GBool &bValueIsNull);
    HGDAL_EXPORT int GetParamNum(OGRSTPenParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT double GetParamDbl(OGRSTPenParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT void SetParamStr(OGRSTPenParam eParam, const char *pszParamString);
    HGDAL_EXPORT void SetParamNum(OGRSTPenParam eParam, int nParam);
    HGDAL_EXPORT void SetParamDbl(OGRSTPenParam eParam, double dfParam);
    HGDAL_EXPORT const char *GetStyleString() override;
};

/**
 * This class represents a style brush
 */
class OGRStyleBrush : public OGRStyleTool
{
  private:

    OGRStyleValue    *m_pasStyleValue;

    GBool Parse() override;

    CPL_DISALLOW_COPY_ASSIGN(OGRStyleBrush)

  public:

    HGDAL_EXPORT OGRStyleBrush();
    HGDAL_EXPORT ~OGRStyleBrush() override;

    /* Explicit fct for all parameters defined in the Drawing tools Brush */

    const char *ForeColor(GBool &bDefault){return GetParamStr(OGRSTBrushFColor,bDefault);}
    void SetForeColor(const char *pszColor){SetParamStr(OGRSTBrushFColor,pszColor);}
    const char *BackColor(GBool &bDefault){return GetParamStr(OGRSTBrushBColor,bDefault);}
    void SetBackColor(const char *pszColor){SetParamStr(OGRSTBrushBColor,pszColor);}
    const char *Id(GBool &bDefault){ return GetParamStr(OGRSTBrushId,bDefault);}
    void  SetId(const char *pszId){SetParamStr(OGRSTBrushId,pszId);}
    double Angle(GBool &bDefault){return GetParamDbl(OGRSTBrushAngle,bDefault);}
    void SetAngle(double dfAngle){SetParamDbl(OGRSTBrushAngle,dfAngle );}
    double Size(GBool &bDefault){return GetParamDbl(OGRSTBrushSize,bDefault);}
    void SetSize(double dfSize){SetParamDbl(OGRSTBrushSize,dfSize  );}
    double SpacingX(GBool &bDefault){return GetParamDbl(OGRSTBrushDx,bDefault);}
    void SetSpacingX(double dfX){SetParamDbl(OGRSTBrushDx,dfX );}
    double SpacingY(GBool &bDefault){return GetParamDbl(OGRSTBrushDy,bDefault);}
    void SetSpacingY(double dfY){SetParamDbl(OGRSTBrushDy,dfY  );}
    int  Priority(GBool &bDefault){ return GetParamNum(OGRSTBrushPriority,bDefault);}
    void SetPriority(int nPriority){ SetParamNum(OGRSTBrushPriority,nPriority);}

    /*****************************************************************/

    HGDAL_EXPORT const char *GetParamStr(OGRSTBrushParam eParam, GBool &bValueIsNull);
    HGDAL_EXPORT int GetParamNum(OGRSTBrushParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT double GetParamDbl(OGRSTBrushParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT void SetParamStr(OGRSTBrushParam eParam, const char *pszParamString);
    HGDAL_EXPORT void SetParamNum(OGRSTBrushParam eParam, int nParam);
    HGDAL_EXPORT void SetParamDbl(OGRSTBrushParam eParam, double dfParam);
    HGDAL_EXPORT const char *GetStyleString() override;
};

/**
 * This class represents a style symbol
 */
class OGRStyleSymbol : public OGRStyleTool
{
  private:

    OGRStyleValue    *m_pasStyleValue;

    GBool Parse() override;

    CPL_DISALLOW_COPY_ASSIGN(OGRStyleSymbol)

  public:

    HGDAL_EXPORT OGRStyleSymbol();
    HGDAL_EXPORT ~OGRStyleSymbol() override;

    /*****************************************************************/
    /* Explicit fct for all parameters defined in the Drawing tools  */
    /*****************************************************************/

    const char *Id(GBool &bDefault){return GetParamStr(OGRSTSymbolId,bDefault);}
    void  SetId(const char *pszId){ SetParamStr(OGRSTSymbolId,pszId);}
    double Angle(GBool &bDefault){ return GetParamDbl(OGRSTSymbolAngle,bDefault);}
    void SetAngle(double dfAngle){SetParamDbl(OGRSTSymbolAngle,dfAngle );}
    const char *Color(GBool &bDefault){return GetParamStr(OGRSTSymbolColor,bDefault);}
    void SetColor(const char *pszColor){SetParamStr(OGRSTSymbolColor,pszColor);}
    double Size(GBool &bDefault){  return GetParamDbl(OGRSTSymbolSize,bDefault);}
    void SetSize(double dfSize){  SetParamDbl(OGRSTSymbolSize,dfSize  );}
    double SpacingX(GBool &bDefault){return GetParamDbl(OGRSTSymbolDx,bDefault);}
    void SetSpacingX(double dfX){SetParamDbl(OGRSTSymbolDx,dfX  );}
    double SpacingY(GBool &bDefault){return GetParamDbl(OGRSTSymbolDy,bDefault);}
    void SetSpacingY(double dfY){SetParamDbl(OGRSTSymbolDy,dfY  );}
    double Step(GBool &bDefault){return GetParamDbl(OGRSTSymbolStep,bDefault);}
    void SetStep(double dfStep){SetParamDbl(OGRSTSymbolStep,dfStep  );}
    double Offset(GBool &bDefault){return GetParamDbl(OGRSTSymbolOffset,bDefault);}
    void SetOffset(double dfOffset){SetParamDbl(OGRSTSymbolOffset,dfOffset  );}
    double Perp(GBool &bDefault){return GetParamDbl(OGRSTSymbolPerp,bDefault);}
    void SetPerp(double dfPerp){SetParamDbl(OGRSTSymbolPerp,dfPerp  );}
    int  Priority(GBool &bDefault){return GetParamNum(OGRSTSymbolPriority,bDefault);}
    void SetPriority(int nPriority){SetParamNum(OGRSTSymbolPriority,nPriority);}
    const char *FontName(GBool &bDefault)
        {return GetParamStr(OGRSTSymbolFontName,bDefault);}
    void SetFontName(const char *pszFontName)
        {SetParamStr(OGRSTSymbolFontName,pszFontName);}
    const char *OColor(GBool &bDefault){return GetParamStr(OGRSTSymbolOColor,bDefault);}
    void SetOColor(const char *pszColor){SetParamStr(OGRSTSymbolOColor,pszColor);}

    /*****************************************************************/

    HGDAL_EXPORT const char *GetParamStr(OGRSTSymbolParam eParam, GBool &bValueIsNull);
    HGDAL_EXPORT int GetParamNum(OGRSTSymbolParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT double GetParamDbl(OGRSTSymbolParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT void SetParamStr(OGRSTSymbolParam eParam, const char *pszParamString);
    HGDAL_EXPORT void SetParamNum(OGRSTSymbolParam eParam, int nParam);
    HGDAL_EXPORT void SetParamDbl(OGRSTSymbolParam eParam, double dfParam);
    HGDAL_EXPORT const char *GetStyleString() override;
};

/**
 * This class represents a style label
 */
class OGRStyleLabel : public OGRStyleTool
{
  private:

    OGRStyleValue    *m_pasStyleValue;

    GBool Parse() override;

    CPL_DISALLOW_COPY_ASSIGN(OGRStyleLabel)

  public:

    HGDAL_EXPORT OGRStyleLabel();
    HGDAL_EXPORT ~OGRStyleLabel() override;

    /*****************************************************************/
    /* Explicit fct for all parameters defined in the Drawing tools  */
    /*****************************************************************/

    const char *FontName(GBool &bDefault){return GetParamStr(OGRSTLabelFontName,bDefault);}
    void  SetFontName(const char *pszFontName){SetParamStr(OGRSTLabelFontName,pszFontName);}
    double Size(GBool &bDefault){return GetParamDbl(OGRSTLabelSize,bDefault);}
    void SetSize(double dfSize){SetParamDbl(OGRSTLabelSize,dfSize);}
    const char *TextString(GBool &bDefault){return GetParamStr(OGRSTLabelTextString,bDefault);}
    void SetTextString(const char *pszTextString){SetParamStr(OGRSTLabelTextString,pszTextString);}
    double Angle(GBool &bDefault){return GetParamDbl(OGRSTLabelAngle,bDefault);}
    void SetAngle(double dfAngle){SetParamDbl(OGRSTLabelAngle,dfAngle);}
    const char *ForeColor(GBool &bDefault){return GetParamStr(OGRSTLabelFColor,bDefault);}
    void SetForColor(const char *pszForColor){SetParamStr(OGRSTLabelFColor,pszForColor);}
    const char *BackColor(GBool &bDefault){return GetParamStr(OGRSTLabelBColor,bDefault);}
    void SetBackColor(const char *pszBackColor){SetParamStr(OGRSTLabelBColor,pszBackColor);}
    const char *Placement(GBool &bDefault){return GetParamStr(OGRSTLabelPlacement,bDefault);}
    void SetPlacement(const char *pszPlacement){SetParamStr(OGRSTLabelPlacement,pszPlacement);}
    int  Anchor(GBool &bDefault){return GetParamNum(OGRSTLabelAnchor,bDefault);}
    void SetAnchor(int nAnchor){SetParamNum(OGRSTLabelAnchor,nAnchor);}
    double SpacingX(GBool &bDefault){return GetParamDbl(OGRSTLabelDx,bDefault);}
    void SetSpacingX(double dfX){SetParamDbl(OGRSTLabelDx,dfX);}
    double SpacingY(GBool &bDefault){return GetParamDbl(OGRSTLabelDy,bDefault);}
    void SetSpacingY(double dfY){SetParamDbl(OGRSTLabelDy,dfY);}
    double Perp(GBool &bDefault){return GetParamDbl(OGRSTLabelPerp,bDefault);}
    void SetPerp(double dfPerp){SetParamDbl(OGRSTLabelPerp,dfPerp);}
    GBool Bold(GBool &bDefault){return GetParamNum(OGRSTLabelBold,bDefault);}
    void SetBold(GBool bBold){SetParamNum(OGRSTLabelBold,bBold);}
    GBool Italic(GBool &bDefault){return GetParamNum(OGRSTLabelItalic,bDefault);}
    void SetItalic(GBool bItalic){SetParamNum(OGRSTLabelItalic,bItalic);}
    GBool Underline(GBool &bDefault){return GetParamNum(OGRSTLabelUnderline,bDefault);}
    void SetUnderline(GBool bUnderline){SetParamNum(OGRSTLabelUnderline,bUnderline);}
    int  Priority(GBool &bDefault){return GetParamNum(OGRSTLabelPriority,bDefault);}
    void SetPriority(int nPriority){SetParamNum(OGRSTLabelPriority,nPriority);}
    GBool Strikeout(GBool &bDefault){return GetParamNum(OGRSTLabelStrikeout,bDefault);}
    void SetStrikeout(GBool bStrikeout){SetParamNum(OGRSTLabelStrikeout,bStrikeout);}
    double Stretch(GBool &bDefault){return GetParamDbl(OGRSTLabelStretch,bDefault);}
    void SetStretch(double dfStretch){SetParamDbl(OGRSTLabelStretch,dfStretch);}
    const char *ShadowColor(GBool &bDefault){return GetParamStr(OGRSTLabelHColor,bDefault);}
    void SetShadowColor(const char *pszShadowColor){SetParamStr(OGRSTLabelHColor,pszShadowColor);}
    const char *OutlineColor(GBool &bDefault){return GetParamStr(OGRSTLabelOColor,bDefault);}
    void SetOutlineColor(const char *pszOutlineColor){SetParamStr(OGRSTLabelOColor,pszOutlineColor);}

    /*****************************************************************/

    HGDAL_EXPORT const char *GetParamStr(OGRSTLabelParam eParam, GBool &bValueIsNull);
    HGDAL_EXPORT int GetParamNum(OGRSTLabelParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT double GetParamDbl(OGRSTLabelParam eParam,GBool &bValueIsNull);
    HGDAL_EXPORT void SetParamStr(OGRSTLabelParam eParam, const char *pszParamString);
    HGDAL_EXPORT void SetParamNum(OGRSTLabelParam eParam, int nParam);
    HGDAL_EXPORT void SetParamDbl(OGRSTLabelParam eParam, double dfParam);
    HGDAL_EXPORT const char *GetStyleString() override;
};

//! @endcond

#endif /* OGR_FEATURESTYLE_INCLUDE */
