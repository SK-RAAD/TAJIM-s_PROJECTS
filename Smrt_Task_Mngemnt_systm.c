#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TASKS 100
#define TAKS_FILE "tasks.bin"

typedef struct{
 int id;
 char name[50];
 char description[200];
 char category[20];
 char dueDate[20];  //2025-04-10
 int priority;      //lower=higher priority
 int completed;     //0=pending, 1=done
}Task;
Task tasks[MAX_TASKS];
int taskcount=0;
int nextID=1;
//prototypes
void loadtasks();
void savetasks();
void addTask();
void displayTasks();
void updateTask();
void deleteTask();
void searchTasks();
void sortTasksByDueDate();
void pauseAndClear();

int main(){
loadtasks();
 printf("\e[1;33m");
 printf("Welcome to the Simple Task Manager!\n");
 printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 printf("\e[0m");
int choice;
 while(1){
    printf("\e[4;32m");
    printf("\n=== Simple Task Manager Menu ===\n");
    printf("\e[0m");
    printf("1. Add Task\n");
    printf("2. Display Tasks\n");
    printf("3. Update Task\n");
    printf("4. Delete Task\n");
    printf("5. Search Tasks\n");
    printf("6. Sort Tasks by Due Date\n");
    printf("7. Exit\n");
    printf("\e[0;31m");
    printf("Enter choice: ");
    printf("\e[0m");
    scanf("%d", &choice);
    getchar();
 switch(choice){
    case 1:
    addTask();
    break;
    case 2:
    displayTasks();
    break;
    case 3:
    updateTask();
    break;
    case 4:
    deleteTask();
    break;
    case 5:
    searchTasks();
    break;
    case 6:
    sortTasksByDueDate();
    break;
    case 7:
    printf("\e[1;33m");
    printf("Tasks Tackled!\nSee You Next Time!!\n");
    printf("\e[0m");
    savetasks();
    exit(0);
    default:
    printf("Invalid choice.\n");
  }
  pauseAndClear();
 }
 return 0;
}

void loadtasks(){
 FILE *fp=fopen(TAKS_FILE, "rb");
    if(fp!=NULL){
        printf("Loading tasks...\n");
        fread(&taskcount,sizeof(int),1,fp);
        fread(&nextID,sizeof(int),1,fp);
        fread(tasks,sizeof(Task),taskcount,fp);
        fclose(fp);
    }
    else{
     printf("No Saved Task File Found.\n");
    }
}

void savetasks(){
 FILE *fp=fopen(TAKS_FILE, "wb");
    if (fp==NULL){
        printf("ERROR SAVING TASKS!\n");
        return;
    }
  fwrite(&taskcount,sizeof(int),1,fp);
  fwrite(&nextID,sizeof(int),1,fp);
  fwrite(tasks,sizeof(Task),taskcount,fp);
  fclose(fp);
 printf("Tasks Saved.\n");
}

void addTask(){
 if(taskcount>=MAX_TASKS){
     printf("Cannot add more tasks.\n");
     return;
    }
    Task t;
    t.id=nextID++;
 printf("Name: ");
 fgets(t.name,sizeof t.name,stdin);
 t.name[strcspn(t.name, "\n")] = 0;

  printf("Description: ");
  fgets(t.description,sizeof t.description,stdin);
  t.description[strcspn(t.description, "\n")] = 0;

 printf("Category: ");
 fgets(t.category,sizeof t.category,stdin);
 t.category[strcspn(t.category, "\n")] = 0;

  printf("Due Date (YYYY-MM-DD): ");
  fgets(t.dueDate,sizeof t.dueDate,stdin);
  t.dueDate[strcspn(t.dueDate, "\n")] = 0;
 printf("Priority (integer): ");
 scanf("%d", &t.priority);
 getchar();
  t.completed = 0;
  tasks[taskcount++] = t;
  savetasks();
  printf("\e[1;32m");
  printf("Task Accounted For...\n");
  printf("\e[0m");
}

void displayTasks(){
 if(taskcount==0)
 {
   printf("No tasks.\n");
   return;
 }

 int i=0;
 char status[5];

    printf("\e[4;32m");
  printf("\nID | Name               | Due Date   | Priority | Done | Category |  Descripttion   | \n");
  printf("----------------------------------------------------------------------\n");
    printf("\e[0m");

 for (i=0;i<taskcount;i++)
 {
    if(tasks[i].completed==1){
        strcpy(status, "Yes");
    }
     else{
        strcpy(status, "No");
        }
    printf("%2d | %-18s | %-10s |  %3d  |   %s  | %s  |  %-40s \n",
    tasks[i].id,
    tasks[i].name,
    tasks[i].dueDate,
    tasks[i].priority,
     status,
    tasks[i].category,
    tasks[i].description);

 }
}

void updateTask(){
 int id;
 printf("Enter ID to update: ");
 scanf("%d", &id);
 getchar();
 for(int i=0;i<taskcount;i++){
    if (tasks[i].id == id){
        printf("Updating... \"%s\"\n",tasks[i].name);
        printf("New name (blank to skip): ");
        char buf[50];
        fgets(buf,sizeof buf,stdin);
        if(buf[0] != '\n')
            {
            buf[strcspn(buf, "\n")] = 0;
            strcpy(tasks[i].name, buf);
            }
        printf("New description (blank to skip): ");
        fgets(buf,sizeof buf, stdin);
        if (buf[0] != '\n')
            {
            buf[strcspn(buf, "\n")] = 0;
            strcpy(tasks[i].description, buf);
            }
        printf("New Due Date [YYYY-MM-DD] (blank to skip): ");
        fgets(buf,sizeof buf, stdin);
        if (buf[0] != '\n')
            {
            buf[strcspn(buf, "\n")] = 0;
            strcpy(tasks[i].dueDate, buf);
            }
        printf("Mark as completed? (1=yes, 0=no): ");
     int c;
     scanf("%d", &c);
     getchar();
     tasks[i].completed = c;
     savetasks();
     printf("\e[1;32m");
     printf("Updated.\n");
     printf("\e[0m");
     return;
     }
    }
 printf("Task %d not found.\n", id);
}

void deleteTask()
{
 int id;
 printf("Enter ID to delete: ");
 scanf("%d",&id);
 getchar();
 for(int i=0;i<taskcount;i++){
    if (tasks[i].id==id){
        for(int j=i;j<taskcount-1;j++){     // shift left
            tasks[j]=tasks[j+1];
         }   
         taskcount--;
         savetasks();
         printf("\e[1;31m");
         printf("TASKS REMOVED FROM EXISTENCE...\n");
         printf("\e[0m");
         return;
        }
    }
 printf("Task %d not found.\n", id);
}

void searchTasks(){
 char key[50];
 printf("Keyword to search: ");
 fgets(key,sizeof key,stdin);
 key[strcspn(key, "\n")] = 0;
 int found=0;
 for(int i=0;i<taskcount;i++){
    if(strstr(tasks[i].name, key)||strstr(tasks[i].category,key)){
        if(!found){
            printf("Target Acquired:\n");
        }
        printf("  %d: %s [%s]\n", tasks[i].id,tasks[i].name,tasks[i].dueDate);
        found=1;
    }
 }
 if(!found)
 printf("No matches.\n");
}

void sortTasksByDueDate(){
 for(int i=0;i<taskcount-1;i++){
    for(int j=0;j<taskcount-i-1;j++){
        if(strcmp(tasks[j].dueDate,tasks[j+1].dueDate)>0){
        Task tmp=tasks[j];
        tasks[j]=tasks[j+1];
        tasks[j+1]=tmp;
        }
    }
 }
 printf("Sorted by due date.\n");
 savetasks();
}

void pauseAndClear(){
    printf("\n(Press Enter)");
    getchar();
#ifdef _WIN32
  system("cls");
#else
 system("clear");
#endif
}
