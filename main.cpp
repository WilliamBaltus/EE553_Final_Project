#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "sqlite_dir/sqlite3.h"

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char* argv[]) {
    sqlite3* DB;
    char *sql;
    char *zErrMsg = 0;
    int db_curr = 0;
    const char* data = "";


    cout << "--------------------------------------------------" << endl;
    cout << "Welcome to SQLite Database System! " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Press 1 to continue.... " << endl;
    cout << "Press 0 to exit.... " << endl;

    int input;
    cin >> input;
    if(input == 0)
        exit(1);

    db_curr =  sqlite3_open_v2("C:\\Users\\wbalt\\CLionProjects\\Final_Project\\university.db",
                                   &DB, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    if( db_curr) {
        //cout << db_curr << endl;
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return(0);
    } else {
        //cout << db_curr << endl;
        fprintf(stderr, "Opened database successfully\n");
    }


    string tableName;
    //cin >> tableName;
    //string sqlStmt = "CREATE TABLE " + tableName + "(";

    /* Create SQL statement */
    sql = "DROP TABLE IF EXISTS STEVENS;"
          "CREATE TABLE STEVENS("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "PROFESSION        CHAR(50)," \
      "SALARY         REAL );";

    /* Execute SQL statement */
    db_curr= sqlite3_exec(DB, sql, callback, 0, &zErrMsg);

    if( db_curr != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    /* INSERT SQL statement */
    sql = "INSERT INTO STEVENS (ID,NAME,AGE,PROFESSION,SALARY) "  \
         "VALUES (1, 'William', 21, 'Student', 0.00 ); " \
         "INSERT INTO STEVENS (ID,NAME,AGE,PROFESSION,SALARY) "  \
         "VALUES (2, 'Julia', 21, 'Student', 0.00 ); "     \
         "INSERT INTO STEVENS (ID,NAME,AGE,PROFESSION,SALARY)" \
         "VALUES (3, 'Yousef', 31, 'Professor', 10.00 );" \
         "INSERT INTO STEVENS (ID,NAME,AGE,PROFESSION,SALARY)" \
         "VALUES (4, 'Alhussain', 25, 'Admin', 69000.00 );";

    /* Execute SQL statement */
    db_curr = sqlite3_exec(DB, sql, callback, 0, &zErrMsg);

    if( db_curr != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    /* Create SQL statement */
    sql = "SELECT * from STEVENS";

    /* Execute SQL statement */
    db_curr = sqlite3_exec(DB, sql, callback, (void*)data, &zErrMsg);

    if( db_curr != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }


    /* Delete SQL statement */
    sql = "DELETE from STEVENS where ID=2; " \
         "SELECT * from STEVENS";
    /* Execute SQL statement */
    db_curr = sqlite3_exec(DB, sql, callback, (void*)data, &zErrMsg);


    cout << "----------------------------------------------------" << endl;
    cout << "DELETING FROM TABLE " << endl;
    if( db_curr != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }


    // CLOSE SQL
    sqlite3_close(DB);
    return (0);
}
