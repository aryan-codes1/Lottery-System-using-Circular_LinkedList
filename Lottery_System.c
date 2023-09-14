#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* Use of structure to create linked list with data field 
as ticket number and name as holder's name */
struct node
{
    int data;
    char name[50];
    struct node *next;
};

// function for displaying the list of entries
void display(struct node *tmp)
{
    struct node *ptr = tmp;
    do
    {
        printf("Ticket Number : %d",ptr->data);
        printf("\tName : %s\n",ptr->name);
        ptr = ptr->next;
    } while (ptr != tmp);
}

/* this function traverses the linked list till it reaches the 
index position and eliminates that ticket from lottery race */
struct node *deleteatposition(struct node *head, int index)
{
    struct node *p = head;
    struct node *q = head->next;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        q = q->next;
    }
    if (q == head)
        head = head->next;
    p->next = q->next;
    free(q);
    return head;
}

/* this function choses index at random and with the help of
 deleteposition() function eliminates members to determine winner */
struct node *randomdelete(struct node *head)
{
    struct node *d = head;
    int rnum;
    srand(time(0));
    while (head->next != head)
    {
        rnum= rand()%6+2; //generating random numbers between 2 & 7 both inclusive
        head = deleteatposition(head, rnum);
        d = d->next;
    }
    return head;
}

/* a function to create list of entries that takes user
 input of ticket number and name */
struct node* create(){
    struct node *head,*temp;
    int size;
    printf("Enter the number of players\n");
    scanf("%d", &size);
    head=(struct node*)malloc(sizeof(struct node));
    temp=head;
    printf("Enter the ticket number: ");
    scanf("%d", &(head->data));
    printf("Enter the name of Ticket Holder: ");
    scanf("%s", &(head->name));
    temp->next=head;
    for (int i = 1; i < size; i++)
    {
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        printf("\nEnter the ticket number: ");
        scanf("%d", &(newnode->data));
        printf("Enter the name of Ticket Holder: ");
        scanf("%s", &(newnode->name));
        temp->next = newnode;
        newnode->next = head;
        temp = newnode;
    }
    return head;
}

/* this function lets users to add a participant at the end
 of the list if anyone wishes to join after list creation */
void addParticipant(struct node *head){
    struct node *p=head;
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    printf("Enter Ticket Number: ");
    scanf("%d",&newnode->data);
    printf("Enter the name of new Participant: ");
    scanf("%s",newnode->name);
    while(p->next != head){
        p=p->next;
    }
    p->next=newnode;
    newnode->next = head;

}

// used to check if a ticket number is present in the list or not
int isKey(struct node *head, int key)
{
    int flag = 0;
    struct node *p;
    p = head;

    do
    {
        if (p->data == key)
        {
            flag = 1;
            break;
        }
        p = p->next;
    }while (p != head);

    return flag;
}

// deletes the first node of the circular linked list
struct node* delbegin(struct node* head){
    struct node *p= head;
    struct node *q= p->next;
    while(p->next!=head){
        p=p->next;
    }
    p->next=q;
    free(head);
    return(q);
}

/* this function is the main function to delete the ticket
 it uses the isKey() and delbegin() functions to delete 
 the tickets using the ticket number */
struct node* deleteTicket(struct node* head){
    struct node* p=head;
    int ticket;
    printf("Enter ticket number: ");
    scanf("%d",&ticket);
    if(isKey(head,ticket)){
        if(head->data==ticket){
            head = delbegin(head);
        }
        else{
            while (p->next->data!=ticket)
            {
                p=p->next;
            }
            struct node* t=p->next;
            p->next=p->next->next;
            free(t);   
        }
        printf("\nDeleted Successfully!!\n");
    }
    else{
        printf("\nTicket does not Exists!!!\n");
    }
    return head;
}

// main function containg the case statements for the user experience 
int main()
{
    struct node* head = NULL;
    int ch;
    do
    {
        printf("\n=========================================\n");
        printf("   ----Lottery System Pegasus Mall----\n");
        printf("\n1-->Take Fresh Entries.\n");
        printf("2-->Display Participants.\n");
        printf("3-->Add another Participant.\n");
        printf("4-->Remove a Participant.\n");
        printf("5-->Start Lottery!\n");
        printf("0-->To Exit.\n");
        printf("Choose what you want to do? ");
        scanf("%d",&ch);
        printf("\n");
        switch (ch)
        {
        case 1:
            head=create();
            printf("\nData Saved Successfully !!\n");
            break;
        case 2:
            if(head!= NULL)
                display(head);
            else
                printf("No Participants Found !!\n");
            break;
        case 3:
            if(head!= NULL){
                addParticipant(head);
                printf("\nData Added Successfully !!\n");
            }
            else
                printf("Create the Entry List First.\n");
            break;
        case 4:
            head=deleteTicket(head);
            break;
        case 5:
            if(head!= NULL){
                head=randomdelete(head);
                printf("The Winner is:\n");
                printf("\n===================================\n");
                display(head);
                printf("Congratulations on winning 1Million !!\n");
                printf("===================================\n");
            }
            else
                printf("Enter participants First !!\n");
            break;
            case 0:
                printf("Thank You for Joining with Us.\nHopefully You Enjoyed it.\nBetter Luck next Time to all Losers !!\n");
                break;
        default:
            printf("Incorrect option!");
            break;
        }

    } while (ch!=0);

    return 0;
}