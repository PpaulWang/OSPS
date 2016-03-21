#ifndef GET_SNR_H
#define GET_SNR_H
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<assert.h>
#include<iostream>
using namespace std;
const int N=222;
struct Point{
    double x,y,snr;
    Point(){}
    Point(double x,double y,double snr):x(x),y(y),snr(snr){}
};
struct Hash{
    double T[N*N];
    int tot;
    Hash(){}
    void clear(){
        tot=0;
    }
    void addData(double x){
        T[tot++]=x;
    }
    void initHash(){
        sort(T,T+tot);
        tot=unique(T,T+tot)-T;
    }
    int get(double x){
        return upper_bound(T,T+tot,x)-T-1;
    }
    double step(){
        return T[1]-T[0];
    }
};
struct snrMap{

    double snrValue[N][N];
    Hash xHash,yHash;
    Point data[N*N];
    int n;
    snrMap(){}
    snrMap(char* str[]){

        read(str);
        initData();
    }
    void read(char* str[]){
        ifstream finX(str[0]);
        ifstream finY(str[1]);
        ifstream finSnr(str[2]);
        n=0;
//        cout<<str[0]<<  "  "<<str[1]<<endl;
//        fin>>n;
        for(int i=0;finX>>data[i].x;n++,i++){

            finY>>data[i].y;
            finSnr>>data[i].snr;
//              cout<<data[i].x<<" ";
//              cout<<data[i].y<<" ";
//              cout<<data[i].snr<<endl;
        }
//        cout<<str[0]<<" "<<str[1]<<" "<<str[2]<<endl;
        finX.close();
        finY.close();
        finSnr.close();
    }
    void initData(){
        xHash.clear(),yHash.clear();


        for(int i=0;i<n;i++){
            xHash.addData(data[i].x);
            yHash.addData(data[i].y);
        }
        xHash.initHash();
        yHash.initHash();
        for(int i=0;i<n;i++){
            int x=xHash.get(data[i].x);
            int y=yHash.get(data[i].y);
            snrValue[x][y]=data[i].snr;
        }
    }
    double getValue(double x,double y){
        int sx,sy;
        x+=xHash.step()/2;
        y+=yHash.step()/2;
        sx=xHash.get(x);
        sy=yHash.get(y);
        return snrValue[sx][sy];
    }
};



#endif // GET_SNR_H
