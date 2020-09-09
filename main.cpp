#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
public:
    string account_owner;
    float beginbalance,balance,totaldeposits,totalwithdrawals,totalservice;
    int Number_of_deposits_this_month;
    int Number_of_withdrawals;
    float Annual_interest_rate;
    float Monthly_service_charges;
    BankAccount() {}
    BankAccount(string account_owner,float Annual_interest_rate,float balance)
    {
        this->account_owner=account_owner;
        beginbalance=balance;
        this->balance=balance;
        this->Annual_interest_rate=Annual_interest_rate;
    }
    void deposit(float amountOfDeposit)
    {

        balance+=amountOfDeposit;
        totaldeposits+=amountOfDeposit;
        Number_of_deposits_this_month+=1;

    }
    void withdarw(float amountOfwithdarw)
    {
        balance-=amountOfwithdarw;
        totalwithdrawals+=amountOfwithdarw;
        Number_of_withdrawals+=1;
    }
    void calclnt()
    {
        float MonthlyInterestRate = (Annual_interest_rate/ 12);
        float MonthlyInterest = balance * MonthlyInterestRate;
        balance = balance + MonthlyInterest;
    }
    void monthlyproc()
    {
        balance-=Monthly_service_charges;
        beginbalance=balance;
        calclnt();
        Number_of_deposits_this_month=0;
        Number_of_withdrawals=0;
        Monthly_service_charges=0;
        totalservice=0;
        totaldeposits=0;
        totalwithdrawals=0;
    }
};
class SavingsAccount:virtual public BankAccount
{
public:
    string status;
    SavingsAccount(float balance):BankAccount()
    {
        if(balance<25)
        {
            status="inactive";
        }
        else
        {
            status="active";
        }
    }
    void withdraw(float amoutofwithdraw)
    {
        if(balance<25)
        {
            status="inactive";
        }
        else
        {
            status="active";
        }
        if((amoutofwithdraw>balance)||(status=="inactive"))
        {
            cout<<"sorry i can't done the withdraw";
        }
        else
        {
            BankAccount::withdarw(amoutofwithdraw);
            if(balance<25)
            {
                status="inactive";
            }
            else
            {
                status="active";
            }
        }
    }
    void deposit(float amountOfDeposit)
    {
        if(balance+amountOfDeposit>25)
        {
            status="active";
        }

        BankAccount::deposit(amountOfDeposit);
    }
    void monthlyProc()
    {
        if(Number_of_withdrawals>4)
        {
            Monthly_service_charges+=Number_of_withdrawals-4.00;
        }
        BankAccount::monthlyproc();
        if(balance<25)
        {
            status="inactive";
        }
        else
        {
            status="active";
        }
    }
};
class CheckingAccount:virtual public BankAccount
{
public:
    float withdraw(float bal)
    {
        if(bal>balance)
        {
            cout<<"sorry the balance in acount not enough";
            return -1;
        }
        else if(bal==balance)
        {
            if(balance<15)
            {
                cout<<"sorry the balance in acount not enough";
                return -1;
            }
            else
            {
                totalservice+=15;
                balance-=15;
                return (bal-15);
            }
        }
        else
        {
            if(balance>(bal+15))
            {
                totalservice+=15;
                balance-=15;
                return (bal);

            }
            else
            {
                totalservice+=15;
                balance-=15;
                return (bal-15);
            }
        }
    }
    void monthlyProc()
    {
        Monthly_service_charges+=5+0.1*Number_of_withdrawals;
    }
};
class AccountOwner : public SavingsAccount,public CheckingAccount
{
public:
    string full_name;
    string mobile_phone;
    string national_id;
    AccountOwner(string account_owner,string mobile_phone,string national_id,float Annual_interest_rate,float balance):BankAccount(account_owner,Annual_interest_rate,balance),SavingsAccount(balance)
    {
        full_name=account_owner;
        this->mobile_phone=mobile_phone;
        this->national_id=national_id;

    }
    void print()
    {
        cout<<"\nName : "<<full_name<<"\nMobile phone : "<<mobile_phone<<"\nnational id : "<<
            national_id<<"\nbalance : "<<balance<<endl;
    }
    void staticchar()
    {
        totalservice+=Monthly_service_charges;
        cout<<"\n\tstatistics for the month\nbeginning balance : "<<beginbalance<<
        "\ntotal amount of deposits : "<<totaldeposits<<"\ntotal amount of withdrawals : "
        <<totalwithdrawals<<"\nservice charges : "<<totalservice<<"\nending balance : "
        <<balance<<endl;
    }
};
int main()
{
    try
    {
        string fullname;
        string phone;
        string national;
        float Annualinterestrate,balances,Withdrawalamount,Depositamount;

        cout<<"excuse me enter the profile information\n";
        cout<<"enter full name\n";
        getline(cin,fullname);
        cout<<"enter phone numper\n";
        cin>>phone;
        cout<<"enter national\n";
        cin>>national;
        cout<<"enter Annual interest rate\n";
        cin>>Annualinterestrate;
        cout<<"enter balances\n";
        cin>>balances;

        if(balances<1)
        {
            throw "the acount will not work";
        }
        if((phone.length()!=11)&&(phone[0]!='0')&&((phone[1]!='0')||(phone[1]!='1')||(phone[1]!='2')||(phone[1]!='5')))
        {
            throw "enter a right number";
        }
        if(national.size()!=14)
        {
            throw "enter a right national id";
        }
        for(int i=3; i<11; i++)
        {
            if(((int)phone[i]>57)||((int)phone[i]<48))//cheaak that is only number
            {
                throw "enter only number";
            }
        }
        for(int i=0; i<14; i++)
        {
            if(((int)national[i]>57)||((int)national[i]<48))//cheaak that is only number
            {
                throw "enter only number";
            }
        }
        if((Annualinterestrate<0)||(Annualinterestrate>1))
        {
            throw "error in Annual interest rate";
        }
        AccountOwner user(fullname,phone,national,Annualinterestrate,balances);

        while(true)
        {
            int key;
            cout<<"\n\n\n\thello sir!\nwhat do you want to do\n1-display the profile user information\n2-makedepose\n3-make withdrow\n4-monthlyProc:\n5-display statistics for the month\n6-end?\n";
            cin>>key;
            if(key==1)
            {
                user.print();
            }
            if(key==2)
            {
                cout<<" enter how many you want to Deposit\n";
                cin>>Depositamount;
                if(Depositamount<1)
                {
                    cout<<"sorry the Deposit is so small";
                }
                else
                {
                    user.deposit(Depositamount);
                }
            }
            if(key==3)
            {
                cout<<" enter how many you want to withdrow\n";
                cin>>Withdrawalamount;
                if(Withdrawalamount<1)
                {
                    cout<<"sorry the withdrow is so small";
                }
                else
                {
                    float x=user.CheckingAccount::withdraw(Withdrawalamount);
                    if(x==-1)
                    {
                        cout<<"sorry you dont have enough balance";
                    }
                    else
                    {
                        user.SavingsAccount::withdraw(x);
                    }
                }
            }
            if(key==4){
                user.CheckingAccount::monthlyProc();
                user.SavingsAccount::monthlyProc();
            }
            if(key==5)
            {
                user.staticchar();
            }
            if(key==6)
            {
                break;
            }
        }
    }
    catch(const char *e)
    {
        cout<<e;
    }
    return 0;
}
