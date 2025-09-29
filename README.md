# Assignment2
Arlene Huerta  

## Overview!
This assignment(2) is about practicing data representation and conversions.

Here, I wrote six functions in **convert.c** and used a simple test runner in **main.c** to check them with the provided `a2_tests.txt`.

## Functions in `convert.c`
- `oct_to_bin` – turns an octal string into binary  
- `oct_to_hex` – turns an octal string into uppercase hex (removes leading zeros but keeps at least one digit)  
- `hex_to_bin` – turns a hex string into binary  
- `to_sign_magnitude` – shows a signed int as 32-bit sign-magnitude  
- `to_ones_complement` – shows a signed int as 32-bit one’s complement  
- `to_twos_complement` – shows a signed int as 32-bit two’s complement  

## How I Built and Ran It
From the terminal in the project folder:


To build:
```bash
gcc -std=c11 -Wall -Wextra convert.c main.c -o a2
