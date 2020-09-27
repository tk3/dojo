#include <stdio.h>
#include <stdlib.h>

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#define COLUMN_NAME_MAX 255

typedef struct _COLUMN_BINDING {
	char *name;
	char *value;
	SQLSMALLINT value_type;
	SQLULEN value_size;
	SQLSMALLINT decimal_digits;
	SQLSMALLINT nullable;

	struct _COLUMN_BINDING *next;
} COLUMN_BINDING;

int column_bind(SQLHSTMT *stmt, SQLSMALLINT num_results_col, COLUMN_BINDING **binding);
int column_binding_print(COLUMN_BINDING *binding);

int main() {
	SQLRETURN ret;
	SQLHENV env;
	SQLHDBC dbc;
	SQLHSTMT stmt;
	const char *conn_str = "DSN=mysqlitedb";
	const char *sql_str = "select name, page as p from books;";
	SQLSMALLINT num_results_col;
	COLUMN_BINDING *binding;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

	ret = SQLDriverConnect(dbc, NULL, (SQLCHAR *)conn_str, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
	if (!SQL_SUCCEEDED(ret)) {
		printf("SQLDriverConnect() failed.\n");
		exit(EXIT_FAILURE);
	} else {
		printf("SQLDriverConnect() succeeded\n");
	}

	SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  
	ret = SQLExecDirect(stmt, (SQLCHAR *)sql_str, SQL_NTS);
	if (SQL_SUCCEEDED(ret)) {
		SQLNumResultCols(stmt, &num_results_col);
		printf("number of results: %d\n", num_results_col);

		column_bind(stmt, num_results_col, &binding);
		column_binding_print(binding);
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);

	ret = SQLDisconnect(dbc);

	SQLFreeHandle(SQL_HANDLE_DBC, dbc);
	SQLFreeHandle(SQL_HANDLE_ENV, env);

	exit(EXIT_SUCCESS);
}

int column_bind(SQLHSTMT *stmt, SQLSMALLINT num_results_col, COLUMN_BINDING **binding)
{
	int i;
	COLUMN_BINDING *current_binding;
	COLUMN_BINDING *prev_binding = NULL;
	SQLLEN length_or_indicator;

	for (i = 1; i <= num_results_col; i++) {
		current_binding = (COLUMN_BINDING *)malloc(sizeof(COLUMN_BINDING));
		if (current_binding == NULL) {
			exit(1);
		}

		current_binding->name = (char *)malloc(COLUMN_NAME_MAX + 1);
		if (current_binding == NULL) {
			exit(1);
		}

		current_binding->next = NULL;

		if (prev_binding == NULL) {
			*binding = current_binding;
		} else {
			prev_binding->next = current_binding;
		}

		SQLDescribeCol(stmt,
				i,
				(SQLCHAR *)(current_binding->name),
				COLUMN_NAME_MAX,
				NULL,
				&(current_binding->value_type),
				&(current_binding->value_size),
				&(current_binding->decimal_digits),
				&(current_binding->nullable));

		current_binding->value = (char *)malloc(current_binding->value_size + 1);

		SQLBindCol(stmt,
				i,
				current_binding->value_type,
				current_binding->value,
				current_binding->value_size,
				&length_or_indicator);

		prev_binding = current_binding;
	}

	return 0;
}

int column_binding_print(COLUMN_BINDING *binding)
{
	COLUMN_BINDING *current_binding;
	for (current_binding = binding; current_binding; current_binding = current_binding->next) {
		printf("name: %s\n", current_binding->name);
		printf("data type: %d\n", current_binding->value_type);
		printf("data size: %ld\n", current_binding->value_size);
		printf("decimal digits: %d\n", current_binding->decimal_digits);
		printf("nullable: %d\n", current_binding->nullable);
		puts("");
	}

	return 0;
}

