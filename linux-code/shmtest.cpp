#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEGPERMS (0644)
#define MESSAGE "Success!"
#define MSG_SIZE 9

const char* path = "shmtest.cpp";
char magic = 'M';

void child_code(key_t shmkey) {
	char message[MSG_SIZE] = MESSAGE;
	void* shm_vaddr; // Address of segment for process
	int seg_id; // Shared 'segment' id

	seg_id = shmget(shmkey, MSG_SIZE, SEGPERMS | IPC_CREAT);
	if(seg_id == -1) {
		printf("Child: Error creating shared memory segment.\n");
		printf("%s.\n", strerror(errno)); 
		exit(1);
	}

	shm_vaddr = shmat(seg_id, NULL, 0);
	if(shm_vaddr == (void*) -1) {
		printf("Child: Error mapping shared memory segment into addrspace\n");
		printf("%s.\n", strerror(errno));
		exit(1);
	}

	memcpy(shm_vaddr, message, MSG_SIZE);

	shmdt(shm_vaddr);
}

void parent_code(key_t shmkey) {
	char message[MSG_SIZE];
	void* shm_vaddr;
	int seg_id;

	seg_id = shmget(shmkey, MSG_SIZE, SEGPERMS);
	if(seg_id == -1) {
		printf("Parent: Error getting shared memory segment.\n");
		printf("%s.\n", strerror(errno)); 
		exit(1);
	}

	shm_vaddr = shmat(seg_id, NULL, 0);
	if(shm_vaddr == (void*) -1) {
		printf("Parent: Error mapping shared memory segment into addrspace\n");
		printf("%s.\n", strerror(errno));
		exit(1);
	}

	memcpy(message, shm_vaddr, MSG_SIZE);
	printf("Received message: %s\n", message);

	shmdt(shm_vaddr);
}

int main(int argc, char** argv) {
	pid_t child_pid;
	key_t shmkey;
	int child_status;

	// Generate a unique key
	shmkey = ftok(path, (int) magic); 
	printf("Shared memory key: %x\n", shmkey);

	child_pid = fork();
	if(child_pid == 0) {
		child_code(shmkey);		
	} else if(child_pid > 0) {
		waitpid(child_pid, &child_status, 0);
		
		if(child_status == 0) {
			parent_code(shmkey);
		}
	} else {
		printf("Error occurred while forking!\n");
	}

	exit(0);
}
