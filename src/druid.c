/*
** EPITECH PROJECT, 2025
** B-CCP-400-LYN-4-1-panoramix-hugo.cathelain
** File description:
** druid
*/

///////////////////////////////////////////////////////////////////////////////
/// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "panoramix.h"

//////////////////////////////////::///////////////////////////////////////////
void *druid_routine(void *arg)
{
    panoramix_t *data = (panoramix_t *)arg;
    int refills_left = data->nb_refills;
    int last_villager = data->villager_left;

    printf("Druid: I'm ready... but sleepy...\n");
    while (refills_left > 0 && last_villager > 0) {
        sem_wait(&data->pot_empty_sem);
        pthread_mutex_lock(&data->pot_mutex);
        if (data->villager_left != last_villager) {
            printf("check here\n");
            last_villager = data->villager_left;
            pthread_mutex_unlock(&data->pot_mutex);
            continue;
        }
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make %d more refills after this one.\n", refills_left - 1);
        data->servings_left = data->pot_size;
        refills_left--;
        pthread_mutex_unlock(&data->pot_mutex);
        sem_post(&data->pot_filled_sem);
    }
    if (data->villager_left > 0) {
        printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    }
    for (int i = 0; i < data->nb_villagers; i++) {
        sem_post(&data->pot_filled_sem);
    }
    return NULL;
}
