#ifndef RLYRES_H_INCLUDED
#define RLYRES_H_INCLUDED

struct Train
{
    char train_no[10];//train No
    char from[10];//code of the station
    char to[10];//code of the station
    int fac_fare;//first AC
    int sac_fare;//second AC
};

struct Passanger
{
    char p_name[20];
    char gender;//for only M or F
    char mob_no[11];
    int age;
    char train_no[10];
    char p_class;// for first AC f and for second AC s
    int ticketno;
    char address[30];
};

typedef struct Train Train;

typedef struct Passanger Passanger;

int enterchoice();// call from main and to display main+

void add_trains();//add the detain of train+

int view_trains();//show the detain of the train+

void book_ticket(Passanger*);//book the ticket return ticker no it ticker is book otherwise return -1+

//int *get_ticket_no(char*);//take the mobile as an argument and return the ticket no any ticket book otherwise return NULL+
void get_ticket_no(char*);//+

void view_ticket(char[],char,int);//it take the mobile number as an argument and search in case of find the detail it print all the detail
//of the ticket booked with that mobile no+

void view_all_bookings(int);//display all the book ticket of that train on the screen//+

void view_booking(char*);//take train no as an argument and display all the detail of the ticket book in that train//+

void cancel_ticket(char[],char,int); // cancel the booking that given ticket no. it success return  else return 0//+

void cancel_train(char* );//train no as an argument and delete all the booking of that train. it success return 1 else return 0.
//int case of cancel train.
Passanger *get_passenger_details();//to take the passenger detail as an input and return it's detail too.+
//if in case the user inter the user enter zero it return NULL.

int check_train_no(char*);//it is call form the passenger *get_passenger_detail();+

int get_booked_ticket_count(char*,char);//+

int last_ticket_no(char*,char);//+

int check_mob_no(char []);//+

int accept_info();//+

int search_ticket_no(int);//+

void print_all_ticket();//+

#endif // RLYRES_H_INCLUDED
