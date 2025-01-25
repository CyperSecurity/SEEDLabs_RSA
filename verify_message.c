#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

void hex_to_string(const char *hex_input, char *output);

int main(void)
{
  // Define required variables.
  
  BIGNUM *c = BN_new(); // Signature.
  BIGNUM *n = BN_new(); // Group.
  BIGNUM *e = BN_new(); // Public key.
  BIGNUM *sign_msg = BN_new(); // Define the decrypted message.
  
  BN_CTX *ctx = BN_CTX_new(); // Define ctx for calculations.

  // Ensure all variables allocated.
  if (!c || !n || !e || !sign_msg || !ctx) {
      fprintf(stderr, "Error: Failed to allocate BIGNUMs or BN_CTX\n");
      return 1;
  }

  // Input the message from the user.
  char message[256];
  char sign[256];

  printf("Enter the message: ");
  fgets(message, sizeof(message), stdin);
  message[strcspn(message, "\n")] = '\0';

  printf("Enter the signature: ");
  fgets(sign, sizeof(sign), stdin);
  sign[strcspn(sign, "\n")] = '\0'; 

  // Assign values.
  BN_hex2bn(&c, sign); 
  BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115"); 
  BN_hex2bn(&e, "010001"); 

  BN_mod_exp(sign_msg, c, e, n, ctx); 

  char sign_msg_text[256] = {0};
  char sign_msg_hex[256] = {0};
  char *sign_hex_ptr = BN_bn2hex(sign_msg);

  strcpy(sign_msg_hex, sign_hex_ptr);
  OPENSSL_free(sign_hex_ptr);
  hex_to_string(sign_msg_hex, sign_msg_text);

  if (strcmp(sign_msg_text, message) == 0)
  {
    printf("Valid signature!\n");
  }
  else
  {
    printf("Invaliad signature!\n");
  }

  // Clean up.
  BN_CTX_free(ctx);
  BN_free(n);
  BN_free(c);
  BN_free(e);
  BN_free(sign_msg);

  return 0;
}

void hex_to_string(const char *hex_input, char *output)
{
    while (*hex_input && *(hex_input + 1)) {
        char hex_byte[3] = {hex_input[0], hex_input[1], '\0'};
        *output = (char)strtol(hex_byte, NULL, 16);
        hex_input += 2;
        output++;
    }
    *output = '\0'; // Null-terminate the string
}
