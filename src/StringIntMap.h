typedef struct StringIntPair
{
    char* s;
    int i;
} StringIntPair;

typedef struct StringIntMap
{
    int index;
    int capacity;
    StringIntPair* pairs;
} StringIntMap;

StringIntMap newStringIntMap()
{
    StringIntMap sim;
    StringIntPair sip;
    StringIntPair* sipp = &sip;

    sim.index = 0;
    sim.capacity = 0;
    sim.pairs = sipp;
    return sim;
}

void resize(StringIntMap* sim, int capacity)
{
    int old_capacity = sim->capacity;
    sim->capacity = capacity;
    StringIntPair* oldPairs = sim->pairs;
    StringIntPair* newPairs = malloc(sizeof(StringIntPair)*capacity);
    int i;
    for (i = 0; i < old_capacity; i++)
        newPairs[i] = oldPairs[i];

    sim->pairs = newPairs;
}

void mapAdd(StringIntMap* sim, char* s, int i)
{
    if (sim->index >= sim->capacity)
    {
        if (sim->capacity == 0)
            resize(sim, 1);
        else
            resize(sim, sim->capacity*2);
    }

    StringIntPair sip;
    sip.i = i;
    sip.s = s;
    sim->pairs[sim->index++] = sip;

}

void mapSet(StringIntMap* sim, char* s, int i)
{
    int x;
    for (x = 0; x < sim->index; x++)
    {
        if (strEqual(sim->pairs[x].s, s))
        {
            sim->pairs[x].i = i;
            return;
        }
    }
}

void mapInc(StringIntMap* sim, char* s)
{
    int i;
    for (i = 0; i < sim->index; i++)
    {
        if (strEqual(sim->pairs[i].s, s))
        {
            sim->pairs[i].i++;
            return;
        }
    }
}

int mapAt(StringIntMap sim, char* s)
{
    int i;
    for (i = 0; i < sim.index; i++)
        if (strEqual(sim.pairs[i].s, s))
            return sim.pairs[i].i;

    return -1;
}
void printMap(StringIntMap sim)
{
    int i;
    for (i = 0; i < sim.index; i++)
        printf("%s:%d\n", sim.pairs[i].s, sim.pairs[i].i);
    printf("\n\n");
}

int mapContains(StringIntMap sim, char* s)
{
    int i;
    for (i = 0; i < sim.index; i++)
        if (strEqual(sim.pairs[i].s, s))
            return 1;

    return 0;
}
