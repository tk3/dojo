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

int input_sql(MYSQL *conn);
void trim_lf(char *line);
int exec_sql(MYSQL *conn, char *line);
int exec_select(MYSQL *conn, char *sql);
int exec_query(MYSQL *conn, char *sql);
int exec_update(MYSQL *conn, char *sql);
int exec_delete(MYSQL *conn, char *sql);

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

    input_sql(conn);

    mysql_close(conn);

    return 0;
}

int input_sql(MYSQL *conn)
{
    char line[1024];

    memset(line, 0, sizeof(line));
    printf("sql> ");
    while (fgets(line, sizeof(line) - 1, stdin) != NULL) {
        trim_lf(line);
        if (strcasecmp(line, "quit") == 0) {
            break;
        }
        printf("command >> [%s]\n", line);
        exec_sql(conn, line);

        memset(line, 0, sizeof(line));
        printf("sql> ");
    }

    return 0;
}

void trim_lf(char *line)
{
    char *lf;

    lf = strrchr(line, '\n');
    if (lf != NULL) {
        *lf = '\0';
    }
}

int exec_sql(MYSQL *conn, char *line)
{
    if (strncasecmp(line, "select ", sizeof("select ") - 1) == 0) {
        exec_select(conn, line);
    } else {
        exec_query(conn, line);
/*
    } else if (strncasecmp(line, "insert ", sizeof("insert ") - 1) == 0) {
    } else if (strncasecmp(line, "update ", sizeof("update ") - 1) == 0) {
    } else if (strncasecmp(line, "delete ", sizeof("delete ") - 1) == 0) {
*/
    }

    return 0;
}

int exec_select(MYSQL *conn, char *sql)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_fields;
    int i;

    if (mysql_query(conn, sql) != 0) {
        printf("Error: mysql_query().[%s]\n", mysql_error(conn));
        return -1;
    }

    result = mysql_store_result(conn);
    if (result == NULL) {
        printf("Error: mysql_store_result().[%s]\n", mysql_error(conn));
        return -1;
    }

    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result))) {
        for (i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);

    return 0;
}

int exec_query(MYSQL *conn, char *sql)
{
    if (mysql_query(conn, sql) != 0) {
        printf("Error: mysql_query().[%s]\n", mysql_error(conn));
        return 1;
    }

    {
        my_ulonglong num = mysql_affected_rows(conn);

        printf("affected row: %lld\n", num);
    }

    {
        int last_id;

        last_id = mysql_insert_id(conn);

        printf("last id: %d\n", last_id);
    }

    return 0;
}

int exec_update(MYSQL *conn, char *sql)
{
    return 0;
}

int exec_delete(MYSQL *conn, char *sql)
{
    return 0;
}

int foo()
{
    MYSQL *conn;
    char *sql_fmt;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error: mysql_init().\n");
        return 1;
    }

    sql_fmt = "INSERT INTO memos (user, content, is_private, created_at) VALUES (\"%s\", \"%s\", 0, now())";

    mysql_close(conn);

    return 0;
}

