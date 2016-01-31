#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "StringDoubleMap.h"
#include "StringFunctions.h"
#include "FileIO.h"
#define DOCUMENTATION "StringCreate Documentation\nStringCreate is used to, given a .stl file from StringLearn, create a random string.\nUsage: %s <stlfile> [--stopX] -l length [-p new-ngram-chance]\nIf --stopX is enabled, StringCreate will stop when an X is reached.\n"
#define USAGE "Usage: %s <stlfile> [--stopX] -l length [-p new-ngram-chance]\n"
#define DEFAULT_NEW_NGRAM_CHANCE 0.5

char* stlContents;
double newNgramChance;
int stringLength;
StringDoubleMap ngrams;
int stopX;
void displayHelp(char* argv0)
{
    printf(DOCUMENTATION, argv0);
}

void usageError(char* argv0)
{
    fprintf(stderr, USAGE);
}

double rand01()
{
    return ((double)rand()/RAND_MAX);
}

int randrange(int start, int end)
{
    return (int)(rand01()*(end-start) + start);
}

char nextChar(char* s, int sz)
{
    int possibleNgrams = 0;
    int i;
    char* ngram;
    int ngramLen;
    double probabilitySum = newNgramChance;
    for (i = 0; i < ngrams.index; i++)
    {
        ngram = ngrams.pairs[i].s;
        ngramLen = strlen(ngram);
        if (ngramLen > (sz+1))
            continue;
        if (strEqual(substring(ngram, 0, ngramLen-1), substring(s, sz-ngramLen+1, ngramLen-1)))
            probabilitySum += ngrams.pairs[i].i;

    }

    double selectedNgram = probabilitySum * rand01();
    if (selectedNgram < newNgramChance)
    {
        if (!stopX)
            return (char)randrange(97, 123);
        else
        {
            int n = randrange(97, 124);
            if (n == 123)
                return 'X';
            else
                return (char)n;
        }
    }
    selectedNgram -= newNgramChance;
    double sum = 0;
    for (i = 0; i < ngrams.index; i++)
    {
        ngram = ngrams.pairs[i].s;
        ngramLen = strlen(ngram);
        if (ngramLen > (sz+1))
            continue;
        if (strEqual(substring(ngram, 0, ngramLen-1), substring(s, sz-ngramLen+1, ngramLen-1)))
        {
            sum += ngrams.pairs[i].i;
            if (sum  > selectedNgram)
                return ngram[ngramLen-1];
        }
    }
    return 'a';
}

char* generateString()
{
    char* string;
    int i = 0;
    if (!stopX)
    {
        string = malloc(stringLength+1);
        for (i = 0; i < stringLength; i++)
            string[i] = nextChar(string, i);
        string[stringLength] = 0;
    }
    else
    {
        char c;
        string = malloc(2048);
        while (1)
        {
            c = nextChar(string, i);
            if (c == 'X')
            {
                if (i >= stringLength)
                    break;
                else
                    continue;
            }
            string[i] = c;
            if ((++i) >= 2047)
                break;
        }
        string[strlen(string)-1] = 0;
    }
    return string;
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    int i;

    if (strListIndex(argv, argc, "--help") != -1)
    {
        displayHelp(argv[0]);
        return 0;
    }

    if (argc < 4)
    {
        usageError(argv[0]);
        return 1;
    }

    if (strListIndex(argv, argc, "-p") == argc-1 || strListIndex(argv, argc, "-l") == -1 || strListIndex(argv, argc, "-l") == argc-1)
    {
        usageError(argv[0]);
        return 1;
    }
    stopX = strListIndex(argv, argc, "--stopX") != -1;

    char* stlfilename;
    newNgramChance = DEFAULT_NEW_NGRAM_CHANCE;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
            continue;
        if (strEqual(argv[i-1], "-p"))
            newNgramChance = atof(argv[i]);
        else if (strEqual(argv[i-1], "-l"))
            stringLength = atoi(argv[i]);
        else
            stlfilename = argv[i];
    }
    stlContents = fileContents(stlfilename);
    ngrams = sdmFromString(stlContents);
    printf("%s\n", generateString());

    return 0;

}
