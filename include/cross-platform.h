#if (defined(_WIN32) || defined(__CYGWIN__))

#include <conio.h>

void init_termios(void) {
	
}

void atexit_termios(void) {

}

#elif (defined(unix) || defined(__unix) || defined(__unix__))

#include <unistd.h>
#include <termios.h>
#include <errno.h>

struct termios
	termios_before;

void init_termios(void) {
	fflush(stdout);

	struct termios old = {0};
	
	if(tcgetattr(0, &old) < 0) {
		perror("tcsetattr()");
	}
	
	termios_before = old;
	
	// Ported from https://github.com/scocoyash/Text-Editor-In-C/edit/master/stex.c
	old.c_lflag &= ~(ECHO | ECHOE | ICANON | IEXTEN);
	old.c_iflag &= ~(INPCK | ISTRIP | IXON);
	old.c_cflag |= (CS8);
	
	old.c_cc[VMIN]  = 1;
	old.c_cc[VTIME] = 0;
	
	if(tcsetattr(0, TCSANOW, &old) < 0) {
		perror("tcsetattr ICANON");
	}
}

char getch(void) {
    return fgetc(stdin);
}

int gotoxy(int x, int y) {
	printf("\033[%d;%df", x, y);
	
	return 0;
}

void atexit_termios(void) {
	if(tcsetattr(0, TCSADRAIN, &termios_before) < 0) {
		perror("tcsetattr ~ICANON");
	}
}

#elif (defined(__APPLE__) || defined(__MACH__))

#elif (defined(__linux__) || defined(linux) || defined(__linux))

#elif (defined(__FreeBSD__))

#elif (defined(__ANDROID__))

#endif
