#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
  pthread_mutex_t pmutex;
  unsigned char data[20];
} sharedmemory;

#define SHAREDMEMORY "shm_file"
int main() {
  int fd;
  fd = shm_open(SHAREDMEMORY, O_RDWR | O_CREAT, 0777);
  ftruncate(fd, 1024);
  sharedmemory *ptr = (sharedmemory *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  memset(ptr, 0, sizeof(sharedmemory));
  close(fd);  // close fd firstly
  if (ptr == MAP_FAILED) {
    printf("open shared failed \n");
    exit(0);
  }
  pthread_mutexattr_t mutexattr;
  pthread_mutexattr_init(&mutexattr);
  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL);
#ifdef _POSIX_THREAD_PROCESS_SHARED
  pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
#else
#error this implementation does not support _POSIX_THREAD_PROCESS_SHARED
#endif
  pthread_mutex_init(&ptr->pmutex, &mutexattr);
  pthread_mutexattr_destroy(&mutexattr);

  pthread_mutex_lock(&ptr->pmutex);
  for (unsigned char i = 0; i < 10; i++) {
    ptr->data[i] = i;
    printf("%d ", ptr->data[i]);
  }
  pthread_mutex_unlock(&ptr->pmutex);
  printf("end\n");
  getchar();
  pthread_mutex_destroy(&ptr->pmutex);
  munmap(ptr, 1024);
  shm_unlink(SHAREDMEMORY);
  return 0;
}
