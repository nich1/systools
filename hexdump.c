// Author: Nicholas R Taylor
// Date: 5-31-2023
// Any feedback is appreciated!

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fileptr;
    int offset = 0;
    char * filename[30];

    if (argc == 2) { // If user provides a commandline argument, open the argument as the filename
        *filename = argv[1];
    }
    else { // If user does not provide a commandline argument, prompt for file input
        printf("Enter file name: "); 
        fscanf(stdin, "%s", *filename);
    }

    fileptr = fopen(*filename, "rb"); // Open file in read bytes mode

    if(fileptr == NULL) // If file did not open
    {
        printf("\nERROR: File was not found or could not be opened\n");
        return 1;
    }

    while(!feof(fileptr)) // Iterate through entire file until eof flag is true
    {
        unsigned char buffer[17]; // Create and clear buffer
        for (int i = 0; i <18; ++i) {
            buffer[i] = '\0';
        }

        int bufferCount = fread(buffer, 16, 1, fileptr); // Read 16 bites at a time
        
        printf("%08X  ",(unsigned int) offset); // Print the offset
        for(int i = 0; i < 16; ++i) // Read in 16 bites
        {
            printf("%02X ", buffer[i]); // Print hex

            if(i == 7) // Spacing for format
            {
                printf(" ");
            }
        }

        printf(" |"); // Separators for format
        for(int j = 0; j < 16; ++j) //Print all printable chars
        {
            if(isprint(buffer[j])) //If char can print
            {
                printf("%c", buffer[j]); // Print ascii character
            }
            else
            {
                printf("."); // If not printable, print a '.'
            }
        }
        printf("|\n"); // Seperator and newline for format
        offset +=16; // Increase offset
        }

    fclose(fileptr); // Close file
    return 0;
}
