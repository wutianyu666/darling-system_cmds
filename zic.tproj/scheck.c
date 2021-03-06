#ifndef lint
#ifndef NOID
#include <sys/cdefs.h>
__unused static const char	elsieid[] = "@(#)scheck.c	8.15";
#endif /* !defined lint */
#endif /* !defined NOID */

#ifndef lint
__unused static const char rcsid[] =
  "$FreeBSD: src/usr.sbin/zic/scheck.c,v 1.7 2001/07/18 11:27:04 dd Exp $";
#endif /* not lint */

/*LINTLIBRARY*/

#include "private.h"

char *
scheck(const char * const string, const char * const format)
{
	char *		fbuf;
	const char *	fp;
	char *		tp;
	int		c;
	char *		result;
	char		dummy;
	static char	nada;

	result = &nada;
	if (string == NULL || format == NULL)
		return result;
	fbuf = imalloc((int) (2 * strlen(format) + 4));
	if (fbuf == NULL)
		return result;
	fp = format;
	tp = fbuf;
	while ((*tp++ = c = *fp++) != '\0') {
		if (c != '%')
			continue;
		if (*fp == '%') {
			*tp++ = *fp++;
			continue;
		}
		*tp++ = '*';
		if (*fp == '*')
			++fp;
		while (is_digit(*fp))
			*tp++ = *fp++;
		if (*fp == 'l' || *fp == 'h')
			*tp++ = *fp++;
		else if (*fp == '[')
			do *tp++ = *fp++;
				while (*fp != '\0' && *fp != ']');
		if ((*tp++ = *fp++) == '\0')
			break;
	}
	*(tp - 1) = '%';
	*tp++ = 'c';
	*tp = '\0';
	if (sscanf(string, fbuf, &dummy) != 1)
		result = (char *) format;
	ifree(fbuf);
	return result;
}
