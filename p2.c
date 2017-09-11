#include <stdio.h>
#include <stdint.h>

#define P 0.5
#define DEBUG

double q[5] = {0.02, 0.15, 0.74, 0.83, 3.39};
int n[5] = {1, 2, 3, 4, 5};
float n1[5] = {1, 1 + 2 * P, 1 + 4 * P, 3 + 2 * P, 5};
float dn[5] = {0, P/2, P, (P + 1)/2, 1};

int main(){
	double x;
	int i, k, d;
	double q1;

	while(1)
	{
		puts("Input a new arrival:");
		scanf("%lf", &x);
		printf("New arrival %lf\n", x);

		// Find cell k and adjust extreme values
		if (x >= q[2])
		{
			if (x < q[3])
				k = 2;
			else if(x >= q[3] && x <= q[4])
				k = 3;
			else
			{
				q[4] = x;
				k = 3;
			}			
		}
		else
		{
			if (x >= q[1])
				k = 1;
			else if (q[0] <= x && x < q[1])
				k = 0;
			else
			{
				q[0] = x;
				k = 0;
			}		
		}
		printf("k equals to %d\n", k);

		// increment positions of markers k+1 through 5
		while (k < 5)
		{
			n[k+1]++;
			k++;
		}

		// Update desired positions for all markers:
		for (i=0; i<5; i++)
			n1[i] += dn[i];

		// Adjust heights of markers 2-4 if necessary
		for (i = 1; i<=3; i++)
		{
			d = n1[i] - n[i];
			if ((d>=1 && n[i+1]-n[i]>1) || (d<=-1 && n[i-1]-n[i]<-1))
			{
				d = d > 0? 1 : -1;
				
				q1 = q[i] + ((float)d/(n[i+1]-n[i-1])) * 
				 	(float)((n[i]-n[i-1]+d)*(q[i+1]-q[i])/(n[i+1]-n[i]) + (n[i+1]-n[i]-d)*(q[i]-q[i-1])/(n[i]-n[i-1]));

				if (q1 > q[i-1] && q1 < q[i+1])
					q[i] = q1;
				else
					q[i] = q[i] + d*(q[i+d] - q[i])/(n[i+d]-n[i]);
	
				printf("d=%d index %d %f\n", d, i, (float)d/(n[i+1]-n[i-1]));
				
				n[i] += d;
				
			}
		}


		printf("The new positions of n: ");
		for (i=0; i<5; i++)
			printf("%d\t", n[i]);
		putchar('\n');

		printf("The new desired positions of n: ");
		for (i=0; i<5; i++)
			printf("%f\t", n1[i]);
		putchar('\n');

		printf("The new desired height of q: ");
		for (i=0; i<5; i++)
			printf("%f\t", q[i]);
		putchar('\n');

		printf("Result: %lf\n", q[2]);
	}
}
















