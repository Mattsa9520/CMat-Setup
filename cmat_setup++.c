#include "directory_create.h"

#define RESOURCE_DIR "resources"
#define SOURCE_DIR "src"
#define INCLUDE_DIR "include"
#define TARGET_DIR "target"
#define DEBUG_DIR "target/debug"
#define RELEASE_DIR "target/release"

/*
=== CMat Setup++ ======
= ** The New and Improved Project Setup tool **
= This program creates a basic project folder for a c++ program
= It will create the necessary directories based on the directory name passed into
= the programs arguments. If more than one argument is passed, as long as the arguments don't contain
= the '-' flag, then they will all be added together in order to create one directory name
= The program will also create a '{WorkspaceName}/cmat.config' and '{Workspacename}/src/main.cpp' file
= in the respective directories. 
=======================
*/

int ArgCountCheck(const int argc);
bool CheckAbsPath(const int argc, char** argv);

int main(int argc, char** argv)
{
    // make sure that there is more than one arg
    if (ArgCountCheck(argc) == -1) return -1;

    // allocate memory for directory name
    char* dirName = (char*)malloc(256);

    // make the directory name from arguments
    MakeDirectoryName(argc, argv, dirName);

    // if directory already exists, or can't be created, quit execution
    if (!CreateDirectory(dirName)) return -1;

    // Create necessary subdirectories
    AddSubDirectory(dirName, RESOURCE_DIR);
    AddSubDirectory(dirName, SOURCE_DIR);
    AddSubDirectory(dirName, INCLUDE_DIR);
    AddSubDirectory(dirName, TARGET_DIR);
    AddSubDirectory(dirName, DEBUG_DIR);
    AddSubDirectory(dirName, RELEASE_DIR);

    // create files
    CreateConfigFile(dirName);
    CreateMainFile(dirName);

    // alert the user the projected was created successfully
    printf("Project [%s] Created Successfully\n", dirName);

    // free allocated memofy
    free(dirName);

    return 0; 
}

int ArgCountCheck(const int argc)
{
    if (argc <= 1) {
        printf("*No Arguments Passed!\n");
        printf("** Pass the name of the directory you want to create!\n");
        return -1;
    }
}