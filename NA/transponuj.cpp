#include <bits/stdc++.h>

int main() {
    int matrica[3][3] = {{1, 2, 3}, 
                         {4, 5, 6}, 
                         {7, 8, 9}};
    for(int i=0; i<3; i++){
        for(int j=i; j<3; j++) {
            if(i!=j) {
                int temp;
                temp = matrica[i][j];
                matrica[i][j] = matrica[j][i];
                matrica[j][i] = temp;
            }
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) {
            std::cout<<matrica[i][j]<<"  ";
        }
        std::cout<<"\n";
    }
    return 0;
}

