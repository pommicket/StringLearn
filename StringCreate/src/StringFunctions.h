int strEqual(char* a, char* b)
{
    //Wether string a is equal to string b
    if (strlen(a) != strlen(b))
        return 0;
    int i;
    for (i = 0; i < strlen(a); i++)
        if (a[i] != b[i])
            return 0;

    return 1;
}

int count(char* a, char c)
{
    //The number of occurences of c in a
    int i, co = 0;
    for (i = 0; i < strlen(a); i++)
        if (a[i] == c)
            co++;

}


char* copy(char* s)
{
    char* c = malloc(strlen(s));
    int i;
    for (i = 0; i < strlen(s); i++)
        c[i] = s[i];
    return c;
}

char* substring(char* s, int start, int length)
{
    //A substring of s in [start,end)
    if (length <= 0)
        return "";
    char* sub = malloc(length+1);
    memcpy(sub, &s[start], length);
    sub[length] = '\0';
    return sub;
}

int indexOf(char* s, char* sub, int start, int end)
{
    //Index of sub in s in [start, end)

    char *result = strstr(s, sub);
    int position = result - s;
    int substringLength = strlen(s) - position;
    return position;
}

int indexOfChar(char* s, char c, int start, int end)
{
    //Index of c in s in [start, end) -1 if no occurences
    int i;
    for (i = start; i < end; i++)
        if (s[i] == c)
            return i;
    return -1;
}

int strListIndex(char** strlist, int strlistlen, char* str)
{
    int i;
    for (i = 0; i < strlistlen; i++)
        if (strEqual(strlist[i], str))
            return i;
    return -1;
}


char* addStrings(char* a, char* b)
{
    int alen = strlen(a);
    int blen = strlen(b);
    char* sum = malloc(alen+blen+1);
    int i;
    for (i = 0; i < alen; i++)
        sum[i] = a[i];
    for (i = alen; i < alen+blen; i++)
        sum[i] = b[i-alen];
    sum[alen+blen] = 0;
    return sum;
}

char* doubleToString(double d)
{
    char* x = malloc(64);
    sprintf(x, "%f", d);
    return x;
}


StringDoublePair sdpFromString(char* s)
{
    int colonIndex = indexOfChar(s, ':', 0, strlen(s));
    char* s1 = substring(s, 0, colonIndex);
    char* s2 = substring(s, colonIndex+1, strlen(s));
    double d = atof(s2);
    StringDoublePair sdp;
    sdp.i = d;
    sdp.s = s1;
    return sdp;

}

StringDoubleMap sdmFromString(char* s)
{
    int end, index = 0;
    StringDoubleMap sdm = newStringDoubleMap();

    while (1)
    {
        end = indexOfChar(s, '\n', index, strlen(s));
        if (end < 0)
            end = strlen(s);
        char* line = substring(s, index, end-index);
        StringDoublePair sdp = sdpFromString(line);

        mapAdd(&sdm, sdp.s, sdp.i);
        if (end == strlen(s))
            break;
        index = end+1;
    }

    return sdm;
}


double getProbability(char* s, char* ngram)
{
    int slen = strlen(s);
    int ngIndex = indexOf(s, addStrings(ngram, ":"), 0, slen);
    if (ngIndex < 0)
        return 0.5;
    ngIndex += strlen(ngram)+1;
    int endingIndex = indexOfChar(s, '\n', ngIndex, slen);
    if (endingIndex == -1)
        endingIndex = strlen(s);
    double p;
    char* sp = substring(s, ngIndex, endingIndex);
    p = atof(sp);
    free(sp);
    return p;
}

char* replaceProbability(char* s, char* ngram, double newP)
{
    int slen = strlen(s);
    char* withColon =  addStrings(ngram, ":");
    int ngIndex = indexOf(s, withColon, 0, slen);
    if (ngIndex < 0)
        return addStrings(addStrings(s, addStrings("\n", withColon)), doubleToString(newP));
    ngIndex += strlen(ngram)+1;
    int endingIndex = indexOfChar(s, '\n', ngIndex, slen);
    if (endingIndex == -1)
        endingIndex = slen;

    char* beforeNG = substring(s, 0, ngIndex);
    char* afterNG = substring(s, endingIndex, slen);
    char* newNG = doubleToString(newP);
    char* bngng = addStrings(beforeNG, newNG);


    char* newS = addStrings(bngng, afterNG);
    return newS;
}
