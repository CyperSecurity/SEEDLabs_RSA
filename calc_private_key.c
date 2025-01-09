#include <stdio.h>
#include <stdlib.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a);

int main(void)
{
  // Define required variables.
  // Define 2 prim numbers.
  BIGNUM *p = BN_new();
  BIGNUM *q = BN_new();

  // Define public key
  BIGNUM *e = BN_new();

  // Define the group.
  BIGNUM *n = BN_new();
  BIGNUM *phi_n = BN_new();

  // Define q-1 and p-1
  BIGNUM *p_1 = BN_new();
  BIGNUM *q_1 = BN_new();

  // Define the private key.
  BIGNUM *d = BN_new();

  // Define constant.
  BIGNUM *one = BN_new();

  // To store p-1 and q-1.
  BN_CTX *ctx = BN_CTX_new();

  // Assign values.
  BN_hex2bn(&p,"7E75FDC469067FFDC4E847C51F452DF"); 
  BN_hex2bn(&q,"E85CED54AF57E53E092113E62F436F4F"); 
  BN_hex2bn(&e,"D88C3"); 
  BN_dec2bn(&one, "1");

  // Get n and phi(n).
  BN_mul(n, p, q, ctx);
  BN_sub(p_1, p, one);
  BN_sub(q_1, q, one);
  BN_mul(phi_n, p_1, q_1, ctx);

  // Get the private key
  d = BN_mod_inverse(d, e, phi_n, ctx);
  printBN("N:          ", n);
  printBN("phi N:      ", phi_n);
  printBN("Private key:", d);

  // Clean up.
  BN_CTX_free(ctx);
  BN_free(p);
  BN_free(q);
  BN_free(e);
  BN_free(n);
  BN_free(phi_n);
  BN_free(p_1);
  BN_free(q_1);
  BN_free(one);

  return 0;
}

void printBN(char *msg, BIGNUM * a)
{
  /* Use BN_bn2hex(a) for hex string
   * Use BN_bn2dec(a) for decimal string */
  char * number_str = BN_bn2hex(a);
  printf("%s %s\n", msg, number_str);
  OPENSSL_free(number_str);
}
