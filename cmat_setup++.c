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

int main(int argc, char** argv)
{
    if (ArgCountCheck(argc) == -1) return -1;

    char* dirName = "";

    dirName = MakeDirectoryName(argc, argv);

    if (!CreateDirectory(dirName)) return -1;

    AddSubDirectory(dirName, RESOURCE_DIR);
    AddSubDirectory(dirName, SOURCE_DIR);
    AddSubDirectory(dirName, INCLUDE_DIR);
    AddSubDirectory(dirName, TARGET_DIR);
    AddSubDirectory(dirName, DEBUG_DIR);
    AddSubDirectory(dirName, RELEASE_DIR);

    CreateConfigFile(dirName);
    CreateMainFile(dirName);

    printf("Project [%s] Created Successfully\n", dirName);

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
