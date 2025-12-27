#include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <semaphore.h>
 #include <unistd.h>
 #include <time.h>

 #define BUF_SIZE 5
 #define P_COUNT 3
 #define C_COUNT 4

 typedef struct {
 int data[BUF_SIZE];
 int write_pos;
 int read_pos;
 sem_t slots;
 sem_t items;
 sem_t lock;
 } shared_buffer;

 shared_buffer buf;
 int global_item = 1;
 time_t base_time;


 void show_buffer() {
 printf("Buffer State: [ ");
 for (int i = 0; i < BUF_SIZE; i++) {
 printf("%d ", buf.data[i]);
 }
 printf("]\n");
 }


 void* produce(void* arg) {
 int pid = *((int*)arg);

 while (1) {
 sem_wait(&buf.slots);
 sem_wait(&buf.lock);

 int value = global_item++;
 buf.data[buf.write_pos] = value;

 printf("[T+%lds] Producer %d -> item %d (index %d)\n",
 time(NULL) - base_time, pid, value, buf.write_pos);

 buf.write_pos = (buf.write_pos + 1) % BUF_SIZE;
 show_buffer();

 sem_post(&buf.lock);
 sem_post(&buf.items);

 sleep(8);
 }
 return NULL;
 }


 void* consume(void* arg) {
 int cid = *((int*)arg);

 while (1) {
 sem_wait(&buf.items);
 sem_wait(&buf.lock);

 int value = buf.data[buf.read_pos];
 buf.data[buf.read_pos] = 0;

 printf("[T+%lds] Consumer %d <- item %d (index %d)\n",
 time(NULL) - base_time, cid, value, buf.read_pos);

 buf.read_pos = (buf.read_pos + 1) % BUF_SIZE;
 show_buffer();

 sem_post(&buf.lock);
 sem_post(&buf.slots);

 sleep(8);
 }
 return NULL;
 }

 int main() {
 pthread_t producers[P_COUNT];
 pthread_t consumers[C_COUNT];

 base_time = time(NULL);

 printf("System started\n");
 printf("Producers: %d | Consumers: %d\n\n", P_COUNT, C_COUNT);

 buf.write_pos = 0;
 buf.read_pos = 0;

 for (int i = 0; i < BUF_SIZE; i++)
 buf.data[i] = 0;

 sem_init(&buf.slots, 0, BUF_SIZE);
 sem_init(&buf.items, 0, 0);
 sem_init(&buf.lock, 0, 1);

 int p_ids[P_COUNT];
 int c_ids[C_COUNT];

 for (int i = 0; i < P_COUNT; i++) {
 p_ids[i] = i + 1;
 pthread_create(&producers[i], NULL, produce, &p_ids[i]);
 }

 for (int i = 0; i < C_COUNT; i++) {
 c_ids[i] = i + 1;
 pthread_create(&consumers[i], NULL, consume, &c_ids[i]);
 }


 for (int i = 0; i < P_COUNT; i++)
 pthread_join(producers[i], NULL);

 for (int i = 0; i < C_COUNT; i++)
 pthread_join(consumers[i], NULL);

 return 0;
 }
