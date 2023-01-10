//
// Created by Dave on 6/27/21.
//
#include "CImg.h"
#include <sqlite3.h>
#include <map>
#include <experimental/filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include<unistd.h>
#include "CImgScanner.h"
#include<thread>

#ifndef PERFORMANCE_COCKPIT_DB_H
#define PERFORMANCE_COCKPIT_DB_H
//CAUTION: very sensible, cleanlog was not tested!
using namespace std;

/*****************************************DONT TOUCH ANY OF THIS!!!!************************************************************************/

//sound functions
void play_achieve(){
    system("play /sound/achieve.mp3");
}
void play_pomostart(){
    system("play /sound/pomostart.mp3");
}
void play_pomopause(){
    system("play /sound/bellpause.mp3");
}
void play_task(){
    system("play /sound/taskfinshort.mp3");
}
void play_victory(){
    thread sound;
    sound = thread{system,"play /sound/dayvictory.mp3"};
    CImg<unsigned char>img("/Pics/Victory_9.jpg");
    CImgDisplay disp;
    img.display(disp);
    while(!disp.is_closed()){

        if(disp.is_keyESC()){
            disp.close();
            system("pkill play");
            sound.join();

        }
    }
}

string dbprefix = "";
string dbprefix2 = "";

string dbrelprefix = dbprefix2;

class db{
public:
    static string log;
    sqlite3*DB;
    //Can Also Create new DB
    void Openclose_DB(int i, string dbname){
        if(i == 1){
            int exit = 0;
            string name = dbname+".db";
            exit = sqlite3_open(name.c_str(),&this->DB);
            if(exit){
                cerr<<"Error open_DB"<<sqlite3_errmsg(this->DB)<<endl;
            } else {
                cout<<"DB opened successfully"<<endl;
            }
        } else {
            sqlite3_close(this->DB);
            cout<<"DB closed"<<endl;
        }

    }
};
string db::log;

int callback(void* data, int argc, char** argv, char** azColName)
{
    string Logstring = "";
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    void* vp = static_cast<void*>(new string(""));
    string *sp = static_cast<string*>(vp);
    Logstring = *sp;
    delete sp;

    for (i = 0; i < argc; i++) {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        //conversion of char to string
        string tmp_string(azColName[i]);
        string tmp_string2(argv[i]);
        Logstring += tmp_string+" = "+tmp_string2+"\n";
    }

    db::log += Logstring;
    //printf("\n");
    return 0;
}
void cleanlog(){
    db::log = "";
}
//TESTED
void Create_table_exec(string dbname, string Tablename, string cols){
    db object;
    object.Openclose_DB(1,dbname);

    //cols is one line foreach index
    string tablename = Tablename;
    char* messageError;

    char* msgErr;
    int exit = sqlite3_exec(object.DB, cols.c_str(), NULL,0,&msgErr);

    if(exit){
        cerr<<"Error Create Table" << endl;
        sqlite3_free(messageError);
    } else {
        cout << " creation successfull"<<endl;
    }
    object.Openclose_DB(2,dbname);

}
void Create_table(string dbname, string Tablename, string cols){
    cleanlog();
    string sql = "CREATE TABLE "+Tablename+"( ";
    sql+=cols;
    sql += ");";

    Create_table_exec(dbname,Tablename,sql);

}
//TESTED
void Insert_exec(string dbname,string Tablename, string cols){
    db object;
    object.Openclose_DB(1,dbname);

    //cols is one line foreach index
    string tablename = Tablename;
    char* messageError;

    char* msgErr;
    int exit = sqlite3_exec(object.DB, cols.c_str(), NULL,0,&msgErr);

    if(exit){
        cerr<<"Error Insert into" << endl;
        sqlite3_free(messageError);
    } else {
        cout << " Insertion successfull"<<endl;
    }
    object.Openclose_DB(2,dbname);

}
void Insert(string dbname,string Tablename, string cols){
    cleanlog();
    string sql = "INSERT INTO "+Tablename+" VALUES(";
    sql += cols;
    sql += ");";

    Insert_exec( dbname, Tablename,sql);
}
//TESTED
void Delete_exec(string dbname,string Tablename, string query){
    db object;
    object.Openclose_DB(1,dbname);
    char* msgerr;

    int exit = sqlite3_exec(object.DB,query.c_str(),NULL,0,&msgerr);

    if(exit){
        cerr<< " Error Delete"<<endl;
        sqlite3_free(msgerr);
    } else {
        cout<<" Deleting successfull"<<endl;
    }
    object.Openclose_DB(2,dbname);

}
void Delete(string dbname,string Tablename, string searchval,string searchcol){
    cleanlog();
    string query = "DELETE FROM "+Tablename+" WHERE "+searchcol+" = "+searchval+";";
    Delete_exec(dbname,Tablename, query);
}
//TESTED
void Delete_All_exec(string dbname,string Tablename,string query){
    db object;
    object.Openclose_DB(1,dbname);
    char* msgerr;

    int exit = sqlite3_exec(object.DB,query.c_str(),NULL,0,&msgerr);

    if(exit){
        cerr<< " Error Delete"<<endl;
        sqlite3_free(msgerr);
    } else {
        cout<<" Deleting successfull"<<endl;
    }
    object.Openclose_DB(2,dbname);
}
void Delete_All(string dbname,string Tablename){
    cleanlog();
    string query = "DELETE FROM "+Tablename+";";
    Delete_exec(dbname,Tablename, query);
}
//TESTED
void Select_exec(string dbname,string Tablename, string sql){
    db object;
    object.Openclose_DB(1,dbname);
    char* msgerr;

    int exit = sqlite3_exec(object.DB,sql.c_str(),callback, 0, &msgerr);

    if(exit){
        cerr<< " Error Selection"<<endl;
        sqlite3_free(msgerr);
    } else {
        cout<<" Selection successfull"<<endl;
    }
    object.Openclose_DB(2,dbname);

}
void Select(string dbname,string Tablename, string col,string val){
    cleanlog();
    string sql = "SELECT * FROM "+Tablename+" WHERE "+col+" = "+val;

    Select_exec(dbname,Tablename,sql);
}
//tested
void Update_exec(string dbname,string Tablename,string query){

    db object;
    object.Openclose_DB(1,dbname);
    char* msgerr;

    int exit = sqlite3_exec(object.DB,query.c_str(),NULL,0,&msgerr);
    sqlite3_free(msgerr);
    if(exit){
        cerr<< " Error Update"<<endl;
        sqlite3_free(msgerr);
    } else {
        cout<<" Update successfull"<<endl;
    }
    object.Openclose_DB(2,dbname);

}
void Update(string dbname,string Tablename,string searchcol ,string searchval, string col, string val){
    cleanlog();
    string query = "UPDATE "+Tablename+" set "+col+" = "+val+" WHERE "+searchcol+"="+searchval+";";
    cout<<query<<endl;
    Update_exec(dbname,Tablename,query);
}
//TESTED
void SelectAll_exec(string dbname,string sql){
    db object;
    object.Openclose_DB(1,dbname);
    char* msgerr;

    int exit = sqlite3_exec(object.DB,sql.c_str(),callback, 0, &msgerr);

    if (exit)
        cerr << "Error SELECT" << endl;
    else {
        cout << "Operation OK!" << endl;
    }
    object.Openclose_DB(2,dbname);
}
void SelectAll(string dbname,string Tablename){
    cleanlog();
    string sql = "SELECT * FROM "+Tablename;
    SelectAll_exec(dbname,sql);
}

void Update_rowid_exec(string dbname, string sql){
    db object;
    object.Openclose_DB(1,dbname);
    char* msgerr;

    int exit = sqlite3_exec(object.DB,sql.c_str(),callback, 0, &msgerr);

    if (exit)
        cerr << "Error Updaterowid" << endl;
    else {
        cout << "Operation OK!" << endl;
    }
    object.Openclose_DB(2,dbname);
}
void Update_rowid(string dbname, string Tablename, string updatecol, string updateval, string rowid){
    //UPDATE `Battlerecords` SET `TUESDAY`=? WHERE _rowid_='6';
    //UPDATE `Battlerecords` SET `TUESDAY`='foo' WHERE _rowid_='6';

    cleanlog();
    string sql = "UPDATE `"+Tablename+"` SET `"+updatecol+"`='"+updateval+"' WHERE _rowid_='"+rowid+"';";
    cout<<sql<<endl;
    Update_rowid_exec(dbname,sql);

}




















//UpdateBattlerecords
///Auxiliary Structs Gamefieles******************************************************************************************************************************************************************
int get_time(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();

    //std::cout << str << std::endl;

    string love = str.substr(11,2)+str.substr(14,2);
    return stoi(love);
}
int get_min(){
    int time = get_time();
    string Time = to_string(time);
    int min = (Time[Time.size()-2]+Time[Time.size()-1])-'0';
    return min;
}
int gettimerow(){

    int hour = 6;
    int minutes = 0;
    int intervall_min = 30;
    int store = 0;
    vector<int> timetable;
    for( int i = 0; i < 31; i++){
        minutes += intervall_min;
        if(minutes == 60){
            minutes = 0;
            hour++;
        }
        string minut;
        if(minutes<10){
            minut = "0"+ to_string(minutes);
        } else {
            minut = to_string(minutes);
        }
        if(hour<10){
            store = stoi(to_string(hour)+minut);
        } else {
            store = stoi(to_string(hour)+minut);
        }
        timetable.push_back(store);
        //cout<<"time::: "<<store<<endl;
    }
    int time = get_time();

    for(int i = 0; i < timetable.size()-1; i++){
        if(timetable[i] <= time && time <= timetable[i+1]){
            return i+1;
            if(i+1 > 31){
                return 31;
            }
        }
    }

    return 31;

}
struct GameData{
    static string Gamefile;
    static int Week;
    static int day;
    static int maxpres;
};
string fileretriever(){

    //Load last game loaded
    db main;
    string dbname = dbrelprefix+"/DBs/mainDB";

    Select(dbname,"SaveGames","Status","'1'");
    string log = main.log;
    string Gfile = "";

    cout<<"logstart: "<<endl;
    cout<<main.log<<endl;
    cout<<"logend: "<<endl;

    for(int i = 7; log[i] != '\n'; i++ ){
        Gfile += log[i];
    }

    cout<<Gfile<<endl;

    return Gfile;
}
string GameData::Gamefile = fileretriever();
bool checkstring(int index, string sub,string main){
    if(index > main.size() || sub.size()> main.size() || sub[sub.size()-1] != main[index]){
        //retard
        //cout<<"retard"<<endl;
        return false;
    } else {
        int c = 0;
        for(int i = 0; i < sub.size(); i++){
            if(sub[sub.size()-1-i] != main[index-i]){
                i = sub.size();
            }else{
                c++;
            }
        }
        if(c == sub.size()){
            return true;
        } else {
            return false;
        }
    }
}
int next_endl(int index, string main){
    int c = 0;

    while(index+c <= main.size()-1){
        if(main[index+c] == '\n'){
            return c;
        } else {
            c++;
        }
    }
    return c;
}
int get_last_id(string dbname, string table){
    cleanlog();
    SelectAll(dbname,table);
    string log = db::log;

    if(log != ""){
        int index =0;
        int ans =0;
        for(int i = 0; i < log.size(); i++){
            if (checkstring(index,"ID = ",log)){
                ans = stoi(log.substr(index+1, next_endl(index+1,log)));
            }
            index++;
        }
        return ans;
    } else {
        return 1;
    }
}
string Select_val(string dbname, string table, string searchcol, string searchval, string selectcol){
    Select(dbname,table,searchcol,searchval);
    int index =0;
    string log = db::log;
    string ans = "";
    for(int i = 0; i < log.size(); i++){
        if (checkstring(index,selectcol+" = ",log)){
            ans = log.substr(index+1, next_endl(index+1,log));
        }
        index++;
    }
    return ans;
}
int get_date(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();

    std::cout << str << std::endl;

    string love = str.substr(6,4)+str.substr(3,2)+str.substr(0,2);

    return stoi(love);
}
int get_currweek(){
    int week = 0;
    
    db main;
    string dbname = dbrelprefix+"/DBs/mainDB";
    Select(dbname,"SaveGames","Status","'1'");
    string log = main.log;

    string startdate = "";

    for(int i = 0; i<log.size()-1;i++){
        if(checkstring(i,"Date = ",log)){
            startdate = log.substr(i+1, next_endl(i+1,log));
        }
    }

    //cout<<startdate<<"_ is startdate"<<endl;
    string currdate = to_string(get_date());
    //cout<<currdate<<"_ is currdate"<<endl;

    string curryear = currdate.substr(0,4);
    string startyear = startdate.substr(0,4);
    //cout<<curryear<<"_ is curryear"<<endl;
    //cout<<startyear<<"_ is startyear"<<endl;

    string currmonth = currdate.substr(4,2);
    string startmonth = startdate.substr(4,2);
    //cout<<currmonth<<"_ is currmonth"<<endl;
    //cout<<startmonth<<"_ is startmonth"<<endl;

    string currday = currdate.substr(6,2);
    string startday = startdate.substr(6,2);
    //cout<<currday<<"_ is currday"<<endl;
    //cout<<startday<<"_ is startday"<<endl;
    
    int Curryear = stoi(curryear);
    int Currmonth = stoi(currmonth);
    int Currday = stoi(currday);
    
    int Startyear = stoi(startyear);
    int Startmonth = stoi(startmonth);
    int Startday = stoi(startday);

    week = (Curryear-Startyear)*52;

    if(Currmonth < Startmonth){
        week -= (Startmonth-Currmonth)*4;
    } else {
        week+=(Currmonth-Startmonth)*4;
    }
    int dayplus = 0;
    if(Currday < Startday){
        int diff = Startday-Currday;
        while(diff>=7){
            diff-=7;
            dayplus++;
        }
        week -= dayplus;
    } else {
        int diff = Currday-Startday;
        while(diff>=7){
            diff-=7;
            dayplus++;
        }
        week += dayplus;    }
    cout<<" WEEK _:__"<<week<<endl;
    return week;
}
int get_currday(){
    const string DAY[]={"Sun","Mon","Tue",
                        "Wed","Thu","Fri","Sat","Sun"};
    // i wish i could cut this out,
    // but apparently it is needed
    // {
    time_t rawtime;
    tm * timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    // }
    int wday=timeinfo->tm_wday;
    if(wday == 0){
        wday = 7;
    }
    cout << "Today is: " << DAY[wday] << "\n" <<wday<< endl;
    cout<<"get_currday"<<endl;

    return wday;
}
int GameData::Week = get_currweek();
int GameData::day = get_currday();
int GameData::maxpres = stoi(Select_val(dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile,"Globalstats","ID","1","Max_Prestige"));



const unsigned char
white[]  = { 255, 255, 255 }, black[] = { 0, 0, 0 }, red[] = { 120, 50, 80 },
yellow[] = { 200, 155, 0 }, green[] = { 30, 200, 70 }, purple[] = { 175, 32, 186 },
blue[] = { 55, 140, 185 }, grey[] = { 127, 127, 127 }, darkblue[] = {20,100,120},
darkgrey[] = {60,60,60}, darkpurple[] = {137,54,149}, strongyellow[] = {255,215,40},
rose[] = {255,192,203},cyan[] = {168,227,241},olive[] = {165,187,104}, lightpink[] = {242,181,236},
brightred[] = {218,64,64}, creme[] = {248,236,223}, darkgold[] = {149,140,102},lightgreen[] = {183,255,177},
lightcyan[] = {157,232,208},red90[] = {221,83,83},red80[] = {225,102,102},red70[] = {229,121,121},red60[] = {232,140,140},
red50[] = {236,159,159}, red40[] ={240,178,178}, red30[] ={243,197,197}, red20[] = {247,216,216};

map<int,const unsigned char *> hashi;
map<string , const unsigned char *> mapi;
map<const unsigned char*,string> mepi;
map<int, string> daily;
map<int, const unsigned char*> heatmap;

bool daily_initfun(){
    daily[1] = "MONDAY";
    daily[2] = "TUESDAY";
    daily[3] = "WEDNESDAY";
    daily[4] = "THURSDAY";
    daily[5] = "FRIDAY";
    daily[6] = "SATURDAY";
    daily[7] = "SUNDAY";

    return true;
}

bool hashi_innitfun(){
    heatmap[100] = brightred;
    heatmap[90] = red90;
    heatmap[80] = red80;
    heatmap[70] = red70;
    heatmap[60] = red60;
    heatmap[50] = red50;
    heatmap[40] = red40;
    heatmap[30] = red30;
    heatmap[20] = red20;
    heatmap[10] = white;

    hashi[0] = white;
    hashi[1] = black;
    hashi[2] = red;
    hashi[3] = yellow;
    hashi[4] = green;
    hashi[5] = purple;
    hashi[6] = blue;
    hashi[7] = grey;
    hashi[8] = darkblue;
    hashi[9] = darkgrey;
    hashi[10] = darkpurple;
    hashi[11] = strongyellow;
    hashi[12] = rose;
    hashi[13] = cyan;
    hashi[14] = olive;
    hashi[15] = lightpink;
    hashi[16] = brightred;
    hashi[17] = creme;
    hashi[16] = darkgold;
    hashi[17] = lightgreen;
    hashi[18] = lightcyan;


    mapi[""] = white;
    mepi[white] = "";
    return true;
}
bool hashi_init = hashi_innitfun();
bool daily_init = daily_initfun();

///Auxiliary Class
void showAchiev(string text){
    CImg<unsigned char> img((dbrelprefix+"/Pics/Achievement.jpg").c_str());
    CImgDisplay new_disp(img,"Achievement");
    img.draw_text(0,0,text.c_str(),brightred,20,1,40,40);
    img.display(new_disp);
    usleep(4*1000000);
    new_disp.close();
}
class Pomos{
public:
    int x;
    int y;
    int x1;
    int y1;
    int fontsize;
    string text;
    int reward;
    string progress;
    string target;
    string unlocked;
    const unsigned char *color;
    const unsigned char *bordercol;
    void (*fun)(int week,vector<vector<Pomos>> arr,vector<vector<Pomos>> Colorgrid, int i_end, int j_end);
    vector<vector<Pomos>> (*fun2)(int week,vector<vector<Pomos>> arr);
    void (*fun3)();
    int (*fun4)(int week, int mode);
    vector<string> trigger;

    Pomos(){
        this->color = white;
        this->bordercol = black;
        this->x = 0;
        this->y = 0;
        this->x1 = 0;
        this->y1 = 0;
        this->fontsize = 15;
        this->text = "";
    }

    void texttopomos(){
        this->text = scanner("Type in Associated work");
    }
    CImg<unsigned char> draw_this(CImg<unsigned char> img){
        img.draw_rectangle(this->x,this->y,this->x1,this->y1,this->color,1);
        img.draw_line(this->x,this->y,this->x,this->y1,this->bordercol,1);
        img.draw_line(this->x1,this->y,this->x1,this->y1,this->bordercol,1);
        img.draw_line(this->x,this->y,this->x1,this->y,this->bordercol,1);
        img.draw_line(this->x,this->y1,this->x1,this->y1,this->bordercol,1);
        img.draw_text(this->x+5,this->y+5,this->text.c_str(),this->bordercol,20,1,this->fontsize,this->fontsize);

        return img;
    }

    void updateAchievements(string dbname){
        for(int i = 0;i<this->trigger.size();i++){
            if(this->trigger[i] != ""){
                int progress = stoi(Select_val(dbname,"Achievements","NAME","'"+this->trigger[i]+"'","PROGRESS"));
                int reward = stoi(Select_val(dbname,"Achievements","NAME","'"+this->trigger[i]+"'","REWARD"));
                int target = stoi(Select_val(dbname,"Achievements","NAME","'"+this->trigger[i]+"'","TARGET"));
                int unlocked = stoi(Select_val(dbname,"Achievements","NAME","'"+this->trigger[i]+"'","UNLOCKED"));

                progress++;
                if(progress >= target){
                    thread bu;
                    bu = thread{play_achieve};
                    unlocked++;
                    progress = 0;
                    Update(dbname,"Achievements","NAME","'"+this->trigger[i]+"'","UNLOCKED", to_string(unlocked).c_str());
                    string sellog2 = Select_val(dbname,"Globalstats","_rowid_","1","VAL2");

                    Update_rowid(dbname,"Globalstats","VAL2", to_string(stoi(sellog2)+reward),"1");
                    Update_rowid(dbname,"Achievements","PROGRESS", "0","1");
                    //
                    showAchiev(this->trigger[i]);

                    bu.join();

                }
                Update(dbname,"Achievements","NAME","'"+this->trigger[i]+"'","PROGRESS", to_string(progress).c_str());



            }
        }

    }
    void claimreward(){
        string dbname = dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile;

        int week = get_currweek()-1;
        int rowid = gettimerow()+week*31;
        int day = get_currday();
        cout<<"Test"<<endl;
        string curr_day = daily[day];
        string rowid_ = to_string(rowid);

        string sellog = Select_val(dbname,"Battlerecords","_rowid_",rowid_,curr_day);

        int preprestige = 0;
        if(sellog != ""){
            preprestige += stoi(sellog);
        }
        preprestige += this->reward;

        string prestige = to_string(preprestige);

        cout<<"lasid__"<<get_last_id(dbname,"Log")<<"__lasid"<<endl;

        Update_rowid(dbname,"Battlerecords",curr_day,prestige,rowid_);
        string sellog2 = Select_val(dbname,"Globalstats","_rowid_","1","VAL2");

        Update_rowid(dbname,"Globalstats","VAL2", to_string(stoi(sellog2)+this->reward),"1");

        if(preprestige > GameData::maxpres){
            Update_rowid(dbname,"Globalstats","Max_Prestige",prestige,"1");
            GameData::maxpres = preprestige;
        }

        string d = "'"+to_string(get_last_id(dbname,"Log")+1)+"'"+ ", "+"'"+to_string(get_currday())+"'"+", "+ "'"+to_string(get_currweek())+"'"+", "+"'"+this->text+"'"+", "+"''"+", "+
                "'"+to_string(this->reward)+"'"+", "+"''"+", "+"''";
        Insert(dbname,"Log",d);

        this->updateAchievements(dbname);
    }
    //Only for Emergency or testing
    void claimreward(int id){
        string dbname = dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile;

        int rowid = id;
        int day = get_currday();

        string curr_day = daily[day];
        string rowid_ = to_string(rowid);

        string sellog = Select_val(dbname,"Battlerecords","_rowid_",rowid_,curr_day);
        cout<<sellog<<endl;

        int preprestige = 0;
        if(sellog != ""){
            preprestige += stoi(sellog);
        }
        preprestige += this->reward;

        string prestige = to_string(preprestige);

        cout<<"lasid__"<<get_last_id(dbname,"Log")<<endl;

        Update_rowid(dbname,"Battlerecords",curr_day,prestige,rowid_);
        string sellog2 = Select_val(dbname,"Globalstats","_rowid_","1","VAL2");

        Update_rowid(dbname,"Globalstats","VAL2", to_string(stoi(sellog2)+this->reward),"1");

        if(preprestige > GameData::maxpres){
            Update_rowid(dbname,"Globalstats","Max_Prestige",prestige,"1");
            GameData::maxpres = preprestige;
        }

        string d = "'"+to_string(get_last_id(dbname,"Log")+1)+"'"+ ", "+"'"+to_string(get_currday())+"'"+", "+ "'"+to_string(get_currweek())+"'"+", "+"'"+this->text+"'"+", "+"''"+", "+
                "'"+to_string(this->reward)+"'"+", "+"''"+", "+"''";
        Insert(dbname,"Log",d);

    }

};
CImg<unsigned char> draw_thing(int i_start, int j_start,int i_end, int j_end,vector<vector<Pomos>> arr,CImg<unsigned char> img){

    for(int i = i_start; i< i_end;i++){
        for(int j = j_start; j< j_end;j++){
            img.draw_rectangle(arr[i][j].x,arr[i][j].y,arr[i][j].x1,arr[i][j].y1,arr[i][j].color,1);
            img.draw_line(arr[i][j].x,arr[i][j].y,arr[i][j].x,arr[i][j].y1,arr[i][j].bordercol,1);
            img.draw_line(arr[i][j].x1,arr[i][j].y,arr[i][j].x1,arr[i][j].y1,arr[i][j].bordercol,1);
            img.draw_line(arr[i][j].x,arr[i][j].y,arr[i][j].x1,arr[i][j].y,arr[i][j].bordercol,1);
            img.draw_line(arr[i][j].x,arr[i][j].y1,arr[i][j].x1,arr[i][j].y1,arr[i][j].bordercol,1);
            img.draw_text(arr[i][j].x+5,arr[i][j].y+5,arr[i][j].text.c_str(),arr[i][j].bordercol,20,1,arr[i][j].fontsize,arr[i][j].fontsize);
        }
    }

    return img;
}

///Aux Methods


///Aux Methods 2
bool battlerecordsfill(){
    cleanlog();
    cout<<"BAttlerecords fill"<<endl;
    cout<<" currweek2 : "<<GameData::Week<<endl;

    string db = dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile;
    SelectAll(db,"Battlerecords");
    int index =0;
    string log = db::log;
    //cout<<"log "<<log<<endl;
    int ans = 0;
    int max = 0;

    if( log != ""){
        for(int i = 0; i < log.size(); i++){
            if (checkstring(index,"WEEK = ",log)){
                ans = stoi(log.substr(index+1, next_endl(index+1,log)));
                if(ans > max){
                    max = ans;
                }
            }
            index++;
        }

        int j = GameData::Week-max;
        int hour = 6;
        int minutes = 0;
        int intervall_min = 30;
        vector<Pomos> timetable;
        for( int i = 0; i < 31; i++){
            timetable.push_back(Pomos());
            minutes += intervall_min;
            if(minutes == 60){
                minutes = 0;
                hour++;
            }
            string minut;
            if(minutes<10){
                minut = "0"+ to_string(minutes);
            } else {
                minut = to_string(minutes);
            }
            if(hour<10){
                timetable[i].text = " "+to_string(hour)+" : "+ minut;
            } else {
                timetable[i].text = to_string(hour)+" : "+ minut;
            }
            timetable[i].color = hashi[11];
        }

        string sql;
        for(int i = 0; i < j; i++){
            for(int k = 0; k< 31; k++){
                sql = to_string(max+i+1)+", "+"'"+timetable[k].text+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'";
                //cout<<"sql string ..."<<endl;
                //cout<<sql<<endl;
                Insert(db,"Battlerecords",sql);
            }
        }

    }else {
        cout<<"else _"<<endl;
        int j = GameData::Week;
        int hour = 6;
        int minutes = 0;
        int intervall_min = 30;
        vector<Pomos> timetable;
        for( int i = 0; i < 31; i++){
            timetable.push_back(Pomos());
            minutes += intervall_min;
            if(minutes == 60){
                minutes = 0;
                hour++;
            }
            string minut;
            if(minutes<10){
                minut = "0"+ to_string(minutes);
            } else {
                minut = to_string(minutes);
            }
            if(hour<10){
                timetable[i].text = " "+to_string(hour)+" : "+ minut;
            } else {
                timetable[i].text = to_string(hour)+" : "+ minut;
            }
            timetable[i].color = hashi[11];
        }

        string sql;
        for(int i = 0; i < j+1; i++){
            for(int k = 0; k< 31; k++){
                sql = to_string(max+i+1)+", "+"'"+timetable[k].text+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'"+", "+"'"+""+"'";
                //cout<<"sql string ..."<<endl;
                //cout<<sql<<endl;
                Insert(db,"Battlerecords",sql);
            }
        }
    }

    return true;
}
bool uptodaterec = battlerecordsfill();

vector<vector<Pomos>> loadplanfun( int week,vector<vector<Pomos>> arr){
    string db = dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile;
    vector<vector<Pomos>> ans;
    //Now Times and Days
    arr[0][0].color = black;
    arr[1][0].text = "Monday";
    arr[2][0].text = "Tuesday";
    arr[3][0].text = "Wednesday";
    arr[4][0].text = "Thursday";
    arr[5][0].text = "Friday";
    arr[6][0].text = "Saturday";
    arr[7][0].text = "Sunday";


    for(int i = 1; i < 8; i++){
        arr[i][0].color = hashi[11];
    }

    int hour = 6;
    int minutes = 0;
    int intervall_min = 30;

    for( int i = 1; i < 32; i++){
        minutes += intervall_min;
        if(minutes == 60){
            minutes = 0;
            hour++;
        }
        string minut;
        if(minutes<10){
            minut = "0"+ to_string(minutes);
        } else {
            minut = to_string(minutes);
        }
        if(hour<10){
            arr[0][i].text = " "+to_string(hour)+" : "+ minut;
        } else {
            arr[0][i].text = to_string(hour)+" : "+ minut;
        }
        arr[0][i].color = hashi[11];
    }

    if(week == 0){

        //load sampleplan
        SelectAll(db,"COLORCODE");
        string colorcode = db::log;

        SelectAll(db,"SampleBattleplan");
        string sampledb = db::log;

        //update arr elements with intel from db
        int index = 0;
        //cout<<sampledb.size()-1<<endl;
        //cout<<sampledb<<endl;

        if(sampledb != ""){
            int x = 1;
            int y = 1;
            while(index <= sampledb.size()-2){
                if(checkstring(index,"ID = ",sampledb)){
                    int id = stoi(sampledb.substr(index+1, next_endl(index+1,sampledb)));
                    //cout<<" ID catcher: "<<id<<endl;
                    y = id;
                } else if (checkstring(index,"MONDAY = ",sampledb)){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Monday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"TUESDAY = ",sampledb)){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Tuesday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"WEDNESDAY = ",sampledb)){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Wednesday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"THURSDAY = ",sampledb)){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Thursday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"FRIDAY = ",sampledb)){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Friday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"SATURDAY = ",sampledb)){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Saturday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"SUNDAY = ",sampledb)){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Sunday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x = 1;
                }
                //cout<<sampledb[index]<<" at "<<index<<endl;
                index++;
            }

            x = 1;
            y = 1;
            index = 0;
            string Name;
            int colr;

            //cout<<colorcode<<endl;

            while(index <= colorcode.size()-2){
                if(checkstring(index,"NAME = ",colorcode)){
                    Name = colorcode.substr(index+1,next_endl(index+1,colorcode));
                } else if (checkstring(index,"COLOR = ",colorcode)){
                    colr = stoi(colorcode.substr(index+1, next_endl(index+1,colorcode)));
                    mapi[Name] = hashi[colr];

                }
                index++;
            }

            mapi[""] = white;

            if(mapi[""] == NULL){
                cout<<" test1 "<<endl;
            } else if (mapi["zubi"] == NULL){
                cout<<" test2 "<<endl;
            }

            //probably .text is not the same string??
            for(int i = 1; i < 8; i++){
                for(int j = 1; j< 32; j++){
                    arr[i][j].color = mapi[arr[i][j].text];
                    mepi[arr[i][j].color] = arr[i][j].text;
                }
            }
            cout<<arr.size()<<"_"<<arr[0].size()<<endl;
            cout<<"finish"<<endl;

            return arr;
        }
        else {
            cout<<"no sample"<<endl;
            string anw = scanner("No sample Battleplan made \n Please make one first \n press ENTER to continue");
            return arr;
        }


    } else {
        //load week************************************************************************************************************************************

        SelectAll(db,"Battlerecords");
        string sampledb = db::log;

        if(sampledb == ""){
            cout<<"no sample"<<endl;
            string anw = scanner("No sample Battleplan made \n Please make one first \n press ENTER to continue");
            return arr;
        }

        //make all white again
        for(int i = 1; i <arr.size();i++){
            for(int j = 1; j< arr[i].size();j++){
                arr[i][j].color = white;
            }
        }

        //update arr elements with intel from db
        int index = 0;
        //cout<<sampledb.size()-1<<endl;
        //cout<<sampledb<<endl;
        bool correct_week = false;

        if(sampledb != ""){
            int x = 1;
            int y = 1;
            while(index <= sampledb.size()-2){
                if (checkstring(index,"WEEK = ",sampledb) ){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Week catcher: "<<text<<endl;
                    if(week == stoi(text)){
                        correct_week = true;

                    }else {
                        correct_week = false;
                    }
                } else if (checkstring(index,"MONDAY = ",sampledb)&& correct_week){
                    x= 1;
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Monday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"TUESDAY = ",sampledb)&& correct_week){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Tuesday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"WEDNESDAY = ",sampledb)&& correct_week){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Wednesday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"THURSDAY = ",sampledb)&& correct_week){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Thursday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"FRIDAY = ",sampledb)&& correct_week){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    cout<<" Friday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                    if(text != ""){
                        cout<<"huhuuu"<<endl;
                    }
                }else if (checkstring(index,"SATURDAY = ",sampledb)&& correct_week){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Saturday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    x++;
                }else if (checkstring(index,"SUNDAY = ",sampledb)&& correct_week){
                    string text = sampledb.substr(index+1, next_endl(index+1,sampledb));
                    //cout<<" Sunday catcher: "<<text<<endl;
                    arr[x][y].text = text;
                    y++;
                }

                //cout<<sampledb[index]<<" at "<<index<<endl;
                index++;
            }

            cout<<"finish"<<endl;

            return arr;
        } else {
            return arr;
        }
    }


    return ans;
}
void saveplan(int week,vector<vector<Pomos>> arr,vector<vector<Pomos>> Colorgrid,int i_end, int j_end){
    //Save Current plan in DB

    string db = dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile;

    cout<<db<<endl;
    if(week == 0){
        //Need to update text of pomos in arr, via color code
        //Here we can always delete
        Delete_All(db,"SampleBattleplan");
        Delete_All(db,"COLORCODE");
        for(int i = 1; i< i_end;i++){
            for(int j = 1; j< j_end; j++){
                for(int i2= 0;i2<Colorgrid.size();i2++){
                    for(int y2 = 0; y2 < Colorgrid[i2].size(); y2++){
                        if (arr[i][j].color == Colorgrid[i2][y2].color){
                            arr[i][j].text = Colorgrid[i2][y2].text;
                        }
                    }
                }
            }
        }

        string sql = "";
        //First iterate on y
        for(int j = 1; j < j_end; j++){
            sql += to_string(j)+", ";
            for( int i = 0; i < i_end; i++){
                sql += "'"+arr[i][j].text+"'"+", ";
            }
            sql+= "0";
            cout<<sql<<endl;
            Insert(db,"SampleBattleplan",sql);
            sql = "";

        }

        //Now Colorcode
        for(int i2= 0;i2<Colorgrid.size();i2++){
            for(int y2 = 0; y2 < Colorgrid[i2].size(); y2++){
                if(Colorgrid[i2][y2].text != ""){
                    for ( int k = 0; k < 18; k++){
                        if(hashi[k] == Colorgrid[i2][y2].color){
                            Insert(db,"COLORCODE","'"+Colorgrid[i2][y2].text+"'"+", "+to_string(k));
                        }
                    }
                }
            }
        }
    }

    else {

    }

}


#endif //PERFORMANCE_COCKPIT_DB_H
