// Name: Yuan-hao Cheng
// ID: 933-048-737
// OSU Email: chengyua@oregonstate.edu



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define MIN_RM_CON 3
#define MAX_RM_CON 6
#define TOTAL_RM 10
#define ACTUAL_RM 7


typedef enum {
    FALSE = 0,
    TRUE = 1
}boolean;


enum Rm_Type{
    START_ROOM,
    MID_ROOM,
    END_ROOM
};

struct Rm_Create{
    char RmName[10];
    int total_cons;
    struct Rm_Create* cons[MAX_RM_CON];
    enum Rm_Type RmTp;
};


struct Rm_Create Rm_List[ACTUAL_RM];
char FolderName[100];


// Initialize the folder.
void Ini_Fdr_Name(){
    memset(FolderName,'\0',sizeof(FolderName));
}

// Set time file which tells and record current time (system).
char *Cur_Time_File = "currentTime.txt";
pthread_mutex_t TimeFile_Mutex;



// Reference: http://c.biancheng.net/cpp/html/320.html
// Reference: http://blog.csdn.net/lin_fs/article/details/7335573
// Reference: http://blog.csdn.net/bjlingzhuo/article/details/51148955
// Reference: https://www.cnblogs.com/jikexianfeng/p/5742887.html


void Select_Fdr(){
    char *fd = "chengyua.rooms.";
    char currentDir[100];
    // Current directory.
    DIR *dir;
    struct dirent *dp;
    struct stat *buffer;
    time_t Last;  // This is equivalent to a long int.
    time_t Latest = 0;
    
    // Create buffers to read in folder stats.
    buffer = malloc(sizeof(struct stat));
    dp = malloc(sizeof(struct dirent));
    
    //clears folder name.
    Ini_Fdr_Name();
    memset(currentDir, '\0', sizeof(currentDir));
    // Get the olute path from currentDir.
    getcwd(currentDir, sizeof(currentDir));
    // Open current directory. If it is a file, then return NULL.
    dir = opendir(currentDir);
    
    // Make sure that dir is not a file.
    if (dir != NULL) {
        // Read all the files under the dir.
        while ((dp = readdir(dir))) {
            if (strstr(dp->d_name, fd) != NULL){
                // Read in stats of a folder
                stat(dp->d_name, buffer);
                // Get the Last date of a file (long int)
                Last = buffer->st_mtime;
                
                // Check if the folder is the latest.
                if(Last > Latest){
                    Latest = Last;
                    strcpy(FolderName, dp->d_name);
                }
            }
        }
    }
}

// Initialize the connections of the room list to NULL.
void Ini_Rm_Con(int rm){
    int i;
    for(i = 0; i < MAX_RM_CON; i++){
        Rm_List[rm].cons[i] = NULL;
    }
}




// Make the name of the list NULL. (Initialize)
void Ini_Rm_List(){
    for(int i = 0; i < ACTUAL_RM; i++){
        memset(Rm_List[i].RmName, '\0', sizeof(Rm_List[i].RmName));
        Rm_List[i].total_cons = 0;
        Ini_Rm_Con(i);
    }
}



/// DESC: from each file fill the names for each room.
void Fill_Rm_List(){
    // Create file.
    DIR *dir;
    struct dirent *ent;
    int CountFile = 0;
    
    // Initalize the room's list.
    Ini_Rm_List();
    
    // Fill up struct Names
    if ((dir = opendir (FolderName)) != NULL) {
        // Print all the files and directories within directories.
        while ((ent = readdir (dir)) != NULL) {
            // copy file name to the list.
            if(strlen(ent->d_name) > 2){
                strcpy(Rm_List[CountFile].RmName, ent->d_name);
                CountFile++;
            }
        }
    }
}



// Find the position (index) of the room.
int Rm_Position(char *rm_name){
    
    for(int i = 0;i < ACTUAL_RM; i++ ){
        // If the room's name matches, then return its position.
        if(strcmp(Rm_List[i].RmName, rm_name) == 0 ){
            return i;
        }
    }
    // Return -1 if nothing was found.
    return -1;
}



// Return a label of a file buffer and value of the other half of it.
// Reference: http://blog.csdn.net/hgj125073/article/details/8447605
void Get_Lab_Val(char *lab, char *val){
    
    // Cut label from value at ":"
    strtok(lab,":");
    // Set value from strtok.
    strcpy(val,strtok(NULL,""));
    // Append to end of line. (Make it end)
    val[strlen(val) - 1] = '\0';
    lab[strlen(lab) - 1] = '\0';
    
    // Remove space form value string.
    for(int i = 0; i < strlen(val); i++){
        val[i] = val[i+1];
    }
}

// Generate a connection between rm1 and rm2.
void Re_Gen_Rm_Con(int rm_pos1,int rm_pos2)
{
    int tol_con = Rm_List[rm_pos1].total_cons;
    
    // Add address.
    Rm_List[rm_pos1].cons[tol_con] = &Rm_List[rm_pos2];
    // Count total connections.
    Rm_List[rm_pos1].total_cons++;
}



// Re-generate the list from the files in the most recent directory.
// Reference: http://blog.csdn.net/daiyutage/article/details/8540932
void Re_Gen_Rm_Stuct()
{
    char File_Line_Buf[100];
    char File_Val_Buf[100];
    
    FILE *Rm_File;
    int i;
    
    // Fill room's list with file names
    Fill_Rm_List();
    // Change to the directory which contains all the files.
    chdir(FolderName);
    
    for(i=0; i < ACTUAL_RM; i++){
        // Open File
        Rm_File = fopen(Rm_List[i].RmName,"r");
        
        // Check if file was opened
        if(Rm_File == NULL){
            printf("%s file was not accessed\n", Rm_List[i].RmName);
            exit(1);
        }
        
        // Initialize two Files.
        memset(File_Line_Buf,'\0',sizeof(File_Line_Buf));
        memset(File_Val_Buf,'\0',sizeof(File_Val_Buf));
        
        // Get each line from the file.
        while(fgets(File_Line_Buf, sizeof(File_Line_Buf), Rm_File) != NULL){
            
            // Get the label and value from the line.
            Get_Lab_Val(File_Line_Buf, File_Val_Buf);
            // Fill in room's type.
            if(strcmp(File_Line_Buf, "ROOM TYP") == 0){
                
                if(strcmp(File_Val_Buf,"START_ROOM") == 0){
                    Rm_List[i].RmTp = START_ROOM;
                }
                else if(strcmp(File_Val_Buf,"END_ROOM") == 0){
                    Rm_List[i].RmTp = END_ROOM;
                }
                else{
                    Rm_List[i].RmTp = MID_ROOM;
                }
            }
            // Fill in connections.
            else if(strcmp(File_Line_Buf, "CONNECTION ") == 0){
                int Connect_Rm_Pos = Rm_Position(File_Val_Buf);
                Re_Gen_Rm_Con(i, Connect_Rm_Pos);
            }
        }
        // Close (End) the file.
        fclose(Rm_File);
    }
    // Go back to the main directory.
    chdir("..");
}


// Return the start room's position (index) in the list.
int Start_Rm_Pos(){
    int i;
    for(i =0;i< ACTUAL_RM; i++){
        if(Rm_List[i].RmTp == START_ROOM){
            // return room's position.
            return i;
        }
    }
    // The start room not found.
    return -1;
}

// Get each name and print their names.
void Print_Step_Path(int *p,int s)
{
    int i;
    // for amount of steps print a name.
    for(i = 0;i < s + 1;i++){
        printf("%s\n",Rm_List[p[i]].RmName);
    }
}


// Create a time file in current diretory.
// Reference: http://stackoverflow.com/questions/5141960/get-the-current-time-in-c
void* Gen_Cur_Time_File()
{
    char Time_Arr[100];
    time_t CurrTime;
    struct tm * TimeInfo;
    FILE *Time_File;
    memset(Time_Arr,'\0',sizeof(Time_Arr));
    
    // Get current time.
    time(&CurrTime);
    // Put time into an easily accessable struct.
    TimeInfo = localtime(&CurrTime);
    // Format string.
    strftime(Time_Arr, 100, "%I:%M%P %A, %B %d, %Y", TimeInfo);

    // Create or overwrite the file. (with "w")
    Time_File = fopen(Cur_Time_File,"w");
    // Print time to file.
    fprintf(Time_File,"%s\n",Time_Arr);
    // End the file.
    fclose(Time_File);
    
    return NULL;
}


// Read the file and display the current time.
void Read_Cur_Time_File()
{
    char Buffer[100];
    FILE *TimeFile;
    memset(Buffer,'\0', sizeof(Buffer));
    
    // Read the file only.
    TimeFile = fopen(Cur_Time_File,"r");
    // Check if the file exists.
    if(TimeFile == NULL){
        printf("The %s file is not accessed.\n",Cur_Time_File);
        exit(1);
    }
    
    // Read every line in the file (there should only be one.)
    while(fgets(Buffer, 100, TimeFile) != NULL){
        // Print the line.
        printf("%s\n", Buffer);
    }
    
    // Close the file.
    fclose(TimeFile);
}



// Create a seperate thread to write a file which containing system time.
// Reference: https://www.thegeekstuff.com/2012/05/c-mutex-examples/?refcom
boolean TimeThread()
{
    // Holder for the thread that will contain the function.
    pthread_t WriteTimeFile_Thread;
    // This thread cannot be used untill it finishes running.
    pthread_mutex_lock(&TimeFile_Mutex);
    
    // If something went wrong, it won't continue.
    if(pthread_create(&WriteTimeFile_Thread,NULL, Gen_Cur_Time_File, NULL) != 0){
        printf("Error from thread!");
        return FALSE;
    }
    
    // Once done, then unlock the mutex.
    pthread_mutex_unlock(&TimeFile_Mutex);
    // Prevent runnaway processes.
    pthread_join(WriteTimeFile_Thread,NULL);
    return TRUE;
}


// Running whole game.
void Run()
{
    int Cur_Step = 0;
    int stepRecord[1028];
    int Cur_Room_Pos, i;
    boolean Rm_Match = FALSE;
    struct Rm_Create currRoom;
    char InputBuffer[100];
    
    // First, find the start room position.
    stepRecord[Cur_Step] = Start_Rm_Pos();
    
    do{
        // Record steps to room.
        Cur_Room_Pos = stepRecord[Cur_Step];
        currRoom = Rm_List[Cur_Room_Pos];
        
        printf("CURRENT LOCATION: %s\n", currRoom.RmName);
        
        printf("POSSIBLE CONNECTIONS:");
        // Print out connections by name.
        for(i = 0; i < currRoom.total_cons - 1; i++){
            printf(" %s,",currRoom.cons[i]->RmName);
        }
        // Print last connection.
        printf(" %s.\n",currRoom.cons[i]->RmName);
        
        // Ask for user's input.
        memset(InputBuffer,'\0',sizeof(InputBuffer));
        printf("WHERE TO? >");
        scanf("%100s",InputBuffer);
        printf("\n");
        
        // Conditional for what is printed after user input.
        Rm_Match = FALSE;
        
        // Check if the input matches the name of a room.
        for(i = 0; i < currRoom.total_cons; i++){
            // If match
            if(strcmp(InputBuffer,currRoom.cons[i]->RmName) == 0){
                // Step count.
                Cur_Step++;
                // Record position of the room in roomlist.
                stepRecord[Cur_Step] = Rm_Position(InputBuffer);
                // Iterate to next room.
                Cur_Room_Pos = stepRecord[Cur_Step];
                currRoom = Rm_List[Cur_Room_Pos];
                // Tell later conditions that room match happened.
                Rm_Match = TRUE;
                // Check if room is end room.
                if(currRoom.RmTp == END_ROOM){
                    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
                    printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", Cur_Step + 1);
                    Print_Step_Path(stepRecord, Cur_Step);
                    exit(1);
                }
            }
        }
        
        // If user input is equal to time, print it out.
        if(strcmp(InputBuffer, "time") == 0 && Rm_Match == FALSE){
            if( TimeThread() == TRUE){
                // If the file was written read it.
                Read_Cur_Time_File();
            }
            
        }
        // Error message if the input was wrong.
        else if(Rm_Match == FALSE){
            printf("HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
        }
    }
    while(TRUE);
}



int main(void)
{
    Select_Fdr();
    Re_Gen_Rm_Stuct();
    
    Run();
}
