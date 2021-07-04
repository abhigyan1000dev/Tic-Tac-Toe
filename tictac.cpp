#include<iostream>
#include<stdlib.h>
using namespace std;

bool *painted = new bool[9];
int *content = new int[9];
int wincombo[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
int turn;
int filled;
int result;
int choice;

class Game{
public:
    void reload(){
        turn=1;
        filled=0;
        result=0;
        for(int i=0;i<9;i++){
            painted[i]=false;
            content[i]=i+1;
        }
        cout<<"Tic - Tac Toe\nEnter\n1 - Kid mode\n2 - Men mode\n3 - Legend mode\n4 - God mode"<<endl;
        cin>>choice;
        update();
    }

    void update(){
        int ch;
        while(1){
            printing();
            if(checkForWinner(content)==0){
                if(turn%2!=0){
                    cout<<"\n\n\n"<<"Please enter the number (from 1-9) where you want to enter X"<<" : ";
                    cin>>ch;
                    if(!(ch>=1 || ch<=9)){
                        cout<<"\nPlease enter a valid choice Press any key to TRY AGAIN and press enter : ";
                        char trial;
                        cin>>trial;
                        continue;
                    }
                }
            }
            else {
                if(result==88){cout<<"\n\n"<<"X has WON...!!";}
                else if(result==79){cout<<"\n\n"<<"O has WON...!!";}
                break;
            }

            if(turn%2!=0){
                if(painted[ch-1]==true){
                    char trial;
                    cout<<"\n\nTHAT SPACE IS ALREADY OCCUPIED...!!...Press any key to TRY AGAIN and press enter : ";
                    cin>>trial;
                    continue;
                }
            }

            if(turn%2==0){
                int aimove;
                if(choice==1){
                    int v = rand() % 100 + 1;
                    if(v<50){
                        aimove=random(painted);
                    }
                    else{
                        aimove=ai(content,painted);
                    }
                }
                else if(choice==2){
                    int v = rand() % 100 + 1;
                    if(v<35){
                        aimove=random(painted);
                    }
                    else{
                        aimove=ai(content,painted);
                    }
                }
                else if(choice==3){
                    int v = rand() % 100 + 1;
                    if(v<20){
                        aimove=random(painted);
                    }
                    else{
                        aimove=ai(content,painted);
                    }
                }
                else if(choice==4){
                        aimove=ai(content,painted);
                }
                painted[aimove]=true;
                content[aimove]=79;
                turn++;
                filled++;
            }
            else{
                painted[ch-1]=true;
                content[ch-1]=88;
                turn++;
                filled++;
            }

            if(checkForWinner(content)!=0){
                printing();
                if(result==88){cout<<"\n\n"<<"X has WON...!!";}
                else if(result==79){cout<<"\n\n"<<"O has WON...!!";}
                break;
            }

            if(availability()){
                break;
            }
        }
        playAgain();
    }

    int availability(){
        if(filled==9){
            printing();
            cout<<"\n\nGame Over...!!";
            return 1;
        }
        else{
            return 0;
        }
    }

    int checkForWinner(int content[9]){
        result=0;
        for(int a=0;a<8;a++){
            if(content[wincombo[a][0]]==88&&content[wincombo[a][1]]==88&&content[wincombo[a][2]]==88){
                result=88;
            }
            if(content[wincombo[a][0]]==79&&content[wincombo[a][1]]==79&&content[wincombo[a][2]]==79){
                result=79;
            }
        }
        return result;
    }

    void playAgain(){
        char conf;
        cout<<"\n\nWanna Play Again ?y/n  :   ";
        cin>>conf;
        if(conf=='y'){reload();}
        else{cout<<"BYE...!!";}
    }

    int printing(){
        system("cls");
        switch(choice){
            case 1:
                cout<<"------------------------Kid Mode-------------------------------\n"<<endl;
                break;
            case 2:
                cout<<"------------------------Men Mode-------------------------------\n"<<endl;
                break;
            case 3:
                cout<<"------------------------Legend Mode-------------------------------\n"<<endl;
                break;
            case 4:
                cout<<"------------------------God Mode-------------------------------\n"<<endl;
                break;
        }
        for(int i=0;i<9;i++){
            if(i==3||i==6){cout<<"\n\n";}
            if(content[i]==88)
            cout<<"\t"<<"X";
            else if(content[i]==79)
            cout<<"\t"<<"O";
            else
            cout<<"\t"<<content[i];
        }
    }

    int ai(int mat[9],bool paint[9]){
        int pc=79;
        int pl=88;
        int sc=0;
        int best=-9999;
        int optimi=0;

        for(int i=0;i<9;i++){
            if(paint[i]==false){
                paint[i]=true;
                mat[i]=pc;
                sc=-(negmax(mat, paint, pl, pc));
                paint[i]=false;
                mat[i]=i+1;
                if(sc>best){
                    best=sc;
                    optimi=i;
                }
            }
        }
        return optimi;
    }

    int negmax(int mat[9], bool paint[9],int pl1,int pl2){
        int best = -9999;
    	int sc = 0;

    	if (checkForWinner(mat) == pl1)
    		return 1000;
    	else if (checkForWinner(mat) == pl2)
    		return -1000;

    	for (int i = 0; i < 9; i++) {
    		if (paint[i] == false) {
                paint[i]=true;
                mat[i] = pl1;
    			sc = -(negmax(mat, paint, pl2, pl1));
    			paint[i]=false;
                mat[i]=i+1;
    			if (sc >= best) {
    				best= sc;
    			}
    		}
    	}

    	if (best == -9999 || best == 0)
    		return 0;

    	else if (best < 0)
    		return best + 1;

    	else if (best > 0)
    		return best - 1;
    }

    int random(bool paint[9]){
        int c=0;
        int val;
        int i;
        for(i=0;i<9;i++)
            if(paint[i]==false)c++;

        val=rand() % c + 1;
        c=0;
        for(i=0;i<9;i++){
            if(paint[i]==false)c++;
            if(c==val)break;
        }
        return i;
    }
};

int main(){
    Game gamer;
    gamer.reload();
}