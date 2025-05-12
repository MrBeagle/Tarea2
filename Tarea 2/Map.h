#ifndef MAP_H
#define MAP_H

typedef struct Map Map;

Map *createMap(int capacity);
void insertMap(Map *map, const char *key, void *value);
void *searchMap(Map *map, const char *key);
void eraseMap(Map *map, const char *key);
void *firstMap(Map *map);
void *nextMap(Map *map);

#endif