#ifndef MYFLIPKART
#define MYFLIPKART

#include "item.h"
#include "user.h"
#include "global.h"

class Flipkart{
    private:
        vector<item*> myProducts;
        unordered_map<string, user*> myUsers;
        bool loggedIn;
        string masterPin;
        
    public:
        Flipkart(string mas_pin, string products_file);
        
        void login_owner(string mas_pin);
        
        void ReadItemList(string file_name);
                
        void registerNewUser(string email_id, string password, string username);
        
        user* userLogin(string email_id, string password);
        
        void addItemToShop(string itemName, int freq, int cost);
        
        void logout_acc();

        bool isLoggedIn();
        
        void printItemList();
        
        void removeItemFromShop(int index);
        
        item* returnCopyItem(int index);

        void exit(string mas_pin);
};

#endif