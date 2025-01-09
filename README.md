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
n = DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5
e = 010001 (this hex value equals to decimal 65537)
M = A top secret!
d = 74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D
```
