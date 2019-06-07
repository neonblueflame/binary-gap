/*
 * This program should print the longest binary gap found in the
 * integer provided. The input should be a decimal integer that
 * is a whole, real number, greater than 0.
 *
 * Error codes
 * 0 - No error
 * 1 - Missing argument
 * 2 - Argument contains non-digit character
 *
 * Author: Neonblueflame
 * Date: 20190601
 * Updated: 20190608
 * */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if the 1st argument is valid
int is_arg_invalid(int argc, char** argv);

// Converts decimal to binary string and store in int array
void decimal_to_binary(int num, int num_b[], int num_b_len);

// Count the binary gap(s) between 1's and store in int array and return max
int get_max_binary_gap(int num_b[], int num_b_len);

int main(int argc, char** argv)
{
    int err_code = is_arg_invalid(argc, argv);
    if (err_code > 0)
    {
        printf("Usage: ./binary <number>\n");
        return err_code;
    }

    int num = atoi(argv[1]);

    int max_binary_gap = 0;
    if (num != 0)
    {
        // The number of 2s + 1 will be the array's length
        int num_b_len = log2(num) + 1;
        int num_b[num_b_len];

        decimal_to_binary(num, num_b, num_b_len);
        max_binary_gap = get_max_binary_gap(num_b, num_b_len);
    }

    printf("Max binary gap is: %i\n", max_binary_gap);
}


// See above for what these functions do

int is_arg_invalid(int argc, char** argv)
{
    if (argc <= 1)
    {
        return 1; // Missing argument
    }

    for (int i = 0, arg_len = strlen(argv[1]); i < arg_len; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            return 2; // Argument contains non-digit character
        }
    }

    return 0; // No error
}

void decimal_to_binary(int num, int num_b[], int num_b_len)
{

    // Lengthy process not needed for 0 and 1 :)
    if (num == 0 || num == 1)
    {
        num_b[0] = num;
    }

    for (int i = num_b_len; i >= 1; i--)
    {
        int count_2s = i - 1;
        int power_2 = exp2(count_2s);

        if (num >= power_2)
        {
            num = num - power_2;
            num_b[count_2s] = 1;
        }
        else // Needed for setting default to 0
        {
            num_b[count_2s] = 0;
        }
    }
}

int get_max_binary_gap(int num_b[], int num_b_len)
{
    // First digit will always be one at this point; default
    int one_pos_cur = num_b_len - 1;
    int one_pos_prev = num_b_len - 1;

    int max_gap = 0;

    for (int i = num_b_len - 2; i >= 0; i -- )
    {
        int gap = 0;

        if (num_b[i] == 1)
        {
            one_pos_prev = one_pos_cur;
            one_pos_cur = i;
            gap = (one_pos_prev - one_pos_cur) - 1;
        }

        if (gap > max_gap)
        {
            max_gap = gap;
        }
    }

    return max_gap;
}
