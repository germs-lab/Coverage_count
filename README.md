# Coverage_count

Let me assume you have metagenomics-short-read file and reference-genome file.

## 1. Mapping on reference genome (Bowtie2, samtools)
You can find how to install bowtie2 here.
1.1 build reference for bowtie2
bowtie2-build reference_sequence referencename

### 1.2 mapping
bowtie2 -x lambda_virus -U ~/BT2_HOME/example/reads/reads_1.fq -S eg1.sam

Now you need Samtools. You can find how to install samtools here.
### 1.3 convert sam to bam
samtools view file.sam > file.bam

### 1.4 sort bam file
samtools sort file.sam.bam file.sam.sorted

### 1.5 index sorted bam file
samtools index file.sam.sorted.bam

## 2. Count average
If you run python for the first time, you may need to install this.(python python-dev python-pip screed pysam numpy)

python sam-to-coverage.py file.sam.sorted.bam reference.fa > filename.coverage.txt

## 3. Merge result