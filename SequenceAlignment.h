#ifndef _MY_EDIT_DISTANCE_H_
#define _MY_EDIT_DISTANCE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

/*------------------------------------------------------------------------------
    SequenceAlignment: find the minimum number of edits that converts one DNA
    structure to another DNA structure.

        str1: the first input string, has an alphabet of [A, C, G, T]
        str2: the second input string, has an alphabet of [A, C, G, T]
        operations: the list of edit operations as string:
            [M] for match, [C] for convert, [I] for insert, [D] for delete

        returns the number of edit distance
------------------------------------------------------------------------------*/
unsigned int SequenceAlignment(
    const std::string &str1,
    const std::string &str2,
    std::string &operations)
{
    int str1Len = str1.length();
    int str2Len = str2.length();

    std::vector<std::vector<int>> memoizationMatrix(str1Len + 1, std::vector<int>(str2Len + 1, 0));

    // First row initialization
    for (int j = 0; j <= str2Len; j++)
    {
        memoizationMatrix[0][j] = j;
    }

    // First column initialization
    for (int i = 0; i <= str1Len; i++)
    {
        memoizationMatrix[i][0] = i;
    }

    for (int i = 1; i <= str1Len; i++)
    {
        for (int j = 1; j <= str2Len; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                memoizationMatrix[i][j] = memoizationMatrix[i - 1][j - 1];
            }
            else
            {
                memoizationMatrix[i][j] = 1 + std::min({memoizationMatrix[i - 1][j - 1], memoizationMatrix[i][j - 1], memoizationMatrix[i - 1][j]});
            }
        }
    }

    std::string op;

    // Trace Back Operations
    int i = str1Len;
    int j = str2Len;

    // Note: There could be multiple ties. The preference order opted was delete, insert, match, change
    while (i > 0 || j > 0)
    {
        if (i > 0 && memoizationMatrix[i][j] == memoizationMatrix[i - 1][j] + 1)
        {
            operations.append(1, 'D');
            --i;
        }

        else if (j > 0 && memoizationMatrix[i][j] == memoizationMatrix[i][j - 1] + 1)
        {
            operations.append(1, 'I');
            --j;
        }

        else if (i > 0 && j > 0 && str1[i - 1] == str2[j - 1])
        {
            operations.append(1, 'M');
            --i;
            --j;
        }

        else if (i > 0 && j > 0 && memoizationMatrix[i][j] == memoizationMatrix[i - 1][j - 1] + 1)
        {
            operations.append(1, 'C');
            --i;
            --j;
        }
    }

    std::reverse(operations.begin(), operations.end());

    // operations = op;

    return memoizationMatrix[str1Len][str2Len];
}

/*------------------------------------------------------------------------------
    PrintAlgnment: prints the two aligned sequences and the corresponding operations
        in the alignment form to stdout

        str1: the first input string, has an alphabet of [A, C, G, T]
        str2: the second input string, has an alphabet of [A, C, G, T]
        operations: the list of edit operations as string:
            [M] for match, [C] for convert, [I] for insert, [D] for delete

    The alignment output should contain three rows:
        The first row corresponds to the first sequence with gaps
        The second row corresponds to the list of operations
        The third row corresponds to the second sequence with gaps
        A match [M] operation should be represented using '|'
        A convert [C] operation should be represented using '*'
        Insert and delete operations should be represented using ' ' (empty space)

    Example:
        str1: "ACAACC"
        str2: "CAAAAC"
        operations: "DMMMICM"

        output alignment:
        ACAA-CC
         ||| *|
        -CAAAAC
------------------------------------------------------------------------------*/
void PrintAlignment(
    const std::string &str1,
    const std::string &str2,
    const std::string &operations)
{
    std::string str_1 = str1;
    std::string str_2 = str2;
    std::string op;

    for (int i = 0; i < operations.length(); i++)
    {
        if (operations[i] == 'D')
        {
            str_2.insert(i, 1, '-');
            op.append(1, ' ');
        }
        else if (operations[i] == 'I')
        {
            str_1.insert(i, 1, '-');
            op.append(1, ' ');
        }
        else if (operations[i] == 'M')
        {
            op.append(1, '|');
        }
        else
        {
            op.append(1, '*');
        }
    }
    std::cout << str_1 << std::endl;
    std::cout << op << std::endl;
    std::cout << str_2 << std::endl;
}

#endif
