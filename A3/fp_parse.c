/*
Theo Rowlett
CS201 Spring 2021
A3: Create an application that takes 3 arguments:
    Fraction bits
    Exponent bits
    # to convert (in hex)

    Then parses the float value.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

bool validate(uint n, uint k, uint hex, char * argv[]);
uint exp_field(uint k, uint hex);
float frac_field(uint n, uint hex, int exp);
bool sign (uint hex, uint n, uint k);


int
main(int argc, char * argv[])
{
    bool signbit = false;   
    uint n = 0;     //Fraction bits
    uint k = 0;     //Exponent bits
    uint hex = 0;   //Hex number to be parsed
    float m = 0.0;  // 1 + frac
    uint e = 0;     // exponent - bias
    int exp = 0;
    float frac = 0;
    uint bias = 0;

    float final_val = 0.0;

    if (argc != 4)
    {
        printf("fp_parse <# fraction bits> <# exponent bits> <hex #>. Invalid arguments.\n");
        exit(0);
    }

    sscanf(argv[1], "%u", &n);
    sscanf(argv[2], "%u", &k);
    if (sscanf(argv[3], "%x", &hex)!=1)
            printf("Argument 3 is not a hexadecimal number (%s)\n",argv[3]);

    if (validate(n,k,hex,argv) == false)
    {
        printf("Terminating application.\n");
        exit(0);
    }
    signbit = sign(hex,n,k);
    if (signbit == true)
        hex = hex % (uint)pow(2,n+k);
    printf(signbit ? "-" : "+");
    bias = pow(2,(k-1))-1;
    exp = exp_field(k,hex);
    //Denormalized
    if (exp == (int)0)
    {
        e = 1 - bias;
        m = frac;
        printf("%.4f\n",0.0);
        exit(1);
    }
    //Special values
    else if (exp == pow(2,k)-1)
    {
        if (frac == 0)
            printf("Inf\n");
        else
            printf("NaN\n");
        exit(1);

    }
    //Normalized
    else
    {
        m = 1 + frac;
        e = exp - bias;
    }
    final_val = m * pow(2,e);
    printf("%.4f\n",final_val);
    exit(1);

}

uint
exp_field(uint k, uint hex)
{
    return hex >> k;
}

float
frac_field(uint n, uint hex, int exp)
{
    float frac = 0.0;
    int i = n-1;
    int j = 1;
    int fract_bits = hex - (exp << n);
    while (fract_bits != 0)
    {
        if (fract_bits/pow(2,i) >= 1 )
        {
            frac += pow(2,-j);
        }
        fract_bits = fract_bits % (int)(pow(2,i));
        --i;
        ++j;
    }
    return frac;
}

bool
validate(uint n, uint k, uint hex, char * argv[])
{
    if (n > 10 || n < 2)
    {
        printf("Invalid number of fraction bits (%s). Must be between 2 and 10.\n",argv[1]);
        return false;
    }
    if (k > 5 || k < 3)
    {
        printf("Invalid number of exponent bits (%s).Must be between 3 and 5.\n", argv[2]);
        return false;
    }

    if (hex > pow(2,(n+k+1)))
    {
        printf("Number %s exceeds number of bits. Only %u allowed.\n", argv[3],n+k+1);
        return false;
    }

    //Validate hex input
    int size = strlen(argv[3]);
    for (int i = 0; i < size; ++i)
    {
        if ((argv[3][i] < '0' || argv[3][i] > '9') && (argv[3][i] < 'A' || argv[3][i] > 'F') && (argv[3][i] < 'a' || argv[3][i] > 'f'))
        {
            printf("%s is not a valid hex number.", argv[3]);
            return false;
        }
    }

    return true;
}
bool
sign (uint hex, uint n, uint k)
{
    if (hex/(int)pow(2,(n+k)) >= 1)
        return true;
    return false;
}
