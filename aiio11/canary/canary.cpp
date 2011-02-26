#include <cstdio>
#include <cstdlib>

using namespace std;

#define GRID(x,y) grid[(y)*C + (x)]
#define CACHE(x,y) cache[(y)*C + (x)]

int R, C;
int* grid;
int* cache;

int find_number_of_paths(int x, int y)
{
	if(CACHE(x, y) > 0)
		return CACHE(x, y);
	
	int paths = 0;
	if(x > 0 && GRID(x-1, y) < GRID(x, y))
		paths += find_number_of_paths(x - 1, y);
	if(y > 0 && GRID(x, y-1) < GRID(x, y))
		paths += find_number_of_paths(x, y - 1);
	if(x + 1 < C && GRID(x+1, y) < GRID(x, y))
		paths += find_number_of_paths(x + 1, y);
	if(y + 1 < R && GRID(x, y+1) < GRID(x, y))
		paths += find_number_of_paths(x, y + 1);
	
	if(paths == 0)
		paths = 1;
		
	CACHE(x, y) = paths % 1000003;
	return paths % 1000003;
}

int pmain();
int main()
{
	char* newstack = (char*)malloc(16*1024*1024) + 16*1024*1024 - 64;
	asm("movl %%eax, %%esp" : : "a" (newstack));
	pmain();
	exit(0);
}

int pmain()
{
	FILE* in = fopen("birdin.txt", "r");
	FILE* out = fopen("birdout.txt", "w");
	
	fscanf(in, "%d %d", &R, &C);
	grid = (int*)malloc(sizeof(int) * R * C);
	cache = (int*)calloc(R * C, sizeof(int));
	
	for(int y = 0; y < R; y++)
		for(int x = 0; x < C; x++)
		{
			fscanf(in, "%d", &(GRID(x, y)));
		}
	
	int paths = 0;
	for(int y = 0; y < R; y++)
		for(int x = 0; x < C; x++)
		{
			if(y > 0 && GRID(x,y) < GRID(x,y-1))
				continue;
			if(x > 0 && GRID(x,y) < GRID(x-1,y))
				continue;
			if(x+1 < C && GRID(x,y) < GRID(x+1,y))
				continue;
			if(y+1 < R && GRID(x,y) < GRID(x,y+1))
				continue;
			// must be local maximum at this point
			paths += find_number_of_paths(x, y);
		}
	
	fprintf(out, "%d\n", paths);
	
	fclose(out);
	fclose(in);
	
	return 0;
}
