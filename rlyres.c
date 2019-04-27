#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include "conio2.h"

#include "rlyres.h"

#include<ctype.h>

#define N 50

int enterchoice()
{
    int choice;
    textcolor(YELLOW);
    gotoxy(70,1);
    printf("Railway Reservation System\n");
    for(int i=0;i<165;i++)
    {
        printf("-");
    }
    textcolor(DARKGRAY);
    printf("\nSelect an option\n");
    printf("1.View Train\n");
    printf("2.Book Ticket\n");
    printf("3.View Ticket\n");
    printf("4.Search Ticket No\n");
    printf("5.View All Booking\n");
    printf("6.View Train Booking\n");
    printf("7.Cancel Ticket\n");
    printf("8.Cancel Train\n");
    printf("9.Quit\n\n");
    printf("Enter choice:-");
    textcolor(LIGHTGREEN);
    scanf("%d",&choice);
    return choice;
}
void add_trains()
{
    FILE *fp=fopen("H:\\C\\NewDataBase\\alltrains.dat","rb");
    if(fp==NULL)//it file doesn't exit first it return null because of the first statement.
    {
        Train alltrains[4]={
            {"123","BPL","GWA",2100,1500},
            {"546","BPL","DEL",3500,2240},
            {"345","HBJ","AGR",1560,1135},
            {"896","HBJ","MUM",4500,3360}
        };
    fp=fopen("H:\\C\\NewDataBase\\alltrains.dat","wb");//because yet the file isn't open so that statement open the file
    //or we can say that this statement will create the file
    fwrite(alltrains,4*sizeof(Train),1,fp);// write the all the statement directly. another way of do that we can write by using
    //using the loop but is not efficient in a case of large number of the record. in case of loop instead of writing 4*sisoof.
    //we simply write the sizeof.
    fclose(fp);//data save in the file
    //printf("File save Successfully\n");//just the checking. try it after deleting the exiting file. we will that message.
    }
    else//file already present.
    {
        //printf("Flie already present");//only for test file is already exit.
        fclose(fp); //because of first the fopen the file open has to be close.
    }
}
int view_trains()
{
    Train t;
    FILE *fp=fopen("H:\\C\\NewDataBase\\alltrains.dat","rb");
    if(fp==NULL)
    {
        printf("File cannot be open");
        return -1;
    }
    textcolor(YELLOW);
    printf("\t\tTRAIN NO\t\tFROM\t\tTO\t\tFIRST AC FAIR\t\tSECOND AC FAIR\n");
    for(int i=0;i<168;i++)
    {
        textcolor(WHITE);
        printf("-");
    }
    while(fread(&t,sizeof(t),1,fp)==1)
    {
        printf("\t\t%s\t\t\t%s\t\t%s\t\t\t%d\t\t\t%d",t.train_no,t.from,t.to,t.fac_fare,t.sac_fare);
        printf("\n");
    }
    fclose(fp);
    textcolor(WHITE);
    printf("press any any key to go back to main screen");
    getch();
    clrscr();
    return 0;
}
int check_train_no(char* trainno)
{
    FILE *fp;
    Train t;
	fp=fopen("H:\\C\\NewDataBase\\alltrains.dat","rb");
	if(fp==NULL)
    {
        printf("File cannot be open");
        return -1;
    }
    else
    {
        while(fread(&t,sizeof(t),1,fp)==1)
        {
            if(strcmp(t.train_no,trainno)==0)
            {
                fclose(fp);//file must be close because it important resource of the information. and it has to be close.
                return 1;
            }
        }
        fclose(fp);
        return 0;
    }
}
Passanger *get_passenger_details()
{
    gotoxy(100,1);
    textcolor(LIGHTGREEN);
    printf("press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter passenger Name:-");
    static Passanger psn;// the variable whose address return must be survive in memory other wise
    //the in c or c++ garbage return.
    fflush(stdin);//stdin is pointier represent the keyboard.
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name, "0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation cancel");
        getch();
        clrscr();
        textcolor(YELLOW);
        return NULL;
    }
    printf("Enter gender(M/F):-");
    int valid;
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("Reservation cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return NULL;
        }
        else if(psn.gender!='M'&&psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Please Enter Either M for male or F for female");
            valid =0;
            getch();
            gotoxy(20,2);
            printf(" \b");//erase the enter data
            textcolor(YELLOW);
        }
        }while(valid==0);
        gotoxy(1,25);//Remove the old printed message.
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        gotoxy(1,3);
        printf("Enter the Train Number:-");
        do// run until use enter the
        {
            fflush(stdin);
            scanf("%s",psn.train_no);
            if(strcmp(psn.train_no,"0")==0)// if user input the 0 to cancel the reservation.
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation cancel ");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
            }
            valid= check_train_no(psn.train_no);
            if(valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error invalid Train no");
                getch();
                gotoxy(24,3);
                printf("\t\t\t\t\t\t\t\t\t\t");
                gotoxy(24,3);
                textcolor(YELLOW);
            }
            }while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,4);
            printf("Enter Traveling class(First AC-F, Second AC-S):-");
    do//class same as the gender logic.
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("Reservation cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return NULL;
        }
        else if(psn.p_class!='F'&&psn.p_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Please Enter Either F for first class or S for second class");
            valid =0;
            getch();
            gotoxy(49,4);
            printf(" \b");//erase the enter data
            textcolor(YELLOW);
        }
        }while(valid==0);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        gotoxy(1,5);
        printf("Enter address:-");
        fflush(stdin);
        fgets(psn.address,30,stdin);
        pos=strchr(psn.address,'\n');
        *pos='\0';
        if(psn.address[0]=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("Reservation cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return NULL;
        }
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        gotoxy(1,6);
        printf("Enter Age:-");
    do//class same as the gender logic.
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("Reservation cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return NULL;
        }
        else if(psn.age<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error Age should be positive");
            valid=0;
            getch();
            gotoxy(12,6);
            printf("\t\t\t\t\t\t\t");
            gotoxy(12,6);
            textcolor(YELLOW);
        }
        }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    gotoxy(1,7);
    printf("Enter the Mobile NO:-");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,11,stdin);
        pos=strchr(psn.mob_no,'\n');//it return 0 or NULL if the search is unsuccessful.
        if(pos!=NULL)
        {
            *pos='\0';
        }
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("Reservation cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error invalid Mobil no");
            getch();
            gotoxy(22,7);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(22,7);
            textcolor(YELLOW);
        }
    }while(valid ==0);
    gotoxy(1,25);
    printf("Passenger Data input Successfully");
    printf("\nPress any key");
    getch();
    clrscr();
    return &psn;
    //getch();
    //return 0;
}
int check_mob_no(char p_mob[])
{
    if(strlen(p_mob)!=10)
    {
        return 0;
    }
    else
    {
        while (*p_mob!='\0')
        {
            if(isdigit(*p_mob)==0)
            {
                return 0;
            }
            p_mob++;
        }
        return 1;
    }
}
void book_ticket(Passanger *ptr)
{
    int i=get_booked_ticket_count(ptr->train_no,ptr->p_class);
    if(i!=-1)
    {
        ptr->ticketno=i;
        FILE *fp=fopen("H:\\C\\NewDataBase\\Passenger Info.dat","ab");
        if(fwrite(ptr,sizeof(Passanger),1,fp)==1)
        {
            printf("Ticket SuccessFully Booked\n");
            printf("Ticket No:-%d",i);
        }
        fclose(fp);
    }
    else
    {
        printf("Seats Full");
    }
    printf("\nPress any key return to main screen\n");
    getch();
    clrscr();
}
int get_booked_ticket_count(char *train_no,char train_class)
{
    textcolor(LIGHTGREEN);
    int i=last_ticket_no(train_no,train_class);
    if(i<30)
    {
        return i;
    }
    else
    {
        return -1;
    }
}
int last_ticket_no(char *traino,char train_class)
{
    int arr[N][2]={0};
    Train t;
    int i=0,j=0,k;
    FILE *fp=fopen("H:\\C\\NewDataBase\\alltrains.datt","rb+");
    FILE *fptr=fopen("H:\\C\\NewDataBase\\Count.dat","rb+");
    if(fptr==NULL)
    {
        FILE *fptr2=fopen("H:\\C\\NewDataBase\\Count.dat","wb");
        fwrite(arr,sizeof(arr),1,fptr2);
        fclose(fptr2);
    }
    if(fp==NULL)
    {
        printf("File cannot be open\n");
        return -1;
    }
    fread(arr,sizeof(arr),1,fptr);
    while(fread(&t,sizeof(t),1,fp)==1)
    {
        if(strcmp(t.train_no,traino)==0)
            {
                if(train_class=='F')
                {
                    arr[i][j]=arr[i][j]+1;
                    k=arr[i][j];
                    FILE *fptr2=fopen("H:\\C\\NewDataBase\\Count.dat","wb");
                    fwrite(arr,sizeof(arr),1,fptr2);
                    fclose(fptr2);
                    fclose(fptr);
                    fclose(fp);
                    return k;
                }
                else if(train_class=='S')
                {
                    j=j+1;
                    arr[i][j]=arr[i][j]+1;
                    k=arr[i][j];
                    FILE *fptr2=fopen("H:\\C\\NewDataBase\\Count.dat","wb");
                    fwrite(arr,sizeof(arr),1,fptr2);
                    fclose(fptr2);
                    fclose(fptr);
                    fclose(fp);
                    return k;
                }
            }
            i++;
    }
    return 0;
}
int accept_info(int i)
{
    gotoxy(100,1);
    textcolor(LIGHTGREEN);
    printf("press 0 to exit");
    gotoxy(1,1);
    char train_no[10],train_class;
    int ticket_no,valid;
    printf("Enter Train No:-");
    do
    {
        fflush(stdin);
        fgets(train_no,5,stdin);
        char *pos;
        pos=strchr(train_no,'\n');
        *pos='\0';
        if(strcmp(train_no, "0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("process cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return 0;
        }
        valid= check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error invalid Train no");
            getch();
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(17,1);
            printf("\t\t\t\t\t");
            gotoxy(17,1);
            textcolor(LIGHTGREEN);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t\t");
    gotoxy(1,2);
    printf("Enter class:-");
    do
    {
        valid=1;
        scanf("%c",&train_class);
        if(train_class=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("Process Cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return 0;
        }
        else if(train_class!='F'&&train_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Please Enter Either F for first class or S for second class");
            valid =0;
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(13,2);
            printf("\t\t\t\t\t");
            gotoxy(13,2);
            textcolor(LIGHTGREEN);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t\t");
    gotoxy(1,3);
    printf("Enter Ticket no:-");
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("Process Cancel\n");
            getch();
            clrscr();
            textcolor(YELLOW);
            return NULL;
        }
        if(ticket_no<=0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Ticket Number should be positive");
            valid=0;
            getch();
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(18,3);
            printf("\t\t\t\t\t");
            gotoxy(18,3);
            textcolor(LIGHTGREEN);
        }
    }while(valid==0);
    clrscr();
    if(i==3)
    {
        view_ticket(train_no,train_class,ticket_no);
    }
    else if(i==7)
    {
        cancel_ticket(train_no,train_class,ticket_no);
    }
    return 0;
}
void view_ticket(char train_no[],char train_class,int ticket_no)
{
    int flag=0;
    Passanger p;
    FILE *fp=fopen("H:\\C\\NewDataBase\\Passenger Info.dat","rb");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmp(p.train_no,train_no)==0)
        {
            if(p.p_class==train_class)
            {
                if(p.ticketno==ticket_no)
                {
                    printf("Train no:-%s",p.train_no);
                    printf("\nPassenger name:-%s",p.p_name);
                    printf("\nGender:-%c",p.gender);
                    printf("\nage:-%d",p.age);
                    printf("\nAddress:-%s",p.address);
                    printf("\nTraveling class:-%c",p.p_class);
                    printf("\nTicket no:-%d",p.ticketno);
                    flag=1;
                }
            }
        }
    }
    fclose(fp);
    if(flag==0)
    {
        printf("No booking found");
    }
    getch();
    clrscr();
}

int search_ticket_no(int i)
{
    gotoxy(100,1);
    textcolor(LIGHTGREEN);
    printf("press 0 to exit");
    gotoxy(1,1);
    char mobile_no[11];
    int valid;
    char *pos;
    printf("Enter the Mobile NO:-");
    do
    {
        fflush(stdin);
        fgets(mobile_no,11,stdin);
        pos=strchr(mobile_no,'\n');//it return 0 or NULL if the search is unsuccessful.
        if(pos!=NULL)
        {
            *pos='\0';
        }
        if(strcmp(mobile_no,"0")==0 )
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");//because the previous message is lager so to erase that message we are using the \t.
            gotoxy(1,25);
            printf("process cancel");
            getch();
            clrscr();
            textcolor(YELLOW);
            return 0;
        }
        valid=check_mob_no(mobile_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error invalid Mobil no");
            getch();
            gotoxy(22,1);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(22,1);
            textcolor(YELLOW);
        }
    }while(valid ==0);
    if(i==4)
        {
            get_ticket_no(mobile_no);
        }
    else if(i==5)
    {
        print_all_ticket(mobile_no);
    }
    return 0;
}
void get_ticket_no(char cell_no[])
{
    clrscr();
    Passanger p;
    int flag=0;
    int no[N];
    FILE *fp=fopen("H:\\C\\NewDataBase\\Passenger Info.dat","rb");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmp(p.mob_no,cell_no)==0)
        {
            no[flag]=p.ticketno;
            flag=flag+1;
        }
    }
    if(flag==0)
    {
        printf("No ticket book on %s number\n",cell_no);
    }
    else
    {
        for(int i=0;i<flag;i++)
        {
            printf("Ticker No:-%d\n",no[i]);
        }

    }
    fclose(fp);
    printf("Press any key");
    getch();
    clrscr();
}
void print_all_ticket(char cell_no[])
{
    clrscr();
    Passanger p;
    int flag=0;
    FILE *fp=fopen("H:\\C\\NewDataBase\\Passenger Info.dat","rb");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmp(p.mob_no,cell_no)==0)
        {
            printf("Train no:-%s",p.train_no);
            printf("\nPassenger name:-%s",p.p_name);
            printf("\nGender:-%c",p.gender);
            printf("\nage:-%d",p.age);
            printf("\nAddress:-%s",p.address);
            printf("\nTraveling class:-%c",p.p_class);
            printf("\nTicket no:-%d",p.ticketno);
            printf("\n");
            for(int i=0;i<168;i++)
            {
                textcolor(WHITE);
                printf("-");
                textcolor(LIGHTGREEN);
            }
            printf("\n");
            flag=1;
        }
    }
    fclose(fp);
    if(flag==0)
    {
        printf("No booking found on %s number",cell_no);
    }
    printf("Press any key\n");
    getch();
    clrscr();
}
void view_all_bookings(int i)
{
    int valid;
    char train_no[10];
    gotoxy(100,1);
    textcolor(LIGHTGREEN);
    printf("press 0 to exit");
    gotoxy(1,1);
    printf("Enter the Train Number:-");
        do
        {
            fflush(stdin);
            scanf("%s",train_no);
            if(strcmp(train_no,"0")==0)// if user input the 0 to cancel the reservation.
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Process cancel");
                getch();
                clrscr();
                textcolor(YELLOW);
                return NULL;
            }
            valid= check_train_no(train_no);
            if(valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error invalid Train no");
                getch();
                gotoxy(24,1);
                printf("\t\t\t\t\t\t\t\t\t\t");
                gotoxy(24,1);
                textcolor(YELLOW);
            }
            }while(valid==0);
            if(i==6)
            {
                view_booking(train_no);
            }
            else if(i==8)
            {
                cancel_train(train_no);
            }
}
void view_booking(char train_no[])
{
    clrscr();
    int flag=0;
    Passanger p;
    FILE *fp=fopen("H:\\C\\NewDataBase\\Passenger Info.dat","rb");
    printf("Train no:-%s",train_no);
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmp(p.train_no,train_no)==0)
        {
            printf("\nTicket no:-%d",p.ticketno);
            //printf("Train no:-%s",p.train_no);
            printf("\nPassenger name:-%s",p.p_name);
            printf("\nGender:-%c",p.gender);
            printf("\nage:-%d",p.age);
            printf("\nAddress:-%s",p.address);
            printf("\nTraveling class:-%c",p.p_class);
            //printf("\nTicket no:-%d",p.ticketno);
            printf("\n");
            for(int i=0;i<168;i++)
            {
                textcolor(WHITE);
                printf("-");
            }
            textcolor(LIGHTGREEN);
            flag=1;
        }
    }
    fclose(fp);
    if(flag==0)
    {
        textcolor(LIGHTGREEN);
        printf("No ticket book yet");
    }
    printf("press any key\n");
    getch();
    clrscr();
}
void cancel_ticket(char train_no[],char train_class,int ticket_no)
{
    int flag=0;
    Passanger p;
    FILE *fp1=fopen("H:\\C\\NewDataBase\\Passenger Info.dat","rb");
    FILE *fp2=fopen("H:\\C\\NewDataBase\\Temporary.dat","wb");
    while(fread(&p,sizeof(p),1,fp1)==1)
    {
        if(strcmp(p.train_no,train_no)!=0)
        {
            if(p.p_class!=train_class)
            {
                if(p.ticketno!=ticket_no)
                   {
                       fwrite(&p,sizeof(p),1,fp2);
                   }
            }
        }
        else
        {
            flag=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("H:\\C\\NewDataBase\\Passenger Info.dat");
    rename("H:\\C\\NewDataBase\\Temporary.dat","H:\\C\\NewDataBase\\Passenger Info.dat");
    if(flag==1)
    {
        textcolor(LIGHTGREEN);
        printf("Ticker Cancel\n");
    }
    else
    {
        textcolor(LIGHTRED);
        printf("Ticket not Found");
    }
    getch();
    clrscr();

}
void cancel_train(char train_no[])
{
    int flag=0;
    Passanger p;
    FILE *fp1=fopen("H:\\C\\NewDataBase\\Passenger Info.dat","rb");
    FILE *fp2=fopen("H:\\C\\NewDataBase\\Temporary.dat","wb");
    while(fread(&p,sizeof(p),1,fp1)==1)
    {
        if(strcmp(p.train_no,train_no)!=0)
        {

                fwrite(&p,sizeof(p),1,fp2);
        }
        else
        {
            flag=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("H:\\C\\NewDataBase\\Passenger Info.dat");
    rename("H:\\C\\NewDataBase\\Temporary.dat","H:\\C\\NewDataBase\\Passenger Info.dat");
    if(flag==1)
    {
        printf("Train Cancel");
    }
    else
    {
        printf("Train not Found");
    }
    getch();
    clrscr();
}
