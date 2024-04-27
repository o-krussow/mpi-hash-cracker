#include <stdio.h>
#include <math.h>
#include <string.h>
#include <mpi.h>
#include <openssl/evp.h>

char* charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890,./<>?;':";

char *strrev(char *str)
{
  char *p1, *p2;

  if (! str || ! *str)
        return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
  {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
  }
  return str;
}

void decimal_to_base_k(long long int decimal_num, char* base_k_num) {
  int new_base = strlen(charset); //For readability sake 

  int index = 0;
  while (decimal_num / new_base != 0) {
    base_k_num[index] = charset[decimal_num % new_base];
    decimal_num = decimal_num / new_base;
    index++;
  }
  //Get character at index (decimal_num % new_base)
  base_k_num[index] = charset[decimal_num % new_base];

  strrev(base_k_num);

  base_k_num[index+1] = '\0';
}

void bytes2md5(char *data, int len, char *md5buf) {
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  const EVP_MD *md = EVP_md5();

  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len, i;

  EVP_DigestInit_ex(mdctx, md, NULL);
  EVP_DigestUpdate(mdctx, data, len);
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  EVP_MD_CTX_free(mdctx);
  for (i = 0; i < md_len; i++) {
    snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
  }
}

void start_hashing(char* processor_name, int world_rank, int world_size, char* testhash) {
  int MAX_PASS_LENGTH = 10;
  long long int UPPER_LIMIT = pow(strlen(charset), MAX_PASS_LENGTH);

  char base_k_num[100];
  long long int decimal_counter = world_rank;
  char md5hash[33];

  while (decimal_counter < UPPER_LIMIT) {
    decimal_to_base_k(decimal_counter, base_k_num);


    bytes2md5(base_k_num, strlen(base_k_num), md5hash);

    if (decimal_counter % 10000000 == 0) {
      printf("Current guess: %s\n", base_k_num);
    } 

    if (strcmp(md5hash, testhash) == 0) {
      printf("%s found string is %s\n", processor_name, base_k_num);
      break;
    }
    decimal_counter += world_size;
  }	
}

int main(int argc, char* argv[]) {

  MPI_Init(NULL, NULL);      // initialize MPI environment
  int world_size; // number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank; // the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  char processor_name[MPI_MAX_PROCESSOR_NAME]; // gets the name of the processor
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  if (argc == 2) {
    start_hashing(processor_name, world_rank, world_size, argv[1]);
  }

  MPI_Abort(MPI_COMM_WORLD, 0);

  MPI_Finalize();

  return 0;

}

