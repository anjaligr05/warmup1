/*
 * Author:      Anjali Gopal Reddy(anjaligr@usc.edu)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#include "cs402.h"

#include "my402list.h"


static char gszProgName[MAXPATHLENGTH];


/*------------- Data Structure holding tokens---------------------------*/

typedef struct tagMy402ListElements {
    char tType;
    long int tTime;
    int tAmount;
    char tDescription[25];
} My402ListElements;

/*-------------------Utility functions-----------------------------------*/
static
void SetProgramName(char *s)
{
    char *c_ptr=strrchr(s, DIR_SEP);

    if (c_ptr == NULL) {
        strcpy(gszProgName, s);
    } else {
        strcpy(gszProgName, ++c_ptr);
    }
}
/*-----------------------Usage-------------------------------------------*/
static
void Usage()
{
    fprintf(stderr,
            "usage: %s %s\n",
            gszProgName, "sort [tfile]");
    exit(-1);
}

/*------------------ProcessOptions---------------------------------------*/
static
int ProcessOptions(int argc, char *argv[])
{
	
	if(argc>3){
	Usage();	
	}
	for (argc--, argv++; argc > 0; argc--, argv++) {
      if(*argv[0]=='s'){
			if (strcmp(*argv, "sort") == 0) {
				       
			return 1;
            } else {
                Usage();
            }
		}
        else {
            Usage();
        }
    }
    return 0;
}

char datearr[15];
char finalamt[15];
char convertedAmt[15];
/*--------------------------validateTimeStamp------------------------------------*/

int validateTimeStamp(My402List *pList,long chktime)
{
	
	 My402ListElem *elem=NULL;
	 My402ListElements *elements;
	  elem=malloc(sizeof(My402ListElem));
	  for (elem=My402ListFirst(pList);elem != NULL;elem=My402ListNext(pList, elem)) 
	  {
		
		elements=(My402ListElements*)elem->obj;
		if(elements->tTime==chktime)
		{
			return(1);//similar time exists
		}
	}
	  return(0);

}


/*-------------------------addTransactionElement----------------------------*/
My402ListElements *addTransactionElement(char *buf){

char tType;
long tTime;
int tAmount;
char tDescription[100];

char *start_ptr;
char *tab_ptr;
char *newline;

char *decptr;

int i=0;

My402ListElements *tElements;

	tElements= malloc(sizeof(My402ListElements));
	
	tab_ptr=buf;
	
	while(tab_ptr != NULL) {		
		
		start_ptr = tab_ptr;
		tab_ptr = strchr(start_ptr,'\t');
			
	if(tab_ptr==NULL ){
			
			while(*start_ptr==' ')
			start_ptr++;
			
			strncpy(tDescription,start_ptr,24);
			tDescription[24]='\0';
			if(strlen(tDescription)==1){
			fprintf(stderr,"Invalid Input in Description\n");	
			free(tElements);
			exit(0);
			}
			strncpy(tElements->tDescription,tDescription,24);
			
			newline=strchr(tElements->tDescription,'\n');
			if(newline!=NULL)
			*newline='\0';
			break;
			}
		
		*tab_ptr++='\0';
	
		
	if(i==0){
	
	tType=start_ptr[0];
	
	if(tType=='-'||tType=='+'){
	
		tElements->tType=tType;
	}
	else
	{
		fprintf(stderr,"Invalid Input in transaction sign\n");
		exit(0);
	}
		
	}
	
		if(i==1){
		
	
		if(strlen(start_ptr)>=11){
		fprintf(stderr,"Invalid Input in time\n");
		exit(0);
		}
	
		tTime=atoi(start_ptr);
		
		//tElements->tTime=(long*)malloc(sizeof(long)*11);
		tElements->tTime=tTime;
		
		
		if(tElements->tTime>time(NULL)){
			fprintf(stderr,"Invalid Input. Time cannot be greater than current time\n");
			free(tElements);
			exit(0);			
		}

				
				}
				
		if(i==2){

			
			if(strlen(start_ptr)>10){
				fprintf(stderr,"Invalid Input in amount (Greater than 10)\n");
				free(tElements);
				exit(0);	
			}
			
			if(strlen(strchr(start_ptr,'.'))>3)
			{
				fprintf(stderr,"Invalid Input in numbers after decimal point (Only 2)\n");
				free(tElements);
				exit(0);
			}
			
			if(start_ptr[0]=='.'){
				fprintf(stderr,"Invalid Input in amount. Must have digits before decimal point\n");
				free(tElements);
				exit(0);
			}
			
			if(start_ptr[0]=='-'){
				fprintf(stderr,"Invalid Input in amount. Cannot be negative\n");
				free(tElements);
				exit(0);
			}
			
			
			decptr=strchr(start_ptr,'.');
			decptr++;
			tAmount=atoi(start_ptr)*100+atoi(decptr);
		
			
				if(tAmount>1000000000||tAmount<0){
				fprintf(stderr,"Invalid Input in amount\n");
				free(tElements);
				exit(0);

				
			}			
			
		
			
			tElements->tAmount=tAmount;

			}
	
			i++;
		if(i>4) {
			fprintf(stderr,"Invalid Input\n. ");
			free(tElements);
			return NULL;
		}
		
		}

		
		if(i!=3){
			fprintf(stderr,"\nInvalid Input. Three tab delimited fields required\n");
			free(tElements);
			return NULL;
		}
		
		
	return tElements;
	

}

/*--------------------printDate--------------------------------------------------*/
char *printDate(char *timestr){
	
	//char *timestr;
	//char timebuf[26];
	char *timebuf=malloc(sizeof(char*)*25);
	memcpy(timebuf,&timestr,25);
	timebuf[25]='\0';
	int j=0;
	
	
	//int timeLength=strlen(timebuf);
	
	
	int i=0;
	while(i<25){
	
	if(i<11){
		
		datearr[j]= timestr[i];
		j++;
	}
	if(i>19){
	datearr[j]= timestr[i];
		j++;
	}
		
		i++;
	}
	return datearr;
}




/*------------------------appendTransactionElements---------------------------------*/
int appendTransactionElements(My402List *pList,My402ListElements *elements){
	
	if(validateTimeStamp(pList,elements->tTime)==1){
			fprintf(stderr,"Invalid Input. Same time stamp exists!.\n");
			free(elements);
			exit(0);
		}
	else{			
	if(My402ListAppend(pList,elements)){
	return 1;	
	}
	}
	return 0;	
}

/*--------------------------createList--------------------------------------*/
void createList(FILE *fp, My402List *pList){
	char buf[1026];
	int len;
	My402ListElements *elements;	
		
	while(fgets(buf, sizeof(buf), fp) != NULL)
     {
		len=strlen(buf);
		if(len>1024){
		fprintf(stderr,"Invalid Input in string length. Only 1024 characters are allowed.\n");
		exit(0);	
		}
		else{
		elements=addTransactionElement(buf);
			if(elements==NULL){
				
			if(fp!=stdin) 
			fclose(fp);
			fprintf(stderr,"Exited\n");
			exit(0);
				
			}
		

			if(!appendTransactionElements(pList,elements)){	
				
			if(fp!=stdin)
			fclose(fp);
			fprintf(stderr,"Error\n");
			exit(0);
				
			}	
		
		}
}
}

static
void BubbleForward(My402List *pList, My402ListElem **pp_elem1, My402ListElem **pp_elem2)
    /* (*pp_elem1) must be closer to First() than (*pp_elem2) */
{
    My402ListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
    My402ListElem *elem1prev=My402ListPrev(pList, elem1);
/*  My402ListElem *elem1next=My402ListNext(pList, elem1); */
/*  My402ListElem *elem2prev=My402ListPrev(pList, elem2); */
    My402ListElem *elem2next=My402ListNext(pList, elem2);

    My402ListUnlink(pList, elem1);
    My402ListUnlink(pList, elem2);
    if (elem1prev == NULL) {
        (void)My402ListPrepend(pList, obj2);
        *pp_elem1 = My402ListFirst(pList);
    } else {
        (void)My402ListInsertAfter(pList, obj2, elem1prev);
        *pp_elem1 = My402ListNext(pList, elem1prev);
    }
    if (elem2next == NULL) {
        (void)My402ListAppend(pList, obj1);
        *pp_elem2 = My402ListLast(pList);
    } else {
        (void)My402ListInsertBefore(pList, obj1, elem2next);
        *pp_elem2 = My402ListPrev(pList, elem2next);
    }
}


static
void BubbleSortForwardList(My402List *pList, int num_items)
{
    My402ListElem *elem=NULL;
    My402ListElements *elements1;
    My402ListElements *elements2;
    int i=0;

    if (My402ListLength(pList) != num_items) {
        fprintf(stderr, "List length is not %1d in BubbleSortForwardList().\n", num_items);
        exit(1);
    }
    for (i=0; i < num_items; i++) {
        int j=0, something_swapped=FALSE;
        My402ListElem *next_elem=NULL;

        for (elem=My402ListFirst(pList), j=0; j < num_items-i-1; elem=next_elem, j++) {
            
            
            
            elements1=(My402ListElements*)elem->obj;
            
            long cur_val=(long)(elements1->tTime), next_val=0;

            
            next_elem=My402ListNext(pList, elem);
            
            elements2= (My402ListElements*)next_elem->obj;
            
            next_val = (long)(elements2->tTime);

            if (cur_val > next_val) {
                BubbleForward(pList, &elem, &next_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}

/*----------------formatNumbers----------------------*/

void formatNumbers(int amount,char tType){
	
	int modulus;
	int temp;
	temp=amount;
	int temp2;
	
	
	if((amount/100)>99999999){
		if(tType=='+'){
		strncpy(finalamt,"  ?,???,???.??  ",15);
		}
		else if(tType=='-'){
		strncpy(finalamt,strcat("?,???,???.?","?"),15);	
		}
	}
	 if(amount<10000){
		
		//char finamt2[15];
		modulus=temp%100;
		char a[2];
		char b[3];
		char *c;
		sprintf(a,"%d",temp/100);
		sprintf(b,"%02d",modulus);
		c=strcat(a,".");
		strncpy(finalamt,strcat(c,b),15);
		
	}
	
	 if(amount>10000&&amount<100000){
		modulus=temp%100;
		char a[10];
		char b[10];
	
		char *c;
		sprintf(a,"%d",temp/100);
		sprintf(b,"%02d",modulus);
		c=strcat(a,".");
		strncpy(finalamt,strcat(c,b),15);
		
	}
	
	int modulus2;
	temp2=amount/100;
	modulus2 =amount%100;
	
	if(temp2<1000000&&amount>100000){
		char a[10];
		char b[10];
		char *c;
		char *d;
		char e[10];
		int num1=temp2/1000;
		int num2=temp2%1000;
		
		
		sprintf(a,"%d",num1);
		sprintf(b,"%03d",num2);
		sprintf(e,"%02d",modulus2);
		c=strcat(a,",");
		d=strcat(b,".");
		
		strncpy(finalamt,strcat(strcat(c,d),e),15);
	
	}
	
	if(temp2<1000000&&temp2>1000000){
	
		char a[10];
		char b[10];
		char *c;
		char *d;
		char e[10];
		int num1=temp2/1000;
		int num2=temp2%1000;
		
		
		sprintf(a,"%d",num1);
		sprintf(b,"%03d",num2);
		sprintf(e,"%02d",modulus2);
		c=strcat(a,",");
		d=strcat(b,".");
		
		strncpy(finalamt,strcat(strcat(c,d),e),15);	
		
		
	}
	
	if(amount<1000000000&&amount>100000000){
		int mod3, mod4, num1, modulus2;
		
		num1=temp2/1000000;
		
		
		mod3=(temp2%1000000)/1000;
		
		
		mod4=(temp2%1000000)%1000;
		
		modulus2=amount%100;
		
		
		
		char a[3];
		
		//char newarr[15];
		sprintf(a,"%d",num1);
		
		sprintf(a,"%d%s",num1,",");
		
		
		sprintf(finalamt,"%s%03d%s%03d%s%02d",a,mod3,",",mod4,".",modulus2);
	
		
	}
	
	
	 
	

}



static
void PrintTestList(My402List *pList, int num_items)
{
    My402ListElem *elem=NULL;
	My402ListElements *elements=NULL;
	
	int balance=0;
	int amt=0;
	char sign;
	
	
	if (My402ListLength(pList) != num_items) {
        fprintf(stderr, "List length is not %1d in PrintTestList().\n", num_items);
        exit(1);
    }
	
	printf("+-----------------+--------------------------+----------------+----------------+\n");
    printf("|       Date      | Description              |         Amount |        Balance |\n");
    printf("+-----------------+--------------------------+----------------+----------------+\n");
	
	
   
    for (elem=My402ListFirst(pList); elem != NULL; elem=My402ListNext(pList, elem)) {
       
       elements=(My402ListElements*)elem->obj;
       long timep = (long)(elements->tTime);
       
       char timearr[24];
       strncpy(timearr,ctime(&timep),24);	
	
		char finaltime[15];
		strncpy(finaltime,printDate(timearr),15);
		finaltime[15]='\0';
       
       /*------------Print Date---------------*/
		
		printlf("| %15s ",finaltime);
		
		/*--------------Print Description------*/
		printf("| %-24s |",elements->tDescription);
		

		/*------------Print Amount-------------*/
     
        formatNumbers(elements->tAmount,elements->tType);
        
        
        if(elements->tType=='+'){
        printf(" %13s  |",finalamt);
		}
		if(elements->tType=='-'){
		printf(" (%12s) |",finalamt);	
		}

		amt=elements->tAmount;
		if(elements->tType=='+'){
				
				balance=balance+amt;
			
			if(balance<0 ){
			sign='-';	
			if((abs(balance)>=1000000000))
			{
				sprintf(finalamt,"%s","\?,\?\?\?,\?\?\?.\?\?");
				printf(" (%12s) |\n",finalamt);
			}
			}
			if(balance>0){
			sign='+';
				if((abs(balance)>=1000000000))
				{
				sprintf(finalamt,"%s","\?,\?\?\?,\?\?\?.\?\?");
				printf(" %13s  |\n",finalamt);
			}
			}
			
		}
		else if(elements->tType=='-'){
			
			balance=balance-amt;
				
			
			if(balance<0 ){
			sign='-';	
			if((abs(balance)>=1000000000))
			{
				sprintf(finalamt,"%s","\?,\?\?\?,\?\?\?.\?\?");
				printf(" (%12s) |\n",finalamt);
			}
			}
			if(balance>0){
			sign='+';
				if((abs(balance)>=1000000000))
				{
				sprintf(finalamt,"%s","\?,\?\?\?,\?\?\?.\?\?");
				printf(" %13s  |\n",finalamt);
			}
			}
			
		}
		/*------------Print Balance------------*/
     
        if(balance<0 && abs(balance)<1000000000){
			
		formatNumbers(balance*-1,sign);
        printf(" (%12s) |\n",finalamt);
		
		}
		
		 if(balance>0&&abs(balance)<1000000000){
		 formatNumbers(balance,sign);	
		 printf(" %13s  |\n",finalamt);
		}
       
			
    }
    
    printf("+-----------------+--------------------------+----------------+----------------+\n");
    //fprintf(stdout, "\n");
}

/*---------------------isDirectory---------------------------------------*/
int isDirectory(char *filename){
	
	DIR* dir= opendir(filename);
	
	if(dir!=NULL){
	closedir(dir);
	return 1;
	}
	
	if(errno==ENOTDIR){
	return 0;
	}
	return -1;
}

/*-------------------Main()----------------------------------------------*/
int main(int argc, char *argv[]){
	FILE *fp;
	
	//My402List list;
	
	My402List *pList;
        pList = (My402List *)malloc(sizeof(My402List));
        (void)My402ListInit(pList);
	
	
	SetProgramName(*argv);
     //memset(&list, 0, sizeof(My402List));
    
    
	if(!My402ListInit (pList)){
		printf("List is uninitialised\n");
		}
	if(ProcessOptions(argc,argv)==1){
		if(argc==2){
			
		fp=stdin;	
		createList(fp,pList);
		BubbleSortForwardList(pList,pList->num_members);
		PrintTestList(pList,pList->num_members);
		fclose(fp);
		
		}
		else{
			
			
			if(isDirectory(argv[2])==0){
			fp=fopen(argv[2],"r");
			
			if(fp==NULL){
				fprintf(stderr, "Cannot open %s for reading.\n", argv[2]);
				printf("Error: %s\n",strerror(errno));
                return 0;        
      		}
      		
      		else{
			createList(fp,pList);
			BubbleSortForwardList(pList,pList->num_members);
			PrintTestList(pList,pList->num_members);
			fclose(fp);
		}
	}
	
	else if(isDirectory(argv[2])==1){
		
		
		fprintf(stderr, "Cannot open %s for reading. It is a directory.\n ", argv[2]);
			//	printf("Error: %s\n",strerror(errno));
                return 0;        
		
	}
	else if(isDirectory(argv[2])==-1){
		
		
		fprintf(stderr, "Cannot open %s for reading.\n ", argv[2]);
			printf("Error: %s\n",strerror(errno));
                return 0;        
		
	}
	
		
	
	}	
		
	
	}
	else{
	
		Usage();
		exit(0);
		}	
		
		return 0;
}

