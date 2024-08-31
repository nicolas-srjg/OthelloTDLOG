#pragma once

#include <vector>
#include <iostream>
#include "board.h"

using namespace std;

// Node of a tree containing an integer at each node
class IntTree {
    Board* data; /*!< Node information */

    std::vector<IntTree*> children; /*!< Sequence of children (empty if none) */
public:
    /**
     * Create a node with given information
     * @param d infomratin of the node
    */
    IntTree(Board* d) { data = d; };

    /** Destruct a node and all its descendents */
    ~IntTree() {
        for(int child=0; child<nbrChildren(); child++){
            delete children[child];
        }
        delete [] data;
    };

    /** Return information of this node */
    Board* getData() const { return data; };

    /** return the number of children */
    int nbrChildren() const { return children.size(); }

    /**
     * Set information of this node
     * @param d information of the node
    */
    void setData(Board* b) { data = b; };

    /**
     * Return the number of children of this node
     * @return the number of children of this node
    */
    int nbChildren() const { return children.size(); };

    /**
     * Return the child at pos, if any (left-most child at position 0)
     * @param pos position of the child (considering left-most child is at position 0)
     * @return child at position pos if pos is valid
     * @throws out_of_range if pos is not a valid position (between 0 and nbChildren-1)
    */
    IntTree* getChild(int pos);

    /**
     * Replace the exisiting child at pos (left-most child at position 0)
     * @param pos position of the child (considering left-most child is at position 0)
     * @param newChild tree replacing the existing one at position pos
     * @throws underflow_error if children is empty
    */
    void setChild(int pos, IntTree* newChild);

    /**
     * Add newChild as supplementary right-most child of this node
     * @param newChild tree added at the end of the vector children
    */
    void addAsLastChild(IntTree* newChild);

    /**
     * Remove right-most child of this node
     * @throws underflow_error if children is empty
    */
    void removeLastChild();

    /**
     * Return the depth of the deepest leef
     * @param depth used to keep an eye on the depth during recursion
     * @param maxDepth maximum depth updated during recursion
     * @return depth of the deepest leef
    */
    int maxDepth(int depth=0, int maxDepth=0) const;

    /**
     * Return the depth of the shallowest leef
     * @return depth of the shallowest leef
    */
    int minDepth() const;
};
