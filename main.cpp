#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

bool exists(char *path);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Invalid amount of arguments!" << endl;
        return 1;
    }

    char *path = argv[1];

    if (!exists(path))
    {
        cout << "'" << path << "' does not exist!" << endl;
        return 1;
    }

    if (access(path, X_OK) != 0)
    {
        cout << "'" << path << "' is not executable!" << endl;
        return 1;
    }

    int status;
    pid_t pid = fork();

    if (pid == 0)
    {
        int outFd = open("out.txt", O_WRONLY | O_CREAT, 0755);
        int errFd = open("err.txt", O_WRONLY | O_CREAT, 0755);

        if (outFd == -1)
        {
            cout << "Failed to open 'out.txt' for writing" << endl;
            return 1;
        }
        if (outFd == -1)
        {
            cout << "Failed to open 'err.txt' for writing" << endl;
            return 1;
        }

        dup2(outFd, STDOUT_FILENO);
        dup2(errFd, STDERR_FILENO);

        execv(path, &argv[1]);

        close(outFd);
        close(errFd);

        return 0;
    }
    else if (pid > 0)
    {
        wait(nullptr);
        return 0;
    }
}

bool exists(char *path)
{
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}
