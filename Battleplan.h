//
// Created by Dave on 6/27/21.
//
#include "DB.h"
#include "Campaign.h"
#ifndef PERFORMANCE_COCKPIT_BATTLEPLAN_H
#define PERFORMANCE_COCKPIT_BATTLEPLAN_H

//https://www.color-hex.com/color/36153b
//Sample battleplan with 0 as week is default, all others have been updated in respective week, are always 3 weeks in advance paste default
//Battlerecors is from Pomodore, and Sync is calculated with respective Battleplans planned and executed


void Battleplans(){
    //string Gamefile = GameData::Gamefile;
    //Each color is associated with a number left to right, top down

    CImg<unsigned char> img((dbrelprefix+"/Pics/rsz_scroll_greek.jpg").c_str());
    CImgDisplay main_disp(img,"Battleplans");

    CImg<unsigned char> ogimg((dbrelprefix+"/Pics/rsz_scroll_greek.jpg").c_str());
    CImg<unsigned char> ogimg2((dbrelprefix+"/Pics/rsz_scroll_greek.jpg").c_str());


    while(!main_disp.is_closed()){
        //cout<<"y: "<<main_disp.mouse_y()<<"x: "<<main_disp.mouse_x()<<endl;

        //img.fillC(0,0,0,30,50,100);
        img.draw_image(ogimg);
        if(main_disp.is_keyESC()){
            main_disp.close();
            cout<<"Test"<<endl;
        }

        //All interactive Textfields
        CImg<unsigned char> Battleplan;
        Battleplan.draw_text(0,0,"Battleplan",black,0,1,50);
        int x0_CU = 1920/2-Battleplan.width()/2;
        int y0_CU = 2*1080/5;
        img.draw_text(x0_CU,y0_CU,"Battleplan",black,0,1,50);

        CImg<unsigned char> Battlerecords;
        Battlerecords.draw_text(0,0,"Battlerecords",black,0,1,50);
        int x0_CD = 1920/2-Battlerecords.width()/2;
        int y0_CD = 2*1080/5+1080/5;
        img.draw_text(x0_CD,y0_CD,"Battlerecords",black,0,1,50);

        bool battleplan_active = false;
        //Battleplan
        while(main_disp.mouse_x()>=x0_CU && main_disp.mouse_x()<=x0_CU+Battleplan.width()
        && main_disp.mouse_y()>=y0_CU && main_disp.mouse_y()<=y0_CU+Battleplan.height() &&!main_disp.is_closed()){
            if(main_disp.is_keyESC()){
                main_disp.close();
                cout<<"Test"<<endl;
            }
            img.draw_rectangle(x0_CU,y0_CU,x0_CU+Battleplan.width(),y0_CU+Battleplan.height(),red,1);
            img.draw_text(x0_CU,y0_CU,"Battleplan",black,0,1,50);
            img.display(main_disp);
            //Click event
            if(main_disp.button()){
                battleplan_active = true;
                cout<<"click"<<endl;
                CImg<unsigned char> img((dbrelprefix+"/Pics/rsz_scroll_greek.jpg").c_str());
                CImgDisplay main_disp(img,"Battleplans");
                //All the prep for showing battleplan
                //PomosGrid

                vector<vector<Pomos>> arr;

                int height = 25;
                int width = 100;

                int borderx = 400;
                int bordery = 150;

                for(int i = 0; i < 8;i++){
                    vector<Pomos> x;
                    arr.push_back(x);
                    for(int j = 0; j < 32; j++){
                        arr[i].push_back(Pomos());
                        arr[i][j].x = borderx+i*width;
                        arr[i][j].y = bordery+j*height;
                        arr[i][j].x1 = arr[i][j].x+width;
                        arr[i][j].y1 = arr[i][j].y+height;
                        arr[i][j].color = white;
                        arr[i][j].bordercol = black;

                    }
                }
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


                img = draw_thing( 0,0,8, 32,arr, img);

                int borderx_2 =borderx+ 9*width;

                //Colorgrid 2*5
                vector<vector<Pomos>> Colorgrid;

                int indexhashi = 0;
                for(int i = 0; i < 2;i++){
                    vector<Pomos> x;
                    Colorgrid.push_back(x);
                    for(int j = 0; j < 9; j++){
                        Colorgrid[i].push_back(Pomos());
                        Colorgrid[i][j].x = borderx_2+i*width;
                        Colorgrid[i][j].y = bordery+j*height;
                        Colorgrid[i][j].x1 = Colorgrid[i][j].x+width;
                        Colorgrid[i][j].y1 = Colorgrid[i][j].y+height;
                        Colorgrid[i][j].color = hashi[indexhashi];
                        indexhashi++;

                    }
                }
                img = draw_thing( 0,0,2,9,Colorgrid, img);
                //Saveplan
                Pomos Saveplan;

                Saveplan.x = borderx-width;
                Saveplan.x1 = borderx;
                Saveplan.y = bordery;
                Saveplan.y1 = bordery+height;
                Saveplan.text = "Save";
                Saveplan.fun = saveplan;

                img = Saveplan.draw_this(img);

                //Loadplan
                Pomos loadplan;

                loadplan.x = borderx-width*2;
                loadplan.x1 = borderx-width;
                loadplan.y = bordery;
                loadplan.y1 = bordery+height;
                loadplan.text = "Load";
                loadplan.fun2 = loadplanfun;

                img = Saveplan.draw_this(img);
                img.display(main_disp);
                const unsigned char *colorselect = white;

                while(battleplan_active){
                    Saveplan.color = white;
                    img = Saveplan.draw_this(img);
                    loadplan.color = white;
                    img = loadplan.draw_this(img);
                    img.display(main_disp);
                    //Save menu
                    while(Battleplan&& main_disp.mouse_x()>= Saveplan.x && main_disp.mouse_x() <= Saveplan.x1
                    && main_disp.mouse_y()>= Saveplan.y && main_disp.mouse_y()<= Saveplan.y1){
                        Saveplan.color = red;
                        img = Saveplan.draw_this(img);
                        img.display(main_disp);
                        if(main_disp.button()){
                            usleep(120*1000);
                            Saveplan.fun(0,arr,Colorgrid,8,32);
                            cout<<"Saving plan..."<<endl;
                            Saveplan.color = white;
                            img = Saveplan.draw_this(img);
                            img.display(main_disp);
                        }
                    }
                    while(Battleplan&& main_disp.mouse_x()>= loadplan.x && main_disp.mouse_x() <= loadplan.x1
                    && main_disp.mouse_y()>= loadplan.y && main_disp.mouse_y()<= loadplan.y1){
                        loadplan.color = red;
                        img = loadplan.draw_this(img);
                        img.display(main_disp);
                        if(main_disp.button()){
                            usleep(120*1000);
                            cout<<"laoding plan..."<<endl;
                            arr = loadplan.fun2(0,arr);
                            indexhashi = 0;
                            for(int i = 0; i < 2;i++){
                                for(int j = 0; j < 9; j++){
                                    Colorgrid[i][j].x = borderx_2+i*width;
                                    Colorgrid[i][j].y = bordery+j*height;
                                    Colorgrid[i][j].x1 = Colorgrid[i][j].x+width;
                                    Colorgrid[i][j].y1 = Colorgrid[i][j].y+height;
                                    Colorgrid[i][j].color = hashi[indexhashi];
                                    Colorgrid[i][j].text = mepi[Colorgrid[i][j].color];
                                    indexhashi++;

                                }
                            }
                            img = draw_thing(0,0,2,9,Colorgrid,img);
                            img = draw_thing(1,1,8,32,arr,img);

                            loadplan.color = white;
                            img = loadplan.draw_this(img);
                            //img.display(main_disp);
                            cout<<"plan loaded "<<endl;
                        }
                    }
                    //cout<<"outside"<<endl;
                    //color menu
                    while(main_disp.mouse_x()>= borderx_2 && main_disp.mouse_x()<= borderx_2+2*width
                    && main_disp.mouse_y()>= bordery&& main_disp.mouse_y()<=bordery+9*height&& battleplan_active){
                        //cout<<"mainframe touch"<<endl;

                        for(int i = 0; i < 2;i++){
                            for(int j = 0; j < 9; j++){
                               while(main_disp.mouse_x()>=Colorgrid[i][j].x && main_disp.mouse_x()<=Colorgrid[i][j].x + width&&
                                main_disp.mouse_y()>= Colorgrid[i][j].y &&main_disp.mouse_y()<= Colorgrid[i][j].y1&& battleplan_active){ 
                                    if(main_disp.is_keySPACE()){
                                        usleep(100*1000);
                                        Colorgrid[i][j].texttopomos();
                                        img = Colorgrid[i][j].draw_this(img);
                                        img.display(main_disp);
                                    } else if(main_disp.button()){
                                        usleep(100*1000);
                                        colorselect = Colorgrid[i][j].color;
                                        cout<<"color copied"<<endl;
                                    }

                                }
                            }
                        }

                    }
                    while(main_disp.mouse_x()>= borderx && main_disp.mouse_x()<= borderx+8*width
                    && main_disp.mouse_y()>= bordery&& main_disp.mouse_y()<=bordery+32*height&& battleplan_active){
                        //cout<<"mainframe touch"<<endl;
                        for(int i = 1; i < 8;i++){
                            for(int j = 1; j < 32; j++){
                                while(main_disp.mouse_x()>=arr[i][j].x && main_disp.mouse_x()<=arr[i][j].x1&&
                                main_disp.mouse_y()>= arr[i][j].y &&main_disp.mouse_y()<= arr[i][j].y1&& battleplan_active){
                                    if(main_disp.button()){
                                        //usleep(100*1000);
                                        arr[i][j].color = colorselect;
                                        img = arr[i][j].draw_this(img);
                                        img.display(main_disp);
                                    }

                                }
                            }
                        }

                    }

                    if(main_disp.is_keyESC()){
                        cout<<"ESC"<<endl;
                        battleplan_active = false;
                    }
                }


            }
        }
        //Battlerecords**************************************************************************************************************
        while (main_disp.mouse_x()>=x0_CD && main_disp.mouse_x()<=x0_CD+Battlerecords.width()
        && main_disp.mouse_y()>=y0_CD && main_disp.mouse_y()<=y0_CD+Battlerecords.height()&&!main_disp.is_closed()) {
            if(main_disp.is_keyESC()){
                main_disp.close();
            }

            img.draw_rectangle(x0_CD,y0_CD,x0_CD+Battlerecords.width(),y0_CD+Battlerecords.height(),red,1);
            img.draw_text(x0_CD,y0_CD,"Battlerecords",black,0,1,50);
            img.display(main_disp);

            //Click event
            if(main_disp.button()){
                bool battlerecord_active = true;
                cout<<"click"<<endl;
                CImg<unsigned char> img((dbrelprefix+"/Pics/rsz_scroll_greek.jpg").c_str());
                CImgDisplay main_disp(img,"Battlerecords");
                //All the prep for showing battleplan
                //PomosGrid

                vector<vector<Pomos>> arr;
                vector<vector<Pomos>> plan;

                int height = 25;
                int width = 100;

                int borderx = 400;
                int bordery = 150;

                //Draw Grid as Heatmap, for showing amount of focus/sync
                for(int i = 0; i < 8;i++){
                    vector<Pomos> x;
                    vector<Pomos> y;
                    arr.push_back(x);
                    plan.push_back(y);
                    for(int j = 0; j < 32; j++){
                        arr[i].push_back(Pomos());
                        plan[i].push_back(Pomos());
                        arr[i][j].x = borderx+i*width;
                        arr[i][j].y = bordery+j*height;
                        arr[i][j].x1 = arr[i][j].x+width;
                        arr[i][j].y1 = arr[i][j].y+height;
                        arr[i][j].color = white;
                        arr[i][j].bordercol = black;

                    }
                }

                //use loadplanfun
                int week = get_currweek();
                Pomos weekly;
                weekly.text = "Week: "+to_string(week);
                weekly.fontsize = 150;
                weekly.x = 1350;
                weekly.x1 = 1880;
                weekly.y = 200;
                weekly.y1 = 370;
                weekly.color = darkgold;
                weekly.bordercol = white;
                img = weekly.draw_this(img);


                //draw Arrows for navigating weeks
                Pomos arrowright;
                arrowright.x = 400;
                arrowright.x1 = 500;
                arrowright.y = 50;
                arrowright.y1 = 70;
                arrowright.color = strongyellow;
                arrowright.text = "----------------->";
                
                Pomos arrowleft;
                arrowleft.x = 300;
                arrowleft.x1 = 400;
                arrowleft.y = 50;
                arrowleft.y1 = 70;
                arrowleft.color = strongyellow;
                arrowleft.text = "<--------------------";

                img = arrowright.draw_this(img);
                img = arrowleft.draw_this(img);

                ogimg2 = img;

                arr = loadplanfun(week,arr);
                plan = loadplanfun(0,plan);

                //cout<<"plansize_"<<plan.size()<<endl;
                //cout<<"arrsize__"<<arr.size()<<endl;

                //calc Synch for each day
                vector<Pomos> Sync;

                for(int i = 0; i < 7; i++){
                    Sync.push_back(Pomos());
                }

                int error = 0;
                for(int i = 1; i < plan.size();i++){
                    for(int j = 1; j <plan[i].size();j++){
                        //cout<<"plansize_"<<plan[i].size()<<endl;
                        //cout<<"arrsize__"<<arr[i].size()<<endl;
                        if(plan[i][j].text != ""){
                            //cout<<plan[i][j].text<<"_:plan text"<<endl;
                            if(arr[i][j].text == ""){
                                //cout<<arr[i][j].text<<"_:records text"<<endl;
                                error++;
                            }
                        }
                    }
                    Sync[i-1].text = ""+to_string(100-floor(error*100/31));
                    error = 0;
                }
                cout<<"testkk"<<endl;
                int x0s = 500;
                int y0a = 980;
                for(int i = 0; i < Sync.size();i++){
                    Sync[i].x = x0s+i*width;
                    Sync[i].x1 = Sync[i].x+width;
                    Sync[i].y = y0a;
                    Sync[i].y1 = y0a+height;
                    Sync[i].color = blue;
                    Sync[i].bordercol = black;
                    img = Sync[i].draw_this(img);
                }

                for(int i = 0; i<arr.size();i++){
                    for(int j =0; j< arr[i].size();j++){
                        img = arr[i][j].draw_this(img);
                        if(i > 0&& j>0){
                            if(arr[i][j].text != ""){
                                //cout<<arr[i][j].text<<" hehe"<<endl;
                                int heat = stoi(arr[i][j].text);
                                //cout<<heat<<" heat "<<endl;
                                int rank = floor(heat*100/GameData::maxpres);
                                //cout<<rank<<" %_"<<endl;
                                int digit2 = (to_string(rank)[to_string(rank).size()-1])-'0';
                                rank -= digit2;
                                //cout <<rank<<" rank"<<endl;
                                if(rank <= 20){
                                    arr[i][j].color = red20;
                                } else {
                                    arr[i][j].color = heatmap[rank];
                                }
                            }
                        }
                    }
                }

                //draw synch indicator below days

                //draw focus indicator below days
                img = draw_thing( 0,0,8, 32,arr, img);
                img.display(main_disp);
                int day = get_currday()+1;

                while(battlerecord_active){
                    if(main_disp.is_keyESC()){
                        battlerecord_active = false;
                        main_disp.close();
                    }

                    if(battlerecord_active && arrowleft.x <= main_disp.mouse_x() && main_disp.mouse_x() <= arrowleft.x1 &&
                    arrowleft.y <= main_disp.mouse_y() && main_disp.mouse_y() <= arrowleft.y1 && main_disp.button()){
                        cout<<"arrowleft"<<endl;
                        if(week >1){
                            week--;
                        }
                        weekly.text = "Week: "+to_string(week);
                        img = ogimg2;
                        img = weekly.draw_this(img);
                        arr = loadplanfun(week,arr);
                        /*
                        for(int i = 0; i<arr.size();i++){
                            for(int j =0; j< arr[i].size();j++){
                                img = arr[i][j].draw_this(img);
                            }
                        }*/
                        //Calc new Sync
                        for(int i = 1; i < plan.size();i++){
                            for(int j = 1; j <plan[i].size();j++){
                                //cout<<"plansize_"<<plan[i].size()<<endl;
                                //cout<<"arrsize__"<<arr[i].size()<<endl;
                                if(plan[i][j].text != ""){
                                    //cout<<plan[i][j].text<<"_:plan text"<<endl;
                                    if(arr[i][j].text == ""){
                                        //cout<<arr[i][j].text<<"_:records text"<<endl;
                                        error++;
                                    }
                                }
                            }
                            Sync[i-1].text = ""+to_string(100-floor(error*100/31));
                            error = 0;
                        }
                        cout<<"testkk"<<endl;
                        for(int i = 0; i < Sync.size();i++){
                            img = Sync[i].draw_this(img);
                        }
                        //HEATMAP
                        for(int i = 0; i<arr.size();i++){
                            for(int j =0; j< arr[i].size();j++){
                                img = arr[i][j].draw_this(img);
                                if(i > 0&& j>0){
                                    if(arr[i][j].text != ""){
                                        //cout<<arr[i][j].text<<" hehe"<<endl;
                                        int heat = stoi(arr[i][j].text);
                                        //cout<<heat<<" heat "<<endl;
                                        int rank = floor(heat*100/GameData::maxpres);
                                        //cout<<rank<<" %_"<<endl;
                                        int digit2 = (to_string(rank)[to_string(rank).size()-1])-'0';
                                        rank -= digit2;
                                        //cout <<rank<<" rank"<<endl;
                                        if(rank <= 20){
                                            arr[i][j].color = red20;
                                        } else {
                                            arr[i][j].color = heatmap[rank];
                                        }
                                    }
                                }
                            }
                        }
                        img = draw_thing(1,1,8,32,arr,img);
                        img.display(main_disp);

                    }
                    else if(battlerecord_active && arrowright.x <= main_disp.mouse_x() && main_disp.mouse_x() <= arrowright.x1 &&
                    arrowright.y <= main_disp.mouse_y() && main_disp.mouse_y() <= arrowright.y1 && main_disp.button()){
                        cout<<"arrowright"<<endl;
                        if(week < get_currweek()){
                            week++;
                        }

                        weekly.text = "Week: "+to_string(week);
                        img = ogimg2;
                        img = weekly.draw_this(img);
                        arr = loadplanfun(week,arr);
                        /*
                        for(int i = 0; i<arr.size();i++){
                            for(int j =0; j< arr[i].size();j++){
                                img = arr[i][j].draw_this(img);
                            }
                        }*/
                        //
                        for(int i = 1; i < plan.size();i++){
                            for(int j = 1; j <plan[i].size();j++){
                                //cout<<"plansize_"<<plan[i].size()<<endl;
                                //cout<<"arrsize__"<<arr[i].size()<<endl;
                                if(plan[i][j].text != ""){
                                    //cout<<plan[i][j].text<<"_:plan text"<<endl;
                                    if(arr[i][j].text == ""){
                                        //cout<<arr[i][j].text<<"_:records text"<<endl;
                                        error++;
                                    }
                                }
                            }
                            Sync[i-1].text = ""+to_string(100-floor(error*100/31));
                            error = 0;
                        }
                        cout<<"testkk"<<endl;
                        for(int i = 0; i < Sync.size();i++){
                            img = Sync[i].draw_this(img);
                        }
                        //HEATMAP
                        for(int i = 0; i<arr.size();i++){
                            for(int j =0; j< arr[i].size();j++){
                                img = arr[i][j].draw_this(img);
                                if(i > 0&& j>0){
                                    if(arr[i][j].text != ""){
                                        //cout<<arr[i][j].text<<" hehe"<<endl;
                                        int heat = stoi(arr[i][j].text);
                                        //cout<<heat<<" heat "<<endl;
                                        int rank = floor(heat*100/GameData::maxpres);
                                        //cout<<rank<<" %_"<<endl;
                                        int digit2 = (to_string(rank)[to_string(rank).size()-1])-'0';
                                        rank -= digit2;
                                        //cout <<rank<<" rank"<<endl;
                                        if(rank <= 20){
                                            arr[i][j].color = red20;
                                        } else {
                                            arr[i][j].color = heatmap[rank];
                                        }
                                    }
                                }
                            }
                        }
                        img = draw_thing(1,1,8,32,arr,img);
                        img.display(main_disp);

                    }

                }


            }

        }

        //always at the end
        img.display(main_disp);
    }
}

#endif //PERFORMANCE_COCKPIT_BATTLEPLAN_H