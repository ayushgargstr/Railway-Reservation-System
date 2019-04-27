#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    Passanger *ptr=NULL;
    int choice;
    add_trains();
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
        {
            textcolor(LIGHTRED);
            printf("\nyou Quit\n");
            getch();
            exit(0);
        }
        else
        {
            switch(choice)
            {
                case 1:
                    clrscr();
                    view_trains();
                    break;
                case 2:
                    clrscr();
                    ptr=get_passenger_details();
                    if(ptr!=NULL)
                    {
                        book_ticket(ptr);
                    }
                    break;
                case 3:
                    clrscr();
                    accept_info(choice);
                    break;
                case 4:
                    clrscr();
                    search_ticket_no(choice);
                    break;
                case 5:
                    clrscr();
                    search_ticket_no(choice);
                    break;
                case 6:
                    clrscr();
                    view_all_bookings(choice);
                    break;
                case 7:
                    clrscr();
                    accept_info(choice);
                    break;
                case 8:
                    clrscr();
                    view_all_bookings(choice);
                    break;
                default:

                    textcolor(LIGHTRED);
                    printf("\nWrong choice. Please Try again!");
                    system("pause");//to pause the screen
                    clrscr();// to cleat the screen
            }

        }
    }
    printf("%s\t%s\t%s\t%d\t%d","123","BPL","GWA",2100,1500);
    return 0;
}
