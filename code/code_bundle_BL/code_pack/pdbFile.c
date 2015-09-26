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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pdbFile.h"

int findNumberOfAtomsPdbFile(FILE *pdbInput)
{
	char line[10000];
	int posn;
	int nAtoms = 0;
	
	printf("-> finding number of atoms in pdb file\n");
	while (fgets(line, 10000, pdbInput) != NULL)
	{
		posn = strncmp(line, "ATOM", 4);
		if (posn == 0) {
			nAtoms++;
			//printf("line %s", line);
			//printf("posn %d nAtoms %d\n", posn, nAtoms);
		} 
	}
	
	printf("<- finding number of atoms in pdb file\n");
	
	return nAtoms;
}

void readPdbFile(pdbFile *macromolecule, FILE *pdbInput)
{
	char line[10000];
	int i = 0;
	int posn;
	char resID[5], x[8], y[8], z[8], O[5], beta[5];
	
	printf("-> reading macromolecule pdb\n");
	
	//Note: Reading information from lines that start with ATOM alone (macromolecule)
	while (fgets(line, 10000, pdbInput) != NULL)
	{
		posn = strncmp(line, "ATOM", 4);
		if (posn == 0) {
			strncpy(macromolecule->atom[i].name, line+13, 3);
			macromolecule->atom[i].name[3] = '\0';
			strncpy(macromolecule->atom[i].resName, line+17, 3);
			macromolecule->atom[i].resName[3] = '\0';  // was not commented out before
			strncpy(resID, line+22, 4);
			resID[4] = '\0';
			macromolecule->atom[i].resID = atoi(resID);
			resID[4] = '\0';
			macromolecule->atom[i].resID = atoi(resID);

			///  Newly-introduced (dc)
			strncpy(macromolecule->atom[i].chain, line+21, 1);
			macromolecule->atom[i].chain[1] = '\0';

			strncpy(x, line+30, 8);  // line was originally:   strncpy(x, line+31, 7);  ########################################################
			x[7] = '\0';
			macromolecule->atom[i].x = atof(x);
			strncpy(y, line+38, 8);  // line was originally:   strncpy(y, line+39, 7);  ########################################################
			y[7] = '\0';
			macromolecule->atom[i].y = atof(y);
			strncpy(z, line+46, 8);  //  line was originally:   strncpy(z, line+47, 7);  #######################################################
			z[7] = '\0';
			macromolecule->atom[i].z = atof(z);
			strncpy(O, line+56, 4);
			O[4] = '\0';
			macromolecule->atom[i].occupancy = atof(O);
			strncpy(beta, line+62, 4);
			beta[4] = '\0';
			macromolecule->atom[i].beta = atof(beta);
			strncpy(macromolecule->atom[i].element, line+77, 2);
			macromolecule->atom[i].element[2] = '\0';
			//printf("line %s%s %s %d %f %f %f %f %f %s   \n  chain: |%s| \n\n", line, macromolecule->atom[i].name, macromolecule->atom[i].resName, macromolecule->atom[i].resID, macromolecule->atom[i].x, macromolecule->atom[i].y, macromolecule->atom[i].z,  macromolecule->atom[i].occupancy,  macromolecule->atom[i].beta, macromolecule->atom[i].element, macromolecule->atom[i].chain);
			i++;
		}
		//printf("i %d\n", i);
	}
	
	printf("<- reading macromolecule pdb\n");
	
	return;
}

