#include <stdio.h>
#include <stdlib.h>

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

int main() {
  SQLRETURN ret;
  SQLHENV hdlEnv;

  ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hdlEnv);
  ret =
      SQLSetEnvAttr(hdlEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

  SQLHDBC hdlDbc;
  ret = SQLAllocHandle(SQL_HANDLE_DBC, hdlEnv, &hdlDbc);

  const char *conn_str = "DSN=PostgreSQL testdb";
  ret = SQLDriverConnect(hdlDbc, NULL, (SQLCHAR *)conn_str, SQL_NTS, NULL, 0,
                         NULL, SQL_DRIVER_NOPROMPT);
  if (!SQL_SUCCEEDED(ret)) {
    printf("failed. not found data source.\n");
    exit(EXIT_FAILURE);
  } else {
    printf("succeeded\n");
  }

  SQLHSTMT hdlStmt;
  SQLAllocHandle(SQL_HANDLE_STMT, hdlDbc, &hdlStmt);

  const char *sql_str = "select * from test;";
  ret = SQLExecDirect(hdlStmt, (SQLCHAR *)sql_str, SQL_NTS);
  if (SQL_SUCCEEDED(ret)) {
    SQLTCHAR node_name[256];
    ret = SQLBindCol(hdlStmt, 1, SQL_C_TCHAR, (SQLPOINTER)node_name,
                     sizeof(node_name), NULL);
    while (SQL_SUCCEEDED(ret = SQLFetchScroll(hdlStmt, SQL_FETCH_NEXT, 1))) {
      printf("Connected to node \n");
    }
  }
  SQLFreeHandle(SQL_HANDLE_STMT, hdlStmt);

  printf("Disconnecting.\n");
  ret = SQLDisconnect(hdlDbc);

  printf("Freeing handles...\n");
  SQLFreeHandle(SQL_HANDLE_DBC, hdlDbc);
  SQLFreeHandle(SQL_HANDLE_ENV, hdlEnv);

  printf("Done!\n");

  exit(EXIT_SUCCESS);
}
