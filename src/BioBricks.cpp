//============================================================================
// Name        : LegoBio.cpp
// Author      : Fritz Sedlazeck
// Version     :
// Copyright   : MIT
// Description : Simulator to simulate population structure and admixture genome
//============================================================================

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

#include "structs.h"
#include "parental_genomes.h"
#include "admixture_genome.h"

int main(int argc, char **argv) {
	if (argc == 11) {
		srand(time(NULL)); //init rand();
		std::string output = string(argv[10]);
		int num_parents=atoi(argv[8]);
		float snp_rate=atof(argv[9]);
		//read in Fasta
		std::vector<chromosome_str> p1;
		std::vector<chromosome_str> p2;
		parse_parental_genomes(string(argv[1]), atoi(argv[2]), atof(argv[3]), p1, p2,output);
		std::string out = output;
		out += "_p1";
		print_parental(p1,num_parents,snp_rate, out);
		out = output;
		out += "_p2";
		print_parental(p2,num_parents,snp_rate, out);
		//Build building blocks and report their locations and ancestry
		float parental_propability = atof(argv[6]);

		for (int round = 0; round < atoi(argv[7]); round++) {
			std::cout << "Generating the admixture genomes: " << round << " out ot " << atoi(argv[7]) << std::endl;
			std::vector<chromosome_str> offspring;
			std::vector<regions_str> regions = generate_admixture(offspring, p1, p2, atoi(argv[4]), atoi(argv[5]), parental_propability,snp_rate);

			//back cross (report the parent in the same fasta file
			// report the regions of blocks etc.
			std::stringstream ss;
			ss << output;
			ss << "_child_";
			ss << round;
			ss << "_";
			if (rand() % 100 < parental_propability) {
				report_admixture(offspring, regions, p1, ss.str());
			} else {
				report_admixture(offspring, regions, p2, ss.str());
			}
		}
	} else {
		cout << "1: Fasta file" << endl;
		cout << "2: Minimum Chr length " << endl;
		cout << "3: SNP mutation between the parental populations (0-1)" << endl;
		cout << "4: min block size" << endl;
		cout << "5: max block size" << endl;
		cout << "6: Probability of p1 for admixture region (0-1): 50 balanced" << endl;
		cout << "7: Number of offspring genomes" << endl;
		cout << "8: Number of parental genomes (per population)"<<endl;
		cout << "9: SNP rate within the population (0-1"<<endl;
		cout << "10: Output prefix" << endl;
	}

	return 0;
}
