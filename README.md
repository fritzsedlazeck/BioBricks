# BioBricks
A simple framework to simulate parental and admixture offsprings. The framework allows for a benchmark to distinguish inheritance blocks on the offsprings.


## Install:
Download SURVIVOR:
<pre>
git clone https://github.com/fritzsedlazeck/BioBricks.git
cd SURVIVOR/Debug
make
</pre>

## Usage:
For example:
<pre>
./BioBricks/Debug/BioBricks reference.fasta 1000000 0.01 10000 100000 0.5 4 10 0.0001 admixture_gen
</pre>


| Parameters      | Description | 
| ------------- |:-------------:| 
| reference.fasta: | The sequence that you want to simulate from |
| 1000000        | Minimum sequence size to consider |
| 0.01          | SNP mutation rate between the parental populations (0-1) |
| 10000        | Minimum size of a block in the child genome | 
| 100000      | Maximum size of a block in the child genome | 
| 0.5  | Probability of p1 for admixture region (0.5 balanced) | 
| 4  | Number of different children genomes. | 
| 10 | Number of parental genomes (per population) |
| 0.0001 | SNP rate within the  population |
| admixture_gen | Prefix of output files  | 

## Output
This will generate multiple files for parents and admixture.
For the parents the SNPs are reported that are dividing the two parental populations (e.g. "admixture_gen_snps_p2.bed"). 
Furthermore, each offspring data set will include a fasta sequence that includes the child genome as well as one of the parental genomes (back crossing) and a bed file (e.g. admixture_gen_child_0_regions.bed) that lists which regions were inherited from which parent. 

