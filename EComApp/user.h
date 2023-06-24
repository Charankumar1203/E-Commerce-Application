#ifndef USER
#define USER

#include "item.h"
class user{
private:
        string mailID;
        string password;
        string userName;
        vector<item> cart;
        int cartAmount;
        bool isloggedin;
public:
        user(string mail, string pass, string uname);

        bool verifyAccount(string mail, string pass);

        void login(string mail, string pass);
        
        string getUserName();
        
        bool isUserLoggedIn();
        
        void addItemToCart(item it);
        
        void removeItemFromCart(int index);
        
        // return a copy of the cart 
        vector<item> getCart();
        
        // items have been checked out, so we can clear the cart and the cart amount
        void purchase();
        
        int totalCartPrice();

        // logs the user out of the application
        void logout();

};

#endif
