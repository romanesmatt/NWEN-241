/**
 * Source file for Assignment 3
 * Full Name:
 * Student ID:
 *
 * You will need to modify this file to perform Tasks 4-5. See the
 * handout for more details.
 *
 * You may also use this as base code to perform Task 6. See the 
 * handout for more details.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

/**
 * Header file contains macros and user-defined types
 * needed in this program. Open server.h for more
 * details.
 */
#include "server.h"

/**
 * Load CSV database file. The implementation of this
 * function is provided so you do not need to implement
 * this.
 * 
 * @param fn CSV database filename
 * @param m Pointer to movie_t
 * @param mlen Number of elements in m
 * @return 0 if successful, -1 otherwise
 */
int db_loadfile(const char *fn, movie_t *m, int mlen);

/**
 * If you are implementing your own functions, declare
 * the function prototypes below. Document your function
 * prototypes using the format above in the prototype
 * declaration of db_loadfile.
 */

/**
 * Main function
 */
int main(void)
{
    int ret, sockfd;
    movie_t movies[CSVDB_RECORDS];
    struct sockaddr_in address;

    printf("Starting server...\n");

    /* Load CSV database file */
    ret = db_loadfile(CSVDB_FILENAME, movies, CSVDB_RECORDS);
    if (ret)
    {
        printf("Error: Failed to open %s\n", CSVDB_FILENAME);
        return 0;
    }

    /**
     * Write your code below to implement Task 4
     */

    /* Create socket */
    int portNum = 12345;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Opening of socket failed.\n");
        exit(1);
    }
    printf("Created sockets.\n", portNum);

    //create address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portNum); //host to network (short value)
    printf("Address created.\n");

    /* Bind socket */
    ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (ret < 0)
    {
        printf("Binding of socket failed.\n");
        exit(1);
    }
    printf("Bind successful.\n");

    /* Listen to socket */
    printf("Listening...\n");
    listen(sockfd, 5);

    /* Accept socket */
    //for client
    struct sockaddr_in cli_addr;
    int clilen = sizeof(cli_addr);

    int newsockfd = accept(sockfd, &cli_addr, &clilen);
    if (newsockfd < 0)
    {
        printf("Accepting of socket failed.\n");
        exit(1);
    }
    printf("Connection established.\n");

    /* Send message to client. */
    char message[] = "HELLO";
    int n = send(newsockfd, message, sizeof(message) / sizeof(char), 0);
    if (n < 0)
    {
        printf("Write failed.\n");
    }
    printf("Message sent.\n");

    while (1)
    {
        int rn, row;

        /* Receive message from client */
        char buffer[256];
        memset(buffer, 0, DEFAULT_STRLEN); //zeroes out array
        int r = recv(newsockfd, buffer, DEFAULT_STRLEN, 0);
        if (r < 0)
        {
            printf("Reading failed.");
        }
        char temporary[DEFAULT_STRLEN];
        rn = sscanf(buffer, "%s %d", buffer, &row);
        printf("FROM CLIENT: %s\n", buffer);

        /**
            * Write your code below to implement Task 5
             */

        //for 6a) and 6b) respectively
        char clientmessage[] = "BYE";
        char clientmessage02[] = "GET";

        /* If message is 'BYE', close connection. */
        if (rn == 1)
        {
            if (strcasecmp(buffer, clientmessage) == 0 || strcasecmp(buffer, "BYE\n") == 0 || strcasecmp(buffer, "BYE") == 0)
            {
                printf("Message received from client equals expected output.\n");
                printf("Closing client...\n");
                close(newsockfd);
                printf("Closing server...\n");
                close(sockfd);
                printf("Shutdown successful.\n");
                exit(1);
            }
        }

        else if (rn == 2)
        {
            /* If message is 'GET X' (X being an arbitrary variable that's less than 26), print the contents of the given row */
            if (strcasecmp(buffer, clientmessage02) == 0 || strcasecmp(buffer, "GET\n") == 0 || strcasecmp(buffer, "GET") == 0)
            {
                if (row > 0 || row < CSVDB_RECORDS)
                {
                    snprintf(temporary, DEFAULT_STRLEN, "%d: %s, %s, %d, %s, %d, %s\r\n", row, movies[row].title,
                             movies[row].director, movies[row].year, movies[row].oscars_won, movies[row].origin_country);
                    int ss = send(newsockfd, row, strlen(row), 0);
                }
                else
                {
                    printf("ERROR.\n");
                    exit(1);
                }
            }
        }
    }

    if(n < 0){
        printf("Message not sent.");
    }

    return 0;
}

/**
 * Implementation of db_loadfile function
 */
int db_loadfile(const char *fn, movie_t *movies, int mlen)
{
    // Input file stream to read csv
    FILE *csv = fopen("scifi.csv", "r");
    if (!csv)
    {
        return -1;
    }

    // Read csv file line by line and scan for input
    int i = 0;
    while (!feof(csv) && i < mlen)
    {
        fscanf(csv, "%[^,],%[^,],%d,%d,%[^\n]%*c",
               movies[i].title, movies[i].director, &movies[i].year,
               &movies[i].oscars_won, movies[i].origin_country);
        i++;
    }

    // Close file after reading
    fclose(csv);

    return 0;
}

/**
 * If you are implementing your own functions, write
 * the function implementation below.
 */
