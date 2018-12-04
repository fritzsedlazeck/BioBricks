/*
 * admixture_genome.h
 *
 *  Created on: Nov 27, 2018
 *      Author: sedlazec
 */

#ifndef ADMIXTURE_GENOME_H_
#define ADMIXTURE_GENOME_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <map>
#include <math.h>

using namespace std;
#include "structs.h"

vector<regions_str> generate_admixture(std::vector<chromosome_str> &offspring1, std::vector<chromosome_str> p1, std::vector<chromosome_str> p2, int min_block, int max_block, float parental_propability,float mutation_rate);
void report_admixture(std::vector<chromosome_str> offspring1,vector<regions_str>  regions,std::vector<chromosome_str> p1, std::string output);
#endif /* ADMIXTURE_GENOME_H_ */
