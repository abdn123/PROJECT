#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct record
{
    char time[6];
    char name[30];
    char place[25];
    char note[500];
    char number[20];
};
void editrecord()
{
	system("CLS");
	
	FILE *fp;
	struct record rec;
	char date[20], time[10];
	int choice, count=0;
	
	printf("\t***EDIT RECORD MENU***");
	printf("\n\nENTER THE DATE OF THE RECORD YOU WISH TO EDIT: ");
	fflush(stdin);
	gets(date);
	
	fp = fopen(date, "rb+");
	
	if(fp == NULL)
	{
		printf("\nTHERE IS NO RECORD OF THE ENTERED DATE");
		printf("\nPRESS ANY KEY TO EXIT");
		getch();
		return;
	}
	else
	{
		printf("\nENTER THE TIME OF THE RECORD YOU WISH TO EDIT: ");
		gets(time);
	
		while(fread(&rec, sizeof(rec), 1, fp) == 1)
		{
			if(strcmp(rec.time,time) == 0)
			{
				printf("\nPREVIOUS RECORD:");
				printf("\nTIME: %s",rec.time);
				printf("\nNAME: %s",rec.name);
				printf("\nPLACE: %s",rec.place);
				printf("\nNOTE: %s",rec.note);
				printf("\nNUMBER: %s",rec.number);
				printf("\n\nTO EDIT TIME...  PRESS 1");
				printf("\nTO EDIT NAME...  PRESS 2");
				printf("\nTO EDIT PLACE..  PRESS 3");
				printf("\nTO EDIT NOTE...  PRESS 4");
				printf("\nTO EDIT NUMBER.. PRESS 5");
				printf("\nTO EDIT ALL....  PRESS 6");
				printf("\n\nENTER YOUR CHOICE: ");
				
				do
				{
					fflush(stdin);		
					scanf("%d",&choice);
					
					switch(choice)
					{
						case 1: 
						{
							printf("\nENTER NEW TIME (hh:mm): ");
							fflush(stdin);
							gets(rec.time);
							break;
						}
						case 2:
						{
							printf("\nENTER NEW NAME: ");
							fflush(stdin);
							gets(rec.name);
							break;
						}	
						case 3:
						{
							printf("\nENTER NEW PLACE: ");
							fflush(stdin);
							gets(rec.place);
							break;
						}
						case 4:
						{
							printf("\nENTER NEW NOTE: ");
							fflush(stdin);
							gets(rec.note);
							break;
						}
						case 5:
						{
							printf("\nENTER NEW NUMBER:");
							fflush(stdin);
							gets(rec.number);
							break;
						}
						case 6:
						{
							printf("\nENTER NEW TIME: ");
							fflush(stdin);
							gets(rec.time);
							
							printf("\nENTER NEW NAME: ");
							fflush(stdin);
							gets(rec.name);
							
							printf("\nENTER NEW PLACE: ");
							fflush(stdin);
							gets(rec.place);
							
							printf("\nENTER NEW NOTE: ");
							fflush(stdin);
							gets(rec.note);
							break;
							
							printf("\nENTER NEW NUMBER:");
							fflush(stdin);
							gets(rec.number);
							break;
						}
						default:
						{
							printf("\nINCORRECT CHOICE! ENTER YOUR CHOICE: ");				
						}
					}
				}
				while(choice<1 || choice>7);
				
				fseek(fp,-sizeof(rec),SEEK_CUR);
                fwrite(&rec,sizeof(rec),1,fp);
                fseek(fp,-sizeof(rec),SEEK_CUR);
                fread(&rec,sizeof(rec),1,fp);
                
                count = 1;
			}
			
			if(count == 1)
			{
				system("CLS");
				printf("\t THE RECORD WAS EDITED SUCCESSFULLY!");
				printf("\n\t....................................");
				printf("\nEDITED RECORD:");
				printf("\nTIME: %s",rec.time);
				printf("\nNAME: %s",rec.name);
				printf("\nPLACE: %s",rec.place);
				printf("\nNOTE: %s",rec.note);
				printf("\nNUMBER: %s",rec.number);
			}
		}
	}
}
deleterecord()
{
    system("cls");
    FILE *fp,*ptr ;
    struct record file ;
    char filename[15],cont='Y',time[10];;
    int choice,verify;
    printf("\n\n\t\t*************************\n");
    printf("\t\t THIS IS DELETE MENU");
    printf("\n\t\t*************************\n\n");
    verify=password();
    if(verify==1)
    {
        return ;
    }
    while ( cont== 'Y' )
    {
        printf("\n\n\tPLEASE SELECT AN OPTION BELOW.");
        printf("\n\n\t1)DELETE WHOLE RECORD");
        printf("\n\t2)DELETE A PARTICULAR RECORD BY TIME");
        do
        {
            printf("\n\t\tENTER YOU CHOICE:");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:(dd-mm-yyyy):");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename,"wb") ;
                if ( fp == NULL )
                {
                    printf("\nINVALID FILE NAME!");
                    printf("\nPRESS ANY KEY TO EXIT:.");
                    getch();
                    return ;
                }
                fclose(fp);
                remove(filename);
                printf("\n\tTHE RECORD HAS BEEN DELETED!");
                break;
            case 2:
                printf("\n\tENTER THE DATE OF RECORD(dd-mm-yyyy):");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename, "rb" ) ;
                if ( fp == NULL )
                {
                    printf("\nTHE FILE DOES NOT EXISTS");
                    printf("\nPRESS ANY KEY TO GO EXIT:.");
                    getch();
                    return ;
                }
                ptr=fopen("temp","wb");
                if(ptr==NULL)
                {
                    printf("\nSYSTEM ERROR");
                    printf("\nPRESS ANY KEY TO GO BACK");
                    getch();
                    return ;
                }
                printf("\n\tENTER THE TIME OF RECORD TO BE DELETED(hh:mm):");
                fflush(stdin);
                gets(time);
                while(fread(&file,sizeof(file),1,fp)==1)
                {
                    if(strcmp(file.time,time)!=0)
                        fwrite(&file,sizeof(file),1,ptr);
                }
                fclose(fp);
                fclose(ptr);
                remove(filename);
                rename("temp",filename);
                printf("\nFILE HAS BEEN DELETED!");
                break;
            default:
                printf("\n\tPLEASE SELECT A VALID OPTION!");
                break;
            }
        }
        while(choice<1||choice>2);
        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD?(Y/N):");
        fflush(stdin);
        scanf("%c",&cont);
    }
    printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();
}
int password()
{
    FILE *fp;
    char l='\0';
    char ch;
    char check[40];
    char password[40];
    int i=0,j=0,k=0;
    for(i=0;i<40;i++)
    {
        password[i]='\0';
    }
    fp=fopen("password.txt","r");
        if(fp==NULL)
        {
            fp=fopen("password.txt","w");
            fprintf(fp,"diary");
            fclose(fp);
            printf("SINCE THIS IS YOUR FIRST TIME USING, YOUR DEFAULT PASSWORD IS 'diary'\n");
            printf("TRY USING THE DEFAULT PASSWORD\n");
        }
        else
        {
			printf("YOU HAVE THREE TRIES FOR SECURITY PURPOSES\n");
		}
	fp=fopen("password.txt","r");	
	rewind(fp);
    fscanf(fp,"%s",check);	
    printf("PLEASE ENTER YOUR PASSWORD:\n");
    for(i=0;i<3;i++)
    {
    	j=0;
    	if(i>0)
    		{
			
	    		for(k=0;k<40;k++)
	    		{
	       			password[k]='\0';
	    		}
	    	}
        while(1)
        {
            
            ch=getch();
            if(ch==13) // ascii code of enter
            {
                break;
            }
            if(ch==8) // ascii code of backspace
            {
                j--;
                printf("\b");
            }
            else
            {
                printf("*");
                password[j]=ch;
                j++;
            }
        }
        
        if(strcmp(check,password)==0)
        {
            printf("\nACCESS GRANTED");
            return 0;
        }
        if(i<2)
        {
            printf("\nACCESS DENIED\nTRY AGAIN RE-ENTER YOUR PASSWORD\n");    
    	}
        
	}
	printf("\nYOU ENTERED WRONG PASSWORD THREE TIMES YOU CANNOT ACCESS ANY RECORD\nPRESS ANY KEY TO GO BACK:");
	return 1;
}
void addrecord()
{
    struct record rec;
    FILE * fp;
    int choice = 0;
    char time[10];
    char file[30];
    char entry = 'y';
    system("cls");
    printf("\n\n\t\t*************************\n");
    printf("\t\t THIS IS ADD MENU");
    printf("\n\t\t*************************\n\n");
    printf("\n ENTER THE DATE ENTRY OF YOUR RECORD(dd-mm-yyyy):\n ");
    fflush(stdin);
    gets(file);
    fp = fopen (file, "ab+" );
    if (fp == NULL)
    {
        fp = fopen(file, "wb+");
        if(fp = NULL)
        {
        
            printf("\nSYSTEM ERROR OCCURED!");
            printf("\nPRESS ANY KEY TO EXIT:");
            getch();
            return;
        }
    }
    while(entry == 'Y'|| entry == 'y')
    {
    
        printf("\nENTER THE TIME OF RECORD(hh:mm):\n");
        fflush(stdin);
        gets(time);
        while (fread(&rec,sizeof(rec),1,fp)==1);
        {
            if(strcmp(rec.time,time)==0)
            {
                printf("THE RECORD ALREADY EXISTS!\n");
                choice =1;
            }
        }
        if(choice==0)
            {
            	fp = fopen (file, "ab+" );
                strcpy(rec.time,time);
                printf("\nENTER NAME OF PERSON:\n");
                fflush(stdin);
                gets(rec.name);
                printf("\nENTER THE PLACE OF MEETING:\n");
                fflush(stdin);
                gets(rec.place);
                printf("\nENTER A NOTE FOR THIS ENTRY:\n");
                fflush(stdin);
                gets(rec.note);
                printf("\nENTER THE NUMBER OF PERSON:\n");
                fflush(stdin);
                gets(rec.number);
                fwrite(&rec,sizeof(rec),1,fp);
                fclose(fp);
                
            
            }
        	printf("\nDO YOU WANT TO MAKE ANOTHER ENTRY?(Y/N) \n");
            fflush(stdin);
            scanf("%c",&entry);
            if(entry== 'n' || entry == 'N')
            {
                printf("PRESS ANY KEY TO GO BACK TO THE MAIN MENU:");
                getch();
				return;
            }    
    }
} 
void viewrecord()
{
	system("cls");
	struct record user;
	char timecheck[10],file[15],cont;
	int choice,verify;
	FILE *ptr;
	printf("\n\n\t\t***************************\n");
    printf("\t\t    RECORD VIEWING MENU ");
    printf("\n\t\t***************************\n\n");
	verify=password();
	if(verify==0)
	{
		do
		{
			printf("\nENTER THE DATE OF RECORD TO BE VIEWED(dd-mm-yyyy):");
			fflush(stdin);
			gets(file);
			ptr=fopen(file,"rb");
			if(ptr==NULL)
			{
				printf("RECORD DOES NOT EXIST!\n");
				printf("PRESS ANY KEY TO CONTINE\n");
				getch();
				return;
			}
			system("cls");
			printf("\tPLEASE SELECT AN OPTION BELOW:\n");
			printf("\t1) VIEW THE ENTIRE RECORD OF THAT DAY\n");
			printf("\t2) VIEW THE RECORD OF A PARTICULAR TIME\n");
			printf("\n\tENTER CHOICE:");
			scanf("%d",&choice);
			getc(stdin);
			switch (choice)
			{
				case 1:
					printf("THE WHOLE RECORD FOR THE DATE: %s\n",file);
					while (fread( &user,sizeof(user),1,ptr) == 1 )
					{
						printf("\n\nRECORDED TIME: %s\n",user.time);
						printf("RECORDED NAME: %s\n",user.name);
						printf("RECORDED PLACE: %s\n",user.place);
						printf("RECORDED NOTE: %s\n",user.note);
						printf("RECORDED NUMBER: %s\n",user.number);
					}
					break;
				
				case 2:
					printf("PLEASE SELECT THE TIME YOU WANT TO VIEW THE RECORD OF(hh:mm):");
					gets(timecheck);
					while (fread( &user,sizeof(user),1,ptr) == 1 )
					{
						if(strcmp(timecheck,user.time)==0)
						{
							
							printf("\nRECORDED TIME: %s\n",user.time);
							printf("RECORDED NAME: %s\n",user.name);
							printf("RECORDED PLACE: %s\n",user.place);
							printf("RECORDED NOTE: %s\n",user.note);
							printf("RECORDED NUMBER: %s\n",user.number);
						}
					}
					break;
				
				default:
					printf("THE OPTION YOU SELECTED IS NOT VALID!");
					break;
			}
			printf("\n\nWOULD YOU LIKE TO VIEW ANOTHER RECORD? (Y/N):");
			scanf("%c",&cont);
			getc(stdin);
		}
		while(cont=='Y' || cont=='y');
		fclose(ptr);
		return;
	}
	else
	{
		printf("RECORDS COULD NOT BE VIEWED SINCE WRONG PASSWORD!\n");
		printf("PRESS ANY KEY TO GO BACK TO MENU\n");
		getch();
		return;
	}
}
changepassword()
{
	int verify,i=0,j=0,k=0;
	FILE *ptr;
	char pass[50],pass1[50],ch;
	system("cls");
	printf("\n\n\t\t*******************************\n");
	printf("\t\t EDIT PASSWORD MENU \n");
	printf("\n\n\t\t*******************************\n");
	printf("\n\n FOR SECURITY PURPOSES YOU NEED TO VERIFY USING YOUR PASSWORD:\n");
	verify=password();
	if(verify==0)
	{
		system("cls");
		printf("PLEASE ENTER THE NEW PASSWORD:\n");
		while(1)
		{
			if(j<0)
			{
				j=0;
			}
			ch=getch();
			if(ch==13) // ascii code of enter
			{
				break;
			}
			if(ch==8) // ascii code of backspace
			{
				j--;
				printf("\b");
			}
			else
			{
				printf("*");
				pass[j]=ch;
				j++;
			}
		}
		printf("\nPLEASE RE-ENTER YOUR NEW PASSWORD:\n");
		while(1)
		{
			if(k<0)
			{
				k=0;
			}
			ch=getch();
			if(ch==13) // ascii code of enter
			{
				break;
			}
			if(ch==8) // ascii code of backspace
			{
				k--;
				printf("\b");
			}
			else
			{
				printf("*");
				pass1[k]=ch;
				k++;
			}
		}
		if(strcmp(pass,pass1)==0)
		{
			ptr=fopen("password.txt","r+");
			while(i<50)
			{
				fprintf(ptr,"\0");
				i++;
				fclose(ptr);
			}
			ptr=fopen("password.txt","w");
			fprintf(ptr,"%s",pass);
			fclose(ptr);
			printf("\nPASSWORD SUCCESSFULLY CHANGED!\n");
			printf("\nPRESS ANY KEY TO GET BACK TO THE MAIN MENU:\n");
			getch();
			return;
		}
		else
		{
			printf("\nTHE TWO PASSWORDS ENTERED WERE NOT SIMILAR!\nPASSWORD COULD NOT BE CHANGED!\n");
			printf("\nPRESS ANY KEY TO GO BACK TO THE MAIN MENU:\n");
			getch();
			return;
		}
	}
	
}
main()
{
	int choice,verify;
	printf("\n\n\t\t*******************************\n");
	printf("\n\n\t\tWELCOME TO PERSONAL DIARY PROGRAM\n");
	printf("\n\n\t\t*******************************\n");
	verify=password();
	if(verify==0)
	{
		while(1)
		{
			printf("\n\n\t\tTABLE OF CONTENTS:");
			printf("\n\t\tADD NEW RECORD\t[1]");
			printf("\n\t\tEDIT A RECORD\t[2]");
			printf("\n\t\tVIEW A RECORD\t[3]");
			printf("\n\t\tDELETE A RECORD\t[4]");
			printf("\n\t\tCHANGE PASSWORD\t[5]");
			printf("\n\t\tEXIT\t\t[6]");
			printf("\n\t\tENTER YOUR SELECTION: ");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
					addrecord();
					break;
				case 2:
					editrecord();
					break;
				case 3:
					viewrecord();
					break;
				case 4:
					deleterecord();
					break;
				case 5:
					changepassword();
					break;
				case 6:
					printf("\nTHANK YOU FOR USING PERSONALISED DIARY");
					printf("\nPRESS ANY KEY TO EXIT:");
					getch();
					exit(0);
					break;
				default:
					printf("\nYOU ENTERED AN INVALID CHOICE PLEASE SELECT A VALID OPTION!");
					printf("\nPRESS ANY KEY TO TRY AGAIN:");
					getch();
					break;
			}
			system("cls");
		}
	}
	else
	{
		printf("ACCESS TO THE DIARY COULD NOT BE GRANTED!\n");
		printf("PRESS ANY KEY TO EXIT:\n");
		getch();
		exit(0);
	}
}
