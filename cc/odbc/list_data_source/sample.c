#include <stdio.h>

#include <sql.h>
#include <sqlext.h>

int main() {
  SQLHENV henv;
  SQLRETURN r;

  SQLCHAR ds_name[256];
  SQLSMALLINT ds_name_len;
  SQLCHAR driver_desc[256];
  SQLSMALLINT driver_desc_len;
  SQLUSMALLINT direction;

  r = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

  r = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);

  direction = SQL_FETCH_FIRST;
  r = SQLDataSources(henv, direction, ds_name, sizeof(ds_name), &ds_name_len,
                     driver_desc, sizeof(driver_desc), &driver_desc_len);
  while (SQL_SUCCEEDED(r)) {
    printf("Data Source\n");
    printf("  name: %.*s\n", ds_name_len, ds_name);
    printf("  description: %.*s\n", driver_desc_len, driver_desc);
    printf("\n");

    direction = SQL_FETCH_NEXT;
    r = SQLDataSources(henv, direction, ds_name, sizeof(ds_name), &ds_name_len,
                       driver_desc, sizeof(driver_desc), &driver_desc_len);
  }

  if (henv != SQL_NULL_HENV) {
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
  }

  return 0;
}
