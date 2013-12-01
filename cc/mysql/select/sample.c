#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <my_global.h>
#include <mysql.h>

typedef struct {
    char *host;
    char *username;
    char *password;
    char *database;
} conf;

conf c = { "localhost", "foo", "pass", "isucon" };

int main(int argc, char **argv)
{
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error: mysql_init().\n");
        return 1;
    }

    if (mysql_real_connect(conn, c.host, c.username, c.password, c.database, 0, NULL, 0) == NULL) {
        printf("Error: mysql_real_connect().[%s]\n", mysql_error(conn));
        return 1;
    }

    if (mysql_query(conn, "SELECT * FROM memos") != 0) {
        printf("Error: mysql_query().[%s]\n", mysql_error(conn));
        return 1;
    }

    {
        MYSQL_RES *result;
        MYSQL_ROW row;
        int num_fields;
        int i;

        result = mysql_store_result(conn);
        if (result == NULL) {
            printf("Error: mysql_store_result().[%s]\n", mysql_error(conn));
            return 1;
        }

        num_fields = mysql_num_fields(result);

        while ((row = mysql_fetch_row(result))) { 
            for (i = 0; i < num_fields; i++) { 
                printf("%s ", row[i] ? row[i] : "NULL"); 
            } 
            printf("\n"); 
        }

        mysql_free_result(result);
    }

    {
        int last_id;

        last_id = mysql_insert_id(conn);

        printf("last id: %d\n", last_id);
    }

    mysql_close(conn);

    return 0;
}

