/*
** EPITECH PROJECT, 2025
** B-CCP-400-LYN-4-1-panoramix-hugo.cathelain
** File description:
** villager
*/

///////////////////////////////////////////////////////////////////////////////
/// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "panoramix.h"

///////////////////////////////////////////////////////////////////////////////
void *villager_routine(void *arg)
{
    villager_args_t *villager = (villager_args_t *)arg;
    panoramix_t *data = villager->data;
    int fights_left = data->nb_fights;
    int need_to_wake_druid = 0;

    printf("Villager %d: Going into battle!\n", villager->id);
    while (fights_left > 0) {
        pthread_mutex_lock(&data->pot_mutex);
        printf("Villager %d: I need a drink... I see %d servings left.\n",
               villager->id, data->servings_left);
        if (data->servings_left == 0) {
            need_to_wake_druid = 1;
            pthread_mutex_unlock(&data->pot_mutex);
            printf("Villager %d: Hey Pano wake up! We need more potion.\n",
                villager->id);
            sem_post(&data->pot_empty_sem);
            sem_wait(&data->pot_filled_sem);
            pthread_mutex_lock(&data->pot_mutex);
        }
        if (data->servings_left > 0) {
            data->servings_left--;
            pthread_mutex_unlock(&data->pot_mutex);
            if (need_to_wake_druid) {
                need_to_wake_druid = 0;
                sem_post(&data->pot_filled_sem);
            }
            printf("Villager %d: Take that roman scum! Only %d left.\n",
                   villager->id, fights_left - 1);
            fights_left--;
        } else {
            pthread_mutex_unlock(&data->pot_mutex);
            break;
        }
    }
    pthread_mutex_lock(&data->pot_mutex);
    data->villager_left--;
    pthread_mutex_unlock(&data->pot_mutex);
    sem_post(&data->pot_empty_sem);
    printf("Villager %d: I'm going to sleep now.\n", villager->id);
    return NULL;
}
