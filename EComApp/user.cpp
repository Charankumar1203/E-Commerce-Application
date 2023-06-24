#include "global.h"
#include "item.h"
#include "user.h"

user::user(string mail, string pass, string uname){
    mailID = mail;
    password = pass;
    userName = uname;
    cartAmount = 0;
    cart.clear();
    isloggedin = true;
}

string user::getUserName(){
    return userName;
}

bool user::verifyAccount(string mail, string pass){
    return mailID == mail and password == pass;
}

void user::login(string mailID, string pass){
    if(verifyAccount(mailID, pass)){
        isloggedin = true;
    }
    else{
        cerr << "Invalid login or password!\n";
    }
}

bool user::isUserLoggedIn(){
    return isloggedin;
}

void user::addItemToCart(item it){
    cart.push_back(it);
    cartAmount += it.price;
}

void user::removeItemFromCart(int index){
    //indexing from 1
    if (index < 1 || index > cart.size())    {
        cerr << "Invalid index.\n";
        return;
    }

    cart.erase(cart.begin() + index - 1);
}

vector<item> user::getCart(){
    vector<item> cartCopy = cart;
    return cartCopy;
}

int user::totalCartPrice(){
    return cartAmount;
}

void user::purchase(){
    cart.clear();
    cartAmount = 0;
}

void user::logout(){
    isloggedin = false;
}

