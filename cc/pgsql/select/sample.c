#include <stdio.h>
#include <libpq-fe.h>

int main(int argc, char **argv)
{
    printf("version = %d\n", PQlibVersion());

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

    PGresult *result;

    result = PQexec(pgconn, "select * from books;");
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        fprintf(stderr, ">> %s", PQerrorMessage(pgconn));
        PQclear(result);
        PQfinish(pgconn);
        return -1;
    }

    int num_rows = PQntuples(result);
    int num_cols = PQnfields(result);
    int i, j;

    for (i = 0; i < num_rows; i++) {
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

