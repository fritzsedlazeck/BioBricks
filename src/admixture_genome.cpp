/*
 * admixture_genome.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: sedlazec
 */

#include "admixture_genome.h"

char mut_char2(char old) {
	std::string nucs = "ACGT";
	int index = rand() % 4;
	switch (old) {
	case 'A':
		while (index == 0) {
			index = rand() % 4;
		}
		return nucs[index];
		break;
	case 'C':
		while (index == 1) {
			index = rand() % 4;
		}
		return nucs[index];
		break;
	case 'G':
		while (index == 2) {
			index = rand() % 4;
		}
		return nucs[index];
		break;
	case 'T':
		while (index == 3) {
			index = rand() % 4;
		}
		return nucs[index];
		break;
	default:
		return 'N';
		break;
	}
	return 'N';
}

vector<int> generate_boarders(size_t size, int num_blocks) {
	int med_size = size/num_blocks; // (max_block + min_block) / 2;
	int min_block=med_size- (med_size*0.2);
	int net_len= (med_size*0.4);


	vector<int> blocks;
	int i = 0;
	while (i < size) {
		i += min_block + (rand() % net_len); //jump forward;
		blocks.push_back(min(i, (int) size)); // to avoid an overflow
	}
	return blocks;
}
vector<regions_str> generate_admixture(std::vector<chromosome_str> &offspring1, std::vector<chromosome_str> p1, std::vector<chromosome_str> p2, int min_block, int max_block, float parental_propability, float mutation_rate) {

	offspring1 = p1;
	//int net_len = max_block - min_block;

	vector<regions_str> regions;

	for (size_t i = 0; i < p1.size(); i++) {
		vector<int> boarders = generate_boarders(p1[i].sequence.size(), 200);
		int pos = 0;
		for (size_t j = 0; j < boarders.size(); j++) {
			regions_str tmp;
			tmp.chr = offspring1[i].name;
			tmp.start = pos;
			tmp.stop = boarders[j];
			float x = ((float) rand() / (float) (RAND_MAX));
			if (x < parental_propability) { //only if it is the other parent (p2)
				for (size_t t = tmp.start; t < tmp.stop && t < offspring1[i].sequence.size(); t++) {
					offspring1[i].sequence[t] = p2[i].sequence[t];
				}
				tmp.p1 = false;
			} else {
				tmp.p1 = true;
			}
			regions.push_back(tmp);

			pos = boarders[j];
		}

		/*	size_t pos = 0;
		 while (pos < p1[i].sequence.size()) {
		 int len = min_block + (rand() % net_len);
		 regions_str tmp;
		 tmp.chr = offspring1[i].name;
		 tmp.start = pos;
		 tmp.stop = pos + len;
		 float x = ((float) rand() / (float) (RAND_MAX));
		 if (x < parental_propability) { //only if it is the other parent (p2)
		 for (size_t t = 0; t < len && t + pos < offspring1[i].sequence.size(); t++) {
		 offspring1[i].sequence[t + pos] = p2[i].sequence[t + pos];
		 }
		 tmp.p1 = false;
		 } else {
		 tmp.p1 = true;
		 }
		 regions.push_back(tmp);
		 pos += len;
		 }*/

		pos = 0;
		while (pos < offspring1[i].sequence.size()) {
			float x = ((float) rand() / (float) (RAND_MAX));
			if (x < mutation_rate) {
				offspring1[i].sequence[pos] = mut_char2(toupper(offspring1[i].sequence[pos]));
			}
			pos++;
		}
	}

	return regions;

}

void report_admixture(std::vector<chromosome_str> offspring, vector<regions_str> regions, std::vector<chromosome_str> p1, std::string output) {
	//print the sequence;
	std::string out = output;
	out += "genome.fa";
	FILE *file2;
	file2 = fopen(out.c_str(), "w");
	for (size_t i = 0; i < offspring.size(); i++) {
		fprintf(file2, "%c", '>');
		fprintf(file2, "%s", offspring[i].name.c_str());
		fprintf(file2, "%s", "_of\n");
		for (size_t j = 0; j < offspring[i].sequence.size(); j++) {
			fprintf(file2, "%c", offspring[i].sequence[j]);
			//	if (j % 800 == 0 && j != 0) {
			//		fprintf(file2, "%c", '\n');
			//	}
		}
		fprintf(file2, "%c", '\n');
	}
//print parent;
	for (size_t i = 0; i < p1.size(); i++) {
		fprintf(file2, "%c", '>');
		fprintf(file2, "%s", p1[i].name.c_str());
		fprintf(file2, "%s", "_parent\n");
		for (size_t j = 0; j < p1[i].sequence.size(); j++) {
			fprintf(file2, "%c", p1[i].sequence[j]);
			//	if (j % 800 == 0 && j != 0) {
			//		fprintf(file2, "%c", '\n');
			//	}
		}
		fprintf(file2, "%c", '\n');
	}

	fclose(file2);

	//print the region file;
	out = output;
	out += "regions.bed";
	file2 = fopen(out.c_str(), "w");

	for (size_t i = 0; i < regions.size(); i++) {
		fprintf(file2, "%s", regions[i].chr.c_str());
		fprintf(file2, "%c", '\t');
		fprintf(file2, "%i", regions[i].start + 1);
		fprintf(file2, "%c", '\t');
		fprintf(file2, "%i", regions[i].stop + 1);
		fprintf(file2, "%c", '\t');
		if (regions[i].p1) {
			fprintf(file2, "%s", "P1");
		} else {
			fprintf(file2, "%s", "P2");
		}
		fprintf(file2, "%c", '\n');
	}

}
