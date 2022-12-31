//NAME : SUNDEEP A
//SRN : PES1UG20CS445

#include "header.h"
#include<limits.h>
// ANY STATIC FUNCTIONS ARE UP HERE
typedef struct edge {
  int u, v, w;
} edge;
typedef struct stack
{
    int arr[400];
    int top;
}stack_t;
typedef struct e_list {
  edge data[400];
  int n;
} e_list;

e_list elist;
e_list slist;

static void DFS_1(int v,int n,const connection_t connections[n][n],int visit[])
{
    visit[v]=1;
    for(int o=0;o<n;o++)
        if(connections[v][o].distance>0 && v!=o && connections[v][o].distance<INT_MAX && visit[o]==0)
            DFS_1(o,n,connections,visit);
return;
}

static void DFS_2(int src,int desti,int n,const connection_t connections[n][n],int visit[],int *minimum_edge,int *counter)
{
visit[src]=1;
if(src==desti)
    if(*counter<*minimum_edge)
        *minimum_edge=*counter;
for(int o=0;o<n;o++)
{
    if(visit[o]==0 && connections[src][o].distance>0 && connections[src][o].distance<INT_MAX && o!=src)
    {
        *counter=*counter+1;
        DFS_2(o,desti,n,connections,visit,minimum_edge,counter);
    }
}
visit[src]=0;
*counter=*counter-1;
}
//3
static int pathfinding(int src, int desti, int n, int *visit, const connection_t connections[n][n])
{
    int u;
    visit[src] = 1;
    for (u = 0; u < n; u++)
        if ((connections[src][u].distance != INT_MAX) && (visit[u] == 0))
            if ((u == desti) || pathfinding(u, desti, n, visit, connections))
                return 1;
    return 0;
}

static int route(int src, int desti, int n, const connection_t connections[n][n])
{
    int visit[n];
    int o;
    for (o = 0; o < n; o++)
        visit[o] = 0;
    return pathfinding(src, desti, n, visit, connections);
}
//4
static void swap(airport_t *a, airport_t *b)
{
    airport_t t = *a;
    *a = *b;
    *b = t;
}
static int func_partition(int n, airport_t airport_list[n], int lo, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    airport_t pivot = airport_list[high];
    int o = (lo - 1);
    for (int z = lo; z < high; z++)
        if (predicate_func(&airport_list[z], &pivot))
        {
            o++;
            swap(&airport_list[o], &airport_list[z]);
        }
    swap(&airport_list[o + 1], &airport_list[high]);
    return (o + 1);
}

static void quick_sorting(int n, airport_t airport_list[n], int lo, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    if (lo < high)
    {
        int partition = func_partition(n, airport_list, lo, high, predicate_func);
        quick_sorting(n, airport_list, lo, partition - 1, predicate_func);
        quick_sorting(n, airport_list, partition + 1, high, predicate_func);
    }
}
//5
static int len(airport_t airport_1,airport_t airport_2)
{
    int o=0;
    while(airport_1.airport_name[o]!='\0' && airport_2.airport_name[o]!='\0' && airport_1.airport_name[o] == airport_2.airport_name[o])
        o++;
    return o;
}
//6
static int binarySearch(int arr[], int l, int r, int x, int n)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid + 1;
        else if ((arr[mid - 1] < x) && (x < arr[mid]))
            return mid;
        else if (mid == n - 1)
            return mid + 1;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x, n);
        return binarySearch(arr, mid + 1, r, x, n);
    }
    return -1;
}
//7
static int length(const char *string)
{
    int string_len = 0;
    while (*string)
    {
        string_len++;
        string++;
    }

    return string_len;
}
static void shifttable(const char *p, int t[])
{
    int k, z, c;
    c = length(p);
    for (k = 0; k < 200; k++)
        t[k] = c;
    for (z = 0; z < c - 1; z++)
        t[p[z]] = c - 1 - z;
}

static int horspool_algo(const char src[], const char *p, int t[], int len)
{
    int q, z, k, c, n;
    n = length(src);
    c = length(p);
    // printf("\nLength of text=%d",n);
    // printf("\n Length of pattern=%d",c);
    q = c - 1;
    while (q < n)
    {
        k = 0;
        while ((k < c) && (p[c - 1 - k] == src[q - k]))
            k++;
        if (k == c)
            return (q - c + 1);
        else
            q += t[src[q]];
    }
    return -1;
}
//8
static void initialization(stack_t* s)
{
    s->top=-1;
}
static int full(stack_t* s)
{
    return s->top==400-1;
}
static void push(stack_t* s,int ele)
{
    if(!full(s))
    {
        s->top=s->top+1;
        s->arr[s->top]=ele;
    }
}
static int pop(stack_t* s)
{ 
    return s->arr[s->top--];
}
static int top(stack_t* s)
{   
    return s->arr[s->top];
}
static void insert(int cycles[25][25],int v,int* cycle_no)
{
    int i=*cycle_no;
    int index=-1;
    for(int j=0;j<25 && index == -1;j++)
        if(cycles[i][j]==-1)
            index=j;
    cycles[i][index]=v;
}
static void cycle(stack_t* s,int v,int cycles[25][25],int* cycle_no)
{
    stack_t s2;
    initialization(&s2);
    push(&s2,top(s));
    pop(s);
    while(top(&s2)!=v)
    {
        push(&s2,top(s));
        pop(s);
    }
    while(s2.top!=-1)
    {
        insert(cycles,top(&s2),cycle_no);
        push(s,top(&s2));
        pop(&s2);
    }
}
static void DFS_8(int n,const connection_t connections[n][n],stack_t* s,int visit[n],int cycles[25][25],int* cycle_no)
{
    int u=top(s);
    for(int i=0;i<n;i++)
    {
        if(connections[u][i].distance!=0 && connections[u][i].distance!=INT_MAX &&visit[i]==0)
        {
            *cycle_no=*cycle_no+1;
            cycle(s,i,cycles,cycle_no);
        }
        else if(connections[u][i].distance!=0 && connections[u][i].distance!=INT_MAX &&visit[i]==-1)
        {
            push(s,i);
            visit[i]=0;
            DFS_8(n,connections,s,visit,cycles,cycle_no);
        }
    }
    visit[top(s)]=1;
    pop(s);
}
static void finding_cycles(int n,const connection_t connections[n][n],int visit[n],int cycles[25][25],int* cycle_no)
{
    for(int i=0;i<n;i++)
        if(visit[i]==-1)
        {
            stack_t s;
            initialization(&s);
            push(&s,i);
            visit[i]=0;
            DFS_8(n,connections,&s,visit,cycles,cycle_no);
        }
}

//9
static int finding(int g[], int v_no) {
  return (g[v_no]);
}
static void applying_union(int n, int g[], int c1, int c2)
 {
  int o;
  for (o = 0; o < n; o++)
    if (g[o] == c2)
      g[o] = c1;
}
static void sorting() 
{
  int o, z;
  edge temp;
  for (o = 1; o < elist.n; o++)
    for (z = 0; z < elist.n - 1; z++)
      if (elist.data[z].w > elist.data[z + 1].w) 
      {
        temp = elist.data[z];
        elist.data[z] = elist.data[z + 1];
        elist.data[z + 1] = temp;
      }
}
static int display(pair_t edges[])
{
  int o, value = 0;
  for (o = 0; o < slist.n; o++) 
  {
    edges[o].first = slist.data[o].v;
    edges[o].second = slist.data[o].u;
    value = value + slist.data[o].w;
  }
  return value;
}
// Applying Krushkal Algo
static void krushkal_algorithm(int n, const connection_t connections[n][n])
{
  int g[400], o, z, c_1, c_2;
  elist.n = 0;
  for (o = 1; o < n; o++)
    for (z = 0; z < o; z++) 
    {
      if (connections[o][z].time != 0) 
      {
        elist.data[elist.n].u = o;
        elist.data[elist.n].v = z;
        elist.data[elist.n].w = connections[o][z].time;
        elist.n++;
      }
    }
  sorting();
  for (o = 0; o < n; o++)
    g[o] = o;
  slist.n = 0;
  for (o = 0; o < elist.n; o++)
   {
        c_1 = finding(g, elist.data[o].u);
        c_2 = finding(g, elist.data[o].v);
        if (c_1 != c_2) 
        {
            slist.data[slist.n] = elist.data[o];
            slist.n = slist.n + 1;
            applying_union(n, g, c_1, c_2);
        }
    }
}
//10
static void Dijkstras(int n, const connection_t connections[n][n], int src, const int desti[], int costs[], int k)
{
    int value[n][n], distance[n], pred[n];
    int visit[n], counter, minimum_distance, next_node, o, z;
    for (o = 0; o < n; o++)
        for (z = 0; z < n; z++)
            if (connections[o][z].time == 0)
                value[o][z] = INT_MAX;
            else
                value[o][z] = connections[o][z].time;
    for (o = 0; o < n; o++)
    {
        distance[o] = value[src][o];
        pred[o] = src;
        visit[o] = 0;
    }
    distance[src] = 0;
    visit[src] = 1;
    counter = 1;
    while (counter < n - 1)
    {
        minimum_distance = INT_MAX;
        for (o = 0; o < n; o++)
            if (distance[o] < minimum_distance && !visit[o])
            {
                minimum_distance = distance[o];
                next_node = o;
            }
        visit[next_node] = 1;
        for (o = 0; o < n; o++)
            if (!visit[o])
                if (minimum_distance + value[next_node][o] < distance[o])
                {
                    distance[o] = minimum_distance + value[next_node][o];
                    pred[o] = next_node;
                }
        counter++;
    }
    for (int o = 0; o < k; o++)
        costs[o] = distance[desti[o]];
}
// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n])
{  
int visit[n];
for(int z=0;z<n;z++)
{    
    for(int o=0;o<n;o++)
        visit[o]=0;

DFS_1(z,n,connections,visit);
for(int o=0;o<n;o++)
    if(visit[o]==0)
        return 0;
}
return 1;
}

int q2(const airport_t *src, const airport_t *desti, int n, int k,
       const connection_t connections[n][n])
{
    int visit[n];
    for(int o=0;o<n;o++)
        visit[o]=0;
    int minimum_edge=INT_MAX;
    int counter=0;
    DFS_2(src->num_id,desti->num_id,n,connections,visit,&minimum_edge,&counter);
    if(counter<=k) return 1;
    return 0;
}

int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
     int i = 1;
    for (int o = 0; o < n; o++)
        if (o != src->num_id)
            if (route(src->num_id, o, n, connections))
                if (!route(o, src->num_id, n, connections))
                    i = 0;
    return i;
}

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    quick_sorting( n, airport_list, 0, n-1, predicate_func);
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    int maximum = 0;
    int a;
    for(int o=0; o<n; o++)
        for(int z = o+1; z<n; z++)
        {
            a = len(airports[o],airports[z]);
            if(maximum < a)
            {
                maximum = a;
                ans.first = airports[o].num_id;
                ans.second = airports[z].num_id;
            }
        }
    return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
    int cost[n];
    for (int o = 0; o < n; o++)
        cost[o] = entry_fee[o];
    int result = binarySearch(cost, 0, n - 1, amount, n);
    return result;
}

void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int t[200];
    for (int o = 0; o < 200; o++)
         t[o] = 0;
    for (int o = 0; o < n; o++)
    {
        shifttable(pat, t);
        if (horspool_algo(airports[o].airport_name, pat, t, n) != -1)
            contains[o] = 1;
    }
}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
int visit[n];
    int cycles[25][25];
    int cycle_no = 0;
    int minimum_index;
    int minimum = INT_MAX;
    int cost=0;
    int p,q;
    for(int i=0;i<n;i++)
        visit[i]=-1;
    for(int a=0;a<25;a++)
        for(int b=0;b<25;b++)
            cycles[a][b]=-1;
    finding_cycles(n,connections,visit,cycles,&cycle_no);
    int counter[cycle_no+1];
    for(int i=0;i<cycle_no+1;i++)
        counter[i]=0;
    int result[cycle_no+1][n];
    int x=0;
    int y=0;
    for(int a=0;a<cycle_no+1;a++)
        for(int b=0;b<n;b++)
            result[a][b]=-1;
    for(int a=0;a<25;a++)
    {
        y=0;
        int flag=0;
        for(int b=0;b<25;b++)
        {
            if(cycles[a][b]!=-1)
            {
                if(!flag)
                {
                    x++;
                    flag=1;
                }
                result[x][y]=cycles[a][b];
                counter[x]=counter[x]+1;
                y++;
            }
        }
    }
    for(int a=1;a<cycle_no+1;a++)
    {
        if(counter[a]==n-1)
        {
            cost=0;
            for(int b=0;b<n-1;b++)
            {
                if(result[a][b]!=-1 && result[a][b+1]!=-1)
                {
                    p=result[a][b];
                    q= result[a][b+1];
                    cost+= connections[p][q].distance;
                    // printf(" c : %d\t",cost);
                }
            }
            cost+=connections[q][result[a][0]].distance;
            if(cost<minimum)
            {
                minimum=cost;
                minimum_index=a;
            }
        }
    }
    if(minimum==INT_MAX)
        return -1;
    else
    {
        for(int i=0;i<n-1;i++)
            trip_order[i]=cycles[minimum_index][i];
        return minimum;
    }
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    krushkal_algorithm(n, connections);
    int result = 0;
    result = display(edges);
    return result;
}

void q10(int n, int k, const airport_t *src,const connection_t connections[n][n], const int destinations[k],int costs[k])
{
     Dijkstras(n, connections, src->num_id, destinations, costs, k);
}
// END
