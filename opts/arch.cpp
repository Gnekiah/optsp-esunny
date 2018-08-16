#include "arch.h"

#if defined(__linux__)
int _getch(void) {
	struct termios tm, tm_old;
	int fd = 0, c;
	if (tcgetattr(fd, &tm) < 0)
		return -1;
	tm_old = tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd, TCSANOW, &tm) < 0)
		return -1;
	c = fgetc(stdin);
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0)
		return -1;
	return c;
}
#endif


char *InputPasswd(char *passwd, int max)
{
	int i = 0, ch;
	max--;
	puts("Password:");
	while ((ch = _getch()) != -1 && ch != ASCII_ENTER) {
		if (i == max && ch != ASCII_BACKSPACE) {
			putchar(ASCII_ALARM);
			continue;
		}
		if (ch == ASCII_BACKSPACE) {
			if (i == 0) {
				putchar(ASCII_ALARM);
				continue;
			}
			i--;
			putchar(ASCII_BACKSPACE);
			putchar(' ');
			putchar(ASCII_BACKSPACE);
		}
		else {
			passwd[i] = ch;
			putchar('*');
			i++;
		}
	}
	if (ch == -1) {
		while (i != -1) {
			passwd[i--] = '\0';
		}
		return NULL;
	}
	passwd[i] = '\0';
	printf("\n");
	return passwd;
}
