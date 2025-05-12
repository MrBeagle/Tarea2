#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

typedef struct Node {
    char *key;
    void *value;
    struct Node *next;
} Node;

struct Map {
    Node **buckets;
    int capacity;
    Node *current;
};

unsigned int hash(const char *key, int capacity) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash *31) + *key++;
    }
    return hash % capacity;
}

Map *createMap(int capacity) {
    Map *map = (Map *)malloc(sizeof(Map));
    map->buckets = (Node **)calloc(capacity, sizeof(Node *));
    map->capacity = capacity;
    map->current = NULL;
    return map;
}

void insertMap(Map *map, const char *key, void *value) {
    unsigned int index = hash(key, map->capacity);
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = value;
    node->next = map->buckets[index];
    map->buckets[index] = node;
}

void *searchMap(Map *map, const char *key) {
    unsigned int index = hash(key, map->capacity);
    Node *node = map->buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            map->current = node;
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void eraseMap(Map *map, const char *key) {
    unsigned int index = hash(key, map->capacity);
    Node *node = map->buckets[index];
    Node *prev = NULL;
    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                map->buckets[index] = node->next;
            }
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void *firstMap(Map *map) {
    for (int i = 0; i < map->capacity; i++) {
        if (map->buckets[i]) {
            map->current = map->buckets[i];
            return map->current->value;
        }
    }
    return NULL;
}

void *nextMap(Map *map) {
    if (map->current && map->current->next) {
        map->current = map->current->next;
        return map->current->value;
    }
    unsigned int index = hash(map->current->key, map->capacity) + 1;
    for (int i = index; i < map->capacity; i++) {
        if (map->buckets[i]) {
            map->current = map->buckets[i];
            return map->current->value;
        }
    }
    return NULL;
}