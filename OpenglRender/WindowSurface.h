/*
* Copyright (C) 2011 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef _LIBRENDER_WINDOWSURFACE_H
#define _LIBRENDER_WINDOWSURFACE_H

#include "ColorBuffer.h"
#include "RenderContext.h"
#include "FBConfig.h"
#include "smart_ptr.h"
#include "FixedBuffer.h"
#include "egl.h"
#include "gl.h"
#include "gl2.h"

enum SurfaceBindType {
    SURFACE_BIND_READ,
    SURFACE_BIND_DRAW,
    SURFACE_BIND_READDRAW
};

class WindowSurface
{
public:
    static WindowSurface *create(int p_config, int p_width, int p_height);
    ~WindowSurface();
    EGLSurface getEGLSurface() const { return m_eglSurface; }

    void setColorBuffer(ColorBufferPtr p_colorBuffer);
    bool flushColorBuffer();
    void bind(RenderContextPtr p_ctx, SurfaceBindType p_bindType);
    void bind_fbo();
    void unbind_fbo();
    void create_fbo_api1();
    void create_fbo_api2();

private:
    WindowSurface();

    bool blitToColorBuffer();  // copy pbuffer content with texload and blit
    bool resizePbuffer(unsigned int p_width, unsigned int p_height);

private:
    EGLSurface m_eglSurface;
    ColorBufferPtr m_attachedColorBuffer;
    RenderContextPtr m_readContext;
    RenderContextPtr m_drawContext;
    GLuint m_width;
    GLuint m_height;
    GLuint m_pbufWidth;
    GLuint m_pbufHeight;
    GLuint m_fbo;
    GLuint m_blitTex;
    EGLImageKHR m_blitEGLImage;

    const FBConfig *m_fbconf;
};

typedef emugl::SmartPtr<WindowSurface> WindowSurfacePtr;

#endif
