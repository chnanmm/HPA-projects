//merge sort
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<omp.h>
using namespace std;
vector<pair<string,double>> vect;

void merge(vector<pair<string,double>> vect, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;   
    pair<string,double> L[n1], R[n2];

    #pragma omp parallel for
    for (int i = 0; i < n1; i++)
        L[i] = vect[l + i];

    #pragma omp parallel for
    for (int j = 0; j < n2; j++)
        R[j] = vect[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i].second <= R[j].second) {
            vect[k] = L[i];
            i++;
        }
        else {
            vect[k] = R[j];
            j++;
        }
        k++;
    }

    if (i < n1){
        do{
            vect[k] = L[i];
            i++;
            k++;
        }while(i < n1);
    }

    if (j < n2){
        do{
            vect[k] = R[j];
            j++;
            k++;
        }while(j < n2);
    }

}
 
void mergeSort(vector<pair<string,double>> vect,int l,int r){
    if(l>=r){
        return;
    }
    int m =l+ (r-l)/2;
    #pragma omp task firstprivate (vect,l,m)
    mergeSort(vect,l,m);
    #pragma omp task firstprivate (vect,r,m)
    mergeSort(vect,m+1,r);
    #pragma omp taskwait
    merge(vect,l,m,r);
}

int main(int argc,char *argv[]){
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    string name;
    string score;
    int i = 0;
    if(infile.is_open()){
        while(getline(infile,name,' ') && getline(infile,score)){
            vect.push_back(make_pair(name,stod(score)));
            i++;
        }
        infile.close();
    }
    #pragma omp parallel
    {
        #pragma omp single
        mergeSort(vect, 0, i - 1);
    }

    if (outfile.is_open()){
        for(auto i:vect){
           outfile << i.first << " " << to_string(i.second) << endl;
      }
    }
    outfile.close();
    return 0;
}