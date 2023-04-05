#ifndef _LOAD_SHADER_H
#define _LOAD_SHADER_H

#include "OpenGLInclude.h"
#include <bullet/bullet_export.h>


#ifdef __cplusplus
extern "C"
{
#endif  //__cplusplus

	BT_EXPORT GLuint gltLoadShaderPair(const char *szVertexProg, const char *szFragmentProg);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif  //_LOAD_SHADER_H
