// f= x^2 + cos(sqrt(x)), x>=0

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <windows.h>

void main(void)
{
	double a = 0, b = 0, step;
	double x, f, t;

	puts("Enter the limits of calculations ( a b ):");
	scanf_s("%lf%lf", &a, &b);
	puts("Enter the value of step  ( step ):");
	scanf_s("%lf", &step);

	LARGE_INTEGER timerFrequency, timerStart, timerStop;

	x = a;
	f = 0;
	QueryPerformanceFrequency(&timerFrequency);
	QueryPerformanceCounter(&timerStart);
	_asm {
		finit

		fld b
		fld x
loop_start :
		fcom
			fstsw ax
			and ah, 01000101b
			jz loop_end

			fld x
			fsqrt

			fcos

			fld x
			fmul x

			fadd

			fadd f
			fstp f

			fadd step
			fst x
			jmp loop_start
	loop_end :
		fwait
	}
	QueryPerformanceCounter(&timerStop);
	t = ((double)timerStop.QuadPart - timerStart.QuadPart) / (double)timerFrequency.QuadPart;
	printf("Time ASM is %lf seconds.\n", t);
	printf("%lf\n", f);

	x = a;
	f = 0;
	QueryPerformanceFrequency(&timerFrequency);
	QueryPerformanceCounter(&timerStart);
	while (x <= b)
	{
		f += x*x + cos(sqrt(x));
		x += step;
	};
	QueryPerformanceCounter(&timerStop);
	t = (double)(timerStop.QuadPart - timerStart.QuadPart) / (double)timerFrequency.QuadPart;
	printf("Time C is %lf seconds.\n", t);
	printf("%lf\n", f);
	_getch();
}
