#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "headers.h"
#include <shlobj.h>

#include "rlutil.h"

#include <chrono>
#include <algorithm>



using namespace std;

typedef std::chrono::high_resolution_clock Clock;

string cubeRevert(bool);
void applyMove2(char amove);
void showCube(void);
void unpruner(void);
string remove_last_word_if(string sentence);
//void algparser(int);
size_t countWords(std::string s);
string solutionreducer(string);
string scramble;
string inputWCA;
bool firstWordWCA=0;
bool isScramble2=0;
bool isSolver2=0;
bool isCheck=0;
bool isDepth=0;
bool isAnalyze=0;
bool isSet=0;
int isSet2=0;
int number=3;
int oldnumber=0;
int tempnumber;
bool setOutput=1;
bool asetstate=0;
bool prunedyet=0;
int prunedmethod=99;
__int64 EPo, EOo, CPo, COo, CNo;
bool dosomething(int, int, string, bool);
vector < string > orientations= {"UF"};
vector < string > rotations{" "};
bool firstdo=1;
string usedrotation;
string usedorientation;
void customparser(void);
bool executecommand(string comma, int nom, vector < string > oris, vector < string > rots);
void cubeSet(vector < __int64 > setter);
vector < __int64 > setter(5);
string moveReverse(string a);
vector < char > move2vec (string movesstring);
string vec2move ( vector < char >  movevec);
void solves12(int depth, int method, int step, int nom, vector < string > oris, vector < string > rots, int allowedmoves);
void analyze(int quantity, int prunedmethod, vector < string > orientations, vector < string > rotations);

void prunes12 (int depth, int method, int step, int allowedmoves);


void introWCA()
{
    cout << string(100, '\n') <<
         "      ooooo   ooooo       .o.       ooooooooo.     .oooooo.    .oooooo..o \n"
         "      `888'   `888'      .888.      `888   `Y88.  d8P'  `Y8b  d8P'    `Y8 \n"
         "       888     888      .88888.      888   .d88' 888          Y88bo.      \n"
         "       888ooooo888     .8' `888.     888ooo88P'  888           `\Y8888o.  \n"
         "       888     888    .88ooo8888.    888`88b.    888               `\Y88b \n"
         "       888     888   .8'     `888.   888  `88b.  `88b    ooo  oo     .d8P \n"
         "      o888o   o888o o88o     o8888o o888o  o888o  `Y8bood8P'  `8888888P' \n\n\n"
         "                       Here's A Replacement Cube Solver\n\n\n\n\n\n\n";
}
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

string ToString(size_t val)
{
    stringstream stream;
    stream << val;
    return stream.str();
}

string replaceStrChar(string str, const string& replace, char ch)
{

    size_t found = str.find_first_of(replace);

    while (found != string::npos)
    {
        str[found] = ch;
        found = str.find_first_of(replace, found+1);
    }

    return str; // return our new string.
}

void putCursor()
{
    cout<<"HARCS>> ";
}
void showHelpWCA()
{
    cout <<"\n   info\t\tdisplay version information\n"
         "   apply * #\tapply a scramble/moves to current cube, ending with #\n\t\t   (ex: apply R U2 B' L ... #)\n"
         "   set * * * * * # set a scrambled state via hex input; order EP EO CP CO CN\n"
         "   revert\trevert cube to solved state\n"
         "   number *\tset desired count of substep solutions (default: 3)\n"
         "   state\tshow current hexadecimal cubestate representation\n"
         "   view\t\topen current cube on alg.cubing.net\n"
         "   print\tprint applied sequences on current cube\n"
         "   save\t\tappend applied sequences to text file in directory\n"
         "   style * #\tset solution orientations \n\t\t   (ex: style UF DB #) (default: UF) CN and DCN are options\n"
         "   cfop\t\tprunes for cross (D) and xcross (D,DFR)\n"
         "   petrus\tprunes for 2x2x2 (DLB), 3x2x2 (DL), eo, f2l, and zbll\n"
         "   roux\t\tprunes for fs (DLB), fb (DL), sb (DR), cmll, and lse\n"
         "   zz\t\tprunes for eoline (D), eo3x2x2 (DL), lb, rb, and zbll\n"
         "   custom\tprunes for the method defined in custom.txt\n"
         "   all\t\tsolves entire cube with set method in single orientation\n"
         "   analyze *\tanalyzes desired number of solves with set method\n\n"
         "   To solve a substep for a pruned method, type the step, as written above.\n"
         "   To apply a generated substep solution, type the number next to it.\n\n"
         ;

}
int getInputWCA(bool CLI, string commands)
{

    while (1)
    {
        if (CLI)
        {
            inputWCA=commands;
        }
        else
        {
            firstWordWCA=0;
            cout<<"HARCS>> ";
            getline(cin, inputWCA);
        }
        string buf;
        stringstream ss(inputWCA);
        while (ss >> buf)
        {
            rlutil::setColor(rlutil::YELLOW);
            bool notrecognized=1;
            if (buf=="test")
            {
                std::cout<<"\n   Blessed are they which are persecuted\n   for righteousness' sake, for theirs\n   is the kingdom of heaven.\t(Mt 5:10)\n\n";
                firstWordWCA=1;
            }
            if (buf=="gullible")
            {
                std::cout<<"\n   3.141592653\n\n";
                firstWordWCA=1;
            }
            if (buf=="custom")
            {
                firstWordWCA=1;
                if (prunedmethod==4)
                {
                    cout<<"\n   custom method already loaded.\n\n";
                }
                else
                {
                    prunedmethod=4;
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }

                    customparser();
                    prunedyet=1;
                    prunedmethod=4;
                }
            }

            if (buf=="petrus")
            {
                auto t1 = Clock::now();
                firstWordWCA=1;
                if (prunedmethod==1)
                {
                    cout<<"\n   petrus already loaded.\n\n";
                }
                else
                {
                    prunedmethod=1;
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    cout<<"\n   Loaded 2x2x2,";
                    prunes12(4,1,0,1);
                    cout<<" 3x2x2,";
                    prunes12(5,1,1,1);
                    cout<<" eo,";
                    prunes12(4,1,2,6);
                    cout<<" f2l,";
                    prunes12(7,1,3,4);
                    cout<<" zbll,";
                    prunes12(1,1,4,8);
                    auto t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=1;
                }

            }


            if (buf=="cfop")
            {
                auto t1 = Clock::now();
                firstWordWCA=1;
                if (prunedmethod==0)
                {
                    cout<<"\n   cfop already loaded.\n\n";
                }
                else
                {
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    cout<<"\n   Loaded cross,";
                    prunes12(4,0,0,1);
                    cout<<" xcross,";
                    prunes12(5,0,1,1);
                    //cout<<" pairs,";
                    //prunes12(0,0,2,666);
                    auto t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=0;
                }
            }

            if (buf=="zz")
            {
                auto t1 = Clock::now();
                firstWordWCA=1;
                if (prunedmethod==3)
                {
                    cout<<"\n   zz already loaded.\n\n";
                }
                else
                {
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    cout<<"\n   Loaded eoline,";
                    prunes12(4,3,0,1);
                    cout<<" eo3x2x2,";
                    prunes12(5,3,1,1);
                    cout<<" lb,";
                    prunes12(6,3,2,5);
                    cout<<" rb,";
                    prunes12(7,3,3,4);
                    cout<<" zbll,";
                    prunes12(1,3,4,8);
                    auto t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=3;
                }

            }

            if (buf=="roux")
            {
                auto t1 = Clock::now();
                firstWordWCA=1;
                if (prunedmethod==2)
                {
                    cout<<"\n   roux already loaded.\n\n";
                }
                else
                {
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    cout<<"\n   Loaded fs,";
                    prunes12(4,2,3,2);
                    cout<<" fb,";
                    prunes12(4,2,0,2);
                    cout<<" sb,";
                    prunes12(6,2,1,3);
                    cout<<" cmll,";
                    prunes12(1,2,4,8);
                    cout<<" lse,";
                    prunes12(10,2,5,7);
                    auto t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=2;
                }
            }

            if (prunedmethod==4)
            {
                notrecognized=executecommand(buf,number,orientations,rotations);
            }

            else
            {
                if (buf=="all")
                {
                    oldnumber=number;
                    number=1;
                    firstWordWCA=1;
                    if (prunedmethod!=1&&prunedmethod!=2&&prunedmethod!=3)
                    {
                        cout<<"\n   must be pruned for petrus/roux/zz/custom\n\n";
                    }
                    else if (orientations.size()==1)
                    {
                        auto t1 = Clock::now();
                        if (prunedmethod==1) // petrus
                        {
                            solves12(6,1,1,number,orientations,rotations,1);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(5,1,2,number,orientations,rotations,6);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(7,1,3,number,orientations,rotations,4);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(1,1,4,number,orientations,rotations,8);
                            firstdo=dosomething(0,1," ",firstdo);
                            auto t2 = Clock::now();
                            cout<<"\n   stepwise-optimal petrus solution applied in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n\n";
                        }

                        if (prunedmethod==2) // roux
                        {
                            solves12(5,2,0,number,orientations,rotations,2);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(6,2,1,number,orientations,rotations,3);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(1,2,4,number,orientations,rotations,8);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(10,2,5,number,orientations,rotations,7);
                            firstdo=dosomething(0,1," ",firstdo);
                            auto t2 = Clock::now();
                            cout<<"\n   stepwise-optimal roux solution applied in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n\n";
                        }

                        if (prunedmethod==3) // zz
                        {
                            solves12(5,3,0,number,orientations,rotations,1);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(6,3,2,number,orientations,rotations,5);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(7,3,3,number,orientations,rotations,4);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(1,3,4,number,orientations,rotations,8);
                            firstdo=dosomething(0,1," ",firstdo);
                            auto t2 = Clock::now();
                            cout<<"\n   stepwise-optimal zz solution applied in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n\n";
                        }

                    }
                    else
                    {
                        cout<<"\n   specify a single orientation\n\n";
                    }
                    number=oldnumber;
                }



                if (buf=="eoline")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,3,0,number,orientations,rotations,1);
                    }
                }

                if (buf=="eo3x2x2")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,3,1,number,orientations,rotations,1);
                    }
                }

                if (buf=="lb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,3,2,number,orientations,rotations,5);
                    }
                }

                if (buf=="rb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(7,3,3,number,orientations,rotations,4);
                    }
                }

                if (buf=="zbll")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3 && prunedmethod!=1)
                    {
                        cout<<"\n   neither zz nor petrus is currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(1,1,4,number,orientations,rotations,8);
                    }
                }

                if (buf=="fs")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(4,2,3,number,orientations,rotations,2);
                    }
                }


                if (buf=="fb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,2,0,number,orientations,rotations,2);
                    }
                }

                if (buf=="sb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,2,1,number,orientations,rotations,3);
                    }
                }


                if (buf=="cmll")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(1,2,4,number,orientations,rotations,8);
                    }
                }


                if (buf=="lse")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(10,2,5,number,orientations,rotations,7);
                    }
                }


                if (buf=="cross")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=0)
                    {
                        cout<<"\n   cfop is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,0,0,number,orientations,rotations,1);
                    }
                }

                if (buf=="xcross")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=0)
                    {
                        cout<<"\n   cfop is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,0,1,number,orientations,rotations,1);
                    }
                }

                if (buf=="2x2x2")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,1,0,number,orientations,rotations,1);
                    }
                }

                if (buf=="3x2x2")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,1,1,number,orientations,rotations,1);
                    }
                }

                if (buf=="eo")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,1,2,number,orientations,rotations,6);
                    }
                }

                if (buf=="f2l")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(7,1,3,number,orientations,rotations,4);
                    }
                }

            }
            if (buf=="illuminati")
            {
                firstWordWCA=1;
                cout<<"\n   Confirmed.\n\n";
            }
            if (buf=="help")
            {
                firstWordWCA=1;
                showHelpWCA();
            }
            else if (buf=="cls")
            {
                firstWordWCA=1;
                cout << string(400, '\n');
            }
            else if (buf=="info")
            {
                firstWordWCA=1;
                cout << "\n   HARCS v0.9 : 05-28-2017 : Matt DiPalma : USA\n\n";
            }
            else if (buf=="number")
            {
                firstWordWCA=1;
                isDepth=1;
            }
            else if (buf=="analyze")
            {
                firstWordWCA=1;
                isAnalyze=1;
            }
            else if (buf=="revert")
            {
                firstWordWCA=1;
                scramble=cubeRevert(1);
                usedrotation.clear();
                firstdo=1;
                asetstate=0;
                cout << "\n   Reset to solved.\n\n";
            }
            else if (buf=="state")
            {
                firstWordWCA=1;
                showCube();
            }
            else if (buf=="print")
            {
                firstWordWCA=1;
                if (!wherretf.empty())
                {
                    for (int j=0; j<wherretf.size(); j++)
                    {
                        if (asetstate && j==0)
                        {
                            cout<<std::hex<<"\n   init state:\n   EP: 0x"<<EPo<<"\n   EO: 0x"<<EOo<<"\n   CP: 0x"<<CPo<<"\n   CO: 0x"<<COo<<"\n   CN: 0x"<<CNo<<"\n";
                        }
                        cout <<std::dec<< "\n   "<<wherretf[j][0]<<" // "<<wherretf[j][1];
                        if (j>1 || (j>0 && asetstate))
                        {
                            cout<<" ("<<countWords(wherretf[j][0])<<")";
                        }
                        cout<<endl;
                    }
                    cout<<endl;
                }
                else
                {
                    cout<<"\n   no sequences applied yet\n\n";
                }
            }

            else if (buf=="save")
            {
                firstWordWCA=1;
                ofstream outfile;
                outfile.open("solutions.txt",ios_base::app);
                if (!wherretf.empty())
                {
                    //outfile<<endl;
                    for (int j=0; j<wherretf.size(); j++)
                    {
                        if (asetstate && j==0)
                        {
                            outfile<<std::hex<<"\ninit state: 0x"<<EPo<<" 0x"<<EOo<<" 0x"<<CPo<<" 0x"<<COo<<" 0x"<<CNo<<std::dec;
                        }
                        outfile << "\n"<<wherretf[j][0]<<" // "<<wherretf[j][1];
                        if (j>1 || (j>0 && asetstate))
                        {
                            outfile<<" ("<<countWords(wherretf[j][0])<<")";
                        }
                        // outfile<<endl;
                    }
                    outfile<<"\n---"<<endl;
                    cout<<"\n   sequences saved to solutions.txt\n\n";
                }
                else
                {
                    cout<<"\n   no sequences applied yet\n\n";
                }
                outfile.close();
            }


            else if (buf=="view")
            {
                firstWordWCA=1;
                if (!wherretf.empty())
                {
                    string url="https://alg.cubing.net?";
                    string useit;
                    if (!asetstate)
                    {
                        for (int j=0; j<wherretf.size(); j++)
                        {
                            useit=replaceStrChar(wherretf[j][0], "'", '-');
                            useit=replaceStrChar(useit, " ", '_');
                            if (j==0)
                            {
                                url+=("setup="+useit);
                            }
                            else if (j==1)
                            {
                                url+=("&alg="+useit+"_%2F%2F_"+wherretf[j][1]);
                            }
                            else if (j>1)
                            {
                                url+=("%0A"+useit+"_%2F%2F_"+wherretf[j][1]+"_("+ToString(countWords(wherretf[j][0]))+")");
                            }
                        }
                    }
                    else if (asetstate)
                    {
                        for (int j=0; j<wherretf.size(); j++)
                        {
                            if (j==0)
                            {
                                useit="";
                                for (int k=0; k<wherretf.size(); k++)
                                {
                                    useit+=(wherretf[k][0]+" ");
                                }
                                useit=moveReverse(useit);
                                useit=replaceStrChar(useit, "'", '-');
                                useit=replaceStrChar(useit, " ", '_');
                                url+=("setup="+useit);
                                useit=replaceStrChar(wherretf[j][0], "'", '-');
                                useit=replaceStrChar(useit, " ", '_');
                                url+=("&alg="+useit+"_%2F%2F_"+wherretf[j][1]);
                            }
                            else if (j>0)
                            {
                                useit=replaceStrChar(wherretf[j][0], "'", '-');
                                useit=replaceStrChar(useit, " ", '_');
                                url+=("%0A"+useit+"_%2F%2F_"+wherretf[j][1]+"_("+ToString(countWords(wherretf[j][0]))+")");
                            }
                        }
                    }



                    cout<<"\n   opening alg.cubing.net in default browser\n\n";
                    ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );

                }

                else
                {
                    cout<<"\n   no sequences applied yet\n\n";
                }
            }


            else if (buf == "style")
            {
                firstWordWCA=1;
                isCheck=1;
                orientations.clear();
                rotations.clear();

            }
            else if (isCheck)
            {
                if (buf=="UB")
                {
                    orientations.push_back("UB");
                    rotations.push_back("y2");
                }
                else if (buf=="UR")
                {
                    orientations.push_back("UR");
                    rotations.push_back("y'");
                }
                else if (buf=="UF")
                {
                    orientations.push_back("UF");
                    rotations.push_back(" ");
                }
                else if (buf=="UL")
                {
                    orientations.push_back("UL");
                    rotations.push_back("y");
                }
                else if (buf=="BL")
                {
                    orientations.push_back("BL");
                    rotations.push_back("z' y");
                }
                else if (buf=="BR")
                {
                    orientations.push_back("BR");
                    rotations.push_back("z y'");
                }
                else if (buf=="FR")
                {
                    orientations.push_back("FR");
                    rotations.push_back("z' y'");
                }
                else if (buf=="FL")
                {
                    orientations.push_back("FL");
                    rotations.push_back("z y");
                }
                else if (buf=="DB")
                {
                    orientations.push_back("DB");
                    rotations.push_back("x2");
                }
                else if (buf=="DR")
                {
                    orientations.push_back("DR");
                    rotations.push_back("y z2");
                }
                else if (buf=="DF")
                {
                    orientations.push_back("DF");
                    rotations.push_back("z2");
                }
                else if (buf=="DL")
                {
                    orientations.push_back("DL");
                    rotations.push_back("y' z2");
                }
                else if (buf=="BU")
                {
                    orientations.push_back("BU");
                    rotations.push_back("x");
                }
                else if (buf=="RU")
                {
                    orientations.push_back("RU");
                    rotations.push_back("x y");
                }
                else if (buf=="FU")
                {
                    orientations.push_back("FU");
                    rotations.push_back("x y2");
                }
                else if (buf=="LU")
                {
                    orientations.push_back("LU");
                    rotations.push_back("x y'");
                }
                else if (buf=="LB")
                {
                    orientations.push_back("LB");
                    rotations.push_back("z y2");
                }
                else if (buf=="RB")
                {
                    orientations.push_back("RB");
                    rotations.push_back("z' y2");
                }
                else if (buf=="RF")
                {
                    orientations.push_back("RF");
                    rotations.push_back("z");
                }
                else if (buf=="LF")
                {
                    orientations.push_back("LF");
                    rotations.push_back("z'");
                }
                else if (buf=="BD")
                {
                    orientations.push_back("BD");
                    rotations.push_back("x' y2");
                }
                else if (buf=="RD")
                {
                    orientations.push_back("RD");
                    rotations.push_back("x' y'");
                }
                else if (buf=="FD")
                {
                    orientations.push_back("FD");
                    rotations.push_back("x'");
                }
                else if (buf=="LD")
                {
                    orientations.push_back("LD");
                    rotations.push_back("x' y");
                }

                else if (buf=="DCN")
                {
                    orientations.push_back("UB");
                    rotations.push_back("y2");

                    orientations.push_back("UR");
                    rotations.push_back("y'");

                    orientations.push_back("UF");
                    rotations.push_back("");

                    orientations.push_back("UL");
                    rotations.push_back("y");

                    orientations.push_back("DB");
                    rotations.push_back("x2");

                    orientations.push_back("DR");
                    rotations.push_back("y z2");

                    orientations.push_back("DF");
                    rotations.push_back("z2");

                    orientations.push_back("DL");
                    rotations.push_back("y' z2");
                }

                else if (buf=="CN")
                {
                    orientations.push_back("UB");
                    rotations.push_back("y2");

                    orientations.push_back("UR");
                    rotations.push_back("y'");

                    orientations.push_back("UF");
                    rotations.push_back(" ");

                    orientations.push_back("UL");
                    rotations.push_back("y");

                    orientations.push_back("BL");
                    rotations.push_back("z' y");

                    orientations.push_back("BR");
                    rotations.push_back("z y'");

                    orientations.push_back("FR");
                    rotations.push_back("z' y'");

                    orientations.push_back("FL");
                    rotations.push_back("z y");

                    orientations.push_back("DB");
                    rotations.push_back("x2");

                    orientations.push_back("DR");
                    rotations.push_back("y z2");

                    orientations.push_back("DF");
                    rotations.push_back("z2");

                    orientations.push_back("DL");
                    rotations.push_back("y' z2");

                    orientations.push_back("BU");
                    rotations.push_back("x");

                    orientations.push_back("RU");
                    rotations.push_back("x y");

                    orientations.push_back("FU");
                    rotations.push_back("x y2");

                    orientations.push_back("LU");
                    rotations.push_back("x y'");

                    orientations.push_back("LB");
                    rotations.push_back("z y2");

                    orientations.push_back("RB");
                    rotations.push_back("z' y2");

                    orientations.push_back("RF");
                    rotations.push_back("z");

                    orientations.push_back("LF");
                    rotations.push_back("z'");

                    orientations.push_back("BD");
                    rotations.push_back("x' y2");

                    orientations.push_back("RD");
                    rotations.push_back("x' y'");

                    orientations.push_back("FD");
                    rotations.push_back("x'");

                    orientations.push_back("LD");
                    rotations.push_back("x' y");
                }

                else if (buf=="#")
                {
                    cout<<"\n   orientations set to: ";
                    isCheck=0;
                    for (int i=0; i<orientations.size(); i++)
                    {
                        cout<<orientations[i]<<" ";
                    }
                    cout<<"\n\n";
                }
                else
                    cout << "\n   invalid orientation specified.\n\n";

            }

            else if (buf=="set")
            {
                isSet=1;
                cout << "\n   state set\n\n";
            }

            else if (buf=="apply")
            {
                isScramble2=1;
                cout << "\n   sequence applied\n\n";
            }
            else if (isDepth==1)
            {
                istringstream convert(buf);
                if ( (convert >> tempnumber) )
                {
                    number=tempnumber;
                    cout << "\n   max count set to: " << number << "\n\n";
                    isDepth=0;
                }
                else
                {
                    cout << "\n   invalid count specified; count remains: "<<number<<"\n\n";
                    isDepth=0;
                }

            }
            else if (isAnalyze==1)
            {
                istringstream convert(buf);
                if ( (convert >> tempnumber) )
                {
                    if (orientations.size()>1)
                    {
                        cout<<"\n   specify a single orientation\n\n";
                    }
                    else
                    {
                        analyze(tempnumber, prunedmethod, orientations, rotations);
                    }
                    isAnalyze=0;
                }
                else
                {
                    cout << "\n   invalid quantity for analysis\n\n";
                    isAnalyze=0;
                }
            }
        else if (isSet==1)
        {
            if (buf=="#")
            {
                if (isSet)
                {
                    isSet=0;
                    isSet2=0;
                    cubeSet(setter);
                    scramble="";
                    asetstate=1;
                    EPo=setter[0];
                    EOo=setter[1];
                    CPo=setter[2];
                    COo=setter[3];
                    CNo=setter[4];
                }
            }
            else
            {
                istringstream buffer(buf);
                __int64 value;
                buffer >> std::hex >> value;
                setter[isSet2]=value;
                isSet2++;
            }
        }

        else if (isScramble2==1)
        {
            if (buf=="#")
            {
                if (isScramble2)
                {
                    isScramble2=0;
                    dosomething(1,0,scramble,firstdo);
                    scramble="";
                }

            }
            else
            {
                //applyMove(buf);
                vector < char > tempmove=move2vec(buf);
                for (int i=0; i<tempmove.size(); i++)
                {
                    applyMove2(tempmove[i]);
                }
                scramble.append(buf);
                scramble.append(" ");
            }
        }
        else if (buf=="#")
        {

            if (isCheck)
            {
                cout<<"\n   orientations set to: ";
                isCheck=0;
                for (int i=0; i<orientations.size(); i++)
                {
                    cout<<orientations[i]<<" ";
                }
                cout<<"\n\n";
            }
        }
        else if (firstWordWCA==1)
        {
            firstWordWCA=0;
        }

        else if (is_number(buf))
        {
            firstdo=dosomething(0,atoi(buf.c_str())," ",firstdo);
        }

        else
        {
            if (notrecognized)
            {
                cout << "\n   command not recognized\n\n";
                rlutil::setColor(rlutil::WHITE);
                break;
            }
        }
    rlutil::setColor(rlutil::WHITE);
    }
    if (CLI)
    {
        break;
    }
}
return 0;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc > 1)
    {
        string asmb="";
        for (int j=1; j<argc; j++)
        {
            asmb=asmb+argv[j]+" ";
        }
        getInputWCA(1,asmb);
    }
    else
    {
        rlutil::setColor(rlutil::LIGHTRED);
        introWCA();
        rlutil::setColor(rlutil::WHITE);
        while (1)
        {
            getInputWCA(0,"");
        }
    }
    return 0;
}
