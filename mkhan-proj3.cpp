//
//    Name:       Khan, Mahmudur
//    Project:    03
//    Due:        November 14, 2016
//    Course:     cs25602-f16
//
//    Description:
//          A small project which reads the maze from the file and finds the shortest path.
//

#include <iostream>
#include <string>
#include <fstream>

//================== SETTING MAXIMUM SIZE FOR THE MAZE. MAKE CHANGES TO CONTROL MAXIMUM SIZE FOR MAZE ================
#define MAX_ROW 24
#define MAX_COL 80

using namespace std;

//============== DECLARING FUNCTION PROTOTYPES =======================================
void getMaze (int mazeArray[MAX_ROW][MAX_COL],int &row, int &col);
bool solveMaze (int mazeArray[MAX_ROW][MAX_COL], char solMaze[MAX_ROW][MAX_COL], int row, int col);
void printMaze (char solMaze[MAX_ROW][MAX_COL], int row, int col);

int main() {
    
    //==================== DECLARING VARIABLES ================
    ifstream infile;
    string fileName;
    bool flag = false;
    int actualRow = 0, actualCol = 0;
    int mazeArray[MAX_ROW][MAX_COL];
    char solMaze[MAX_ROW][MAX_COL];
    

    cout<<"M. Khan's A-Mazing!"<<endl<<endl;
    
    
    //==================== ASKING USER FOR FILE NAME ================
    
    do{
        if (!flag){
            cout<<"Enter the maze file name? ";
            cin>>fileName;
       
            infile.open(fileName.c_str());
            flag = true;
            
        }else{
            cout<<"ERROR: Could Not Open File!"<<endl;
            cout<<"Enter the maze file name? ";
            cin>>fileName;
            infile.open(fileName.c_str());
        }
        
    }while (infile.fail());

    //==================== INNITIALIZING ARRAY  ================
    
    for(int i =0; i <MAX_ROW;i++){
        for (int j=0; j<MAX_COL;j++){
           mazeArray[i][j]= -1;
           solMaze[i][j]= ' ';
        }
    }
    
    //==================== READING FILE INPUTS AND USING ASCII VALUE TO IDENTIFY NEW LINE ================
    bool overFlowFlag=false;
    
    for(int i =0; i <MAX_ROW;i++){
        int j=0;
        int skip=0;
        while (j<MAX_COL && i<MAX_ROW && !overFlowFlag){
         
                int number= infile.get();
                if(number==10)
                {
                    mazeArray[i][j] = number;
                    i++;
                    j=0;
                }
                else
                {
                    mazeArray[i][j]= number;
                    if(mazeArray[i][j]!=-1)
                    {
                        solMaze[i][j]= static_cast<char>(number);
                    }
                    j++;
                }
            if (j==80 && mazeArray[i][j-1]!=-1 && mazeArray[i][j-1]!=10)
            {
                overFlowFlag=true;
                actualRow++;
            }

        }
        
        if(overFlowFlag==true && mazeArray[i][j-1]!=-1){
            do{
                skip = infile.get();
            }while (skip!=10);
            if (skip==10)
                overFlowFlag=false;
        }
        
    }
    
    //============= CALLING FUNCTION TO SOLVE THE MAZE FOR POSSIBLE SOLUTIONS ============
    getMaze(mazeArray, actualRow, actualCol);
    printMaze(solMaze, actualRow, actualCol);
    
    if (!solveMaze(mazeArray,solMaze, actualRow, actualCol))
        cout<<"No solution."<<endl;
    else{
        printMaze(solMaze, actualRow, actualCol);
    }

    cout<<endl<<endl;
    
    return 0;
}



bool solveMaze (int mazeArray[MAX_ROW][MAX_COL],char solMaze[MAX_ROW][MAX_COL], int row, int col){
    
    //=============== CONVERTING MAZE TO NUMERICAL ALTERNATIVE FOR SOLVING =================
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            if (mazeArray[i][j]!=83 && mazeArray[i][j]!=115 && mazeArray[i][j]!=70 && mazeArray[i][j]!=102 && mazeArray[i][j]!= 32)
                mazeArray[i][j]= -3;
            else if (mazeArray[i][j]==83 || mazeArray[i][j]==115)
                mazeArray[i][j]= 0;
            else if (mazeArray[i][j]==70 || mazeArray[i][j]==102)
                mazeArray[i][j]= -2;
            else if (mazeArray[i][j]==32)
                mazeArray[i][j]= -5;
        }
    }
    
    
    //=============== SOLVING MAZE FOR POSSIBLE PATH ===================
    bool flag= false;
    int count=0;
    int path=0;
    int x=0;
    int y=0;
    for (int i=0;i<row*col && flag!=true;i++){
        for (int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(mazeArray[i][j]==count){
                    if((mazeArray[i][j+1]==-2 || mazeArray[i][j-1]==-2 || mazeArray[i+1][j]==-2|| mazeArray[i-1][j]==-2) && flag!=true)
                    {
                        path=count;
                        cout<<endl<<"Path:"<<path<<endl;
                        flag=true;
                        x=i;
                        y=j;
                    }
                    if (mazeArray[i][j+1]==-5 && flag!=true)
                    {
                        mazeArray[i][j+1]=count+1;
                    }
                    if (mazeArray[i][j-1]==-5 && flag!=true)
                    {
                        mazeArray[i][j-1]=count+1;
                    }
                    if (mazeArray[i+1][j]==-5 && flag!=true){
                        mazeArray[i+1][j]=count+1;
                    }
                    if (mazeArray[i-1][j]==-5 && flag!=true){
                        mazeArray[i-1][j]=count+1;
                    }
                }
            }
        }
    
        count++;
    }
    
    
    //================ DRAWING PATH IN THE MAZE ================
    bool redFlag=false;
    solMaze[x][y]='.';
    for (int p=path;p>1 && flag==true;p--)
    {
                if (mazeArray[x][y+1]==p-1 && redFlag!=true)
                {
                    solMaze[x][y+1]='.';
                    y=y+1;
                    redFlag=true;
                }
                if (mazeArray[x][y-1]==p-1 && redFlag!=true)
                {
                    solMaze[x][y-1]='.';
                    y=y-1;
                    redFlag=true;
                }
                if (mazeArray[x+1][y]==p-1 && redFlag!=true){
                    solMaze[x+1][y]='.';
                    x=x+1;
                    redFlag=true;
                }
                if (mazeArray[x-1][y]==p-1 && redFlag!=true){
                    solMaze[x-1][y]='.';
                    x=x-1;
                    redFlag=true;
                }
        redFlag=false;
    }
    return flag;
}

void printMaze (char solMaze[MAX_ROW][MAX_COL], int row, int col){
    
    for(int i =0; i <row;i++){
        for (int j=0; j<col;j++){
            cout<< solMaze[i][j];
        }
        cout<<endl;
    }
}

void getMaze (int mazeArray[MAX_ROW][MAX_COL],int &row, int &col){
    
    //================= FINDING ACTUAL ROW OF THE MAZE ==================
    for(int i=0; i<MAX_ROW;i++){
        for(int j=0;j<MAX_COL;j++){
            if (mazeArray[i][j]!=-1 && mazeArray[i][j+1]==-1)
                row++;
        }
    }
    
    //================= FINDING ACTUAL COLUMN OF THE MAZE ================
    bool flag=false;
    int temp=0;
    
    for (int i=0;i<row;i++){
        for (int j=0;j<MAX_COL && flag!=true;j++)
        {
            if (mazeArray[i][j]==-1)
            {
                flag=true;
            }
            else
                temp++;
        }
        flag=false;
        if (temp>=col)
        {
            col=temp;
            temp=0;
        }
        else
            temp=0;
    }
    
}

