#ifndef GENERATE_GRAPH_H
#define GENERATE_GRAPH_H
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
void addEdge(int u,int v,int flag,vector<pair<int,int> >& edges,set<pair<int,int> > & st){

    if(rand()%3||flag){
        if(st.find(make_pair(u,v))!=st.end())return ;
        st.insert(make_pair(u,v));
        edges.push_back(make_pair(u,v));
    }
}
void offSet(int & pos,int x,int y,int n,int m){
    x--,y--;
    pos=x*m+y+1;
}
int offSet(int x,int y,int n,int m){
    int ret;
    offSet(ret,x,y,n,m);
    return ret;
}
void antiOffSet(int pos,int & x,int & y,int n,int m){
    pos--;
    y=pos%m;
    x=pos/m;
    x++,y++;
}
void generate_graph(int n,int m,vector<pair<int,int> > & ret){
    set<pair<int,int> > st;
    ret.clear();
    for(int i=1;i<n;i++){
        addEdge(offSet(i,1,n,m),offSet(i+1,1,n,m),1,ret,st);
        addEdge(offSet(i,m,n,m),offSet(i+1,m,n,m),1,ret,st);
    }
    for(int i=1;i<m;i++){
        addEdge(offSet(1,i,n,m),offSet(1,i+1,n,m),1,ret,st);
        addEdge(offSet(n,i,n,m),offSet(n,i+1,n,m),1,ret,st);
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            addEdge(offSet(i,j,n,m),offSet(i,j+1,n,m),0,ret,st);
            addEdge(offSet(i,j,n,m),offSet(i+1,j,n,m),0,ret,st);
        }
    }

}



#endif // GENERATE_GRAPH_H
