#include <stdio.h>
#include <stdlib.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a);

int main(void)
{
  // Define required variables.
  
  BIGNUM *m = BN_new(); // Define message.

  BIGNUM *e = BN_new(); // Define public key
  
  BIGNUM *n = BN_new(); // Define the group.

  BIGNUM *d = BN_new(); // Define the private key.

  BIGNUM *encrypted_msg = BN_new(); // Define the encrypted message.
  BIGNUM *decrypted_msg = BN_new(); // Define the decrypted message.
  
  BN_CTX *ctx = BN_CTX_new(); // Define ctx for calculations.

  // Assign values.
  BN_hex2bn(&m,"E85CED54AF57E53E092113E62F436F4F"); 
  BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5"); 
  BN_bin2bn("010001", 6, e); 
  BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D"); 

  BN_mod_exp(encrypted_msg, m, e, n, ctx); 
  BN_mod_exp(decrypted_msg, encrypted_msg, d, n, ctx); 

  printBN("Encrypted message:", encrypted_msg);
  printBN("Decrypted message:", decrypted_msg);

  // Clean up.
  BN_CTX_free(ctx);
  BN_free(n);
  BN_free(m);
  BN_free(e);
  BN_free(d);
  BN_free(encrypted_msg);
  BN_free(decrypted_msg);

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
