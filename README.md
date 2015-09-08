# Coverage_count
This repository let you count coverage of metagenome on your reference
Let's assume you have metagenomics-short-read file and reference-genome file.
eg. metagenomics-short-read file
A1_CGATGT_L007_R1_001.fastq.gz
A1_CGATGT_L007_R2_001.fastq.gz 

eg. reference-genome file
RefSoil.fa

## 1. Mapping on reference genome (Bowtie2, samtools)
You can find how to install bowtie2 here.

### 1.1 build reference for bowtie2
```
bowtie2-build RefSoil.fa RefSoil
```
### 1.2 mapping
```
bowtie2 -x RefSoil -1 A1_CGATGT_L007_R1_001.fastq.gz -2 A1_CGATGT_L007_R2_001.fastq.gz -S A1_CGATGT_L007_R1_001.sam 2> A1_CGATGT_L007_R1_001.out
```
Now you need Samtools. You can find how to install samtools here.
### 1.3 convert sam to bam
```
samtools view A1_CGATGT_L007_R1_001.sam > A1_CGATGT_L007_R1_001.sam.bam
```
### 1.4 sort bam file
```
samtools sort A1_CGATGT_L007_R1_001.sam.bam A1_CGATGT_L007_R1_001.sam.sorted
```
### 1.5 index sorted bam file
```
samtools index A1_CGATGT_L007_R1_001.sam.sorted.bam
```
## 2. Count average
If you run python for the first time, you may need to install this.(python python-dev python-pip screed pysam numpy)
```
python sam-to-coverage.py A1_CGATGT_L007_R1_001.sam.sorted.bam RefSoil.fa > A1_CGATGT_L007_R1_001.sam.sorted.bam.coverage.txt
```
## 3. Merge result
```
mkdir coverageResult
mv *.coverage.txt coverageResult
g++ MergeResult.cpp -o MergeResult
./MergeResult coverageResult coverageResult.txt
```
## 4. If you use idxstats;

If you want to count by using idstats, following.

```
samtools idxstats *.sorted.bam
mkdir counts 
mv *.sorted.bam counts
bash idxstatsToOnefile.sh counts
```