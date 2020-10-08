/*
    Dawson Dauphinais
    CS426, Operating Systems
    Date Last Modified: 09/29/2020

    The purpose of this program is to use mmap to copy multiple files into a designated output file.
    
*/
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

using namespace std;

size_t file_size(int file) //stackoverflow
{
    struct stat st;
    fstat(file, &st);
    int file_size = st.st_size;
    return file_size;
}

int main(int argc, char *argv[])
{
    struct stat st;
    int len = argc - 1;
    size_t total_size = 0; // size of all files combined
    size_t s_size = 0;     // size of individual file
    char *src_arr[1000];
    char *src;
    char *dest = argv[len];
    int d, s;
    char *sp, *dp;
    ftruncate(d, total_size);
    d = open(dest, O_RDWR | O_CREAT | O_EXCL | O_APPEND, 0660); // should this be O_TRUNC or O_APPEND??
    if (d == -1)
    {
        perror("Opening destination file");
        exit(1);
    }
    for (int i = 0; i < len - 1; i++)
    {
        src_arr[i] = argv[i + 1];
        cout << "Source is : " << src_arr[i] << endl;
        cout << "Destination is: " << dest << endl;
        src = src_arr[i];
        s = open(src, O_RDONLY);
        if (s == -1)
        {
            perror("Opening the source file");
            exit(1);
        }
        s_size = file_size(s);
        cout << "Size of file: " << src << " = " << s_size << endl;
        total_size = s_size + total_size;

        if (fstat(s, &st))
        {
            perror("stat source file");
            exit(1);
        }
        if (ftruncate(d, total_size))
        {
            perror("truncating destination file");
            exit(1);
        }
        sp = (char *)mmap(NULL, total_size, PROT_READ, MAP_SHARED, s, 0);
        madvise(sp, total_size, MADV_SEQUENTIAL);
        if (sp == MAP_FAILED)
        {
            perror("map source");
            exit(1);
        }
        madvise(dp, total_size, MADV_SEQUENTIAL);
        dp = (char *)mmap(NULL, total_size, PROT_WRITE | PROT_READ, MAP_SHARED, d, 0);
        if (dp == MAP_FAILED)
        {
            perror("map destination");
            exit(1);
        }
        memcpy(dp + (total_size - s_size), sp, total_size);
        cout << "Size of: " << dest << " = " << total_size << endl;
        close(s);
    }
    return 0;
}
