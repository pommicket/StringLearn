#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "StringFunctions.h"
#include "FileIO.h"
#include "StringIntMap.h"
#define DEFAULT_NGRAM_LENGTH 5
#define DEFAULT_POWER 0.75

char* stlContents;
double power;
double rating;

void displayHelp()
{
    //Display StringLearn documentation
    printf("StringLearn documentation\nStringLearn usage: StringLearn <string> -r <rating> -s <stlfile>\n");
}

int usageError(char* argv0)
{
    fprintf(stderr, "Error. Usage: %s <string> -r <rating> -s <stlfile>\n", argv0);
}

double sigmoid(double z)
{
    return 1.0/(1.0+exp(-z));
}

double inverseSigmoid(double z)
{
    if (z == 1)
        return 10000;
    if (z == 0)
    	return -10000;
    return log(z/(1.0-z));
}

double benefitOf(int usage)
{
    return rating*pow(usage, power);
}

double newProbability(double currentProbability, int usage)
{
    return sigmoid(benefitOf(usage)+inverseSigmoid(currentProbability));
}

int main(int argc, char** argv)
{
    int i;
    if (strListIndex(argv, argc, "--help") != -1)
    {
        displayHelp();
        return 0;
    }

    int dashrIndex = strListIndex(argv, argc, "-r");
    int dashsIndex = strListIndex(argv, argc, "-s");
    int dashlIndex = strListIndex(argv, argc, "-l");
    int dashpIndex = strListIndex(argv, argc, "-p");
    if (argc < 6 || dashrIndex == -1 || dashsIndex == -1 || dashrIndex == argc-1 || dashsIndex == argc-1 || dashlIndex == argc-1 || dashpIndex == argc-1)
        usageError(argv[0]);



    char* string;
    char* stlFilename;
    int ngramLength = DEFAULT_NGRAM_LENGTH;
    power = DEFAULT_POWER;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && !strEqual(argv[i-1], "-r"))
            continue;

        if (strEqual(argv[i-1], "-r"))
        {
            rating = atof(argv[i]);
        }
        else if (strEqual(argv[i-1], "-s"))
            stlFilename = argv[i];

        else if (strEqual(argv[i-1], "-l"))
            ngramLength = atoi(argv[i]);

        else if (strEqual(argv[i-1], "-p"))
            power = atof(argv[i]);

        else
            string = argv[i];
    }
    if (rating == 0)
        return 0;


    stlContents = fileContents(stlFilename);

    StringIntMap usage = newStringIntMap();
    int slen = strlen(string);

    int ngramLen;

    char* ngram;
    for (ngramLen = 1; ngramLen <= ngramLength; ngramLen++)
    {
        for (i = 0; i <= slen-ngramLen; i++)
        {
            ngram = substring(string, i, ngramLen);

            if (mapContains(usage, ngram))
            {
                mapInc(&usage, ngram);
                continue;
            }
            mapAdd(&usage, ngram, 1);
        }
    }

    int currentUsage;
    double np, prob;

    for (i = 0; i < usage.index; i++)
    {

        ngram = usage.pairs[i].s;

        currentUsage = usage.pairs[i].i;
        prob = getProbability(stlContents, ngram);
        np = newProbability(prob, currentUsage);
        stlContents = replaceProbability(stlContents, ngram, np);
    }

    fileWrite(stlFilename, stlContents);

    return 0;

}
