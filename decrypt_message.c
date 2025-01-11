#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

void hex_to_string(const char *hex_input, char *output);

int main(void)
{
  // Define required variables.
  
  BIGNUM *c = BN_new(); // Cipher.
  BIGNUM *e = BN_new(); // Public key
  BIGNUM *n = BN_new(); // Group.
  BIGNUM *d = BN_new(); // Private key.
  BIGNUM *decrypted_msg = BN_new(); // Define the decrypted message.
  
  BN_CTX *ctx = BN_CTX_new(); // Define ctx for calculations.

  // Ensure all variables allocated.
  if (!c || !e || !n || !d || !decrypted_msg || !ctx) {
      fprintf(stderr, "Error: Failed to allocate BIGNUMs or BN_CTX\n");
      return 1;
  }

  // Input the message from the user.
  char hex_cipher[256];
  printf("Enter the cipher text: ");
  fgets(hex_cipher, sizeof(hex_cipher), stdin);

  // Assign values.
  BN_hex2bn(&c, hex_cipher); 
  BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5"); 
  BN_hex2bn(&e, "010001"); 
  BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D"); 

  BN_mod_exp(decrypted_msg, c, d, n, ctx); 

  char decrypted_msg_text[256] = {0};
  char decrypted_msg_hex[256] = {0};
  char *decrypted_hex_ptr = BN_bn2hex(decrypted_msg);

  strcpy(decrypted_msg_hex, decrypted_hex_ptr);
  OPENSSL_free(decrypted_hex_ptr);
  hex_to_string(decrypted_msg_hex, decrypted_msg_text);

  printf("Decrypted message (hex): %s\n", decrypted_msg_hex);
  printf("Decrypted message (text): %s\n", decrypted_msg_text);

  // Clean up.
  BN_CTX_free(ctx);
  BN_free(n);
  BN_free(c);
  BN_free(e);
  BN_free(d);
  BN_free(decrypted_msg);

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
