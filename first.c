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




int main() {

}
