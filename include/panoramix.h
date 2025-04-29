/*
** EPITECH PROJECT, 2025
** B-CCP-400-LYN-4-1-panoramix-hugo.cathelain
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

///////////////////////////////////////////////////////////////////////////////
/// Dependencies
///////////////////////////////////////////////////////////////////////////////
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <string.h>

typedef struct {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int servings_left;
    int is_druid_sleeping;
    int villager_left;
    pthread_mutex_t pot_mutex;
    pthread_mutex_t druid_mutex;
    sem_t pot_empty_sem;
    sem_t pot_filled_sem;
} panoramix_t;

typedef struct {
    int id;
    panoramix_t *data;
} villager_args_t;

int panoramix_core(int argc, char **argv);

void *druid_routine(void *arg);
void *villager_routine(void *arg);

#endif /* !PANORAMIX_H_ */
