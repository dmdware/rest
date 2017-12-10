

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../texture.h"

#define JUST

int main()
{
#define NP		200
#define S		0.1f
#define V		6
#define DT		0.00005f
#define F		3000000
#define NW		3

#ifndef JUST
	char *tt;
#endif

	float x[NP];
	float v[NP];
	float a[NP];
	int i;
	float t;
	int j;
	float d;
	double dt;
	float x1, x2, xx;
	float d1, d2;
	int f;

#ifdef JUST
	float tr[NW];
	float htr[NW];
	float h2tr[NW];

	memset(tr, 0, sizeof(float)*NW);
	memset(htr, 0, sizeof(float)*NW);
	memset(h2tr, 0, sizeof(float)*NW);
#endif

#ifndef JUST
	tt = (char*)malloc(10 * NP * 3 * F);
#endif

	for (i = 0; i < NP; ++i)
	{
		v[i] = 0;
		x[i] = S + S * i;
	}

	v[0] = V;
	t = 0;
	dt = DT;
	f = 0;

	while (f < F)
	{
#ifdef JUST
		if (f % (F / 1000) == 0)
		{
			printf("f%d\r\n", f);
		}
#endif
#ifndef JUST
		for(i=0; i<10*NP; ++i)
		{
			tt[i * F * 3  + f * 3] = 255;
			tt[i * F * 3 + f * 3 + 1] = 255;
			tt[i * F * 3 + f * 3 + 2] = 255;

			if(i%10 == 0 && f%3 == 2)
				tt[i * F * 3 + f * 3] = 0;

		}
#endif
		//t += 0.5f;
		//dt = 0.5f;
	re:
		for (i = 0; i < NP; ++i)
		{
			x1 = x[(i + NP - 1) % NP] + v[(i + NP - 1) % NP] * dt;
			x2 = x[(i + 1) % NP] + v[(i + 1) % NP] * dt;
			xx = x[i] + v[i] * dt;

			if (x1 > S*NP)
				x1 -= S*NP;
			if (x1 < 0)
				x1 += S*NP;
			if (x2 > S*NP)
				x2 -= S*NP;
			if (x2 < 0)
				x2 += S*NP;

			if (xx > x2 && xx - x2 <= (S*NP) / 2.0f)
			{
				dt /= 2.0f;
				exit(0);
			}

			if (xx < x1 && x1 - xx <= (S*NP) / 2.0f)
			{
				dt /= 2.0f;
				exit(0);
			}

			if (xx >= S*NP && ((xx - S*NP) > x2) && (xx - S*NP) - x2 <= (S*NP)/2.0f)
			{
				dt /= 2.0f;
				exit(0);
			}
			if (xx < 0 && ((xx + S*NP) < x1) && x1 - (xx - S*NP) <= (S*NP) / 2.0f)
			{
				dt /= 2.0f;
				exit(0);
			}
		}

		t += dt;

		for (i = 0; i < NP; ++i)
		{
			x[i] += v[i] * dt;
			a[i] = 0;
			for (j = 0; j < NP; ++j)
			{
				if (j == i)
					continue;
				d1 = x[i] - x[j];
				if (d1 < 0)
				{
					d1 = fabs(S*NP + d1);
				}
				d2 = -fabs(d1 - S*NP);

				a[i] += fabs(d1) / d1 / (d1*d1);
				a[i] += fabs(d2) / d2 / (d2*d2);
			}
			v[i] += dt * a[i];

			if (x[i] < 0)
				x[i] += S*NP;
			if (x[i] >= S*NP)
				x[i] -= S*NP;
			j = ((int)((x[i] / (S) * 10)) % (NP * 10));

#ifdef JUST
			if (i == NP / 2)
			{
				if (v[i] > 0)
				{
					for (j = NW - 1; j >= 0; --j)
					{
						if (j % 2 == 0)
						{
							if (tr[j] == 0)
							{
								if (j == 0)
								{
									goto y;
								}
							}
						}
						else
						{
							if (tr[j] == 0)
							{
							}
							else
							{
								++j;
								goto y;
							}
						}
					}
				}
				else if (v[i] < 0)
				{
					for (j = NW - 1; j >= 0; --j)
					{
						if (j % 2 == 0)
						{
							if (tr[j] == 0)
							{
							}
							else
							{
								++j;
								goto y;
							}
						}
						else
						{
							if (tr[j] == 0)
							{
							}
						}
					}
				}

				goto n;

			y:
				tr[j] = f;
				printf("tr[%d]=%d\r\n", j, f);
			}

		n:
			;


			if (i == NP / 4)
			{
				if (v[i] > 0)
				{
					for (j = NW - 1; j >= 0; --j)
					{
						if (j % 2 == 0)
						{
							if (htr[j] == 0)
							{
								if (j == 0)
								{
									goto y;
								}
							}
						}
						else
						{
							if (htr[j] == 0)
							{
							}
							else
							{
								++j;
								goto y;
							}
						}
					}
				}
				else if (v[i] < 0)
				{
					for (j = NW - 1; j >= 0; --j)
					{
						if (j % 2 == 0)
						{
							if (htr[j] == 0)
							{
							}
							else
							{
								++j;
								goto y;
							}
						}
						else
						{
							if (htr[j] == 0)
							{
							}
						}
					}
				}

				goto hn;

			hy:
				htr[j] = f;
				printf("htr[%d]=%d\r\n", j, f);
			}

		hn:
			;





			if (i == NP * 3 / 4)
			{
				if (v[i] > 0)
				{
					for (j = NW - 1; j >= 0; --j)
					{
						if (j % 2 == 0)
						{
							if (h2tr[j] == 0)
							{
								if (j == 0)
								{
									goto y;
								}
							}
						}
						else
						{
							if (h2tr[j] == 0)
							{
							}
							else
							{
								++j;
								goto y;
							}
						}
					}
				}
				else if (v[i] < 0)
				{
					for (j = NW - 1; j >= 0; --j)
					{
						if (j % 2 == 0)
						{
							if (h2tr[j] == 0)
							{
							}
							else
							{
								++j;
								goto y;
							}
						}
						else
						{
							if (h2tr[j] == 0)
							{
							}
						}
					}
				}

				goto h2n;

			h2y:
				h2tr[j] = f;
				printf("h2tr[%d]=%d\r\n", j, f);
			}

		h2n:
			;
#endif

#ifndef JUST
			tt[j* F*3 + f * 3 + i % 2 + 1] = 0;
#endif
		}

		f++;
	}

#ifndef JUST
	savepng("alksjlaksd.png", (unsigned char*)tt, F, NP * 10, 3);
#endif
	system("pause");

	return 0;
}