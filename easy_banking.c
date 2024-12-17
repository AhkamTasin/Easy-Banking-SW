#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct user{
    char phone[50];
    char name[50];
    char ac[50];
    char password[50];
    char homeadd[200];
    char nid[20];
    char Fathername[30];
    char mothername[30];
    char nomine[30];
    char nomineeadd[100];
    char nomineenid[20];
    char nomineemobile[20];
    float balance;

    // Loan related fields
    float loan_amount;
    float monthly_payment;
    int loan_duration;
    char last_payment_date[15]; // YYYY-MM-DD
    float extra_charge;
};

int main(){ 
    struct user usr,usr1;

    FILE *fp;
    char filename[50];
    char phone[50];
    char pword[50];
    char newp[50];
    char detailp[50];

    int opt,choice;
    char cont='y';
    float amount;
    int oploan,loanch;
    // char currentDate[50];
    // char dueDate[50];
     

    printf("\n\033[1;32mWhat do you want to do?\033[0m\n"); 
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);

    if(opt==1){
        // create new account:
        system("cls"); // Clear the screen

        printf("Enter your account number:\t");  
        scanf("%s",usr.ac);
        printf("Enter your phone number:\t");
        scanf("%s",usr.phone);
        printf("Enter your new password:\t");
        scanf("%s",usr.password);
        printf("Enter your name:\t");
        scanf("%s",usr.name);
        printf("Enter your home address:\t");
        scanf("%s",usr.homeadd);
        printf("Enter your NID card number:\t");
        scanf("%s",usr.nid);
        printf("Enter your Father's name:\t");
        scanf("%s",usr.Fathername);
        printf("Enter your Mother's name:\t");
        scanf("%s",usr.mothername);
        printf("Enter your Nominee name:\t");
        scanf("%s",usr.nomine);
        printf("Enter your Nominee Address:\t");
        scanf("%s",usr.nomineeadd);

        printf("Enter your Nominee Phone:\t");
        scanf("%s",usr.nomineemobile);
        printf("Enter your Nominee NID Number:\t");
        scanf("%s",usr.nomineenid);

        // initial account create korar somoy balance 0
        usr.balance=0;

        strcpy(filename,usr.phone);
        fp=fopen(strcat(filename,".txt"),"w");
        fwrite(&usr,sizeof(struct user),1,fp);
        if(fwrite!=0){ 
            printf("\n\nAccount successfully registered");
        }
        else{
            printf("\n\nSomething went wrong, Please try again");
        }
        fclose(fp);
    }
    if(opt==2){
        // Login to account
        system("cls");

        printf("\nPhone number:\t");
        scanf("%s",phone);
        printf("Password:\t");
        scanf("%s",pword);
        strcpy(filename,phone);
        fp=fopen(strcat(filename,".txt"),"r");
        if(fp==NULL)
        {
            printf("\nAccount number is not registered");
        }
        else{
            fread(&usr,sizeof(struct user),1,fp);
            fclose(fp);
            if(!strcmp(pword,usr.password)){
                //Password matched
                while(cont=='y'){
                    system("cls");
                    printf("\033[1;34m"); // set green color
                    printf("+-------------------------------------+\n");
                    printf("|              MAIN MENU              |\n");
                    printf("+-------------------------------------+\n");
                    printf("| 1. Balance Inquiry.                 |\n");
                    printf("| 2. Depositing Cash.                 |\n");
                    printf("| 3. Cash Withdrawal.                 |\n");
                    printf("| 4. Online Transfer.                 |\n");
                    printf("| 5. Password Change.                 |\n");
                    printf("| 6. Check Your Registration Details  |\n");
                    printf("| 7. All about Loan                   |\n");
                    printf("+-------------------------------------+\n");
                    printf("\033[0m");
                    printf("\n\nYour choice:\t");
                    scanf(" %d",&choice);
                    
                    switch(choice){   
                        case 1:
                            printf("\nYour current balance is Tk. %.2f",usr.balance);
                            break;
                        case 2:
                            printf("\nEnter the amount:\t");
                            scanf("%f",&amount);
                            usr.balance+=amount;
                            fp=fopen(filename,"w"); // Again concate .txt korte hobe na karon agei ekbar koresi
                            fwrite(&usr,sizeof(struct user),1,fp);
                            if(fwrite!=NULL) printf("\nSuccessfully deposited");
                            fclose(fp);
                            break;
                        case 3:
                            printf("\nEnter the amount:\t");
                            scanf("%f",&amount);
                            if(amount>usr.balance){
                                printf("\nInsufficient balance");
                                break;
                            } 
                            else{
                                usr.balance-=amount;
                                fp=fopen(filename,"w"); // Again concate .txt korte hobe na karon agei ekbar koresi
                                fwrite(&usr,sizeof(struct user),1,fp);
                                if(fwrite!=NULL) printf("\nYou have withdrawn Tk. %.2f",amount);
                                fclose(fp);
                                break;

                            }
                        case 4:
                            printf("\nPlease enter the phone number to transfer the balance:\t");
                            scanf("%s",phone);
                            printf("\nPlease enter the amount to transfer:\t");
                            scanf("%f",&amount);
                            if(amount>usr.balance) printf("\nInsufficient balance");
                            else{
                                strcpy(filename,phone);
                                fp=fopen(strcat(filename,".txt"),"r"); // We open this account where I send money
                               
                                fread(&usr1,sizeof(struct user),1,fp);
                                fclose(fp);
                                fp=fopen(filename,"w");
                                usr1.balance+=amount;
                                fwrite(&usr1,sizeof(struct user),1,fp);
                                fclose(fp);
                                if(fwrite!=NULL){
                                    printf("\nYou have successfully transfered Tk. %.2f to %s",amount,phone);
                                    strcpy(filename,usr.phone);
                                    fp=fopen(strcat(filename,".txt"),"w");
                                    usr.balance-=amount;
                                    fwrite(&usr,sizeof(struct user),1,fp);
                                    fclose(fp);

                                }
                            }
                            break;
                        case 5:
                            printf("\nPlease enter your current password: \t");
                            scanf("%s",&newp);
                            fp=fopen(filename,"r");
                            fread(&usr,sizeof(struct user),1,fp);
                            if(strcmp(usr.password,newp)==0)
                            {
                                printf("\nPlease enter your new password: \t");
                                scanf("%s",&pword);
                                fclose(fp);
                                fp=fopen(filename,"w");
                                strcpy(usr.password,pword);
                                fwrite(&usr,sizeof(struct user),1,fp);
                                if(fwrite!=NULL)
                                {
                                    printf("\nPassword changed successfully.\t");
                                }
                                fclose(fp);
                            }
                            else{
                                printf("\nPassword not matched.\t");
                                fclose(fp);
                            }
                            break;
                        case 6:
                            printf("\nEnter your Password: \t");
                            scanf("%s",&detailp);
                            fp=fopen(filename,"r");
                            fread(&usr,sizeof(struct user),1,fp);
                            if(strcmp(usr.password,detailp)==0)
                            {
                                system("cls");
                                printf("|----------Personal Information-----------------------|\n");
                                printf("|A/C Number            : %s\n",usr.ac);
                                printf("|Your Name             : %s\n",usr.name);
                                printf("|Phone Number          : %s\n",usr.phone);
                                printf("|Home Address          : %s\n",usr.homeadd);
                                printf("|NID Card Number       : %s\n",usr.nid);
                                printf("|Father's Name         : %s\n",usr.Fathername);
                                printf("|Mother's Name         : %s\n",usr.mothername);
                                printf("|Nominee's Name        : %s\n",usr.nomine);
                                printf("|Nominee's Address     : %s\n",usr.nomineeadd);
                                printf("|Nominee's Phone Number: %s\n",usr.nomineemobile);
                                printf("|Nominee's NID Number  : %s\n",usr.nomineenid);
                                printf("|-----------------------------------------------------|\n");

                                
                            }
                            else
                            {
                                printf("\nPassword not matched.\t");
                                fclose(fp);
                            }
                            break;
                        case 7:
                            system("cls");
                            printf("|----------------About Loan-----------------|\n");
                            printf("| 1. Take a Loan                            |\n");
                            printf("| 2. Pay your monthly payment of Loan       |\n");
                            printf("|-------------------------------------------|\n");
                            printf("\nWhat is your choice?\t");
                            scanf("%d", &oploan);

                            if (oploan == 1) {
                                system("cls");
                                printf("How much of a loan do you want?\n");
                                printf("1. 1,00000 Taka - (You must have at least 10,000 Taka in your main balance)\n");
                                printf("2. 2,00000 Taka - (You must have at least 50,000 Taka in your main balance)\n");
                                printf("3. 5,00000 Taka - (You must have at least 1,00000 Taka in your main balance)\n");
                                printf("\nCaution: [You must pay at least 10,000 Taka monthly.\nIf you miss a payment, a 2%% charge of the total loan amount will be added.\nIf you pay in advance, no charge will be applied.]\n");
                                printf("\n\nYour choice:\t");
                                scanf("%d", &loanch);

                                float loan_amounts[] = {100000, 200000, 500000};
                                float required_balances[] = {10000, 50000, 100000};

                                if (loanch >= 1 && loanch <= 3) {
                                    float selected_loan = loan_amounts[loanch - 1];
                                    float required_balance = required_balances[loanch - 1];

                                    if (usr.balance >= required_balance) {
                                        // Update loan details
                                        usr.loan_amount = selected_loan;
                                        usr.monthly_payment = 10000.0;
                                        usr.loan_duration = (int)(selected_loan / usr.monthly_payment);
                                        usr.extra_charge = 0.0;

                                        // Record the current date as last payment date
                                        time_t t = time(NULL);
                                        struct tm tm = *localtime(&t);
                                        sprintf(usr.last_payment_date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

                                        // Update balance
                                        usr.balance += selected_loan;

                                        // Save to file
                                        fp = fopen(filename, "w");
                                        fwrite(&usr, sizeof(struct user), 1, fp);
                                        fclose(fp);

                                        printf("\nLoan of %.2f Taka activated successfully!\n", selected_loan);
                                    }
                                    else {
                                        printf("\nYou have insufficient balance to take this loan.\n");
                                        }
                                }
                                else {
                                    printf("\nInvalid loan choice.\n");
                                }
                            }
                            else if (oploan == 2)
                            {
                                system("cls");
                                if (usr.loan_amount == 0)
                                {
                                    printf("\nYou have no active loans.\n");
                                }
                                else
                                {
                                    printf("\nYour current loan balance: Tk. %.2f", usr.loan_amount);
                                    printf("\nYour monthly payment: Tk. %.2f", usr.monthly_payment);
                                    printf("\nYour penalties so far: Tk. %.2f", usr.extra_charge); // Display penalties
                                    printf("\nEnter the amount you want to pay: \t");
                                    scanf("%f", &amount);

                                    // Get the current date
                                    char currentDate[15];
                                    time_t t = time(NULL);
                                    struct tm tm = *localtime(&t);
                                    sprintf(currentDate, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

                                    // Parse the last payment date
                                    int lastYear, lastMonth, lastDay;
                                    sscanf(usr.last_payment_date, "%d-%d-%d", &lastYear, &lastMonth, &lastDay);

                                    // Calculate the number of months skipped
                                    int monthsSkipped = (int)(amount / usr.monthly_payment);

                                    if (monthsSkipped > 0)
                                    {
                                        printf("\nYou have paid for the next %d month(s).\n", monthsSkipped);
                                    }

                                    // Update the loan balance
                                    if (amount >= usr.loan_amount)
                                    {
                                        usr.loan_amount = 0; // Loan fully paid
                                        printf("\nLoan fully repaid! Congratulations!\n");
                                    }
                                    else
                                    {
                                        usr.loan_amount -= amount;
                                        printf("\nPayment of Tk. %.2f accepted. Remaining loan balance: Tk. %.2f\n", amount, usr.loan_amount);
                                    }

                                    // Calculate the next payment date
                                    int nextYear = lastYear;
                                    int nextMonth = lastMonth + monthsSkipped;

                                    while (nextMonth > 12)
                                    {
                                        nextMonth -= 12;
                                        nextYear++;
                                    }

                                    // Update the next payment date
                                    char nextPaymentDate[15];
                                    sprintf(nextPaymentDate, "%04d-%02d-%02d", nextYear, nextMonth, lastDay);

                                    // Display the next payment date
                                    printf("\nYour next payment is due on: %s\n", nextPaymentDate);

                                    // Update the user's payment record
                                    strcpy(usr.last_payment_date, nextPaymentDate);

                                    // Save the updated data to the file
                                    fp = fopen(filename, "w");
                                    fwrite(&usr, sizeof(struct user), 1, fp);
                                    fclose(fp);
                                }
                            }
                    }

                    printf("\n\nDo you want to continue the transaction? [y/n] ");
                    scanf("%s",&cont);
                }
            }
            else{
                printf("\nInvalid password");
            }
        }

    }

    return 0;
}