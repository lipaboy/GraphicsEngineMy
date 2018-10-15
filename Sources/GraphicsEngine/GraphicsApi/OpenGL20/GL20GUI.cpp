#include "GL20GUI.h"
#include <string.h>
#include <stdio.h>

namespace graphics_engine {

void GL20GUI::Label(int x, int y, int width, int height, const char * labelStr)
{
	// http://stackoverflow.com/questions/9430852/glutbitmapcharacter-positions-text-wrong	

    //TEXT
    glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix() ; // save
    glLoadIdentity();// and clear
    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;

    glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top

    glRasterPos2f( -1,-1 ) ; // center of screen. (-1,0) is center left.
//    glRasterPos2i(x,y);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    char buf[300];
    sprintf( buf, labelStr ) ;
    const char * p = buf ;
    do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); while( *(++p) ) ;

    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix() ; // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix() ;
}

}
