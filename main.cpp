#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;
typedef int in;
//#define int short
#define ll unsigned long long
#define pb push_back
#define pp push
#define f first
#define s second
int xx1,yy1,xx2,yy2;
int pawnpos[8][8]={0,   0,   0,   0,   0,   0,   0,   0,
50,  50,  50,  50,  50,  50,  50,  50,
10,  10,  20,  30,  30,  20,  10,  10,
5,   5,  10,  25,  25,  10,   5,   5,
0,   0,   0,  20,  20,   0,   0,   0,
5,  -5, -10,   0,   0, -10,  -5,   5,
5,  10,  10, -20, -20,  10,  10,   5,
0,   0,   0,   0,   0,   0,   0,   0};
int pawnposend[8][8]={0,   0,   0,   0,   0,   0,   0,   0,
80,  80,  80,  80,  80,  80,  80,  80,
50,  50,  50,  50,  50,  50,  50,  50,
30,  30,  30,  30,  30,  30,  30,  30,
20,  20,  20,  20,  20,  20,  20,  20,
10,  10,  10,  10,  10,  10,  10,  10,
10,  10,  10,  10,  10,  10,  10,  10,
0,   0,   0,   0,   0,   0,   0,   0};
int rookpos[8][8]={0,  0,  0,  0,  0,  0,  0,  0,
10, 15, 15, 15, 15, 15, 15,  10,
5,  5,  5,  5,  5,  5,  5, 5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
0,  0,  0,  5,  5,  0,  0,  0};
int knightpos[8][8]={-50,-40,-30,-30,-30,-30,-40,-50,
-40,-20,  0,  0,  0,  0,-20,-40,
-30,  0, 10, 15, 15, 10,  0,-30,
-30,  5, 15, 20, 20, 15,  5,-30,
-30,  0, 15, 20, 20, 15,  0,-30,
-30,  5, 10, 15, 15, 10,  5,-30,
-40,-20,  -10,  -5,  -5,  -10,-20,-40,
-50,-40,-30,-30,-30,-30,-40,-50};
int bishoppos[8][8]={-20,-10,-10,-10,-10,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5, 10, 10,  5,  0,-10,
-10,  5,  5, 10, 10,  5,  5,-10,
-10,  0, 10, 10, 10, 10,  0,-10,
-10, 10, 10, 10, 10, 10, 10,-10,
-10,  5,  0,  0,  0,  0,  5,-10,
-20,-10,-10,-10,-10,-10,-10,-20};
int queenpos[8][8]={-20,-10,-10, -5, -5,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5,  5,  5,  5,  0,-10,
-5,  0,  5,  5,  5,  5,  0, -5,
0,  0,  5,  5,  5,  5,  0, -5,
-10,  5,  5,  5,  5,  5,  0,-10,
-10,  0,  5,  0,  0,  0,  0,-10,
-20,-10,-10, -5, -5,-10,-10,-20};
int kingpos[8][8]={-80, -70, -70, -70, -70, -70, -70, -80,
-60, -60, -60, -60, -60, -60, -60, -60,
-40, -50, -50, -60, -60, -50, -50, -40,
-30, -40, -40, -50, -50, -40, -40, -30,
-20, -30, -30, -40, -40, -30, -30, -20,
-10, -20, -20, -20, -20, -20, -20, -10,
20, 20, -5, -5, -5, -5, 20, 20,
20, 30, 10, 0, 0, 10, 30, 20};
int kingposend[8][8]={-20, -10, -10, -10, -10, -10, -10, -20,
-5, 0, 5, 5, 5, 5, 0, -5,
-10, -5, 20, 30, 30, 20, -5, -10,
-15, -10, 35, 45, 45, 35, -10, -15,
-20, -15, 30, 40, 40, 30, -15, -20,
-25, -20, 20, 25, 25, 20, -20, -25,
-30, -25, 0, 0, 0, 0, -25, -30,
-50, -30, -30, -30, -30, -30, -30, -50};
map<string,int> vis;
string br(string curs){
    string ans="";
    for(int i=0;i<curs.size()&&curs[i]!=' ';i++)
        ans+=curs[i];
    return ans;
}
struct board{
    string fen="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    string brd[8]={"rnbqkbnr","pppppppp","........","........","........","........","PPPPPPPP","RNBQKBNR"};
    bool turn=0;
    bool cwk=1;
    bool cwq=1;
    bool cbk=1;
    bool cbq=1;
    string lstmv="-";
    int halfmove=0;
    int movecnt=1;
    bool hcw=0;
    bool hcb=0;
    int eval=0;
    bool endgame=0;
    int qcnt=2,pcnt=8;
    short bkpos=4,wkpos=60;
    ll whash=65535,bhash=65535;
}reset,cur;
struct stmove{
    int str,stc,trr,trc;
    char trp;
};
map<pair<string,pair<pair<pair<int,int>,pair<int,int>>,char>>,int> eval;
void convertfromfen(board &brd){
    int curidx=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(brd.fen[curidx]=='/')
                continue;
            if(brd.fen[curidx]>='1'&&brd.fen[curidx]<='8'){
                int x=brd.fen[curidx++]-'1';
                while(x--)
                    brd.brd[i][j++]='.';
                brd.brd[i][j]='.';
                continue;
            }
            brd.brd[i][j]=brd.fen[curidx];
            curidx++;
        }
        curidx++;
    }
    if(brd.fen[curidx]=='w')
        brd.turn=0;
    else
        brd.turn=1;
    curidx+=2;
    brd.cwk=brd.cwq=brd.cbk=brd.cbq=0;
    while(brd.fen[curidx]!=' '){
        if(brd.fen[curidx]=='K')
            brd.cwk=1;
        else if(brd.fen[curidx]=='Q')
            brd.cwq=1;
        else if(brd.fen[curidx]=='k')
            brd.cbk=1;
        else if(brd.fen[curidx]=='q')
            brd.cbq=1;
        curidx++;
    }
    curidx++;
    brd.lstmv="";
    while(brd.fen[curidx]!=' ')
        brd.lstmv+=brd.fen[curidx++];
    curidx++;
    brd.halfmove=0;
    while(brd.fen[curidx]!=' '){
        brd.halfmove*=10;
        brd.halfmove+=brd.fen[curidx++]-'0';
    }
    curidx++;
    brd.movecnt=0;
    while(curidx<(int)brd.fen.size()){
        brd.movecnt*=10;
        brd.movecnt+=brd.fen[curidx++]-'0';
    }
    return;
}
void converttofen(board &brd){
    brd.fen="";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(brd.brd[i][j]=='.'){
                if(j&&brd.brd[i][j-1]=='.')
                    brd.fen[brd.fen.size()-1]++;
                else
                    brd.fen+="1";
            }
            else
                brd.fen+=brd.brd[i][j];
        }
        if(i<7)
            brd.fen+="/";
    }
    brd.fen+=" ";
    brd.fen+=(brd.turn?"b ":"w ");
    if(brd.cbk||brd.cbq||brd.cwk||brd.cwq){
        if(brd.cwk)
            brd.fen+="K";
        if(brd.cwq)
            brd.fen+="Q";
        if(brd.cbk)
            brd.fen+="k";
        if(brd.cbq)
            brd.fen+="q";
        brd.fen+=" ";
    }
    else
        brd.fen+="- ";
    brd.fen+=brd.lstmv+" ";
    int x=brd.halfmove;
    string temp="";
    while(x){
        temp+=x%10+'0';
        x/=10;
    }
    if(temp.empty())
        temp="0";
    reverse(temp.begin(),temp.end());
    brd.fen+=temp;
    brd.fen+=" ";
    x=brd.movecnt;
    temp="";
    while(x){
        temp+=x%10+'0';
        x/=10;
    }
    reverse(temp.begin(),temp.end());
    brd.fen+=temp;
    return;
}
void prtbrd(board brd){
    cout<<"\n\n\n\n\n\n"<<"FEN: "<<brd.fen<<"\n";
    for(int i=0;i<8;i++)
        cout<<(8-i)<<"  "<<brd.brd[i]<<'\n';
    cout<<"\n   ABCDEFGH\n";
    cout<<(brd.turn?"Black":"White")<<"'s turn\n";
    cout<<"White king side castle rights: "<<(brd.cwk?"true\n":"false\n");
    cout<<"White queen side castle rights: "<<(brd.cwq?"true\n":"false\n");
    cout<<"Black king side castle rights: "<<(brd.cbk?"true\n":"false\n");
    cout<<"Black queen side castle rights: "<<(brd.cbq?"true\n":"false\n");
    cout<<"Possible En Passant target: "<<(brd.lstmv=="-"?"None":brd.lstmv)<<"\n";
    cout<<"Half move count: "<<brd.halfmove<<"\n";
    cout<<"Move count: "<<brd.movecnt<<endl;
    return;
}
void mkmv(stmove mv){
    cout<<"bestmove "<<char(mv.stc+'a')<<8-mv.str<<char(mv.trc+'a')<<8-mv.trr;
    if(mv.trp=='q'||mv.trp=='Q'||mv.trp=='b'||mv.trp=='B'||mv.trp=='n'||mv.trp=='N'||mv.trp=='r'||mv.trp=='R')
        cout<<char(tolower(mv.trp));
    cout<<"\n";
    return;
}
map<pair<ll,short>,short> kingvun;
board domove(board brd,stmove mv,bool bol=0){
    if(bol)
        mkmv(mv);
    int osafe=0;
    if(brd.brd[0][6]=='k'){
        osafe-=10;
        int cnt=0;
        cnt+=brd.brd[1][5]=='p';
        cnt+=brd.brd[1][6]=='p';
        cnt+=brd.brd[1][7]=='p';
        if(cnt==3)
            osafe-=40;
        if(cnt==2)
            osafe-=15;
    }
    if(brd.brd[7][6]=='K'){
        osafe+=10;
        int cnt=0;
        cnt+=brd.brd[6][5]=='P';
        cnt+=brd.brd[6][6]=='P';
        cnt+=brd.brd[6][7]=='P';
        if(cnt==3)
            osafe+=40;
        if(cnt==2)
            osafe+=15;
    }
    brd.lstmv="-";
    brd.halfmove++;
    int ans=brd.eval;
    //ans+=kingvun[{brd.whash,brd.wkpos}]*2-2;
    //ans-=kingvun[{brd.bhash,brd.bkpos}]*2-2;
    if(brd.movecnt<30&&brd.brd[0][3]=='q'&&mv.str==0&&mv.stc==3)
        ans+=100;
    if(brd.movecnt<30&&brd.brd[7][3]=='Q'&&mv.str==7&&mv.stc==3)
        ans-=100;
    if(brd.brd[0][1]=='n'&&mv.str==0&&mv.stc==1)
        ans-=20;
    if(brd.brd[0][2]=='b'&&mv.str==0&&mv.stc==2)
        ans-=20;
    if(brd.brd[0][5]=='b'&&mv.str==0&&mv.stc==5)
        ans-=20;
    if(brd.brd[0][6]=='n'&&mv.str==0&&mv.stc==6)
        ans-=20;
    if(brd.brd[7][1]=='N'&&mv.str==7&&mv.stc==1)
        ans+=20;
    if(brd.brd[7][2]=='B'&&mv.str==7&&mv.stc==2)
        ans+=20;
    if(brd.brd[7][5]=='B'&&mv.str==7&&mv.stc==5)
        ans+=20;
    if(brd.brd[7][6]=='N'&&mv.str==7&&mv.stc==6)
        ans+=20;
    if(mv.trr==0&&mv.trc==1&&brd.brd[mv.str][mv.stc]=='n')
        ans+=20;
    if(mv.trr==0&&mv.trc==2&&brd.brd[mv.str][mv.stc]=='b')
        ans+=20;
    if(mv.trr==0&&mv.trc==5&&brd.brd[mv.str][mv.stc]=='b')
        ans+=20;
    if(mv.trr==0&&mv.trc==6&&brd.brd[mv.str][mv.stc]=='n')
        ans+=20;
    if(mv.trr==7&&mv.trc==1&&brd.brd[mv.str][mv.stc]=='N')
        ans-=20;
    if(mv.trr==7&&mv.trc==2&&brd.brd[mv.str][mv.stc]=='B')
        ans-=20;
    if(mv.trr==7&&mv.trc==5&&brd.brd[mv.str][mv.stc]=='B')
        ans-=20;
    if(mv.trr==7&&mv.trc==6&&brd.brd[mv.str][mv.stc]=='N')
        ans-=20;
    if(brd.brd[mv.str][mv.stc]=='P'){
        if(!brd.endgame){
            ans-=pawnpos[mv.str][mv.stc];
            ans+=pawnpos[mv.trr][mv.trc];
        }
        else{
            ans-=pawnposend[mv.str][mv.stc];
            ans+=pawnposend[mv.trr][mv.trc];
        }
    }
    if(brd.brd[mv.str][mv.stc]=='p'){
        if(!brd.endgame){
            ans+=pawnpos[7-mv.str][7-mv.stc];
            ans-=pawnpos[7-mv.trr][7-mv.trc];
        }
        else{
            ans+=pawnposend[7-mv.str][7-mv.stc];
            ans-=pawnposend[7-mv.trr][7-mv.trc];
        }
    }
    if(brd.brd[mv.str][mv.stc]=='N'){
        ans-=knightpos[mv.str][mv.stc];
        ans+=knightpos[mv.trr][mv.trc];
    }
    if(brd.brd[mv.str][mv.stc]=='n'){
        ans+=knightpos[7-mv.str][7-mv.stc];
        ans-=knightpos[7-mv.trr][7-mv.trc];
    }
    if(brd.brd[mv.str][mv.stc]=='B'){
        ans-=bishoppos[mv.str][mv.stc];
        ans+=bishoppos[mv.trr][mv.trc];
    }
    if(brd.brd[mv.str][mv.stc]=='b'){
        ans+=bishoppos[7-mv.str][7-mv.stc];
        ans-=bishoppos[7-mv.trr][7-mv.trc];
    }
    if(brd.brd[mv.str][mv.stc]=='R'){
        ans-=rookpos[mv.str][mv.stc];
        ans+=rookpos[mv.trr][mv.trc];
    }
    if(brd.brd[mv.str][mv.stc]=='r'){
        ans+=rookpos[7-mv.str][7-mv.stc];
        ans-=rookpos[7-mv.trr][7-mv.trc];
    }
    if(brd.brd[mv.str][mv.stc]=='K'){
        if(!brd.endgame){
            ans-=kingpos[mv.str][mv.stc];
            ans+=kingpos[mv.trr][mv.trc];
        }
        else{
            ans-=kingposend[mv.str][mv.stc];
            ans+=kingposend[mv.trr][mv.trc];
        }
        brd.wkpos=mv.trr*8+mv.trc;
    }
    if(brd.brd[mv.str][mv.stc]=='k'){
        if(!brd.endgame){
            ans+=kingpos[7-mv.str][7-mv.stc];
            ans-=kingpos[7-mv.trr][7-mv.trc];
        }
        else{
            ans+=kingposend[7-mv.str][7-mv.stc];
            ans-=kingposend[7-mv.trr][7-mv.trc];
        }
        brd.bkpos=mv.trr*8+mv.trc;
    }
    if(brd.brd[mv.trr][mv.trc]!='.'){
        if(brd.turn==0)
            brd.bhash-=(1ll<<(mv.trr*8+mv.trc));
        else
            brd.whash-=(1ll<<((7-mv.trr)*8+(7-mv.trc)*8));
        brd.halfmove=0;
        char c=brd.brd[mv.trr][mv.trc];
        if(c=='p'){
            ans+=100;
            if(!brd.endgame)
                ans+=pawnpos[7-mv.trr][7-mv.trc];
            else
                ans+=pawnposend[7-mv.trr][7-mv.trc];
        }
        if(c=='P'){
            ans-=100;
            if(!brd.endgame)
                ans-=pawnpos[mv.trr][mv.trc];
            else
                ans-=pawnposend[mv.trr][mv.trc];
        }
        if(c=='n'){
            brd.pcnt--;
            ans+=300;
            ans+=knightpos[7-mv.trr][7-mv.trc];
        }
        if(c=='N'){
            brd.pcnt--;
            ans-=300;
            ans-=knightpos[mv.trr][mv.trc];
        }
        if(c=='b'){
            brd.pcnt--;
            ans+=350;
            ans+=bishoppos[7-mv.trr][7-mv.trc];
        }
        if(c=='B'){
            brd.pcnt--;
            ans-=350;
            ans-=bishoppos[mv.trr][mv.trc];
        }
        if(c=='r'){
            ans+=500;
            ans+=rookpos[7-mv.trr][7-mv.trc];
        }
        if(c=='R'){
            ans-=500;
            ans-=rookpos[mv.trr][mv.trc];
        }
        if(c=='q'){
            brd.qcnt--;
            ans+=1000;
            ans+=queenpos[7-mv.trr][7-mv.trc];
        }
        if(c=='Q'){
            brd.qcnt--;
            ans-=1000;
            ans-=queenpos[mv.trr][mv.trc];
        }
        if(c=='k')
        	ans+=30000;
        if(c=='K')
        	ans-=30000;
    }
    if(brd.brd[mv.str][mv.stc]=='P'){
        brd.halfmove=0;
        if(mv.stc==mv.trc){
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
            if(mv.trr==0){
                brd.brd[0][mv.trc]=mv.trp;
                if(mv.trp=='q')
                    ans-=900;
                else if(mv.trp=='r')
                    ans-=400;
                else if(mv.trp=='b')
                    ans-=250;
                else
                    ans-=200;
            }
            if(mv.trr==4&&mv.str==6){
                brd.lstmv=char(mv.stc+'a');
                brd.lstmv+='3';
            }
        }
        else if(brd.brd[mv.trr][mv.trc]!='.'){
            brd.brd[mv.trr][mv.trc]='.';
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
            if(mv.trr==0)
                brd.brd[0][mv.trc]=mv.trp;
            ans-=25;
        }
        else{
            brd.bhash-=(1ll<<((mv.trr+1)*8+mv.trc));
            ans+=75;
            if(!brd.endgame)
                ans+=pawnpos[7-mv.trr][7-mv.trc];
            else
                ans+=pawnposend[7-mv.trr][7-mv.trc];
            brd.brd[mv.trr+1][mv.trc]='.';
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
        }
    }
    else if(brd.brd[mv.str][mv.stc]=='p'){
        brd.halfmove=0;
        if(mv.stc==mv.trc){
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
            if(mv.trr==3&&mv.str==1){
                brd.lstmv=char(mv.stc+'a');
                brd.lstmv+='6';
            }
            if(mv.trr==7){
                brd.brd[7][mv.trc]=mv.trp;
                if(mv.trp=='q')
                    ans-=900;
                else if(mv.trp=='r')
                    ans-=400;
                else if(mv.trp=='b')
                    ans-=250;
                else
                    ans-=200;
            }
        }
        else if(brd.brd[mv.trr][mv.trc]!='.'){
            brd.brd[mv.trr][mv.trc]='.';
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
            if(mv.trr==7)
                brd.brd[7][mv.trc]=mv.trp;
            ans+=25;
        }
        else{
            brd.whash-=(1ll<<((7-mv.trr+1)*8+(7-mv.trc)));
            ans-=75;
            if(!brd.endgame)
                ans-=pawnpos[mv.trr][mv.trc];
            else
                ans-=pawnposend[mv.trr][mv.trc];
            brd.brd[mv.trr-1][mv.trc]='.';
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
        }
    }
    else if(brd.brd[mv.str][mv.stc]=='K'){
        if(brd.cwk)
            ans-=30;
        brd.cwk=0;
        if(brd.cwq)
            ans-=30;
        brd.cwq=0;
        if(abs(mv.stc-mv.trc)!=2){
            brd.brd[mv.trr][mv.trc]='.';
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
        }
        else{
        	brd.hcw=1;
        	ans+=110;
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
            if(mv.trc==6){
                brd.brd[mv.str][5]='R';
                brd.brd[mv.str][7]='.';
                brd.whash-=1;
                brd.whash+=4;
            }
            else{
                brd.brd[mv.str][3]='R';
                brd.brd[mv.str][0]='.';
                brd.whash-=127;
                brd.whash+=16;
            }
        }
    }
    else if(brd.brd[mv.str][mv.stc]=='k'){
        if(brd.cbk)
            ans+=30;
        brd.cbk=0;
        if(brd.cbq)
            ans+=30;
        brd.cbq=0;
        if(abs(mv.stc-mv.trc)!=2){
            brd.brd[mv.trr][mv.trc]='.';
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
        }
        else{
        	brd.hcb=1;
        	ans-=110;
            swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
            if(mv.trc==6){
                brd.brd[mv.str][5]='r';
                brd.brd[mv.str][7]='.';
                brd.bhash-=127;
                brd.bhash+=32;
            }
            else{
                brd.brd[mv.str][3]='r';
                brd.brd[mv.str][0]='.';
                brd.bhash-=1;
                brd.bhash+=8;
            }
        }
    }
    else{
        brd.brd[mv.trr][mv.trc]='.';
        swap(brd.brd[mv.str][mv.stc],brd.brd[mv.trr][mv.trc]);
    }
    if(brd.brd[0][0]!='r'&&brd.cbq){
        brd.cbq=0;
        ans+=30;
    }
    if(brd.brd[0][7]!='r'&&brd.cbk){
        brd.cbk=0;
        ans+=30;
    }
    if(brd.brd[7][0]!='R'&&brd.cwq){
        brd.cwq=0;
        ans-=30;
    }
    if(brd.brd[7][7]!='R'&&brd.cwk){
        brd.cwk=0;
        ans-=30;
    }
    int nsafe=0;
    if(brd.brd[0][6]=='k'){
        nsafe-=10;
        int cnt=0;
        cnt+=brd.brd[1][5]=='p';
        cnt+=brd.brd[1][6]=='p';
        cnt+=brd.brd[1][7]=='p';
        if(cnt==3)
            nsafe-=40;
        if(cnt==2)
            nsafe-=15;
    }
    if(brd.brd[7][6]=='K'){
        nsafe+=10;
        int cnt=0;
        cnt+=brd.brd[6][5]=='P';
        cnt+=brd.brd[6][6]=='P';
        cnt+=brd.brd[6][7]=='P';
        if(cnt==3)
            osafe+=40;
        if(cnt==2)
            nsafe+=15;
    }
    ans+=nsafe-osafe;
    if(brd.endgame==0&&brd.qcnt==0&&brd.pcnt<4){
        ans-=nsafe;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(brd.brd[i][j]=='p'){
                    ans+=pawnpos[7-i][7-j];
                    ans-=pawnposend[7-i][7-j];
                }
                else if(brd.brd[i][j]=='P'){
                    ans-=pawnpos[i][j];
                    ans+=pawnposend[i][j];
                }
                else if(brd.brd[i][j]=='k'){
                    ans+=kingpos[7-i][7-j];
                    ans-=kingposend[7-i][7-j];
                }
                else if(brd.brd[i][j]=='K'){
                    ans-=kingpos[i][j];
                    ans+=kingposend[i][j];
                }
            }
        }
        brd.endgame=1;
    }
    if(brd.turn==0){
        brd.whash-=(1ll<<((7-mv.str)*8+(7-mv.stc)));
        brd.whash+=(1ll<<((7-mv.trr)*8+(7-mv.trc)));
    }
    else{
        brd.bhash-=(1ll<<(mv.str*8+mv.stc));
        brd.bhash+=(1ll<<(mv.trr*8+mv.trc));
    }
    /*int wkpos=(7-brd.wkpos/8)*8+(7-brd.wkpos%8);
    if(kingvun[{brd.whash,wkpos}])
        ans-=kingvun[{brd.whash,wkpos}]*2-2;
    else{
        int cnt=0;
        bool up=1,dn=1,rt=1,lt=1;
        int idx=brd.wkpos/8,idy=brd.wkpos%8;
        for(int x=1;x<=7;x++){
            if(up&&idx-x>=0&&(brd.brd[idx-x][idy]<'A'||brd.brd[idx-x][idy]>'Z'))
                cnt++;
            else
                up=0;
            if(dn&&idx+x<8&&(brd.brd[idx+x][idy]<'A'||brd.brd[idx+x][idy]>'Z'))
                cnt++;
            else
                dn=0;
            if(lt&&idy-x>=0&&(brd.brd[idx][idy-x]<'A'||brd.brd[idx][idy-x]>'Z'))
                cnt++;
            else
                lt=0;
            if(rt&&idy+x<8&&(brd.brd[idx][idy+x]<'A'||brd.brd[idx][idy+x]>'Z'))
                cnt++;
            else
                rt=0;
        }
        bool ul=1,ur=1,dl=1,dr=1;
        for(int x=1;x<=7;x++){
            if(ul&&idx-x>=0&&idy-x>=0&&(brd.brd[idx-x][idy-x]<'A'||brd.brd[idx-x][idy-x]>'Z'))
                cnt++;
            else
                ul=0;
            if(ur&&idx-x>=0&&idy+x<8&&(brd.brd[idx-x][idy+x]<'A'||brd.brd[idx-x][idy+x]>'Z'))
                cnt++;
            else
                ur=0;
            if(dl&&idx+x<8&&idy-x>=0&&(brd.brd[idx+x][idy-x]<'A'||brd.brd[idx+x][idy-x]>'Z'))
                cnt++;
            else
                dl=0;
            if(dr&&idx+x<8&&idy+x<8&&(brd.brd[idx+x][idy+x]<'A'||brd.brd[idx+x][idy+x]>'Z'))
                cnt++;
            else
                dr=0;
        }
        kingvun[{brd.whash,wkpos}]=cnt+1;
        ans-=cnt*2;
    }
    int bkpos=brd.bkpos-brd.bkpos%8+(7-brd.bkpos%8);
    if(kingvun[{brd.bhash,bkpos}])
        ans+=kingvun[{brd.bhash,bkpos}]*2-2;
    else{
        int cnt=0;
        bool up=1,dn=1,rt=1,lt=1;
        int idx=brd.bkpos/8,idy=brd.bkpos%8;
        for(int x=1;x<=7;x++){
            if(up&&idx-x>=0&&(brd.brd[idx-x][idy]<'a'||brd.brd[idx-x][idy]>'z'))
                cnt++;
            else
                up=0;
            if(dn&&idx+x<8&&(brd.brd[idx+x][idy]<'a'||brd.brd[idx+x][idy]>'z'))
                cnt++;
            else
                dn=0;
            if(lt&&idy-x>=0&&(brd.brd[idx][idy-x]<'a'||brd.brd[idx][idy-x]>'z'))
                cnt++;
            else
                lt=0;
            if(rt&&idy+x<8&&(brd.brd[idx][idy+x]<'a'||brd.brd[idx][idy+x]>'z'))
                cnt++;
            else
                rt=0;
        }
        bool ul=1,ur=1,dl=1,dr=1;
        for(int x=1;x<=7;x++){
            if(ul&&idx-x>=0&&idy-x>=0&&(brd.brd[idx-x][idy-x]<'a'||brd.brd[idx-x][idy-x]>'z'))
                cnt++;
            else
                ul=0;
            if(ur&&idx-x>=0&&idy+x<8&&(brd.brd[idx-x][idy+x]<'a'||brd.brd[idx-x][idy+x]>'z'))
                cnt++;
            else
                ur=0;
            if(dl&&idx+x<8&&idy-x>=0&&(brd.brd[idx+x][idy-x]<'a'||brd.brd[idx+x][idy-x]>'z'))
                cnt++;
            else
                dl=0;
            if(dr&&idx+x<8&&idy+x<8&&(brd.brd[idx+x][idy+x]<'a'||brd.brd[idx+x][idy+x]>'z'))
                cnt++;
            else
                dr=0;
        }
        kingvun[{brd.bhash,bkpos}]=cnt+1;
        ans+=cnt*2;
    }*/
    if(brd.turn==0){
        brd.turn=1;
        brd.movecnt++;
    }
    else
        brd.turn=0;
    brd.eval=ans;
    converttofen(brd);
    return brd;
}
board tmpbrd;
vector<stmove> calcmoves(board brd,bool ch=0){
    vector<stmove> ans;
    int idx=0,idy=0;
    for(int i=0;i<(int)brd.fen.size();i++){
        if(brd.fen[i]==' ')
            break;
        if(brd.fen[i]=='/'){
            idx++,idy=0;
            continue;
        }
        if(brd.fen[i]>='1'&&brd.fen[i]<='8'){
            idy+=brd.fen[i]-'0';
            continue;
        }
        if(brd.fen[i]>='a'&&brd.fen[i]<='z'&&!brd.turn){
            idy++;
            continue;
        }
        if(brd.fen[i]>='A'&&brd.fen[i]<='Z'&&brd.turn){
            idy++;
            continue;
        }
        if(brd.fen[i]=='K'){
            for(int x=-1;x<=1;x++){
                for(int y=-1;y<=1;y++){
                    if(x==y&&x==0)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7)
                        continue;
                    if(brd.brd[idx+x][idy+y]>='A'&&brd.brd[idx+x][idy+y]<='Z')
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
            if(brd.cwk&&brd.brd[7][5]=='.'&&brd.brd[7][6]=='.')
                ans.pb({7,4,7,6,'-'});
            if(brd.cwq&&brd.brd[7][3]=='.'&&brd.brd[7][2]=='.'&&brd.brd[7][1]=='.')
                ans.pb({7,4,7,2,'-'});
        }
        if(brd.fen[i]=='k'){
            for(int x=-1;x<=1;x++){
                for(int y=-1;y<=1;y++){
                    if(x==y&&x==0)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7)
                        continue;
                    if(brd.brd[idx+x][idy+y]>='a'&&brd.brd[idx+x][idy+y]<='z')
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
            if(brd.cbk&&brd.brd[0][5]=='.'&&brd.brd[0][6]=='.')
                ans.pb({0,4,0,6,'-'});
            if(brd.cbq&&brd.brd[0][3]=='.'&&brd.brd[0][2]=='.'&&brd.brd[0][1]=='.')
                ans.pb({0,4,0,2,'-'});
        }
        if(brd.fen[i]=='P'){
            if(brd.brd[idx-1][idy]=='.'){
                if(idx>1)
                    ans.pb({idx,idy,idx-1,idy,'-'});
                else{
                    ans.pb({idx,idy,idx-1,idy,'Q'});
                    ans.pb({idx,idy,idx-1,idy,'R'});
                    ans.pb({idx,idy,idx-1,idy,'B'});
                    ans.pb({idx,idy,idx-1,idy,'N'});
                }
                if(idx==6&&brd.brd[4][idy]=='.')
                    ans.pb({idx,idy,idx-2,idy,'-'});
            }
            if(idy&&((brd.brd[idx-1][idy-1]>='a'&&brd.brd[idx-1][idy-1]<='z')||(brd.lstmv!="-"&&brd.lstmv[0]=='a'+idy-1&&idx==3))){
                if(idx>1)
                    ans.pb({idx,idy,idx-1,idy-1,'-'});
                else{
                    ans.pb({idx,idy,idx-1,idy-1,'Q'});
                    ans.pb({idx,idy,idx-1,idy-1,'R'});
                    ans.pb({idx,idy,idx-1,idy-1,'B'});
                    ans.pb({idx,idy,idx-1,idy-1,'N'});
                }
            }
            if(idy<7&&((brd.brd[idx-1][idy+1]>='a'&&brd.brd[idx-1][idy+1]<='z')||(brd.lstmv!="-"&&brd.lstmv[0]=='a'+idy+1&&idx==3))){
                if(idx>1)
                    ans.pb({idx,idy,idx-1,idy+1,'-'});
                else{
                    ans.pb({idx,idy,idx-1,idy+1,'Q'});
                    ans.pb({idx,idy,idx-1,idy+1,'R'});
                    ans.pb({idx,idy,idx-1,idy+1,'B'});
                    ans.pb({idx,idy,idx-1,idy+1,'N'});
                }
            }
        }
        if(brd.fen[i]=='p'){
            if(brd.brd[idx+1][idy]=='.'){
                if(idx<6)
                    ans.pb({idx,idy,idx+1,idy,'-'});
                else{
                    ans.pb({idx,idy,idx+1,idy,'q'});
                    ans.pb({idx,idy,idx+1,idy,'r'});
                    ans.pb({idx,idy,idx+1,idy,'b'});
                    ans.pb({idx,idy,idx+1,idy,'n'});
                }
                if(idx==1&&brd.brd[3][idy]=='.')
                    ans.pb({idx,idy,idx+2,idy,'-'});
            }
            if(idy&&((brd.brd[idx+1][idy-1]>='A'&&brd.brd[idx+1][idy-1]<='Z')||(brd.lstmv!="-"&&brd.lstmv[0]=='a'+idy-1&&idx==4))){
                if(idx<6)
                    ans.pb({idx,idy,idx+1,idy-1,'-'});
                else{
                    ans.pb({idx,idy,idx+1,idy-1,'q'});
                    ans.pb({idx,idy,idx+1,idy-1,'r'});
                    ans.pb({idx,idy,idx+1,idy-1,'b'});
                    ans.pb({idx,idy,idx+1,idy-1,'n'});
                }
            }
            if(idy<7&&((brd.brd[idx+1][idy+1]>='A'&&brd.brd[idx+1][idy+1]<='Z')||(brd.lstmv!="-"&&brd.lstmv[0]=='a'+idy+1&&idx==4))){
                if(idx<6)
                    ans.pb({idx,idy,idx+1,idy+1,'-'});
                else{
                    ans.pb({idx,idy,idx+1,idy+1,'q'});
                    ans.pb({idx,idy,idx+1,idy+1,'r'});
                    ans.pb({idx,idy,idx+1,idy+1,'b'});
                    ans.pb({idx,idy,idx+1,idy+1,'n'});
                }
            }
        }
        if(brd.fen[i]=='N'){
            for(int x=-2;x<=2;x++){
                for(int y=-2;y<=2;y++){
                    if(abs(x)+abs(y)!=3)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7||(brd.brd[idx+x][idy+y]>='A'&&brd.brd[idx+x][idy+y]<='Z'))
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
        }
        if(brd.fen[i]=='n'){
            for(int x=-2;x<=2;x++){
                for(int y=-2;y<=2;y++){
                    if(abs(x)+abs(y)!=3)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7||(brd.brd[idx+x][idy+y]>='a'&&brd.brd[idx+x][idy+y]<='z'))
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
        }
        if(brd.fen[i]=='R'||brd.fen[i]=='Q'){
            bool up=1,dn=1,rt=1,lt=1;
            for(int x=1;x<=7;x++){
                if(up&&idx-x>=0&&(brd.brd[idx-x][idy]<'A'||brd.brd[idx-x][idy]>'Z')){
                    ans.pb({idx,idy,idx-x,idy});
                    if(brd.brd[idx-x][idy]!='.')
                        up=0;
                }
                else
                    up=0;
                if(dn&&idx+x<8&&(brd.brd[idx+x][idy]<'A'||brd.brd[idx+x][idy]>'Z')){
                    ans.pb({idx,idy,idx+x,idy});
                    if(brd.brd[idx+x][idy]!='.')
                        dn=0;
                }
                else
                    dn=0;
                if(lt&&idy-x>=0&&(brd.brd[idx][idy-x]<'A'||brd.brd[idx][idy-x]>'Z')){
                    ans.pb({idx,idy,idx,idy-x});
                    if(brd.brd[idx][idy-x]!='.')
                        lt=0;
                }
                else
                    lt=0;
                if(rt&&idy+x<8&&(brd.brd[idx][idy+x]<'A'||brd.brd[idx][idy+x]>'Z')){
                    ans.pb({idx,idy,idx,idy+x});
                    if(brd.brd[idx][idy+x]!='.')
                        rt=0;
                }
                else
                    rt=0;
            }
        }
        if(brd.fen[i]=='r'||brd.fen[i]=='q'){
            bool up=1,dn=1,rt=1,lt=1;
            for(int x=1;x<=7;x++){
                if(up&&idx-x>=0&&(brd.brd[idx-x][idy]<'a'||brd.brd[idx-x][idy]>'z')){
                    ans.pb({idx,idy,idx-x,idy});
                    if(brd.brd[idx-x][idy]!='.')
                        up=0;
                }
                else
                    up=0;
                if(dn&&idx+x<8&&(brd.brd[idx+x][idy]<'a'||brd.brd[idx+x][idy]>'z')){
                    ans.pb({idx,idy,idx+x,idy});
                    if(brd.brd[idx+x][idy]!='.')
                        dn=0;
                }
                else
                    dn=0;
                if(lt&&idy-x>=0&&(brd.brd[idx][idy-x]<'a'||brd.brd[idx][idy-x]>'z')){
                    ans.pb({idx,idy,idx,idy-x});
                    if(brd.brd[idx][idy-x]!='.')
                        lt=0;
                }
                else
                    lt=0;
                if(rt&&idy+x<8&&(brd.brd[idx][idy+x]<'a'||brd.brd[idx][idy+x]>'z')){
                    ans.pb({idx,idy,idx,idy+x});
                    if(brd.brd[idx][idy+x]!='.')
                        rt=0;
                }
                else
                    rt=0;
            }
        }
        if(brd.fen[i]=='B'||brd.fen[i]=='Q'){
            bool ul=1,ur=1,dl=1,dr=1;
            for(int x=1;x<=7;x++){
                if(ul&&idx-x>=0&&idy-x>=0&&(brd.brd[idx-x][idy-x]<'A'||brd.brd[idx-x][idy-x]>'Z')){
                    ans.pb({idx,idy,idx-x,idy-x});
                    if(brd.brd[idx-x][idy-x]!='.')
                        ul=0;
                }
                else
                    ul=0;
                if(ur&&idx-x>=0&&idy+x<8&&(brd.brd[idx-x][idy+x]<'A'||brd.brd[idx-x][idy+x]>'Z')){
                    ans.pb({idx,idy,idx-x,idy+x});
                    if(brd.brd[idx-x][idy+x]!='.')
                        ur=0;
                }
                else
                    ur=0;
                if(dl&&idx+x<8&&idy-x>=0&&(brd.brd[idx+x][idy-x]<'A'||brd.brd[idx+x][idy-x]>'Z')){
                    ans.pb({idx,idy,idx+x,idy-x});
                    if(brd.brd[idx+x][idy-x]!='.')
                        dl=0;
                }
                else
                    dl=0;
                if(dr&&idx+x<8&&idy+x<8&&(brd.brd[idx+x][idy+x]<'A'||brd.brd[idx+x][idy+x]>'Z')){
                    ans.pb({idx,idy,idx+x,idy+x});
                    if(brd.brd[idx+x][idy+x]!='.')
                        dr=0;
                }
                else
                    dr=0;
            }
        }
        if(brd.fen[i]=='b'||brd.fen[i]=='q'){
            bool ul=1,ur=1,dl=1,dr=1;
            for(int x=1;x<=7;x++){
                if(ul&&idx-x>=0&&idy-x>=0&&(brd.brd[idx-x][idy-x]<'a'||brd.brd[idx-x][idy-x]>'z')){
                    ans.pb({idx,idy,idx-x,idy-x});
                    if(brd.brd[idx-x][idy-x]!='.')
                        ul=0;
                }
                else
                    ul=0;
                if(ur&&idx-x>=0&&idy+x<8&&(brd.brd[idx-x][idy+x]<'a'||brd.brd[idx-x][idy+x]>'z')){
                    ans.pb({idx,idy,idx-x,idy+x});
                    if(brd.brd[idx-x][idy+x]!='.')
                        ur=0;
                }
                else
                    ur=0;
                if(dl&&idx+x<8&&idy-x>=0&&(brd.brd[idx+x][idy-x]<'a'||brd.brd[idx+x][idy-x]>'z')){
                    ans.pb({idx,idy,idx+x,idy-x});
                    if(brd.brd[idx+x][idy-x]!='.')
                        dl=0;
                }
                else
                    dl=0;
                if(dr&&idx+x<8&&idy+x<8&&(brd.brd[idx+x][idy+x]<'a'||brd.brd[idx+x][idy+x]>'z')){
                    ans.pb({idx,idy,idx+x,idy+x});
                    if(brd.brd[idx+x][idy+x]!='.')
                        dr=0;
                }
                else
                    dr=0;
            }
        }
        idy++;
    }
    tmpbrd=brd;
    if(ch)
        return ans;
    vector<pair<int,stmove>> ans2;
    for(int i=0;i<(int)ans.size();i++){
        bool bol=1;
        board brd2=domove(brd,ans[i]);
        vector<stmove> temp=calcmoves(brd2,1);
        for(int j=0;j<(int)temp.size()&&bol;j++){
            if(brd2.brd[temp[j].trr][temp[j].trc]=='K'||brd2.brd[temp[j].trr][temp[j].trc]=='k')
                bol=0;
        }
        if((brd.brd[ans[i].str][ans[i].stc]=='K'||brd.brd[ans[i].str][ans[i].stc]=='k')&&abs(ans[i].stc-ans[i].trc)==2){
            stmove tmp={ans[i].str,ans[i].stc,ans[i].trr,(ans[i].stc+ans[i].trc)/2,'-'};
            board brd2=domove(brd,tmp);
            vector<stmove> temp=calcmoves(brd2,1);
            for(int j=0;j<(int)temp.size()&&bol;j++){
                if(brd2.brd[temp[j].trr][temp[j].trc]=='K'||brd2.brd[temp[j].trr][temp[j].trc]=='k')
                    bol=0;
            }
            brd2=brd;
            brd2.turn=!brd2.turn;
            converttofen(brd2);
            temp=calcmoves(brd2,1);
            for(int j=0;j<(int)temp.size()&&bol;j++){
                if(brd2.brd[temp[j].trr][temp[j].trc]=='K'||brd2.brd[temp[j].trr][temp[j].trc]=='k')
                    bol=0;
            }
        }
        if(bol){
            int x=0;
            if(brd.brd[ans[i].str][ans[i].stc]=='P'||brd.brd[ans[i].str][ans[i].stc]=='p')
                x-=100;
            if(brd.brd[ans[i].str][ans[i].stc]=='N'||brd.brd[ans[i].str][ans[i].stc]=='n')
                x-=300;
            if(brd.brd[ans[i].str][ans[i].stc]=='B'||brd.brd[ans[i].str][ans[i].stc]=='b')
                x-=325;
            if(brd.brd[ans[i].str][ans[i].stc]=='Q'||brd.brd[ans[i].str][ans[i].stc]=='q')
                x-=900;
            if(brd.brd[ans[i].trr][ans[i].trc]=='P'||brd.brd[ans[i].trr][ans[i].trc]=='p')
                x+=100;
            if(brd.brd[ans[i].trr][ans[i].trc]=='N'||brd.brd[ans[i].trr][ans[i].trc]=='n')
                x+=300;
            if(brd.brd[ans[i].trr][ans[i].trc]=='B'||brd.brd[ans[i].trr][ans[i].trc]=='b')
                x+=325;
            if(brd.brd[ans[i].trr][ans[i].trc]=='Q'||brd.brd[ans[i].trr][ans[i].trc]=='q')
                x+=900;
            ans2.pb({x,ans[i]});
        }
    }
    ans.clear();
    for(int i=1;i<ans2.size();i++){
        if(ans2[i].f>ans2[i-1].f){
            swap(ans2[i].f,ans2[i-1].f);
            i--;
        }
    }
    for(int i=0;i<ans2.size();i++)
        ans.pb(ans2[i].s);
    return ans;
}
vector<stmove> calccap(board brd,bool ch=0){
    vector<stmove> ans;
    int idx=0,idy=0;
    for(int i=0;i<(int)brd.fen.size();i++){
        if(brd.fen[i]==' ')
            break;
        if(brd.fen[i]=='/'){
            idx++,idy=0;
            continue;
        }
        if(brd.fen[i]>='1'&&brd.fen[i]<='8'){
            idy+=brd.fen[i]-'0';
            continue;
        }
        if(brd.fen[i]>='a'&&brd.fen[i]<='z'&&!brd.turn){
            idy++;
            continue;
        }
        if(brd.fen[i]>='A'&&brd.fen[i]<='Z'&&brd.turn){
            idy++;
            continue;
        }
        if(brd.fen[i]=='K'){
            for(int x=-1;x<=1;x++){
                for(int y=-1;y<=1;y++){
                    if(x==y&&x==0)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7)
                        continue;
                    if(brd.brd[idx+x][idy+y]>='A'&&brd.brd[idx+x][idy+y]<='Z')
                        continue;
                    if(brd.brd[idx+x][idy+y]=='.')
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
        }
        if(brd.fen[i]=='k'){
            for(int x=-1;x<=1;x++){
                for(int y=-1;y<=1;y++){
                    if(x==y&&x==0)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7)
                        continue;
                    if(brd.brd[idx+x][idy+y]>='a'&&brd.brd[idx+x][idy+y]<='z')
                        continue;
                    if(brd.brd[idx+x][idy+y]=='.')
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
        }
        if(brd.fen[i]=='P'){
            if(idy&&(brd.brd[idx-1][idy-1]>='a'&&brd.brd[idx-1][idy-1]<='z'&&brd.brd[idx-1][idy-1]!='p')){
                if(idx>1)
                    ans.pb({idx,idy,idx-1,idy-1,'-'});
                else{
                    ans.pb({idx,idy,idx-1,idy-1,'Q'});
                    ans.pb({idx,idy,idx-1,idy-1,'R'});
                    ans.pb({idx,idy,idx-1,idy-1,'B'});
                    ans.pb({idx,idy,idx-1,idy-1,'N'});
                }
            }
            if(idy<7&&(brd.brd[idx-1][idy+1]>='a'&&brd.brd[idx-1][idy+1]<='z'&&brd.brd[idx-1][idy+1]!='p')){
                if(idx>1)
                    ans.pb({idx,idy,idx-1,idy+1,'-'});
                else{
                    ans.pb({idx,idy,idx-1,idy+1,'Q'});
                    ans.pb({idx,idy,idx-1,idy+1,'R'});
                    ans.pb({idx,idy,idx-1,idy+1,'B'});
                    ans.pb({idx,idy,idx-1,idy+1,'N'});
                }
            }
        }
        if(brd.fen[i]=='p'){
            if(idy&&(brd.brd[idx+1][idy-1]>='A'&&brd.brd[idx+1][idy-1]<='Z'&&brd.brd[idx+1][idy-1]!='P')){
                if(idx<6)
                    ans.pb({idx,idy,idx+1,idy-1,'-'});
                else{
                    ans.pb({idx,idy,idx+1,idy-1,'q'});
                    ans.pb({idx,idy,idx+1,idy-1,'r'});
                    ans.pb({idx,idy,idx+1,idy-1,'b'});
                    ans.pb({idx,idy,idx+1,idy-1,'n'});
                }
            }
            if(idy<7&&(brd.brd[idx+1][idy+1]>='A'&&brd.brd[idx+1][idy+1]<='Z'&&brd.brd[idx+1][idy+1]!='P')){
                if(idx<6)
                    ans.pb({idx,idy,idx+1,idy+1,'-'});
                else{
                    ans.pb({idx,idy,idx+1,idy+1,'q'});
                    ans.pb({idx,idy,idx+1,idy+1,'r'});
                    ans.pb({idx,idy,idx+1,idy+1,'b'});
                    ans.pb({idx,idy,idx+1,idy+1,'n'});
                }
            }
        }
        if(brd.fen[i]=='N'){
            for(int x=-2;x<=2;x++){
                for(int y=-2;y<=2;y++){
                    if(abs(x)+abs(y)!=3)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7||(brd.brd[idx+x][idy+y]>='A'&&brd.brd[idx+x][idy+y]<='Z'))
                        continue;
                    if(brd.brd[idx+x][idy+y]=='.'||brd.brd[idx+x][idy+y]=='p')
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
        }
        if(brd.fen[i]=='n'){
            for(int x=-2;x<=2;x++){
                for(int y=-2;y<=2;y++){
                    if(abs(x)+abs(y)!=3)
                        continue;
                    if(idx+x<0||idx+x>7||idy+y<0||idy+y>7||(brd.brd[idx+x][idy+y]>='a'&&brd.brd[idx+x][idy+y]<='z'))
                        continue;
                    if(brd.brd[idx+x][idy+y]=='.'||brd.brd[idx+x][idy+y]=='P')
                        continue;
                    ans.pb({idx,idy,idx+x,idy+y,'-'});
                }
            }
        }
        if(brd.fen[i]=='R'||brd.fen[i]=='Q'){
            bool up=1,dn=1,rt=1,lt=1;
            for(int x=1;x<=7;x++){
                if(up&&idx-x>=0&&(brd.brd[idx-x][idy]<'A'||brd.brd[idx-x][idy]>'Z')){
                    if(brd.brd[idx-x][idy]!='.'&&brd.brd[idx-x][idy]!='p'){
                        up=0;
                        ans.pb({idx,idy,idx-x,idy});
                    }
                }
                else
                    up=0;
                if(dn&&idx+x<8&&(brd.brd[idx+x][idy]<'A'||brd.brd[idx+x][idy]>'Z')){
                    if(brd.brd[idx+x][idy]!='.'&&brd.brd[idx+x][idy]!='p'){
                        dn=0;
                        ans.pb({idx,idy,idx+x,idy});
                    }
                }
                else
                    dn=0;
                if(lt&&idy-x>=0&&(brd.brd[idx][idy-x]<'A'||brd.brd[idx][idy-x]>'Z')){
                    if(brd.brd[idx][idy-x]!='.'&&brd.brd[idx][idy-x]!='p'){
                        lt=0;
                        ans.pb({idx,idy,idx,idy-x});
                    }
                }
                else
                    lt=0;
                if(rt&&idy+x<8&&(brd.brd[idx][idy+x]<'A'||brd.brd[idx][idy+x]>'Z')){
                    if(brd.brd[idx][idy+x]!='.'&&brd.brd[idx][idy+x]!='p'){
                        rt=0;
                        ans.pb({idx,idy,idx,idy+x});
                    }
                }
                else
                    rt=0;
            }
        }
        if(brd.fen[i]=='r'||brd.fen[i]=='q'){
            bool up=1,dn=1,rt=1,lt=1;
            for(int x=1;x<=7;x++){
                if(up&&idx-x>=0&&(brd.brd[idx-x][idy]<'a'||brd.brd[idx-x][idy]>'z')){
                    if(brd.brd[idx-x][idy]!='.'&&brd.brd[idx-x][idy]!='P')
                        ans.pb({idx,idy,idx-x,idy});
                    if(brd.brd[idx-x][idy]!='.')
                        up=0;
                }
                else
                    up=0;
                if(dn&&idx+x<8&&(brd.brd[idx+x][idy]<'a'||brd.brd[idx+x][idy]>'z')){
                    if(brd.brd[idx+x][idy]!='.'&&brd.brd[idx+x][idy]!='P')
                        ans.pb({idx,idy,idx+x,idy});
                    if(brd.brd[idx+x][idy]!='.')
                        dn=0;
                }
                else
                    dn=0;
                if(lt&&idy-x>=0&&(brd.brd[idx][idy-x]<'a'||brd.brd[idx][idy-x]>'z')){
                    if(brd.brd[idx][idy-x]!='.'&&brd.brd[idx][idy-x]!='P')
                        ans.pb({idx,idy,idx,idy-x});
                    if(brd.brd[idx][idy-x]!='.')
                        lt=0;
                }
                else
                    lt=0;
                if(rt&&idy+x<8&&(brd.brd[idx][idy+x]<'a'||brd.brd[idx][idy+x]>'z')){
                    if(brd.brd[idx][idy+x]!='.'&&brd.brd[idx][idy+x]!='P')
                        ans.pb({idx,idy,idx,idy+x});
                    if(brd.brd[idx][idy+x]!='.')
                        rt=0;
                }
                else
                    rt=0;
            }
        }
        if(brd.fen[i]=='B'||brd.fen[i]=='Q'){
            bool ul=1,ur=1,dl=1,dr=1;
            for(int x=1;x<=7;x++){
                if(ul&&idx-x>=0&&idy-x>=0&&(brd.brd[idx-x][idy-x]<'A'||brd.brd[idx-x][idy-x]>'Z')){
                    if(brd.brd[idx-x][idy-x]!='.'&&brd.brd[idx-x][idy-x]!='p')
                        ans.pb({idx,idy,idx-x,idy-x});
                    if(brd.brd[idx-x][idy-x]!='.')
                        ul=0;
                }
                else
                    ul=0;
                if(ur&&idx-x>=0&&idy+x<8&&(brd.brd[idx-x][idy+x]<'A'||brd.brd[idx-x][idy+x]>'Z')){
                    if(brd.brd[idx-x][idy+x]!='.'&&brd.brd[idx-x][idy+x]!='p')
                        ans.pb({idx,idy,idx-x,idy+x});
                    if(brd.brd[idx-x][idy+x]!='.')
                        ur=0;
                }
                else
                    ur=0;
                if(dl&&idx+x<8&&idy-x>=0&&(brd.brd[idx+x][idy-x]<'A'||brd.brd[idx+x][idy-x]>'Z')){
                    if(brd.brd[idx+x][idy-x]!='.'&&brd.brd[idx+x][idy-x]!='p')
                        ans.pb({idx,idy,idx+x,idy-x});
                    if(brd.brd[idx+x][idy-x]!='.')
                        dl=0;
                }
                else
                    dl=0;
                if(dr&&idx+x<8&&idy+x<8&&(brd.brd[idx+x][idy+x]<'A'||brd.brd[idx+x][idy+x]>'Z')){
                    if(brd.brd[idx+x][idy+x]!='.'&&brd.brd[idx+x][idy+x]!='p')
                        ans.pb({idx,idy,idx+x,idy+x});
                    if(brd.brd[idx+x][idy+x]!='.')
                        dr=0;
                }
                else
                    dr=0;
            }
        }
        if(brd.fen[i]=='b'||brd.fen[i]=='q'){
            bool ul=1,ur=1,dl=1,dr=1;
            for(int x=1;x<=7;x++){
                if(ul&&idx-x>=0&&idy-x>=0&&(brd.brd[idx-x][idy-x]<'a'||brd.brd[idx-x][idy-x]>'z')){
                    if(brd.brd[idx-x][idy-x]!='.'&&brd.brd[idx-x][idy-x]!='P')
                        ans.pb({idx,idy,idx-x,idy-x});
                    if(brd.brd[idx-x][idy-x]!='.')
                        ul=0;
                }
                else
                    ul=0;
                if(ur&&idx-x>=0&&idy+x<8&&(brd.brd[idx-x][idy+x]<'a'||brd.brd[idx-x][idy+x]>'z')){
                    if(brd.brd[idx-x][idy+x]!='.'&&brd.brd[idx-x][idy+x]!='P')
                        ans.pb({idx,idy,idx-x,idy+x});
                    if(brd.brd[idx-x][idy+x]!='.')
                        ur=0;
                }
                else
                    ur=0;
                if(dl&&idx+x<8&&idy-x>=0&&(brd.brd[idx+x][idy-x]<'a'||brd.brd[idx+x][idy-x]>'z')){
                    if(brd.brd[idx+x][idy-x]!='.'&&brd.brd[idx+x][idy-x]!='P')
                        ans.pb({idx,idy,idx+x,idy-x});
                    if(brd.brd[idx+x][idy-x]!='.')
                        dl=0;
                }
                else
                    dl=0;
                if(dr&&idx+x<8&&idy+x<8&&(brd.brd[idx+x][idy+x]<'a'||brd.brd[idx+x][idy+x]>'z')){
                    if(brd.brd[idx+x][idy+x]!='.'&&brd.brd[idx+x][idy+x]!='P')
                        ans.pb({idx,idy,idx+x,idy+x});
                    if(brd.brd[idx+x][idy+x]!='.')
                        dr=0;
                }
                else
                    dr=0;
            }
        }
        idy++;
    }
    vector<pair<int,stmove>> ans2;
    for(int i=0;i<(int)ans.size();i++){
        int x=0;
        if(brd.brd[ans[i].str][ans[i].stc]=='P'||brd.brd[ans[i].str][ans[i].stc]=='p')
            x-=100;
        if(brd.brd[ans[i].str][ans[i].stc]=='N'||brd.brd[ans[i].str][ans[i].stc]=='n')
            x-=300;
        if(brd.brd[ans[i].str][ans[i].stc]=='B'||brd.brd[ans[i].str][ans[i].stc]=='b')
            x-=325;
        if(brd.brd[ans[i].str][ans[i].stc]=='Q'||brd.brd[ans[i].str][ans[i].stc]=='q')
            x-=900;
        if(brd.brd[ans[i].trr][ans[i].trc]=='P'||brd.brd[ans[i].trr][ans[i].trc]=='p')
            x+=100;
        if(brd.brd[ans[i].trr][ans[i].trc]=='N'||brd.brd[ans[i].trr][ans[i].trc]=='n')
            x+=300;
        if(brd.brd[ans[i].trr][ans[i].trc]=='B'||brd.brd[ans[i].trr][ans[i].trc]=='b')
            x+=325;
        if(brd.brd[ans[i].trr][ans[i].trc]=='Q'||brd.brd[ans[i].trr][ans[i].trc]=='q')
            x+=900;
        ans2.pb({x,ans[i]});
    }
    ans.clear();
    for(int i=1;i<ans2.size();i++){
        if(ans2[i].f>ans2[i-1].f){
            swap(ans2[i].f,ans2[i-1].f);
            i--;
        }
    }
    for(int i=0;i<ans2.size();i++)
        ans.pb(ans2[i].s);
    tmpbrd=brd;
    return ans;
}
int evaluateboard(board brd){
    return brd.eval;
}
in tim=0;
in tllimit=5;
int nds;
int minimax(int depth,board brd,bool ismx,int tardepth=4,in alpha=-30000,in beta=30000){
    //vis[br(brd.fen)]++;
    nds++;
    if(abs(brd.eval)>10000){
        vis[br(brd.fen)]--;
        return brd.eval;
    }
    if((brd.halfmove==100||(0&&vis[br(brd.fen)]>=2))&&depth){
        vis[br(brd.fen)]--;
        return 0;
    }
    if(depth>=tardepth){
        if(depth>=tardepth){
            vis[br(brd.fen)]--;
            return evaluateboard(brd);
        }
        vector<stmove> moves=calccap(brd);
        if(moves.empty()){
            moves=calcmoves(brd);
            if(moves.size()){
                //vis[br(brd.fen)]--;
                return evaluateboard(brd);
            }
            board brd2=brd;
            brd2.turn=!brd2.turn;
            vector<stmove> temp=calcmoves(brd2,1);
            bool bol=1;
            for(int j=0;j<(int)temp.size()&&bol;j++){
                if(brd2.brd[temp[j].trr][temp[j].trc]=='K'||brd2.brd[temp[j].trr][temp[j].trc]=='k')
                    bol=0;
            }
            int ret=30000*(ismx?-1:1);
            if(bol)
                ret=0;
            //vis[br(brd.fen)]--;
            if(bol)
                return 0;
            return 30000*(ismx?-1:1);
        }
        if(ismx){
            int mx=evaluateboard(brd),mxi=0;
            alpha=max(alpha,mx);
            if(beta<=alpha){
                vis[br(brd.fen)]--;
                return mx;
            }
            for(int i=0;i<(int)moves.size();i++){
                board brd2=domove(brd,moves[i]);
                int x=minimax(depth+1,brd2,!ismx,tardepth,alpha,beta);
                if(x>mx){
                    mx=x;
                    mxi=i;
                }
                alpha=max(alpha,mx);
                if(beta<=alpha)
                    break;
            }
            //vis[br(brd.fen)]--;
            return mx;
        }
        else{
            int mx=evaluateboard(brd),mxi=0;
            beta=min(beta,mx);
            if(beta<=alpha){
                vis[br(brd.fen)]--;
                return mx;
            }
            for(int i=0;i<(int)moves.size();i++){
                board brd2=domove(brd,moves[i]);
                int x=minimax(depth+1,brd2,!ismx,tardepth,alpha,beta);
                if(x<mx){
                    mx=x;
                    mxi=i;
                }
                beta=min(beta,mx);
                if(beta<=alpha)
                    break;
            }
            //vis[br(brd.fen)]--;
            return mx;
        }
    }
    int xx=evaluateboard(brd);
    if(abs(xx)>20000){
        //vis[br(brd.fen)]--;
        return xx;
    }
	vector<stmove> moves=calcmoves(brd,(depth>2));
	if(moves.size()==0){
		board brd2=brd;
		brd2.turn=!brd2.turn;
		vector<stmove> temp=calcmoves(brd2,1);
		bool bol=1;
		for(int j=0;j<(int)temp.size()&&bol;j++){
            if(brd2.brd[temp[j].trr][temp[j].trc]=='K'||brd2.brd[temp[j].trr][temp[j].trc]=='k')
                bol=0;
        }
        int ret=30000*(ismx?-1:1);
        if(bol)
            ret=0;
        //vis[br(brd.fen)]--;
        if(bol)
        	return 0;
        return 30000*(ismx?-1:1);
	}
    if(ismx){
    	int mx=-30000,mxi=0;
		for(int i=0;i<(int)moves.size();i++){
			board brd2=domove(brd,moves[i]);
			int x=minimax(depth+1,brd2,!ismx,tardepth,alpha,beta);
			if(x>mx){
				mx=x;
				mxi=i;
			}
			alpha=max(alpha,mx);
			if(beta<=alpha){
				break;
			}
		}
		if(depth==0){
			cur=domove(brd,moves[mxi],1);
		}
		//vis[br(brd.fen)]--;
		return mx;
    }
    else{
        int mx=30000,mxi=0;
		for(int i=0;i<(int)moves.size();i++){
			board brd2=domove(brd,moves[i]);
			int x=minimax(depth+1,brd2,!ismx,tardepth,alpha,beta);
			if(x<mx){
				mx=x;
				mxi=i;
			}
			beta=min(beta,mx);
			if(beta<=alpha){
				break;
			}
		}
		if(depth==0){
			cur=domove(brd,moves[mxi],1);
		}
		//vis[br(brd.fen)]--;
		return mx;
    }
}
void initboard(){
    while((GetKeyState(VK_LBUTTON)&0x8000)==0);
    POINT p;
    GetCursorPos(&p);
    xx1=p.x,yy1=p.y;
    Sleep(300);
    while((GetKeyState(VK_LBUTTON)&0x8000)==0);
    GetCursorPos(&p);
    xx2=p.x,yy2=p.y;
}
map<string,string> book;
void init(){
    vis.clear();
    cur.fen="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    cur.endgame=0;
    cur.eval=0;
    cur.whash=cur.bhash=65535;
    cur.bkpos=4;
    cur.wkpos=60;
    cur.halfmove=0;
    cur.movecnt=1;
    cur.hcw=0;
    cur.hcb=0;
    cur.eval=0;
    cur.endgame=0;
    cur.qcnt=2;
    cur.pcnt=8;
}
void uci(){
    string inp="";
    getline(cin,inp);
    {
        if(inp=="quit"){
            exit(0);
        }
        if(inp=="uci"){
            cout<<"id name AihayBot\nid author aihay\ninfo string uci done\nuciok\n";
            uci();
            return;
        }
        if(inp=="isready"){
            cout<<"readyok\n";
            uci();
            return;
        }
        if(inp=="ucinewgame"){
            uci();
            return;
        }
        if(br(inp)=="position"){
            if(inp=="position startpos"){
                init();
                convertfromfen(cur);
            }
            else if(inp[9]=='s'){
                init();
                convertfromfen(cur);
                int idx=0;
                string cr="";
                inp+=" ";
                while(idx<inp.size()){
                    if(inp[idx]==' '){
                        if(cr=="position"||cr=="startpos"||cr=="moves"){
                            idx++;
                            cr="";
                            continue;
                        }
                        string s=cr;
                        int str=7-(s[1]-'1'),stc=s[0]-'a',trr=7-(s[3]-'1'),trc=s[2]-'a';
                        char c=s[4];
                        if(cur.turn==0)
                            c=toupper(c);
                        cur=domove(cur,{str,stc,trr,trc,c});
                        vis[br(cur.fen)]++;
                        cr="";
                        idx++;
                        continue;
                    }
                    cr+=inp[idx++];
                }
            }
            else if(inp[9]=='f'){
                init();
                convertfromfen(cur);
                int idx=0;
                string cr="";
                inp+=" ";
                int spcnt=0;
                while(idx<inp.size()){
                    if(inp[idx]==' '){
                        if(cr=="position"||cr=="startpos"||cr=="moves"||cr=="fen"){
                            idx++;
                            cr="";
                            continue;
                        }
                        if(cr.size()>5){
                            spcnt++;
                            if(spcnt==6){
                                cur.fen=cr;
                                cr="";
                                idx++;
                                convertfromfen(cur);
                                continue;
                            }
                            else{
                                cr+=" ";
                                idx++;
                                continue;
                            }
                        }
                        string s=cr;
                        int str=7-(s[1]-'1'),stc=s[0]-'a',trr=7-(s[3]-'1'),trc=s[2]-'a';
                        char c=s[4];
                        if(cur.turn==0)
                            c=toupper(c);
                        cur=domove(cur,{str,stc,trr,trc,c});
                        vis[br(cur.fen)]++;
                        cr="";
                        idx++;
                        continue;
                    }
                    cr+=inp[idx++];
                }
            }
            return;
        }
    }
    if(br(inp)=="go"){
        nds=0;
        vis[br(cur.fen)]--;
        if(inp=="go infinite"){
            int curdepth=5,tim2=time(0);
            while(time(0)-tim2<60){
                tllimit=30;
                tim=time(0);
                minimax(1,cur,!cur.turn,curdepth+1);
                if(time(0)-tim>tllimit)
                    break;
                curdepth++;
            }
            curdepth--;
            minimax(0,cur,!cur.turn,curdepth);
        }
        else{
            int wtime=-2,btime=-2;
            string cr="";
            inp+=" ";
            int idx=0;
            while(idx<inp.size()){
                if(inp[idx]==' '){
                    if(cr=="go"||cr=="winc"||cr=="binc"){
                        idx++;
                        cr="";
                        continue;
                    }
                    else if(cr=="wtime"){
                        idx++;
                        cr="";
                        wtime=-1;
                        continue;
                    }
                    else if(cr=="btime"){
                        idx++;
                        cr="";
                        btime=-1;
                        continue;
                    }
                    int x=0;
                    for(int i=0;i<cr.size();i++){
                        x*=10;
                        x+=cr[i]-'0';
                    }
                    if(wtime==-1)
                        wtime=x;
                    if(btime==-1)
                        btime=x;
                    idx++;
                    cr="";
                    continue;
                }
                cr+=inp[idx++];
            }
            int mytime=(cur.turn==0?wtime:btime);
            if(mytime<=15000){
                tim=time(0);
                tllimit=1;
                minimax(0,cur,!cur.turn,2+(cur.endgame?0:0));
            }
            else if(mytime<=60000){
                tim=time(0);
                tllimit=1;
                minimax(0,cur,!cur.turn,6+(cur.endgame?0:0));
            }
            else if(1||mytime<=60000){
                tim=time(0);
                tllimit=10;
                minimax(0,cur,!cur.turn,6+(cur.endgame?0:0));
            }
            else{
                tim=time(0);
                if(mytime<=180000)
                    tllimit=4;
                else
                    tllimit=8;
                minimax(0,cur,!cur.turn,6+(cur.endgame?1:0));
            }
            cout<<nds<<"\n";
        }
        return;
    }
    return;
}
in main(){
    srand(time(0));
    while(1){
        uci();
    }
    return 0;
}
