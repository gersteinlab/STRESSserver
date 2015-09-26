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


#ifndef _pdb_h
#define _pdb_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	char name[4]; //name of atom
	char resName[4]; // residue name of atom
	int resID; //residue number of atom
	char chain[2]; //residue number of atom
	float x, y, z; //x,y, and z coordinates of atom
	float beta; //beta of atom
	float occupancy; //occupancy of atom
	char element[3]; //element of atom
} atomStr;


typedef struct 
{
   int nAtoms; //Number of atoms 
   atomStr *atom; //Information about each atom
} pdbFile;

//This function calculates the number of macromolecular atoms (not HETATM) in the pdb file
int findNumberOfAtomsPdbFile(FILE *pdbInput); 
//* param: pdbInput is the input pdb file for which the number of atoms are calculated.
//* returns value of number of atoms in the pdb file

//This function reads the pdb file and initializes the whole pdbInput data structure
void readPdbFile(pdbFile *macromolecule, FILE *pdbInput);
//* param: macromolecule is the data structure which contains the information in the pdb file
//* param: pdbInput is the input pdb file from which the information is read

#endif
