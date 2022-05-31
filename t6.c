#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

struct frame 
{
	int first;
	int second;
	int third;

	int strike;
	int spare;

	int score;
};


struct frame  game[11];

int current_frame_no ;
int latest_sum_up_frame_no ;
char *fgets();

main()
{
	printf("Bowling Score Calculation\n");
	latest_sum_up_frame_no=0;
	for (current_frame_no=1; current_frame_no<=10; current_frame_no++)
	{
		get_score();
		compute_score();
		print_score();
	}
}

get_score()
{
	int j, k, l;
	char s[100];
	int cn;

	j=k=l=0;
	printf("\nFrame Number is %2d.\n",current_frame_no);
	if (current_frame_no<=9){
		do
		{

			do 
			{
				printf("\nFirst Throw? ");
				cn=scanf("%d",&j);
				if (cn==EOF) exit;
				if (cn!=1) {
					fgets(s, 100, stdin);
					j=-1;
				}

			} while (j<0 || j>10);

			if (j!=10) do
			{
				printf("\nSecond Throw? ");
				cn=scanf("%d",&k);
				if (cn==EOF) exit;
				if(cn!=1)
				{
					fgets(s, 100, stdin);
					k=-1;
				}


			} while (k<0 || k>10);
			printf("\nOK? y/n  ");
			scanf("%s",s);
		}    while(strcmp(s,"y") || (j+k)>10);
		game[current_frame_no].first=j;
		game[current_frame_no].second=k;
		game[current_frame_no].strike=(j==10);
		game[current_frame_no].spare=((k!=10)&&((j+k)==10));

	}
	else /* 10th frame */
	{
		do
		{
			do 
			{
				printf("\nFirst Throw? ");
				cn=scanf("%d",&j);
				if (cn==EOF) exit;
				if(cn!=1)
				{
					fgets(s, 100, stdin);
					j=-1;

				}
			} while (j<0 || j>10);
			do
			{
				printf("\nSecond Throw? ");
				cn=scanf("%d",&k);
				if (cn==EOF) exit;
				if(cn!=1)
				{
					fgets(s, 100, stdin);
					k=-1;
				}
			} while (k<0 || k>10);
			if (j==10 || k==10 || j+k==10)
			{
				do
				{
					printf("\nThird Throw? ");
					cn=scanf("%10d",&l);
					if (cn==EOF) exit;
					if (cn!=1){ 
						fgets(s,100,stdin);
						l=-1;

					}

				} while (l<0 || l>10);
			} else l=0;
			printf("\nOK? y/n  ");
			scanf("%s",s);

		}    while(strcmp(s,"y") || 
		       (j==10 && ((k==10 && l>10) || (k<10 && k+l>10))) ||
		       (j<10 && ((j+k==10 && l>10) || (j+k<10 && l!=0))) );
		game[current_frame_no].first=j;
		game[current_frame_no].second=k;
		game[current_frame_no].third=l;
		game[current_frame_no].strike=(j==10);
		game[current_frame_no].spare=((j!=10)&&((j+k)==10));

	}
}




compute_score()
{
if (current_frame_no != 10)
      {
	   if (current_frame_no - latest_sum_up_frame_no ==3)
	     {
		 fix_score(latest_sum_up_frame_no + 1);
		 ++latest_sum_up_frame_no ;
	     }
	  if  (current_frame_no - latest_sum_up_frame_no ==2)
	    {
		if (game[current_frame_no].strike &&
		    game[current_frame_no-1].strike) return;
		else 
		  {	  fix_score(latest_sum_up_frame_no + 1);
			  ++latest_sum_up_frame_no ;
		      }
	    }
                      /* Here, current_frame_no - latest_sum_up_frame_no ==1 */
		if (game[current_frame_no].strike ||
		    game[current_frame_no].spare)	return;
		else
		  {
		      fix_score(current_frame_no);
		      ++latest_sum_up_frame_no ;
		  }
       }
 else    while ( latest_sum_up_frame_no <= current_frame_no)
	    {
	        fix_score(latest_sum_up_frame_no + 1);
		 ++latest_sum_up_frame_no ;
		}      
      
 
}

fix_score(fr)
    int fr;
{
    int sum;
    
    if (fr <10)
      {
	  
	  sum=0;
	  if (game[fr].strike)
	    {
		sum=10;
		if (game[fr+1].strike)
		  {
		      sum=sum+10;
		      if(fr+1 <10) sum=sum+game[fr+2].first;
		      else sum=sum+game[10].second;
		  }
		else sum=sum+game[fr+1].first+game[fr+1].second;
	    }
	  else if (game[fr].spare) sum=10+game[fr+1].first;
	  else sum=game[fr].first+game[fr].second;
	  if (fr==1) game[fr].score=sum; 
	  else game[fr].score=game[fr-1].score+sum;
      }
    else 
	  game[10].score=game[9].score+
	    game[10].first+game[10].second+game[10].third;
}

print_score()


{
	int i;
	printf("Frame No.  ");
	for (i=1; i<=current_frame_no; i++)
	{
		printf(" %d     ",i);
	}
	printf("\n");
	printf("           ");
	for (i=1; i<=current_frame_no; i++)
	{
		if (i<10)
		{

			if (game[i].strike) printf("  ");
			else if (game[i].first==0) printf("G ");
			else printf("%d ",game[i].first);

			if	 (game[i].strike) printf(" X   ");
			else if (game[i].spare) printf(" /   ");
			else if (game[i].second==0) printf(" -   ");
			else printf(" %d   ",game[i].second);
		} else
		/* 10th frame handling */
		{
			if (game[i].strike) printf("X ");
			else if (game[i].first==0) printf("G ");
			else printf("%d ",game[i].first);

			if (game[i].spare) printf(" / ");
			else if	 (game[i].second==10) printf(" X ");
			else if (game[i].second==0) printf(" - ");
			else printf(" %d ",game[i].second);

			/*3rd Frame handling */

			if (game[i].spare || game[i].strike)
			  {
			      if
				((game[i].strike
				    &&game[i].second==10&&game[i].third==10)||
				 (game[i].spare&&game[i].third==10))
				                             printf(" X");
			      else if (game[i].strike && 
				       (game[i].second+game[i].third)==10) 
				printf(" /");
			      else if (game[i].third==0) printf(" - ");
			      else printf(" %d ",game[i].third);

			}
		}
	}


	printf("\n");
	printf("          ");
	for (i=1; (i<=latest_sum_up_frame_no&& i<=10); i++)
		printf("%3d    ",game[i].score);
	printf("\n");
}
