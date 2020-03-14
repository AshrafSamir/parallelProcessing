#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc , char * argv[])
{
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	char message[100];	/* storage for message	*/
	int index;
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/


	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank != 0)
	{
		dest = 0;
		int colSiz;
		//int rowSiz1;
		int resutSiz;
        int e;

		MPI_Recv(colSiz, 1, MPI_INT, source, tag, MPI_COMM_WORLD,&status);
		int *arr = (int *)malloc(colSiz*sizeof(int ));

		//MPI_Recv(rowSiz1, 1, MPI_INT, dest, tag, MPI_COMM_WORLD,&status);
		MPI_Recv(resutSiz, 1, MPI_INT, dest, tag, MPI_COMM_WORLD,&status);
		MPI_Recv(arr, colSiz, MPI_INT, dest, tag, MPI_COMM_WORLD,&status);
		int x ;
		int r = 0;
		for(x=0;x<colSiz;x++){
            MPI_Recv(e, 1, MPI_INT, dest, tag, MPI_COMM_WORLD,&status);
            r +=(e*arr[x]);
		}


		MPI_Send(r , 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}else
	{

	    int i,j,r,c,r1,c1,**Matrix1,**Matrix2;


	    printf("enter the number of row=");
        scanf("%d",&r);
        printf("enter the number of column=");
        scanf("%d",&c);

        Matrix1 =(int **)malloc(r*sizeof(int *));
        for(i=0;i<r;i++)Matrix1[i]=(int *)malloc(c*sizeof(int ));

        printf("enter the first matrix element=\n");
        for(i=0;i<r;i++){
            for(j=0;j<c;j++){
                scanf("%d",&Matrix1[i][j]);
            }
        }
        printf("enter the number of row=");
        scanf("%d",&r1);
        printf("enter the number of column=");
        scanf("%d",&c1);

            while(r1!=c){
                printf("They cant be multiplied enter another numbers of row");
                scanf("%d",&r1);
            }


        Matrix2 =(int **)malloc(r1*sizeof(int *));
        for(i=0;i<r1;i++)Matrix2[i]=(int *)malloc(c1*sizeof(int ));

        printf("enter the second matrix element=\n");
        for(i=0;i<r1;i++){
            for(j=0;j<c1;j++){
                scanf("%d",&Matrix2[i][j]);
            }
        }
        int m;
        int turn = 1;
        int rNum = 0;
        int rNum1 = 0;
        for( source = 1; source < p ; source++){
            MPI_Send( c, 1 , MPI_INT, source, tag, MPI_COMM_WORLD);
            //MPI_Send( r1, 1 , MPI_INT, source, tag, MPI_COMM_WORLD);
            MPI_Send( (r*c1), 1 , MPI_INT, source, tag, MPI_COMM_WORLD);
        }



        for(m=0;m<(r*c1);m++){
            MPI_Send( Matrix1[rNum], c , MPI_INT, turn, tag, MPI_COMM_WORLD);
            int e;
            for(e=0;e<r1;e++){
                MPI_Send( Matrix2[rNum1][e], 1 , MPI_INT, turn, tag, MPI_COMM_WORLD);
            }
            turn++;
            if(turn >= p) turn = 0;
            rNum1++;
            if(rNum1 > c1){
                rNum1 = 0;
                rNum++;
            }

        }
		for( source = 1; source < p ; source++)
		{
            MPI_Recv(index, 1, MPI_INT, source, tag, MPI_COMM_WORLD,&status);
			printf("%d\n" , &index);
		}
	}

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
