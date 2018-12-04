/*
 * parental_genomes.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: sedlazec
 */

#include "parental_genomes.h"

char mut_char(char old) {
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


std::vector<chromosome_str> parse_fasta(std::string file_name, int min_length) {
	std::string buffer;
	std::ifstream myfile;

	myfile.open(file_name.c_str(), std::ifstream::in);
	if (!myfile.good()) {
		std::cout << "Fasta Parser: could not open file: " << file_name.c_str() << std::endl;
		exit(0);
	}

	getline(myfile, buffer);
	std::vector<chromosome_str> genome;

	std::string seq;
	std::string name;
	while (!myfile.eof()) {
		if (buffer[0] == '>') {
			if ((int) seq.size() > min_length) {
				chromosome_str chrom;
				chrom.name = name;
				chrom.sequence = seq;
				genome.push_back(chrom);
			}
			name.clear();
			seq.clear();

			for (size_t i = 1; i < buffer.size() && buffer[i] != '\n' && buffer[i] != '\0' && buffer[i] != ' '; i++) {
				name += (buffer[i]);
			}
		} else {
			for (size_t i = 0; i < buffer.size() && buffer[i] != '\n' && buffer[i] != '\0'; i++) {
				seq += toupper(buffer[i]);
			}
		}
		getline(myfile, buffer);
	}
	for (size_t i = 0; i < buffer.size() && buffer[i] != '\n' && buffer[i] != '\0'; i++) {
		seq += toupper(buffer[i]);
	}
	myfile.close();
	if ((int) seq.size() > min_length) {
		chromosome_str chrom;
		chrom.name = name;
		chrom.sequence = seq;
		genome.push_back(chrom);
	}
	seq.clear();
	name.clear();
	std::cout << "# Chrs passed size threshold:" << genome.size() << std::endl;
	return genome;
}


void parse_parental_genomes(std::string file_name, int min_length, float mutation_rate, std::vector<chromosome_str> & p1, std::vector<chromosome_str> &p2, std::string output) {

	p1 = parse_fasta(file_name, min_length);
	cout << "Parsed ref genome: " << p1.size() << " chrs." << endl;
	// random mutate X % SNPs
	p2 = p1;

	FILE *file2;
	std::string out = output;
	out += "_snps_p2.bed";
	file2 = fopen(out.c_str(), "w");

	for (size_t i = 0; i < p1.size(); i++) {
		for (size_t j = 0; j < p1[i].sequence.size(); j++) {
			float x = ((float) rand() / (float) (RAND_MAX));
			if (x < mutation_rate) {
				fprintf(file2, "%s", p1[i].name.c_str());
				fprintf(file2, "%c", '\t');
				fprintf(file2, "%i", (int) j + 1);
				fprintf(file2, "%c", '\t');
				fprintf(file2, "%i", (int) j + 2);
				fprintf(file2, "%c", '\t');
				fprintf(file2, "%c", p2[i].sequence[j]);

				char t = mut_char(toupper(p2[i].sequence[j]));
				//	cout<<"SNP: "<<p2[i].sequence[j]<<" "<<t<<endl;
				p2[i].sequence[j] = t;
				fprintf(file2, "%c", '\t');
				fprintf(file2, "%c", p2[i].sequence[j]);

				fprintf(file2, "%c", '\n');
			}
		}
	}
	cout << "Finished generating genome of second parental population" << endl;
}


void print_parental(std::vector<chromosome_str> p1, int num, float mutation_rate, std::string output) {
	FILE *file2;
	for (int p = 0; p < num; p++) {
		std::stringstream ss;
		ss << output;
		ss << "_";
		ss << p;
		ss << "_genome.fa";
		file2 = fopen(ss.str().c_str(), "w");

		for (size_t i = 0; i < p1.size(); i++) {
			fprintf(file2, "%c", '>');
			fprintf(file2, "%s", p1[i].name.c_str());
			fprintf(file2, "%s", "\n");
			for (size_t j = 0; j < p1[i].sequence.size(); j++) {

				float x = ((float) rand() / (float) (RAND_MAX));
				if (x < mutation_rate) {
					fprintf(file2, "%c", mut_char(toupper(p1[i].sequence[j])));
				} else {
					fprintf(file2, "%c", p1[i].sequence[j]);
				}
				//if (j+1 % 100 == 0 ) {
				//	fprintf(file2, "%c", '\n');
				//}
			}
			fprintf(file2, "%c", '\n');
		}
		fclose(file2);
	}

}
