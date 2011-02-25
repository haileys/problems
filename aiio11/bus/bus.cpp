#include <cstdio>
#include <cstdlib>

using namespace std;

struct node
{
	int data;
	node* next;
	node* prev;
	
	node(int data)
	  : data(data),
		next(NULL),
		prev(NULL)
	{ }  
};

int ndrivers;
int* drivers;
int nshortlist;
int* shortlist;
bool* seen;

node* noderam;

node* head = NULL;
int driversleft = 0;

void rmnode(node* n)
{
	if(n == head)
		head = n->next;
	else
		n->prev->next = n->next;
	if(n->next != NULL)
		n->next->prev = n->prev;
//	delete n;
}
int main()
{
	FILE* in = fopen("busin.txt", "r");
	FILE* out = fopen("busout.txt", "w");

	fscanf(in, "%d %d", &ndrivers, &nshortlist);
	drivers = (int*)malloc(sizeof(int) * (ndrivers + 1));
	seen = (bool*)calloc(ndrivers + 1, sizeof(bool));
	shortlist = (int*)calloc(ndrivers + 1, sizeof(int));
	noderam = (node*)malloc(sizeof(node) * (ndrivers + 1));
	
	node* tail = NULL;
	for(int i = 1; i <= ndrivers; i++)
	{
		fscanf(in, "%d", drivers + i);
		node* driver = noderam++;
		driver->data = i;
		if(head == NULL)
			head = driver;
		if(tail != NULL)
			tail->next = driver;
		driver->prev = tail;
		tail = driver;
	}
	driversleft = ndrivers;

	for(int i = 0; i < nshortlist; i++)
	{
		int d;
		fscanf(in, "%d", &d);
		shortlist[d] = 1;
	}
	
	int rounds = nshortlist;
	while(driversleft > 2)
	{
		for(node* cur = head; cur != NULL;)
		{
			node* next = cur->next->next;
			
			int a = cur->data;
			int b = cur->next->data;
		#ifdef EBUG
			printf("%d vs %d\n", a, b);
		#endif
			if(shortlist[a] && shortlist[b])
			{
			#ifdef EBUG
				printf("  - both in shortlist\n");
			#endif
				if(!seen[a]	&& !seen[b])
				{
					seen[a] = seen[b] = 1;
				#ifdef EBUG
					printf("  - haven't seen either before\n");
				#endif
					rounds--;
				}
			}
			if(drivers[a] < drivers[b])
			{
				rmnode(cur);
			}
			else
			{
				rmnode(cur->next);
			}
			
			cur = next;
		}
		driversleft /= 2;
	}
	
	fprintf(out, "%d\n", rounds);
}
