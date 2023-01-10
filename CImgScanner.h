//
// Created by Dave on 8/2/21.
//


#ifndef PERFORMANCE_COCKPIT_CIMGSCANNER_H
#define PERFORMANCE_COCKPIT_CIMGSCANNER_H
using namespace std;
using namespace cimg_library;


//TESTED
string scanner(string msg){
    const unsigned char
    white[]  = { 255, 255, 255 }, black[] = { 0, 0, 0 }, red[] = { 120, 50, 80 },
    yellow[] = { 200, 155, 0 }, green[] = { 30, 200, 70 }, purple[] = { 175, 32, 186 },
    blue[] = { 55, 140, 185 }, grey[] = { 127, 127, 127 }, darkblue[] = {20,100,120},
    darkgrey[] = {60,60,60};

    string input = "";

    CImg<unsigned char> img("/Pics/Scroll1.jpg");
    CImgDisplay show(img, "User Input");

    int milisecond = 1000;
    int large = 0;

    while(!show.is_closed()){

        if(show.is_key0()){
            input += "0";
            usleep(110*milisecond);
        } else if (show.is_key1()){
            input += "1";
            usleep(110*milisecond);
        } else if (show.is_key2()){
            input += "2";
            usleep(110*milisecond);
        } else if (show.is_key3()){
            input += "3";
            usleep(110*milisecond);
        } else if (show.is_key4()){
            input += "4";
            usleep(110*milisecond);
        } else if (show.is_key5()){
            input += "5";
            usleep(110*milisecond);
        } else if (show.is_key6()){
            input += "6";
            usleep(110*milisecond);
        } else if (show.is_key7()){
            input += "7";
            usleep(110*milisecond);
        } else if (show.is_key8()){
            input += "8";
            usleep(110*milisecond);
        } else if (show.is_key9()){
            input += "9";
            usleep(110*milisecond);
        }

        if(large == 1){
            if (show.is_keyQ()){
                input += "Q";
                usleep(110*milisecond);
            } else if (show.is_keyW()){
                input += "W";
                usleep(110*milisecond);
            } else if (show.is_keyE()){
                input += "E";
                usleep(110*milisecond);
            } else if (show.is_keyR()){
                input += "R";
                usleep(110*milisecond);
            } else if (show.is_keyT()){
                input += "T";
                usleep(110*milisecond);
            } else if (show.is_keyZ()){
                input += "Z";
                usleep(110*milisecond);
            } else if (show.is_keyU()){
                input += "U";
                usleep(110*milisecond);
            } else if (show.is_keyI()){
                input += "I";
                usleep(110*milisecond);
            } else if (show.is_keyO()){
                input += "O";
                usleep(110*milisecond);
            } else if (show.is_keyP()){
                input += "P";
                usleep(110*milisecond);
            } else if (show.is_keyA()){
                input += "A";
                usleep(110*milisecond);
            } else if (show.is_keyS()){
                input += "S";
                usleep(110*milisecond);
            } else if (show.is_keyD()){
                input += "D";
                usleep(110*milisecond);
            } else if (show.is_keyF()){
                input += "F";
                usleep(110*milisecond);
            } else if (show.is_keyG()){
                input += "G";
                usleep(110*milisecond);
            } else if (show.is_keyH()){
                input += "H";
                usleep(110*milisecond);
            } else if (show.is_keyJ()){
                input += "J";
                usleep(110*milisecond);
            } else if (show.is_keyK()){
                input += "K";
                usleep(110*milisecond);
            } else if (show.is_keyL()){
                input += "L";
                usleep(110*milisecond);
            } else if (show.is_keyY()){
                input += "Y";
                usleep(110*milisecond);
            } else if (show.is_keyX()){
                input += "X";
                usleep(110*milisecond);
            } else if (show.is_keyC()){
                input += "C";
                usleep(110*milisecond);
            } else if (show.is_keyV()){
                input += "V";
                usleep(110*milisecond);
            } else if (show.is_keyB()){
                input += "B";
                usleep(110*milisecond);
            } else if (show.is_keyN()){
                input += "N";
                usleep(110*milisecond);
            } else if (show.is_keyM()){
                input += "M";
                usleep(110*milisecond);
            }
        }

        else if (large == 0){
            if (show.is_keyQ()){
                input += "q";
                usleep(110*milisecond);
            } else if (show.is_keyW()){
                input += "w";
                usleep(110*milisecond);
            } else if (show.is_keyE()){
                input += "e";
                usleep(110*milisecond);
            } else if (show.is_keyR()){
                input += "r";
                usleep(110*milisecond);
            } else if (show.is_keyT()){
                input += "t";
                usleep(110*milisecond);
            } else if (show.is_keyZ()){
                input += "z";
                usleep(110*milisecond);
            } else if (show.is_keyU()){
                input += "u";
                usleep(110*milisecond);
            } else if (show.is_keyI()){
                input += "i";
                usleep(110*milisecond);
            } else if (show.is_keyO()){
                input += "o";
                usleep(110*milisecond);
            } else if (show.is_keyP()){
                input += "p";
                usleep(110*milisecond);
            } else if (show.is_keyA()){
                input += "a";
                usleep(110*milisecond);
            } else if (show.is_keyS()){
                input += "s";
                usleep(110*milisecond);
            } else if (show.is_keyD()){
                input += "d";
                usleep(110*milisecond);
            } else if (show.is_keyF()){
                input += "f";
                usleep(110*milisecond);
            } else if (show.is_keyG()){
                input += "g";
                usleep(110*milisecond);
            } else if (show.is_keyH()){
                input += "h";
                usleep(110*milisecond);
            } else if (show.is_keyJ()){
                input += "j";
                usleep(110*milisecond);
            } else if (show.is_keyK()){
                input += "k";
                usleep(110*milisecond);
            } else if (show.is_keyL()){
                input += "l";
                usleep(110*milisecond);
            } else if (show.is_keyY()){
                input += "y";
                usleep(110*milisecond);
            } else if (show.is_keyX()){
                input += "x";
                usleep(110*milisecond);
            } else if (show.is_keyC()){
                input += "c";
                usleep(110*milisecond);
            } else if (show.is_keyV()){
                input += "v";
                usleep(110*milisecond);
            } else if (show.is_keyB()){
                input += "b";
                usleep(110*milisecond);
            } else if (show.is_keyN()){
                input += "n";
                usleep(110*milisecond);
            } else if (show.is_keyM()){
                input += "m";
                usleep(110*milisecond);
            }
        }
        //Switching between large and small letters and special
        if (show.is_keySHIFTLEFT()){
            large = 1;
        } else if (show.is_keySHIFTRIGHT()){
            large = 0;
        } else if (show.is_keyENTER()){
            cout<<input<<endl;
            return input;
        } else if (show.is_keyDELETE()){
            input.erase(input.end()-1);
            usleep(120*milisecond);
            cout<<input<<endl;
        }

        CImg<unsigned char> img("/Pics/Scroll1.jpg");
        img.draw_text(500,100,msg.c_str(),black,0,1,100);
        img.draw_text(500,500,input.c_str(),black,0,1,100);        img.display(show);

    }


    return input;
}


#endif //PERFORMANCE_COCKPIT_CIMGSCANNER_H
