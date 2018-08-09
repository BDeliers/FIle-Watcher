/*

    SIMPLE FILE WATCHER
    When you call the script, you specify the path of the file to watch. Each time it's modified on the disk, the specified script is started and the provious instance is killed
    BY BDeliers in June 2018

    CALL SAMPLE  :  file-watcher /home/myname/somewhere/somefile /home/myname/somewhere/someExecutableFile /path/to/executer commandToExecute
    REAL EXAMPLE :  file-watcher /home/server/myDataBase /home/server/myscript.py /usr/bin/python3 python3
    REAL EXAMPLE II : file-watcher /home/server/myDataBase /home/server/myscript.sh /bin/sh sh

    Uses 0% ram and 0% cpu for me

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <spawn.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

int main(int argc, char *argv[]) {

    struct stat fileData;

    //  If we didn't send enough infos to run the program
    if(argc < 4) {
        printf("No enough arguments : specify a file to watch \n");
        printf("Example call : file-watcher /home/myname/somewhere/somefile /home/myname/somewhere/someExecutableFile /path/to/executer commandToExecute");
        return EXIT_SUCCESS;
    }
    else {
        time_t lastEdit = 0;    //  To store last edit time
        int first = 1;  //  Is it first loop ?
        pid_t pid = 0;  //  To store the PID of the child process
        char * args[] = {argv[4], argv[2], NULL};    //  Our command

        //  While true
        do {
            // If we succeed reading the infos of the file
            if (stat(argv[1], &fileData) == 0) {
                //  If it was modified since last time
                if (fileData.st_mtime != lastEdit) {
                    lastEdit = fileData.st_mtime;

                    printf("\nLast edit : %s", ctime(&fileData.st_mtime));

                    if (first == 1) {
                        printf("First start \n");
                        first = 0;
                    }
                    //  If we already started a process last loop
                    else {
                        //  If we succeed killing last started process
                        if (kill(pid, SIGKILL) == 0) {
                            printf("Old child process killed \n");
                        }
                        else {
                            perror("Error killing old child process");
                        }
                    }

                    // If we succeed starting the specified script
                    if (posix_spawn(&pid, argv[3], NULL, NULL, args, environ) == 0) {
                        printf("Child process started with pid %i \n\n", pid);
                    }
                    else {
                        perror("Can't start child process");
                        return EXIT_FAILURE;
                    }

                }
            }
            else {
                perror("Error : make sure file exists and is accessible \n");
                return EXIT_FAILURE;
            }

            sleep(5);
        } while (1);

        return EXIT_SUCCESS;
    }
}
