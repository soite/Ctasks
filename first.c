#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLen 100
#define MaxTask 100
#define FileName "tasks.txt"

typedef struct{
    char description[MaxLen];
    int done;
} Task;

Task tasks[MaxTask];
int task_cnt = 0;

void load_task() {
    FILE *file = fopen(FileName, "r");
    if (file == NULL) {
        return;
    }
    while(fscanf(file, "%d;%[^\n]\n", &tasks[task_cnt].done, tasks[task_cnt].description) != EOF) {
        task_cnt++;
    }
    fclose(file);
}

void save_task() {
    FILE *file = fopen(FileName, "w");
    if(file == NULL) {
        printf("ERROR file is empty! \n");
        return;
    }
    for(int i = 0; i < task_cnt; i++) {
        fprintf(file,"%d;%s\n", tasks[i].done, tasks[i].description);
    }
    fclose(file);
}
void add_task() {
    if(task_cnt >= MaxLen) {
        printf("List is full!");
        return;
    }
    printf("Enter your task description: ");
    getchar();
    fgets(tasks[task_cnt].description,MaxLen,stdin);
    tasks[task_cnt].description[strcspn(tasks[task_cnt].description,"\n")] = '\0';
    tasks[task_cnt].done = 0;
    task_cnt++;
    save_task();
    printf("Task added! \n");
}

void view_task() {
   printf("\n--- To-Do List ---\n");
   for(int i = 0; i < task_cnt; i++) {
       printf("%d. [%c] %s\n",i + 1, tasks[i].done ? 'X' : ' ', tasks[i].description);
   }
   printf("------------------\n");
}

void mark_done() {
    int num;
    view_task();
    printf("Enter task number to mark as done: ");
    scanf("%d", &num);
    if(num < 1 || num > task_cnt) {
       printf("Your input number is invalid\n");
       return;
    }
    tasks[num - 1].done = 1;
    save_task();
    printf("Your task marked as done! \n");
}

void delete_task() {
    int num;
    view_task();
    printf("Enter task number to delete: ");
    scanf("%d", &num);
    if(num < 1 || num > task_cnt) {
       printf("Your input number is invalid\n");
       return;
    }
    for(int i = num - 1; i < task_cnt - 1; i++) {
       tasks[i] = tasks[i + 1];
    }
    task_cnt--;
    save_task();
    printf("Your task is deleted!\n");
}


int main() {
    int choice;
    load_task();
    do {
        printf("\nTo-Do List Manager\n");
        printf("1. View Tasks\n");
        printf("2. Add Task\n");
        printf("3. Mark Task as Done\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: view_task(); break;
            case 2: add_task(); break;
            case 3: mark_done(); break;
            case 4: delete_task(); break;
            case 5: printf("Goodbye!\n"); break;
            default: printf("Invalid option.\n");
        }

    } while (choice != 5);
    return 0;

}
