#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

long long check_acc, transfer_acc;
const float f_interest=3.75;

struct Address
{
    char house_no[10];
    char city[20];
    char state[30];
};

struct
{
    char description[20];
    float amt;
    long account_no;

}tran;

struct
{
    char name[30];
    char dob[10];
    long long contact_number, aadhar_no, account_no;
    float amount, interest;
    struct Address address;

}customer, find, trnsfr;

void loan();        //for loan purpose
void remove_transactions(long long);        //if we remove account the transcations need to be removed
void get_address();     //for address while creating a new account
int quit_or_not();      //in order to quit or not
void loading();         //starting screen
void quitting();        //quit to show my name
void menu();            //menu layout for bms
void create_account();      //creating an account
void deposit_wihtdraw();        //for depoisting and withdrawing
void transactions();            //show transactions of account
void customer_list();           //get all of the customer list
void update_details();          //update the customer details
void interest();                //calculate interest of FD
void remove_account();          //close a bank account
void make_changes(long long);       //make changes to file 
void fd();                      //for fixed deposist purposes
void transfer();            //for tranferring money to another account
void transfer_changes(long long);   

int main()
{
    //creates file if not exists

    FILE *fptr=fopen("Transactions.dat", "a");
    fclose(fptr);

    fptr=fopen("Records.dat", "a");
    fclose(fptr);

    char username[10], password[20];

    RETRY:
    printf("Enter Username: ");
    gets(username);

    printf("Enter Password: ");
    gets(password);

    /*
        username= cgc
        password= cgc@123#
    */

    if( (strcmp(username, "cgc") != 0) || (strcmp(password, "cgc@123#") != 0) )
    {
        printf("Enter Valid Username/Password!\n");
        loading();
        goto RETRY;
    }
    system("cls");

    printf("Username and Password Matched!\n\n");
    printf("LOADING");
    for(int z=0; z<=6; z++)
    {
        loading();
        printf(".");
    }

    system("cls");
    menu();

    return 1;
}

int quit_or_not()
{
    int option;

    QUIT_OR_NOT:
    printf("Enter 1 to 'Continue' and '0' to Quit: ");
    scanf("%d", &option);

    if(option==1)
        return 0;

    else if(option == 0)
        quitting();

    else
        goto QUIT_OR_NOT;

}

void loading()
{
    int i,k;
    long j=100000000;
    for(i=0;i<j;i++)
         k=i;
}

void quitting()
{

    //credits of the author

    system("cls");

    printf("\n****************************************************************\n");
    printf("This was Developed By:\nDeepanshu Narang, 1802328, ECE B\n");
    printf("\n****************************************************************\n");

    exit(0);
}

void menu()
{
    int choice;
    while(1)
    {
        printf("Capital Bank Management System\n\n");

        //menu layout
        printf("\n****************************************************************\n");
        printf("1. Create Bank Account\n2. Deposit / Withdraw\n3. View Transactions\n4. Create a Fixed Deposit\n5. Get Customer List\n6. Update Information\n7. Calculate Interest on Fixed Deposit\n8. Apply for Loan\n9. Tranfer Money\n10. Close Bank Account\n11. Exit\n");
        printf("\n****************************************************************\n");

        printf("Please Enter your Choice: ");
        scanf("%d", &choice);
        printf("\n****************************************************************\n");

        switch(choice)
        {
            case 1: create_account();
                    break;

            case 2: deposit_wihtdraw();
                    break;

            case 3: transactions();
                    break;

            case 4: fd();
                    break;

            case 5: customer_list();
                    break;

            case 6: update_details();
                    break;

            case 7: interest();
                    break;

            case 8: loan();
                    break;

            case 9: transfer();
                    break;

            case 10: remove_account();
                    break;

            case 11: quitting();

            default: printf("\n===> Enter a Valid Option!<=== \n");
        }

        printf("\n****************************************************************\n");
        system("cls");  //clears the screen

    }
}

void create_account()
{
    printf("\n****************************************************************\n");
    ACCOUNT_NO:
    printf("Enter Account Number: ");
    scanf("%lld", &check_acc);

    FILE *rec=fopen("Records.dat", "a+");

    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", find.name, find.dob, &find.contact_number, &find.aadhar_no, &find.account_no, &find.amount, &find.interest, find.address.house_no, find.address.city, find.address.state) != EOF)
    {
        if(check_acc == find.account_no)
        {
            printf("Account already exits. Enter a new account number.\n");
            printf("\n****************************************************************\n");
            loading();
            fclose(rec);
            goto ACCOUNT_NO;
        }
    }

    customer.account_no=check_acc;

    printf("Enter your Name: ");
    scanf("%s", customer.name);

    printf("Enter your Date of Birth (dd/mm/yyyy): ");
    scanf("%s", customer.dob);

    printf("Enter Your Contact Number: ");
    scanf("%lld", &customer.contact_number);

    printf("Enter your Aadhar Number: ");
    scanf("%lld", &customer.aadhar_no);

    //for address this function is made
    get_address();

    int choice;
    ACC_TYPE:
    printf("Enter 1 for 'Savings' and 0 for 'Current': ");
    scanf("%d", &choice);

    if(choice==1)
        customer.interest=4.75;

    else if(choice == 0)
        customer.interest=3.25;

    else
        goto ACC_TYPE;

    printf("Enter Amount to Deposit: ");
    scanf("%f", &customer.amount);

    fprintf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", customer.name, customer.dob, customer.contact_number, customer.aadhar_no,\
            customer.account_no, customer.amount, customer.interest, customer.address.house_no,\
             customer.address.city, customer.address.state);

    FILE* ftran=fopen("Transactions.dat", "a+");
    fprintf(ftran,"Deposited %lld %f\n", customer.account_no, customer.amount);

    fclose(ftran);
    fclose(rec);

    printf("\n****************************************************************\n\n");
    printf("\nAccount Successfully Created! Your Account Number:  %lld\n", customer.account_no);
    printf("\n****************************************************************\n");
    loading();
    quit_or_not();

}

void deposit_wihtdraw()
{
    int flag=0, choice;
    float amt;

    printf("Enter your Account Number: ");
    scanf("%lld", &check_acc);

    FILE *rec=fopen("Records.dat", "a+");

    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", customer.name, customer.dob, &customer.contact_number, &customer.aadhar_no, &customer.account_no, &customer.amount, &customer.interest, customer.address.house_no, customer.address.city, customer.address.state) != EOF)
    {
        if(customer.account_no == check_acc)
        {
            flag=1;
            fclose(rec);
            goto DEP_WD;
        }
    }

    if(flag==0)
    {
        printf("Account Not Found!\n");
        printf("\n****************************************************************\n");
        fclose(rec);
        goto UNABLE;
    }

    DEP_WD:
    //load_data(check_acc);
    printf("Enter 1 for Deposit and 0 for Withdrawl: ");
    scanf("%d", &choice);

    printf("Enter Amount: ");
    scanf("%f", &amt);

    FILE *trans=fopen("Transactions.dat", "a+");

    if(choice == 1)
    {
        customer.amount+=amt;
        fprintf(trans,"Deposited %lld %f\n", check_acc, amt);
    }

    else if(choice == 0)
    {
        if(customer.amount < amt)
        {
            printf("Amount Unavailable in Bank Account!");
            printf("\n****************************************************************\n");
            goto UNABLE;
        }

        customer.amount-=amt;
        fprintf(trans, "Withdrawn %lld %f\n", check_acc, -amt);
    }

    else
    {
        fclose(trans);
        goto DEP_WD;
    }

    fclose(trans);
    make_changes(check_acc);
    printf("\n****************************************************************\n");
    printf("Process Done! Thank you for Service.\n");
    printf("\n****************************************************************\n");

    UNABLE:
    quit_or_not();
}

void transactions()
{
    printf("Enter your Account Number: ");
    scanf("%lld", &check_acc);

    int flag=0,count=0;
    FILE *trans=fopen("Transactions.dat", "a+");

    printf("\n****************************************************************\n");
    printf("Sr. No.\t\t Description\t\t Amount\n");
    printf("\n****************************************************************\n");
    while(fscanf(trans, "%s %lld %f", tran.description, &tran.account_no, &tran.amt) != EOF)
    {
        if(check_acc == tran.account_no)
        {
            flag=1;
            printf("%d\t\t %s\t\t %.2f\n", ++count, tran.description, tran.amt);
        }
    }


    if(flag==0)
        printf("Either no Transactions or Check the Entered Account Number!\n");

    printf("\n****************************************************************\n");

    fclose(trans);
    quit_or_not();

}

void fd()
{
    float f_amt;
    int f_time;

    printf("Enter your Account Number: ");
    scanf("%lld", &check_acc);

    //load_data(check_acc);

    int flag=0;

    FILE *rec=fopen("Records.dat", "a+");
    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", customer.name, customer.dob, &customer.contact_number, &customer.aadhar_no, &customer.account_no, &customer.amount, &customer.interest, customer.address.house_no, customer.address.city, customer.address.state) != EOF)
    {
        if(customer.account_no==check_acc)
        {
            goto FIXED_DEP;
        }
    }

    if(flag==0)
    {
        fclose(rec);
        goto ACC_NOT_FND;
    }

    FIXED_DEP:
    printf("Enter Amount: ");
    scanf("%f", &f_amt);

    if(customer.amount<f_amt)
    {
        int opt;
        printf("Amount in Your Account is Unavailable.\n");

        while(1)
        {
            printf("Press 1 to 'Enter a Valid Amount' or 0 for Main Menu: ");
            scanf("%d", &opt);

            if(opt==1)
                goto FIXED_DEP;

            else if(opt==0)
                goto SKIP;

            else
                continue;
        }

    }

    printf("Enter the Time(years): ");
    scanf("%d", &f_time);

    FILE* ftrans=fopen("Transactions.dat", "a+");
    fprintf(ftrans, "Fixed-Deposit %lld %.2f\n",check_acc, f_amt);
    customer.amount-=f_amt;
    fclose(ftrans);
    fclose(rec);

    make_changes(check_acc);

    printf("\n****************************************************************\n");
    printf("Fixed Deposit of Rs %.2f was Successful!\n\n");
    goto SKIP;

    ACC_NOT_FND:
    printf("Enter Valid Account Number!\n");

    SKIP:
    printf("\n****************************************************************\n");
    quit_or_not();
}

void customer_list()
{
    FILE *rec=fopen("Records.dat", "a+");
    int count=0;

    printf("Sr. No.\t Name\t\t Account Number\t\t Amount\n");
    printf("\n****************************************************************\n");
    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", find.name, find.dob, &find.contact_number, &find.aadhar_no, &find.account_no, &find.amount, &find.interest, find.address.house_no, find.address.city, find.address.state) != EOF)
    {
        count++;
        printf("%d\t %s\t\t %lld\t\t %.2f\n",count, find.name, find.account_no, find.amount);
    }

    printf("\n****************************************************************\n");
    fclose(rec);
    quit_or_not();

}

void update_details()
{
    int flag=0, choice;

    VALID_OR_NOT:
    printf("Enter Account No: ");
    scanf("%lld", &check_acc);

    FILE *rec=fopen("Records.dat", "a+");
    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", customer.name, customer.dob, &customer.contact_number, &customer.aadhar_no, &customer.account_no, &customer.amount, &customer.interest, customer.address.house_no, customer.address.city, customer.address.state) != EOF)
    {
        if(customer.account_no == check_acc)
        {
            flag=1;
            fclose(rec);
            goto UPDATE;
        }
    }
    if(flag==0)
    {
        fclose(rec);
        goto CANT_UPDATE;
    }

    UPDATE:
    printf("\n****************************************************************\n");
    printf("1. Name\n2. Contact Number\n3. Address\n");
    printf("Select from Above option to Update: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1: printf("Enter Name to Update: ");
                scanf("%s", customer.name);
                break;

        case 2: printf("Enter Contact Number to Update: ");
                scanf("%lld", &customer.account_no);
                break;

        case 3: printf("Enter the Address to Update: ");
                get_address();
                break;

        default: printf("Enter a Valid Option!\n\n\n");
                goto UPDATE;
    }

    printf("\n****************************************************************\n");
    make_changes(check_acc);
    printf("Updates have been made!\n");
    goto MOVE;

    CANT_UPDATE:
    printf("Enter a Valid Account Number!\n");

    MOVE:
    printf("\n****************************************************************\n");
    quit_or_not();
}

void interest()
{
    float principle;
    int time;

    printf("Enter Amount to Calculate Interest on Fixed Deposit: ");
    scanf("%f", &principle);

    printf("Enter Time in Years: ");
    scanf("%d", &time);

    float amount=(principle*time*f_interest)/100;
    printf("Interest on Fixed Deposit: %.2f%% \n", f_interest);
    printf("The Amount after Maturing: Rs %.2f \n", (principle+amount));

    printf("\n****************************************************************\n");

    quit_or_not();
}

void remove_account()
{
    printf("Enter the Account to Close: ");
    scanf("%lld", &check_acc);

    FILE *rec, *news;
    rec=fopen("Records.dat", "a+");
    news=fopen("new.dat", "w");

    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s", find.name, find.dob, &find.contact_number, &find.aadhar_no, &find.account_no, &find.amount, &find.interest, find.address.house_no, find.address.city, find.address.state) != EOF)
    {
        if(find.account_no == check_acc)
            continue;

        else

            fprintf(news,"%s %s %lld %lld %lld %f %f %s %s %s\n", find.name, find.dob, find.contact_number, find.aadhar_no, find.account_no, find.amount, find.interest, find.address.house_no, find.address.city, find.address.state);
    }

    fclose(rec);
    fclose(news);

    remove("Records.dat");   //records.dat
    rename("new.dat", "Records.dat");   //new---> records.dat

    remove_transactions(check_acc);
    printf("\n****************************************************************\n");
    printf("Account Closed!\n");
    quit_or_not();
}

void make_changes(long long act_no)
{
    FILE *fptr=fopen("Records.dat", "a+");
    FILE *news=fopen("new.dat", "w");

    while(fscanf(fptr,"%s %s %lld %lld %lld %f %f %s %s %s", find.name, find.dob, &find.contact_number, &find.aadhar_no, &find.account_no, &find.amount, &find.interest, find.address.house_no, find.address.city, find.address.state) != EOF)
    {

        if(find.account_no == act_no)
        {
            fprintf(news,"%s %s %lld %lld %lld %f %f %s %s %s\n", customer.name, customer.dob, customer.contact_number, customer.aadhar_no, customer.account_no, customer.amount, customer.interest, customer.address.house_no, customer.address.city, customer.address.state);
        }

        else
        {
            fprintf(news,"%s %s %lld %lld %lld %f %f %s %s %s\n", find.name, find.dob, find.contact_number, find.aadhar_no, find.account_no, find.amount, find.interest, find.address.house_no, find.address.city, find.address.state);
        }

    }

    fclose(fptr);
    fclose(news);
    remove("Records.dat");
    rename("new.dat","Records.dat");

    /* 
        how this function works
        1-> it gets the account no as arguemnet
        2-> opens the file as new.dat
        3-> if account no matches, writes data to file
        4-> data is stored as global variable
        5-> closes the file, removes the OG one
        6-> rename new file as og one
    */
}

void get_address()
{
    printf("Enter House Number: ");
    scanf("%s", customer.address.house_no);

    printf("Enter City: ");
    scanf("%s", customer.address.city);

    printf("Enter State: ");
    scanf("%s", customer.address.state);
}

void remove_transactions(long long acctNo)
{
    FILE* ftran=fopen("Transactions.dat", "a+");
    FILE* nptr=fopen("newtran.dat", "w");

    while(fscanf(ftran,"%s %lld %f", tran.description, &tran.account_no, &tran.amt) != EOF)
    {
        if(tran.account_no == check_acc)
            continue;

        else
        {
            fprintf(nptr, "%s %lld %f\n", tran.description, tran.account_no, tran.amt);
        }

    }

    fclose(nptr);
    fclose(ftran);

    remove("Transactions.dat");
    rename("newtran.dat", "Transactions.dat");

}

void loan()
{
    int flag=0, opt=0, l_type=0;
    float loan_amt;

    LOAN_ACT:
    printf("Enter your Bank Account: ");
    scanf("%lld", &check_acc);

    FILE *rec=fopen("Records.dat", "a+");

    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", customer.name, customer.dob, &customer.contact_number, &customer.aadhar_no, &customer.account_no, &customer.amount, &customer.interest, customer.address.house_no, customer.address.city, customer.address.state) != EOF)
    {
        if(customer.account_no == check_acc)
        {
            flag=1;
            fclose(rec);
            flag=0;
            goto LOAN;
        }
    }

    if(flag==0)
    {
        fclose(rec);

        printf("Enter a Valid Account Number!\n");
        printf("\n****************************************************************\n");
        printf("1.Enter Account Number again\n 2. Skip\n");
        printf("\n****************************************************************\n");

        while (1)
        {
            printf("Select from above options: ");
            scanf("%d", &opt);

            if(opt==1)
                goto LOAN_ACT;

            else if(opt == 2)
                goto SKIP_LOAN;

            else
                printf("Enter a valid Option!\n");

        }

    }

    LOAN:
    printf("\n****************************************************************\n");
    printf("1. Vehicle Loan\n2. Home Loan\n3. Business Loan\n4. Education Loan\n5. Gold Loan\n6. Agriculture Loan\n");
    printf("\n****************************************************************\n");

    while(1)
    {
        printf("Select from Above Type of Loan: ");
        scanf("%d", &l_type);

        switch (l_type)
        {
            case 1:  strcpy(tran.description, "Vehicle-Loan");
                    flag=1;
                    break;

            case 2:  strcpy(tran.description, "Home-Loan");
                    flag=1;
                    break;

            case 3:  strcpy(tran.description, "Business-Loan");
                    flag=1;
                    break;

            case 4:  strcpy(tran.description, "Education-Loan");
                    flag=1;
                    break;

            case 5:  strcpy(tran.description, "Gold-Loan");
                    flag=1;
                    break;

            case 6:  strcpy(tran.description, "Agriculture-Loan");
                    flag=1;
                    break;

            default: printf("Enter a valid Option!\n");
        }

        if(flag==1)
            break;

    }

    printf("Enter Your Loan Amount: ");
    scanf("%f", &loan_amt);

    customer.amount+=loan_amt;
    make_changes(check_acc);

    FILE *trans=fopen("Transactions.dat", "a+");
    fprintf(trans, "%s %lld %.2f", tran.description, customer.account_no, loan_amt);
    fclose(trans);

    printf("\n****************************************************************\n");
    printf("Loan Sanctioned & Amount Transferred! to Account\n");

    SKIP_LOAN:
        quit_or_not();

}


void transfer()
{
    float tran_amt;
    int flag=0, flag_tran=0;

    TRAN_ACC:
    printf("Enter your Bank Account: ");
    scanf("%lld", &check_acc);

    FILE *rec=fopen("Records.dat", "a+");

    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", customer.name, customer.dob, &customer.contact_number, &customer.aadhar_no, &customer.account_no, &customer.amount, &customer.interest, customer.address.house_no, customer.address.city, customer.address.state) != EOF)
    {
        if(customer.account_no == check_acc)
        {
            flag=1;
            fclose(rec);
            flag=0;
            goto TRANSFER;
        }
    }

    if(flag==0)
    {
        fclose(rec);

        printf("Enter a Valid Account Number!\n");
        printf("\n****************************************************************\n");
        printf("1.Enter Account Number again\n 2. Skip\n");
        printf("\n****************************************************************\n");

        while (1)
        {
            printf("Select from above options: ");
            scanf("%d", &opt);

            if(opt==1)
                goto TRAN_ACC;

            else if(opt == 2)
                goto SKIP_TRAN;

            else
                printf("Enter a valid Option!\n");

        }

    }

    TRANFER:
    printf("Enter Account Number to transfer to: ");
    scanf("%lld", &transfer_acc);

    printf("Enter Amount to Transfer: ");
    scanf("%f", &tran_amt);

    if(tran_amt < customer.amount)
    {
        printf("Amount Unavailble in Account!\n");
        goto SKIP_TRAN:
    }

    while(fscanf(rec,"%s %s %lld %lld %lld %f %f %s %s %s", trnsfr.name, trnsfr.dob, &trnsfr.contact_number, &trnsfr.aadhar_no, &trnsfr.account_no, &trnsfr.amount, &trnsfr.interest, trnsfr.address.house_no, trnsfr.address.city, trnsfr.address.state) != EOF)
    {
        if(trnsfr.account_no == check_acc)
        {
            flag_tran=1;
            break;
        }

    }


    if(flag_tran == 0)  //if amt to tranfer is not in same bank
    {
        customer.amount-=tran_amt;
        make_changes(check_acc);
        printf("Amount Transferred to Another Bank's Account no: %lld !\n", transfer_acc);
    }

    else if(flag_tran==1)      //if amt to tranfer is in same bank
    {
        customer.amount-=tran_amt;
        trnsfr.amount+=tran_amt;

        make_changes(check_acc);
        transfer_changes(transfer_acc);

        printf("Amount Transferred to Same Bank's Account no: %lld !\n", transfer_acc);
    }
    

    SKIP_TRAN:
    quit_or_not();

}

void tranfer_changes(long long transfer_account)
{
    FILE *fptr=fopen("Records.dat", "a+");
    FILE *news=fopen("new.dat", "w");

    while(fscanf(fptr,"%s %s %lld %lld %lld %f %f %s %s %s", find.name, find.dob, &find.contact_number, &find.aadhar_no, &find.account_no, &find.amount, &find.interest, find.address.house_no, find.address.city, find.address.state) != EOF)
    {

        if(find.account_no == act_no)
        {
            fprintf(news,"%s %s %lld %lld %lld %f %f %s %s %s\n", trnsfr.name, trnsfr.dob, trnsfr.contact_number, trnsfr.aadhar_no, trnsfr.account_no, trnsfr.amount, trnsfr.interest, trnsfr.address.house_no, trnsfr.address.city, trnsfr.address.state);
        }

        else
        {
            fprintf(news,"%s %s %lld %lld %lld %f %f %s %s %s\n", find.name, find.dob, find.contact_number, find.aadhar_no, find.account_no, find.amount, find.interest, find.address.house_no, find.address.city, find.address.state);
        }

    }

    fclose(fptr);
    fclose(news);
    remove("Records.dat");
    rename("new.dat","Records.dat");
}


//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328
//Deepanshu Narang, ECE B, 1802328