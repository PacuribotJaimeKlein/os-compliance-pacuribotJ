#include <stdio.h>
 #include <pthread.h>
 #include <semaphore.h>
 #include <unistd.h>
 
 #define NUM_PHILOSOPHERS 5
 
 pthread_t philosophers[NUM_PHILOSOPHERS];
 sem_t chopsticks[NUM_PHILOSOPHERS];
 
 void think(int id);
 void eat(int id);
 void pick_up_chopsticks(int id);
 void put_down_chopsticks(int id);
 
 void* philosopher(void* num) {
 int id = *(int*)num;
 
 usleep(id * 100000); 
 
 while (1) {
 think(id);
 pick_up_chopsticks(id);
 eat(id);
 put_down_chopsticks(id);
 }
 return NULL;
 }
 
 void think(int id) {
 printf("Philosopher %d is thinking\n", id + 1);
 sleep(1);
 }
 
 void eat(int id) {
 printf("Philosopher %d is eating\n", id + 1);
 sleep(1);
 }
 
 void pick_up_chopsticks(int id) {
 int philosopher_number = id + 1; 
 if (philosopher_number % 2 == 1) {
 sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]); 
 sem_wait(&chopsticks[id]); 
 } else {
 sem_wait(&chopsticks[id]); 
 sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]); 
 }
 
 printf("Philosopher %d picked up chopsticks\n", philosopher_number);
 }
 
 void put_down_chopsticks(int id) {
 int philosopher_number = id + 1;
 
 sem_post(&chopsticks[id]);
 sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
 printf("Philosopher %d put down chopsticks\n", philosopher_number);
 }
 
 int main() {
 int ids[NUM_PHILOSOPHERS];
 
 for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
 sem_init(&chopsticks[i], 0, 1);
 }
 
 for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
 ids[i] = i;
 pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
 usleep(100000); 
 }
 
 for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
 pthread_join(philosophers[i], NULL);
 }
 
 for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
 sem_destroy(&chopsticks[i]);
 }
 
 return 0;
 }
