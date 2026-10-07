#include <stdio.h>
#include <string.h>

void rc4(unsigned char *data, int len,
         unsigned char *key, int keylen)
{
    unsigned char S[256];
    unsigned char temp;
    int i, j = 0, k;

    /* Key Scheduling Algorithm (KSA) */

    for (i = 0; i < 256; i++)
        S[i] = i;

    for (i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keylen]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    /* Pseudo Random Generation Algorithm (PRGA) */

    i = 0;
    j = 0;

    for (k = 0; k < len; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        data[k] ^= S[(S[i] + S[j]) % 256];
    }
}

int main()
{
    unsigned char plaintext[500];
    unsigned char key[100];

    int len, keylen;

    printf("RC4 ENCRYPTION\n\n");

    /* Get input from user */

    printf("Enter Plain Text: ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);

    plaintext[strcspn((char *)plaintext, "\n")] = '\0';

    printf("Enter Key: ");
    scanf("%99s", key);

    len = strlen((char *)plaintext);
    keylen = strlen((char *)key);

    if (keylen == 0)
    {
        printf("Error: Key cannot be empty.\n");
        return 1;
    }

    printf("\nPlain Text : %s", plaintext);
    printf("\nKey        : %s", key);

    /* Encryption */

    rc4(plaintext, len, key, keylen);

    printf("\nCipher Text: ");

    for (int i = 0; i < len; i++)
    {
        printf("%02X", plaintext[i]);
    }

    printf("\n");

    return 0;
}
