#include <cstdlib>
#include <cstdio>
#include <cmath>

int* cipher;

int analyzerepetition(int symbol)
{
	int* seen = (int*)calloc(201, sizeof(int));
	int sym = symbol;
	int steps = 0;
	do
	{
		steps++;
		sym = cipher[sym];
		if(sym != symbol && seen[sym])
			return -1;
		seen[sym] = 1;
	}
	while(sym != symbol);
	return steps;
}

int gcd(int num, int den)
{
	int temp;
	while(den > 0)
	{
		temp = den;
		den = num % den;
		num = temp;
	}
	return num;
}

int lcm(int a, int b)
{
	if(b > a)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	int divisor = gcd(a, b);
	int n = a;
	while(n % a != 0 || n % b != 0)
		n += divisor;
	return n;
}

int main()
{
	FILE* in = fopen("leakin.txt", "r");
	FILE* out = fopen("leakout.txt", "w");
	
	int ncipher;
	int recipelength;
	fscanf(in, "%d %d", &ncipher, &recipelength);
	
	cipher = (int*)malloc(sizeof(int) * (1 + ncipher));
	
	for(int i = 1; i <= ncipher; i++)
		fscanf(in, "%d", cipher + i);
	
	int reps = 1;
	bool* recipeseen = (bool*)calloc(ncipher + 1, sizeof(bool));
	for(int i = 0; i < recipelength; i++)
	{
		int sym;
		fscanf(in, "%d", &sym);
		if(!recipeseen[sym])
		{
			recipeseen[sym] = true;
			int repanalysis = analyzerepetition(sym);
			if(repanalysis == -1)
			{
				fprintf(out, "Never");
				return 0;
			}
		#ifdef EBUG
			printf("analysis for symbol %d: %lld\n", sym, repanalysis);
		#endif
			reps = lcm(repanalysis, reps);
		}
	}
	
	fprintf(out, "%lld\n", reps);
}
