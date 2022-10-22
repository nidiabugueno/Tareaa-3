#ifndef HashMap_h
#define HashMap_h
#define MAP_H


typedef struct Map Map;

typedef struct Pair {
     char * key;
     void * value;
} Pair;

Map * createMap(long capacity);

void insertMap(Map * table, char * key, void * value);

void eraseMap(Map * table, char * key);

Pair * searchMap(Map * table, char * key);

Pair * firstMap(Map * table);

Pair * nextMap(Map * table);

void enlarge(Map * map);

#endif /* HashMap_h */
