#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::string;


struct User{
    string name;
    string public_key;
    double balance;
};
struct Transaction{
    string transactionID;
    string senderKey;
    string recipientKey;
    double sum;
    bool completed;
};
struct Block{
    string prevBlockHash;
    time_t timeStamp;
    string version;
    string merkelRootHash;
    uint32_t nonce;
    uint32_t difficultyTarget;
    vector<Transaction> Transactions;
};
int main(){
    vector<Block>Blockchain;
    ///Block genesisBlock(-1,timestamp,version,merkelRootHash,0,4,0);
    vector <User> users;
    for(int i = 0; i<100;i++){
        User client;
        client.name = "";
        ///client.public_key = hash_function(name+timestamp);
        ///client.balance = rand() % 200 + 1;
    }
// 1000 useriu
    vector<Transaction> transactionPool;
    for(int i = 0; i< 10000; i++){
        Transaction trans;
        int x = (int)rand()%100+1;
        int y = (int)rand()%100+1;
        while (y!=x)
            y = rand()%100+1;
        ///trans.senderKey = users[rand%100+1].public_key;
        ///trans.recipientKey = users[rand%100+1].public_key;
        ///trans.sum = rand()%500;
        ///trans.transactionID = hash_function(trans.senderKey + trans.recipientKey + trans.sum;
        ///transactionPool.push_back(trans);
    }
// 10000 transakciju
    while(transactionPool.size()!=0){
        vector<Transaction>takenTransactions;
        for(int i = 0; i<100;i++)
            takenTransactions.push_back(transactionPool.pop_back());
        ///Block newBlock=SearchForNextBlock();
        ///newblock.Transactions = takenTransactions;
        for(int i = 0; i<100;i++){
         ///   transactionConfirmation(newblock.Transactions[i]);
        }
    }
    return 0;
}
