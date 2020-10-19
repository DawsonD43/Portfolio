
/*
    Dawson Dauphinais
    CS426 - Operating Systems
    Date Last Modified: 10/19/2020

    This program will count directory structures in a linux file system.
*/
#include <dirent.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <assert.h>
using namespace std;
int TOTAL_SIZE = 0;

/*returns true if the inode's type is a file*/
bool is_file(struct dirent *sd)
{
    return (sd->d_type == DT_REG);
}

/*returns true if the inode's type is a directory*/
bool is_directory(struct dirent *sd)
{
    return (sd->d_type == DT_DIR);
}

/*returns true if the inode's type is a link*/
bool is_link(struct dirent *sd)
{
    return (sd->d_type == DT_LNK);
}

/*returns the permissions of the given file*/
char *get_permissions(char *path) // referenced stackoverflow
{
    struct stat st;
    char *perm = (char *)malloc(sizeof(char) * 9 + 1);
    if (stat(path, &st) == 0)
    {
        mode_t p = st.st_mode;
        perm[0] = (p & S_IRUSR) ? 'r' : '-';
        perm[1] = (p & S_IWUSR) ? 'w' : '-';
        perm[2] = (p & S_IXUSR) ? 'x' : '-';
        perm[3] = (p & S_IRGRP) ? 'r' : '-';
        perm[4] = (p & S_IWGRP) ? 'w' : '-';
        perm[5] = (p & S_IXGRP) ? 'x' : '-';
        perm[6] = (p & S_IROTH) ? 'r' : '-';
        perm[7] = (p & S_IWOTH) ? 'w' : '-';
        perm[8] = (p & S_IXOTH) ? 'x' : '-';
        perm[9] = '\0';
        return perm;
    }
    else
    {
        return strerror(errno);
    }
}

/*returns the link as a string*/
string getLink(char *path) // referenced man readlink
{
    struct stat sb;
    ssize_t r;
    char *link;
    assert(lstat(path, &sb) != -1);
    link = (char *)malloc(sb.st_size + 1);
    assert(link != NULL);
    r = readlink(path, link, sb.st_size + 1);
    assert(r > 0);
    link[sb.st_size] = '\0';
    return link;
}

/*creates a new path by adding the subdirectory to the current directory*/
char *create_new_path(char *dir, char *inode) // referenced stackoverflow for conversions of char pointers to strings and visa-versa
{
    char *path = (char *)malloc(2 + strlen(dir) + strlen(inode));
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, inode);
    return path;
}

/*returns the size of the file passed in*/
size_t getSize(const char *file, int fd) // stackoverflow
{
    struct stat sb;
    int res = fstatat(fd, file, &sb, 0);
    size_t size = sb.st_size;
    return size;
}

/*searches a specified directory for files, subdirectories, and links on the given path*/
void dircount(char *path)
{
    auto dir = opendir(path);
    char *currDir = strstr(path, "/test");
    struct dirent *inode;
    struct stat sb;
    assert(dir != NULL);
    cout << "." << currDir << " (d)" << endl;
    while ((inode = readdir(dir)) != NULL)
    {
        if (is_file(inode))
        {
            int dir_fd = dirfd(dir);
            TOTAL_SIZE += getSize(inode->d_name, dir_fd);
            cout << get_permissions(path) << " "
                 << "." << currDir << "/" << inode->d_name << " (f, " << getSize(inode->d_name, dir_fd) << ")" << endl;
        }
        else if (is_directory(inode))
        {
            auto name = inode->d_name;
            if ((strcmp(name, ".") == 0) || (strcmp(name, "..") == 0))
            {
                cout << "." << currDir << "/" << name << " (d)" << endl;
            }
            else
            {
                char *nPath = create_new_path(path, inode->d_name);
                dircount(nPath);
            }
        }
        else if (is_link(inode)) 
        {
            cout << "." << currDir << "(l, -> " << getLink(create_new_path(path, inode->d_name)) << ")" << endl;
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    dircount(argv[1]);
    cout << "Total File Size: " << TOTAL_SIZE << endl;
    return 0;
}