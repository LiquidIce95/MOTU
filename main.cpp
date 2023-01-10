#include "./DB.h"
#include "./Pomofocus.h"
#include "./Battleplan.h"
using namespace std;
using namespace cimg_library;


/* does not work
bool Mouse_sensor_rectangle(CImgDisplay disp, int x0, int y0, int x1, int y1){
    if(disp.mouse_x() >= x0 && disp.mouse_x() <= x1&&
    disp.mouse_y()>= y0 && disp.mouse_y() <= y1){
        return true;
    }

    return false;
}
*/
/*TODO  Pomofocus fertig (schön), verbindung mit DB, testen
 *          -Eingabe von Tagesablauf, wie internetversion
 *          -Anzeige mit Fortschrittsbalken
 *          -Verbindung mit Db , schreiben
 *      Kalender machen, verbindung mit DB, testen
 *      Stats
 *      Polishing (Gamification), fertig stellen
 *      Messenger*/

//https://www.pixilart.com/draw
//    system("pushd /home/Dave/Music/Downloaded by MediaHuman/ \nplay lofi.mp3");
int main() {
    //Basic Colors
    const unsigned char
    white[]  = { 255, 255, 255 }, black[] = { 0, 0, 0 }, red[] = { 120, 50, 80 },
    yellow[] = { 200, 155, 0 }, green[] = { 30, 200, 70 }, purple[] = { 175, 32, 186 },
    blue[] = { 55, 140, 185 }, grey[] = { 127, 127, 127 }, darkblue[] = {20,100,120},
    darkgrey[] = {60,60,60}, darkpurple[] = {54,21,59};

    //making main window of app
    CImg<unsigned char> img((dbrelprefix+"/Pics/Background.jpg").c_str());
    CImgDisplay main_disp(img, "Performance Cockpit");

    CImg<unsigned char> ogimg((dbrelprefix+"/Pics/Background.jpg").c_str());
    cout<<"maxpres "<<GameData::maxpres<<endl;
    while(!main_disp.is_closed()){
        if(main_disp.is_keyESC()){
            //Update Battlerecords
            main_disp.close();
        }
        //Background color
        img.draw_image(ogimg);
        //Menu display
        CImg<unsigned char> Title;
        Title.draw_text(0,0,"Master Of The Universe",darkpurple,0,1,120);
        img.draw_text(1920/2-Title.width()/2,1080/5,"Master Of The Universe",darkpurple,0,1,120);

        CImg<unsigned char> Pomofocus_menu;
        Pomofocus_menu.draw_text(0,0,"Pomofocus",black,0,1,50);
        int x0_pomo = 1920/2-Pomofocus_menu.width()/2;
        int y0_pomo = 2*1080/5;
        img.draw_text(x0_pomo,y0_pomo,"Pomofocus",black,0,1,50);

        CImg<unsigned char> Stats;
        Stats.draw_text(0,0,"Stats",black,0,1,50);
        int x0_stat = 1920/2-Stats.width()/2;
        int y0_stat = 2*1080/5+1080/8;
        img.draw_text(x0_stat,y0_stat,"Stats",black,0,1,50);

        CImg<unsigned char> Battleplan;
        Battleplan.draw_text(0,0,"Battleplan",black,0,1,50);
        int x0_Cal = 1920/2-Battleplan.width()/2;
        int y0_Cal = 2*1080/5+1080/4;
        img.draw_text(x0_Cal,y0_Cal,"Battleplan",black,0,1,50);

        CImg<unsigned char> Messenger;
        Messenger.draw_text(0,0,"Campaign",black,0,1,50);
        int x0_Mes = 1920/2-Messenger.width()/2;
        int y0_Mes = 2*1080/5+3*1080/8;
        img.draw_text(x0_Mes,y0_Mes,"Campaign",black,0,1,50);

        //Selection and calling mechanics
        if(main_disp.mouse_x()>=x0_pomo && main_disp.mouse_x()<=x0_pomo+Pomofocus_menu.width()
            && main_disp.mouse_y()>=y0_pomo && main_disp.mouse_y()<=y0_pomo+Pomofocus_menu.height() ){

            img.draw_rectangle(x0_pomo,y0_pomo,x0_pomo+Pomofocus_menu.width(),y0_pomo+Pomofocus_menu.height(),red,1);
            img.draw_text(x0_pomo,y0_pomo,"Pomofocus",black,0,1,50);

            //Click event
            if(main_disp.button()){
                Pomofocus();
            }

        } else if (main_disp.mouse_x()>=x0_stat && main_disp.mouse_x()<=x0_stat+Stats.width()
                   && main_disp.mouse_y()>=y0_stat && main_disp.mouse_y()<=y0_stat+Stats.height()) {

            img.draw_rectangle(x0_stat,y0_stat,x0_stat+Stats.width(),y0_stat+Stats.height(),red,1);
            img.draw_text(x0_stat,y0_stat,"Stats",black,0,1,50);

            //Click event
            if(main_disp.button()){
                //Stats();
            }

        } else if (main_disp.mouse_x()>=x0_Cal && main_disp.mouse_x()<=x0_Cal+Battleplan.width()
        && main_disp.mouse_y()>=y0_Cal && main_disp.mouse_y()<=y0_Cal+Battleplan.height()){

            img.draw_rectangle(x0_Cal,y0_Cal,x0_Cal+Battleplan.width(),y0_Cal+Battleplan.height(),red,1);
            img.draw_text(x0_Cal,y0_Cal,"Battleplan",black,0,1,50);

            //Click event
            if(main_disp.button()){
                Battleplans();
            }

        } else if (main_disp.mouse_x()>=x0_Mes && main_disp.mouse_x()<=x0_Mes+Messenger.width()
                   && main_disp.mouse_y()>=y0_Mes && main_disp.mouse_y()<=y0_Mes+Messenger.height()){

            img.draw_rectangle(x0_Mes,y0_Mes,x0_Mes+Messenger.width(),y0_Mes+Messenger.height(),red,1);
            img.draw_text(x0_Mes,y0_Mes,"Campaign",black,0,1,50);

            //Click event
            if(main_disp.button()){
                Campaign();
            }
        }

        img.display(main_disp);
    }

    return 0;
}
