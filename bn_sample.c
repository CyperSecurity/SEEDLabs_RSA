#include <stdio.h>
#include <openssl/bn.h>

#define NBITS 256

void printBN(char *msg, BIGNUM *a);

int main(void)
{
  BIGNUM *a = BN_new();

  // Assign a value from a decimal number string
  BN_dec2bn(&a, "12345678901112231223");

  // Assign a value from a hex number string
  // BN_hex2bn(&a, "2A3B4C55FF77889AED3F");

  // Generate a random number of 128 bits
  // BN_rand(a, 128, 0, 0);

  // Generate a random prime number of 128 bits
  // BN_generate_prime_ex(a, 128, 1, NULL, NULL, NULL);

  printBN("This is my big num", a);
  return 0;
}

void printBN(char *msg, BIGNUM * a)
{
  // Convert the BIGNUM to number string
  char * number_str = BN_bn2dec(a);

  // Print out the number string
  printf("%s %s\n", msg, number_str);

  // Free the dynamically allocated memory
  OPENSSL_free(number_str);
}
