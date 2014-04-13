#include <stdio.h>
#include <libpq-fe.h>

int sample_client_version(void);
int sample_connect(void);
int sample_select(void);

int main(int argc, char **argv)
{
    sample_client_version();
    sample_connect();
    sample_select();

    return 0;
}

int sample_client_version(void)
{
    printf("version = %d\n", PQlibVersion());

    return 0;
}

int sample_connect(void)
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

    PQfinish(pgconn);

    return 0;
}

int sample_select(void)
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

