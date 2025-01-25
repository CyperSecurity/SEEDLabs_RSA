#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a);
void string_to_hex(const char *input, char *output);

int main(void)
{
  // Define required variables.
  
  BIGNUM *m = BN_new(); // Message.
  BIGNUM *e = BN_new(); // Public key
  BIGNUM *n = BN_new(); // Group.
  BIGNUM *signing_msg = BN_new(); // Define the encrypted message.
  
  BN_CTX *ctx = BN_CTX_new(); // Define ctx for calculations.

  // Ensure all variables allocated.
  if (!m || !e || !n || !signing_msg || !ctx) {
      fprintf(stderr, "Error: Failed to allocate BIGNUMs or BN_CTX\n");
      return 1;
  }

  // Input the message from the user.
  char input[256];
  printf("Enter the message: ");
  fgets(input, sizeof(input), stdin);
  input[strcspn(input, "\n")] = '\0';  // Remove newline character if present

  // Convert the message to a hex string.
  char hex_message[512] = {0};
  string_to_hex(input, hex_message);

  // Assign values.
  BN_hex2bn(&m, hex_message); 
  BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5"); 
  BN_hex2bn(&e, "010001"); 

  BN_mod_exp(signing_msg, m, e, n, ctx); 

  printBN("Signature: ", signing_msg);

  // Clean up.
  BN_CTX_free(ctx);
  BN_free(n);
  BN_free(m);
  BN_free(e);
  BN_free(signing_msg);

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

void string_to_hex(const char *input, char *output)
{
    while (*input) {
        sprintf(output, "%02X", (unsigned char)*input);
        input++;
        output += 2;
    }
}
