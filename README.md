# Blockchain V0.2  

This is my iteration of simulation of a blockchain.  

## What does the program do?  
- Creates 1000 random users with random balances (1-200)  
- Creates 10000 transactions between the random users (users are picked randomly), the transaction might be correct and incorrect (transaction amount<=500 ).
- Picks 100 transaction out of the 10000 transaction pool.  
- Finds a new block for the blockchain.  
- Puts the picked 100 transactions into the new block.  
- Checks the transactions, if the sender and recipient of the transaction exists. Also checks, if the sender has the right amount to complete the transaction.  
- Whether the transactions are correct or incorrect, they are marked accordingly and the user balances are changed.  
- Steps 3-7 are repeated till there are no more transactions.

# User, Transaction and Block Structs:  
## User  
```
struct User{
    string name;
    string public_key;
    double balance;
};
```
## Transaction  
```
struct Transaction{
    string transactionID;
    string senderKey;
    string recipientKey;
    double sum;
    bool completed;
};
```
## Block  
```
struct Block{
    string prevBlockHash;
    time_t timeStamp;
    string version;
    string merkelRootHash;
    uint32_t nonce;
    uint32_t difficultyTarget;
    vector<Transaction> Transactions;
};
```
# Changelog  
## V0.2  
- Upgraded block mining function.  
- Made better transaction verification.  
- Using <random> library instead of rand() function.

## V0.1  
- Integrated my own hash function to the blockchain.  
- Created SearchForTheNextBlock function.  
- Created getBlockMerkelRootHash function.
- Created transactionConfirmation function.  
- Created random user and transaction creation.
