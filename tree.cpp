#include <iostream>
#include "tree.h"
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

IntTree* IntTree::getChild(int pos){
    if(pos<0 || pos>=nbrChildren()) throw std::out_of_range("parameter pos is out of range");
    return children[pos];
}

void IntTree::setChild(int pos, IntTree* newChild){
    if(pos<0 || pos>=nbrChildren()) throw std::out_of_range("parameter pos is out of range");
    delete [] children[pos];
    children[pos] = newChild;
}

void IntTree::addAsLastChild(IntTree* newChild){
    children.push_back(newChild);
}

void IntTree::removeLastChild(){
    if(children.size()==0) throw underflow_error("trying to remove element from empty vector");
    delete [] children[ children.size() - 1 ]; // je ne sais pas si le pop delete le dernier element
    children.pop_back();
}

int IntTree::maxDepth(int depth, int maxDepth) const{
    if(children.size()==0){
        return depth;
    }

    int newDepth = depth + 1;

    for(int i=0; i<nbrChildren(); i++){
        int possibleMaxDepth = children[i]->maxDepth(newDepth, maxDepth);
        if(possibleMaxDepth>maxDepth) maxDepth = possibleMaxDepth;
    }
    return maxDepth;
}

int IntTree::minDepth() const{
    // on parcours l'arbre en largeur d'abord de maniere evidente

    if(children.size() == 0){
        return 0;
    }

    queue<IntTree*> treeQueue;
    queue<int> intQueue;

    for(int i = 0; i<children.size(); i++){
        treeQueue.push(children[i]);
        intQueue.push(1);
    }

    while(true){
        int nbrOfChildren = treeQueue.front()->nbChildren();
        int depth = intQueue.front();

        if(nbrOfChildren == 0) return depth;

        intQueue.pop();

        for(int i=0; i<nbrOfChildren; i++){
            treeQueue.push(treeQueue.front()->getChild(i));
            intQueue.push(depth+1);
        }
        treeQueue.pop();
    }
}
