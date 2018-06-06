#include <SDL2/SDL.h>
#include <SDL/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Mon premier programme OpenGL !",NULL);
	SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	bool continuer = true;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = false;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
		glColor3ub(0,255,0);    glVertex2d(0,0.75);
		glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
		glEnd();

		glFlush();
		SDL_GL_SwapBuffers();
	}

	SDL_Quit();

	return 0;
}
