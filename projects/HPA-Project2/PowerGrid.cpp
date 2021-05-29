#include<stdio.h>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<omp.h>
#include<set>
#include <numeric>
using namespace std;
set<int> adj[128];
int result[128];
int number_of_nodes,number_of_edges;
int min_nodes;
 
void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
    cout<< endl;
}

bool cover(int cities[]){
    set<int> check;
    for (int i=0;i<number_of_nodes;i++){
            if(cities[i]){
                check.insert(i);
                check.insert(adj[i].begin(),adj[i].end());
            }
        }
    if(check.size()==number_of_nodes) return true;
    else return false;
}

void addMoreCityAndCheck(int cities[],int lastAdded){
    for (int i=1;i<number_of_nodes-lastAdded;i++){
        int new_cities[number_of_nodes] ={};
        copy(cities,cities+number_of_nodes,new_cities);
        new_cities[lastAdded+i] = 1;

        if(cover(new_cities)){
            int npo = accumulate(new_cities, new_cities+number_of_nodes, 0);
            if(min_nodes >= npo){
                min_nodes  = npo;
                copy(new_cities,new_cities+number_of_nodes,result);
                //printArray(result,number_of_nodes);
                return;

            }else{
                return;
            }

        }else{
            if (number_of_nodes-1!=lastAdded+i){
                addMoreCityAndCheck(new_cities,lastAdded+i);
            }else{
                return;
            }

        }
    }

}
int main(int argc,char *argv[]){
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    string n,e,na,nb;
    int i = 0;
    if(infile.is_open()){
        getline(infile,n);
        getline(infile,e);   
        while(getline(infile,na,' ') && getline(infile,nb)){
            adj[stoi(na)].insert(stoi(nb));
            adj[stoi(nb)].insert(stoi(na));
        }
        infile.close();
    }
    number_of_nodes = stoi(n);
    min_nodes = number_of_nodes;

    
    for (int i=0;i<number_of_nodes;i++){
        int cities[number_of_nodes] ={};
        cities[i]=1;
        if(cover(cities)){
            int npo = accumulate(cities, cities+number_of_nodes, 0);
            if(min_nodes >= npo){
                min_nodes  = npo;
                copy(cities,cities+number_of_nodes,result);
            }else break;
        }
        else{
            addMoreCityAndCheck(cities,i);
        }
    }

    if (outfile.is_open()){
        string s ="";
        for (int i = 0; i < number_of_nodes; i++)
            s = s + to_string(result[i]);
        outfile<<s;
    }
    outfile.close();
    return 0;
}