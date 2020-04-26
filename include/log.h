/*
Copyright (c) 2020 matt pallissard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 * yes, is fucking terrible. it's on my todo list.
 */
#define _POSIX_C_SOURCE 200809L // for gmtime_r
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define LOG_EMERG 0
#define LOG_ALERT 1
#define LOG_CRIT 2
#define LOG_ERR 3
#define LOG_WARNING 4
#define LOG_NOTICE 5
#define LOG_INFO 6
#define LOG_DEBUG 7

uint8_t level;
uint8_t date;
const char *label[] = { "emerge", "alert", "crit", "err", "warning", "notice", "info", "debug" };

const char *color[] = {
	"\x1b[35m", "\x1b[31m", "\x1b[31m", "\x1b[31m", "\x1b[33m", "\x1b[32m", "\x1b[36m", "\x1b[94m", "\x1b[94m", "\x1b[94m",
};
const char *color_reset = "\x1b[0m";

#define setprintmask(i) level = i;

#define setprintdate(i) date = i;

void get_time(char *c_time)
{
	time_t t = time(NULL);
	struct tm *lt = NULL;
	gmtime_r(&t, lt);
	int ct = strftime(c_time, 20, "%Y-%m-%d %H:%M:%S", lt);
	c_time[ct++] = ' ';
	c_time[ct] = '\0';
}

void print_string(const char *format, uint8_t log_level, va_list m)
{
	char c_time[20];
	c_time[0] = '\0';
	if (date) {
		get_time(c_time);
	};
	printf("%s%s%-7s%s", c_time, color[log_level], label[log_level], color_reset);
	vprintf(format, m);
	printf("\n");
}

void printu(uint8_t log_level, const char *format, ...)
{
	if (log_level <= level) {
		va_list m;
		va_start(m, format);
		print_string(format, log_level, m);
		va_end(m);
	};
}
