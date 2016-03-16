#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<iostream>
#include<assert.h>
#include<fstream>
#include<map>
using namespace std;
const int N=3000;
const float inf=1e9;
int n;
const int L=100;
bool canChose[N];
bool tempCanChose[N];
bool ok[N][N];
float dis[N][N];
struct Picture{
	int topone;
	float top;
	Picture(){}
	Picture(int topone,float top):topone(topone),top(top){}

}Pic[N];
void SET(int l,int r){
    l=max(0,l);
    r=min(N-1,r);
    memset(tempCanChose+l,1,sizeof(bool)*(r-l+1));
}
int tp,fp,tn,fn;
pair<float,float> get_zql(float dist){
	for(int i=0;i<n;i++){
		int j=Pic[i].topone;
		if(ok[i][j]){
			if(dis[i][j]<dist)tp++;
			else fn++;
		}
		else{
			if(dis[i][j]<dist)fp++;
			else tn++;
		}
	}
	if(tp+fp==0)tp=1,fp=0;
	return make_pair(1.0*tp/(tp+fp),1.0*tp/(tp+fn));
}
void prepare(){
	string layer_name;
	ifstream fin_lyaer_name("layer_name.txt");
	fin_lyaer_name>>layer_name;
	fin_lyaer_name.close();
	string input_file_name=layer_name+"_dis.out";
	cout<<input_file_name<<endl;
	ifstream fin2(input_file_name.c_str());
	fin2>>n;
	fin2>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			fin2>>dis[i][j];

		}
	}
	fin2.close();
	cout<<n<<endl;
	char c;
	ifstream fin("/home/wcq/Documents/data/CityCentreTextFormat.txt");
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
//            assert(fin>>c);
            fin>>c;
//            cout<<c<<endl;
			while(c!='0'&&c!='1')fin>>c;
//			cout<<c<<endl;
			ok[i][j]=(c=='1');
		}
	fin.close();
	memset(canChose,1,sizeof(canChose));

	for(int i=0;i<=n;i++){dis[i][n]=inf,Pic[i]=Picture(n,dis[i][n]);}
	for(int i=0;i<n;i++){
        memset(tempCanChose,0,sizeof(tempCanChose));
		for(int j=0;j+40<i;j++){
            if(canChose[j])
			if(dis[i][j]<Pic[i].top){
				Pic[i]=Picture(j,dis[i][j]);
				SET(j-L,j+L);
			}
		}
		memcpy(canChose,tempCanChose,sizeof(canChose));
	}
}
int main(){
	float dist;
	prepare();
	string layer_name;
	ifstream fin_lyaer_name("layer_name.txt");
	fin_lyaer_name>>layer_name;
	fin_lyaer_name.close();
	string result_file1=layer_name+"_result11.out";
	string result_file2=layer_name+"_result22.out";
	ofstream fout1(result_file1.c_str());
	ofstream fout2(result_file2.c_str());
	double temp=0;
	for(float i=0;temp<0.85;i+=10){
		pair<float,float> tp=get_zql(i);
		temp=tp.second;

        fout1<<tp.first<<", ";
        fout2<<tp.second<<", ";
		printf("%f %f %f\n",i,tp.first,tp.second);
	}
	fout1.close();
	fout2.close();
	return 0;
}
