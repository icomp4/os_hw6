#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int sharedData = 0; // the data we will be reading/writing
pthread_mutex_t mutex; // the mutex to lock the data

// the write function thread1 will call
void* WriteToData(void* arg) {

    // write 5 random numbers
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex);
        sharedData = rand() % 100;
        printf("wrote value %d\n", sharedData);
        pthread_mutex_unlock(&mutex); // unlock the mutex
        sleep(1);
    }

    return NULL;
}

// the read function thread2 will call
void* ReadFromData(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex); // lock the data so the writer cant write until reading is finished

        printf("read value %d\n", sharedData);

        pthread_mutex_unlock(&mutex); // unlock the data
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t thead1; // the writer thread
    pthread_t thread2; // the reader thread

    pthread_mutex_init(&mutex, NULL); // init the mutex

    printf(".....starting threads.....\n");

    // spawn our threads
    pthread_create(&thead1, NULL, WriteToData, NULL);
    pthread_create(&thread2, NULL, ReadFromData, NULL);

    pthread_join(thead1, NULL);
    pthread_join(thread2, NULL);

    printf(".....all threads finished.....\n");

    return 0;
}
