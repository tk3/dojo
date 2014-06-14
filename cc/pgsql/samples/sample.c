#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int sample_PQlibVersion(void);
int sample_PQconnectdb(void);
int sample_PQexec_select(void);
int sample_PQexecParams_select(void);
int sample_PQexecPrepared_select(void);

int main(int argc, char **argv)
{
    int no = 0;

    if (argc > 1) {
        no = atoi(argv[1]);
    }

    switch (no) {
    case 0:
        sample_PQlibVersion();
        break;
    case 1:
        sample_PQconnectdb();
        break;
    case 2:
        sample_PQexec_select();
        break;
    case 3:
        sample_PQexecParams_select();
        break;
    case 4:
        sample_PQexecPrepared_select();
        break;
    default:
        break;
    }

    return 0;
}

int sample_PQlibVersion(void)
{
    printf("version = %d\n", PQlibVersion());

    return 0;
}

int sample_PQconnectdb(void)
{
    char *conn_str = "host=localhost port=5432 dbname=testdb user=dbuser password=dbpass";

    PGconn *pgconn = PQconnectdb(conn_str);
    if (pgconn == NULL) {
        fprintf(stderr, "Error: PQconnectdb() failed.\n");
        return -1;
    }

    if (PQstatus(pgconn) != CONNECTION_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQfinish(pgconn);
        return -1;
    }

    printf("connect succeeded.\n");

    PQfinish(pgconn);

    return 0;
}

int sample_PQexec_select(void)
{
    char *conn_str = "host=localhost port=5432 dbname=testdb user=dbuser password=dbpass";

    PGconn *pgconn = PQconnectdb(conn_str);
    if (pgconn == NULL) {
        fprintf(stderr, "Error: PQconnectdb() failed.\n");
        return -1;
    }

    if (PQstatus(pgconn) != CONNECTION_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQfinish(pgconn);
        return -1;
    }

    PGresult *result = PQexec(pgconn, "select * from books;");
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQclear(result);
        PQfinish(pgconn);
        return -1;
    }

    int num_rows = PQntuples(result);
    int num_cols = PQnfields(result);
    int i, j;

    for (i = 0; i < num_cols; i++) {
        printf("%s  ", PQfname(result, i));
    }
    puts("");

    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            printf("%s  ", PQgetvalue(result, i, j));
        }
        puts("");
    }
    PQclear(result);

    PQfinish(pgconn);

    return 0;
}

int sample_PQexecParams_select(void)
{
    char *conn_str = "host=localhost port=5432 dbname=testdb user=dbuser password=dbpass";

    PGconn *pgconn = PQconnectdb(conn_str);
    if (pgconn == NULL) {
        fprintf(stderr, "Error: PQconnectdb() failed.\n");
        return -1;
    }

    if (PQstatus(pgconn) != CONNECTION_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQfinish(pgconn);
        return -1;
    }

    const char *paramValues[1] = {"2"};
    char *sql = "select * from books where id = $1;";
    PGresult *result = PQexecParams(pgconn, sql,
                       1,
                       NULL,
                       paramValues,
                       NULL,
                       NULL,
                       0);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQclear(result);
        PQfinish(pgconn);
        return -1;
    }


    int num_rows = PQntuples(result);
    int num_cols = PQnfields(result);
    int i, j;

    for (i = 0; i < num_cols; i++) {
        printf("%s  ", PQfname(result, i));
    }
    puts("");

    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            printf("%s  ", PQgetvalue(result, i, j));
        }
        puts("");
    }
    PQclear(result);

    PQfinish(pgconn);

    return 0;
}

int sample_PQexecPrepared_select(void)
{
    char *conn_str = "host=localhost port=5432 dbname=testdb user=dbuser password=dbpass";

    PGconn *pgconn = PQconnectdb(conn_str);
    if (pgconn == NULL) {
        fprintf(stderr, "Error: PQconnectdb() failed.\n");
        return -1;
    }

    if (PQstatus(pgconn) != CONNECTION_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQfinish(pgconn);
        return -1;
    }

    const char *paramValues[1] = {"3"};
    char *sql = "select * from books where id = $1;";
    PGresult *result = PQexecPrepared(pgconn, sql,
                        1,
                        paramValues,
                        NULL,
                        NULL,
                        0);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQclear(result);
        PQfinish(pgconn);
        return -1;
    }


    int num_rows = PQntuples(result);
    int num_cols = PQnfields(result);
    int i, j;

    for (i = 0; i < num_cols; i++) {
        printf("%s  ", PQfname(result, i));
    }
    puts("");

    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            printf("%s  ", PQgetvalue(result, i, j));
        }
        puts("");
    }
    PQclear(result);

    PQfinish(pgconn);

    return 0;
}

