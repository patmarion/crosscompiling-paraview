
/*
 * Demo of off-screen Mesa rendering
 *
 * Usage: osdemo filename.ppm
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GL/osmesa.h"
#include "GL/glu.h"

#define WIDTH 800
#define HEIGHT 600

void InitGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // This Will Clear The Background Color To Black
  glClearDepth(1.0);        // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);              // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);            // Enables Depth Testing
  glShadeModel(GL_SMOOTH);      // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();        // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f); // Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
}

void RenderImage()
{

  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);  // Clear The Screen And The Depth Buffer
  glLoadIdentity();        // Reset The View

  glTranslatef(-1.5f,0.0f,-6.0f);    // Move Left 1.5 Units And Into The Screen 6.0

  glRotatef(30,0.0f,1.0f,0.0f);    // Rotate The Pyramid On The Y axis 

  // draw a pyramid (in smooth coloring mode)
  glBegin(GL_POLYGON);        // start drawing a pyramid

  // front face of pyramid
  glColor3f(1.0f,0.0f,0.0f);      // Set The Color To Red
  glVertex3f(0.0f, 1.0f, 0.0f);            // Top of triangle (front)
  glColor3f(0.0f,1.0f,0.0f);      // Set The Color To Green
  glVertex3f(-1.0f,-1.0f, 1.0f);    // left of triangle (front)
  glColor3f(0.0f,0.0f,1.0f);      // Set The Color To Blue
  glVertex3f(1.0f,-1.0f, 1.0f);            // right of traingle (front)  

  // right face of pyramid
  glColor3f(1.0f,0.0f,0.0f);      // Red
  glVertex3f( 0.0f, 1.0f, 0.0f);    // Top Of Triangle (Right)
  glColor3f(0.0f,0.0f,1.0f);      // Blue
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Left Of Triangle (Right)
  glColor3f(0.0f,1.0f,0.0f);      // Green
  glVertex3f( 1.0f,-1.0f, -1.0f);    // Right Of Triangle (Right)

  // back face of pyramid
  glColor3f(1.0f,0.0f,0.0f);      // Red
  glVertex3f( 0.0f, 1.0f, 0.0f);    // Top Of Triangle (Back)
  glColor3f(0.0f,1.0f,0.0f);      // Green
  glVertex3f( 1.0f,-1.0f, -1.0f);    // Left Of Triangle (Back)
  glColor3f(0.0f,0.0f,1.0f);      // Blue
  glVertex3f(-1.0f,-1.0f, -1.0f);    // Right Of Triangle (Back)

  // left face of pyramid.
  glColor3f(1.0f,0.0f,0.0f);      // Red
  glVertex3f( 0.0f, 1.0f, 0.0f);    // Top Of Triangle (Left)
  glColor3f(0.0f,0.0f,1.0f);      // Blue
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Left Of Triangle (Left)
  glColor3f(0.0f,1.0f,0.0f);      // Green
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Right Of Triangle (Left)

  glEnd();          // Done Drawing The Pyramid

  glLoadIdentity();        // make sure we're no longer rotated.
  glTranslatef(1.5f,0.0f,-7.0f);    // Move Right 3 Units, and back into the screen 7
  
  glRotatef(25,1.0f,1.0f,1.0f);    // Rotate The Cube On X, Y, and Z

  // draw a cube (6 quadrilaterals)
  glBegin(GL_QUADS);        // start drawing the cube.
  
  // top of cube
  glColor3f(0.0f,1.0f,0.0f);      // Set The Color To Blue
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)

  // bottom of cube
  glColor3f(1.0f,0.5f,0.0f);      // Set The Color To Orange
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)

  // front of cube
  glColor3f(1.0f,0.0f,0.0f);      // Set The Color To Red
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)

  // back of cube.
  glColor3f(1.0f,1.0f,0.0f);      // Set The Color To Yellow
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)

  // left of cube
  glColor3f(0.0f,0.0f,1.0f);      // Blue
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)

  // Right of cube
  glColor3f(1.0f,0.0f,1.0f);      // Set The Color To Violet
  glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Right)
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  glEnd();          // Done Drawing The Cube


   /* This is very important!!!
    * Make sure buffered commands are finished!!!
    */
   glFinish();
}



static void
write_ppm(const char *filename, const GLubyte *buffer, int width, int height)
{
   const int binary = 0;
   FILE *f = fopen( filename, "w" );
   if (f) {
      int i, x, y;
      const GLubyte *ptr = buffer;
      if (binary) {
         fprintf(f,"P6\n");
         fprintf(f,"# ppm-file created by osdemo.c\n");
         fprintf(f,"%i %i\n", width,height);
         fprintf(f,"255\n");
         fclose(f);
         f = fopen( filename, "ab" );  /* reopen in binary append mode */
         for (y=height-1; y>=0; y--) {
            for (x=0; x<width; x++) {
               i = (y*width + x) * 4;
               fputc(ptr[i], f);   /* write red */
               fputc(ptr[i+1], f); /* write green */
               fputc(ptr[i+2], f); /* write blue */
            }
         }
      }
      else {
         /*ASCII*/
         int counter = 0;
         fprintf(f,"P3\n");
         fprintf(f,"# ascii ppm file created by osdemo.c\n");
         fprintf(f,"%i %i\n", width, height);
         fprintf(f,"255\n");
         for (y=height-1; y>=0; y--) {
            for (x=0; x<width; x++) {
               i = (y*width + x) * 4;
               fprintf(f, " %3d %3d %3d", ptr[i], ptr[i+1], ptr[i+2]);
               counter++;
               if (counter % 5 == 0)
                  fprintf(f, "\n");
            }
         }
      }
      fclose(f);
   }
}





int main( int argc, char *argv[] )
{
   void *buffer;
   int i;
   char *filename = NULL;


   /* Create an RGBA-mode context */
#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
   /* specify Z, stencil, accum sizes */
   OSMesaContext ctx = OSMesaCreateContextExt( OSMESA_RGBA, 16, 0, 0, NULL );
#else
   OSMesaContext ctx = OSMesaCreateContext( OSMESA_RGBA, NULL );
#endif
   if (!ctx) {
      printf("OSMesaCreateContext failed!\n");
      return 0;
   }

   for ( i=1; i<argc; i++ ) {
      if (argv[i][0] != '-') filename = argv[i];
   }

   /* Allocate the image buffer */
   buffer = malloc( WIDTH * HEIGHT * 4 * sizeof(GLubyte) );
   if (!buffer) {
      printf("Alloc image buffer failed!\n");
      return 0;
   }

   /* Bind the buffer to the context and make it current */
   if (!OSMesaMakeCurrent( ctx, buffer, GL_UNSIGNED_BYTE, WIDTH, HEIGHT )) {
      printf("OSMesaMakeCurrent failed!\n");
      return 0;
   }
     

   {
      int z, s, a;
      glGetIntegerv(GL_DEPTH_BITS, &z);
      glGetIntegerv(GL_STENCIL_BITS, &s);
      glGetIntegerv(GL_ACCUM_RED_BITS, &a);
      printf("Depth=%d Stencil=%d Accum=%d\n", z, s, a);
   }

  InitGL();
  RenderImage();

   if (filename != NULL) {
      write_ppm(filename, (GLubyte*)buffer, WIDTH, HEIGHT);
   }
   else {
      printf("Specify a filename (with ppm extension) if you want to make an image file\n");
   }

   printf("all done\n");

   /* free the image buffer */
   free( buffer );

   /* destroy the context */
   OSMesaDestroyContext( ctx );

   return 0;
}
