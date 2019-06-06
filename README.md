Prerequisites:

- A GPU driver supporting EGL. 
- EGL and KHR headers. They can be obtained from https://www.khronos.org/registry/EGL/
- GNU C Compiler

Compilation steps:


gcc -I<path to EGL/KHR headers> -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"eglut.d" -MT"eglut.d" -o "eglut.o" "eglut.c"

gcc -I<path to EGL/KHR headers> -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"eglut_screen.d" -MT"eglut_screen.d" -o "eglut_screen.o" "eglut_screen.c"

gcc -shared -o "libeglut.so"  ./eglut.o ./eglut_screen.oe


Compiling eglgears sample:

g++ -I<paths to gpu-eglut and EGL/KHR headers> -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"eglgears.d" -MT"eglgears.d" -o "eglgears.o" "../eglgears.cpp"

g++ -L<paths to EGL/OpenGL Libs and gpu-eglut lib> -o "eglgears"  ./eglgears.o   -lm -leglut -lGL -lEGL