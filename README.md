# SEED labs 2 (RSA Public-Key Encryption and Signature Lab)

## Lab accessablitity
The lab pdf can be accessed through the following link [SEED labs 2 (RSA)](https://seedsecuritylabs.org/Labs_20.04/Files/Crypto_RSA/Crypto_RSA.pdf).
This lab will use `C` as the main programming language to write the RSA function.

## Get starting with openssl
Due to RSA requires large nubmers like **512bit** normal varbles like `int` **(32bits)** or `long` **(64bits)** can't store those numbers, so big number algrothims or functions are required here where `openssl` come in handy because
it's had all required function to write RSA.
openssl big number documnetation can be found in [openssl big numbers](https://linux.die.net/man/3/bn)

## BIGNUM APIs
This code [bn_sample.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/bn_sample.c) provides basic mod and mulitplication.

To complie the code run the command:
```
gcc bn_sample.c -lcrypto -o bin/bn_sample
```
To run the complied code:
```
./bin/bn_sample
```

## Lab tasks
### Task 1: Deriving the Private Key
Let p, q, and e be three prime numbers. Let n = p*q. We will use (e, n) as the public key. Please
calculate the private key d. The hexadecimal values of p, q, and e are listed in the following. It should be
noted that although p and q used in this task are quite large numbers, they are not large enough to be secure.
We intentionally make them small for the sake of simplicity. In practice, these numbers should be at least
512 bits long (the one used here are only 128 bits).
```
p = F7E75FDC469067FFDC4E847C51F452DF
q = E85CED54AF57E53E092113E62F436F4F
e = 0D88C3
```

The code of that task is in [calc_private_key.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/calc_private_key.c).

To complie the code run the command:
```
gcc calc_private_key.c -lcrypto -o bin/calc_private_key
```
To run the complied code:
```
./bin/calc_private_key
```

My results:
```
N:           072C8D59E4307CFD226E6FA4263F3FDC5D9676BCCC70118BD0AA1968DBB143D1
phi N:       072C8D59E4307CFD226E6FA4263F3FDB6D52298BD687C44DEB3A81065A7981A4
Private key: 026C3A9992028FF6F17091504A527D6D6AB1E0C4F2A1AC2413994E6210700297
```

### Task 2: Encrypting a Message
Let (e, n) be the public key. Please encrypt the message "A top secret!" (the quotations are not
included). We need to convert this ASCII string to a hex string, and then convert the hex string to a BIGNUM
using the hex-to-bn API BN hex2bn(). The following python command can be used to convert a plain
ASCII string to a hex string.

To get the hex value of the text, following command is used:
```
python3 -c 'print("A top secret!".encode("utf-8").hex())'
```
hex value:
```
4120746f702073656372657421
```

The following parameters are used:
```
M = A top secret!
n = DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5
e = 010001 (this hex value equals to decimal 65537)
```

The code of that task is in [encrypt_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/encrypt_message.c).

To complie the code run the command:
```
gcc encrypt_message.c -lcrypto -o bin/encrypt_message
```
To run the complied code:
```
./bin/encrypt_message
```

My results:
```
Enter the message: A top secret!
Encrypted message: 6FB078DA550B2650832661E14F4F8D2CFAEF475A0DF3A75CACDC5DE5CFC5FADC
```

### Task 3: Decoding a Message
The public/private keys used in this task are the same as the ones used in **Task 2**.

convert a hex string back to to a plain ASCII, following command is used:
```
python3 -c 'print(bytes.fromhex("4120746f702073656372657421").decode("utf-8"))'
```

The following parameters are used:
```
n = DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5
C = 8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F
d = 74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D
```
The code of that task is in [decrypt_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/decrypt_message.c).

To complie the code run the command:
```
gcc decrypt_message.c -lcrypto -o bin/calc_private_key
```
To run the complied code:
```
./bin/decrypt_message
```

My results:
```
Enter the cipher text:    8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F
Decrypted message (hex):  50617373776F72642069732064656573
Decrypted message (text): Password is dees
```

### Task 4: Signing a Message
The public/private keys used in this task are the same as the ones used in Task 2. Please generate a signature
for the following message (please directly sign this message, instead of signing its hash value):

```
M1 = "I owe you $2000."
M2 = "I owe you $3000."
```

The code of that task is in [sign_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/sign_message.c).

To complie the code run the command:
```
gcc sign_message.c -lcrypto -o bin/sign_message
```
To run the complied code:
```
./bin/sign_message
```

My results:
```
[01/25/25]seed@VM:~/.../RSA$ ./bin/sign_message 
Enter the message: I owe you $2000.
Signature:  55A4E7F17F04CCFE2766E1EB32ADDBA890BBE92A6FBE2D785ED6E73CCB35E4CB
[01/25/25]seed@VM:~/.../RSA$ ./bin/sign_message 
Enter the message: I owe you $3000.
Signature:  BCC20FB7568E5D48E434C387C06A6025E90D29D848AF9C3EBAC0135D99305822
```

Observation:
The two results are completely different so small change in the message will result in completey different output.

### Task 5: Verifying a Signature
Bob receives a message M = "Launch a missile." from Alice, with her signature S. We know that
Alice’s public key is (e, n). Please verify whether the signature is indeed Alice’s or not. The public key
and signature (hexadecimal) are listed in the following:
```
M = Launch a missile.
S = 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F
e = 010001 (this hex value equals to decimal 65537)
n = AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115
```
Suppose that the signature above is corrupted, such that the last byte of the signature changes from 2F
to 3F, i.e, there is only one bit of change.
```
S1 = 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F
S2 = 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F
```

The code of that task is in [verify_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/verify_message.c).

To complie the code run the command:
```
gcc verify_message.c -lcrypto -o bin/sign_message
```
To run the complied code:
```
./bin/verify_message
```

My results:
```
[01/25/25]seed@VM:~/.../RSA$ ./bin/verify_message 
Enter the message: Launch a missile.
Enter the signature: 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F
Valid signature!
[01/25/25]seed@VM:~/.../RSA$ ./bin/verify_message 
Enter the message: Launch a missile.
Enter the signature: 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F    
Invaliad signature!
```

Observation:
Small change in signature or change in singature can't give you a correct signature that much the message.

