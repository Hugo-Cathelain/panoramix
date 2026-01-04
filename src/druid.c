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

static void druid_final_actions(panoramix_t *data)
{
    if (data->villager_left > 0) {
        printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    }
}

///////////////////////////////////////////////////////////////////////////////
static void druid_speach(int nb)
{
    printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware ");
    printf("I can only make %d more refills after this one.\n", nb - 1);
}

///////////////////////////////////////////////////////////////////////////////
void *druid_routine(void *arg)
{
    panoramix_t *data = (panoramix_t *)arg;
    int last_villager = data->villager_left;

    printf("Druid: I'm ready... but sleepy...\n");
    while (data->nb_refills > 0 && last_villager > 0) {
        sem_wait(&data->pot_empty_sem);
        pthread_mutex_lock(&data->pot_mutex);
        if (data->villager_left != last_villager) {
            last_villager = data->villager_left;
            pthread_mutex_unlock(&data->pot_mutex);
            continue;
        }
        druid_speach(data->nb_refills);
        data->servings_left = data->pot_size;
        data->nb_refills--;
        pthread_mutex_unlock(&data->pot_mutex);
        sem_post(&data->pot_filled_sem);
    }
    druid_final_actions(data);
    return NULL;
}
