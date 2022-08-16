#include<bits/stdc++.h>
using namespace std;


#define MAX 110005
typedef  pair<long long int,long long int>pa;


#define pb push_back

long long int INF=3*1e18;

vector<pa>adj[MAX];   // Graph
vector<pa>adjr[MAX];  // Reversed Graph
long long  int v_for[MAX];  //virtual function for forward/main Graph
long long int v_back[MAX];  //virtual function for Backward Graph
long long int src,dest,n,m;
pa location[MAX];     //coordinates of each node

long long int f_dist[MAX];  //distance array
bool f_vis[MAX];            //visited array
//For faster input and output
void fastio()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}


//cmputing virtual function for each node
void computing_virtual_function()
{
    for(int i=1;i<=n;i++)
    {
    
           unsigned long long cc=(((location[dest].first-location[i].first))*((location[dest].first-location[i].first)))+
                 (((location[dest].second-location[i].second))*((location[dest].second-location[i].second)));
           v_for[i]=sqrt(cc);
       
    }
}




//Astar for faster output
long long int Astar()
{
    computing_virtual_function();
    priority_queue<pa,vector<pa>,greater<pa>>f_pq; //priority queue for forward/original graph
    
    for(int i=1;i<=n;i++)
    {
        f_dist[i]=INF;
        f_vis[i]=false;
    }
  
    long long int estimate=INF;
    f_pq.push({0,src});
    f_dist[src]=0;
    f_vis[src]=true;
    
    // A star - dijkstra with virtual function 
    while(!f_pq.empty())
    {
        
            long long int wt=f_pq.top().first;
            long long int v=f_pq.top().second;
            f_vis[v]=true;
            f_pq.pop();
          
            if(f_vis[dest])
            {
                 return f_dist[dest]+v_for[src];
            }
            
          
                for (auto jj:adj[v])
                {
                    long long int u=jj.second;
                    long long int edge_wt=jj.first+v_for[u]-v_for[v];
                    
                    if(!f_vis[u] && f_dist[v]+edge_wt<f_dist[u])
                    {
                       
                        f_dist[u]=f_dist[v]+edge_wt;
                        f_pq.push({f_dist[v]+edge_wt,u});
                    }
                }

    }
  
     return -1;  

}

int main()
{
    fastio();
    long long int x,y,wt;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
         cin>>x>>y;
         location[i]={x,y};
         
    }
    for(int i=0;i<m;i++)
    {
        cin>>x>>y>>wt;
        adj[x].pb({wt,y});    //adding edge to the graph
        adjr[y].pb({wt,x});  //adding edge to the reversed Graph
    }
    
    long long int num_of_queries;
    cin>>num_of_queries;
    while(num_of_queries--)
    {
       
        cin>>src>>dest;
        if(src==dest)
        {
            cout<<0<<"\n";
            continue;
        }
        long long int ans=Astar();

            cout<<ans<<"\n";
    }
   
}
