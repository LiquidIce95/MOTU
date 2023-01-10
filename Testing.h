#include "DB.h"
#include "CImgScanner.h"
#ifndef PERFORMANCE_COCKPIT_TESTING_H
#define PERFORMANCE_COCKPIT_TESTING_H

//Test Code for testing Database

void Test_Open_createDB(){
    /*db object;
    string dbname = "/home/Dave/Desktop/dev/CLion_projects/Performance_Cockpit/DBs/newDB";
    string cols[] = {"ID INT PRIMARY KEY     NOT NULL, ",
                     "NAME           TEXT    NOT NULL, ",
                     "SURNAME          TEXT     NOT NULL, ",
                     "AGE            INT     NOT NULL, ",
                     "ADDRESS        CHAR(50), ",
                     "SALARY         REAL"};

    Create_table(dbname,"PERSON",cols);

    string vals[] = {"1,","'Dave',","'Sanchez',","26,","'pogo',","20.3"};
    Insert(dbname,"PERSON",vals);

    //object.Delete("PERSON","1");
    Select(dbname,"PERSON","NAME","'Dave'");


    SelectAll(dbname,"PERSON");

    cout<<"Log content: \n";
    cout<<db::log<<"\nLog end"<<endl;*/
    //MUST BE DONE BEFORE
    string dbname = "/home/Dave/Desktop/dev/CLion_projects/Performance_Cockpit/DBs/NewDB";
    string cols2[] = {"ID INT PRIMARY KEY     NOT NULL, ",
                      "NAME           TEXT    NOT NULL, ",
                      "SURNAME          TEXT     NOT NULL, ",
                      "AGE            INT     NOT NULL, ",
                      "ADDRESS        CHAR(50), ",
                      "SALARY         REAL"};
    string cols = "ID INT PRIMARY KEY     NOT NULL, "
                      "NAME           TEXT    NOT NULL, "
                      "SURNAME          TEXT     NOT NULL, "
                      "AGE            INT     NOT NULL, "
                      "ADDRESS        CHAR(50), "
                      "SALARY         REAL";

    string Tablename = "PERSON";


    string sql = "CREATE TABLE "+Tablename+"( ";
    sql+=cols;
    sql += ");";


    //params::para1 = dbname;
    //params::para2 = Tablename;
    //params::para3 = sql;

    //sql = merger(cols);
    Create_table(dbname,Tablename,cols);
    string vals =    "1,"
                     "'Dave',"
                     "'Sanchez',"
                     "26,"
                     "'pogo',"
                     "20.3";

    Insert(dbname,Tablename,vals);

    //Delete(dbname,Tablename,"1","ID");
    Select(dbname,Tablename,"NAME","'Dave'");
    cout<<db::log<<endl;

    string col = "ADDRESS";
    string val = "'PIGI'";
    string searchcol = "ID";
    string searchval = "1";

    Update(dbname,Tablename,searchcol,searchval,col,val);

    string vals2 =   "2,"
                     "'Dorian',"
                     "'HeldenHammer',"
                     "22,"
                     "'pork',"
                     "20.2";

    Insert(dbname,Tablename,vals2);

    SelectAll(dbname,Tablename);

    //sqlite3* DB;
    //SampleQueries2(dbname,Tablename,sql);
    //SampleQueries();
}
void ScannerTests(){
    scanner("");

}



#endif //PERFORMANCE_COCKPIT_TESTING_H


