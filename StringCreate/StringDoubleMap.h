typedef struct StringDoublePair
{
    char* s;
    double i;
} StringDoublePair;

typedef struct StringDoubleMap
{
    int index;
    int capacity;
    StringDoublePair* pairs;
} StringDoubleMap;

StringDoubleMap newStringDoubleMap()
{
    StringDoubleMap sdm;
    StringDoublePair sdp;
    StringDoublePair* sdpp = &sdp;

    sdm.index = 0;
    sdm.capacity = 0;
    sdm.pairs = sdpp;
    return sdm;
}

void resize(StringDoubleMap* sdm, int capacity)
{
    int old_capacity = sdm->capacity;
    sdm->capacity = capacity;
    StringDoublePair* oldPairs = sdm->pairs;
    StringDoublePair* newPairs = malloc(sizeof(StringDoublePair)*capacity);
    int i;
    for (i = 0; i < old_capacity; i++)
        newPairs[i] = oldPairs[i];

    sdm->pairs = newPairs;
}

void mapAdd(StringDoubleMap* sdm, char* s, double i)
{
    if (sdm->index >= sdm->capacity)
    {
        if (sdm->capacity == 0)
            resize(sdm, 1);
        else
            resize(sdm, sdm->capacity*2);
    }

    StringDoublePair sdp;
    sdp.i = i;
    sdp.s = s;
    sdm->pairs[sdm->index++] = sdp;

}

void mapSet(StringDoubleMap* sdm, char* s, double i)
{
    int x;
    for (x = 0; x < sdm->index; x++)
    {
        if (strEqual(sdm->pairs[x].s, s))
        {
            sdm->pairs[x].i = i;
            return;
        }
    }
}

void mapInc(StringDoubleMap* sdm, char* s)
{
    int i;
    for (i = 0; i < sdm->index; i++)
    {
        if (strEqual(sdm->pairs[i].s, s))
        {
            sdm->pairs[i].i++;
            return;
        }
    }
}

int mapAt(StringDoubleMap sdm, char* s)
{
    int i;
    for (i = 0; i < sdm.index; i++)
        if (strEqual(sdm.pairs[i].s, s))
            return sdm.pairs[i].i;

    return -1;
}
void printMap(StringDoubleMap sdm)
{
    int i;
    for (i = 0; i < sdm.index; i++)
        printf("%s:%f\n", sdm.pairs[i].s, sdm.pairs[i].i);
    printf("\n\n");
}

int mapContains(StringDoubleMap sdm, char* s)
{
    int i;
    for (i = 0; i < sdm.index; i++)
        if (strEqual(sdm.pairs[i].s, s))
            return 1;

    return 0;
}
