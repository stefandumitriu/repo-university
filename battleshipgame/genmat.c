#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main()
{
    srand(time(0));
    int mat[12][12],shipsCounter[4]={4,3,2,1}, i ,j;
    for(i = 1; i <= 10; i++){
        for(j = 1; j <= 10; j++)
            mat[i][j]=0;
    }
    for(i = 0; i <= 11; i++){
        mat[i][0] = 2;
        mat[i][11] = 2;
    } 
    for(j = 0; j <= 11; j++){
        mat[0][j] = 2;
        mat[11][j] = 2;
    }
    for(i = 3; i >= 0; i--){
        while(shipsCounter[i] != 0){
            int shipDim = i + 1;
            int free = 1;
            int randDirection = rand() % 2;
            if(randDirection == 0) { // orizontal
                while(1) {
                    int randX = rand() % 10 + 1;
                    int randY = rand() % 10 + 1;
                    if(randX + shipDim > 10) {
                            break;
                    }
                    for(int y = randY - 1; y <= randY + 1; y++)
                    {
                        for(int x = randX - 1; x <= randX + shipDim + 1; x++)
                        {
                            if(mat[y][x]==1)
                                {
                                    free = 0;
                                }
                        }
                    }
                    if(!free)
                    {
                        break;
                    }
                    for(int x = randX; x < randX + shipDim; x++)
                    {
                        mat[randY][x]=1;
                    }
                    shipsCounter[i]--;
                    break;
                }
            }
            if(randDirection == 1) {// vertical
                while(1) {
                    int randX = rand() % 10 + 1;
                    int randY = rand() % 10 + 1;
                    if(randY + shipDim > 10) {
                            break;
                    }
                    for(int y = randY - 1; y <= randY + shipDim + 1; y++)
                    {
                        for(int x = randX - 1; x <= randX + 1; x++)
                        {
                            if(mat[y][x]==1)
                                {
                                    free = 0;
                                }
                        }
                    }
                    if(!free){
                        break;
                    }
                    for(int y = randY; y < randY + shipDim; y++)
                    {
                        mat[y][randX]=1;
                    }
                    shipsCounter[i]--;
                    break;
                }
            }
        }
    }
    for(int a=1;a<=10;a++)
    {
      for(int b=1;b<=10;b++)
             printf("%d ",mat[a][b]);
         printf("\n");
         }
}