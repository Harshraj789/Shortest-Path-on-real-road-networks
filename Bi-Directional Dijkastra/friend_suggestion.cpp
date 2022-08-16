#include<bits/stdc++.h>
using namespace std;


#define MAX 1000005
typedef  pair<long long int,long long int> pa;


#define pb push_back
long long int INF=1e18;

vector<pa>adj[MAX];   // Graph
vector<pa>adjr[MAX];  // Reversed Graph
long long int src,dest,n,m;

set<long long int>worksetD;  //to store those value which are updated during query

long long int f_dist[MAX];  // distance measured from src in forward dijkstra
long long int r_dist[MAX]; // distance measured from dest in backward dijkstra
bool f_vis[MAX];  // visited array for forward dijkstra
bool r_vis[MAX];  // visited array for backward dijkstra

//For faster input and output
void fastio()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

//bidirectional dijkstra for faster output
long long int bidijkstra()
{
    priority_queue<pa,vector<pa>,greater<pa>>f_pq; //priority queue for forward/original graph
    priority_queue<pa,vector<pa>,greater<pa>>r_pq; //priority queue for reversed graph
    
    //updating all the values changed during previous query
   for(auto k:worksetD)
    {
        f_dist[k]=INF;
        r_dist[k]=INF;
        f_vis[k]=false;
        r_vis[k]=false;
    }
    worksetD.clear();

    long long int estimate=INF;
    f_pq.push({0,src});
    r_pq.push({0,dest});
    f_dist[src]=0;
    f_vis[src]=true;
    r_vis[dest]=true;
    r_dist[dest]=0;
    worksetD.insert(src);
    worksetD.insert(dest);
    long long int minf=INF/10;
    long long int minr=INF/10;
    // bidijisktra with alternate forward and backward step 
    while(!f_pq.empty() || !r_pq.empty())
    {
    	//forward_iteration
        if(!f_pq.empty())
        {
            long long int wt=f_pq.top().first;
            long long int v=f_pq.top().second;
            f_vis[v]=true;
            f_pq.pop();
          
            minf=wt;
            
          
                for (auto jj:adj[v])
                {
                    long long int edge_wt=jj.first;
                    long long int u=jj.second;
                    if(!f_vis[u] && f_dist[v]+edge_wt<f_dist[u])
                    {
                        worksetD.insert(u);
                        f_dist[u]=f_dist[v]+edge_wt;
                        estimate=min(estimate,f_dist[v]+r_dist[u]+edge_wt);
                        f_pq.push({f_dist[u],u});
                    }
                }
           
            
        
        
        }
        //backward_iteration
        
         if(!r_pq.empty())
        {
            long long int wt=r_pq.top().first;
            long long int v=r_pq.top().second;
            r_pq.pop();
            r_vis[v]=true;
            minr=wt;             
            
                for (auto jj:adjr[v])
                {
                    long long int edge_wt=jj.first;
                    long long int u=jj.second;
                    
                    if(!r_vis[u] && r_dist[v]+edge_wt<r_dist[u])
                    {
                        worksetD.insert(u);
                        r_dist[u]=r_dist[v]+edge_wt;
                        estimate=min(estimate,r_dist[v]+f_dist[u]+edge_wt);
                        r_pq.push({r_dist[u],u});
                    }
                }
          
            
           
        }
       //stopping condition
        if(minf+minr>=estimate)
           break;
    }
    
   return estimate;

}

int main()
{
    fastio();
    long long int x,y,wt;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        worksetD.insert(i);
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
        long long int ans=bidijkstra();
        
        if(ans==INF)
        {
            cout<<-1<<"\n";
        }
        else
            cout<<ans<<"\n";
    }
   
}
