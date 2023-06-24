#include "global.h"
#include "item.h"
#include "user.h"
#include "myflipkart.h"

Flipkart::Flipkart(string mas_pin, string product_file){
    masterPin = mas_pin;
    loggedIn = false;
    myProducts.clear();
    myUsers.clear();
    ReadItemList(product_file);
}

void Flipkart::ReadItemList(string product_file){
    
    fstream file_in(product_file, ios::in);
    string line;
    while (file_in >> line){
        item *productDetails = new item;
        stringstream ss(line);
        // we read the line as : itemName-itemcount-itemprice

        // this is for the name
        string word;
        getline(ss, word, '-');
        productDetails->name = word;

        // this is for the count
        getline(ss, word, '-');
        productDetails->count = stoi(word);

        // this is for the price
        getline(ss, word);
        productDetails->price = stoi(word);

        // push the item to the data structure we use in the code
        myProducts.push_back(productDetails);
    }

    file_in.close();
    return;
}

void Flipkart::login_owner(string mas_pin){
    if (mas_pin == masterPin){
        loggedIn = true;
    }
    else{
        cerr << "Invalid pin!\n";
    }
}

void Flipkart::addItemToShop(string item_name, int freq, int price){
    if (!loggedIn)
    {
        cerr << "Log in first to add items.\n";
        return;
    }

    item *prod = new item;
    prod->count = freq;
    prod->price = price;
    prod->name = item_name;
    cout << " item has been added successfully!\n";
    myProducts.push_back(prod);
}

void Flipkart::logout_acc(){
    loggedIn = false;
}

bool Flipkart::isLoggedIn(){
    return loggedIn;
}

void Flipkart::removeItemFromShop(int index)
{
    //index is 1 based indexing
    if (!loggedIn){
        cerr << "Please login to continue!\n";
        return;
    }
    if (index < 1 || index > myProducts.size()){
        cerr << "Invalid index!\n";
        return;
    }
    free(myProducts[index - 1]);
    myProducts.erase(myProducts.begin() + index - 1);
}

void Flipkart::exit(string mas_pin){
    if (mas_pin != masterPin){
        cerr << "Invalid Pin!\n";
        return;
    }
    for (auto it : myUsers){
        free(it.second);
        it.second = NULL;
    }
    for (auto it : myProducts){
        free(it);
        it = NULL;
    }
}

void Flipkart::registerNewUser(string email_id, string pass, string uname){
    if (myUsers.find(email_id) != myUsers.end()){
        cerr << "A user with this Email-id already exist!\n";
        return;
    }
    user *newUser = new user(uname, pass, email_id);
    myUsers[email_id] = newUser;
}

user* Flipkart::userLogin(string email_id, string pass){
    if (myUsers.find(email_id) == myUsers.end()){
        cerr << "User Does not exist!\n";
        return NULL;
    }
    user *user = myUsers[email_id];
    user->login(email_id,pass);
    return user;
}

void Flipkart::printItemList(){
    for (int i=1; i<=myProducts.size(); i++){
        cout << i << ". " << myProducts[i-1]->name << " -- " << myProducts[i-1]->price << endl;
    }
}

item* Flipkart::returnCopyItem(int index){
    if (index > myProducts.size()){
        cerr << "Product number does not exists!\n";
        return NULL;
    }
    item copyItem = myProducts[index - 1]->returnCopy();
    item* pointer_copyItem = new item;
    pointer_copyItem->name = copyItem.name;
    pointer_copyItem->count = copyItem.count;
    pointer_copyItem->price = copyItem.price;
    return pointer_copyItem;

}
