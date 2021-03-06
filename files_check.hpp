#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class imageCheck
{
public:
    vector<string> fileName;
    imageCheck()
    {
        fileName.push_back(MAIN_MENU_PLAY_BUTTON_OUTER);
        fileName.push_back(FELT_FRONT);
        fileName.push_back(X_WINNING_PIECE_FILEPATH);
        fileName.push_back(O_WINNING_PIECE_FILEPATH);
        fileName.push_back(PLAY_BUTTON);
        fileName.push_back(PAUSE_BUTTON);
        fileName.push_back(X_PIECE_FILEPATH);
        fileName.push_back(O_PIECE_FILEPATH);
        fileName.push_back(resume_button);
        fileName.push_back(Home_button);
        fileName.push_back(GRID_SPRITE_FILEPATH);
        fileName.push_back("Resources/res/Retry Button.png");
        fileName.push_back("Resources/res/Home Button.png");
        fileName.push_back("Resources/fonts/ARIAL.TTF");
    }

    bool check_image_exist()
    {
        bool missing=false;
      
        for (unsigned int i = 0; i < fileName.size(); i++)
        {
            std::ifstream infile(fileName[i]);
            if (!infile.good())
            {
                if(!missing)
                    cout<<"Missing files:"<<endl;
                missing=true;
                cout << fileName[i] << endl;
            }
        }
        if(missing){
            //false for missing files
            return false;
        }
        else{
            //true for no files are missing
            return true;
        }
        cout<<"Image files check finished"<<endl;
    }
};
