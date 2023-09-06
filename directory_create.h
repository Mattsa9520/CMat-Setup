#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

const char* CONFIG_FILE_NAME = "cmat.config";

// check if a directory exists
bool DirectoryExists(const char* dirName)
{
    DIR* dir = opendir(dirName);

    if (dir)
    {
        closedir(dir);
        return true;
    }

    return false;
}

// Concatonate strings to create the directory name from the program arguments
void MakeDirectoryName(const int argc, char** argv, char* dirName)
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-') 
        {
            // ensure there is no trailing "/"
            if (argv[i][strlen(argv[i]) - 1] == '/') argv[i][strlen(argv[i]) - 1] = 0;

            int newSize = sizeof(dirName) + strlen(argv[i]);

            char* newDirName = (char*)malloc(newSize);
            strcpy(newDirName, dirName);
            strcat(newDirName, argv[i]);

            strcpy(dirName, newDirName);
        }
    }
}

// Create directory from directory name
bool CreateDirectory(const char* dirName)
{
    if (strlen(dirName) <= 0)
    {
        printf("ERROR: No Directory Name Given\n");
        return false;
    }

    if (!DirectoryExists(dirName))
    {
        if (mkdir(dirName, 0777) == -1) {
            printf("ERROR: Unable to create Directory %s\n", dirName);
            return false;
        } else {
            return true;
        }
    }

    printf("Directory [%s] Already Exists!\n", dirName);
    return false;
}

// Add subdirectory from directory name and subdirectory name
void AddSubDirectory(const char* dirName, const char* subDir)
{
    if (!DirectoryExists(dirName)) {
        printf("Directory: %s Does not exist\n", dirName);
        return;
    }

    int newFullSubDirSize = strlen(dirName) + strlen(subDir);

    char* fullSubDir = (char*)malloc(newFullSubDirSize);
    strcpy(fullSubDir, dirName);
    strcat(fullSubDir, "/");
    strcat(fullSubDir, subDir);

    CreateDirectory(fullSubDir);

    free(fullSubDir);
}

// create config file with default text
void CreateConfigFile(const char* baseDir)
{
    int fileNameSize = strlen(CONFIG_FILE_NAME) + strlen(baseDir);
    char* fileName = (char*)malloc(fileNameSize);

    strcpy(fileName, baseDir);
    strcat(fileName, "/");
    strcat(fileName, CONFIG_FILE_NAME);

    FILE* configFile = fopen(fileName, "w");

    if (configFile == NULL)
    {
        printf("Unable to open/create config file\n");
        return;
    }

    char details[60] = "[Program Details]\nname = Program\nstd_version = 11\n";
    char include[30] = "[Include]\n\n";
    char libs[30] = "[Libraries]\n\n";

    fputs(details, configFile);
    fputs(include, configFile);
    fputs(libs, configFile);    

    fclose(configFile);

    free(fileName);
}

void CreateMainFile(const char* baseDir)
{
    int fileNameSize = strlen(baseDir) + strlen("/src/cpp/main.cpp");
    char* fileName = (char*)malloc(fileNameSize);
    strcpy(fileName, baseDir);
    strcat(fileName, "/src/cpp/main.cpp");

    FILE* mainFile = fopen(fileName, "w");

    if (mainFile == NULL)
    {
        printf("ERROR: Unable to make main file\n");
        return;
    }

    fprintf(mainFile, "#include <iostream>\n\n");
    fprintf(mainFile, "int main()\n");
    fprintf(mainFile, "{\n");
    fprintf(mainFile, "\tstd::cout << \"Hello, World!\\n\";\n");
    fprintf(mainFile, "}\n");

    fclose(mainFile);

    free(fileName);
}