#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <sstream>
#include <chrono>
#include <ctype.h>
#include <iterator>
#include <fstream>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <typeinfo>
#include <stdio.h>
#include <regex>
#include "headers.h"
#include <boost/algorithm/string.hpp>
#include <numeric>

using namespace std;

__int64 EPs=0x123456789abc;
__int64 EOs=0x222222222222;
__int64 CPs=0x12345678;
__int64 COs=0x44444444;
__int64 CNs=0x123;
__int64 EP=EPs, EO=EOs, CP=CPs, CO=COs, CN=CNs;
vector < __int64 > slicemask;
vector < __int64 > slicers;
vector < int > shiftin;
__int64 EPb, EOb, CPb, COb, CNb, EPi, EOi, CPi, COi, CNi;
int temp=0;
vector < string > setups6gen;
vector < vector < char > > setups6gen2;
vector < string > solutionss1;
vector < vector < char > > solutionss12;
vector < string > moves;
vector < vector < char > > moveinsets = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,36,37,38},
    {0,1,2,6,7,8,18,19,20,36,37,38},
    {0,1,2,3,4,5,6,7,8},
    {0,1,2,3,4,5,6,7,8,9,10,11},
    {0,1,2,6,7,8,12,13,14,15,16,17},
    {0,1,2,18,19,20},
    {0,1,2},
    {0,1,2,3,4,5,18,19,20},
    {0,1,2,3,4,5,9,10,11}
};
__int64 maskEPs1;
__int64 maskEOs1;
__int64 maskCPs1;
__int64 maskCOs1;
__int64 maskCNs1=0xfff;
string currentstep;
vector < string > solutionsLog;
vector < string > solutionsList;
vector < string > rotationsLog;
vector < string > orientationsLog;
vector < vector < string > > wherretf;
vector <__int64> cpdictionary;
bool lbdone=0;
bool rbdone=0;
bool mirrorit=0;
bool stateset=0;
vector < string > customsteps(8);
vector < string > custommg(8);
vector < string > customall;
vector < vector < __int64 > > customdets(8, vector <__int64> (16)); // 12-16 are custom solved states
string algset;
bool veil=0;
bool noprune=0;
int foundsolutions=0;
void EOfixer(void);
void cleanScrambler(void);
void masks1(int, int);
string moveReverse(string);
void applyMove2(char);
typedef std::chrono::high_resolution_clock Clock;
vector <string> scramblesave;
int squares=0;
int nostep=0;
int nosteps=0;

string vec2move ( vector < char >  movevec)
{
    string outmoves="";
    for (int i=0; i<movevec.size(); i++)
    {
        if (movevec[i]==0) outmoves+="U ";
        else if (movevec[i]==1) outmoves+="U2 ";
        else if (movevec[i]==2) outmoves+="U' ";
        else if (movevec[i]==3) outmoves+="D ";
        else if (movevec[i]==4) outmoves+="D2 ";
        else if (movevec[i]==5) outmoves+="D' ";
        else if (movevec[i]==6) outmoves+="R ";
        else if (movevec[i]==7) outmoves+="R2 ";
        else if (movevec[i]==8) outmoves+="R' ";
        else if (movevec[i]==9) outmoves+="L ";
        else if (movevec[i]==10) outmoves+="L2 ";
        else if (movevec[i]==11) outmoves+="L' ";
        else if (movevec[i]==12) outmoves+="F ";
        else if (movevec[i]==13) outmoves+="F2 ";
        else if (movevec[i]==14) outmoves+="F' ";
        else if (movevec[i]==15) outmoves+="B ";
        else if (movevec[i]==16) outmoves+="B2 ";
        else if (movevec[i]==17) outmoves+="B' ";
        else if (movevec[i]==18) outmoves+="M ";
        else if (movevec[i]==19) outmoves+="M2 ";
        else if (movevec[i]==20) outmoves+="M' ";
        else if (movevec[i]==21) outmoves+="E ";
        else if (movevec[i]==22) outmoves+="E2 ";
        else if (movevec[i]==23) outmoves+="E' ";
        else if (movevec[i]==24) outmoves+="S ";
        else if (movevec[i]==25) outmoves+="S2 ";
        else if (movevec[i]==26) outmoves+="S' ";
        else if (movevec[i]==27) outmoves+="x ";
        else if (movevec[i]==28) outmoves+="x2 ";
        else if (movevec[i]==29) outmoves+="x' ";
        else if (movevec[i]==30) outmoves+="y ";
        else if (movevec[i]==31) outmoves+="y2 ";
        else if (movevec[i]==32) outmoves+="y' ";
        else if (movevec[i]==33) outmoves+="z ";
        else if (movevec[i]==34) outmoves+="z2 ";
        else if (movevec[i]==35) outmoves+="z' ";
        else if (movevec[i]==36) outmoves+="r ";
        else if (movevec[i]==37) outmoves+="r2 ";
        else if (movevec[i]==38) outmoves+="r' ";
        else if (movevec[i]==39) outmoves+="l ";
        else if (movevec[i]==40) outmoves+="l2 ";
        else if (movevec[i]==41) outmoves+="l' ";
        else if (movevec[i]==42) outmoves+="u ";
        else if (movevec[i]==43) outmoves+="u2 ";
        else if (movevec[i]==44) outmoves+="u' ";
        else if (movevec[i]==45) outmoves+="d ";
        else if (movevec[i]==46) outmoves+="d2 ";
        else if (movevec[i]==47) outmoves+="d' ";
        else if (movevec[i]==48) outmoves+="f ";
        else if (movevec[i]==49) outmoves+="f2 ";
        else if (movevec[i]==50) outmoves+="f' ";
        else if (movevec[i]==51) outmoves+="b ";
        else if (movevec[i]==52) outmoves+="b2 ";
        else if (movevec[i]==53) outmoves+="b' ";
    }
    return outmoves;
}

vector < char > move2vec (string movesstring)
{
    char j;
    vector < char > outmoves;
    string tuf;
    stringstream ss(movesstring);
    while (ss >> tuf)
    {
        if (tuf=="U") j=0;
        else if (tuf=="U2") j=1;
        else if (tuf=="U'") j=2;
        else if (tuf=="D") j=3;
        else if (tuf=="D2") j=4;
        else if (tuf=="D'") j=5;
        else if (tuf=="R") j=6;
        else if (tuf=="R2") j=7;
        else if (tuf=="R'") j=8;
        else if (tuf=="L") j=9;
        else if (tuf=="L2") j=10;
        else if (tuf=="L'") j=11;
        else if (tuf=="F") j=12;
        else if (tuf=="F2") j=13;
        else if (tuf=="F'") j=14;
        else if (tuf=="B") j=15;
        else if (tuf=="B2") j=16;
        else if (tuf=="B'") j=17;
        else if (tuf=="M") j=18;
        else if (tuf=="M2") j=19;
        else if (tuf=="M'") j=20;
        else if (tuf=="E") j=21;
        else if (tuf=="E2") j=22;
        else if (tuf=="E'") j=23;
        else if (tuf=="S") j=24;
        else if (tuf=="S2") j=25;
        else if (tuf=="S'") j=26;
        else if (tuf=="x") j=27;
        else if (tuf=="x2") j=28;
        else if (tuf=="x'") j=29;
        else if (tuf=="y") j=30;
        else if (tuf=="y2") j=31;
        else if (tuf=="y'") j=32;
        else if (tuf=="z") j=33;
        else if (tuf=="z2") j=34;
        else if (tuf=="z'") j=35;
        else if (tuf=="r") j=36;
        else if (tuf=="r2") j=37;
        else if (tuf=="r'") j=38;
        else if (tuf=="l") j=39;
        else if (tuf=="l2") j=40;
        else if (tuf=="l'") j=41;
        else if (tuf=="u") j=42;
        else if (tuf=="u2") j=43;
        else if (tuf=="u'") j=44;
        else if (tuf=="d") j=45;
        else if (tuf=="d2") j=46;
        else if (tuf=="d'") j=47;
        else if (tuf=="f") j=48;
        else if (tuf=="f2") j=49;
        else if (tuf=="f'") j=50;
        else if (tuf=="b") j=51;
        else if (tuf=="b2") j=52;
        else if (tuf=="b'") j=53;
        outmoves.push_back(j);
    }
    return outmoves;
}

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

__int64 hexparse(int eoc, __int64 toparse, __int64 thismask, string orr)
{
    //eoc=1 edges, eoc=2 corners, eoc=3 centers
    __int64 accumask=0x0000000000000000;
    __int64 A=0x0000000000000000;
    int hm=0;
    if (eoc==1)
    {
        hm=44;
        A=EPs&thismask;
    }
    else if (eoc==2)
    {
        hm=28;
        A=CPs&thismask;
    }
    else if (eoc==3)
    {
        hm=8;
        A=CNs&thismask;
    }
    for (int i=0; i<=hm; i=i+4)
    {
        if ((A>>i)&0xf)
        {
            for (int j=0; j<=hm; j=j+4)
            {
                if (((A>>i)&0xf)==((toparse>>j)&0xf))
                {
                    accumask=((((__int64)0xf)<<j))+accumask;
                }
            }
        }
    }
    return accumask;
}

void algparser(vector < char > str, vector < vector < char > > &thisone, int whichset)
{
    string pullin;
    if (whichset==2) //CMLL, roux is 2
    {
        ifstream infile;
        infile.open("CMLL.txt");
        while(getline(infile,pullin))
        {
            bool toggleme=0;
            string tuf;
            string part1="";
            stringstream ss(pullin);
            while (ss >> tuf)
            {
                if (!toggleme && (tuf!="//"))
                {
                    part1+=(tuf+" ");
                }
                if (tuf=="//")
                {
                    toggleme=1;
                }
            }
            vector < char > tempmoves=move2vec(moveReverse(part1));
            for (int k=0; k<str.size(); k++) tempmoves.insert(tempmoves.begin(),str[k]);
            thisone.push_back(tempmoves);
        }
        infile.close();
    }

    if (whichset==1 || whichset==3) //petrus,zz
    {
        ifstream infile;
        infile.open("ZBLL.txt");
        while(getline(infile,pullin))
        {
            bool toggleme=0;
            string tuf;
            string part1="";
            stringstream ss(pullin);
            while (ss >> tuf)
            {
                if (!toggleme && (tuf!="//"))
                {
                    part1+=(tuf+" ");
                }

                if (tuf=="//")
                {
                    toggleme=1;
                }
            }
            vector < char > tempmoves=move2vec(moveReverse(part1));
            for (int k=0; k<str.size(); k++) tempmoves.insert(tempmoves.begin(),str[k]);
            thisone.push_back(tempmoves);
        }
        infile.close();
    }


    if (whichset==4) //custom
    {
        ifstream infile;
        infile.open(algset);
        while(getline(infile,pullin))
        {
            bool toggleme=0;
            string tuf;
            string part1="";
            stringstream ss(pullin);
            while (ss >> tuf)
            {
                if (!toggleme && (tuf!="//"))
                {
                    part1+=(tuf+" ");
                }

                if (tuf=="//")
                {
                    toggleme=1;
                }
            }
            vector < char > tempmoves=move2vec(moveReverse(part1));
            for (int k=0; k<str.size(); k++) tempmoves.insert(tempmoves.begin(),str[k]);
            thisone.push_back(tempmoves);
        }
        infile.close();
    }



    return;
}

bool dosomething(int isscramble, int whatthing, string scr, bool firstdo)
{
    if (isscramble)
    {
        if (wherretf.size()<1)
        {
            vector <string> tempcolumn= {trim(scr),"scramble"};
            wherretf.push_back(tempcolumn);
            usedrotation.clear();
            usedorientation.clear();
        }
        else
        {
            vector <string> tempcolumn= {trim(scr),"moves"};
            wherretf.push_back(tempcolumn);
        }
    }
    else
    {
        if (whatthing>solutionsLog.size()) //valid number
        {
            cout<<"\n   no such solution generated\n\n";
        }
        else
        {
            if (firstdo)
            {
                vector <string> tempcolumn= {trim(rotationsLog[whatthing-1]),"inspection"};
                wherretf.push_back(tempcolumn);
                usedrotation=rotationsLog[whatthing-1];
                usedorientation=orientationsLog[whatthing-1];
            }



            if (currentstep=="lb" && !mirrorit && !rbdone)
            {
                lbdone=1;
                //cout<<"lbdone1";
                currentstep="lb";//
            }
            else if (currentstep=="lb" && mirrorit && !lbdone)
            {
                rbdone=1;
                //cout<<"rbdone1";
                currentstep="rb";//
            }
            else if (currentstep=="rb" && !mirrorit && lbdone)
            {
                rbdone=1;
                //cout<<"rbdone2";
                currentstep="rb";//
            }
            else if (currentstep=="rb" && mirrorit && rbdone)
            {
                lbdone=1;
                //cout<<"lbdone2";
                currentstep="lb";//
            }


            vector <string> tempcolumn= {trim(solutionsLog[whatthing-1]),currentstep};
            wherretf.push_back(tempcolumn);
            cout<<"\n   "<<currentstep<<" #"<<whatthing<<" applied\n\n";


            firstdo=0;

            if (stateset)
            {
                EP=EPi;
                EO=EOi;
                CP=CPi;
                CO=COi;
                CN=CNi;
                vector <char> tempmoves=move2vec(trim(solutionsLog[whatthing-1]));
                for (int ij=0; ij<tempmoves.size(); ij++)
                {
                    applyMove2(tempmoves[ij]);
                }
                EPi=EP;
                EOi=EO;
                CPi=CP;
                COi=CO;
                CNi=CN;
            }
        }

    }
    cleanScrambler();
    return firstdo;
}


string remove_last_word_if(string sentence)
{
    sentence=trim(sentence);

    size_t index = sentence.find_last_of(" ");

    //string lastun=sentence.substr(index+1, sentence.length());
    if (sentence[index+1]=='U')
    {
        sentence.erase(sentence.begin()+index+1,sentence.end());
    }

    return sentence;

    //if (string::npos != pos) sentence.erase(pos, word.length());

    return sentence;
}


template <typename T>
string NumberToString(T pNumber)
{
    ostringstream oOStrStream;
    oOStrStream << pNumber;
    return oOStrStream.str();
}

size_t countWords(std::string s)
{
    string tuf;
    string fin;
    size_t out=0;
    stringstream ss(s);
    while (ss >> tuf)
    {
        if ((tuf[0]!='x')&&(tuf[0]!='y')&&(tuf[0]!='z'))
        {
            out++;
        }
    }
    return out;

    //  return s.empty() ? 0 : std::count_if(std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))), std::unique(s.begin(), s.end()), std::ptr_fun<int, int>(std::isspace)) + !std::isspace(*s.rbegin());
}

string cubeRevert(bool killscrtoo)
{
    if (killscrtoo)
    {
        wherretf.clear();
        lbdone=0;
        rbdone=0;
        stateset=0;
    }
    EP=EPs;
    EO=EOs;
    CP=CPs;
    CO=COs;
    CN=CNs;

    return "";
}


void cubeSet(vector < __int64 > setter)
{
    wherretf.clear();
    lbdone=0;
    rbdone=0;
    stateset=1;
    EPi=setter[0];
    EOi=setter[1];
    CPi=setter[2];
    COi=setter[3];
    CNi=setter[4];
    EP=setter[0];
    EO=setter[1];
    CP=setter[2];
    CO=setter[3];
    CN=setter[4];
    return;
}


void showCube()
{
    if (!stateset)
    {
        cout << "\n   EP: 0x" <<std::hex<< EP << "\n"
             "   EO: 0x" << EO << "\n"
             "   CP: 0x" << CP << "\n"
             "   CO: 0x" << CO << "\n"
             "   CN: 0x" << CN << "\n\n";
    }
    else if (stateset)
    {
        cout << "\n   EP: 0x" <<std::hex<< EPi << "\n"
             "   EO: 0x" << EOi << "\n"
             "   CP: 0x" << CPi << "\n"
             "   CO: 0x" << COi << "\n"
             "   CN: 0x" << CNi << "\n\n";
    }
    std::dec;
    return;
}


void applyMove2(char themove)
{
    // 0 1 2 = U U2 U'
    // 3 4 5 = D
    // 6 7 8 = R
    // 9 10 11 = L
    // 12 13 14 = F
    // 15 16 17 = B
    // 18 19 20 = M
    // 21 22 23 = E
    // 24 25 26 = S
    // 27 28 29 = x
    // 30 31 32 = y
    // 33 34 35 = z
    // 36 37 38 = r
    // 39 40 41 = l
    // 42 43 44 = u
    // 45 46 47 = d
    // 48 49 50 = f
    // 51 52 53 = b
    switch (themove)
    {
    case 0:
        EP=(EP&0x0000ffffffff)|((EP&0xfff000000000)>>4)|((EP&0x000f00000000)<<12);
        EO=(EO&0x0000ffffffff)|((EO&0xfff000000000)>>4)|((EO&0x000f00000000)<<12);
        CP=(CP&0x0000ffff)|((CP&0xfff00000)>>4)|((CP&0x000f0000)<<12);
        CO=(CO&0x0000ffff)|((CO&0xfff00000)>>4)|((CO&0x000f0000)<<12);
        break;
    case 1:
        EP=(EP&0x0000ffffffff)|((EP&0xff0000000000)>>8)|((EP&0x00ff00000000)<<8);
        EO=(EO&0x0000ffffffff)|((EO&0xff0000000000)>>8)|((EO&0x00ff00000000)<<8);
        CP=(CP&0x0000ffff)|((CP&0xff000000)>>8)|((CP&0x00ff0000)<<8);
        CO=(CO&0x0000ffff)|((CO&0xff000000)>>8)|((CO&0x00ff0000)<<8);
        break;
    case 2:
        EP=(EP&0x0000ffffffff)|((EP&0x0fff00000000)<<4)|((EP&0xf00000000000)>>12);
        EO=(EO&0x0000ffffffff)|((EO&0x0fff00000000)<<4)|((EO&0xf00000000000)>>12);
        CP=(CP&0x0000ffff)|((CP&0x0fff0000)<<4)|((CP&0xf0000000)>>12);
        CO=(CO&0x0000ffff)|((CO&0x0fff0000)<<4)|((CO&0xf0000000)>>12);
        break;
    case 3:
        EP=(EP&0xffffffff0000)|((EP&0x000000000fff)<<4)|((EP&0x00000000f000)>>12);
        EO=(EO&0xffffffff0000)|((EO&0x000000000fff)<<4)|((EO&0x00000000f000)>>12);
        CP=(CP&0xffff0000)|((CP&0x00000fff)<<4)|((CP&0x0000f000)>>12);
        CO=(CO&0xffff0000)|((CO&0x00000fff)<<4)|((CO&0x0000f000)>>12);
        break;
    case 4:
        EP=(EP&0xffffffff0000)|((EP&0x0000000000ff)<<8)|((EP&0x00000000ff00)>>8);
        EO=(EO&0xffffffff0000)|((EO&0x0000000000ff)<<8)|((EO&0x00000000ff00)>>8);
        CP=(CP&0xffff0000)|((CP&0x000000ff)<<8)|((CP&0x0000ff00)>>8);
        CO=(CO&0xffff0000)|((CO&0x000000ff)<<8)|((CO&0x0000ff00)>>8);
        break;
    case 5:
        EP=(EP&0xffffffff0000)|((EP&0x00000000fff0)>>4)|((EP&0x00000000000f)<<12);
        EO=(EO&0xffffffff0000)|((EO&0x00000000fff0)>>4)|((EO&0x00000000000f)<<12);
        CP=(CP&0xffff0000)|((CP&0x0000fff0)>>4)|((CP&0x0000000f)<<12);
        CO=(CO&0xffff0000)|((CO&0x0000fff0)>>4)|((CO&0x0000000f)<<12);
        break;
    case 6:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f000f000000)>>16)|((EP&0x000000f00000)<<20)|((EP&0x000000000f00)<<12);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f000f000000)>>16)|((EO&0x000000f00000)<<20)|((EO&0x000000000f00)<<12);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>16)|((CP&0x00f00000)<<4)|((CP&0x00000f00)>>4)|((CP&0x000000f0)<<16);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>16)|((CO&0x00f00000)<<4)|((CO&0x00000f00)>>4)|((CO&0x000000f0)<<16);
        CO+=0x01100110;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00100100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 7:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f0000000000)>>32)|((EP&0x000000f00000)<<4)|((EP&0x00000f000000)>>4)|((EP&0x000000000f00)<<32);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f0000000000)>>32)|((EO&0x000000f00000)<<4)|((EO&0x00000f000000)>>4)|((EO&0x000000000f00)<<32);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>20)|((CP&0x00f00000)>>12)|((CP&0x00000f00)<<12)|((CP&0x000000f0)<<20);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>20)|((CO&0x00f00000)>>12)|((CO&0x00000f00)<<12)|((CO&0x000000f0)<<20);
        break;
    case 8:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f0000000000)>>20)|((EP&0x000000f00000)>>12)|((EP&0x00000f000000)<<16)|((EP&0x000000000f00)<<16);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f0000000000)>>20)|((EO&0x000000f00000)>>12)|((EO&0x00000f000000)<<16)|((EO&0x000000000f00)<<16);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>4)|((CP&0x00f00000)>>16)|((CP&0x00000f00)<<16)|((CP&0x000000f0)<<4);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>4)|((CO&0x00f00000)>>16)|((CO&0x00000f00)<<16)|((CO&0x000000f0)<<4);
        CO+=0x01100110;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00100100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 9:
        EP=(EP&0xfff00ff0fff0)|((EP&0x000f000f0000)>>16)|((EP&0x0000f0000000)<<4)|((EP&0x00000000000f)<<28);
        EO=(EO&0xfff00ff0fff0)|((EO&0x000f000f0000)>>16)|((EO&0x0000f0000000)<<4)|((EO&0x00000000000f)<<28);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>12)|((CP&0x000f0000)>>16)|((CP&0x0000f000)<<16)|((CP&0x0000000f)<<12);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>12)|((CO&0x000f0000)>>16)|((CO&0x0000f000)<<16)|((CO&0x0000000f)<<12);
        CO+=0x10011001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x10000001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 10:
        EP=(EP&0xfff00ff0fff0)|((EP&0x000f00000000)>>32)|((EP&0x0000f0000000)>>12)|((EP&0x00000000000f)<<32)|((EP&0x0000000f0000)<<12);
        EO=(EO&0xfff00ff0fff0)|((EO&0x000f00000000)>>32)|((EO&0x0000f0000000)>>12)|((EO&0x00000000000f)<<32)|((EO&0x0000000f0000)<<12);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>28)|((CP&0x000f0000)>>4)|((CP&0x0000f000)<<4)|((CP&0x0000000f)<<28);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>28)|((CO&0x000f0000)>>4)|((CO&0x0000f000)<<4)|((CO&0x0000000f)<<28);
        break;
    case 11:
        EP=(EP&0xfff00ff0fff0)|((EP&0x0000000f000f)<<16)|((EP&0x0000f0000000)>>28)|((EP&0x000f00000000)>>4);
        EO=(EO&0xfff00ff0fff0)|((EO&0x0000000f000f)<<16)|((EO&0x0000f0000000)>>28)|((EO&0x000f00000000)>>4);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>16)|((CP&0x000f0000)<<12)|((CP&0x0000f000)>>12)|((CP&0x0000000f)<<16);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>16)|((CO&0x000f0000)<<12)|((CO&0x0000f000)>>12)|((CO&0x0000000f)<<16);
        CO+=0x10011001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x10000001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 12:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000f00000)>>16)|((EP&0x0000000f0000)<<20)|((EP&0x0000000000f0)<<12);
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000f00000)>>16)|((EO&0x0000000f0000)<<20)|((EO&0x0000000000f0)<<12);
        EO=EO^0x001000110010; //1
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>16)|((CP&0x000f0000)<<4)|((CP&0x000000f0)>>4)|((CP&0x0000000f)<<16);
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>16)|((CO&0x000f0000)<<4)|((CO&0x000000f0)>>4)|((CO&0x0000000f)<<16);
        CO+=0x00110011;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00010010;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 13:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000000000)>>32)|((EP&0x0000000f0000)<<4)|((EP&0x0000000000f0)<<32)|((EP&0x000000f00000)>>4);
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000000000)>>32)|((EO&0x0000000f0000)<<4)|((EO&0x0000000000f0)<<32)|((EO&0x000000f00000)>>4);
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>20)|((CP&0x000f0000)>>12)|((CP&0x000000f0)<<12)|((CP&0x0000000f)<<20);
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>20)|((CO&0x000f0000)>>12)|((CO&0x000000f0)<<12)|((CO&0x0000000f)<<20);
        break;
    case 14:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000000000)>>20)|((EP&0x0000000f0000)>>12)|((EP&0x000000f000f0)<<16); //10
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000000000)>>20)|((EO&0x0000000f0000)>>12)|((EO&0x000000f000f0)<<16);
        EO=EO^0x001000110010; //1
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>4)|((CP&0x000f0000)>>16)|((CP&0x000000f0)<<16)|((CP&0x0000000f)<<4); //13
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>4)|((CO&0x000f0000)>>16)|((CO&0x000000f0)<<16)|((CO&0x0000000f)<<4);

        CO+=0x00110011;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00010010;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 15:
        EP=(EP&0x0fff00ff0fff)|((EP&0xf000f0000000)>>16)|((EP&0x00000000f000)<<12)|((EP&0x00000f000000)<<20);
        EO=(EO&0x0fff00ff0fff)|((EO&0xf000f0000000)>>16)|((EO&0x00000000f000)<<12)|((EO&0x00000f000000)<<20);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>16)|((CP&0x0f000000)<<4)|((CP&0x0000f000)>>4)|((CP&0x00000f00)<<16);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>16)|((CO&0x0f000000)<<4)|((CO&0x0000f000)>>4)|((CO&0x00000f00)<<16);
        EO=EO^0x100011001000;
        CO+=0x11001100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x01001000;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 16:
        EP=(EP&0x0fff00ff0fff)|((EP&0xf00000000000)>>32)|((EP&0x00000000f000)<<32)|((EP&0x00000f000000)<<4)|((EP&0x0000f0000000)>>4);
        EO=(EO&0x0fff00ff0fff)|((EO&0xf00000000000)>>32)|((EO&0x00000000f000)<<32)|((EO&0x00000f000000)<<4)|((EO&0x0000f0000000)>>4);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>20)|((CP&0x0f000000)>>12)|((CP&0x0000f000)<<12)|((CP&0x00000f00)<<20);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>20)|((CO&0x0f000000)>>12)|((CO&0x0000f000)<<12)|((CO&0x00000f00)<<20);
        break;
    case 17:
        EP=(EP&0x0fff00ff0fff)|((EP&0x0000f000f000)<<16)|((EP&0xf00000000000)>>20)|((EP&0x00000f000000)>>12);
        EO=(EO&0x0fff00ff0fff)|((EO&0x0000f000f000)<<16)|((EO&0xf00000000000)>>20)|((EO&0x00000f000000)>>12);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>4)|((CP&0x0f000000)>>16)|((CP&0x0000f000)<<16)|((CP&0x00000f00)<<4);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>4)|((CO&0x0f000000)>>16)|((CO&0x0000f000)<<16)|((CO&0x00000f00)<<4);
        EO=EO^0x100011001000;

        CO+=0x11001100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x01001000;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 18:
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>8)|((EP&0x00f000000000)>>32)|((EP&0x00000000f000)<<32)|((EP&0x0000000000f0)<<8);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>8)|((EO&0x00f000000000)>>32)|((EO&0x00000000f000)<<32)|((EO&0x0000000000f0)<<8);
        CN=(CN&0x0f0)|((((CN&0x00f)+2)%6+1)<<8)|((CN&0xf00)>>8);
        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 19:
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>40)|((EP&0x00f000000000)>>24)|((EP&0x00000000f000)<<24)|((EP&0x0000000000f0)<<40);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>40)|((EO&0x00f000000000)>>24)|((EO&0x00000000f000)<<24)|((EO&0x0000000000f0)<<40);
        CN=(CN&0x0f0)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((CN&0x00f)+2)%6+1);
        break;
    case 20:
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>32)|((EP&0x00f000000000)<<8)|((EP&0x00000000f000)>>8)|((EP&0x0000000000f0)<<32);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>32)|((EO&0x00f000000000)<<8)|((EO&0x00000000f000)>>8)|((EO&0x0000000000f0)<<32);

        CN=(CN&0x0f0)|((((CN&0xf00)>>8)+2)%6+1)|((CN&0x00f)<<8);

        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 21:
        EP=(EP&0xffff0000ffff)|((EP&0x00000fff0000)<<4)|((EP&0x0000f0000000)>>12);
        EO=(EO&0xffff0000ffff)|((EO&0x00000fff0000)<<4)|((EO&0x0000f0000000)>>12);
        CN=(CN&0xf00)|((((CN&0x0f0)>>4)+2)%6+1)|((CN&0x00f)<<4);
        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 22:
        EP=(EP&0xffff0000ffff)|((EP&0x000000ff0000)<<8)|((EP&0x0000ff000000)>>8);
        EO=(EO&0xffff0000ffff)|((EO&0x000000ff0000)<<8)|((EO&0x0000ff000000)>>8);
        CN=(CN&0xf00)|(((((CN&0x0f0)>>4)+2)%6+1)<<4)|(((CN&0x00f)+2)%6+1);
        break;
    case 23:
        EP=(EP&0xffff0000ffff)|((EP&0x0000fff00000)>>4)|((EP&0x0000000f0000)<<12);
        EO=(EO&0xffff0000ffff)|((EO&0x0000fff00000)>>4)|((EO&0x0000000f0000)<<12);
        CN=(CN&0xf00)|((((CN&0x00f)+2)%6+1)<<4)|((CN&0x0f0)>>4);
        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 24:
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>32)|((EP&0x000f00000000)<<8)|((EP&0x000000000f00)>>8)|((EP&0x00000000000f)<<32);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>32)|((EO&0x000f00000000)<<8)|((EO&0x000000000f00)>>8)|((EO&0x00000000000f)<<32);
        CN=(CN&0x00f)|(((((CN&0x0f0)>>4)+2)%6+1)<<8)|((CN&0xf00)>>4);
        EO=EO^(0x101011111010);
        break;
    case 25:
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>40)|((EP&0x000f00000000)>>24)|((EP&0x000000000f00)<<24)|((EP&0x00000000000f)<<40);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>40)|((EO&0x000f00000000)>>24)|((EO&0x000000000f00)<<24)|((EO&0x00000000000f)<<40);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((((CN&0x0f0)>>4)+2)%6+1)<<4);
        break;
    case 26:
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>8)|((EP&0x000f00000000)>>32)|((EP&0x000000000f00)<<32)|((EP&0x00000000000f)<<8);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>8)|((EO&0x000f00000000)>>32)|((EO&0x000000000f00)<<32)|((EO&0x00000000000f)<<8);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<4)|((CN&0x0f0)<<4);
        EO=EO^(0x101011111010);
        break;
    case 27:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f000f000000)>>16)|((EP&0x000000f00000)<<20)|((EP&0x000000000f00)<<12);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f000f000000)>>16)|((EO&0x000000f00000)<<20)|((EO&0x000000000f00)<<12);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>16)|((CP&0x00f00000)<<4)|((CP&0x00000f00)>>4)|((CP&0x000000f0)<<16);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>16)|((CO&0x00f00000)<<4)|((CO&0x00000f00)>>4)|((CO&0x000000f0)<<16);
        CN=(CN&0x0f0)|((((CN&0xf00)>>8)+2)%6+1)|((CN&0x00f)<<8);
        CO+=0x01100110;
        for (int o=28; o>=0; o=o-4)
        {

            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00100100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>32)|((EP&0x00f000000000)<<8)|((EP&0x00000000f000)>>8)|((EP&0x0000000000f0)<<32);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>32)|((EO&0x00f000000000)<<8)|((EO&0x00000000f000)>>8)|((EO&0x0000000000f0)<<32);
        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        EP=(EP&0xfff00ff0fff0)|((EP&0x0000000f000f)<<16)|((EP&0x0000f0000000)>>28)|((EP&0x000f00000000)>>4);
        EO=(EO&0xfff00ff0fff0)|((EO&0x0000000f000f)<<16)|((EO&0x0000f0000000)>>28)|((EO&0x000f00000000)>>4);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>16)|((CP&0x000f0000)<<12)|((CP&0x0000f000)>>12)|((CP&0x0000000f)<<16);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>16)|((CO&0x000f0000)<<12)|((CO&0x0000f000)>>12)|((CO&0x0000000f)<<16);
        CO+=0x10011001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x10000001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 28:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f0000000000)>>32)|((EP&0x000000f00000)<<4)|((EP&0x00000f000000)>>4)|((EP&0x000000000f00)<<32);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f0000000000)>>32)|((EO&0x000000f00000)<<4)|((EO&0x00000f000000)>>4)|((EO&0x000000000f00)<<32);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>20)|((CP&0x00f00000)>>12)|((CP&0x00000f00)<<12)|((CP&0x000000f0)<<20);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>20)|((CO&0x00f00000)>>12)|((CO&0x00000f00)<<12)|((CO&0x000000f0)<<20);
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>40)|((EP&0x00f000000000)>>24)|((EP&0x00000000f000)<<24)|((EP&0x0000000000f0)<<40);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>40)|((EO&0x00f000000000)>>24)|((EO&0x00000000f000)<<24)|((EO&0x0000000000f0)<<40);
        CN=(CN&0x0f0)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((CN&0x00f)+2)%6+1);
        EP=(EP&0xfff00ff0fff0)|((EP&0x000f00000000)>>32)|((EP&0x0000f0000000)>>12)|((EP&0x00000000000f)<<32)|((EP&0x0000000f0000)<<12);
        EO=(EO&0xfff00ff0fff0)|((EO&0x000f00000000)>>32)|((EO&0x0000f0000000)>>12)|((EO&0x00000000000f)<<32)|((EO&0x0000000f0000)<<12);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>28)|((CP&0x000f0000)>>4)|((CP&0x0000f000)<<4)|((CP&0x0000000f)<<28);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>28)|((CO&0x000f0000)>>4)|((CO&0x0000f000)<<4)|((CO&0x0000000f)<<28);
        break;
    case 29:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f0000000000)>>20)|((EP&0x000000f00000)>>12)|((EP&0x00000f000000)<<16)|((EP&0x000000000f00)<<16);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f0000000000)>>20)|((EO&0x000000f00000)>>12)|((EO&0x00000f000000)<<16)|((EO&0x000000000f00)<<16);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>4)|((CP&0x00f00000)>>16)|((CP&0x00000f00)<<16)|((CP&0x000000f0)<<4);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>4)|((CO&0x00f00000)>>16)|((CO&0x00000f00)<<16)|((CO&0x000000f0)<<4);
        CN=(CN&0x0f0)|((((CN&0x00f)+2)%6+1)<<8)|((CN&0xf00)>>8);
        CO+=0x01100110;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00100100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>8)|((EP&0x00f000000000)>>32)|((EP&0x00000000f000)<<32)|((EP&0x0000000000f0)<<8);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>8)|((EO&0x00f000000000)>>32)|((EO&0x00000000f000)<<32)|((EO&0x0000000000f0)<<8);
        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        EP=(EP&0xfff00ff0fff0)|((EP&0x000f000f0000)>>16)|((EP&0x0000f0000000)<<4)|((EP&0x00000000000f)<<28);
        EO=(EO&0xfff00ff0fff0)|((EO&0x000f000f0000)>>16)|((EO&0x0000f0000000)<<4)|((EO&0x00000000000f)<<28);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>12)|((CP&0x000f0000)>>16)|((CP&0x0000f000)<<16)|((CP&0x0000000f)<<12);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>12)|((CO&0x000f0000)>>16)|((CO&0x0000f000)<<16)|((CO&0x0000000f)<<12);
        CO+=0x10011001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x10000001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 30:
        EP=(EP&0x0000ffffffff)|((EP&0xfff000000000)>>4)|((EP&0x000f00000000)<<12);
        EO=(EO&0x0000ffffffff)|((EO&0xfff000000000)>>4)|((EO&0x000f00000000)<<12);
        CP=(CP&0x0000ffff)|((CP&0xfff00000)>>4)|((CP&0x000f0000)<<12);
        CO=(CO&0x0000ffff)|((CO&0xfff00000)>>4)|((CO&0x000f0000)<<12);
        CN=(CN&0xf00)|((((CN&0x00f)+2)%6+1)<<4)|((CN&0x0f0)>>4);
        EP=(EP&0xffff0000ffff)|((EP&0x0000fff00000)>>4)|((EP&0x0000000f0000)<<12);
        EO=(EO&0xffff0000ffff)|((EO&0x0000fff00000)>>4)|((EO&0x0000000f0000)<<12);
        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        EP=(EP&0xffffffff0000)|((EP&0x00000000fff0)>>4)|((EP&0x00000000000f)<<12);
        EO=(EO&0xffffffff0000)|((EO&0x00000000fff0)>>4)|((EO&0x00000000000f)<<12);
        CP=(CP&0xffff0000)|((CP&0x0000fff0)>>4)|((CP&0x0000000f)<<12);
        CO=(CO&0xffff0000)|((CO&0x0000fff0)>>4)|((CO&0x0000000f)<<12);
        break;
    case 31:
        EP=(EP&0x0000ffffffff)|((EP&0xff0000000000)>>8)|((EP&0x00ff00000000)<<8);
        EO=(EO&0x0000ffffffff)|((EO&0xff0000000000)>>8)|((EO&0x00ff00000000)<<8);
        CP=(CP&0x0000ffff)|((CP&0xff000000)>>8)|((CP&0x00ff0000)<<8);
        CO=(CO&0x0000ffff)|((CO&0xff000000)>>8)|((CO&0x00ff0000)<<8);
        EP=(EP&0xffff0000ffff)|((EP&0x000000ff0000)<<8)|((EP&0x0000ff000000)>>8);
        EO=(EO&0xffff0000ffff)|((EO&0x000000ff0000)<<8)|((EO&0x0000ff000000)>>8);
        CN=(CN&0xf00)|(((((CN&0x0f0)>>4)+2)%6+1)<<4)|(((CN&0x00f)+2)%6+1);
        EP=(EP&0xffffffff0000)|((EP&0x0000000000ff)<<8)|((EP&0x00000000ff00)>>8);
        EO=(EO&0xffffffff0000)|((EO&0x0000000000ff)<<8)|((EO&0x00000000ff00)>>8);
        CP=(CP&0xffff0000)|((CP&0x000000ff)<<8)|((CP&0x0000ff00)>>8);
        CO=(CO&0xffff0000)|((CO&0x000000ff)<<8)|((CO&0x0000ff00)>>8);
        break;
    case 32:
        EP=(EP&0x0000ffffffff)|((EP&0x0fff00000000)<<4)|((EP&0xf00000000000)>>12);
        EO=(EO&0x0000ffffffff)|((EO&0x0fff00000000)<<4)|((EO&0xf00000000000)>>12);
        CP=(CP&0x0000ffff)|((CP&0x0fff0000)<<4)|((CP&0xf0000000)>>12);
        CO=(CO&0x0000ffff)|((CO&0x0fff0000)<<4)|((CO&0xf0000000)>>12);
        CN=(CN&0xf00)|((((CN&0x0f0)>>4)+2)%6+1)|((CN&0x00f)<<4);
        EP=(EP&0xffff0000ffff)|((EP&0x00000fff0000)<<4)|((EP&0x0000f0000000)>>12);
        EO=(EO&0xffff0000ffff)|((EO&0x00000fff0000)<<4)|((EO&0x0000f0000000)>>12);
        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        EP=(EP&0xffffffff0000)|((EP&0x000000000fff)<<4)|((EP&0x00000000f000)>>12);
        EO=(EO&0xffffffff0000)|((EO&0x000000000fff)<<4)|((EO&0x00000000f000)>>12);
        CP=(CP&0xffff0000)|((CP&0x00000fff)<<4)|((CP&0x0000f000)>>12);
        CO=(CO&0xffff0000)|((CO&0x00000fff)<<4)|((CO&0x0000f000)>>12);
        break;
    case 33:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000f00000)>>16)|((EP&0x0000000f0000)<<20)|((EP&0x0000000000f0)<<12);
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000f00000)>>16)|((EO&0x0000000f0000)<<20)|((EO&0x0000000000f0)<<12);
        EO=EO^0x001000110010; //1
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>16)|((CP&0x000f0000)<<4)|((CP&0x000000f0)>>4)|((CP&0x0000000f)<<16);
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>16)|((CO&0x000f0000)<<4)|((CO&0x000000f0)>>4)|((CO&0x0000000f)<<16);
        CN=(CN&0x00f)|(((((CN&0x0f0)>>4)+2)%6+1)<<8)|((CN&0xf00)>>4);
        CO+=0x00110011;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00010010;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>32)|((EP&0x000f00000000)<<8)|((EP&0x000000000f00)>>8)|((EP&0x00000000000f)<<32);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>32)|((EO&0x000f00000000)<<8)|((EO&0x000000000f00)>>8)|((EO&0x00000000000f)<<32);
        EO=EO^(0x101011111010);
        EP=(EP&0x0fff00ff0fff)|((EP&0x0000f000f000)<<16)|((EP&0xf00000000000)>>20)|((EP&0x00000f000000)>>12);
        EO=(EO&0x0fff00ff0fff)|((EO&0x0000f000f000)<<16)|((EO&0xf00000000000)>>20)|((EO&0x00000f000000)>>12);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>4)|((CP&0x0f000000)>>16)|((CP&0x0000f000)<<16)|((CP&0x00000f00)<<4);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>4)|((CO&0x0f000000)>>16)|((CO&0x0000f000)<<16)|((CO&0x00000f00)<<4);
        EO=EO^0x100011001000;
        CO+=0x11001100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x01001000;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 34:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000000000)>>32)|((EP&0x0000000f0000)<<4)|((EP&0x0000000000f0)<<32)|((EP&0x000000f00000)>>4);
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000000000)>>32)|((EO&0x0000000f0000)<<4)|((EO&0x0000000000f0)<<32)|((EO&0x000000f00000)>>4);
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>20)|((CP&0x000f0000)>>12)|((CP&0x000000f0)<<12)|((CP&0x0000000f)<<20);
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>20)|((CO&0x000f0000)>>12)|((CO&0x000000f0)<<12)|((CO&0x0000000f)<<20);
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>40)|((EP&0x000f00000000)>>24)|((EP&0x000000000f00)<<24)|((EP&0x00000000000f)<<40);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>40)|((EO&0x000f00000000)>>24)|((EO&0x000000000f00)<<24)|((EO&0x00000000000f)<<40);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((((CN&0x0f0)>>4)+2)%6+1)<<4);
        EP=(EP&0x0fff00ff0fff)|((EP&0xf00000000000)>>32)|((EP&0x00000000f000)<<32)|((EP&0x00000f000000)<<4)|((EP&0x0000f0000000)>>4);
        EO=(EO&0x0fff00ff0fff)|((EO&0xf00000000000)>>32)|((EO&0x00000000f000)<<32)|((EO&0x00000f000000)<<4)|((EO&0x0000f0000000)>>4);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>20)|((CP&0x0f000000)>>12)|((CP&0x0000f000)<<12)|((CP&0x00000f00)<<20);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>20)|((CO&0x0f000000)>>12)|((CO&0x0000f000)<<12)|((CO&0x00000f00)<<20);
        break;
    case 35:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000000000)>>20)|((EP&0x0000000f0000)>>12)|((EP&0x000000f000f0)<<16); //10
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000000000)>>20)|((EO&0x0000000f0000)>>12)|((EO&0x000000f000f0)<<16);
        EO=EO^0x001000110010; //1
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>4)|((CP&0x000f0000)>>16)|((CP&0x000000f0)<<16)|((CP&0x0000000f)<<4); //13
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>4)|((CO&0x000f0000)>>16)|((CO&0x000000f0)<<16)|((CO&0x0000000f)<<4);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<4)|((CN&0x0f0)<<4);
        CO+=0x00110011;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00010010;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>8)|((EP&0x000f00000000)>>32)|((EP&0x000000000f00)<<32)|((EP&0x00000000000f)<<8);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>8)|((EO&0x000f00000000)>>32)|((EO&0x000000000f00)<<32)|((EO&0x00000000000f)<<8);
        EO=EO^(0x101011111010);
        EP=(EP&0x0fff00ff0fff)|((EP&0xf000f0000000)>>16)|((EP&0x00000000f000)<<12)|((EP&0x00000f000000)<<20);
        EO=(EO&0x0fff00ff0fff)|((EO&0xf000f0000000)>>16)|((EO&0x00000000f000)<<12)|((EO&0x00000f000000)<<20);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>16)|((CP&0x0f000000)<<4)|((CP&0x0000f000)>>4)|((CP&0x00000f00)<<16);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>16)|((CO&0x0f000000)<<4)|((CO&0x0000f000)>>4)|((CO&0x00000f00)<<16);
        EO=EO^0x100011001000;
        CO+=0x11001100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x01001000;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 36:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f000f000000)>>16)|((EP&0x000000f00000)<<20)|((EP&0x000000000f00)<<12);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f000f000000)>>16)|((EO&0x000000f00000)<<20)|((EO&0x000000000f00)<<12);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>16)|((CP&0x00f00000)<<4)|((CP&0x00000f00)>>4)|((CP&0x000000f0)<<16);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>16)|((CO&0x00f00000)<<4)|((CO&0x00000f00)>>4)|((CO&0x000000f0)<<16);
        CN=(CN&0x0f0)|((((CN&0xf00)>>8)+2)%6+1)|((CN&0x00f)<<8);
        CO+=0x01100110;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00100100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>32)|((EP&0x00f000000000)<<8)|((EP&0x00000000f000)>>8)|((EP&0x0000000000f0)<<32);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>32)|((EO&0x00f000000000)<<8)|((EO&0x00000000f000)>>8)|((EO&0x0000000000f0)<<32);
        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 37:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f0000000000)>>32)|((EP&0x000000f00000)<<4)|((EP&0x00000f000000)>>4)|((EP&0x000000000f00)<<32);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f0000000000)>>32)|((EO&0x000000f00000)<<4)|((EO&0x00000f000000)>>4)|((EO&0x000000000f00)<<32);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>20)|((CP&0x00f00000)>>12)|((CP&0x00000f00)<<12)|((CP&0x000000f0)<<20);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>20)|((CO&0x00f00000)>>12)|((CO&0x00000f00)<<12)|((CO&0x000000f0)<<20);
        CN=(CN&0x0f0)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((CN&0x00f)+2)%6+1);
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>40)|((EP&0x00f000000000)>>24)|((EP&0x00000000f000)<<24)|((EP&0x0000000000f0)<<40);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>40)|((EO&0x00f000000000)>>24)|((EO&0x00000000f000)<<24)|((EO&0x0000000000f0)<<40);
        break;
    case 38:
        EP=(EP&0xf0fff00ff0ff)|((EP&0x0f0000000000)>>20)|((EP&0x000000f00000)>>12)|((EP&0x00000f000000)<<16)|((EP&0x000000000f00)<<16);
        EO=(EO&0xf0fff00ff0ff)|((EO&0x0f0000000000)>>20)|((EO&0x000000f00000)>>12)|((EO&0x00000f000000)<<16)|((EO&0x000000000f00)<<16);
        CP=(CP&0xf00ff00f)|((CP&0x0f000000)>>4)|((CP&0x00f00000)>>16)|((CP&0x00000f00)<<16)|((CP&0x000000f0)<<4);
        CO=(CO&0xf00ff00f)|((CO&0x0f000000)>>4)|((CO&0x00f00000)>>16)|((CO&0x00000f00)<<16)|((CO&0x000000f0)<<4);
        CN=(CN&0x0f0)|((((CN&0x00f)+2)%6+1)<<8)|((CN&0xf00)>>8);
        CO+=0x01100110;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00100100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>8)|((EP&0x00f000000000)>>32)|((EP&0x00000000f000)<<32)|((EP&0x0000000000f0)<<8);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>8)|((EO&0x00f000000000)>>32)|((EO&0x00000000f000)<<32)|((EO&0x0000000000f0)<<8);
        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 39:
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>8)|((EP&0x00f000000000)>>32)|((EP&0x00000000f000)<<32)|((EP&0x0000000000f0)<<8);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>8)|((EO&0x00f000000000)>>32)|((EO&0x00000000f000)<<32)|((EO&0x0000000000f0)<<8);

        CN=(CN&0x0f0)|((((CN&0x00f)+2)%6+1)<<8)|((CN&0xf00)>>8);

        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        EP=(EP&0xfff00ff0fff0)|((EP&0x000f000f0000)>>16)|((EP&0x0000f0000000)<<4)|((EP&0x00000000000f)<<28);
        EO=(EO&0xfff00ff0fff0)|((EO&0x000f000f0000)>>16)|((EO&0x0000f0000000)<<4)|((EO&0x00000000000f)<<28);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>12)|((CP&0x000f0000)>>16)|((CP&0x0000f000)<<16)|((CP&0x0000000f)<<12);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>12)|((CO&0x000f0000)>>16)|((CO&0x0000f000)<<16)|((CO&0x0000000f)<<12);
        CO+=0x10011001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x10000001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 40:
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>40)|((EP&0x00f000000000)>>24)|((EP&0x00000000f000)<<24)|((EP&0x0000000000f0)<<40);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>40)|((EO&0x00f000000000)>>24)|((EO&0x00000000f000)<<24)|((EO&0x0000000000f0)<<40);
        CN=(CN&0x0f0)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((CN&0x00f)+2)%6+1);
        EP=(EP&0xfff00ff0fff0)|((EP&0x000f00000000)>>32)|((EP&0x0000f0000000)>>12)|((EP&0x00000000000f)<<32)|((EP&0x0000000f0000)<<12);
        EO=(EO&0xfff00ff0fff0)|((EO&0x000f00000000)>>32)|((EO&0x0000f0000000)>>12)|((EO&0x00000000000f)<<32)|((EO&0x0000000f0000)<<12);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>28)|((CP&0x000f0000)>>4)|((CP&0x0000f000)<<4)|((CP&0x0000000f)<<28);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>28)|((CO&0x000f0000)>>4)|((CO&0x0000f000)<<4)|((CO&0x0000000f)<<28);
        break;
    case 41:
        EP=(EP&0x0f0fffff0f0f)|((EP&0xf00000000000)>>32)|((EP&0x00f000000000)<<8)|((EP&0x00000000f000)>>8)|((EP&0x0000000000f0)<<32);
        EO=(EO&0x0f0fffff0f0f)|((EO&0xf00000000000)>>32)|((EO&0x00f000000000)<<8)|((EO&0x00000000f000)>>8)|((EO&0x0000000000f0)<<32);
        CN=(CN&0x0f0)|((((CN&0xf00)>>8)+2)%6+1)|((CN&0x00f)<<8);
        if (((CN&0x0f0)==0x020) || ((CN&0x0f0)==0x050))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0x0f0)==0x010) || ((CN&0x0f0)==0x040))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0x0f0)==0x030) || ((CN&0x0f0)==0x060))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0xf00000000000,0x00f000000000,0x00000000f000,0x0000000000f0};
            shiftin= {44,36,12,4};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0x0f0000000000,0x000f00000000,0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000,0x000000000f00,0x00000000000f};
            shiftin= {40,32,28,24,20,16,8,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        EP=(EP&0xfff00ff0fff0)|((EP&0x0000000f000f)<<16)|((EP&0x0000f0000000)>>28)|((EP&0x000f00000000)>>4);
        EO=(EO&0xfff00ff0fff0)|((EO&0x0000000f000f)<<16)|((EO&0x0000f0000000)>>28)|((EO&0x000f00000000)>>4);
        CP=(CP&0x0ff00ff0)|((CP&0xf0000000)>>16)|((CP&0x000f0000)<<12)|((CP&0x0000f000)>>12)|((CP&0x0000000f)<<16);
        CO=(CO&0x0ff00ff0)|((CO&0xf0000000)>>16)|((CO&0x000f0000)<<12)|((CO&0x0000f000)>>12)|((CO&0x0000000f)<<16);
        CO+=0x10011001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x10000001;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        break;
    case 44:
        EP=(EP&0x0000ffffffff)|((EP&0x0fff00000000)<<4)|((EP&0xf00000000000)>>12);
        EO=(EO&0x0000ffffffff)|((EO&0x0fff00000000)<<4)|((EO&0xf00000000000)>>12);
        CP=(CP&0x0000ffff)|((CP&0x0fff0000)<<4)|((CP&0xf0000000)>>12);
        CO=(CO&0x0000ffff)|((CO&0x0fff0000)<<4)|((CO&0xf0000000)>>12);
        EP=(EP&0xffff0000ffff)|((EP&0x00000fff0000)<<4)|((EP&0x0000f0000000)>>12);
        EO=(EO&0xffff0000ffff)|((EO&0x00000fff0000)<<4)|((EO&0x0000f0000000)>>12);
        CN=(CN&0xf00)|((((CN&0x0f0)>>4)+2)%6+1)|((CN&0x00f)<<4);
        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 43:
        EP=(EP&0x0000ffffffff)|((EP&0xff0000000000)>>8)|((EP&0x00ff00000000)<<8);
        EO=(EO&0x0000ffffffff)|((EO&0xff0000000000)>>8)|((EO&0x00ff00000000)<<8);
        CP=(CP&0x0000ffff)|((CP&0xff000000)>>8)|((CP&0x00ff0000)<<8);
        CO=(CO&0x0000ffff)|((CO&0xff000000)>>8)|((CO&0x00ff0000)<<8);
        EP=(EP&0xffff0000ffff)|((EP&0x000000ff0000)<<8)|((EP&0x0000ff000000)>>8);
        EO=(EO&0xffff0000ffff)|((EO&0x000000ff0000)<<8)|((EO&0x0000ff000000)>>8);
        CN=(CN&0xf00)|(((((CN&0x0f0)>>4)+2)%6+1)<<4)|(((CN&0x00f)+2)%6+1);
        break;
    case 42:
        EP=(EP&0x0000ffffffff)|((EP&0xfff000000000)>>4)|((EP&0x000f00000000)<<12);
        EO=(EO&0x0000ffffffff)|((EO&0xfff000000000)>>4)|((EO&0x000f00000000)<<12);
        CP=(CP&0x0000ffff)|((CP&0xfff00000)>>4)|((CP&0x000f0000)<<12);
        CO=(CO&0x0000ffff)|((CO&0xfff00000)>>4)|((CO&0x000f0000)<<12);
        EP=(EP&0xffff0000ffff)|((EP&0x0000fff00000)>>4)|((EP&0x0000000f0000)<<12);
        EO=(EO&0xffff0000ffff)|((EO&0x0000fff00000)>>4)|((EO&0x0000000f0000)<<12);
        CN=(CN&0xf00)|((((CN&0x00f)+2)%6+1)<<4)|((CN&0x0f0)>>4);

        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 45:
        EP=(EP&0xffffffff0000)|((EP&0x000000000fff)<<4)|((EP&0x00000000f000)>>12);
        EO=(EO&0xffffffff0000)|((EO&0x000000000fff)<<4)|((EO&0x00000000f000)>>12);
        CP=(CP&0xffff0000)|((CP&0x00000fff)<<4)|((CP&0x0000f000)>>12);
        CO=(CO&0xffff0000)|((CO&0x00000fff)<<4)|((CO&0x0000f000)>>12);
        EP=(EP&0xffff0000ffff)|((EP&0x00000fff0000)<<4)|((EP&0x0000f0000000)>>12);
        EO=(EO&0xffff0000ffff)|((EO&0x00000fff0000)<<4)|((EO&0x0000f0000000)>>12);
        CN=(CN&0xf00)|((((CN&0x0f0)>>4)+2)%6+1)|((CN&0x00f)<<4);
        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 46:
        EP=(EP&0xffffffff0000)|((EP&0x0000000000ff)<<8)|((EP&0x00000000ff00)>>8);
        EO=(EO&0xffffffff0000)|((EO&0x0000000000ff)<<8)|((EO&0x00000000ff00)>>8);
        CP=(CP&0xffff0000)|((CP&0x000000ff)<<8)|((CP&0x0000ff00)>>8);
        CO=(CO&0xffff0000)|((CO&0x000000ff)<<8)|((CO&0x0000ff00)>>8);
        EP=(EP&0xffff0000ffff)|((EP&0x000000ff0000)<<8)|((EP&0x0000ff000000)>>8);
        EO=(EO&0xffff0000ffff)|((EO&0x000000ff0000)<<8)|((EO&0x0000ff000000)>>8);
        CN=(CN&0xf00)|(((((CN&0x0f0)>>4)+2)%6+1)<<4)|(((CN&0x00f)+2)%6+1);
        break;
    case 47:
        EP=(EP&0xffffffff0000)|((EP&0x00000000fff0)>>4)|((EP&0x00000000000f)<<12);
        EO=(EO&0xffffffff0000)|((EO&0x00000000fff0)>>4)|((EO&0x00000000000f)<<12);
        CP=(CP&0xffff0000)|((CP&0x0000fff0)>>4)|((CP&0x0000000f)<<12);
        CO=(CO&0xffff0000)|((CO&0x0000fff0)>>4)|((CO&0x0000000f)<<12);
        EP=(EP&0xffff0000ffff)|((EP&0x0000fff00000)>>4)|((EP&0x0000000f0000)<<12);
        EO=(EO&0xffff0000ffff)|((EO&0x0000fff00000)>>4)|((EO&0x0000000f0000)<<12);
        CN=(CN&0xf00)|((((CN&0x00f)+2)%6+1)<<4)|((CN&0x0f0)>>4);
        if (((CN&0xf00)==0x100) || ((CN&0xf00)==0x400))
        {
            slicers= {0x5,0x6,0x7,0x8};
        }
        else if (((CN&0xf00)==0x200) || ((CN&0xf00)==0x500))
        {
            slicers= {0x1,0x3,0x9,0xb};
        }
        else if (((CN&0xf00)==0x300) || ((CN&0xf00)==0x600))
        {
            slicers= {0x2,0x4,0xa,0xc};
        }
        else
        {
            slicers= {0x0};
        }
        if (slicers.size()>1)
        {
            slicemask= {0x0000f0000000,0x00000f000000,0x000000f00000,0x0000000f0000};
            shiftin= {28,24,20,16};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])!=slicers[0]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[1]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[2]) & (((EP&slicemask[i])>>shiftin[i])!=slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
            slicemask= {0xf00000000000,0x0f0000000000,0x00f000000000,0x000f00000000,0x00000000f000,0x000000000f00,0x0000000000f0,0x00000000000f};
            shiftin= {44,40,36,32,12,8,4,0};
            for (int i=0; i<slicemask.size(); i++)
            {
                if ((((EP&slicemask[i])>>shiftin[i])==slicers[0]) | (((EP&slicemask[i])>>shiftin[i])==slicers[1]) | (((EP&slicemask[i])>>shiftin[i])==slicers[2]) | (((EP&slicemask[i])>>shiftin[i])==slicers[3]))
                {
                    EO=EO^(0x111111111111&slicemask[i]);
                }
            }
        }
        break;
    case 48:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000f00000)>>16)|((EP&0x0000000f0000)<<20)|((EP&0x0000000000f0)<<12);
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000f00000)>>16)|((EO&0x0000000f0000)<<20)|((EO&0x0000000000f0)<<12);
        EO=EO^0x001000110010; //1
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>16)|((CP&0x000f0000)<<4)|((CP&0x000000f0)>>4)|((CP&0x0000000f)<<16);
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>16)|((CO&0x000f0000)<<4)|((CO&0x000000f0)>>4)|((CO&0x0000000f)<<16);
        CO+=0x00110011;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00010010;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>32)|((EP&0x000f00000000)<<8)|((EP&0x000000000f00)>>8)|((EP&0x00000000000f)<<32);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>32)|((EO&0x000f00000000)<<8)|((EO&0x000000000f00)>>8)|((EO&0x00000000000f)<<32);
        CN=(CN&0x00f)|(((((CN&0x0f0)>>4)+2)%6+1)<<8)|((CN&0xf00)>>4);
        EO=EO^(0x101011111010);
        break;
    case 49:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000000000)>>32)|((EP&0x0000000f0000)<<4)|((EP&0x0000000000f0)<<32)|((EP&0x000000f00000)>>4);
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000000000)>>32)|((EO&0x0000000f0000)<<4)|((EO&0x0000000000f0)<<32)|((EO&0x000000f00000)>>4);
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>20)|((CP&0x000f0000)>>12)|((CP&0x000000f0)<<12)|((CP&0x0000000f)<<20);
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>20)|((CO&0x000f0000)>>12)|((CO&0x000000f0)<<12)|((CO&0x0000000f)<<20);
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>40)|((EP&0x000f00000000)>>24)|((EP&0x000000000f00)<<24)|((EP&0x00000000000f)<<40);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>40)|((EO&0x000f00000000)>>24)|((EO&0x000000000f00)<<24)|((EO&0x00000000000f)<<40);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((((CN&0x0f0)>>4)+2)%6+1)<<4);
        break;
    case 50:
        EP=(EP&0xff0fff00ff0f)|((EP&0x00f000000000)>>20)|((EP&0x0000000f0000)>>12)|((EP&0x000000f000f0)<<16); //10
        EO=(EO&0xff0fff00ff0f)|((EO&0x00f000000000)>>20)|((EO&0x0000000f0000)>>12)|((EO&0x000000f000f0)<<16);
        EO=EO^0x001000110010; //1
        CP=(CP&0xff00ff00)|((CP&0x00f00000)>>4)|((CP&0x000f0000)>>16)|((CP&0x000000f0)<<16)|((CP&0x0000000f)<<4); //13
        CO=(CO&0xff00ff00)|((CO&0x00f00000)>>4)|((CO&0x000f0000)>>16)|((CO&0x000000f0)<<16)|((CO&0x0000000f)<<4);
        CO+=0x00110011;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x00010010;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>8)|((EP&0x000f00000000)>>32)|((EP&0x000000000f00)<<32)|((EP&0x00000000000f)<<8);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>8)|((EO&0x000f00000000)>>32)|((EO&0x000000000f00)<<32)|((EO&0x00000000000f)<<8);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<4)|((CN&0x0f0)<<4);
        EO=EO^(0x101011111010);
        break;
    case 53:
        EP=(EP&0x0fff00ff0fff)|((EP&0x0000f000f000)<<16)|((EP&0xf00000000000)>>20)|((EP&0x00000f000000)>>12);
        EO=(EO&0x0fff00ff0fff)|((EO&0x0000f000f000)<<16)|((EO&0xf00000000000)>>20)|((EO&0x00000f000000)>>12);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>4)|((CP&0x0f000000)>>16)|((CP&0x0000f000)<<16)|((CP&0x00000f00)<<4);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>4)|((CO&0x0f000000)>>16)|((CO&0x0000f000)<<16)|((CO&0x00000f00)<<4);
        EO=EO^0x100011001000;
        CO+=0x11001100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x01001000;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>32)|((EP&0x000f00000000)<<8)|((EP&0x000000000f00)>>8)|((EP&0x00000000000f)<<32);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>32)|((EO&0x000f00000000)<<8)|((EO&0x000000000f00)>>8)|((EO&0x00000000000f)<<32);
        CN=(CN&0x00f)|(((((CN&0x0f0)>>4)+2)%6+1)<<8)|((CN&0xf00)>>4);
        EO=EO^(0x101011111010);
        break;
    case 52:
        EP=(EP&0x0fff00ff0fff)|((EP&0xf00000000000)>>32)|((EP&0x00000000f000)<<32)|((EP&0x00000f000000)<<4)|((EP&0x0000f0000000)>>4);
        EO=(EO&0x0fff00ff0fff)|((EO&0xf00000000000)>>32)|((EO&0x00000000f000)<<32)|((EO&0x00000f000000)<<4)|((EO&0x0000f0000000)>>4);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>20)|((CP&0x0f000000)>>12)|((CP&0x0000f000)<<12)|((CP&0x00000f00)<<20);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>20)|((CO&0x0f000000)>>12)|((CO&0x0000f000)<<12)|((CO&0x00000f00)<<20);
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>40)|((EP&0x000f00000000)>>24)|((EP&0x000000000f00)<<24)|((EP&0x00000000000f)<<40);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>40)|((EO&0x000f00000000)>>24)|((EO&0x000000000f00)<<24)|((EO&0x00000000000f)<<40);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<8)|(((((CN&0x0f0)>>4)+2)%6+1)<<4);
        break;
    case 51:
        EP=(EP&0x0fff00ff0fff)|((EP&0xf000f0000000)>>16)|((EP&0x00000000f000)<<12)|((EP&0x00000f000000)<<20);
        EO=(EO&0x0fff00ff0fff)|((EO&0xf000f0000000)>>16)|((EO&0x00000000f000)<<12)|((EO&0x00000f000000)<<20);
        CP=(CP&0x00ff00ff)|((CP&0xf0000000)>>16)|((CP&0x0f000000)<<4)|((CP&0x0000f000)>>4)|((CP&0x00000f00)<<16);
        CO=(CO&0x00ff00ff)|((CO&0xf0000000)>>16)|((CO&0x0f000000)<<4)|((CO&0x0000f000)>>4)|((CO&0x00000f00)<<16);
        EO=EO^0x100011001000;
        CO+=0x11001100;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        CO+=0x01001000;
        for (int o=28; o>=0; o=o-4)
        {
            if (!((CO&(0xf<<o))>>(o+2)))
            {
                CO&=~(0xf<<o);
            }
            else if (!((~((CO&(0x7<<o))>>o)&0x7)<<60))
            {
                CO&=~(0xb<<o);
            }
        }
        EP=(EP&0xf0f0fffff0f0)|((EP&0x0f0000000000)>>8)|((EP&0x000f00000000)>>32)|((EP&0x000000000f00)<<32)|((EP&0x00000000000f)<<8);
        EO=(EO&0xf0f0fffff0f0)|((EO&0x0f0000000000)>>8)|((EO&0x000f00000000)>>32)|((EO&0x000000000f00)<<32)|((EO&0x00000000000f)<<8);
        CN=(CN&0x00f)|(((((CN&0xf00)>>8)+2)%6+1)<<4)|((CN&0x0f0)<<4);
        EO=EO^(0x101011111010);
    }
    return;
}

string y2rotator(string initial)
{
    vector<string> words;
    string tuf;
    stringstream ss(initial);
    while (ss >> tuf)
    {
        words.push_back(tuf+" ");
    }
    for (int q=0; q<words.size(); q++)
    {
        if (words[q][0]=='R')
        {
            words[q][0]='L';
        }
        else if (words[q][0]=='L')
        {
            words[q][0]='R';
        }
    }

    string goout;
    for (const auto &piece : words) goout += piece + " ";
    goout = regex_replace(goout, std::regex(" +"), " ");
    return goout;
}


string solutionreducer(string initial, int step)
{
    vector<string> words;
    vector<int> clearthese= {};
    string tuf;
    stringstream ss(initial);
    while (ss >> tuf)
    {
        words.push_back(tuf+" ");
    }

    if (words.size()>0)
    {
        if ((customdets[step][8]==1)&&(words[words.size()-1][0]=='U'))
        {
            words.pop_back();
        }
    }
    for (int q=(words.size()-1); q>0; q--)
    {
        if ((words[q][0]=='U' && words[q-1][0]=='U') || (words[q][0]=='D' && words[q-1][0]=='D') || (words[q][0]=='R' && words[q-1][0]=='R') || (words[q][0]=='L' && words[q-1][0]=='L') || (words[q][0]=='F' && words[q-1][0]=='F') || (words[q][0]=='B' && words[q-1][0]=='B') || (words[q][0]=='M' && words[q-1][0]=='M') || (words[q][0]=='S' && words[q-1][0]=='S') || (words[q][0]=='E' && words[q-1][0]=='E') || (words[q][0]=='r' && words[q-1][0]=='r'))
        {
            if ( (words[q][1]==' ' && words[q-1][1]==' ') || (words[q][1]=='\'' && words[q-1][1]=='\'') )
            {
                words[q-1][1]='2';
                clearthese.push_back(q);
            }
            else if ( (words[q][1]=='2' && words[q-1][1]==' ') || (words[q][1]==' ' && words[q-1][1]=='2') )
            {
                words[q-1][1]='\'';
                clearthese.push_back(q);
            }
            else if ( (words[q][1]=='2' && words[q-1][1]=='\'') || (words[q][1]=='\'' && words[q-1][1]=='2') )
            {
                words[q-1][1]=' ';
                clearthese.push_back(q);
            }
            else if ( (words[q][1]=='2' && words[q-1][1]=='2') || (words[q][1]=='\'' && words[q-1][1]==' ') || (words[q][1]==' ' && words[q-1][1]=='\'') )
            {
                clearthese.push_back(q);
                clearthese.push_back(q-1);
            }
        }
    }

    for (int q=(words.size()-1); q>0; q--)
    {
        if ((words[q][0]=='R' && words[q-1][0]=='L') || (words[q][0]=='U' && words[q-1][0]=='D') || (words[q][0]=='F' && words[q-1][0]=='B')
                || (words[q][0]=='R' && words[q-1][0]=='r') || (words[q][0]=='R' && words[q-1][0]=='M') || (words[q][0]=='R' && words[q-1][0]=='l')
                || (words[q][0]=='L' && words[q-1][0]=='r') || (words[q][0]=='L' && words[q-1][0]=='M') || (words[q][0]=='L' && words[q-1][0]=='l')
                || (words[q][0]=='M' && words[q-1][0]=='r') || (words[q][0]=='M' && words[q-1][0]=='l') || (words[q][0]=='r' && words[q-1][0]=='l')
                || (words[q][0]=='U' && words[q-1][0]=='u') || (words[q][0]=='U' && words[q-1][0]=='E') || (words[q][0]=='U' && words[q-1][0]=='d')
                || (words[q][0]=='D' && words[q-1][0]=='u') || (words[q][0]=='D' && words[q-1][0]=='E') || (words[q][0]=='D' && words[q-1][0]=='d')
                || (words[q][0]=='E' && words[q-1][0]=='u') || (words[q][0]=='E' && words[q-1][0]=='d') || (words[q][0]=='u' && words[q-1][0]=='d')
                || (words[q][0]=='F' && words[q-1][0]=='f') || (words[q][0]=='F' && words[q-1][0]=='S') || (words[q][0]=='F' && words[q-1][0]=='b')
                || (words[q][0]=='B' && words[q-1][0]=='f') || (words[q][0]=='B' && words[q-1][0]=='S') || (words[q][0]=='B' && words[q-1][0]=='b')
                || (words[q][0]=='S' && words[q-1][0]=='f') || (words[q][0]=='S' && words[q-1][0]=='b') || (words[q][0]=='f' && words[q-1][0]=='b')
           )
        {
            string temp1=words[q-1];
            words[q-1]=words[q];
            words[q]=temp1;
        }
    }

    sort( clearthese.begin(), clearthese.end() );
    clearthese.erase( unique( clearthese.begin(), clearthese.end() ), clearthese.end() );


    for (int i=(clearthese.size()-1); i>=0; i--)
    {
        words.erase(words.begin()+clearthese[i]);
    }

    string goout;

    for (const auto &piece : words) goout += piece + " ";

    goout = regex_replace(goout, std::regex(" +"), " ");

    return goout;

}

// need to switcheroo this
string moveReverse(string regular)
{
    string reversed=" "; // added an extra space here
    string tuf;
    string temp;
    stringstream ss(regular);
    while (ss >> tuf)
    {
        if (tuf=="U")
        {
            temp="U' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="U'")
        {
            temp="U ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="U2")
        {
            temp="U2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="D")
        {
            temp="D' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="D'")
        {
            temp="D ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="D2")
        {
            temp="D2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="R")
        {
            temp="R' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="R'")
        {
            temp="R ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="R2")
        {
            temp="R2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="L")
        {
            temp="L' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="L'")
        {
            temp="L ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="L2")
        {
            temp="L2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="F")
        {
            temp="F' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="F'")
        {
            temp="F ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="F2")
        {
            temp="F2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="B")
        {
            temp="B' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="B'")
        {
            temp="B ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="B2")
        {
            temp="B2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="x")
        {
            temp="x' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="x'")
        {
            temp="x ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="x2")
        {
            temp="x2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="y")
        {
            temp="y' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="y'")
        {
            temp="y ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="y2")
        {
            temp="y2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="z")
        {
            temp="z' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="z'")
        {
            temp="z ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="z2")
        {
            temp="z2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="E")
        {
            temp="E' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="E'")
        {
            temp="E ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="E2")
        {
            temp="E2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="S")
        {
            temp="S' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="S'")
        {
            temp="S ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="S2")
        {
            temp="S2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="M")
        {
            temp="M' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="M'")
        {
            temp="M ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="M2")
        {
            temp="M2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="r")
        {
            temp="r' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="r'")
        {
            temp="r ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="r2")
        {
            temp="r2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="l")
        {
            temp="l' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="l'")
        {
            temp="l ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="l2")
        {
            temp="l2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="u")
        {
            temp="u' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="u'")
        {
            temp="u ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="u2")
        {
            temp="u2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="u")
        {
            temp="u' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="d'")
        {
            temp="d ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="d2")
        {
            temp="d2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="d")
        {
            temp="d' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="f'")
        {
            temp="f ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="f2")
        {
            temp="f2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="f")
        {
            temp="f' ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="b'")
        {
            temp="b ";
            reversed=temp.append(reversed);
        }
        else if (tuf=="b2")
        {
            temp="b2 ";
            reversed=temp.append(reversed);
        }
        else if (tuf==" ")
        {
            temp=" ";
            reversed=temp.append(reversed);
        }
    }
    return reversed;
}


string concat_strings(const vector<string> &elements, const string &separator)
{
    if (!elements.empty())
    {
        std::stringstream ss;
        auto it = elements.cbegin();
        while (true)
        {
            ss << *it++;
            if (it != elements.cend())
                ss << separator;
            else
                return ss.str();
        }
    }
    return "";
}

typedef boost::tuples::tuple<__int64,__int64,__int64,__int64,__int64> Edge;

struct ihash
    : std::unary_function<Edge, std::size_t>
{
    std::size_t operator()(Edge const& e) const
    {
        std::size_t seed = 0;
        boost::hash_combine( seed, e.get<0>() );
        boost::hash_combine( seed, e.get<1>() );
        boost::hash_combine( seed, e.get<2>() ); // only up to here
        boost::hash_combine( seed, e.get<3>() );
        boost::hash_combine( seed, e.get<4>() );
        //  boost::hash_combine( seed, e.get<3>() );
        return seed;
    }
};

struct iequal_to
    : std::binary_function<Edge, Edge, bool>
{
    bool operator()(Edge const& x, Edge const& y) const
    {
        return ( x.get<0>()==y.get<0>() &&
                 x.get<1>()==y.get<1>() &&
                 x.get<2>()==y.get<2>()
                 && x.get<3>()==y.get<3>()
                 && x.get<4>()==y.get<4>());
    }
};

//old one
//typedef boost::unordered_multimap< Edge, string, ihash, iequal_to > EdgeMap;
typedef boost::unordered_multimap< Edge, vector < char >, ihash, iequal_to > EdgeMap;
EdgeMap mapp0;
EdgeMap mapp1;
EdgeMap mapp2;
EdgeMap mapp3;
EdgeMap mapp4; // reserved for alg sets in presets? nah boy
EdgeMap mapp5;
EdgeMap mapp6;
EdgeMap mapp7;
EdgeMap mapp8;

void addLayers2(vector < char > curset, vector < vector < char > > &thisone, int allowedmoves)
{
    // allowedmoves: 1=6 gen, 2=6gen+Mr, 3=RUMr, 4=RUD, 5=RULD, 6=FURB, 7=MU, 8=U (algs), 9=MUD, 10=LUD;
    // 0 1 2 = U U2 U'      axis-0, /3=0
    // 3 4 5 = D            axis-0, /3=1
    // 6 7 8 = R            axis-1, /3=2
    // 9 10 11 = L          axis-1, /3=3
    // 12 13 14 = F         axis-2, /3=4
    // 15 16 17 = B         axis-2, /3=5
    // 18 19 20 = M         axis-1, /3=6
    // 21 22 23 = E         axis-0, /3=7
    // 24 25 26 = S         axis-2, /3=8
    // 36 37 38 = r         axis-1, /3=12
    // 39 40 41 = l         axis-1, /3=13
    // 42 43 44 = u         axis-0, /3=14
    // 45 46 47 = d         axis-0, /3=15
    // 48 49 50 = f         axis-2, /3=16
    // 51 52 53 = b         axis-2, /3=17
    vector < char > candimoves=moveinsets[allowedmoves-1];
    char axis=10;
    char laxis=10;
    for (int i=curset.size()-1; i>=0; i--)
    {
        if ((curset[i]/3)==0)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
        }
        else if((curset[i]/3)==1)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
        }
        else if((curset[i]/3)==7)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 3), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 4), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 5), candimoves.end());
        }
        else if((curset[i]/3)==14)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 3), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 4), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 5), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 21), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 22), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 23), candimoves.end());
        }
        else if((curset[i]/3)==15)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 3), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 4), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 5), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 21), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 22), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 23), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 42), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 43), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 44), candimoves.end());
        }

        else if ((curset[i]/3)==2)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
        }
        else if((curset[i]/3)==3)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
        }
        else if((curset[i]/3)==6)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 9), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 10), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 11), candimoves.end());
        }
        else if((curset[i]/3)==12)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 9), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 10), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 11), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 18), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 19), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 20), candimoves.end());
        }
        else if((curset[i]/3)==13)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 9), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 10), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 11), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 18), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 19), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 20), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 36), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 37), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 38), candimoves.end());
        }

        if ((curset[i]/3)==4)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
        }
        else if((curset[i]/3)==5)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
        }
        else if((curset[i]/3)==8)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 15), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 16), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 17), candimoves.end());
        }
        else if((curset[i]/3)==16)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 15), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 16), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 17), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 24), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 25), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 26), candimoves.end());
        }
        else if((curset[i]/3)==17)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 15), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 16), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 17), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 24), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 25), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 26), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 48), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 49), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 50), candimoves.end());
        }
        candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), ((curset[i])/3)*3), candimoves.end());
        candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), ((curset[i]/3)*3+1)), candimoves.end());
        candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), ((curset[i]/3)*3+2)), candimoves.end());

        laxis=axis;
    }
    for (int j=0; j<candimoves.size(); j++)
    {
        vector < char > tempset=curset;
        tempset.push_back(candimoves[j]);
        thisone.push_back(tempset);
    }
}

void addLayersCustom(vector < char > curset, vector < vector < char > > &thisone, vector < char > candimoves)
{
    // allowedmoves: 1=6 gen, 2=6gen+Mr, 3=RUMr, 4=RUD, 5=RULD, 6=FURB, 7=MU, 8=U (algs), 9=MUD, 10=LUD;
    // 0 1 2 = U U2 U'      axis-0, /3=0
    // 3 4 5 = D            axis-0, /3=1
    // 6 7 8 = R            axis-1, /3=2
    // 9 10 11 = L          axis-1, /3=3
    // 12 13 14 = F         axis-2, /3=4
    // 15 16 17 = B         axis-2, /3=5
    // 18 19 20 = M         axis-1, /3=6
    // 21 22 23 = E         axis-0, /3=7
    // 24 25 26 = S         axis-2, /3=8
    // 36 37 38 = r         axis-1, /3=12
    // 39 40 41 = l         axis-1, /3=13
    // 42 43 44 = u         axis-0, /3=14
    // 45 46 47 = d         axis-0, /3=15
    // 48 49 50 = f         axis-2, /3=16
    // 51 52 53 = b         axis-2, /3=17
    char axis=10;
    char laxis=10;
    for (int i=curset.size()-1; i>=0; i--)
    {
        if ((curset[i]/3)==0)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
        }
        else if((curset[i]/3)==1)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
        }
        else if((curset[i]/3)==7)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 3), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 4), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 5), candimoves.end());
        }
        else if((curset[i]/3)==14)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 3), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 4), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 5), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 21), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 22), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 23), candimoves.end());
        }
        else if((curset[i]/3)==15)
        {
            axis=0;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 0), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 1), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 2), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 3), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 4), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 5), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 21), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 22), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 23), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 42), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 43), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 44), candimoves.end());
        }

        else if ((curset[i]/3)==2)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
        }
        else if((curset[i]/3)==3)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
        }
        else if((curset[i]/3)==6)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 9), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 10), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 11), candimoves.end());
        }
        else if((curset[i]/3)==12)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 9), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 10), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 11), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 18), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 19), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 20), candimoves.end());
        }
        else if((curset[i]/3)==13)
        {
            axis=1;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 6), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 7), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 8), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 9), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 10), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 11), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 18), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 19), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 20), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 36), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 37), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 38), candimoves.end());
        }

        if ((curset[i]/3)==4)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
        }
        else if((curset[i]/3)==5)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
        }
        else if((curset[i]/3)==8)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 15), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 16), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 17), candimoves.end());
        }
        else if((curset[i]/3)==16)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 15), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 16), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 17), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 24), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 25), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 26), candimoves.end());
        }
        else if((curset[i]/3)==17)
        {
            axis=2;
            if ((i<(curset.size()-1))&&(axis!=laxis)) break;
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 12), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 13), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 14), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 15), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 16), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 17), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 24), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 25), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 26), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 48), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 49), candimoves.end());
            candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), 50), candimoves.end());
        }
        candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), ((curset[i])/3)*3), candimoves.end());
        candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), ((curset[i]/3)*3+1)), candimoves.end());
        candimoves.erase(std::remove(candimoves.begin(), candimoves.end(), ((curset[i]/3)*3+2)), candimoves.end());

        laxis=axis;
    }
    for (int j=0; j<candimoves.size(); j++)
    {
        vector < char > tempset=curset;
        tempset.push_back(candimoves[j]);
        thisone.push_back(tempset);
    }
}

void EOfixer(void)
{
    for (int o=44; o>=0; o=o-4)
    {
        if (!((EO>>o)&0x02))
        {
            EO&=~((__int64) (0xf)<<o);
        }
    }
}

void cleanScrambler(void)
{
    cubeRevert(0);
    for (int i=0; i<wherretf.size(); i++)
    {
        vector <char> tempmoves=move2vec(wherretf[i][0]);
        for (int ij=0; ij<tempmoves.size(); ij++)
        {
            applyMove2(tempmoves[ij]);
        }
    }
    EOfixer();
    CN&=maskCNs1;
}


void unpruner(void)
{
    mapp0.clear();
    mapp1.clear();
    mapp2.clear();
    mapp3.clear();
    mapp4.clear();
    mapp5.clear();
    mapp6.clear();
    mapp7.clear();
    mapp8.clear();
    customsteps.clear();
    custommg.clear();
    algset="";
    customdets.clear();
    customall.clear();
    return;
}


void masks1(int method, int step)
{
    if (method==0) // cfop
    {
        if (step==0) // cross on D
        {
            currentstep="cross";
            maskEPs1=0x00000000ffff;
            maskEOs1=0x00000000ffff;
            maskCPs1=0x00000000;
            maskCOs1=0x00000000;
            maskCNs1=0x000;
        }
        if (step==1) // xcross on D, block at DFR
        {
            currentstep="xcross";
            maskEPs1=0x000000f0ffff;
            maskEOs1=0x000000f0ffff;
            maskCPs1=0x000000f0;
            maskCOs1=0x000000f0;
            maskCNs1=0x000;
        }

        /* if (step==2) // cfop pairs
         {
             currentstep="pair";
             maskEPs1=0x0000ffffffff;
             maskEOs1=0x0000ffffffff;
             maskCPs1=0x0000ffff;
             maskCOs1=0x0000ffff;
             maskCNs1=0xfff;

             for (int k=0; k<pairs.size(); k++)
             {
                     if (currentpair!=pairs[k])
                     {
                         maskEPs1&=~(0xf<<(12+pairs[k]*4));
                         maskEOs1&=~(0xf<<(12+pairs[k]*4));
                         maskCPs1&=~(0xf<<(pairs[k]*4-4));
                         maskCOs1&=~(0xf<<(pairs[k]*4-4));

                        // maskCPs1&=~(0xf<<((k*4)-4));
                       //  maskCOs1&=~(0xf<<((k*4)-4));

                     }
             }
         }*/


    }

    if (method==1) // petrus
    {
        if (step==0) // 2x2x2 at DLB
        {
            currentstep="2x2x2";
            maskEPs1=0x0000f000f00f;
            maskEOs1=0x0000f000f00f;
            maskCPs1=0x0000f000;
            maskCOs1=0x0000f000;
            maskCNs1=0xfff;
        }
        if (step==1) // 3x2x2 at DL
        {
            currentstep="3x2x2";
            maskEPs1=0x0000f00ff0ff;
            maskEOs1=0x0000f00ff0ff;
            maskCPs1=0x0000f00f;
            maskCOs1=0x0000f00f;
            maskCNs1=0xfff;
        }
        if (step==2) // eo
        {
            currentstep="eo";
            maskEPs1=0x0000f00ff0ff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0x0000f00f;
            maskCOs1=0x0000f00f;
            maskCNs1=0xfff;
        }
        if (step==3) // f2l
        {
            currentstep="f2l";
            maskEPs1=0x0000ffffffff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0x0000ffff;
            maskCOs1=0x0000ffff;
            maskCNs1=0xfff;
        }
        if (step==4) // zbll
        {
            currentstep="zbll";
            maskEPs1=0xffffffffffff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0xffffffff;
            maskCOs1=0xffffffff;
            maskCNs1=0xfff;
        }
    }

    if (method==2) // roux
    {
        if (step==0) // fb at DL
        {
            currentstep="fb";
            maskEPs1=0x0000f00f000f;
            maskEOs1=0x0000f00f000f;
            maskCPs1=0x0000f00f;
            maskCOs1=0x0000f00f;
            maskCNs1=0x0f0;
        }
        if (step==1) // sb at DR
        {
            currentstep="sb";
            maskEPs1=0x0000ffff0f0f;
            maskEOs1=0x0000ffff0f0f;
            maskCPs1=0x0000ffff;
            maskCOs1=0x0000ffff;
            maskCNs1=0x0f0;
        }
        if (step==3) // fs at DLB
        {
            currentstep="fs";
            maskEPs1=0x0000f000000f;
            maskEOs1=0x0000f000000f;
            maskCPs1=0x0000f000;
            maskCOs1=0x0000f000;
            maskCNs1=0x0f0;
        }

        if (step==4) //
        {
            currentstep="cmll";
            maskEPs1=0x0000ffff0f0f;
            maskEOs1=0x0000ffff0f0f;
            maskCPs1=0xffffffff;
            maskCOs1=0xffffffff;
            maskCNs1=0x0f0;
        }


        if (step==5) // LSE
        {
            currentstep="lse";
            maskEPs1=0xffffffffffff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0xffffffff;
            maskCOs1=0xffffffff;
            maskCNs1=0xfff;
        }
    }

    if (method==3) // zz
    {

        if (step==0) // eoline at D
        {
            currentstep="eoline";
            maskEPs1=0x00000000f0f0;
            maskEOs1=0xffffffffffff;
            maskCPs1=0x00000000;
            maskCOs1=0x00000000;
            maskCNs1=0xfff;
        }
        if (step==1) // eo3x2x2 at D
        {
            currentstep="eo3x2x2";
            maskEPs1=0x0000f00ff0ff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0x0000f00f;
            maskCOs1=0x0000f00f;
            maskCNs1=0xfff;
        }
        //     if (azzblockdone==0)
        //   {
        if (step==2) // lb
        {
            currentstep="lb";
            maskEPs1=0x0000f00ff0ff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0x0000f00f;
            maskCOs1=0x0000f00f;
            maskCNs1=0xfff;
        }

        if (step==3) // rb
        {
            currentstep="rb";
            maskEPs1=0x0000ffffffff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0x0000ffff;
            maskCOs1=0x0000ffff;
            maskCNs1=0xfff;
        }


        if (step==4) // zbll
        {
            currentstep="zbll";
            maskEPs1=0xffffffffffff;
            maskEOs1=0xffffffffffff;
            maskCPs1=0xffffffff;
            maskCOs1=0xffffffff;
            maskCNs1=0xfff;
        }
        //  }

    }

    if (method==4) // custom method
    {
        currentstep=customsteps[step];
        maskEPs1=customdets[step][3];
        maskEOs1=customdets[step][4];
        maskCPs1=customdets[step][5];
        maskCOs1=customdets[step][6];
        maskCNs1=customdets[step][7];
    }
}


void prunes12 (int depth, int method, int step, int allowedmoves)
{
    if (customdets[step][11]) EPs=customdets[step][11];
    if (customdets[step][12]) EOs=customdets[step][12];
    if (customdets[step][13]) CPs=customdets[step][13];
    if (customdets[step][14]) COs=customdets[step][14];
    if (customdets[step][15]) CNs=customdets[step][15];

    bool isalgset=0;
    string movestouse="";
    setups6gen2.clear();
    setups6gen2.push_back({});


    if (method==2 && step==4)
    {
        customdets[step][8]==1;
    }

    if (allowedmoves==8)
    {
        isalgset=1;
    }

    if (allowedmoves==99)
    {
        // create the custom move set vector here
        movestouse=custommg[step];
        string separated="";
        for (int qqq=0; qqq<movestouse.length(); qqq++)
        {
            separated+=string{movestouse[qqq]}+" "+string{movestouse[qqq]}+"2 "+string{movestouse[qqq]}+"' ";
        }
        vector < char > custommoveinset=move2vec(separated);

        // actually make the table
        if (depth>0)
        {
            int startat=0;
            for (int ii=1; ii<=depth; ii++)
            {
                int endat=setups6gen2.size();
                for (int i=startat; i<endat; i++)
                {
                    addLayersCustom(setups6gen2[i], setups6gen2, custommoveinset);
                }
                startat=endat;
            }
        }
    }

    else if (!isalgset)
    {
        if (depth>0)
        {
            int startat=0;
            for (int ii=1; ii<=depth; ii++)
            {
                int endat=setups6gen2.size();
                for (int i=startat; i<endat; i++)
                {
                    addLayers2(setups6gen2[i], setups6gen2, allowedmoves);
                }
                startat=endat;
            }
        }
    }
    else if (isalgset)
    {
        addLayers2(setups6gen2[0], setups6gen2, allowedmoves);
        for (int i=0; i<4; i++)
        {
            algparser(setups6gen2[i], setups6gen2, method);
        }
    }


    // switcheroo this too
    vector < char > premoves= {70};
    if (customdets[step][8]==1) // if Udisplacements permitted
    {
        premoves.push_back(0);
        premoves.push_back(1);
        premoves.push_back(2);
    }
    for (int p=0; p<premoves.size(); p++)
    {
        for (int i=0; i<setups6gen2.size(); i++)
        //for (int i=setups6gen2.size()-1; i>=0; i--)
        {
            cubeRevert(0);
            masks1(method, step);
            EP=EPs&maskEPs1;
            EO=EOs&maskEOs1;
            CP=CPs&maskCPs1;
            CO=COs&maskCOs1;
            CN=CNs;

            applyMove2(premoves[p]); // change this (and above) to do new premoves

            for (int m=0; m<setups6gen2[i].size(); m++)
            {
                applyMove2(setups6gen2[i][m]);
            }

            CN=CN&maskCNs1;
            EOfixer();
            Edge key (EP, EO, CP, CO, CN);

            if (step==0)
            {
                mapp0.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==1)
            {
                mapp1.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==2)
            {
                mapp2.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==3)
            {
                mapp3.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==4)
            {
                mapp4.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==5)
            {
                mapp5.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==6)
            {
                mapp6.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==7)
            {
                mapp7.insert(make_pair(key,setups6gen2[i]));
            }
            else if (step==8)
            {
                mapp8.insert(make_pair(key,setups6gen2[i]));
            }
        }

    }

    if (customdets[step][11]) EPs=0x123456789abc;
    if (customdets[step][12]) EOs=0x222222222222;
    if (customdets[step][13]) CPs=0x12345678;
    if (customdets[step][14]) COs=0x44444444;
    if (customdets[step][15]) CNs=0x123;

    cubeRevert(0);
}

bool iscpsolved(string soln, string k)
{
    cubeRevert(0);
    string thescramble="";
    if (stateset)
    {
        EP=EPi;
        EO=EOi;
        CP=CPi;
        CO=COi;
        CN=CNi;
    }
    else
    {
        for (int i=0; i<wherretf.size(); i++)
        {
            thescramble+=wherretf[i][0]+" ";
        }
    }
    thescramble+=soln;
    vector <char> tempmoves=move2vec(thescramble);
    for (int ij=0; ij<tempmoves.size(); ij++)
    {
        applyMove2(tempmoves[ij]);
    }

    if(find(cpdictionary.begin(), cpdictionary.end(), (CP&0xffff0ff0)) != cpdictionary.end())
    {
        return 1;
    }

    return 0;
}


bool iscpsolvedanal(string soln, string k, bool isanal, int hm, vector < vector <__int64> > &statelist)
{
    cubeRevert(0);
    string thescramble="";
    if (stateset)
    {
        EP=EPi;
        EO=EOi;
        CP=CPi;
        CO=COi;
        CN=CNi;
    }
    else if (isanal)
    {
        EP=statelist[hm][0];
        EO=statelist[hm][1];
        CP=statelist[hm][2];
        CO=statelist[hm][3];
        CN=statelist[hm][4];
    }
    else
    {
        for (int i=0; i<wherretf.size(); i++)
        {
            thescramble+=wherretf[i][0]+" ";
        }
    }
    thescramble+=soln;
    vector <char> tempmoves=move2vec(thescramble);
    for (int ij=0; ij<tempmoves.size(); ij++)
    {
        applyMove2(tempmoves[ij]);
    }

    if(find(cpdictionary.begin(), cpdictionary.end(), (CP&0xffff0ff0)) != cpdictionary.end())
    {
        return 1;
    }

    return 0;
}


bool checktables(EdgeMap &mapp, int i, int step, bool mirrorit, bool isfirst, int nom, vector < string > oris, vector < string > rots, int orr)
{
    Edge key (EP, EO, CP, CO, CN);
    if (mapp.find(key) != mapp.end())
    {
        pair <boost::unordered_multimap<Edge, vector < char > >::iterator,boost::unordered_multimap<Edge, vector < char > >::iterator> ret = mapp.equal_range(key);
        boost::unordered_multimap<Edge, vector < char > >::iterator it;
        for (it=ret.first; it!=ret.second; ++it)
        {
            vector < char > solfound0=(*it).second;
            string solfound = vec2move(solfound0);
            if (std::find(solutionsList.begin(), solutionsList.end(), solutionreducer(vec2move(solutionss12[i])+" "+moveReverse(solfound),step)) == solutionsList.end())
            {
                string soln=solutionreducer(vec2move(solutionss12[i])+" "+moveReverse(solfound),step);
                if (mirrorit)
                {
                    soln=y2rotator(soln);
                }
                if (isfirst)
                {
                    if ((customdets[step][9]==0) || ((customdets[step][9]==1) && iscpsolved(moveReverse(rots[orr])+soln,rots[orr])))
                    {
                        rotationsLog.push_back(moveReverse(rots[orr])+" ");
                        orientationsLog.push_back(oris[orr]);
                        solutionsLog.push_back(soln);
                        solutionsList.push_back(soln);
                        foundsolutions++;
                        cout<<"\n   " <<solutionsLog.size()<<".  "<<moveReverse(rots[orr])<< soln <<" ("<<std::dec<<countWords(soln)<<")\n";
                    }
                }
                else
                {
                    if ((customdets[step][9]==0) || ((customdets[step][9]==1) && iscpsolved(soln, rots[orr])))
                    {
                        solutionsLog.push_back(soln);
                        solutionsList.push_back(soln);
                        foundsolutions++;
                        cout<<"\n   " <<solutionsLog.size()<<".  "<< soln <<" ("<<std::dec<<countWords(soln)<<")\n";
                    }
                }
                if (foundsolutions==nom)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    return 0;
}



vector < char > analyzechecktables(EdgeMap &mapp, int i, int step, bool mirrorit, bool isfirst, int nom, vector < string > oris, vector < string > rots, int orr, int hm, vector <vector <__int64> > &statelist)
{
    Edge key (EP, EO, CP, CO, CN);
    if (mapp.find(key) != mapp.end())
    {
        pair <boost::unordered_multimap<Edge, vector < char > >::iterator,boost::unordered_multimap<Edge, vector < char > >::iterator> ret = mapp.equal_range(key);
        boost::unordered_multimap<Edge, vector < char > >::iterator it;
        for (it=ret.first; it!=ret.second; ++it)
        {
            vector < char > solfound0=(*it).second;
            string solfound = vec2move(solfound0);
            if (std::find(solutionsList.begin(), solutionsList.end(), solutionreducer(vec2move(solutionss12[i])+" "+moveReverse(solfound),step)) == solutionsList.end())
            {
                string soln=solutionreducer(vec2move(solutionss12[i])+" "+moveReverse(solfound),step);
                if (mirrorit)
                {
                    soln=y2rotator(soln);
                }
                if (isfirst)
                {
                    if ((customdets[step][9]==0) || ((customdets[step][9]==1) && iscpsolvedanal(moveReverse(rots[orr])+soln,rots[orr],1,hm,statelist)))
                    {
                        foundsolutions++;
                        cout<<"\n   " <<solutionsLog.size()<<".  "<<moveReverse(rots[orr])<< soln <<" ("<<std::dec<<countWords(soln)<<")\n";
                    }
                }
                else
                {
                    if ((customdets[step][9]==0) || ((customdets[step][9]==1) && iscpsolvedanal(soln, rots[orr],1,hm,statelist)))
                    {
                        foundsolutions++;
                        cout<<"\n   " <<solutionsLog.size()<<".  "<< soln <<" ("<<std::dec<<countWords(soln)<<")\n";
                    }
                }
                if (foundsolutions==nom)
                {
                    return move2vec(soln);
                }
                else
                {
                    return {'g'};
                }
            }
        }
    }
    return {'g'};
}



void solves12(int depth, int method, int step, int nom, vector < string > oris, vector < string > rots, int allowedmoves)
{
    solutionsLog.clear();
    rotationsLog.clear();
    orientationsLog.clear();
    string thescramble;
    bool isfirst=1;
    bool isalgset=0;
    mirrorit=0;


    if ((method==2)&&(step==4)) //remove correctional AUF if it's LSE for roux method
    {
        customdets[step][8]=1;
    }


    for (int i=0; i<wherretf.size(); i++)
    {
        thescramble=thescramble+wherretf[i][0]+" ";
    }

    if (!(usedrotation.empty()))
    {
        rots.clear();
        rots.push_back(moveReverse(usedrotation));
        oris.clear();
        oris.push_back(usedorientation);
        isfirst=0;
    }
    for (int orr=0; orr<rots.size(); orr++)
    {
        auto t1 = Clock::now();
        cubeRevert(0);
        vector <char> tempmoves=move2vec(trim(moveReverse(rots[orr])));
        for (int ij=0; ij<tempmoves.size(); ij++)
        {
            applyMove2(tempmoves[ij]);
        }

        cpdictionary.clear();
        cpdictionary.push_back(CP&0xffff0ff0);
        if (customdets[step][9]==1)
        {
            bool startR=0;
            int dire=0;
            while (cpdictionary.size()<120)
            {
                dire=rand()%3;
                if (dire==0)
                {
                    if (startR)
                    {
                        applyMove2(0);
                    }
                    else if (!startR)
                    {
                        applyMove2(6);
                    }
                }
                else if (dire==1)
                {
                    if (startR)
                    {
                        applyMove2(1);
                    }
                    else if (!startR)
                    {
                        applyMove2(7);
                    }
                }
                else if (dire==2)
                {
                    if (startR)
                    {
                        applyMove2(2);
                    }
                    else if (!startR)
                    {
                        applyMove2(8);
                    }
                }
                startR=!startR;
                if(find(cpdictionary.begin(), cpdictionary.end(), (CP&0xffff0ff0)) == cpdictionary.end())
                {
                    cpdictionary.push_back(CP&0xffff0ff0);
                }
            }
        }


        bool nomore=0;
        string thenewscramble;
        solutionsList.clear();
        if (isfirst)
        {
            thenewscramble=rots[orr]+" "+thescramble+" "+moveReverse(rots[orr]);
        }
        else
        {
            thenewscramble=rots[orr]+" "+thescramble+" ";
        }

        if (!lbdone && !rbdone && method==3 && step==3)
        {
            step=2;
            mirrorit=1;
            thenewscramble= "y2 " + thenewscramble + " y2";

        }

        if (!lbdone && rbdone && method==3 && step==2)
        {
            step=3;
            mirrorit=1;
            thenewscramble= "y2 " + thenewscramble + " y2";
        }

        cubeRevert(0);
        masks1(method,step);

        cout<<"\n"<<oris[orr]<<" - "<<currentstep<<":"<<endl;


        EP=EPs&maskEPs1;
        EO=EOs&maskEOs1;
        CP=CPs&maskCPs1;
        CO=COs&maskCOs1;
        CN=CNs;

        if (customdets[step][11]) EP=EPs;
        if (customdets[step][12]) EO=EOs;
        if (customdets[step][13]) CP=CPs;
        if (customdets[step][14]) CO=COs;
        if (customdets[step][15]) CN=CNs;

        //mask the unscrambled cube
        tempmoves=move2vec(thenewscramble);
        for (int ij=0; ij<tempmoves.size(); ij++)
        {
            applyMove2(tempmoves[ij]);
        }

        if (stateset)
        {

            if (oris[orr]!="UF")
            {
                cout<<"\n   No alternate orientations on set states. Set rotated state instead.\n\n";
                return;
            }
            else
            {
                EP=EPi&hexparse(1,EPi,maskEPs1,rots[orr]);
                EO=EOi&hexparse(1,EPi,maskEOs1,rots[orr]);
                CP=CPi&hexparse(2,CPi,maskCPs1,rots[orr]);
                CO=COi&hexparse(2,CPi,maskCOs1,rots[orr]);
                CN=CNi&hexparse(3,CNi,maskCNs1,rots[orr]);
            }
        }

        if (customdets[step][11]) EPs=customdets[step][11];
        if (customdets[step][11]) EP=EP&hexparse(1,EP,maskEPs1,rots[orr]);
        if (customdets[step][12]) EOs=customdets[step][12];
        if (customdets[step][12]) EO=EO&hexparse(1,EP,maskEOs1,rots[orr]);
        if (customdets[step][13]) CPs=customdets[step][13];
        if (customdets[step][13]) CP=CP&hexparse(2,CP,maskCPs1,rots[orr]);
        if (customdets[step][14]) COs=customdets[step][14];
        if (customdets[step][14]) CO=CO&hexparse(2,CP,maskCOs1,rots[orr]);
        if (customdets[step][15]) CNs=customdets[step][15];
        if (customdets[step][15]) CN=CN&hexparse(3,CN,maskCNs1,rots[orr]);

        EOfixer();

        EPb=EP;
        EOb=EO;
        CPb=CP;
        COb=CO;
        CNb=CN;


        string movestouse=""; // can kill temporarily
        solutionss12.clear();
        solutionss12.push_back({});


        if (allowedmoves==99)
        {
            // create the custom move set vector here
            movestouse=custommg[step];
            string separated="";
            for (int qqq=0; qqq<movestouse.length(); qqq++)
            {
                separated+=string{movestouse[qqq]}+" "+string{movestouse[qqq]}+"2 "+string{movestouse[qqq]}+"' ";
            }
            vector < char > custommoveinset=move2vec(separated);

            // actually make the table
            if (depth>0)
            {
                int startat=0;
                for (int ii=1; ii<=depth; ii++)
                {
                    int endat=solutionss12.size();
                    for (int i=startat; i<endat; i++)
                    {
                        addLayersCustom(solutionss12[i], solutionss12, custommoveinset);
                    }
                    startat=endat;
                }
            }
        }
        else if (!isalgset)
        {
            //insert hypermolding here

            if (depth>0)
            {
                int startat=0;
                for (int ii=1; ii<=depth; ii++)
                {
                    int endat=solutionss12.size();
                    for (int i=startat; i<endat; i++)
                    {
                        addLayers2(solutionss12[i], solutionss12, allowedmoves);
                    }
                    startat=endat;
                }
            }
        }

        foundsolutions=0;
        for (int ee=0; ee<solutionss12.size(); ee++)
        {
            EP=EPb;
            EO=EOb;
            CP=CPb;
            CO=COb;
            CN=CNb;

            for (int m=0; m<solutionss12[ee].size(); m++)
            {
                applyMove2(solutionss12[ee][m]);
            }

            CN=CN&maskCNs1;
            EOfixer();

            //check the prune table to see if that sequence puts you on it
            //Edge key (EP, EO, CP, CO, CN);

            if (step==0)
            {
                nomore=checktables(mapp0,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==1)
            {
                nomore=checktables(mapp1,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==2)
            {
                nomore=checktables(mapp2,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==3)
            {
                nomore=checktables(mapp3,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==4)
            {
                nomore=checktables(mapp4,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==5)
            {
                nomore=checktables(mapp5,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==6)
            {
                nomore=checktables(mapp6,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==7)
            {
                nomore=checktables(mapp7,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            else if (step==8)
            {
                nomore=checktables(mapp8,ee,step,mirrorit,isfirst,nom,oris,rots,orr);
            }
            if (nomore)
            {

                break;
            }
        }
        auto t2 = Clock::now();
        if (!foundsolutions)
        {
            cout<<"\n   no solutions found within search depth in prescribed movegroup in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms\n\n";
        }
        else if (foundsolutions<nom)
        {
            cout<<"\n   only "<<foundsolutions<<" solution(s) found in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms\n\n";
        }
        else
        {
            cout<<"\n   "<<nom<<" solution(s) generated in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms\n\n";
        }
    }
    if (customdets[step][11]) EPs=0x123456789abc;
    if (customdets[step][12]) EOs=0x222222222222;
    if (customdets[step][13]) CPs=0x12345678;
    if (customdets[step][14]) COs=0x44444444;
    if (customdets[step][15]) CNs=0x123;
    cleanScrambler();
}

void printSquares(int n)
{
    cout.clear();
    for (int i=0; i<n; i++)
    {
        cout<<"#";
    }
    cout.setstate(ios_base::failbit);
}



vector < vector <__int64> > analyze12(int depth, int method, int step, int nom, vector < string > oris, vector < string > rots, int allowedmoves, vector < vector <__int64> > &statelist, bool firstdo)
{
    solutionsLog.clear();
    rotationsLog.clear();
    orientationsLog.clear();
    string thescramble;
    bool isfirst=1;
    bool isalgset=0;
    mirrorit=0;

    if ((method==2)&&(step==4)) //remove correctional AUF if it's LSE for roux method
    {
        customdets[step][8]=1;
    }


    for (int i=0; i<wherretf.size(); i++)
    {
        thescramble=thescramble+wherretf[i][0]+" ";
    }

    if (!(usedrotation.empty()))
    {
        rots.clear();
        rots.push_back(moveReverse(usedrotation));
        oris.clear();
        oris.push_back(usedorientation);
        isfirst=0;
    }
    for (int orr=0; orr<rots.size(); orr++)
    {
        cubeRevert(0);
        vector <char> tempmoves=move2vec(trim(moveReverse(rots[orr])));
        for (int ij=0; ij<tempmoves.size(); ij++)
        {
            applyMove2(tempmoves[ij]);
        }

        cpdictionary.clear();
        cpdictionary.push_back(CP&0xffff0ff0);
        if (customdets[step][9]==1)
        {
            bool startR=0;
            int dire=0;
            while (cpdictionary.size()<120)
            {
                dire=rand()%3;
                if (dire==0)
                {
                    if (startR)
                    {
                        applyMove2(0);
                    }
                    else if (!startR)
                    {
                        applyMove2(6);
                    }
                }
                else if (dire==1)
                {
                    if (startR)
                    {
                        applyMove2(1);
                    }
                    else if (!startR)
                    {
                        applyMove2(7);
                    }
                }
                else if (dire==2)
                {
                    if (startR)
                    {
                        applyMove2(2);
                    }
                    else if (!startR)
                    {
                        applyMove2(8);
                    }
                }
                startR=!startR;
                if(find(cpdictionary.begin(), cpdictionary.end(), (CP&0xffff0ff0)) == cpdictionary.end())
                {
                    cpdictionary.push_back(CP&0xffff0ff0);
                }
            }
        }


        vector <char> nomore;
        string thenewscramble;
        solutionsList.clear();
        if (isfirst)
        {
            thenewscramble=rots[orr]+" "+thescramble+" "+moveReverse(rots[orr]);
        }
        else
        {
            thenewscramble=rots[orr]+" "+thescramble+" ";
        }

        cubeRevert(0);
        masks1(method,step);

        cout<<"\n"<<oris[orr]<<" - "<<currentstep<<":"<<endl;


        EP=EPs&maskEPs1;
        EO=EOs&maskEOs1;
        CP=CPs&maskCPs1;
        CO=COs&maskCOs1;
        CN=CNs;

        if (customdets[step][11]) EP=EPs;
        if (customdets[step][12]) EO=EOs;
        if (customdets[step][13]) CP=CPs;
        if (customdets[step][14]) CO=COs;
        if (customdets[step][15]) CN=CNs;

        //mask the unscrambled cube
        tempmoves=move2vec(thenewscramble);
        for (int ij=0; ij<tempmoves.size(); ij++)
        {
            applyMove2(tempmoves[ij]);
        }

        if (stateset)
        {

            if (oris[orr]!="UF")
            {
                cout<<"\n   No alternate orientations on set states. Set rotated state instead.\n\n";
                break;
            }
            else
            {
                EP=EPi&hexparse(1,EPi,maskEPs1,rots[orr]);
                EO=EOi&hexparse(1,EPi,maskEOs1,rots[orr]);
                CP=CPi&hexparse(2,CPi,maskCPs1,rots[orr]);
                CO=COi&hexparse(2,CPi,maskCOs1,rots[orr]);
                CN=CNi&hexparse(3,CNi,maskCNs1,rots[orr]);
            }
        }

        if (customdets[step][11]) EPs=customdets[step][11];
        if (customdets[step][11]) EP=EP&hexparse(1,EP,maskEPs1,rots[orr]);
        if (customdets[step][12]) EOs=customdets[step][12];
        if (customdets[step][12]) EO=EO&hexparse(1,EP,maskEOs1,rots[orr]);
        if (customdets[step][13]) CPs=customdets[step][13];
        if (customdets[step][13]) CP=CP&hexparse(2,CP,maskCPs1,rots[orr]);
        if (customdets[step][14]) COs=customdets[step][14];
        if (customdets[step][14]) CO=CO&hexparse(2,CP,maskCOs1,rots[orr]);
        if (customdets[step][15]) CNs=customdets[step][15];
        if (customdets[step][15]) CN=CN&hexparse(3,CN,maskCNs1,rots[orr]);

        EOfixer();

        EPb=EP;
        EOb=EO;
        CPb=CP;
        COb=CO;
        CNb=CN;


        string movestouse=""; // can kill temporarily
        solutionss12.clear();
        solutionss12.push_back({});


        if (allowedmoves==99)
        {
            // create the custom move set vector here
            movestouse=custommg[step];
            string separated="";
            for (int qqq=0; qqq<movestouse.length(); qqq++)
            {
                separated+=string{movestouse[qqq]}+" "+string{movestouse[qqq]}+"2 "+string{movestouse[qqq]}+"' ";
            }
            vector < char > custommoveinset=move2vec(separated);

            // actually make the table
            if (depth>0)
            {
                int startat=0;
                for (int ii=1; ii<=depth; ii++)
                {
                    int endat=solutionss12.size();
                    for (int i=startat; i<endat; i++)
                    {
                        addLayersCustom(solutionss12[i], solutionss12, custommoveinset);
                    }
                    startat=endat;
                }
            }
        }
        else if (!isalgset)
        {
            //insert hypermolding here

            if (depth>0)
            {
                int startat=0;
                for (int ii=1; ii<=depth; ii++)
                {
                    int endat=solutionss12.size();
                    for (int i=startat; i<endat; i++)
                    {
                        addLayers2(solutionss12[i], solutionss12, allowedmoves);
                    }
                    startat=endat;
                }
            }
        }

        for (int hm=0; hm<statelist.size(); hm++)
        {
            foundsolutions=0;

            for (int ee=0; ee<solutionss12.size(); ee++)
            {

            EP=statelist[hm][0]&hexparse(1,statelist[hm][0],maskEPs1,rots[orr]);
            EO=statelist[hm][1]&hexparse(1,statelist[hm][0],maskEOs1,rots[orr]);
            CP=statelist[hm][2]&hexparse(2,statelist[hm][2],maskCPs1,rots[orr]);
            CO=statelist[hm][3]&hexparse(2,statelist[hm][2],maskCOs1,rots[orr]);
            //CN=statelist[hm][4]&hexparse(3,statelist[hm][4],maskCNs1,rots[orr]);
            CN=statelist[hm][4]&maskCNs1; // non me ne frega niente

                for (int m=0; m<solutionss12[ee].size(); m++)
                {
                    applyMove2(solutionss12[ee][m]);
                }

                CN=CN&maskCNs1;
                EOfixer();

                //check the prune table to see if that sequence puts you on it
                //Edge key (EP, EO, CP, CO, CN);

                if (step==0)
                {
                    nomore=analyzechecktables(mapp0,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==1)
                {
                    nomore=analyzechecktables(mapp1,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==2)
                {
                    nomore=analyzechecktables(mapp2,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==3)
                {
                    nomore=analyzechecktables(mapp3,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==4)
                {
                    nomore=analyzechecktables(mapp4,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==5)
                {
                    nomore=analyzechecktables(mapp5,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==6)
                {
                    nomore=analyzechecktables(mapp6,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==7)
                {
                    nomore=analyzechecktables(mapp7,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                else if (step==8)
                {
                    nomore=analyzechecktables(mapp8,ee,step,mirrorit,isfirst,nom,oris,rots,orr,hm,statelist);
                }
                if (nomore.size()==0)
                {
                    break;
                }
                if (nomore[0]!='g')
                 {
                     break;
                 }
            }
            if (foundsolutions<nom)
            {
                cout.clear();
                EP=statelist[hm][0];
                EO=statelist[hm][1];
                CP=statelist[hm][2];
                CO=statelist[hm][3];
                CN=statelist[hm][4];
                showCube();
                cout<<"\n   Fail thrown in step "<<step<<"+1. Insufficient depth likely.\n\n";
                cout<<"   Press return to continue.\n\n";
                getchar();
                cout.setstate(ios_base::failbit);
            }
            statelist[hm][5]=countWords(vec2move(nomore));
            EP=statelist[hm][0];
            EO=statelist[hm][1];
            CP=statelist[hm][2];
            CO=statelist[hm][3];
            CN=statelist[hm][4];
            if (nomore.size()>0)
            {
                for (int mov=0; mov<nomore.size(); mov++)
                {
                    applyMove2(nomore[mov]);
                }
            }
            statelist[hm][0]=EP;
            statelist[hm][1]=EO;
            statelist[hm][2]=CP;
            statelist[hm][3]=CO;
            statelist[hm][4]=CN;

            printSquares(int(floor(12*(float(hm)+float(statelist.size()*nostep))/float(nosteps*statelist.size())))-squares);
            squares=int(floor(12*(float(hm)+float(statelist.size()*nostep))/float(nosteps*statelist.size())));
        }
    }
    if (customdets[step][11]) EPs=0x123456789abc;
    if (customdets[step][12]) EOs=0x222222222222;
    if (customdets[step][13]) CPs=0x12345678;
    if (customdets[step][14]) COs=0x44444444;
    if (customdets[step][15]) CNs=0x123;

    return statelist;
}

void customparser(void)
{
    auto t1 = Clock::now();
    ifstream infile("custom.txt");
    int stepnumber=-1;
    for( string line; getline( infile, line ); )
    {
        string sss;
        bool isstep=0;
        bool ismg=0;
        bool ispd=0;
        bool issd=0;
        bool isep=0;
        bool iseo=0;
        bool iscp=0;
        bool isco=0;
        bool iscn=0;
        bool isall=0;
        bool isas=0;
        bool iseps=0;
        bool iseos=0;
        bool iscps=0;
        bool iscos=0;
        bool iscns=0;
        int commandnumber=1;
        stringstream comma(line);
        while (comma >> sss)
        {
            if (isall)
            {
                customall.push_back(sss.c_str());
            }
            if (commandnumber==2 && isall==0)
            {
                if (isstep)
                {
                    customsteps[stepnumber]=sss.c_str();
                    isstep=0;
                }
                else if (isas)
                {
                    customdets[stepnumber][10]=1;
                    customdets[stepnumber][0]=8;
                    customdets[stepnumber][1]=1;
                    customdets[stepnumber][2]=1;
                    algset=sss.c_str();
                }
                else if (ismg && sss[0]=='<')
                {
                    customdets[stepnumber][0]=99;
                    custommg[stepnumber]=sss.substr(1, sss.size()-2);
                    ismg=0;
                }
                else
                {
                    __int64 x;
                    stringstream tohex;
                    tohex<<std::hex<<sss;
                    tohex>>x;
                    if (ismg)
                    {
                        customdets[stepnumber][0]=x;
                        ismg=0;
                    }
                    if (ispd)
                    {
                        stringstream todec;
                        todec<<std::dec<<sss;
                        todec>>x;
                        customdets[stepnumber][1]=x;
                        ispd=0;
                    }
                    if (issd)
                    {
                        stringstream todec;
                        todec<<std::dec<<sss;
                        todec>>x;
                        customdets[stepnumber][2]=x;
                        issd=0;
                    }
                    if (isep)
                    {
                        customdets[stepnumber][3]=x;
                        isep=0;
                    }
                    if (iseo)
                    {
                        customdets[stepnumber][4]=x;
                        iseo=0;
                    }
                    if (iscp)
                    {
                        customdets[stepnumber][5]=x;
                        iscp=0;
                    }
                    if (isco)
                    {
                        customdets[stepnumber][6]=x;
                        isco=0;
                    }
                    if (iscn)
                    {
                        customdets[stepnumber][7]=x;
                        iscn=0;
                    }
                    if (iseps)
                    {
                        customdets[stepnumber][11]=x;
                        iseps=0;
                    }
                    if (iseos)
                    {
                        customdets[stepnumber][12]=x;
                        iseos=0;
                    }
                    if (iscps)
                    {
                        customdets[stepnumber][13]=x;
                        iscps=0;
                    }
                    if (iscos)
                    {
                        customdets[stepnumber][14]=x;
                        iscos=0;
                    }
                    if (iscns)
                    {
                        customdets[stepnumber][15]=x;
                        iscns=0;
                    }
                    commandnumber++;
                }
            }
            if (commandnumber==1)
            {
                if (sss=="step")
                {
                    isstep=1;
                    stepnumber++;
                }
                if (sss=="movegroup")
                {
                    ismg=1;
                }
                if (sss=="prunedepth")
                {
                    ispd=1;
                }
                if (sss=="searchdepth")
                {
                    issd=1;
                }
                if (sss=="epmask")
                {
                    isep=1;
                }
                if (sss=="eomask")
                {
                    iseo=1;
                }
                if (sss=="cpmask")
                {
                    iscp=1;
                }
                if (sss=="comask")
                {
                    isco=1;
                }
                if (sss=="cnmask")
                {
                    iscn=1;
                }
                if (sss=="eps")
                {
                    iseps=1;
                }
                if (sss=="eos")
                {
                    iseos=1;
                }
                if (sss=="cps")
                {
                    iscps=1;
                }
                if (sss=="cos")
                {
                    iscos=1;
                }
                if (sss=="cns")
                {
                    iscns=1;
                }
                if (sss=="Udisplacement")
                {
                    customdets[stepnumber][8]=1;
                }
                if (sss=="2genreduction")
                {
                    customdets[stepnumber][9]=1;
                }
                if (sss=="algset")
                {
                    isas=1;
                }
                if (sss=="all")
                {
                    isall=1;
                }
                commandnumber++;
            }
        }
    }
    cout<<"\n   Loaded";
    for (int stepgo=0; stepgo<customsteps.size(); stepgo++)
    {
        if (customsteps[stepgo]!="")
        {
            cout<<" "<<customsteps[stepgo]<<",";
            prunes12(customdets[stepgo][1],4,stepgo,customdets[stepgo][0]);
        }
    }
    auto t2 = Clock::now();
    cout<<" in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms\n\n";
}


bool executecommand(string comma, int nom, vector < string > oris, vector < string > rots)
{
    bool firstdo=1;
    if (comma=="all")
    {
        auto t1 = Clock::now();
        for (int j=0; j<customall.size(); j++)
        {
            for (int i=0; i<customsteps.size(); i++)
            {

                if (customall[j]==customsteps[i])
                {
                    solves12(customdets[i][2],4,i,1,oris,rots,customdets[i][0]);
                    firstdo=dosomething(0,1," ",firstdo);
                }
            }
        }
        auto t2 = Clock::now();
        cout<<"\n   stepwise-optimal custom solution applied in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n\n";

        return 0;
    }
    else
    {
        for (int i=0; i<customsteps.size(); i++)
        {
            if (comma==customsteps[i])
            {
                solves12(customdets[i][2],4,i,nom,oris,rots,customdets[i][0]);
                return 0;
            }
        }
    }
    return 1;
}


bool isPossibleState(__int64 tEP, __int64 tCP)
{
    bool good=1;
    for (int q=1; q<=12; q++)
    {
        if (q!=((tEP&(((__int64)0xf)<<(48-q*4)))>>(48-q*4)))
        {
            for (int w=q+1; w<=12; w++)
            {
                if (q==((tEP&(((__int64)0xf)<<(48-w*4)))>>(48-w*4)))
                {
                    tEP=tEP&(~(((__int64)0xf)<<(48-w*4)))|(((__int64)((tEP&(((__int64)0xf)<<(48-q*4)))>>(48-q*4)))<<(48-w*4));
                    tEP=tEP&(~(((__int64)0xf)<<(48-q*4)))|(((__int64)q)<<(48-q*4));
                    good=!good;
                }
            }
        }
    }
    for (int q=1; q<=8; q++)
    {
        if (q!=((tCP&(((__int64)0xf)<<(32-q*4)))>>(32-q*4)))
        {
            for (int w=q+1; w<=8; w++)
            {
                if (q==((tCP&(((__int64)0xf)<<(32-w*4)))>>(32-w*4)))
                {
                    tCP=tCP&(~(((__int64)0xf)<<(32-w*4)))|(((__int64)((tCP&(((__int64)0xf)<<(32-q*4)))>>(32-q*4)))<<(32-w*4));
                    tCP=tCP&(~(((__int64)0xf)<<(32-q*4)))|(((__int64)q)<<(32-q*4));
                    good=!good;
                }
            }
        }
    }
    return good;
}


vector <__int64> randomizer2()
{
    __int64 cEP=0;
    __int64 cEO=0;
    __int64 cCP=0;
    __int64 cCO=0;
    __int64 cCN=0;
    vector <int> bco={4,6,5};
    int tt=0;
    int gg=0;
    for (int i=0; i<11; i++)
    {
        tt=rand()%2;
        gg+=tt;
        cEO|=((__int64)(tt+2)<<(44-4*i));
    }
    cEO|=2+(gg%2);

    gg=0;
    for (int i=0; i<7; i++)
    {
        tt=rand()%3;
        gg+=tt;
        cCO|=((__int64)(tt+4)<<(28-4*i));
    }
    cCO|=bco[gg%3];

    vector <int> candiE={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc};
    vector <int> candiC={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8};
    for (int i=0; i<12; i++)
    {
        tt=rand()%candiE.size();
        gg=candiE[tt];
        cEP|=((__int64)(gg)<<(44-4*i));
        candiE.erase(std::remove(candiE.begin(), candiE.end(), gg), candiE.end());
    }
    for (int i=0; i<8; i++)
    {
        tt=rand()%candiC.size();
        gg=candiC[tt];
        cCP|=((__int64)(gg)<<(28-4*i));
        candiC.erase(std::remove(candiC.begin(), candiC.end(), gg), candiC.end());
    }

    while(!isPossibleState(cEP,cCP))
    {
        candiE={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc};
        candiC={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8};
        cEP=0;
        cCP=0;
        for (int i=0; i<12; i++)
        {
            tt=rand()%candiE.size();
            gg=candiE[tt];
            cEP|=((__int64)(gg)<<(44-4*i));
            candiE.erase(std::remove(candiE.begin(), candiE.end(), gg), candiE.end());
        }
        for (int i=0; i<8; i++)
        {
            tt=rand()%candiC.size();
            gg=candiC[tt];
            cCP|=((__int64)(gg)<<(28-4*i));
            candiC.erase(std::remove(candiC.begin(), candiC.end(), gg), candiC.end());
        }
    }
    cCN=0x123;
    //std::cout<<std::hex<<cEO<<" "<<cCO<<" "<<cEP<<" "<<cCP<<" "<<cCN<<endl;
    //std::cout<<isPossibleState(cEP,cCP)<<endl;
    return {cEP, cEO, cCP, cCO, cCN};
}




void printStats(vector < vector < int > > statistics, vector < string > steps)
{
    int quantity=statistics.size();
    float totalmax,totalmin,totalmean;
    float allmin = 999;
    float allmax = 0;
    cout<<"\n\tSOLVES: "<<quantity;
    for (int k=0; k<quantity; k++)
    {
        float acc = 0;
        for (int o=0; o<steps.size(); o++)
        {
            acc+=float(statistics[k][o]);
        }
        if (acc>allmax)
            allmax = acc;
        if (acc<allmin)
            allmin = acc;
    }
    cout<<"\n\n\tLEAST MOVES:\t"<<allmin<<"\n\tMOST MOVES:\t"<<allmax;

    cout<<"\n\n\tSTEP\t\tMEAN\t\tBEST\t\tWORST";
    for (int o=0; o<steps.size(); o++)
    {
        float acc = 0;
        float maximum = 0;
        float minimum = 999;
        for (int k=0; k<quantity; k++)
        {
            acc+=float(statistics[k][o]);
            //std::cout<<acc<<std::endl;
            if (float(statistics[k][o])>maximum)
                maximum = float(statistics[k][o]);
            if (float(statistics[k][o])<minimum)
                minimum = float(statistics[k][o]);
        }
        cout<<"\n\t"<<steps[o]<<"\t\t"<<acc/float(quantity)<<"\t\t"<<minimum<<"\t\t"<<maximum;
        totalmax+=maximum;
        totalmin+=minimum;
        totalmean+=acc/float(quantity);
    }
    cout<<"\n\tTOTAL\t\t"<<totalmean<<"\t\t"<<totalmin<<"\t\t"<<totalmax<<"\n\n";
}

void savedata(vector < vector <__int64> > &states, vector < vector <int> > &stats, int stepnumber)
{
    for (int i=0; i<states.size(); i++)
        {
            stats[i][stepnumber]=states[i][5];
        }
    return;
}


void analyze(int quantity, int prunedmethod, vector < string > orientations, vector < string > rotations)
{

// put it in the default orientation only

vector < vector <__int64> > statelist(quantity, vector <__int64> (6));

    scramblesave.clear();
    for (int i=0;i<quantity;i++)
    {
        cubeRevert(1);

        vector <__int64> randos=randomizer2();

        statelist[i][0]=randos[0];
        statelist[i][1]=randos[1];
        statelist[i][2]=randos[2];
        statelist[i][3]=randos[3];
        statelist[i][4]=randos[4];



    }

    if (prunedmethod==4)
    {
        auto t1 = Clock::now();
        cout<<"\n\t|ANALYZING...|\n\t|";
        vector < vector < int > > statistics(quantity, vector < int > (customall.size()));
        vector < string > steps(customall.size());
        squares=0;
        nostep=0;
        nosteps=customall.size();
        cout.setstate(ios_base::failbit);
        bool firstdo=1;
        for (int ii=0; ii<customall.size(); ii++)
        {
            nostep=ii;
            for (int i=0; i<customsteps.size(); i++)
            {
                if (customall[ii]==customsteps[i])
                {
                    statelist=analyze12(customdets[i][2],4,i,1,orientations,rotations,customdets[i][0],statelist,firstdo);
                    savedata(statelist,statistics,nostep);
                    firstdo=0;
                    steps[ii]=customsteps[i];
                }
            }
        }

        cout.clear();
        printSquares(12-squares);
        cout.clear();
        auto t2 = Clock::now();
        cout<<"|\t"<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms"<<std::endl;;
        printStats(statistics,steps);
    }
    else if (prunedmethod!=1&&prunedmethod!=2&&prunedmethod!=3)
    {
        cout<<"\n   must be pruned for petrus/roux/zz/custom\n\n";
    }
    else
    {
        auto t1 = Clock::now();
        cout<<"\n\t|ANALYZING...|\n\t|";
        vector < vector < int > > statistics(quantity, vector < int > (4));
        vector < string > steps(4);
        squares=0;
        nostep=0;
        nosteps=4;
        cout.setstate(ios_base::failbit);
        if (prunedmethod==1) // petrus
        {
            statelist=analyze12(6,1,1,1,orientations,rotations,1,statelist,1);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(5,1,2,1,orientations,rotations,6,statelist,0);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(7,1,3,1,orientations,rotations,4,statelist,0);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(1,1,4,1,orientations,rotations,8,statelist,0);
            savedata(statelist,statistics,nostep);
            steps = {"3x2x2","eo","f2l","zbll"};
        }
        if (prunedmethod==2) // roux
        {
            statelist=analyze12(5,2,0,1,orientations,rotations,2,statelist,1);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(7,2,1,1,orientations,rotations,3,statelist,0);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(1,2,4,1,orientations,rotations,8,statelist,0);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(10,2,5,1,orientations,rotations,7,statelist,0);
            savedata(statelist,statistics,nostep);
            steps = {"fb","sb","cmll","lse"};
        }
        if (prunedmethod==3) // zz
        {
            statelist=analyze12(5,3,0,1,orientations,rotations,1,statelist,1);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(6,3,2,1,orientations,rotations,5,statelist,0);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(7,3,3,1,orientations,rotations,4,statelist,0);
            savedata(statelist,statistics,nostep);
            nostep++;
            statelist=analyze12(1,3,4,1,orientations,rotations,8,statelist,0);
            savedata(statelist,statistics,nostep);
            steps = {"eoline","lb","rb","zbll"};
        }
        cout.clear();

    printSquares(12-squares);
    cout.clear();
    auto t2 = Clock::now();
    cout<<"|\t"<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms"<<std::endl;;
    printStats(statistics,steps);
    }

}
