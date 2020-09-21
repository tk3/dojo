#include <stdio.h>
#include <stdlib.h>

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

int main() {
  SQLRETURN ret;
  SQLHENV hEnv;

  ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
  ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

  SQLHDBC hDbc;
  ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

  const char *conn_str = "DSN=mysqlitedb";
  ret = SQLDriverConnect(hDbc, NULL, (SQLCHAR *)conn_str, SQL_NTS, NULL, 0,
                         NULL, SQL_DRIVER_NOPROMPT);
  if (!SQL_SUCCEEDED(ret)) {
    printf("failed. Exiting.\n");
    exit(EXIT_FAILURE);
  } else {
    printf("succeeded\n");
  }

  SQLHSTMT hStmt;
  SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

  const char *sql_str = "select * from books;";
  ret = SQLExecDirect(hStmt, (SQLCHAR *)sql_str, SQL_NTS);
  if (SQL_SUCCEEDED(ret)) {
    SQLSMALLINT num_resuls;
    {
      SQLNumResultCols(hStmt, &num_resuls);

      printf("number of results: %d\n", num_resuls);
    }

    SQLTCHAR colname[256];
    ret = SQLBindCol(hStmt, 1, SQL_C_TCHAR, (SQLPOINTER)node_name,
                     sizeof(node_name), NULL);
    while (SQL_SUCCEEDED(ret = SQLFetchScroll(hStmt, SQL_FETCH_NEXT, 1))) {
      printf("Connected to node \n");
    }
  }
  SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

  printf("Disconnecting.\n");
  ret = SQLDisconnect(hDbc);

  printf("Freeing handles...\n");
  SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
  SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

  printf("Done!\n");

  exit(EXIT_SUCCESS);
}
