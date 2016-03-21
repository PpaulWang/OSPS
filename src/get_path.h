#ifndef GET_PATH_H
#define GET_PATH_H

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;
namespace getPath{

const int maxN=1000;
const int maxM=1000;
const int INF=100000000;
//array to mark that has the point been visited
bool vi[maxN];
bool tvi[maxN];
bool isKeyNode[maxN];
//data structure to store the point

int Prev[maxM],info[maxN],to[maxM],length[maxM];
int nedge;

int flag;
int dis[maxN];
int stk[maxN];
int startdis;
int keyNum;
int ans;
int finalAns[maxN];
int n,cl,ro; 				//row
int countAns;				//count ans



void insert(int u,int v,int len){
    nedge++;

    length[nedge]=len;
    to[nedge]=v;
    Prev[nedge]=info[u];
    info[u]=nedge;

}

//update the optimization answer


void updateAns(){

    int st=0;
    int ret=0;
    int startlen=0,start=0;
    for(int i=0;i<n;i++){
        if(start==0)startlen=dis[stk[i]];
        if(isKeyNode[stk[i]]==true){
            ret=max(ret,dis[stk[i]]-dis[stk[st]]);
            st=i;
            start=1;
        }
    }
    /*
    for(int i=0;i<n;i++){

        printf("%d %d \n",stk[i],dis[stk[i]]);
    }puts("");
    */
    if(max(ret,dis[stk[n-1]]-dis[stk[st]]+startlen)<ans){
        ans=max(ret,startdis-dis[stk[st]]+startlen);
        for(int i=0;i<n;i++){
            finalAns[i]=stk[i];
        }
    }
}

// dye the region to count the number of region
void dye(int u){

    for(int i=info[u];i;i=Prev[i]){
        int v=to[i];
        if(tvi[v]==true)continue;
        // mark that this postion has been visit
        tvi[v]=true;

        dye(v); 	//Recursion
    }
}

//count the number of regions
int countRegion(){
    int ret=0;

    //copy the state of all unit
    memcpy(tvi,vi,sizeof(vi));

    //for every unit observe that has this unit been marked or not
    for(int i=1;i<=n;i++){

        //if this unit hasn't been marked ,then mark this unit and it's region
        if(!tvi[i]){
            tvi[i]=true;
            dye(i);		//recursion
            ++ret; 		//update the number of regions
        }
    }
    //memcpy(vi,tvi,sizeof(vi));
    return ret;
}

//enumerate the path
void dfs(int u,int deep,int nowAns){
    //printf("%d\n",u);
    // if get the ans
    if(deep==n){
        bool flag=false;
        for(int i=info[u];i;i=Prev[i]){
            int v=to[i];
            //printf("%d\n",v);
            if(v==stk[0]){
                flag=true;
                startdis=dis[u]+length[i];
            }

        }

        if(flag==false)return;
        updateAns();
        countAns++; //update the number of path
    }
    if(((flag&(1)))&&nowAns>=ans)return;
    if((flag&(1<<1))&&countRegion()>1)return ;
    if(isKeyNode[u])nowAns=0;
    for(int i=info[u];i;i=Prev[i]){

        int v=to[i];

        //printf("%d\n",v);
        if(vi[v]==true)continue;
        vi[v]=true;
        dis[v]=dis[u]+length[i];
        stk[deep]=v;					// store the answer
        dfs(v,deep+1,nowAns+length[i]);					// Recursion
        vi[v]=false;					//backtracking
    }
}

void printANS(){
    int x,y;
//    printf("the optimization answer of this input is %d,\nand the path is :\n\n",ans);
    for(int i=0;i<n;i++){
        if(i)printf(" -> ");
        antiOffSet(finalAns[i],x,y,cl,ro);
        printf("(%2d,%2d) ",x,y);
    }
    puts("");
}
// work function
void work(int st){
    // initial the parameter
    countAns=0;

    memset(vi,0,sizeof(vi));

    vi[st]=true;			//mark
    stk[0]=st;	//store the answer
    dis[st]=0;	//
    dfs(st,1,0);				//recursion




}



int getPath(vector<pair<int,int > > & edges,vector<int> & keyNode,int _cl,int _ro){

    ans=INF;
    memset(isKeyNode,0,sizeof(isKeyNode));
    nedge=0;
    memset(info,0,sizeof(info));
    cl=_cl,ro=_ro;
    n=cl*ro;

    for(int i=0;i<edges.size();i++){

        insert(edges[i].first,edges[i].second,1);
        insert(edges[i].second,edges[i].first,1);
    }
    for(int i=0;i<keyNode.size();i++){
        isKeyNode[keyNode[i]]=true;
    }
    puts("\ncalculating...\n");
    //work
    work(keyNode[0]);
    return ans!=INF;
}

}
#endif // GET_PATH_H
