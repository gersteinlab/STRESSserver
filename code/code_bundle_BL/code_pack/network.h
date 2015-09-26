/*
 * University of Illinois Open Source License
 * Copyright 2009, 2011, 2012 Luthey-Schulten Group,
 * All rights reserved.
 *
 * Developed by: Luthey-Schulten Group
 *                           University of Illinois at Urbana-Champaign
 *                           http://www.scs.uiuc.edu/~schulten
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the Software), to deal with
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to
 * do so, subject to the following conditions:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimers.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimers in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the names of the Luthey-Schulten Group, University of Illinois at
 * Urbana-Champaign, nor the names of its contributors may be used to endorse or
 * promote products derived from this Software without specific prior written
 * permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS WITH THE SOFTWARE.
 *
 * Author(s): Anurag Sethi, John Eargle
 * Modifications by: Shantao Li, Declan Clarke (lab of Mark Gerstein,
 * Yale University, 2015)
 */


#ifndef _network_h
#define _network_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pdbFile.h"

/**
 * This is a structure that indicates that there is an edge between res1 and 
 * res2. The edge connectivity of this edge is stored in the variable edgeConn.
 */
typedef struct {
  int res1, res2;
  //float edgeConn;
} EdgeStr;

typedef EdgeStr *edgePtr;

/**
 * Contains all graph information needed for calculation of pairwise path,
 * betweenness, community structure, and flow.
 */
typedef struct {
  int nres;          /**< Number of nodes or residues */
  int nedges;        /**< Number of edges */
  int **dis;         /**< Matrix of edge weights */
  int **shortDis;    /**< Matrix of shortest path distances */
  edgePtr *edge;     /**< Structures having information edges including its connectivity */
  float *LC;		 /**< Local clustering quantity */
} Graph;

void constructNetwork(Graph *network, pdbFile *macromolecule);
/**
 * Constructs the network given the macromolecule
 * returns all edges within network
 */

void floydWarshall(Graph *network, int *residues, int residueCount);

/**
 * Finds the shortest path between the source and target residues.
 * The network is input to this function.
 * @param network graph for shortest path calculation
 * @param residue is array of residues for which the shortest path calculation is done
 * @param residueCount is number of elementsi n residue
 */

void calculateLC(Graph *network, int *residue, int residueCount);

/**
 * Calculates LC or Local Clustering defined in Mitternacht and Berezovsky, Prot Engg, Des & Sel, pp 1-5, 2010
 * @param network graph for shortest path calculation
 * @param residue is array of residues for which the LC calculation is done
 * @param residueCount is number of elementsi n residue
 */
 
#endif