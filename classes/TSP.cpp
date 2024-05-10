#include "TSP.h"
#include <utility>

void tspRec(std::vector<std::vector<double>> dists, unsigned int n, int curI,int curDist, std::vector<double> curPath, double &minDist, std::vector<double> &path) {
    if(curI == n) {
        curDist += dists[curPath[n-1]][curPath[0]];
        if(curDist < minDist) {
            minDist = curDist;
            for(int i = 0;i < n;i++) {
                path[i] = curPath[i];
            }
            return;
        }
    } else {
        for(int i = 1; i < n; i++) {
            if(curDist + dists[curPath[curI - 1 ]][curPath[i]] < minDist) {
                bool isNewNode = true;
                for(int j = 1; j < curI; j++) {
                    if(curPath[j] == i) {
                        isNewNode = false;
                        break;
                    }
                }
                if(isNewNode) {
                    curPath[curI] = i;
                    tspRec(dists,n,curI + 1,curDist + dists[curPath[curI - 1]][curPath[curI]],curPath,minDist,path);
                }
            }
        }
    }
}

unsigned int tspBT(std::vector<std::vector<double>> dists,unsigned int n, std::vector<double> &path) {
    std::vector<double> curPath(n+1,0);
    double minDist = std::numeric_limits<double>::max();
    curPath[0] = 0;
    tspRec(std::move(dists),n,1,0,curPath,minDist,path);
    return minDist;
}
