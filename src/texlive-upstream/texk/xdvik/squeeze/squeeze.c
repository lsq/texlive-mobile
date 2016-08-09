/*========================================================================*\

Copyright (c) 1994-2004  Paul Vojta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
PAUL VOJTA OR ANY OTHER AUTHOR OF THIS SOFTWARE BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

NOTE:
This routine is adapted from the squeeze.c that comes with dvips;
it bears the message:
This software is Copyright 1988 by Radical Eye Software.
Used with permission.

\*========================================================================*/

/*
 *   This routine squeezes a PostScript file down to its
 *   minimum.  We parse and then output it.
 *   Adapted for xdvi 1/94.  Writes a C program that contains the PS file
 *   as a constant string.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif


#define LINELENGTH (72)
#define BUFLENGTH (1000)
#undef putchar
#define putchar(a) (void)putc(a, out) ;
FILE *in, *out;
static int linepos = 0;
static int lastspecial = 1;
static int stringlen = 0;
/*
 *   This next routine writes out a `special' character.  In this case,
 *   we simply put it out, since any special character terminates the
 *   preceding token.
 */
static void
specialout(char c)
{
    if (linepos + 1 > LINELENGTH) {
	(void)fputs("\\n\\\n", out);
	stringlen += linepos + 1;
	linepos = 0;
    }
    putchar(c);
    linepos++;
    lastspecial = 1;
}

static void
strout(char *s)
{
    if (linepos + strlen(s) > LINELENGTH) {
	(void)fputs("\\n\\\n", out);
	stringlen += linepos + 1;
	linepos = 0;
    }
    linepos += strlen(s);
    while (*s != 0)
	putchar(*s++);
    lastspecial = 1;
}

static void
cmdout(char *s)
{
    int l;

    l = strlen(s);
    if (linepos + l + 1 > LINELENGTH) {
	(void)fputs("\\n\\\n", out);
	stringlen += linepos + 1;
	linepos = 0;
	lastspecial = 1;
    }
    if (!lastspecial) {
	putchar(' ');
	linepos++;
    }
    while (*s != 0) {
	putchar(*s++);
    }
    linepos += l;
    lastspecial = 0;
}

char buf[BUFLENGTH];
#ifndef VMS
int
#endif
main(int argc, char *argv[])
{
    int c;
    char *b;
    char seeking;
    extern void exit();

    if (argc > 3 || (in = (argc < 2 ? stdin : fopen(argv[1], "r"))) == NULL ||
	(out = (argc < 3 ? stdout : fopen(argv[2], "w"))) == NULL) {
	(void)fprintf(stderr, "Usage:  squeeze [infile [outfile]]\n");
	exit(EXIT_FAILURE);
    }
    (void)fputs("/*\n"
		" *   DO NOT EDIT THIS FILE!\n"
		" *   It was created by squeeze.c from another file (see the Makefile).\n"
		" */\n\n"
		"const char psheader[] = \"\\\n", out);
    while (1) {
	c = getc(in);
	if (c == EOF)
	    break;
	if (c == '%') {
	    while ((c = getc(in)) != '\n');
	}
	if (c <= ' ')
	    continue;
	switch (c) {
	case '{':
	case '}':
	case '[':
	case ']':
	    specialout(c);
	    break;
	case '<':
	case '(':
	    if (c == '(')
		seeking = ')';
	    else
		seeking = '>';
	    b = buf;
	    *b++ = c;
	    do {
		c = getc(in);
		if (b > buf + BUFLENGTH - 2) {
		    (void)fprintf(stderr, "Overran buffer seeking %c", seeking);
		    exit(EXIT_FAILURE);
		}
		*b++ = c;
		if (c == '\\')
		    *b++ = getc(in);
	    } while (c != seeking);
	    *b++ = 0;
	    strout(buf);
	    break;
	default:
	    b = buf;
	    while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
		   (c >= '0' && c <= '9') || (c == '/') || (c == '@') ||
		   (c == '!') || (c == '"') || (c == '&') || (c == '*')
		   || (c == ':') || (c == ',') || (c == ';') || (c == '?')
		   || (c == '^') || (c == '~') || (c == '-') || (c == '.')
		   || (c == '#') || (c == '|') || (c == '_') || (c == '=')
		   || (c == '$') || (c == '+')) {
		*b++ = c;
		c = getc(in);
	    }
	    if (b == buf) {
		(void)fprintf(stderr, "Oops!  Missed a case: %c.\n", c);
		exit(EXIT_FAILURE);
	    }
	    *b++ = 0;
	    (void)ungetc(c, in);
	    cmdout(buf);
	}
    }
    (void)fprintf(out,
		  "\\n\";\n\n int\tpsheaderlen\t= %d;\n",
		  stringlen + linepos + 1);
    return 0;
}
