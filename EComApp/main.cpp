#include "global.h"
#include "item.h"
#include "user.h"
#include "myflipkart.h"

void shopping(string MasterPin, Flipkart &ajaysFlipkart, user* User)
{
    while (User->isUserLoggedIn())
    {
        
        cout << "<------List of Products----->\n\n";

        ajaysFlipkart.printItemList();

        cout << "\n\n\n\n";
        int itemnumber;

        cout << "Enter any number from the following : \n";
        cout << "To show cart : -1\n";
        cout << "To logout : -2\n";
        cout << "Enter item number to add it to cart : \n";
        cout << "To remove an item from the cart : -3\n";
        cout << "To purchase all the items in the cart : -5\n\n";

        cin >> itemnumber;

        if (itemnumber == -1)
        {
            vector<item> userCart = User->getCart();
            system("clear");
            cout << "\tYour Cart\n\n";
            for (int i = 0; i < userCart.size(); i++){
                cout << (i + 1) << ". " << userCart[i].name << " -- " << userCart[i].price << "\n";
            }

            cout << "\nTotal price -> " << User->totalCartPrice() << "\n\n";
            cout << "Enter b to go back : ";

            string ch;
        TOGOBACK:
            cin >> ch;
            if (ch != "b")
            {
                cerr << "Press b to go back! : ";
                goto TOGOBACK;
            }
            system("clear");
        }

        else if (itemnumber == -2)
        {
            User->logout();
        }

        else if (itemnumber == -3)
        {
            cout << "\tYour cart\n\n";
            vector<item> userCart = User->getCart();
            for (int i=1; i<=userCart.size(); i++)
            {
                cout << i << ". " << userCart[i-1].name << " --> " << userCart[i-1].price << "\n";
            }
            int ind;
            cout << "Enter index no. of element from the cart list to remove it : ";
            cin >> ind;
            User->removeItemFromCart(ind);

            cout << "Enter b to go back : ";

            string ch;
        TOGOBACK2:
            cin >> ch;
            if (ch != "b")
            {
                cerr << "Press b to go back! : ";
                goto TOGOBACK2;
            }
            system("clear");
        }

        else if (itemnumber == -5){
            User->purchase();
            cout << "All items purchased sucesfully\n";
        }

        else if (itemnumber > 0)
        {
        item* additem = ajaysFlipkart.returnCopyItem(itemnumber);
        if(additem != NULL){
            User->addItemToCart(*additem);
            cout << "Item Number - " << itemnumber << " is successfully added to your cart.\n";
            }

        }

        else{
            cout << "Invalid Index Number!! Please try again!\n";
        }
    }
}

int main()
{

    // clear the terminal screen for better experience :)
    system("clear");
    string MasterPin, fileName;

    cout << "Enter Master Pin for the ajaysFlipkart : ";
    cin >> MasterPin;

    // we have a list of products listed in another text file and we read from the file

    cout << "Enter file name containing list of products \n";
    cout << "(By default, products have stored in products.txt file) : ";
    cin >> fileName;

    //open my flipkart and ready to do transactions

    Flipkart ajaysFlipkart(MasterPin, fileName);

    while (true)
    {
        char type;
        system("clear");
        cout << "WELCOME TO AJAY'S FLIPKART\n\n";
        cout << "\tLogin or Signup page\n\n\n";
        cout << "Press A to login as owner\n";
        cout << "Press L to login as User\n";
        cout << "Dont have an account yet? Press S to sign up\n";
        cout << "Press E Exit the program\n";

        cin >> type;

        if(type == 'S')
        {
            string emailId, pass, uname;
            cout << "Hey user, Please enter your details in order to create a new account.\n";
            cout << "Enter your EmailId : ";
            cin >> emailId;

            cout << "Set your password : ";
            cin >> pass;

            cout << "What should we call you (your name): ";
            cin >> uname;

            ajaysFlipkart.registerNewUser(emailId, pass, uname);
            cout << "Registered successfully\n";

            cout << "Enter h to go to home page : ";

            string ch;
        TOGOHOME:
            cin >> ch;
            if (ch != "h")
            {
                cerr << "Press h to go to home page! : ";
                goto TOGOHOME;
            }
            system("clear");

            user *User = ajaysFlipkart.userLogin(emailId, pass);
            if(User != NULL){
                cout << "\nHey " << uname << ", welcome to Ajay's Flipkart\n";
                shopping(MasterPin, ajaysFlipkart, User);
            }
            
        }

        else if(type == 'L'){
            string emailId;
            cout << "Enter your emailId : ";
            cin >> emailId;

            string Password;
            cout << "Enter a new password : ";
            cin >> Password;

            system("clear");
            user *User = ajaysFlipkart.userLogin(emailId, Password);
            if(User != NULL){
                cout << "\t\tWelcome " << User->getUserName() << " to ajaysFlipkart\n";
                shopping(MasterPin, ajaysFlipkart, User);
            }

            
        }
        
        else if(type == 'A'){
            string MasterPin;
            cout << "Enter Master Pin : ";
            cin >> MasterPin;

            system("clear");
            ajaysFlipkart.login_owner(MasterPin);
            while (ajaysFlipkart.isLoggedIn())
            {
                system("clear");
                int input;
                cout << "Welcome Ajay!, enter any of the following number for an operation: \n";
                cout << "\nEnter -1 to logout\n";
                cout << "Enter 0 to add item to the product list\n";
                cout << "Enter 1 to print products list\n";
                cout << "Enter 2 to delete an item from the list\n\nYour Response : ";
                cin >> input;
                if (input == 0)
                {
                    system("clear");
                    string prod;
                    cout << "Enter product name : ";
                    cin >> prod;
                    int quantity, price;
                    cout << "Enter item quantity :: ";
                    cin >> quantity;
                    cout << "Enter price per item in Rs.";
                    cin >> price;

                    ajaysFlipkart.addItemToShop(prod, quantity, price);
                    cout << "\nTHe product has been added successfully.\n";

                }
                else if (input == -1)
                {
                    ajaysFlipkart.logout_acc();
                }
                else if (input == 2)
                {
                    int index;
                    cout << "Enter index no. of the product from the list\n";
                    cin >> index;

                    ajaysFlipkart.removeItemFromShop(index);
                }
                else if (input == 1)
                {
                    ajaysFlipkart.printItemList();
                }
                else
                {
                    cout << "Invalid input!! Please Try again";
                }
            }
        }
        else if (type == 'E')
        {
            string masterPin;
            cout << "Enter Master Pin : ";
            cin >> masterPin;
            ajaysFlipkart.exit(MasterPin);
            exit(0);
        }
        else
        {
            cout << "Invalid character entered!! Please try again. Thank you!\n\n";
        }
    }
    return 0;
}
