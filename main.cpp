#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "sqlite_dir/sqlite3.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
};

int main(int argc, char* argv[]) {
    sqlite3* DB;
    char *sql;
    char *zErrMsg = 0;
    int db_curr = 0;

    db_curr =  sqlite3_open_v2("C:\\Users\\wbalt\\CLionProjects\\Final_Project\\university.db",
                                   &DB, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    if( db_curr) {
        cout << db_curr << endl;
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return(0);
    } else {
        cout << db_curr << endl;
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sql = "DROP TABLE IF EXISTS COMPANY;"
          "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";

    /* Execute SQL statement */
    db_curr= sqlite3_exec(DB, sql, callback, 0, &zErrMsg);

    if( db_curr != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    /* Create SQL statement */
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    /* Execute SQL statement */
    db_curr = sqlite3_exec(DB, sql, callback, 0, &zErrMsg);

    if( db_curr != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(DB);
    return (0);
}
