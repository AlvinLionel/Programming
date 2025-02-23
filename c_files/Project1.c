#include <stdio.h>
int main()
{

    int num, phone, amount, pin, agentNumber, storeNumber, atmNumber, accountNumber;
    char address[30], name[20];

mainmenu:
    printf("\n1.Send Money\n");
    printf("2.Windraw cash\n");
    printf("3.Buy Airtime\n");
    printf("4.Loans and Savings\n");
    printf("5.Financial services\n");
    printf("6.Lipa na M-PESA\n");
    printf("7.My Account\n");
    printf("8.Pochi la Biashara\n");
    printf("9.M-PESA Ratiba\n");
    printf("10.MORE\n");

    printf("\nChoose a service:");
    scanf("%d", &num);

    switch (num)
    {
    case 1:
        printf("Send Money.\n");
        printf("1.Send Money to Any Network\n");
        printf("2.M-PESA Global\n");
        printf("3.Pochi la Biashara\n");
        printf("4 Home\n");
        printf("\nChoose a service:");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            printf("Enter Phone Number: ");
            scanf("%d", &phone);
            printf("Enter Amount:");
            scanf("%d", &amount);
            printf("Enter M-pesa pin: ");
            scanf("%d", &pin);
            break;
        case 2:
            printf("Enter your Pysical address E.g Safaricom House,Waiyaki Way:");
            scanf("%s", &address);
            break;
        case 3:
            printf("Enter Phone Number: ");
            scanf("%d", &phone);
            printf("Enter Amount:");
            scanf("%d", &amount);
            printf("Enter M-pesa pin: ");
            scanf("%d", &pin);
            break;
        case 4:
            goto mainmenu;
            break;
        default:
            printf("Invalid Input");
            break;
        }
        break;
    case 2:
        printf("1 From Agent\n");
        printf("2 From ATM\n");
        printf("3 From BANK TO M-PESA\n");
        printf("4 Home\n");
        printf("\nChoose a service: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            printf("Enter Agent Number: ");
            scanf("%d", &agentNumber);
            printf("Enter Store Number: ");
            scanf("%d", &storeNumber);
            break;
        case 2:
            printf("Enter ATM Number: ");
            scanf("%d", &atmNumber);
            printf("Withdraw from %d\n", atmNumber);
            printf("1.Accept\n");
            printf("2.Cancel\n");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                printf("Your request has been received successfully.");
                break;
            case 2:
                goto mainmenu;
            default:
                printf("Invalid Input");
                break;
            }
            break;
        case 3:
        back3:
            printf("FROM BANK TO M-PESA\n");
            printf("1 Equity Bank LTD\n");
            printf("2 COOPERATIVE BANK\n");
            printf("3 KCB BANK\n");
            printf("4 NCBA\n");
            printf("5 ABSA");
            printf("\nChoose a service: ");
            scanf("%d", &num);
            switch (num)
            {
            case 1: // equity bank
            back1:
                printf("Welcome to Equity\n");
                printf("1.English\n");
                printf("2.Kiswahili\n");
                printf("\nChoose a service: ");
                scanf("%d", &num);
                switch (num)
                {
                case 1:
                case 2:
                back2:
                    printf("Select an option to proceed.\n");
                    printf("1.Link Existing Equity Bank Account\n");
                    printf("2.Open a mobile account\n");
                    printf("3.Back\n");
                    printf("\nChoose a service: ");
                    scanf("%d", &num);
                default:
                    printf("Invalid Input");
                    break;
                    switch (num)
                    {
                    case 1:
                        printf("What is your Equity Account number: ");
                        scanf("%d", &accountNumber);
                        printf("1.Back\n");
                        printf("2.Main Menu\n");
                        scanf("%d", &num);
                        switch (num)
                        {
                        case 1:
                            goto back2;
                            break;
                        case 2:
                            goto mainmenu;
                            break;
                        default:
                            printf("Invalid Input");
                            break;
                        }
                    case 2:
                        printf("What is your first name: ");
                        scanf("%s", &name);
                        printf("1.Back\n");
                        printf("2.Main Menu\n");
                        scanf("%d", &num);
                        switch (num)
                        {
                        case 1:
                            goto back2;
                            break;
                        case 2:
                            goto mainmenu;
                            break;
                        default:
                            printf("Invalid Input");
                            break;
                        }
                        break;
                    case 3:
                        goto back1;
                        break;
                    default:
                        printf("Invalid Input");
                    }
                    break;
                }
                break;
            case 2: // co-operative bank
                printf("Phone number Not Registered.\n");
                printf("Kindly download MCo-op Cash App or Self register on retail-onlinebanking.co-opbank.co.ke or visit your nearest co-operative bank branch for assistance.\n");
                printf("1.Back\n");
                scanf("%d", &num);
                switch (num)
                {
                case 1:
                    goto back3;
                    break;
                }
                break;
            case 3: // KCB Bank
                break;
            case 4: // NCBA
                break;
            case 5: // ABSA
                break;
            default:
                printf("Invalid Input");
                break;
            }
            break;
        case 4:
            goto mainmenu;
            break;
        }
        break;
    case 3:
        printf("Buy Airtime\n");
        printf("1 Buy Airtime\n");
        printf("2 Buy Data Bundles\n");
        printf("3 Buy Minute Bundles\n");
        printf("4 Home\n");
        printf("\nChoose a service: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            printf("Buy Airtime\n");
            printf("1 My Phone\n");
            printf("2 Other Phone\n");
            printf("3 Home\n");
            printf("\n Choose a service: ");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                printf("Enter amount:");
                scanf("%d", &amount);
                printf("Enter M-Pesa pin:");
                scanf("%d", &pin);
                break;
            case 2:
                printf("Enter phone number: ");
                scanf("%d", &phone);
                printf("Enter amount:");
                scanf("%d", &amount);
                printf("Enter M-Pesa pin:");
                scanf("%d", &pin);
                break;
            case 3:
                goto mainmenu;
                break;
            default:
                printf("Invalid Input");
                break;
            }
            break;
        case 2:
        back4:
            printf("1.Sh20=500MB,3hr\n");
            printf("2.Sh10=100MB,3days\n");
            printf("3.Sh10=150MB TikTok,24hr\n");
            printf("4.Sh10=1024MB TikTok,1hr\n");
            printf("\nChoose a service: ");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                printf("Buy Sh20=500MB,3hrs using:\n");
                printf("1.Airtime\n");
                printf("2.M-PESA\n");
                printf("3.Okoa\n");
                printf("4.BACK\n");
                printf("Choose a service: ");
                scanf("%d", &num);
                switch (num)
                {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    goto back4;
                    break;
                }
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                printf("Invalid Input");
                break;
            }
            break;
        case 3:
            printf("OFA MOTO!!\n");
            printf("1.Sh20=100Mins,3hrs\n");
            printf("2.Sh10=20Mins,1hr\n");
            printf("3.Sh20=Kredo 60,Midnyt\n");
            printf("4.Sh20=Dakika 20,Midnyt\n");
            printf("5.Sh50=60 Mins,Midnyt\n");
            printf("6.Sh200=250 Mins,7days,\n");
            printf("7.Back\n");
            printf("8.MORE\n");
            printf("\nChoose a service:");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                goto back4;
                break;
            case 8:
                printf("7.Sh500=455 Mins,30days\n");
                printf("8.Sh1000=1250 Mins,30days\n");
                printf("9.Sh50=Kredo 150, Midnyt\n");
                printf("Choose a service: ");
                scanf("%d", &num);
                switch (num)
                {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    printf("Invalid Input.");
                    break;
                }
                break;
            default:
                printf("Invalid Input");
                break;
            }
            break;
        case 4:
            goto mainmenu;
            break;
        default:
            printf("Invalid Input");
            break;
        }
        break;
    case 4:
        printf("Loans and Savings\n");
        printf("1 Fuliza\n");
        printf("2 M-Shwari\n");
        printf("3 KCB M-PESA\n");
        printf("4 Halal Pesa\n");
        printf("\nChoose a service: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            printf("Invalid Input.");
            break;
        }
        break;
    case 5:
        printf("Financial Services\n");
        printf("1 MALI\n");
        printf("2 M-Banking\n");
        printf("3 SACCOs\n");
        printf("4 Insurance\n");
        printf("5 Wealth Management\n");
        printf("6 Unclaimed Funds\n");
        printf("7 Home\n");
        switch (num)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            goto mainmenu;
            break;
        default:
            printf("Invalid Input.");
            break;
        }
        break;
    case 6:
        printf("Lipa na M-PESA\n");
        printf("1 Pay Bill\n");
        printf("2 Buy Goods and Services\n");
        printf("3 Pochi La Biashara\n");
        printf("4 T-Kash\n");
        printf("5 Bill Manager\n");
        printf("6 Global Pay\n");
        printf("7 Goverment Services\n");
        printf("8 County Services\n");
        printf("9: MORE");
        printf("\nChoose a service: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            printf("Invalid Input.");
            break;
        }
        break;
    case 7:
        printf("My Account\n");
        printf("1 INLOCK M-PESA PIN\n");
        printf("2 M-PESA PIN Manager\n");
        printf("3 M-PESA Statement\n");
        printf("4 Manage Junior Account\n");
        printf("5 Check Balance\n");
        printf("6 Tariff Query\n");
        printf("7 Home\n");
        printf("\nChoose a service: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            goto mainmenu;
            break;
        default:
            printf("Invalid Input.");
            break;
        }
        break;
    case 8:
        printf("Pochi La Biashara\n");
        printf("1.Send Money\n");
        printf("2.Sell Airtime\n");
        printf("3.Lipa na Pochi\n");
        printf("4.Withdraw Cash\n");
        printf("5.Move Money\n");
        printf("6.Mkopo wa Pochi\n");
        printf("7.My Account\n");
        printf("8.M-Pesa Promos/Offers\n");
        printf("9:MORE\n");
        printf("\nChoose a service: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        }
        break;
    case 9:
        printf("M-PESA Ratiba\n");
        printf("0 Opt In\n");
        printf("Choose a service: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            break;
        case 2:
            break;
        default:
            printf("Invalid Input.");
            break;
        }
        break;
    case 10:
        printf("11 My M-Pesa Offer\n");
        printf("2:BACK\n");
        printf("Choose a service:");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            break;
        case 2:
            break;
        default:
            printf("Invalid Input.");
            break;
        }
        break;
    default:
        printf("Invalid Input\n");
        break;
    }
    return 0;
}