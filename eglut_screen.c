/*
 * eglut_screen.c
 *
 *  Created on: May 2, 2019
 *      Author: benjha
 */
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define EGL_EGLEXT_PROTOTYPES
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include "eglutint.h"

#define MAX_MODES 100

static EGLint kms_width, kms_height;

void
_eglutNativeInitDisplay(void)
{
   _eglut->native_dpy = EGL_DEFAULT_DISPLAY;
   _eglut->surface_type = EGL_PBUFFER_BIT;
}

void
_eglutNativeFiniDisplay(void)
{
   kms_width = 0;
   kms_height = 0;
}


void
_eglutNativeInitWindow(struct eglut_window *win, const char *title,
                       int x, int y, int w, int h)
{
   EGLint surf_attribs[16];
   EGLint i;

   i = 0;
   surf_attribs[i++] = EGL_WIDTH;
   surf_attribs[i++] = w;
   surf_attribs[i++] = EGL_HEIGHT;
   surf_attribs[i++] = h;
   surf_attribs[i++] = EGL_NONE;

   /* create surface */
   win->native.u.surface =
		   eglCreatePbufferSurface (_eglut->dpy, win->config, surf_attribs);

   if (win->native.u.surface == EGL_NO_SURFACE)
      _eglutFatal("eglCreatePbufferSurface failed\n");

   win->native.width = w;
   win->native.height = h;
}

void
_eglutNativeFiniWindow(struct eglut_window *win)
{
   eglDestroySurface(_eglut->dpy, win->native.u.surface);
}

void
_eglutNativeEventLoop(void)
{
   int start = _eglutNow();
   int frames = 0;

   _eglut->redisplay = 1;

   while (1) {
      struct eglut_window *win = _eglut->current;
      int now = _eglutNow();

      if (now - start > 5000) {
         double elapsed = (double) (now - start) / 1000.0;

         printf("%d frames in %3.1f seconds = %6.3f FPS\n",
               frames, elapsed, frames / elapsed);

         start = now;
         frames = 0;

         /* send escape */
         if (win->keyboard_cb)
            win->keyboard_cb(27);
      }

      if (_eglut->idle_cb)
         _eglut->idle_cb();

      if (_eglut->redisplay) {
         _eglut->redisplay = 0;

         if (win->display_cb)
            win->display_cb();
         eglSwapBuffers(_eglut->dpy, win->surface);
         frames++;
      }
   }
}

