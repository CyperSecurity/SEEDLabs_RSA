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

Task code can be found in [calc_private_key.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/calc_private_key.c).

To complie the code run the command:
```
gcc calc_private_key.c -lcrypto -o bin/calc_private_key
```
To run the complied code:
```
./bin/calc_private_key
```

Results:
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

Task code can be found in  [encrypt_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/encrypt_message.c).

To complie the code run the command:
```
gcc encrypt_message.c -lcrypto -o bin/encrypt_message
```
To run the complied code:
```
./bin/encrypt_message
```

Results:
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
Task code can be found in  [decrypt_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/decrypt_message.c).

To complie the code run the command:
```
gcc decrypt_message.c -lcrypto -o bin/calc_private_key
```
To run the complied code:
```
./bin/decrypt_message
```

Results:
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

Task code can be found in  [sign_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/sign_message.c).

To complie the code run the command:
```
gcc sign_message.c -lcrypto -o bin/sign_message
```
To run the complied code:
```
./bin/sign_message
```

Results:
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

Task code can be found in  [verify_message.c](https://github.com/CyperSecurity/SEEDLabs_RSA/blob/main/verify_message.c).

To complie the code run the command:
```
gcc verify_message.c -lcrypto -o bin/sign_message
```
To run the complied code:
```
./bin/verify_message
```

Results:
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

### Task 6: Manually Verifying an X.509 Certificate
In this task, we will manually verify an X.509 certificate using our program. An X.509 contains data about
a public key and an issuer’s signature on the data. We will download a real X.509 certificate from a web
server, get its issuer’s public key, and then use this public key to verify the signature on the certificate.

To get the certificate, the following command is used:
```
openssl s_client -connect www.example.org:443 -showcerts
```

The following output is shown:
```
CONNECTED(00000003)
depth=1 C = US, O = DigiCert Inc, CN = DigiCert Global G3 TLS ECC SHA384 2020 CA1
verify error:num=20:unable to get local issuer certificate
verify return:1
depth=0 C = US, ST = California, L = Los Angeles, O = Internet Corporation for Assigned Names and Numbers, CN = *.example.org
verify return:1
---
Certificate chain
 0 s:C = US, ST = California, L = Los Angeles, O = Internet Corporation for Assigned Names and Numbers, CN = *.example.org
   i:C = US, O = DigiCert Inc, CN = DigiCert Global G3 TLS ECC SHA384 2020 CA1
-----BEGIN CERTIFICATE-----
MIIFnTCCBSSgAwIBAgIQByKnSbVYR2GW1VREXtvSVDAKBggqhkjOPQQDAzBZMQsw
CQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMTMwMQYDVQQDEypEaWdp
Q2VydCBHbG9iYWwgRzMgVExTIEVDQyBTSEEzODQgMjAyMCBDQTEwHhcNMjUwMTE1
MDAwMDAwWhcNMjYwMTE1MjM1OTU5WjCBjjELMAkGA1UEBhMCVVMxEzARBgNVBAgT
CkNhbGlmb3JuaWExFDASBgNVBAcTC0xvcyBBbmdlbGVzMTwwOgYDVQQKEzNJbnRl
cm5ldCBDb3Jwb3JhdGlvbiBmb3IgQXNzaWduZWQgTmFtZXMgYW5kIE51bWJlcnMx
FjAUBgNVBAMMDSouZXhhbXBsZS5vcmcwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNC
AARvcLhq3uFMuzkqpTXG4X8Wcw413owfBJMz4JcqnNnlgNb2+2F0TaF4fVoDpf8+
arlyqMYsxSxpUH/NbTudhW/Mo4IDljCCA5IwHwYDVR0jBBgwFoAUiiPrnmvX+Tdd
+W0hOXaaoWfeEKgwHQYDVR0OBBYEFBJFomWJllXyCp7B3wWf3VnuZbpRMCUGA1Ud
EQQeMByCDSouZXhhbXBsZS5vcmeCC2V4YW1wbGUub3JnMD4GA1UdIAQ3MDUwMwYG
Z4EMAQICMCkwJwYIKwYBBQUHAgEWG2h0dHA6Ly93d3cuZGlnaWNlcnQuY29tL0NQ
UzAOBgNVHQ8BAf8EBAMCA4gwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMC
MIGfBgNVHR8EgZcwgZQwSKBGoESGQmh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9E
aWdpQ2VydEdsb2JhbEczVExTRUNDU0hBMzg0MjAyMENBMS0yLmNybDBIoEagRIZC
aHR0cDovL2NybDQuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0R2xvYmFsRzNUTFNFQ0NT
SEEzODQyMDIwQ0ExLTIuY3JsMIGHBggrBgEFBQcBAQR7MHkwJAYIKwYBBQUHMAGG
GGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTBRBggrBgEFBQcwAoZFaHR0cDovL2Nh
Y2VydHMuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0R2xvYmFsRzNUTFNFQ0NTSEEzODQy
MDIwQ0ExLTIuY3J0MAwGA1UdEwEB/wQCMAAwggF+BgorBgEEAdZ5AgQCBIIBbgSC
AWoBaAB3AJaXZL9VWJet90OHaDcIQnfp8DrV9qTzNm5GpD8PyqnGAAABlGd6xV4A
AAQDAEgwRgIhAO28p5oX3gxA0RJJ/2MaZ3zzMcyZggy2lwVQnqSpX5R3AiEAqUWx
+2l1xeojShV0ab+MbcPNg8bYvw1xb32sJOYuxKkAdQBkEcRspBLsp4kcogIuALyr
TygH1B41J6vq/tUDyX3N8AAAAZRnesVjAAAEAwBGMEQCIAzHUguIG8H+0JF72uTL
HatlorikPR/D3P/HRsyrF+44AiBGH0KcLNqcj2ZGEjChiiRfOjLdUrFKg6jnMIoV
FMlYFwB2AEmcm2neHXzs/DbezYdkprhbrwqHgBnRVVL76esp3fjDAAABlGd6xXgA
AAQDAEcwRQIgRESM73pynQ140QSowDrC49oQXZut2nYQc2DYrX26VXgCIQDRBYhi
5U3bC19GT2EzfDLr38vkM5yNNYnYlY1En7+TczAKBggqhkjOPQQDAwNnADBkAjBH
fYRsXBNHMfs6MlztuZRrCRw0ERMhMSHe7Al5nSDz+cP3KHcdxkRWtf1xFksSljUC
ME1pXV7GC3Vq2Pmd0wPkRSngBR9Hm2X8srwINo/QvZ91oS7dUDseaBJ5wOb5oHmA
jw==
-----END CERTIFICATE-----
 1 s:C = US, O = DigiCert Inc, CN = DigiCert Global G3 TLS ECC SHA384 2020 CA1
   i:C = US, O = DigiCert Inc, OU = www.digicert.com, CN = DigiCert Global Root G3
-----BEGIN CERTIFICATE-----
MIIDeTCCAv+gAwIBAgIQCwDpLU1tcx/KMFnHyx4YhjAKBggqhkjOPQQDAzBhMQsw
CQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cu
ZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBHMzAe
Fw0yMTA0MTQwMDAwMDBaFw0zMTA0MTMyMzU5NTlaMFkxCzAJBgNVBAYTAlVTMRUw
EwYDVQQKEwxEaWdpQ2VydCBJbmMxMzAxBgNVBAMTKkRpZ2lDZXJ0IEdsb2JhbCBH
MyBUTFMgRUNDIFNIQTM4NCAyMDIwIENBMTB2MBAGByqGSM49AgEGBSuBBAAiA2IA
BHipnHWuiF1jpK1dhtgQSdavklljQyOF9EhlMM1KNJWmDj7ZfAjXVwUoSJ4Lq+vC
05ae7UXSi4rOAUsXQ+Fzz21zSDTcAEYJtVZUyV96xxMH0GwYF2zK28cLJlYujQf1
Z6OCAYIwggF+MBIGA1UdEwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFIoj655r1/k3
XfltITl2mqFn3hCoMB8GA1UdIwQYMBaAFLPbSKT5ocXYrjZBzBFjaWIpvEvGMA4G
A1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwdgYI
KwYBBQUHAQEEajBoMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5j
b20wQAYIKwYBBQUHMAKGNGh0dHA6Ly9jYWNlcnRzLmRpZ2ljZXJ0LmNvbS9EaWdp
Q2VydEdsb2JhbFJvb3RHMy5jcnQwQgYDVR0fBDswOTA3oDWgM4YxaHR0cDovL2Ny
bDMuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0R2xvYmFsUm9vdEczLmNybDA9BgNVHSAE
NjA0MAsGCWCGSAGG/WwCATAHBgVngQwBATAIBgZngQwBAgEwCAYGZ4EMAQICMAgG
BmeBDAECAzAKBggqhkjOPQQDAwNoADBlAjB+Jlhu7ojsDN0VQe56uJmZcNFiZU+g
IJ5HsVvBsmcxHcxyeq8ickBCbmWE/odLDxkCMQDmv9auNIdbP2fHHahv1RJ4teaH
MUSpXca4eMzP79QyWBH/OoUGPB2Eb9P1+dozHKQ=
-----END CERTIFICATE-----
---
Server certificate
subject=C = US, ST = California, L = Los Angeles, O = Internet Corporation for Assigned Names and Numbers, CN = *.example.org

issuer=C = US, O = DigiCert Inc, CN = DigiCert Global G3 TLS ECC SHA384 2020 CA1

---
No client certificate CA names sent
Peer signing digest: SHA256
Peer signature type: ECDSA
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 2723 bytes and written 397 bytes
Verification error: unable to get local issuer certificate
---
New, TLSv1.3, Cipher is TLS_AES_256_GCM_SHA384
Server public key is 256 bit
Secure Renegotiation IS NOT supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
Early data was not sent
Verify return code: 20 (unable to get local issuer certificate)
---
---
Post-Handshake New Session Ticket arrived:
SSL-Session:
    Protocol  : TLSv1.3
    Cipher    : TLS_AES_256_GCM_SHA384
    Session-ID: 9E65993453ECD08208C9BBA7244D4DD281710121C6210FCF8A392650C297B2FE
    Session-ID-ctx: 
    Resumption PSK: 0DEA3B38B31178B8CE733E35B5635CCEAADEEFE01F30CC5B2B885DFC38639931C77323CA82228622E51DE80E3D7E7844
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 83100 (seconds)
    TLS session ticket:
    0000 - 00 04 20 7f dc e0 fc 72-a3 d0 99 fd 5b 30 39 b5   .. ....r....[09.
    0010 - 68 b2 77 a7 f7 c0 83 3e-1e f6 f3 5d 1b 52 4e 76   h.w....>...].RNv
    0020 - 58 d3 50 14 f1 27 36 9f-19 31 0c 88 8e 5f 94 2c   X.P..'6..1..._.,
    0030 - 7c 0a 66 49 cb 36 74 27-7f 4a a3 20 9f eb cb b9   |.fI.6t'.J. ....
    0040 - d1 fc 37 75 82 24 84 9c-59 55 1f 9d 83 b1 8b ce   ..7u.$..YU......
    0050 - 8d 0d 86 f4 c6 ad 0d 33-37 80 43 23 72 f7 5d 23   .......37.C#r.]#
    0060 - e2 5c 1b 4e 47 1a 2b bb-72 d4 cc d9 6d bd 8c 76   .\.NG.+.r...m..v
    0070 - 62 24 ff 0b b5 a2 e7 d3-52 0f 40 95 e6 48 bf bb   b$......R.@..H..
    0080 - 25 4d b9 d0 7b 45 39 f6-80 8c dc 2e ad d8 45 67   %M..{E9.......Eg
    0090 - f2 30 5e 5a c0 3b 22 d9-e4 bb a7 57 5d 51 fe 13   .0^Z.;"....W]Q..
    00a0 - 02 cd 6b 81 5b ae 55 f4-4c 38 3f d4 e4 1e 7c 75   ..k.[.U.L8?...|u
    00b0 - 52 e5 06 c0 66 67 cf 94-1e ea 74 8c 60 9c 88 24   R...fg....t.`..$
    00c0 - 71 42 44 d3 95 f5 0d 4d-93 12 88 9e 45 6b ec 0e   qBD....M....Ek..
    00d0 - 1d 75 01 ed 1b 00 87 77-38 a1 b9 d3 89 7b 1b e2   .u.....w8....{..

    Start Time: 1737831801
    Timeout   : 7200 (sec)
    Verify return code: 20 (unable to get local issuer certificate)
    Extended master secret: no
    Max Early Data: 0
---
read R BLOCK
---
Post-Handshake New Session Ticket arrived:
SSL-Session:
    Protocol  : TLSv1.3
    Cipher    : TLS_AES_256_GCM_SHA384
    Session-ID: 8F1CB3436C4D91577FF3641F06D65637936546808F12873AB08A3E1C0367C7BA
    Session-ID-ctx: 
    Resumption PSK: AC6C1239932C48603D217CF632BE861F9304971941B983966D99016B62AFE7519252DAA8EBD08CEC526A9F239B43CA53
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 83100 (seconds)
    TLS session ticket:
    0000 - 00 04 20 7f dc e0 fc 72-a3 d0 99 fd 5b 30 39 b5   .. ....r....[09.
    0010 - 67 8e cc 9b 05 0b d3 e9-07 07 ac 03 c9 78 2f 88   g............x/.
    0020 - 89 47 7a 87 1a e3 5a d9-91 67 f5 38 f8 7c 3b 37   .Gz...Z..g.8.|;7
    0030 - 66 b5 04 84 e0 f4 eb d1-e5 2a 9b e9 33 20 6b b2   f........*..3 k.
    0040 - 3a 72 9d b5 42 34 b6 cc-f2 19 86 37 a0 0f 98 f9   :r..B4.....7....
    0050 - 98 3b d1 68 7d 79 55 8c-97 79 78 16 67 ca 49 09   .;.h}yU..yx.g.I.
    0060 - b3 f9 7b 7b 40 e3 96 01-3a 41 e4 cc 20 6c 72 b9   ..{{@...:A.. lr.
    0070 - f1 73 58 91 7c aa 81 03-04 6e bf a9 af 7f 55 ee   .sX.|....n....U.
    0080 - 7d 56 eb d1 2f d7 9c 67-7b 17 df 92 e5 0d 79 e4   }V../..g{.....y.
    0090 - b6 66 14 84 53 dc f6 3e-8c d6 fb d7 7c 6d d6 90   .f..S..>....|m..
    00a0 - ed 3c 41 26 2a 7e 56 f3-9e 12 30 d6 22 a9 83 6b   .<A&*~V...0."..k
    00b0 - 28 9d c6 a9 72 fc 89 40-e0 23 39 5e 1e b5 f0 4e   (...r..@.#9^...N
    00c0 - 97 ca e7 32 c9 a1 22 e2-81 af 31 ee 7d 53 31 d0   ...2.."...1.}S1.
    00d0 - 76 28 15 36 2b b7 79 db-c8 81 47 c2 4c 24 5a 6f   v(.6+.y...G.L$Zo

    Start Time: 1737831801
    Timeout   : 7200 (sec)
    Verify return code: 20 (unable to get local issuer certificate)
    Extended master secret: no
    Max Early Data: 0
---
read R BLOCK
---
```

