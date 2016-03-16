

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
#include"generate_graph.h"
#include"get_path.h"
#include"get_snr.h"
void readGraph(vector<pair<int,int > > &edges){
    edges.clear();
    ifstream fin("graph.txt");
    int u,v;
    while(fin>>u>>v){
        edges.push_back(make_pair(u,v));
    }
    fin.close();
}
void getGraph(int cl,int ro){

    srand((unsigned int)time(0));
    vector<pair<int,int > > edges;
    vector<int> keyNode(1,1);
    int cnt=1;
    ofstream fout("graph.txt");
    while(cnt){
        readGraph(edges);
        generate_graph(cl,ro,edges);
        if(getPath::getPath(edges,keyNode,cl,ro)){
            cnt--;
            for(int i=0;i<edges.size();i++){
                fout<<edges[i].first<<" "<<edges[i].second<<endl;
            }
        }
    }
    fout.close();

}

void initData(int cl,int ro,vector<double>& data,char* str[]){
    double stX=-6,stY=-5;
    double stepX=50/cl,stepY=25/ro;
//    char* stre[]={"x.txt","y.txt","z.txt"};
    char * stre[]={
        "/home/wcq/Documents/WYL/data/Krig/x_krig.txt",
        "/home/wcq/Documents/WYL/data/Krig/y_krig.txt",
        "/home/wcq/Documents/WYL/data/Krig/z_krig.txt"
//        "/home/wcq/Documents/WYL/data/IDW/x_IDW.txt",
//        "/home/wcq/Documents/WYL/data/IDW/y_IDW.txt",
//        "/home/wcq/Documents/WYL/data/IDW/z_IDW.txt"
    };
    snrMap snrmap(stre);
//    snrmap.read(str);
//    double x,y;
//    while(cin>>x>>y&&x!=0&&y!=0){
//
//        cout<<snrmap.getValue(x,y)<<endl;
//    }
    data.resize(cl*ro+1);
    for(int i=0;i<cl;i++){
        for(int j=0;j<ro;j++){
            data[offSet(i+1,j+1,cl,ro)]=snrmap.getValue(stX+stepX*i,stY+stepY*j);
            printf("%f\n",data[offSet(i+1,j+1,cl,ro)]);
        }
    }

}

double getKeyNode(vector<int> & keyNode,int cl,int ro,vector<double>& data){
    keyNode.clear();
    double minValue=1e9;
    int minID=-1;
    for(int i=0;i<cl;i++){
        for(int j=0;j<ro;j++){
            if(minValue> data[offSet(i+1,j+1,cl,ro)]){
                minValue=data[offSet(i+1,j+1,cl,ro)];
                minID=offSet(i+1,j+1,cl,ro);
            }
        }
    }

    for(int i=0;i<cl;i++){
        for(int j=0;j<ro;j++){
            if(data[offSet(i+1,j+1,cl,ro)]!=1e9){
                keyNode.push_back(offSet(i+1,j+1,cl,ro));
            }
        }
    }
    data[minID]=1e9;
    return minValue;
}
double f(double snr){
    double stdSnr[6]={39.18 , 41.97 , 44.90 , 48.96 , 51.22 , 57.05 };
//    double stdSnr[6]={39.18 , 41.97 , 44.90 , 48.96 , 51.22 , 57.05 };
//    double stdSnr[6]={49.18 , 51.97 , 54.90 , 58.69 , 61.22 , 67.05 };
    double fValue[6]={0.5 , 1.00 , 1.5 , 2.25 , 3.00 , 4.5};
    for(int i=0;i<5;i++)
        if(snr*2<=stdSnr[i]+stdSnr[i+1])return fValue[i];
    return fValue[5];
}
double updateAns(double snr,int k,int sizeKey,double deltaL,int length,double eta){
    double B = 20;//MHz
    double v = 1;//m/s
    double ans1=k*deltaL/v;
    double ans2=length*deltaL*eta/(sizeKey*v*B*f(snr));
    return ans1+ans2*16.5837;


}

int main(int argv,char* argc[]){
    int flag;
    int cl,ro;
    cout<<"dsf"<<endl;
//    scanf("%d%d%d",&cl,&ro,&flag);
    cl=12,ro=6,flag=1;
    ofstream foutPath("path.txt");
    ofstream foutKeyNode("keyNode.txt");
    if(!flag)getGraph(cl,ro);
    else{
        vector<pair<int,int > > edges;
        vector<int> keyNode(1,1);
        readGraph(edges);
        vector<double> data;
        initData(cl,ro,data,argc+3);
        double minAns=1e9;
        while(true){

            double minValue=getKeyNode(keyNode,cl,ro,data);
            if(keyNode.size()==63){

                getPath::getPath(edges,keyNode,cl,ro);
                cout<<getPath::ans<<endl;
//                double ans=updateAns(minValue,getPath::ans,keyNode.size(),50/cl,cl*ro,atoi(argc[1]));
//                double ans=updateAns(minValue,getPath::ans,keyNode.size(),50/cl,cl*ro,20);
//                fout<<ans<<" "<<getPath::ans<<" "<<minValue<<" "<<keyNode.size()<<" "<<f(minValue)<<endl;
                printf("%.4f\n",minValue);
//                minAns=ans;
                getPath::printANS();
                int x,y;
                for(int i=0;i<cl*ro;i++){
                    foutPath<<getPath::finalAns[i]<<endl;
                }
                for(int i=0;i<keyNode.size();i++){
                    foutKeyNode<<keyNode[i]<<endl;
                }
            }
            if(minValue>=52)break;
        }
    }
    foutPath.close();
    foutKeyNode.close();
}

