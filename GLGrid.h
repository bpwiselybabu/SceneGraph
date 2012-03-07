#ifndef _GL_GRID_H_
#define _GL_GRID_H_

#include "GLObject.h"


/////////////////////////////////////////////////////////////////////////////
class GLGrid : public GLObject
{
    public:

        // from mvl dispview
        void draw(void)
        {

            int i;
#define NLINES 50
#define LDELTA 1

            glPushMatrix();

            glDepthMask (GL_TRUE);
            glEnable (GL_BLEND);
            glDisable(GL_LIGHTING);

            glBegin(GL_LINES);

            for(i = -NLINES; i < NLINES; i++){
                glColor4ub(32, 32, 32, 255);
                glVertex3f( LDELTA*NLINES, i*LDELTA, 0.0);
                glVertex3f(-LDELTA*NLINES, i*LDELTA, 0.0);

                glColor4ub(32, 32, 32, 255);
                glVertex3f(i*LDELTA,  LDELTA*NLINES, 0.0);
                glVertex3f(i*LDELTA, -LDELTA*NLINES, 0.0);
            }

            glColor4ub(255, 0, 0, 128);
            glVertex3f( LDELTA*NLINES , 0.0, 0.0);
            glVertex3f(-LDELTA*NLINES , 0.0, 0.0);

            glColor4ub(0, 255, 0, 128);
            glVertex3f( 0.0,  LDELTA*NLINES, 0.0);
            glVertex3f( 0.0, -LDELTA*NLINES, 0.0);

            glEnd();

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            glEnable( GL_BLEND );

            // so we generate depth on the ground plane
            glEnable( GL_DEPTH_TEST );
            glBegin( GL_QUADS );
            glColor4ub( 0, 0, 0, 0);
            glVertex3f(  LDELTA*NLINES ,  LDELTA*NLINES, 0.01);
            glVertex3f( -LDELTA*NLINES ,  LDELTA*NLINES, 0.01);
            glVertex3f( -LDELTA*NLINES , -LDELTA*NLINES, 0.01);
            glVertex3f(  LDELTA*NLINES , -LDELTA*NLINES, 0.01);
            glEnd();
            glPopMatrix();

            Eigen::Vector3d v = GetPosUnderCursor();
            glPointSize( 5 );
            glBegin( GL_POINTS );
            glColor4ub( 255, 255, 255, 255 );
            glVertex3f( v[0],  v[1], v[2] );
            glEnd();


        }

};

#endif

