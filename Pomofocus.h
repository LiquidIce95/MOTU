//
// Created by Dave on 6/27/21.
//
#include "DB.h"

#ifndef PERFORMANCE_COCKPIT_POMOFOCUS_H
#define PERFORMANCE_COCKPIT_POMOFOCUS_H

using namespace std;
using namespace cimg_library;
using namespace std::chrono;

vector<Pomos> loadday(vector<vector<Pomos>> arr, int day){
    vector<Pomos> Todo;
    arr = loadplanfun(0,arr);
    for(int j = 1; j < arr[day].size(); j++){
        if(arr[day][j].text != ""){
            Todo.push_back(arr[day][j]);
        }
    }
    return Todo;

}
CImg<unsigned char> drawTodo(vector<Pomos> Todo, CImg<unsigned char> img, int view, int x0,int y0, int height, int width){
    cout<<"draw_todo"<<endl;
    cout<<Todo.size()<<endl;
    cout<<view<<endl;
    for(int j = 0; j < 10 && j+view<Todo.size(); j++){
        Todo[j+view].x = x0;
        Todo[j+view].y = y0+j*height;
        Todo[j+view].x1 = Todo[j+view].x+width;
        Todo[j+view].y1 = Todo[j+view].y+height;
        Todo[j+view].fontsize = 40;
        img = Todo[j+view].draw_this(img);
    }
    return img;
}
//irreführend, nicht für woche sondern scrollen gebraucht
int weekmod(int week, int mode){
    if(mode == 1) {
        week++;
    }else {
        week--;
    }
    return week;
}
/*void* item_fireworks() {
    CImg<unsigned char> img(640,480,1,3,0);
    CImgDisplay disp(img,"[#21] - Fireworks (Click to add/explode rockets)");
    CImgList<unsigned char> colors;
    const unsigned char white[] = { 255,255,255 }, red[] = { 128,0,0 };
    CImgList<float> particles;
    float time = 0, speed = 100.0f;

    while (!disp.is_closed() && !disp.is_keyQ() && !disp.is_keyESC()) {

        if (disp.button()&1 || !particles.size() || (--time)<0) {
            particles.insert(CImg<>::vector((float)cimg::rand()*img.width(),(float)img.height(),
                                            (float)cimg::rand(-1,1)*4,-6 - (float)cimg::rand()*3,
                                            30 + 60*(float)cimg::rand(),3));
            colors.insert(CImg<unsigned char>::vector(255,255,255));
            time = (float)(cimg::rand()*speed);
        }
        img*=0.92f;

        cimglist_for(particles,l) {
            bool remove_particle = false;
            float &x = particles(l,0), &y = particles(l,1), &vx = particles(l,2), &vy = particles(l,3),
            &t = particles(l,4), &r = particles(l,5);
            const float r2 = (t>0 || t<-42)?r/3:r*(1 - 2*(-(t + 2)/40.0f)/3);
            img.draw_ellipse((int)x,(int)y,r,r2,(float)(std::atan2(vy,vx)*180/cimg::PI),colors[l].data(),0.6f);
            x+=vx; y+=vy; vy+=0.09f; t--;
            if (y>img.height() + 10 || x<0 || x>=img.width() + 10) remove_particle = true;

            if (t<0 && t>=-1) {
                if ((speed*=0.9f)<10) speed=10.0f;
                const unsigned char
                cr = (unsigned char)std::min(50 + 3*(unsigned char)(100*cimg::rand()), 255),
                cg = (unsigned char)std::min(50 + 3*(unsigned char)(100*cimg::rand()), 255),
                cb = (unsigned char)std::min(50 + 3*(unsigned char)(100*cimg::rand()), 255);
                const float di = 10 + (float)cimg::rand()*60, nr = (float)cimg::rand()*30;
                for (float i=0; i<360; i+=di) {
                    const float rad = i*(float)cimg::PI/180, c = (float)std::cos(rad), s = (float)std::sin(rad);
                    particles.insert(CImg<>::vector(x,y,2*c + vx/1.5f,2*s + vy/1.5f,-2.0f,nr));
                    colors.insert(CImg<unsigned char>::vector(cr,cg,cb));
                }
                remove_particle = true;
            } else if (t<-1) { r*=0.95f; if (r<0.5f) remove_particle=true; }
            if (remove_particle) { particles.remove(l); colors.remove(l); l--; }
        }
        if (disp.button()&2) cimglist_for(particles,l) if (particles(l,4)>0) particles(l,4)=0.5f;
        img.draw_text(5,5," %u frames/s ",white,red,0.5f,13,(unsigned int)disp.frames_per_second());
        disp.display(img).wait(25);
        if (disp.is_keyCTRLLEFT() && disp.is_keyF()) disp.resize(640,480,false).toggle_fullscreen(false);
        if (disp.is_resized()) disp.resize(disp,false);
    }
    return 0;
}*/
/*void dostuff(Pomos h){
    h.claimreward();
}*/
/*void dostuff2(Pomos h,int  id){
    h.claimreward(id);
}*/
void highfocuspomos(int prestige){


    int rank = floor(prestige*100/GameData::maxpres);
    cout<<"persige is ::_"<<prestige<<endl;
    if(rank>= 80){
        Pomos highpom;
        highpom.reward = 0;
        highpom.text = "highpomo";
        highpom.trigger.push_back("Focus");
        highpom.trigger.push_back("Channeler");
        highpom.trigger.push_back("Hard Focus");
        highpom.trigger.push_back("Enlightened");
        highpom.trigger.push_back("Serious");

        highpom.claimreward();

    }


}
void getearly(){

    int time = get_time();

    if(time <= 735){
        Pomos highpom;
        highpom.reward = 0;
        highpom.text = "timepomo";
        highpom.trigger.push_back("reliable");
        highpom.trigger.push_back("clock");
        highpom.trigger.push_back("Conquer the morning");
        highpom.trigger.push_back("Morning Routine");
        highpom.trigger.push_back("Agent of The blazing Sun");
        highpom.trigger.push_back("Morning Champion");
        highpom.trigger.push_back("God of the blazing Sun");

        highpom.claimreward();

    }

}
void Pomofocus(){
    //return int to claim, then here you get index via that integer if not 0 execute

    CImg<unsigned char> img((dbrelprefix+"/Pics/PomofocusMenu.png").c_str());
    CImgDisplay main_disp(img,"Pomofocus");
    vector<Pomos> window_ele;
    vector<Pomos> arrows;

    Pomos Pomodoros;
    Pomodoros.text = "Pomodorofinish";
    Pomodoros.reward = 5;

    int xpres = 1500;
    int ypres = 280;

    Pomos prestige;
    prestige.text =  Select_val((dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile).c_str(),"Globalstats","_rowid_","1","VAL2");
    prestige.x = xpres;
    prestige.x1 = prestige.x+400;
    prestige.y = ypres;
    prestige.y1 = prestige.y+30;
    prestige.fontsize = 25;
    img = prestige.draw_this(img);

    //draw load menu
    Pomos Load;
    Load.x = 220;
    Load.y = 130;
    Load.x1 = 320;
    Load.y1 = 150;
    Load.text = "Load day";
    img = Load.draw_this(img);

    //Arrow up
    Pomos arrowup;
    arrowup.x = 860;
    arrowup.y = 130;
    arrowup.x1 = 900;
    arrowup.y1 = 150;
    arrowup.fun4 = weekmod;
    arrowup.text = "up";
    arrows.push_back(arrowup);
    img = arrowup.draw_this(img);

    Pomos arrowdown;
    arrowdown.x = 860;
    arrowdown.y = 900;
    arrowdown.x1 = 900;
    arrowdown.y1 = 920;
    arrowdown.fun4 = weekmod;
    arrowdown.text = "down";
    arrows.push_back(arrowdown);
    img = arrowdown.draw_this(img);


    Pomos Clock;
    Clock.x = 120;
    Clock.x1 = 350;
    Clock.y = 350;
    Clock.y1 = 600;

    //actions
    Pomos Grade_45;
    Grade_45.x = 1260;
    Grade_45.y = 50;
    Grade_45.x1 = 1460;
    Grade_45.y1 = 100;
    Grade_45.reward = 5;
    Grade_45.text = "Earn_a_Grade_4.5";
    Grade_45.trigger.push_back("reputation");
    window_ele.push_back(Grade_45);
    img = Grade_45.draw_this(img);
    
    Pomos Grade_5;
    Grade_5.x = 1260;
    Grade_5.y = 100;
    Grade_5.x1 = 1460;
    Grade_5.y1 = 150;
    Grade_5.reward = 10;
    Grade_5.text = "Earn_a_Grade_5.0";
    Grade_5.trigger.push_back("Mystical");
    window_ele.push_back(Grade_5);
    img = Grade_5.draw_this(img);
    
    Pomos Grade_55;
    Grade_55.x = 1260;
    Grade_55.y = 150;
    Grade_55.x1 = 1460;
    Grade_55.y1 = 200;
    Grade_55.reward = 20;
    Grade_55.text = "Earn_a_Grade_5.5";
    Grade_55.trigger.push_back("Legendary");
    window_ele.push_back(Grade_55);
    img = Grade_55.draw_this(img);

    Pomos Grade_6;
    Grade_6.x = 1260;
    Grade_6.y = 200;
    Grade_6.x1 = 1460;
    Grade_6.y1 = 250;
    Grade_6.reward = 35;
    Grade_6.text = "Earn_a_Grade_6.0";
    Grade_6.trigger.push_back("Divinity");
    window_ele.push_back(Grade_6);
    img = Grade_6.draw_this(img);

    Pomos AR;
    AR.x = 1260;
    AR.y = 250;
    AR.x1 = 1460;
    AR.y1 = 300;
    AR.reward = 12;
    AR.text = "Active_Recall";
    AR.trigger.push_back("Reminder");
    AR.trigger.push_back("Memory Expert");
    AR.trigger.push_back("Memory Champ");
    AR.trigger.push_back("Memory God");
    window_ele.push_back(AR);
    img = AR.draw_this(img);

    Pomos read;
    read.x = 1260;
    read.y = 300;
    read.x1 = 1460;
    read.y1 = 350;
    read.reward = 1;
    read.text = "Read_Pages";
    read.trigger.push_back("BookWorm");
    read.trigger.push_back("Scanner");
    read.trigger.push_back("Professor");
    read.trigger.push_back("Philosopher");
    window_ele.push_back(read);
    img = read.draw_this(img);

    Pomos Lecture;
    Lecture.x = 1260;
    Lecture.y = 350;
    Lecture.x1 = 1460;
    Lecture.y1 = 400;
    Lecture.reward = 10;
    Lecture.text = "Watch_Lecture";
    Lecture.trigger.push_back("Listener");
    Lecture.trigger.push_back("Absorber");
    Lecture.trigger.push_back("Sponge");
    Lecture.trigger.push_back("Assimilator");
    Lecture.trigger.push_back("Integrator");
    window_ele.push_back(Lecture);
    img = Lecture.draw_this(img);

    Pomos Correction;
    Correction.x = 1260;
    Correction.y = 400;
    Correction.x1 = 1460;
    Correction.y1 = 450;
    Correction.reward = 12;
    Correction.text = "Make_Correction";
    Correction.trigger.push_back("Corrector");
    Correction.trigger.push_back("Judge");
    Correction.trigger.push_back("Precision");
    Correction.trigger.push_back("skeptic");
    Correction.trigger.push_back("Investigator");
    Correction.trigger.push_back("Inquisitor");
    Correction.trigger.push_back("Lord Inquisitor");
    window_ele.push_back(Correction);
    img = Correction.draw_this(img);

    Pomos Summary;
    Summary.x = 1260;
    Summary.y = 450;
    Summary.x1 = 1460;
    Summary.y1 = 500;
    Summary.reward = 12;
    Summary.text = "Make_Summary";
    Summary.trigger.push_back("Morpher");
    Summary.trigger.push_back("Modeller");
    Summary.trigger.push_back("Structurer");
    Summary.trigger.push_back("Manifestician");
    Summary.trigger.push_back("Scriptor");
    Summary.trigger.push_back("Archscriptor");
    Summary.trigger.push_back("Primescriptor");
    window_ele.push_back(Summary);
    img = Summary.draw_this(img);

    Pomos Question;
    Question.x = 1260;
    Question.y = 500;
    Question.x1 = 1460;
    Question.y1 = 550;
    Question.reward = 3;
    Question.text = "Answer_Question";
    Question.trigger.push_back("Student");
    Question.trigger.push_back("Truth Seeker");
    Question.trigger.push_back("Scientist");
    Question.trigger.push_back("Precursor");
    Question.trigger.push_back("Void Wanderer");
    Question.trigger.push_back("All Mighty");
    window_ele.push_back(Question);
    img = Question.draw_this(img);

    Pomos Solve_Task;
    Solve_Task.x = 1260;
    Solve_Task.y = 550;
    Solve_Task.x1 = 1460;
    Solve_Task.y1 = 600;
    Solve_Task.reward = 7;
    Solve_Task.text = "Solve_Task_Subtask";
    Solve_Task.trigger.push_back("Solver");
    Solve_Task.trigger.push_back("Accomplisher");
    Solve_Task.trigger.push_back("Sharpshooter");
    Solve_Task.trigger.push_back("Analytician");
    Solve_Task.trigger.push_back("Mathematician");
    window_ele.push_back(Solve_Task);
    img = Solve_Task.draw_this(img);

    Pomos Test_idea;
    Test_idea.x = 1260;
    Test_idea.y = 600;
    Test_idea.x1 = 1460;
    Test_idea.y1 = 650;
    Test_idea.reward = 3;
    Test_idea.text = "Test_Idea";
    window_ele.push_back(Test_idea);
    img = Test_idea.draw_this(img);
    
    int day = get_currday();
    vector<vector<Pomos>> arr;
    for(int i = 0; i < 8; i++){
        vector<Pomos> x;
        arr.push_back(x);
        for(int j = 0; j< 32; j++){
            arr[i].push_back(Pomos());
        }
    }

    int x0 = 650;
    int y0 = 290;
    int width = 500;
    int height = 50;
    int view = 0;
    vector<Pomos> Todo;
    for(int i = 0; i< 30; i++){
        Todo.push_back(Pomos());
    }
    bool active = true;
    bool loaded = false;
    bool start = false;
    CImg<unsigned char> ogimg = img;

    img.display(main_disp);
    CImg<unsigned char> img2((dbrelprefix+"/Pics/rsz_sunlarge.jpg").c_str());
    CImg<unsigned char> ogimg2((dbrelprefix+"/Pics/rsz_sunlarge.jpg").c_str());
    int progress = 0;

    int starttime = 0;
    int currtime = 0;
    int oldtmin =0;
    int oldmin = 0;
    int min = 0;
    bool pause = false;
    int Pomodoro = 25;
    int pauset = 5;

    int realsize = 0;
    int prestige2 = 0;

    vector<thread> listi;
    int z = -1;

    while(!main_disp.is_closed()&& active){

        //Clock
        while(active && Clock.x <= main_disp.mouse_x()&& main_disp.mouse_x() <= Clock.x1 &&
        Clock.y <= main_disp.mouse_y() && main_disp.mouse_y()<= Clock.y1 && main_disp.button()){
            start = true;
            listi.push_back(thread());
            z++;
            listi[z] = thread{play_pomostart};
            if(scanner("Freestye or planned? 1 == planned\n, 2 == Frestyle") == "1"){
                if(scanner("Start from 0? 1 == yes") == "1"){
                    Update_rowid(dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile,"Globalstats","VAL","0","1");
                    progress = 0;
                } else {
                    progress = stoi(Select_val(dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile,"Globalstats","ID","1","VAL"));
                }
            } else {
                int amount = stoi(scanner("How many units do you want to study? type int "));
                for(int i = 0; i< amount; i++){
                    Todo.push_back(Pomos());
                    Todo[i].text = scanner("Type in study topic");
                }
                realsize = amount;
            }
            oldtmin = get_min();
            oldmin = oldtmin;

            img2.display(main_disp);
        }
        while(start){
            if(main_disp.is_keyESC()){
                start = false;
                //main_disp.close();
            }
            if(progress >= realsize){
                start = false;
                listi.push_back(thread());
                z++;
                listi[z] = thread{play_victory};
            }
            if(!pause){
                oldtmin = get_min();
                if(oldtmin != oldmin){
                    min++;
                    oldmin = oldtmin;
                    img2 = ogimg2;
                }

                img2.draw_text(910,20, to_string(Pomodoro-min).c_str(),strongyellow,10,1,130 ,130);
                if(Pomodoro-min<= 0){
                    progress++;
                    Update_rowid(dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile,"Globalstats","VAL",to_string(progress),"1");
                    Pomodoros.claimreward();
                    listi.push_back(thread());
                    z++;
                    listi[z] = thread{play_task};
                    //std::thread newwindow;
                    highfocuspomos(prestige2);
                    getearly();
                    listi.push_back(thread());
                    z++;
                    listi[z] = thread{play_pomopause};
                    prestige2 = 0;
                    //newwindow = thread{dostuff,Pomodoros};

                    //newwindow.join();
                    prestige.text =  Select_val(dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile,"Globalstats","_rowid_","1","VAL2");
                    img = prestige.draw_this(img);

                    min = 0;
                    pause = true;
                }
                img2.draw_text(20,20,(" working on: "+Todo[progress].text).c_str(),brightred,10,1,50,50);
                img2.display(main_disp);
            } else {
                oldtmin = get_min();
                if(oldtmin != oldmin){
                    min++;
                    oldmin = oldtmin;
                    img = ogimg;
                }
                if(pauset-min<= 0){
                    listi.push_back(thread());
                    z++;
                    listi[z] = thread{play_pomostart};
                    min = 0;
                    pause = false;
                }
                img.draw_text(910,20, to_string(pauset-min).c_str(),cyan,10,1,130 ,130);
                //img.draw_text(20,20,Todo[progress].text.c_str(),brightred,10,1,50,50);
                img.display(main_disp);
            }


            while(active && window_ele[0].x-10 <= main_disp.mouse_x() &&main_disp.mouse_x() <= window_ele[11].x1+10
            && window_ele[0].y-10 <= main_disp.mouse_y() && main_disp.mouse_y()<= window_ele[11].y1+10 ){
                for(int i = 0; i< window_ele.size();i++){
                    while(active && window_ele[i].x <= main_disp.mouse_x() &&main_disp.mouse_x() <= window_ele[i].x1
                    && window_ele[i].y <= main_disp.mouse_y() && main_disp.mouse_y()<= window_ele[i].y1 ){
                        window_ele[i].color = red;
                        img2 = window_ele[i].draw_this(img2);
                        img2.display(main_disp);
                        if( main_disp.button()){
                            usleep(100000);
                            window_ele[i].claimreward();
                            prestige2 += window_ele[i].reward;
                            listi.push_back(thread());
                            z++;
                            listi[z] = thread{play_task};
                            //newwindow = thread{dostuff,window_ele[i]};
                            cout<<"action_performed"<<endl;
                        }
                    }
                    window_ele[i].color = white;
                    img2 = window_ele[i].draw_this(img2);

                }
                img2 = ogimg2;
                img2.display(main_disp);

            }

        }

        //loadmenu
        while(active && Load.x <= main_disp.mouse_x()&& main_disp.mouse_x() <= Load.x1 &&
        Load.y <= main_disp.mouse_y() && main_disp.mouse_y()<= Load.y1 && main_disp.button()){
            cout<<"Load_menu"<<endl;
            if(main_disp.button()){
                usleep(100000);
                Todo = loadday(arr,day);
                //draw
                loaded = true;
                cout<<Todo.size()<<"size of todo"<<endl;
                realsize = Todo.size();
                img = drawTodo(Todo,img,view,x0,y0,height,width);
                ogimg = img;
                img.display(main_disp);
            }
        }
        while(active && window_ele[0].x-10 <= main_disp.mouse_x() &&main_disp.mouse_x() <= window_ele[11].x1+10
        && window_ele[0].y-10 <= main_disp.mouse_y() && main_disp.mouse_y()<= window_ele[11].y1+10 ){
            for(int i = 0; i< window_ele.size();i++){
                while(active && window_ele[i].x <= main_disp.mouse_x() &&main_disp.mouse_x() <= window_ele[i].x1
                && window_ele[i].y <= main_disp.mouse_y() && main_disp.mouse_y()<= window_ele[i].y1 ){
                    window_ele[i].color = red;
                    img = window_ele[i].draw_this(img);
                    img.display(main_disp);
                    if(main_disp.is_keyT() && main_disp.button()){
                        usleep(100000);
                        int id = stoi(scanner("type in rowid__ think twice before using this!!"));
                        window_ele[i].claimreward(id);
                        //newwindow = thread{dostuff2,window_ele[i],id};

                        prestige.text =  Select_val(dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile,"Globalstats","_rowid_","1","VAL2");
                        img = prestige.draw_this(img);
                        listi.push_back(thread());
                        z++;
                        listi[z] = thread{play_task};
                        cout<<"action_performed2"<<endl;
                    }
                    if( main_disp.button()){
                        usleep(100000);
                        window_ele[i].claimreward();
                        listi.push_back(thread());
                        z++;
                        listi[z] = thread{play_task};
                        //newwindow = thread{dostuff,window_ele[i]};
                        prestige.text =  Select_val(dbrelprefix+"/DBs/Campaigns/"+GameData::Gamefile,"Globalstats","_rowid_","1","VAL2");
                        img = prestige.draw_this(img);
                        listi.push_back(thread());
                        z++;
                        listi[z] = thread{play_task};
                        cout<<"action_performed"<<endl;
                    }
                }
                window_ele[i].color = white;
                img = window_ele[i].draw_this(img);

            }
            img = ogimg;
            img.display(main_disp);

        }

        for(int i = 0; i< arrows.size();i++){
            while(active && arrows[i].x <= main_disp.mouse_x() && main_disp.mouse_x() <= arrows[i].x1
            && arrows[i].y <= main_disp.mouse_y() && main_disp.mouse_y() <= arrows[i].y1 && main_disp.button()
            && Todo[0].text != ""){
                usleep(100*1000);
                if(arrows[i].text =="up" && view < Todo.size()-10 && Todo.size() > 10){
                    view = arrows[i].fun4(view,1);
                    //cout<<"arrow_boy"<<endl;
                }else if(arrows[i].text =="down" && view > 0){
                    view = arrows[i].fun4(view,0);
                    //cout<<"arrow_boy"<<endl;
                }
                img = drawTodo(Todo,img,view,x0,y0,height,width);
                ogimg = img;
                img.display(main_disp);

            }
        }

        if(main_disp.is_keyESC()){
            active = false;
            for(int i = 0; i< listi.size();i++){
                listi[i].join();
            }
            main_disp.close();
        }

    }

}


#endif //PERFORMANCE_COCKPIT_POMOFOCUS_H
