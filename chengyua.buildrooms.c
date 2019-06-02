// Name: Yuan-hao Cheng
// ID: 933-048-737
// OSU Email: chengyua@oregonstate.edu


#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


#define MIN_RM_CON 3
#define MAX_RM_CON 6
#define TOTAL_RM 10
#define ACTUAL_RM 7


// Set names for 10 rooms.
char *Rm_Name[TOTAL_RM] = {
    "Fire",
    "Thunder",
    "Ground",
    "Hydra",
    "Heal",
    "Dark",
    "Plant",
    "Demon",
    "Light",
    "Ice"
};


// Reference: https://www.cnblogs.com/wgang171412/p/5382291.html
// Define room types.
enum Rm_Type{
    START_ROOM,
    MID_ROOM,
    END_ROOM
};

// Define boolean to easily return True or false.
typedef enum {
    FALSE = 0,
    TRUE = 1
}boolean;

// A basic frame of each room's information.
struct Rm_Create{
    char RmName[10];
    int total_cons;
    struct Rm_Create* cons[MAX_RM_CON];
    enum Rm_Type RmTp;
};


struct Rm_Create Rm_List[MAX_RM_CON];


// Check if two rooms are connected. Return TRUE if they are connected; FALSE if they are not.
// Reference: http://www.cplusplus.com/reference/cstring/strcmp/
boolean PreCheck_Con(int rm1, int rm2){
    // Room1 connects to all of the rest of the rooms.
    if(Rm_List[rm1].total_cons == MAX_RM_CON)
        return TRUE;
    
    for(int i=0; i < Rm_List[rm1].total_cons; i++){
        if(Rm_List[rm1].cons[i] == NULL)
            return FALSE;
        // If rm2's name is listed in rm1's connection list, then return TRUE.
        else if(strcmp(Rm_List[rm1].cons[i]->RmName, Rm_List[rm2].RmName) == 0)
            return TRUE;
    }
    return FALSE;
}

// Check if the rooms were exactly connected.
boolean Is_Con(int rm1, int rm2){
    if(PreCheck_Con(rm1, rm2) == TRUE)
        return TRUE;
    
    else if (strcmp(Rm_List[rm1].RmName, Rm_List[rm2].RmName) == 0)
        return TRUE;
    
    else
        return FALSE;
}

// Check if the room can have more rooms to connect. If it reaches the maximum of the rooms that can connect, then return FALSE. If not, return TRUE.
boolean Add_Rm(int rm){
    if(Rm_List[rm].total_cons == MAX_RM_CON)
        return FALSE;
    
    else return TRUE;
}

// Generate random rooms to connect.
int Gen_Rm(){
    int rm;
    
    do{
        rm = rand() % TOTAL_RM;
    }while(Add_Rm(rm) == FALSE);
    
    return rm;
}


int Correct_Num(int min, int max){
    int rm;
    
    // Make sure that the number of the connections of the room is in the correct range.
    do{
        rm = rand() % max + min;
    }while(Add_Rm(rm) == FALSE && rm >= min && rm <= max);
    
    return rm;
}

// Connect Rooms.
void Con_Rm(int rm){
    boolean Con = FALSE;
    // If the total connections of the room has reached its maximum connections, then return.
    if(Rm_List[rm].total_cons == MAX_RM_CON){
        return;
    }
    
    int rm1, rm2;
    
    
    do{
        rm1 = rm;
        rm2 = Correct_Num(0, ACTUAL_RM);
        // If rm1 and rm2 are not connected, then make them connected.
        if(Is_Con(rm1, rm2) == FALSE){
            int con1 = Rm_List[rm1].total_cons;
            int con2 = Rm_List[rm2].total_cons;
            
            // Make connections each room, then add 1 to their connected total rooms countings.
            Rm_List[rm1].cons[con1] = &Rm_List[rm2];
            Rm_List[rm2].cons[con2] = &Rm_List[rm1];
            Rm_List[rm1].total_cons++;
            Rm_List[rm2].total_cons++;
            Con = TRUE;
        }
    }while(Con == FALSE);
}


void Ini_Rm_Con(int rm){
    for (int i=0; i < MAX_RM_CON; i++){
        Rm_List[rm].cons[i] = NULL;
    }
}


boolean Ini_Rms[ACTUAL_RM];


// Reference: https://www.tutorialspoint.com/c_standard_library/c_function_memset.htm
// Initialize room list, making them NULL.
void Ini_Rm_List(){
    int i;
    for (i=0; i < ACTUAL_RM; i++){
        Ini_Rms[i] = FALSE;
    }
    
    // Make all the total_cons info NULL (Initialize).
    for(i=0; i < ACTUAL_RM; i++){
        Rm_List[i].total_cons = 0;
        Ini_Rm_Con(i);
        
        // Get a room index to put into room list.
        while(1){
            int GRm = Gen_Rm();
            // Make all the room type "MID" then define the start and end after all the rooms are generated.
            if(Ini_Rms[GRm] == FALSE){
                Ini_Rms[GRm] = TRUE;
                memset(Rm_List[i].RmName, '\0', sizeof(Rm_List[i].RmName));
                strcpy(Rm_List[i].RmName, Rm_Name[GRm]);
                Rm_List[i].RmTp = MID_ROOM;
                break;
            }
        }
    }
    // Make the first room's type "Start", and the last one's "End"
    Rm_List[0].RmTp = START_ROOM;
    Rm_List[ACTUAL_RM - 1].RmTp = END_ROOM;
}


// Initialize the room list then make then connect at least 3 (minimum room connections) rooms.
void Com_Rm_List(){
    Ini_Rm_List();
    
    for(int i=0; i < ACTUAL_RM; i++){
        for(int j=0; j < MIN_RM_CON; j++){
            Con_Rm(i);
        }
    }
}


char FolderName[50];

// Reference: http://pubs.opengroup.org/onlinepubs/009695399/functions/mkdir.html
// Make room directory.
void MkRmDir(){
    char* DirName = "chengyua.rooms.";
    // Set process ID;
    int pid = getpid();
    // Change permission just like "chmod".
    int Permission = 0770;
    
    // Make content of FolderName Null.
    memset(FolderName,'\0', sizeof(FolderName));
    // Set the folder's name
    sprintf(FolderName, "%s%d", DirName, pid);
           
    // Create a folder.
    mkdir(FolderName, Permission);
}

//Reference: http://blog.csdn.net/lanchunhui/article/details/50752780
// Make room's file.
void MkRmFile(){
    FILE *Rm_File;
    char FolderDir[50];
    // Get a folder named chengyua.rooms.processID
    sprintf(FolderDir, "./chengyua.rooms.%d",getpid());
    
    MkRmDir();
    
    // Prevents errors, checks if the folder exists or directory was changed.
    if(chdir(FolderDir) != 0){
        printf("Directory is not changed to: %s\n", FolderDir);
        return;
    }
    
    // Generate files.
    for(int i=0; i < ACTUAL_RM; i++){
        
        // Open or Create the file.
        Rm_File = fopen(Rm_List[i].RmName, "w");
        
        // Print (Write) the room's name and rooms they connect.
        fprintf(Rm_File, "ROOM NAME: %s\n", Rm_List[i].RmName);
        
        for(int j=0; j < Rm_List[i].total_cons; j++){
            fprintf(Rm_File, "CONNECTION %d: %s\n", j+1, Rm_List[i].cons[j]->RmName);
        }
        
        // Check the room's type and print to file.
        if(Rm_List[i].RmTp == START_ROOM)
            fprintf(Rm_File, "ROOM TYPE: %s\n", "START_ROOM");
        else if(Rm_List[i].RmTp == MID_ROOM)
            fprintf(Rm_File, "ROOM TYPE: %s\n", "MID_ROOM");
        else if(Rm_List[i].RmTp == END_ROOM)
            fprintf(Rm_File, "ROOM TYPE: %s\n", "END_ROOM");
        else
            fprintf(Rm_File, "ROOM TYPE: %s\n", "NULL");
        fclose(Rm_File);
    }
}


           
int main(){
    
    srand((unsigned)time(NULL));
    Com_Rm_List();
    MkRmFile();
    return 0;
}