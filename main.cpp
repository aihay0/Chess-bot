#pragma GCC optimize("-Ofast")
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define pb push_back
#define pp push
#define f first
#define s second
#define pawn 1
#define knight 2
#define bishop 3
#define rook 4
#define queen 5
#define king 6
const int MOD=10000019;

int powcalc[20][100];
ll power(ll x,ll y){
    if(powcalc[x][y])
        return powcalc[x][y];
    if(y==0)
        return 1;
    ll z=power(x,y/2);
    z*=z;
    z%=MOD;
    if(y%2)
        z*=x;
    z%=MOD;
    return powcalc[x][y]=z;
}
const string startingposition="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";
const int dir[]={8,-8,1,-1,7,-7,9,-9};
const int mvv_lva[6][6] = {
    105, 205, 305, 405, 505, 605,
    104, 204, 304, 404, 504, 604,
    103, 203, 303, 403, 503, 603,
    102, 202, 302, 402, 502, 602,
    101, 201, 301, 401, 501, 601,
    100, 200, 300, 400, 500, 600,
};
int squarestoedge[64][8];
int pawnpos[64]={0,   0,   0,   0,   0,   0,   0,   0,
50,  50,  50,  50,  50,  50,  50,  50,
10,  10,  20,  30,  30,  20,  10,  10,
5,   5,  10,  25,  25,  10,   5,   5,
0,   0,   0,  20,  20,   0,   0,   0,
5,  -5, -10,   0,   0, -10,  -5,   5,
5,  10,  10, -20, -20,  10,  10,   5,
0,   0,   0,   0,   0,   0,   0,   0};
int pawnposend[64]={0,   0,   0,   0,   0,   0,   0,   0,
80,  80,  80,  80,  80,  80,  80,  80,
50,  50,  50,  50,  50,  50,  50,  50,
30,  30,  30,  30,  30,  30,  30,  30,
20,  20,  20,  20,  20,  20,  20,  20,
10,  10,  10,  10,  10,  10,  10,  10,
10,  10,  10,  10,  10,  10,  10,  10,
0,   0,   0,   0,   0,   0,   0,   0};
int rookpos[64]={0,  0,  0,  0,  0,  0,  0,  0,
10, 15, 15, 15, 15, 15, 15,  10,
5,  5,  5,  5,  5,  5,  5, 5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
0,  0,  0,  5,  5,  0,  0,  0};
int knightpos[64]={-50,-40,-30,-30,-30,-30,-40,-50,
-40,-20,  0,  0,  0,  0,-20,-40,
-30,  0, 10, 15, 15, 10,  0,-30,
-30,  5, 15, 20, 20, 15,  5,-30,
-30,  0, 15, 20, 20, 15,  0,-30,
-30,  5, 10, 15, 15, 10,  5,-30,
-40,-20,  -10,  -5,  -5,  -10,-20,-40,
-50,-40,-30,-30,-30,-30,-40,-50};
int bishoppos[64]={-20,-10,-10,-10,-10,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5, 10, 10,  5,  0,-10,
-10,  5,  5, 10, 10,  5,  5,-10,
-10,  0, 10, 10, 10, 10,  0,-10,
-10, 10, 10, 10, 10, 10, 10,-10,
-10,  5,  0,  0,  0,  0,  5,-10,
-20,-10,-10,-10,-10,-10,-10,-20};
int queenpos[64]={-20,-10,-10, -5, -5,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5,  5,  5,  5,  0,-10,
-5,  0,  5,  5,  5,  5,  0, -5,
0,  0,  5,  5,  5,  5,  0, -5,
-10,  5,  5,  5,  5,  5,  0,-10,
-10,  0,  5,  0,  0,  0,  0,-10,
-20,-10,-10, -5, -5,-10,-10,-20};
int kingpos[64]={-80, -70, -70, -70, -70, -70, -70, -80,
-60, -60, -60, -60, -60, -60, -60, -60,
-40, -50, -50, -60, -60, -50, -50, -40,
-30, -40, -40, -50, -50, -40, -40, -30,
-20, -30, -30, -40, -40, -30, -30, -20,
-10, -20, -20, -20, -20, -20, -20, -10,
20, 20, -5, -5, -5, -5, 20, 20,
20, 30, 10, 0, 0, 10, 30, 20};
int kingposend[64]={-20, -10, -10, -10, -10, -10, -10, -20,
-5, 0, 5, 5, 5, 5, 0, -5,
-10, -5, 20, 30, 30, 20, -5, -10,
-15, -10, 35, 45, 45, 35, -10, -15,
-20, -15, 30, 40, 40, 30, -15, -20,
-25, -20, 20, 25, 25, 20, -20, -25,
-30, -25, 0, 0, 0, 0, -25, -30,
-50, -30, -30, -30, -30, -30, -30, -50};

int indexonboard(int idx,int idy){
    return (7-idx)*8+idy;
}
void precalcste(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            int idx=indexonboard(i,j);
            int north=i;
            int south=7-i;
            int west=j;
            int east=7-j;
            squarestoedge[idx][0]=north;
            squarestoedge[idx][1]=south;
            squarestoedge[idx][2]=east;
            squarestoedge[idx][3]=west;
            squarestoedge[idx][4]=min(north,west);
            squarestoedge[idx][5]=min(south,east);
            squarestoedge[idx][6]=min(north,east);
            squarestoedge[idx][7]=min(south,west);
        }
    }
}
struct board{
    int brd[64];
    bool whitetoplay;
    bool canwhitekingcastle;
    bool canwhitequeencastle;
    bool canblackkingcastle;
    bool canblackqueencastle;
    int enpassanttarget;
    int halfmovecount;
    int movenumber;
    int staticeval;
    int wkingpos;
    int bkingpos;
    int positionhash;
    void fromFEN(string fen){
        this->positionhash=0;
        for(int i=0;i<64;i++){
            this->brd[i]=0;
        }
        int idx=0,idy=0,i;
        for(i=0;i<(int)fen.size();i++){
            if(fen[i]==' '){
                i++;
                break;
            }
            if(fen[i]=='/'){
                idx++;
                idy=0;
                continue;
            }
            if(fen[i]>'0'&&fen[i]<'9'){
                idy+=fen[i]-'0';
                continue;
            }
            bool iswhite=isupper(fen[i]);
            char c=tolower(fen[i]);
            int piece=0;
            if(c=='p')
                piece=pawn;
            else if(c=='n')
                piece=knight;
            else if(c=='b')
                piece=bishop;
            else if(c=='r')
                piece=rook;
            else if(c=='q')
                piece=queen;
            else if(c=='k'){
                piece=king;
                if(iswhite){
                    this->wkingpos=indexonboard(idx,idy);
                }
                else{
                    this->bkingpos=indexonboard(idx,idy);
                }
            }
            int id=indexonboard(idx,idy);
            this->brd[id]=(iswhite<<3)+piece;
            ll xx=(iswhite<<3)+piece;
            xx*=power(16,id);
            xx%=MOD;
            this->positionhash+=xx;
            if(this->positionhash>=MOD)
                this->positionhash-=MOD;
            idy++;
        }
        if(fen[i]=='w')
            this->whitetoplay=1;
        else
            this->whitetoplay=0;
        i+=2;
        if(fen[i]=='K'){
            this->canwhitekingcastle=1;
            i++;
        }
        if(fen[i]=='Q'){
            this->canwhitequeencastle=1;
            i++;
        }
        if(fen[i]=='k'){
            this->canblackkingcastle=1;
            i++;
        }
        if(fen[i]=='q'){
            this->canblackqueencastle=1;
            i++;
        }
        if(fen[i]=='-')
            i++;
        i++;
        if(fen[i]=='-'){
            this->enpassanttarget=0;
            i+=2;
        }
        else{
            int col=fen[i]-'A';
            int row=7-(fen[i]-'1');
            this->enpassanttarget=indexonboard(col,row);
            i+=3;
        }
        this->halfmovecount=0;
        for(;fen[i]!=' ';i++){
            this->halfmovecount*=10;
            this->halfmovecount+=fen[i]-'0';
        }
        i++;
        this->movenumber=0;
        for(;i<(int)fen.size();i++){
            this->movenumber*=10;
            this->movenumber+=fen[i]-'0';
        }
        this->staticeval=0;
        return;
    }
}curboard;
struct stmove{
    int startpos,endpos,piece;
};
void domove(board &brd,stmove &mv,bool bol=0){
    int bspos=mv.startpos-(mv.startpos&7)+(7-(mv.startpos&7));
    int wspos=mv.startpos-(mv.startpos>>3)+((7-(mv.startpos>>3))<<3);
    int bepos=mv.endpos-(mv.endpos&7)+(7-(mv.endpos&7));
    int wepos=mv.endpos-(mv.endpos>>3)+((7-(mv.endpos>>3))<<3);
    {
        if(brd.brd[mv.startpos]==pawn)
            brd.staticeval+=pawnpos[bspos]-pawnpos[bepos];
        if(brd.brd[mv.startpos]==pawn+8)
            brd.staticeval-=pawnpos[wspos]-pawnpos[wepos];
        if(brd.brd[mv.startpos]==knight)
            brd.staticeval+=knightpos[bspos]-knightpos[bepos];
        if(brd.brd[mv.startpos]==knight+8)
            brd.staticeval-=knightpos[wspos]-knightpos[wepos];
        if(brd.brd[mv.startpos]==bishop)
            brd.staticeval+=bishoppos[bspos]-bishoppos[bepos];
        if(brd.brd[mv.startpos]==bishop+8)
            brd.staticeval-=bishoppos[wspos]-bishoppos[wepos];
        if(brd.brd[mv.startpos]==rook)
            brd.staticeval+=rookpos[bspos]-rookpos[bepos];
        if(brd.brd[mv.startpos]==rook+8)
            brd.staticeval-=rookpos[wspos]-rookpos[wepos];
        if(brd.brd[mv.startpos]==queen)
            brd.staticeval+=queenpos[bspos]-queenpos[bepos];
        if(brd.brd[mv.startpos]==queen+8)
            brd.staticeval-=queenpos[wspos]-queenpos[wepos];
        if(brd.brd[mv.startpos]==king)
            brd.staticeval+=kingpos[bspos]-kingpos[bepos];
        if(brd.brd[mv.startpos]==king+8)
            brd.staticeval-=kingpos[wspos]-kingpos[wepos];
        if(brd.brd[mv.endpos]==pawn)
            brd.staticeval+=pawnpos[bepos];
        if(brd.brd[mv.endpos]==pawn+8)
            brd.staticeval-=pawnpos[wepos];
        if(brd.brd[mv.endpos]==knight)
            brd.staticeval+=knightpos[bepos];
        if(brd.brd[mv.endpos]==knight+8)
            brd.staticeval-=knightpos[wepos];
        if(brd.brd[mv.endpos]==bishop)
            brd.staticeval+=bishoppos[bepos];
        if(brd.brd[mv.endpos]==bishop+8)
            brd.staticeval-=bishoppos[wepos];
        if(brd.brd[mv.endpos]==rook)
            brd.staticeval+=rookpos[bepos];
        if(brd.brd[mv.endpos]==rook+8)
            brd.staticeval-=rookpos[wepos];
        if(brd.brd[mv.endpos]==queen)
            brd.staticeval+=queenpos[bepos];
        if(brd.brd[mv.endpos]==queen+8)
            brd.staticeval-=queenpos[wepos];
        if(brd.brd[mv.endpos]==king)
            brd.staticeval+=kingpos[bepos];
        if(brd.brd[mv.endpos]==king+8)
            brd.staticeval-=kingpos[wepos];
    }
    brd.halfmovecount++;
    if((brd.brd[mv.startpos]&7)==pawn||brd.brd[mv.endpos])
        brd.halfmovecount=0;
    if((brd.brd[mv.startpos]&7)==pawn&&(abs(mv.endpos-mv.startpos)&7)&&brd.brd[mv.endpos]==0){
        if(brd.whitetoplay){
            brd.brd[mv.endpos-8]=0;
            brd.staticeval+=100;
            brd.staticeval+=pawnpos[bepos-8];
        }
        else{
            brd.brd[mv.endpos+8]=0;
            brd.staticeval-=100;
            brd.staticeval-=pawnpos[(mv.endpos+8)-((mv.endpos+8)>>3)+((7-((mv.endpos+8)>>3))<<3)];
        }
    }
    int piece=brd.brd[mv.endpos];
    if(piece==pawn)
        brd.staticeval+=100;
    if(piece==pawn+8)
        brd.staticeval-=100;
    if(piece==knight)
        brd.staticeval+=300;
    if(piece==knight+8)
        brd.staticeval-=300;
    if(piece==bishop)
        brd.staticeval+=325;
    if(piece==bishop+8)
        brd.staticeval-=325;
    if(piece==rook)
        brd.staticeval+=500;
    if(piece==rook+8)
        brd.staticeval-=500;
    if(piece==queen)
        brd.staticeval+=900;
    if(piece==queen+8)
        brd.staticeval-=900;
    if(piece==king)
        brd.staticeval+=500000;
    if(piece==king+8)
        brd.staticeval-=500000;
    if(mv.startpos==0||mv.endpos==0)
        brd.canwhitequeencastle=0;
    if(mv.startpos==7||mv.endpos==7)
        brd.canwhitekingcastle=0;
    if(mv.startpos==56||mv.endpos==56)
        brd.canblackqueencastle=0;
    if(mv.startpos==63||mv.endpos==63)
        brd.canblackkingcastle=0;
    if(mv.startpos==4)
        brd.canwhitekingcastle=brd.canwhitequeencastle=0;
    if(mv.startpos==60)
        brd.canblackkingcastle=brd.canblackqueencastle=0;
    ll xx=power(16,mv.startpos);
    xx*=brd.brd[mv.startpos];
    xx%=MOD;
    xx=brd.positionhash-xx+MOD;
    if(xx>=MOD)
        xx-=MOD;
    brd.positionhash=xx;
    xx=power(16,mv.endpos);
    xx*=brd.brd[mv.endpos];
    xx%=MOD;
    xx=brd.positionhash-xx+MOD;
    if(xx>=MOD)
        xx-=MOD;
    brd.positionhash=xx;
    xx=power(16,mv.endpos);
    xx*=brd.brd[mv.startpos];
    xx%=MOD;
    xx=brd.positionhash+xx;
    if(xx>=MOD)
        xx-=MOD;
    brd.positionhash=xx;
    brd.brd[mv.endpos]=brd.brd[mv.startpos];
    brd.brd[mv.startpos]=0;
    brd.whitetoplay=!brd.whitetoplay;
    if(brd.whitetoplay)
        brd.movenumber++;
    if((mv.endpos>>3)==7&&(brd.brd[mv.endpos]&7)==pawn){
        if(!mv.piece)
            mv.piece=queen;
        brd.brd[mv.endpos]=8|(mv.piece?mv.piece:queen);
        if((mv.piece&7)==queen)
            brd.staticeval+=800;
        else if(mv.piece-8==rook)
            brd.staticeval+=500;
        else if(mv.piece-8==bishop)
            brd.staticeval+=325;
        else
            brd.staticeval+=300;
    }
    if(mv.endpos<8&&brd.brd[mv.endpos]==pawn){
        if(!mv.piece)
            mv.piece=queen;
        brd.brd[mv.endpos]=(mv.piece?mv.piece:queen);
        if(mv.piece==queen)
            brd.staticeval-=800;
        else if(mv.piece==rook)
            brd.staticeval-=500;
        else if(mv.piece==bishop)
            brd.staticeval-=325;
        else
            brd.staticeval-=300;
    }
    if((brd.brd[mv.endpos]&7)==pawn&&abs(mv.endpos-mv.startpos)==16)
        brd.enpassanttarget=(mv.startpos+mv.endpos)>>1;
    else
        brd.enpassanttarget=0;
    if((brd.brd[mv.endpos]&7)==king&&abs(mv.endpos-mv.startpos)==2){
        if(mv.endpos==2)
            brd.brd[0]=0,brd.brd[3]=rook+8;
        else if(mv.endpos==6)
            brd.brd[7]=0,brd.brd[5]=rook+8,brd.staticeval+=5;
        else if(mv.endpos==62)
            brd.brd[63]=0,brd.brd[61]=rook;
        else
            brd.brd[56]=0,brd.brd[59]=rook,brd.staticeval-=5;
    }
    if(brd.brd[mv.endpos]==king)
        brd.bkingpos=mv.endpos;
    if(brd.brd[mv.endpos]==king+8)
        brd.wkingpos=mv.endpos;
    if(bol){
        cout<<"bestmove "<<char(mv.startpos%8+'a')<<mv.startpos/8+1<<char(mv.endpos%8+'a')<<mv.endpos/8+1;
        if(mv.piece)
            cout<<(mv.piece==queen?'q':mv.piece==rook?'r':mv.piece==bishop?'b':'n');
        cout<<'\n';
    }
    return;
}
bool attacked(board &brd,int id,bool col){
    for(int d=0;d<8;d++){
        for(int dist=0;dist<squarestoedge[id][d];dist++){
            int target=id+dir[d]*(dist+1);
            int targetpiece=brd.brd[target];
            if(targetpiece&&((targetpiece&8)>>3)==col)
                break;
            if(targetpiece){
                if((targetpiece&7)==bishop&&d<4)
                    break;
                if((targetpiece&7)==rook&&d>3)
                    break;
                if((targetpiece&7)==king&&dist)
                    break;
                if((targetpiece&7)==queen||(targetpiece&7)==rook||(targetpiece&7)==bishop||(targetpiece&7)==king)
                    return 1;
                break;
            }
        }
    }
    int idx=7-id/8,idy=id%8;
    if(idx>1&&idy&&(brd.brd[id+15]&7)==knight&&(brd.brd[id+15]&8)!=col*8)
        return 1;
    if(idx&&idy>1&&(brd.brd[id+6]&7)==knight&&(brd.brd[id+6]&8)!=col*8)
        return 1;
    if(idx>1&&idy<7&&(brd.brd[id+17]&7)==knight&&(brd.brd[id+17]&8)!=col*8)
        return 1;
    if(idx&&idy<6&&(brd.brd[id+10]&7)==knight&&(brd.brd[id+10]&8)!=col*8)
        return 1;
    if(idx<6&&idy&&(brd.brd[id-17]&7)==knight&&(brd.brd[id-17]&8)!=col*8)
        return 1;
    if(idx<7&&idy<6&&(brd.brd[id-6]&7)==knight&&(brd.brd[id-6]&8)!=col*8)
        return 1;
    if(idx<6&&idy<7&&(brd.brd[id-15]&7)==knight&&(brd.brd[id-15]&8)!=col*8)
        return 1;
    if(idx<7&&idy>1&&(brd.brd[id-10]&7)==knight&&(brd.brd[id-10]&8)!=col*8)
        return 1;
    if(!col){
        if(id%8<7&&brd.brd[id-7]==pawn+8)
            return 1;
        if(id%8&&brd.brd[id-9]==pawn+8)
            return 1;
    }
    else{
        if(id%8&&brd.brd[id+7]==pawn)
            return 1;
        if(id%8<7&&brd.brd[id+9]==pawn)
            return 1;
    }
    return 0;
}
vector<stmove> moves;
void generateslidingmoves(board &brd,int &idx,int &piece){
    for(int d=((piece&7)==bishop?4:0);d<((piece&7)==rook?4:8);d++){
        for(int dist=0;dist<squarestoedge[idx][d];dist++){
            int target=idx+dir[d]*(dist+1);
            int targetpiece=brd.brd[target];
            if(targetpiece&&((targetpiece&8)>>3)==brd.whitetoplay)
                break;
            moves.pb({idx,target,0});
            if(targetpiece)
                break;
        }
    }
}
void generateknightmoves(board &brd,int &id){
    int idx=7-(id>>3),idy=(id&7);
    if(idx>1&&idy&&(((brd.brd[id+15]&7)==0)||((brd.brd[id+15]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id+15,0});
    if(idx&&idy>1&&(((brd.brd[id+6]&7)==0)||((brd.brd[id+6]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id+6,0});
    if(idx>1&&idy<7&&(((brd.brd[id+17]&7)==0)||((brd.brd[id+17]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id+17,0});
    if(idx&&idy<6&&(((brd.brd[id+10]&7)==0)||((brd.brd[id+10]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id+10,0});
    if(idx<6&&idy&&(((brd.brd[id-17]&7)==0)||((brd.brd[id-17]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id-17,0});
    if(idx<7&&idy<6&&(((brd.brd[id-6]&7)==0)||((brd.brd[id-6]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id-6,0});
    if(idx<6&&idy<7&&(((brd.brd[id-15]&7)==0)||((brd.brd[id-15]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id-15,0});
    if(idx<7&&idy>1&&(((brd.brd[id-10]&7)==0)||((brd.brd[id-10]&8)>>3)!=brd.whitetoplay))
        moves.pb({id,id-10,0});
    return;
}
void generatepawnmoves(board &brd,int &id){
    if(brd.whitetoplay){
        if(brd.brd[id+8]==0){
            moves.pb({id,id+8,0});
            if((id>>3)==1&&brd.brd[id+16]==0)
                moves.pb({id,id+16,0});
        }
        if((id&7)&&(((brd.brd[id+7]&8)==0&&brd.brd[id+7])||brd.enpassanttarget==id+7))
            moves.pb({id,id+7});
        if(id%8<7&&(((brd.brd[id+9]&8)==0&&brd.brd[id+9])||brd.enpassanttarget==id+9))
            moves.pb({id,id+9,0});
    }
    else{
        if(brd.brd[id-8]==0){
            moves.pb({id,id-8,0});
            if((id>>3)==6&&brd.brd[id-16]==0)
                moves.pb({id,id-16,0});
        }
        if((id&7)<7&&(((brd.brd[id-7]&8)==8&&brd.brd[id-7])||brd.enpassanttarget==id-7))
            moves.pb({id,id-7});
        if((id&7)&&(((brd.brd[id-9]&8)==8&&brd.brd[id-9])||(brd.enpassanttarget==id-9&&brd.enpassanttarget)))
            moves.pb({id,id-9,0});
    }
    return;
}
void generatekingmoves(board &brd,int &id){
    for(int i=0;i<8;i++){
        if(squarestoedge[id][i]&&(brd.brd[id+dir[i]]==0||((brd.brd[id+dir[i]]&8)>>3)!=brd.whitetoplay))
            moves.pb({id,id+dir[i],0});
    }
    if(brd.whitetoplay&&brd.canwhitekingcastle&&brd.brd[5]==0&&brd.brd[6]==0&&!attacked(brd,4,brd.whitetoplay)&&!attacked(brd,5,brd.whitetoplay)&&!attacked(brd,6,brd.whitetoplay))
        moves.pb({4,6});
    if(brd.whitetoplay&&brd.canwhitequeencastle&&brd.brd[3]==0&&brd.brd[2]==0&&brd.brd[1]==0&&!attacked(brd,4,brd.whitetoplay)&&!attacked(brd,3,brd.whitetoplay)&&!attacked(brd,2,brd.whitetoplay))
        moves.pb({4,2});
    if(!brd.whitetoplay&&brd.canblackkingcastle&&brd.brd[61]==0&&brd.brd[62]==0&&!attacked(brd,60,brd.whitetoplay)&&!attacked(brd,61,brd.whitetoplay)&&!attacked(brd,62,brd.whitetoplay))
        moves.pb({60,62});
    if(!brd.whitetoplay&&brd.canblackqueencastle&&brd.brd[59]==0&&brd.brd[58]==0&&brd.brd[57]==0&&!attacked(brd,60,brd.whitetoplay)&&!attacked(brd,59,brd.whitetoplay)&&!attacked(brd,58,brd.whitetoplay))
        moves.pb({60,58});
    return;
}
vector<stmove> generatemoves(board &brd){
    moves.clear();
    for(int i=0;i<64;i++){
        int piece=brd.brd[i];
        if(((piece&8)>>3)!=brd.whitetoplay||piece==0)
            continue;
        if((piece&7)!=pawn&&(piece&7)!=king&&(piece&7)!=knight)
            generateslidingmoves(brd,i,piece);
        if((piece&7)==knight)
            generateknightmoves(brd,i);
        if((piece&7)==pawn)
            generatepawnmoves(brd,i);
        if((piece&7)==king)
            generatekingmoves(brd,i);
    }
    vector<pair<int,int>> v;
    board brd2;
    for(int i=0;i<(int)moves.size();i++){
        int x=0;
        if(brd.brd[moves[i].endpos])
            x=mvv_lva[(brd.brd[moves[i].startpos]&7)-1][(brd.brd[moves[i].endpos]&7)-1]*100;
        brd2=brd;
        domove(brd2,moves[i]);
        x+=brd2.staticeval*(brd.whitetoplay?1:-1);
        if(!attacked(brd2,(brd.whitetoplay?brd2.wkingpos:brd2.bkingpos),brd.whitetoplay))
            v.pb({-x,i});
    }
    sort(v.begin(),v.end());
    vector<stmove> mvs2;
    for(int i=0;i<(int)v.size();i++)
        mvs2.pb(moves[v[i].s]);
    return mvs2;
}
void printboard(board &brd){
    for(int i=0;i<8;i++){
        cout<<8-i<<"   ";
        for(int j=0;j<8;j++){
            int id=indexonboard(i,j);
            char c='.';
            if((brd.brd[id]&7)==pawn)
                c='p';
            else if((brd.brd[id]&7)==knight)
                c='n';
            else if((brd.brd[id]&7)==bishop)
                c='b';
            else if((brd.brd[id]&7)==rook)
                c='r';
            else if((brd.brd[id]&7)==queen)
                c='q';
            else if((brd.brd[id]&7)==king)
                c='k';
            if((brd.brd[id]&8)==8)
                c=toupper(c);
            cout<<c;
        }
        cout<<"\n";
    }
    cout<<"\n\n    ABCDEFGH\n";
    cout<<(brd.whitetoplay?"White":"Black")<<" to play\n";
    cout<<"Can white castle king side: "<<(brd.canwhitekingcastle?"Yes\n":"No\n");
    cout<<"Can white castle queen side: "<<(brd.canwhitequeencastle?"Yes\n":"No\n");
    cout<<"Can black castle king side: "<<(brd.canblackkingcastle?"Yes\n":"No\n");
    cout<<"Can black castle queen side: "<<(brd.canblackqueencastle?"Yes\n":"No\n");
    if(brd.enpassanttarget==0)
        cout<<"Possible Enpassant target: none\n";
    else
        cout<<"Possible Enpassant target: "<<char(brd.enpassanttarget/8+'A')<<brd.enpassanttarget%8+1<<"\n";
    cout<<"Half move count: "<<brd.halfmovecount<<"\n";
    cout<<"Move number: "<<brd.movenumber<<"\n\n\n";
}
int evaluateboard(board &brd){
    return brd.staticeval;
    int ans=0;
    for(int i=0;i<64;i++){
        if(brd.brd[i]==pawn)
            ans-=100;
        if(brd.brd[i]==pawn+8)
            ans+=100;
        if(brd.brd[i]==knight)
            ans-=300;
        if(brd.brd[i]==knight+8)
            ans+=300;
        if(brd.brd[i]==bishop)
            ans-=325;
        if(brd.brd[i]==bishop+8)
            ans+=325;
        if(brd.brd[i]==rook)
            ans-=500;
        if(brd.brd[i]==rook+8)
            ans+=500;
        if(brd.brd[i]==queen)
            ans-=900;
        if(brd.brd[i]==queen+8)
            ans+=900;
        if(brd.brd[i]==king)
            ans-=10000;
        if(brd.brd[i]==king+8)
            ans+=10000;
    }
    return ans;
}
ll nds,tardepth;
stmove bestmove;
int tim,mytime,vis[10000020];
int minimax(int depth,board &brd,bool ismax,int alpha=-500000,int beta=500000,bool bol=1){
    vis[brd.positionhash]++;
    int x=evaluateboard(brd);
    if((abs(x)>=100000||((bestmove.endpos!=0||bestmove.startpos!=0)&&(int)GetTickCount()-tim>(mytime-1000)/30))&&depth){
        vis[brd.positionhash]--;
        return x;
    }
    if((brd.halfmovecount>=100||(vis[brd.positionhash]>2&&depth))&&depth)
        return 0;
    if(depth>=tardepth){
        nds++;
        vis[brd.positionhash]--;
        return x;
    }
    vector<stmove> mvs=generatemoves(brd);
    if(mvs.size()==0){
        board brd2=brd;
        brd2.whitetoplay=!brd2.whitetoplay;
        mvs=generatemoves(brd2);
        vis[brd.positionhash]--;
        for(int i=0;i<(int)mvs.size();i++){
            if((brd.brd[mvs[i].endpos]&7)==king){
                return brd.whitetoplay?-5000000:5000000;
            }
        }
        return 0;
    }
    if(ismax){
        int mx=-100000,mxi=0;
        bool dn=0;
        for(int i=0;i<(int)mvs.size()&&depth==0&&!dn;i++){
            if(mvs[i].startpos==bestmove.startpos&&mvs[i].endpos==bestmove.endpos){
                dn=1;
                board brd2=brd;
                domove(brd2,mvs[i]);
                x=minimax(depth+1-(brd.brd[mvs[i].endpos]&&(brd.brd[mvs[i].endpos]&7)!=pawn&&depth==tardepth-1),brd2,0,alpha,beta,0);
                if(x>mx){
                    mx=x;
                    mxi=i;
                }
                alpha=max(alpha,mx);
                if(beta<=alpha)
                    break;
            }
        }
        for(int i=0;i<(int)mvs.size();i++){
            if(dn&&mvs[i].startpos==bestmove.startpos&&mvs[i].endpos==bestmove.endpos)
                continue;
            board brd2=brd;
            domove(brd2,mvs[i]);
            x=minimax(depth+1-(brd.brd[mvs[i].endpos]&&(brd.brd[mvs[i].endpos]&7)!=pawn&&depth==tardepth-1),brd2,0,alpha,beta,0);
            if(x>mx){
                mx=x;
                mxi=i;
            }
            alpha=max(alpha,mx);
            if(beta<=alpha)
                break;
        }
        if(depth==0&&bol)
            domove(curboard,mvs[mxi]);
        if(depth==0)
            bestmove=mvs[mxi];
        vis[brd.positionhash]--;
        return mx;
    }
    else{
        int mx=100000,mxi=0;
        bool dn=0;
        for(int i=0;i<(int)mvs.size()&&depth==0&&!dn;i++){
            if(mvs[i].startpos==bestmove.startpos&&mvs[i].endpos==bestmove.endpos){
                dn=1;
                board brd2=brd;
                domove(brd2,mvs[i]);
                x=minimax(depth+1-(brd.brd[mvs[i].endpos]&&(brd.brd[mvs[i].endpos]&7)!=pawn&&depth==tardepth-1),brd2,1,alpha,beta,0);
                if(x<mx){
                    mx=x;
                    mxi=i;
                }
                beta=min(beta,mx);
                if(beta<=alpha)
                    break;
            }
        }
        for(int i=0;i<(int)mvs.size();i++){
            if(dn&&mvs[i].startpos==bestmove.startpos&&mvs[i].endpos==bestmove.endpos)
                continue;
            board brd2=brd;
            domove(brd2,mvs[i]);
            x=minimax(depth+1-(brd.brd[mvs[i].endpos]&&(brd.brd[mvs[i].endpos]&7)!=pawn&&depth==tardepth-1),brd2,1,alpha,beta,0);
            if(x<mx){
                mx=x;
                mxi=i;
            }
            beta=min(beta,mx);
            if(beta<=alpha)
                break;
        }
        if(depth==0&&bol)
            domove(curboard,mvs[mxi]);
        if(depth==0)
            bestmove=mvs[mxi];
        vis[brd.positionhash]--;
        return mx;
    }
}
string br(string curs){
    string ans="";
    for(int i=0;i<(int)curs.size()&&curs[i]!=' ';i++)
        ans+=curs[i];
    return ans;
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
            memset(vis,0,sizeof vis);
            if(inp=="position startpos"){
                curboard.fromFEN(startingposition);
                vis[curboard.positionhash]++;
            }
            else if(inp[9]=='s'){
                curboard.fromFEN(startingposition);
                vis[curboard.positionhash]++;
                int idx=0;
                string cr="";
                inp+=" ";
                while(idx<(int)inp.size()){
                    if(inp[idx]==' '){
                        if(cr=="position"||cr=="startpos"||cr=="moves"){
                            idx++;
                            cr="";
                            continue;
                        }
                        string s=cr;
                        int str=7-(s[1]-'1'),stc=s[0]-'a',trr=7-(s[3]-'1'),trc=s[2]-'a';
                        int c=(s[4]=='q'?queen:s[4]=='b'?bishop:s[4]=='r'?rook:knight);
                        if(curboard.whitetoplay)
                            c+=8;
                        stmove cur={indexonboard(str,stc),indexonboard(trr,trc),c};
                        domove(curboard,cur);
                        cr="";
                        idx++;
                        vis[curboard.positionhash]++;
                        continue;
                    }
                    cr+=inp[idx++];
                }
            }
            vis[curboard.positionhash]--;
            return;
        }
    }
    if(br(inp)=="go"){
        nds=0;
        int wtime=-2,btime=-2;
        string cr="";
        inp+=" ";
        int idx=0;
        while(idx<(int)inp.size()){
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
                else if(cr=="movetime"){
                    idx++;
                    cr="";
                    wtime=-1;
                    continue;
                }
                int x=0;
                for(int i=0;i<(int)cr.size();i++){
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
        if(btime==-2)
            btime=wtime;
        mytime=(curboard.whitetoplay?wtime:btime);
        bestmove.startpos=bestmove.endpos=bestmove.piece=0;
        tim=GetTickCount();
        int ev;
        stmove st=bestmove;
        nds=0;
        for(int i=1;(int)GetTickCount()-tim<=(mytime-1000)/30||i<2;i++){
            tardepth=i;
            st=bestmove;
            ev=minimax(0,curboard,curboard.whitetoplay,-500000,500000,0);
            cout<<"info depth "<<i<<" nodes "<<nds<<"\n";
        }
        bestmove=st;
        cout<<"info depth "<<tardepth<<" score cp "<<ev<<" nodes "<<nds<<" speed "<<nds/((GetTickCount()-tim)/1000.0)<<"\n";
        domove(curboard,bestmove,1);
        generatemoves(curboard);
        return;
    }
    return;
}

int main()
{
    precalcste();
    while(1){
        uci();
    }
    return 0;
}
