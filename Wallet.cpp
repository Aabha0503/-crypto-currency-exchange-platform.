#include "Wallet.h"
#include <iostream>
using namespace std;
Wallet::Wallet()
{
}
void Wallet::insertCurrency(std::string type, double amount)
{
    double balance=0.0;
    if(amount<0) throw std::exception{};
    if(currencies.count(type)==0){//it says if no of keys are 0then balance is 0
        balance=0;
    }else{
        balance=currencies[type];//the amount of the articular type
    }
    balance+=amount;
    currencies[type]=balance;
}
bool Wallet::removeCurrency(std::string type, double amount){
    if(amount<0) return false;
    if(currencies.count(type)==0){
        cout<<"No currency for: "<<type<<endl;
        return false;
    }else{
        if(containsCurrency(type, amount)){
            cout<<"Removing: "<<type<<" : "<<amount<<endl;
            currencies[type]-= amount ;
            return true;
        }
        else 
            return false;
    }
}
bool Wallet::containsCurrency(std::string type, double amount)
{
    if(currencies.count(type)==0)
        return false;
    else
        return currencies[type]>=amount;
}

std::string Wallet::toString(){
    std::string s;
    for(std::pair<std::string,double> pairs : currencies){
        std::string currency=pairs.first;
        double amount=pairs.second;
        s+=currency+" : "+std::to_string(amount)+"\n";
    }
    return s;
}

bool Wallet::canFulfillOrder(OrderBookEntry order){
    std::vector<std::string>currs=CSVReader::tokenise(order.product,'/');
    //ask
    if(order.orderType==OrderBookType::ask){
        double amount=order.amount;
        std::string currency=currs[0];
        return containsCurrency(currency,amount);
    }
    //bid
    if (order.orderType==OrderBookType::bid)
    {
       double amount=order.amount*order.price;
       std::string currency=currs[1];
       return containsCurrency(currency,amount);
    }
    
    return false;
}
//update the content of wallet assume the offer was make by owner of wallet
void Wallet::processSale(OrderBookEntry & sale){
    std::vector<std::string>currs=CSVReader::tokenise(sale.product,'/');
    std::map<std::string, double> currencies;
    //ask
    if(sale.orderType==OrderBookType::asksale){
        double OutgoingAmount=sale.amount;
        std::string OutgoingCurrency=currs[0];
        double IncomingAmount=sale.amount*sale.price;
        std::string IncomingCurrency=currs[1];
        currencies[IncomingCurrency]+=IncomingAmount;
        currencies[OutgoingCurrency]+=OutgoingAmount;
    }
    //bid
    if (sale.orderType==OrderBookType::bidsale)
    {
       double IncomingAmount=sale.amount;
       std::string IncomingCurrency=currs[0];
       double OutgoingAmount=sale.amount*sale.price;
       std::string OutgoingCurrency=currs[1];
       currencies[IncomingCurrency]+=IncomingAmount;
       currencies[OutgoingCurrency]+=OutgoingAmount;
    }
}