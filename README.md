# Scalar product sum
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

## Steps to run
### sequential version
```bash
gcc prod_escalar_mat_seq.c -o seq -fopenmp -lm
./seq < entrada.txt
./seq < entrada1.txt
./seq < entrada2.txt
```
### parallel version
```bash
gcc prod_escalar_mat_simd.c -o parallel -fopenmp -lm
./parallel < entrada.txt
./parallel < entrada1.txt
./parallel < entrada2.txt
```