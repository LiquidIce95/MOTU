//
// Created by Dave on 6/27/21.
//
// write all functions here, so we can access them also for AI
#include "DB.h"

#ifndef PERFORMANCE_COCKPIT_CAMPAIGN_H
#define PERFORMANCE_COCKPIT_CAMPAIGN_H

namespace fs = std::experimental::filesystem;
/*if(input == "1"){
    cout<<"loading start"<<endl;
    string path = "/home/Dave/Desktop/dev/CLion_projects/Performance_Cockpit/DBs/Campaigns/";
    string dbname = "/home/Dave/Desktop/dev/CLion_projects/Performance_Cockpit/DBs/mainDB";
    cout<<arrga[i]<<endl;
    db main;
    arrga[i].erase(0,72);
    cout<<arrga[i]<<endl;
    string name = arrga[i].substr(0,arrga[i].size()-3);

    cout<<"name is "<<name<<endl;
    Update(dbname,"SaveGames","NAME","'"+GameData::Gamefile+"'","Status","0");
    Update(dbname,"SaveGames","NAME","'"+name+"'","Status","1");
}*/

void loadCampaign()
{
    // TODO Make this more sexy (efficient) and when loading a game, update time and date
    string path = dbrelprefix + "/DBs/Campaigns/";
    CImg<unsigned char> img((dbrelprefix + "/Pics/rsz_scroll_greek.jpg").c_str());
    CImgDisplay main_disp(img, "Campaign");

    bool lc = true;
    vector<vector<Pomos>> arr;
    int c = 0;
    int height = 50;
    int width = 600;
    int borderx = img.width() / 2 - width / 2;
    int bordery = 200;

    vector<Pomos> x0;

    arr.push_back(x0);

    for (const auto &entry : fs::directory_iterator(path))
    {
        arr[0].push_back(Pomos());
        arr[0][c].text = entry.path();
        arr[0][c].x = borderx;
        arr[0][c].x1 = arr[0][c].x + width;
        arr[0][c].y = bordery + c * height;
        arr[0][c].y1 = arr[0][c].y + height;
        arr[0][c].color = hashi[0];
        arr[0][c].bordercol = hashi[1];
        arr[0][c].fontsize = 10;
        c++;
    }
    img = draw_thing(0, 0, 1, c, arr, img);
    img.display(main_disp);

    cout << c << endl;
    while (lc)
    {
        // img.display(main_disp);
        if (main_disp.is_keyESC())
        {
            lc = false;
            main_disp.close();
            cout << "close load camp" << endl;
        }
        // mouse hover over grid
        while (main_disp.mouse_x() >= arr[0][0].x && main_disp.mouse_x() <= arr[0][c - 1].x1 && main_disp.mouse_y() >= arr[0][0].y && main_disp.mouse_y() <= arr[0][c - 1].y1 && lc)
        {
            for (int j = 0; j < c; j++)
            {
                while (main_disp.mouse_x() >= arr[0][j].x && main_disp.mouse_x() <= arr[0][j].x1 && main_disp.mouse_y() >= arr[0][j].y && main_disp.mouse_y() <= arr[0][j].y1 && lc)
                {
                    arr[0][j].color = red;
                    img = arr[0][j].draw_this(img);
                    img.display(main_disp);

                    if (main_disp.button())
                    {
                        usleep(100 * 1000);

                        string input = scanner("Are you sure?? 1 == 'Yes'");

                        if (input == "1")
                        {
                            cout << "loading start_" << arr[0][j].text << endl;
                            string path = dbrelprefix + "/DBs/Campaigns/";
                            string dbname = dbrelprefix + "/DBs/mainDB";
                            cout << arr[0][j].text << "_is being loaded_" << endl;
                            db main;
                            arr[0][j].text.erase(0, 72);
                            cout << arr[0][j].text << endl;
                            string name = arr[0][j].text.substr(0, arr[0][j].text.size() - 3);

                            cout << "name is " << name << endl;
                            Update(dbname, "SaveGames", "NAME", "'" + GameData::Gamefile + "'", "Status", "0");
                            Update(dbname, "SaveGames", "NAME", "'" + name + "'", "Status", "1");

                            // update time and gf
                            GameData::Gamefile = name;
                            // Update(dbname,"SaveGames","NAME","'"+name+"'","Date", to_string(get_date()));
                            // Update(dbname,"SaveGames","NAME","'"+name+"'","TIME", to_string(get_time()));
                            Update_rowid(dbname, "Globalstats", "VAL8", to_string(get_date()), "1");

                            bool load = battlerecordsfill();
                        }
                    }
                }
                arr[0][j].color = white;
                img = arr[0][j].draw_this(img);
                img.display(main_disp);
            }
        }
    }
}

void newCampaign()
{
    // Player ID = 0, AI 1++
    cout << endl
         << "new Campagin generating..." << endl;
    string Name = scanner("Type in Campaignname");
    db New;
    string dbname = dbrelprefix + "/DBs/Campaigns/" + Name;

    // Now create all the necessary tables for Player, AI coming soon
    // Log
    // if statements only for deleting array via garbage collector
    //
    if (true)
    {
        string cols = "NAME PRIMARY KEY           , "
                      "COLOR           INT";
        Create_table(dbname, "COLORCODE", cols);
    }
    if (true)
    {
        string cols = "ID INT PRIMARY KEY           NOT NULL, "
                      "DATE           INT, "
                      "SUBJECT           TEXT, "
                      "TIER           INT,"
                      "GRADE           REAL";

        Create_table(dbname, "Grades", cols);
    }

    if (true)
    {
        string cols = "ID INT PRIMARY KEY           NOT NULL, "
                      "DAY            INT, "
                      "WEEK           INT, "
                      "TASK           TEXT, "
                      "LOG           TEXT, "
                      "PRESTIGE_NET           INT, "
                      "PRESTIGE_BRUT           INT, "
                      "ACHIEVEMENTS           TEXT";

        Create_table(dbname, "Log", cols);
    }

    if (true)
    {
        string cols = "DAY INT PRIMARY KEY           NOT NULL, "
                      "WEEK           INT, "
                      "POMOS           INT            NOT NULL, "
                      "LOG           TEXT, "
                      "PRESTIGE_NET           INT, "
                      "PRESTIGE_BRUT           INT, "
                      "ACHIEVEMENTS           TEXT, "
                      "GLORY           INT           NOT NULL, "
                      "SYNCH           INT           NOT NULL";

        Create_table(dbname, "DailyLog", cols);
    }

    if (true)
    {
        string cols = "DATE INT PRIMARY KEY           NOT NULL, "
                      "WEEK           INT, "
                      "SYNCH_YRLY           INT, "
                      "SYNCH_DLY           INT, "
                      "SYNCH_WKLY           INT, "
                      "POMOS_WKLY           INT, "
                      "POMOS_4WKLY           INT, "
                      "PRESTIGE_BRUT_ALL           INT, "
                      "PRESTIGE_NET_DLY           INT, "
                      "PRESTIGE_NET_WKLY           INT, "
                      "GLORY_ALL           INT, "
                      "GLORY_WKLY           INT, "
                      "IDEAS_ALL           INT, "
                      "IDEAS_DLY           INT, "
                      "IDEAS_WKLY           INT, "
                      "TASK_SOLVED_ALL           INT, "
                      "TASK_SOLVED_DLY           INT, "
                      "TASK_SOLVED_WKLY           INT, "
                      "QUESTIONS_ALL           INT, "
                      "QUESTIONS_DLY           INT, "
                      "QUESTIONS_WKLY           INT, "
                      "LECTURES_ALL           INT, "
                      "CORRECTION_ALL           INT, "
                      "SUMMARY_ALL           INT, "
                      "BOOK_ALL           INT, "
                      "ACTIVE_RE_ALL           INT, "
                      "ACTIVE_RE_WKLY           INT, "
                      "TEST_EXAM_ALL           INT, "
                      "READ_PAGES_ALL           INT";

        Create_table(dbname, "Stats", cols);
    }

    if (true)
    {
        string cols = "ID REAL PRIMARY KEY           NOT NULL, "
                      "NAME           TEXT, "
                      "PROGRESS           INT, "
                      "REWARD           INT, "
                      "TARGET           INT, "
                      "UNLOCKED           INT";

        Create_table(dbname, "Achievements", cols);
        // start on time in the morning
        Insert(dbname, "Achievements", "1, 'reliable', 0, 10, 3, 0");
        Insert(dbname, "Achievements", "2, 'clock', 0, 30, 10, 0");
        Insert(dbname, "Achievements", "3, 'Conquer the morning', 0, 60, 25, 0");
        Insert(dbname, "Achievements", "4, 'Morning Routine', 0, 120, 60, 0");
        Insert(dbname, "Achievements", "5, 'Agent of The blazing Sun', 0, 240, 120, 0");
        Insert(dbname, "Achievements", "6, 'Morning Champion', 0, 480, 240, 0");
        Insert(dbname, "Achievements", "7, 'God of the blazing Sun', 0, 900, 1000, 0");
        // reach 85% or 95% Synch 7 days in a row
        Insert(dbname, "Achievements", "8, 'Executioner', 0, 50, 7, 0");
        Insert(dbname, "Achievements", "9, 'Stoic', 0, 100, 7, 0");
        Insert(dbname, "Achievements", "10, 'Iron Will', 0, 300, 21, 0");
        Insert(dbname, "Achievements", "11, 'Unbreakable', 0, 900, 70, 0");
        Insert(dbname, "Achievements", "12, 'Near Arrete', 0, 1000, 7, 0");
        Insert(dbname, "Achievements", "13, 'Arrete', 0, 2000, 35, 0");
        // finish x Pomodoros (any focus)
        Insert(dbname, "Achievements", "14, 'Grinder', 0, 100, 130, 0");
        Insert(dbname, "Achievements", "15, 'Farmer', 0, 400, 500, 0");
        Insert(dbname, "Achievements", "16, 'Producer', 0, 800, 1000, 0");
        Insert(dbname, "Achievements", "17, 'Creationist', 0, 3200, 4000, 0");
        Insert(dbname, "Achievements", "18, 'Chosen', 0, 6000, 10000, 0");
        // Test ideas
        Insert(dbname, "Achievements", "19, 'Adventurer', 0, 5, 10, 0");
        Insert(dbname, "Achievements", "20, 'Frontier', 0, 15, 30, 0");
        Insert(dbname, "Achievements", "21, 'Explorer', 0, 30, 60, 0");
        Insert(dbname, "Achievements", "22, 'Simulator', 0, 50, 100, 0");
        Insert(dbname, "Achievements", "23, 'Cyborg', 0, 230, 250, 0");
        Insert(dbname, "Achievements", "24, 'Tech Priest', 0, 260, 500, 0");
        Insert(dbname, "Achievements", "25, 'Singularity', 0, 550, 1000, 0");
        // Answer Questions
        Insert(dbname, "Achievements", "26, 'Student', 0, 5, 10, 0");
        Insert(dbname, "Achievements", "27, 'Truth Seeker', 0, 10, 20, 0");
        Insert(dbname, "Achievements", "28, 'Scientist', 0, 35, 70, 0");
        Insert(dbname, "Achievements", "29, 'Precursor', 0, 70, 150, 0");
        Insert(dbname, "Achievements", "30, 'Void Wanderer', 0, 210, 500, 0");
        Insert(dbname, "Achievements", "31, 'All Mighty', 0, 410, 1000, 0");
        // make corrections
        Insert(dbname, "Achievements", "32, 'Corrector', 0, 20, 8, 0");
        Insert(dbname, "Achievements", "33, 'Judge', 0, 40, 16, 0");
        Insert(dbname, "Achievements", "34, 'Precision', 0, 80, 32, 0");
        Insert(dbname, "Achievements", "35, 'skeptic', 0, 160, 64, 0");
        Insert(dbname, "Achievements", "36, 'Investigator', 0, 320, 128, 0");
        Insert(dbname, "Achievements", "37, 'Inquisitor', 0, 520, 200, 0");
        Insert(dbname, "Achievements", "38, 'Lord Inquisitor', 0, 1500, 600, 0");

        // Progress resets after 20 weeks, earn 4.5 to 6.0 grade each 10 times
        Insert(dbname, "Achievements", "39, 'reputation', 0, 40, 10, 0");
        Insert(dbname, "Achievements", "40, 'Mystical', 0, 90, 10, 0");
        Insert(dbname, "Achievements", "41, 'Legendary', 0, 180, 10, 0");
        Insert(dbname, "Achievements", "42, 'Divinity', 0, 300, 10, 0");

        // Real exams!! same as above, but only once
        Insert(dbname, "Achievements", "43, 'Conqueror', 0, 500, 1, 0");
        Insert(dbname, "Achievements", "44, 'Expansion', 0, 1000, 1, 0");
        Insert(dbname, "Achievements", "45, 'Warlord', 0, 5000, 1, 0");
        Insert(dbname, "Achievements", "46, 'Emperor', 0, 10000, 1, 0");

        // Tests under real conditions !!, from 4.5 to 5.5 three times
        Insert(dbname, "Achievements", "47, 'Readiness', 0, 200, 3, 0");
        Insert(dbname, "Achievements", "48, 'War Fevour', 0, 450, 3, 0");
        Insert(dbname, "Achievements", "49, 'Domination', 0, 750, 3, 0");
        // watch lectures
        Insert(dbname, "Achievements", "50, 'Listener', 0, 10, 10, 0");
        Insert(dbname, "Achievements", "51, 'Absorber', 0, 20, 25, 0");
        Insert(dbname, "Achievements", "52, 'Sponge', 0, 40, 50, 0");
        Insert(dbname, "Achievements", "53, 'Assimilator', 0, 90, 100, 0");
        Insert(dbname, "Achievements", "54, 'Integrator', 0, 900, 1000, 0");
        // Write Summaries
        Insert(dbname, "Achievements", "55, 'Morpher', 0, 10, 5, 0");
        Insert(dbname, "Achievements", "56, 'Modeller', 0, 20, 10, 0");
        Insert(dbname, "Achievements", "57, 'Structurer', 0, 40, 20, 0");
        Insert(dbname, "Achievements", "58, 'Manifestician', 0, 80, 50, 0");
        Insert(dbname, "Achievements", "59, 'Scriptor', 0, 160, 100, 0");
        Insert(dbname, "Achievements", "60, 'Archscriptor', 0, 350, 250, 0");
        Insert(dbname, "Achievements", "61, 'Primescriptor', 0, 1200, 1000, 0");

        // 80% or more Pomos
        Insert(dbname, "Achievements", "62, 'Focus', 0, 150, 10, 0");
        Insert(dbname, "Achievements", "63, 'Channeler', 0, 3000, 200, 0");
        Insert(dbname, "Achievements", "64, 'Hard Focus', 0, 10000, 1000, 0");
        Insert(dbname, "Achievements", "65, 'Enlightened', 0, 20000, 3000, 0");
        Insert(dbname, "Achievements", "66, 'Serious', 0, 50000, 10000, 0");
        // read pages
        Insert(dbname, "Achievements", "67, 'BookWorm', 0, 2, 10, 0");
        Insert(dbname, "Achievements", "68, 'Scanner', 0, 6, 60, 0");
        Insert(dbname, "Achievements", "69, 'Sage', 0, 20, 200, 0");
        Insert(dbname, "Achievements", "70, 'Professor', 0, 100, 1000, 0");
        Insert(dbname, "Achievements", "71, 'Philosopher', 0, 800, 10000, 0");

        // one AR is one ankiset
        Insert(dbname, "Achievements", "72, 'Reminder', 0, 20, 10, 0");
        Insert(dbname, "Achievements", "73, 'Memory Expert', 0, 120, 100, 0");
        Insert(dbname, "Achievements", "74, 'Memory Champ', 0, 300, 250, 0");
        Insert(dbname, "Achievements", "75, 'Memory God', 0, 1000, 750, 0");
        // Solve Task/Subtask
        Insert(dbname, "Achievements", "76, 'Solver', 0, 400, 20, 0");
        Insert(dbname, "Achievements", "77, 'Accomplisher', 0, 1000, 80, 0");
        Insert(dbname, "Achievements", "78, 'Sharpshooter', 0, 2000, 400, 0");
        Insert(dbname, "Achievements", "79, 'Analytician', 0, 4000, 1000, 0");
        Insert(dbname, "Achievements", "80, 'Mathematician', 0, 12000, 10000, 0");
    }

    if (true)
    {
        string cols = "ID REAL PRIMARY KEY           NOT NULL, "
                      "NAME           TEXT, "
                      "COST           INT, "
                      "REWARD           INT, "
                      "UNLOCKED           INT";

        Create_table(dbname, "Skilltree", cols);
    }

    // ID is week+"."+Nr. of pomos, after 32 lines new plan
    if (true)
    {
        string cols = "ID INT PRIMARY KEY           NOT NULL, "
                      "TIME           TEXT, "
                      "MONDAY           TEXT, "
                      "TUESDAY           TEXT, "
                      "WEDNESDAY           TEXT, "
                      "THURSDAY           TEXT, "
                      "FRIDAY           TEXT, "
                      "SATURDAY           TEXT, "
                      "SUNDAY           TEXT, "
                      "WEEK           INT";

        Create_table(dbname, "SampleBattleplan", cols);
    }
    if (true)
    {
        string cols = "ID INT PRIMARY KEY           NOT NULL, "
                      "TIME           TEXT, "
                      "MONDAY           TEXT, "
                      "TUESDAY           TEXT, "
                      "WEDNESDAY           TEXT, "
                      "THURSDAY           TEXT, "
                      "FRIDAY           TEXT, "
                      "SATURDAY           TEXT, "
                      "SUNDAY           TEXT, "
                      "WEEK           INT";

        Create_table(dbname, "AI", cols);
    }
    if (true)
    {
        string cols = "ID INT PRIMARY KEY           NOT NULL, "
                      "Max_Prestige           INT, "
                      "VAL           TEXT, "
                      "VAL2           TEXT, "
                      "VAL3           TEXT, "
                      "VAL4           TEXT, "
                      "VAL5           TEXT, "
                      "VAL6           TEXT, "
                      "VAL7           TEXT, "
                      "VAL8           TEXT";

        Create_table(dbname, "Globalstats", cols);
        Insert(dbname, "Globalstats", "1 ,0 ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ");
    }
    // ID consists of week + ID 1.12 is first week and 12th Pomos
    if (true)
    {
        string cols = "WEEK           INT, "
                      "TIME           TEXT, "
                      "MONDAY           TEXT, "
                      "TUESDAY           TEXT, "
                      "WEDNESDAY           TEXT, "
                      "THURSDAY           TEXT, "
                      "FRIDAY           TEXT, "
                      "SATURDAY           TEXT, "
                      "SUNDAY           TEXT";

        Create_table(dbname, "Battlerecords", cols);
    }
    // Maybe use foreign key for AI instead of name?
    if (true)
    {
        string cols = "ID INT PRIMARY KEY           NOT NULL, "
                      "DATE           TEXT, "
                      "CHALLENGER           TEXT, "
                      "DEFENDER           TEXT, "
                      "OUTCOME           INT, "
                      "PRESTIGE_EARNED           INT";

        Create_table(dbname, "Duelrecords", cols);
    }

    if (true)
    {
        string cols = "ID INT PRIMARY KEY           NOT NULL, "
                      "ACTION           TEXT, "
                      "REWARD           TEXT";

        Create_table(dbname, "Actions", cols);

        Insert(dbname, "Actions", "1, 'Earn_a_Grade_4.5', '5'");
        Insert(dbname, "Actions", "2, 'Earn_a_Grade_5.0', '10'");
        Insert(dbname, "Actions", "3, 'Earn_a_Grade_5.5', '20'");
        Insert(dbname, "Actions", "4, 'Earn_a_Grade_6.0', '35'");
        Insert(dbname, "Actions", "5, 'Active_Recall', '12'");
        Insert(dbname, "Actions", "6, 'Read_Pages', '1'");
        Insert(dbname, "Actions", "7, 'Watch_Lecture', '10'");
        Insert(dbname, "Actions", "8, 'Make_Correction', '12'");
        Insert(dbname, "Actions", "9, 'Make_Summary', '12'");
        Insert(dbname, "Actions", "10, 'Answer_Question', '3'");
        Insert(dbname, "Actions", "11, 'Solve_Task_Subtask', '7'");
        Insert(dbname, "Actions", "12, 'Test_Idea', '3'");
        Insert(dbname, "Actions", "13, 'Collect_a_Book', 'SPECIAL'");
        //"passive" actions
        Insert(dbname, "Actions", "14, 'Win_Duel', 'SPECIAL'");
        Insert(dbname, "Actions", "15, 'Focus_60', '5'");
        Insert(dbname, "Actions", "16, 'Focus_70', '10'");
        Insert(dbname, "Actions", "17, 'Focus_80', '20'");
        Insert(dbname, "Actions", "18, 'Focus_90', '40'");
        Insert(dbname, "Actions", "19, 'Focus_100', '60'");
        Insert(dbname, "Actions", "20, 'Sync_80', '10'");
        Insert(dbname, "Actions", "21, 'Sync_90', '20'");
        Insert(dbname, "Actions", "22, 'Sync_100', '50'");
    }
    dbname = dbrelprefix + "/DBs/mainDB";
    // get current date and time as integers
    int date = get_date();
    int time = get_time();
    string vals = "'" + Name + "'" + ", " + "0, " + to_string(date) + ", " + to_string(time);
    cout << vals << endl;
    Insert(dbname, "SaveGames", vals);
}

CImg<unsigned char> drawach(CImg<unsigned char> img, int viewstart, int viewend, vector<Pomos> arr, int y_start, int height, int groups[])
{
    int k = 0;
    for (int i = 0; i < viewstart; i++)
    {
        k += groups[i];
    }
    for (int i = 0; i < viewend; i++)
    {
        for (int j = 0; j < groups[i + viewstart]; j++)
        {
            arr[j + k].y = y_start + i * height;
            arr[j + k].y1 = arr[j + k].y + height;
            img = arr[j + k].draw_this(img);
        }
        k += groups[i + viewstart];
    }

    return img;
}

void Achievements()
{
    CImg<unsigned char> img((dbrelprefix + "/Pics/rsz_scroll_greek.jpg").c_str());
    CImgDisplay main_disp(img, "Campaign");
    CImg<unsigned char> ogimg((dbrelprefix + "/Pics/rsz_scroll_greek.jpg").c_str());
    string dbname = dbrelprefix + "/DBs/Campaigns/" + GameData::Gamefile;

    vector<Pomos> arr;
    for (int i = 0; i < 80; i++)
    {
        arr.push_back(Pomos());
        arr[i].progress = Select_val(dbname, "Achievements", "_rowid_", to_string(i + 1), "PROGRESS");
        arr[i].target = Select_val(dbname, "Achievements", "_rowid_", to_string(i + 1), "TARGET");
        arr[i].unlocked = Select_val(dbname, "Achievements", "_rowid_", to_string(i + 1), "UNLOCKED");
        arr[i].text = Select_val(dbname, "Achievements", "_rowid_", to_string(i + 1), "NAME");

        int h = stoi(arr[i].unlocked);

        if (h >= 60)
        {
            arr[i].color = hashi[13];
        }
        else if (h >= 25)
        {
            arr[i].color = hashi[15];
        }
        else if (h >= 10)
        {
            arr[i].color = hashi[16];
        }
        else if (h >= 5)
        {
            arr[i].color = hashi[7];
        }
        else if (h >= 1)
        {
            arr[i].color = hashi[17];
        }

        /*
        cout<<arr[i].progress<<endl;
        cout<<arr[i].target<<endl;
        cout<<arr[i].unlocked<<endl;
        cout<<arr[i].text<<endl;*/
    }
    int c = 0;
    int x_start = 20;
    int width = 250;
    int y_start = 120;
    int height = 100;

    int groups[] = {
        7,
        6,
        5,
        7,
        6,
        7,
        4,
        4,
        3,
        5,
        7,
        5,
        5,
        4,
        5,
    };

    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < groups[j]; i++)
        {
            arr[i + c].x = x_start + i * width;
            arr[i + c].x1 = arr[i + c].x + width;

            arr[i + c].text += "\n\nProgress      Target      unlocked\n      " + arr[i + c].progress + "          " + arr[i + c].target + "          " + arr[i + c].unlocked;
            // cout<<arr[i+c].text<<"____"<<endl;
        }
        c += groups[j];
    }

    int startview = 0;
    int endview = 8;

    Pomos arrowup;
    arrowup.x = 760;
    arrowup.y = 60;
    arrowup.x1 = arrowup.x + 100;
    arrowup.y1 = arrowup.y + 50;
    arrowup.color = creme;
    arrowup.text = "up";
    img = arrowup.draw_this(img);

    Pomos arrowdown;
    arrowdown.x = 760;
    arrowdown.y = 1000;
    arrowdown.x1 = arrowdown.x + 100;
    arrowdown.y1 = arrowdown.y + 50;
    arrowdown.color = creme;
    arrowdown.text = "down";
    img = arrowdown.draw_this(img);

    ogimg = img;
    img = drawach(img, startview, endview, arr, y_start, height, groups);

    img.display(main_disp);

    while (!main_disp.is_closed())
    {
        if (main_disp.is_keyESC())
        {
            main_disp.close();
        }
        while (startview > 0 && arrowdown.y <= main_disp.mouse_y() && main_disp.mouse_y() <= arrowdown.y1 &&
               arrowdown.x <= main_disp.mouse_x() && main_disp.mouse_x() <= arrowdown.x1)
        {
            if (main_disp.button())
            {
                usleep(100000);
                startview--;
                cout << startview << "startview " << endl;
                img = ogimg;
                img = drawach(img, startview, endview, arr, y_start, height, groups);
                img.display(main_disp);
            }
        }
        while (startview + endview < 15 && arrowup.y <= main_disp.mouse_y() && main_disp.mouse_y() <= arrowup.y1 &&
               arrowup.x <= main_disp.mouse_x() && main_disp.mouse_x() <= arrowup.x1)
        {
            if (main_disp.button())
            {
                usleep(100000);
                startview++;
                cout << startview << "startview " << endl;
                img = ogimg;
                img = drawach(img, startview, endview, arr, y_start, height, groups);
                img.display(main_disp);
            }
        }
    }
}

void Skilltree()
{
}

void Overview()
{
}

void Campaign()
{
    CImg<unsigned char> img((dbrelprefix + "/Pics/rsz_scroll_greek.jpg").c_str());
    CImgDisplay main_disp(img, "Campaign");
    CImg<unsigned char> ogimg((dbrelprefix + "/Pics/rsz_scroll_greek.jpg").c_str());

    while (!main_disp.is_closed())
    {
        // cout<<"y: "<<main_disp.mouse_y()<<"x: "<<main_disp.mouse_x()<<endl;
        img.draw_image(ogimg);
        if (main_disp.is_keyESC())
        {
            main_disp.close();
        }
        // All interactive Textfields
        CImg<unsigned char> Load;
        Load.draw_text(0, 0, "Load Campaign", black, 0, 1, 50);
        int x0_load = 1920 / 2 - Load.width() / 2;
        int y0_load = 1080 / 6;
        img.draw_text(x0_load, y0_load, "Load Campaign", black, 0, 1, 50);

        CImg<unsigned char> New;
        New.draw_text(0, 0, "New Campaign", black, 0, 1, 50);
        int x0_new = 1920 / 2 - New.width() / 2;
        int y0_new = 2 * 1080 / 6;
        img.draw_text(x0_new, y0_new, "New Campaign", black, 0, 1, 50);

        // Saving as and deleting must be done manually , for the moment
        CImg<unsigned char> ach;
        ach.draw_text(0, 0, "Achievements", black, 0, 1, 50);
        int x0_ach = 1920 / 2 - ach.width() / 2;
        int y0_ach = 3 * 1080 / 6;
        img.draw_text(x0_ach, y0_ach, "Achievements", black, 0, 1, 50);

        CImg<unsigned char> Skilltree;
        Skilltree.draw_text(0, 0, "Skilltree", black, 0, 1, 50);
        int x0_sk = 1920 / 2 - Skilltree.width() / 2;
        int y0_sk = 4 * 1080 / 6;
        img.draw_text(x0_sk, y0_sk, "Skilltree", black, 0, 1, 50);

        CImg<unsigned char> Overview;
        Overview.draw_text(0, 0, "Overview", black, 0, 1, 50);
        int x0_ov = 1920 / 2 - Overview.width() / 2;
        int y0_ov = 5 * 1080 / 6;
        img.draw_text(x0_ov, y0_ov, "Overview", black, 0, 1, 50);

        if (main_disp.mouse_x() >= x0_load && main_disp.mouse_x() <= x0_load + Load.width() && main_disp.mouse_y() >= y0_load && main_disp.mouse_y() <= y0_load + Load.height())
        {

            img.draw_rectangle(x0_load, y0_load, x0_load + Load.width(), y0_load + Load.height(), red, 1);
            img.draw_text(x0_load, y0_load, "Load Campaign", black, 0, 1, 50);

            // Click event
            if (main_disp.button())
            {
                loadCampaign();
            }
        }
        if (main_disp.mouse_x() >= x0_new && main_disp.mouse_x() <= x0_new + New.width() && main_disp.mouse_y() >= y0_new && main_disp.mouse_y() <= y0_new + New.height())
        {

            img.draw_rectangle(x0_new, y0_new, x0_new + New.width(), y0_new + New.height(), red, 1);
            img.draw_text(x0_new, y0_new, "New Campaign", black, 0, 1, 50);

            // Click event
            if (main_disp.button())
            {
                newCampaign();
            }
        }
        if (main_disp.mouse_x() >= x0_ach && main_disp.mouse_x() <= x0_ach + ach.width() && main_disp.mouse_y() >= y0_ach && main_disp.mouse_y() <= y0_ach + ach.height())
        {

            img.draw_rectangle(x0_ach, y0_ach, x0_ach + ach.width(), y0_ach + ach.height(), red, 1);
            img.draw_text(x0_ach, y0_ach, "Achievements", black, 0, 1, 50);

            // Click event
            if (main_disp.button())
            {
                Achievements();
            }
        }
        img.display(main_disp);
    }
}

#endif // PERFORMANCE_COCKPIT_CAMPAIGN_H
