#include<bits/stdc++.h>
using namespace std;


#define MAX 110005
typedef  pair<long long int,long long int>pa;


#define pb push_back

long long int INF=1e17;

vector<pa>adj[MAX];   // Graph
vector<pa>adjr[MAX];  // Reversed Graph
long long  int v_for[MAX];  //virtual function for forward/main Graph
long long int v_back[MAX];  //virtual function for Backward Graph
long long int src,dest,n,m;
pa location[MAX];  //coordinates of each node

set<long long int>worksetD; //consists of nodes to be re-initialised

long long int f_dist[MAX]; //distance array from source for forward iterations
long long int r_dist[MAX]; //distance array from dest for backward iterations
bool f_vis[MAX];   //visited array for forward steps 
bool r_vis[MAX];   //visited array for backward steps

//For faster input and output
void fastio()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

//computing virtual function for forward iteration
void computing_forward_virtual_function()
{
    for(int i=1;i<=n;i++)
    {
    
        v_for[i]=(((location[dest].first-location[i].first))*((location[dest].first-location[i].first)))+
                 (((location[dest].second-location[i].second))*((location[dest].second-location[i].second)));
        v_for[i]=sqrt(v_for[i]);
    }
}

//computing backward virtual function for backward iterations
void computing_backward_virtual_function()
{
    for(int i=1;i<=n;i++)
    {
       
        v_back[i]=(((location[src].first-location[i].first))*((location[src].first-location[i].first)))+
           (((location[src].second-location[i].second))*((location[src].second-location[i].second)));
        v_back[i]=sqrt(v_back[i]);
    }
}
//final virtual function
void computing_average_virtual_function()
{
    for(int i=1;i<=n;i++)
    {
        long long int x=v_back[i]-v_for[i];
        x=(x)>>1;
        v_for[i]=-x;
        v_back[i]=x;
    }
}
//bidirectional Astar for faster output
long long int Astar()
{
    computing_forward_virtual_function();
    computing_backward_virtual_function();
    computing_average_virtual_function();
    priority_queue<pa,vector<pa>,greater<pa>>f_pq; //priority queue for forward/original graph
    priority_queue<pa,vector<pa>,greater<pa>>r_pq; //priority queue for reversed graph

   //updating values changed during last query
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
     
    // A star with alternate forward and backward step 
    while(!f_pq.empty() || !r_pq.empty())
    { //forward_iteration
        if(!f_pq.empty())
        {
            long long int wt=f_pq.top().first;
            long long int v=f_pq.top().second;
            f_vis[v]=true;
            f_pq.pop();
          
            
            
          
                for (auto jj:adj[v])
                {
                    long long int u=jj.second;
                    long long int edge_wt=jj.first+v_for[u]-v_for[v];
                    
                    if(!f_vis[u] && f_dist[v]+edge_wt<f_dist[u])
                    {
                         worksetD.insert(u);
                        f_dist[u]=f_dist[v]+edge_wt;
                        f_pq.push({f_dist[v]+edge_wt,u});
                    }
                }
            if(r_vis[v])
                break;
        }
        
        //backward_iteration
         if(!r_pq.empty())
        {
            long long int wt=r_pq.top().first;
            long long int v=r_pq.top().second;
            r_pq.pop();
            r_vis[v]=true;

                for (auto jj:adjr[v])
                {
                    long long int u=jj.second;
                    long long int edge_wt=jj.first+v_back[u]-v_back[v];
                   
                    if(!r_vis[u] && r_dist[v]+edge_wt<r_dist[u])
                    { 
                        worksetD.insert(u);
                        r_dist[u]=r_dist[v]+edge_wt;
                        r_pq.push({r_dist[v]+edge_wt,u});
                    }
                }
            if(f_vis[v])
               break;
     
        }
        
    }
  
    for(int i=1;i<=n;i++)
    {
        if(f_vis[i] && r_vis[i])
        estimate=min(estimate,f_dist[i]+r_dist[i]+v_for[src]-v_for[i]+v_back[dest]-v_back[i]);
        for(auto jj:adj[i])
        {
            if(f_vis[i] && r_vis[jj.second])
             estimate=min(f_dist[i]+r_dist[jj.second]+jj.first+v_for[src]-v_for[i]+v_back[dest]-v_back[jj.second],estimate);
        }
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
        cin>>x>>y;
        worksetD.insert(i);
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
        
        if(ans>=INF)
        {
            cout<<-1<<"\n";
        }
        else
            cout<<ans<<"\n";
    }
   
}
