/*
** EPITECH PROJECT, 2025
** B-CCP-400-LYN-4-1-panoramix-hugo.cathelain
** File description:
** core
*/

///////////////////////////////////////////////////////////////////////////////
/// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "panoramix.h"

///////////////////////////////////////////////////////////////////////////////
static panoramix_t get_data(int argc, char **argv)
{
    panoramix_t data;

    argc = argc;
    data.nb_villagers = atoi(argv[1]);
    data.pot_size = atoi(argv[2]);
    data.nb_fights = atoi(argv[3]);
    data.nb_refills = atoi(argv[4]);
    data.servings_left = data.pot_size;
    data.villager_left = data.nb_villagers;
    data.is_druid_sleeping = 1;
    return data;
}

///////////////////////////////////////////////////////////////////////////////
static int init_mutex(panoramix_t *data)
{
    if (pthread_mutex_init(&data->pot_mutex, NULL) != 0 ||
        pthread_mutex_init(&data->druid_mutex, NULL) != 0 ||
        sem_init(&data->pot_empty_sem, 0, 0) != 0 ||
        sem_init(&data->pot_filled_sem, 0, 0) != 0) {
        fprintf(stderr, "Error initializing synchronization objects\n");
        return (84);
    }
    return (0);
}

///////////////////////////////////////////////////////////////////////////////
int panoramix_core(int argc, char **argv)
{
    pthread_t druid_thread;
    pthread_t *villager_threads;
    villager_args_t *villager_args;
    panoramix_t data = get_data(argc, argv);

    if (init_mutex(&data) != 0) {;
        return 84;
    }
    villager_threads = malloc(sizeof(pthread_t) * data.nb_villagers);
    if (!villager_threads) {
        fprintf(stderr, "Memory allocation error\n");
        return 84;
    }
    villager_args = malloc(sizeof(villager_args_t) * data.nb_villagers);
    if (!villager_args) {
        fprintf(stderr, "Memory allocation error\n");
        free(villager_threads);
        return 84;
    }
    if (pthread_create(&druid_thread, NULL, druid_routine, &data) != 0) {
        fprintf(stderr, "Error creating druid thread\n");
        free(villager_threads);
        free(villager_args);
        return 84;
    }
    for (int i = 0; i < data.nb_villagers; i++) {
        villager_args[i].id = i;
        villager_args[i].data = &data;
        if (pthread_create(&villager_threads[i], NULL, villager_routine, &villager_args[i]) != 0) {
            fprintf(stderr, "Error creating villager thread\n");
            free(villager_threads);
            free(villager_args);
            return 84;
        }
    }
    pthread_join(druid_thread, NULL);
    for (int i = 0; i < data.nb_villagers; i++) {
        pthread_join(villager_threads[i], NULL);
    }
    pthread_mutex_destroy(&data.pot_mutex);
    pthread_mutex_destroy(&data.druid_mutex);
    sem_destroy(&data.pot_empty_sem);
    sem_destroy(&data.pot_filled_sem);
    free(villager_threads);
    free(villager_args);
    return 0;
}
