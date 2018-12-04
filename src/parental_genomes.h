/*
 * parental_genomes.h
 *
 *  Created on: Nov 27, 2018
 *      Author: sedlazec
 */

#ifndef PARENTAL_GENOMES_H_
#define PARENTAL_GENOMES_H_
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

void parse_parental_genomes(std::string file_name,int min_length,float mutation_rate, std::vector<chromosome_str> & p1, std::vector<chromosome_str> &p2,std::string output);

void print_parental(std::vector<chromosome_str> p1, int num, float mutation_rate, std::string output);

#endif /* PARENTAL_GENOMES_H_ */
