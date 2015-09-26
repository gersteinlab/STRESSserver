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


#ifndef _bindingSiteMeasures_h
#define _bindingSiteMeasures_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pdbFile.h"
#include "network.h"
#include "surfaceProbe.h"
#include "modes.h"

void calculateBindingLeverage(pdbFile *macromolecule, modePtr normalModes, float **fnm_t10_data_mode1, float **fnm_t10_data_mode2, float **fnm_t10_data_mode3, float **fnm_t10_data_mode4, float **fnm_t10_data_mode5, float **fnm_t10_data_mode6, float **fnm_t10_data_mode7, float **fnm_t10_data_mode8, float **fnm_t10_data_mode9, float **fnm_t10_data_mode10, int numModes, bindingSite *mergedSites, int numMergedSites, FILE *output, pdbFile *macromolecule_w_heavy);


void map_resid_from_CA_to_heavy(int res_ID, pdbFile *macromolecule_w_heavy); // was not in orig

//float calculateBindingLeverageSite(bindingSite *site, int i, pdbFile *macromolecule, float *R, pdbFile *macromolecule_w_heavy);

float calculateBindingLeverageSite(bindingSite *site, int siteNum, pdbFile *macromolecule, float *R);

float calculateBindingLeverageSite__AddingModes(bindingSite *site, int siteNum, pdbFile *macromolecule, float **fnm_t10_data_modeX);

void calculateLCmergedSite(pdbFile *macromolecule, bindingSite *mergedSites, int numMergedSites, Graph *network, FILE *output);

float calculateLCsite(bindingSite *mergedSites, int i, Graph *network);

void sortArray(float *A, int numMergedSites, int *order);

#endif