
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>

using std::cout;
using std::vector;
using std::string;

using std::string;
using std::to_string;
using std::bitset;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;

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

string hash_function(string fraze);
Block SearchForNextBlock(const Block& lastBlock, const vector<Transaction>& t);
string getBlockMerkelRootHash(const vector<Transaction>& t);
vector<string> getVectorMerkelRootHash(const vector<string>& t);
bool transactionConfirmation(Transaction takenTransaction, vector<User>& AllUsers);

string popas(string hex);
string xoras(string a,string b);
string andas(string a, string b);
string notas(string a);
string oras(string a, string b);


int main(){
    vector<Block>Blockchain;
    Block genesisBlock;
    genesisBlock.prevBlockHash="None";
    genesisBlock.timeStamp = time(0);
    genesisBlock.version = "v0.1";
    genesisBlock.nonce = 0;
    genesisBlock.difficultyTarget = 3;
    Blockchain.push_back(genesisBlock);

    vector <User> users;
    for(int i = 0; i<1000;i++){
        User client;
        client.name = "user"+to_string(i);
        client.public_key = hash_function(hash_function(client.name+to_string(client.name.length())+to_string(rand()%100)) );
        client.balance = rand() % 200 + 1;
        users.push_back(client);
    }
// 1000 useriu

    vector<Transaction> transactionPool;
    int a = 0;
    for(int i = 0; i< 10000; i++){
        Transaction trans;
        int x = (int)rand()%1000;
        int y = (int)rand()%1000;
        while (y!=x)
            y = rand()%1000;
        trans.senderKey = users[x].public_key;
        trans.recipientKey = users[y].public_key;
        trans.sum = rand()%500;
        trans.transactionID = hash_function(trans.senderKey + trans.recipientKey + to_string(trans.sum) );
        transactionPool.push_back(trans);
    }
// 10000 transakciju

    while(transactionPool.size()!=0){
        vector<Transaction>takenTransactions;
        for(int i = 0; i<100;i++){
        takenTransactions.push_back(transactionPool.back());
        transactionPool.pop_back();
        }
        for(int i = 0; i<100;i++){
        takenTransactions[i].completed=transactionConfirmation(takenTransactions[i], users);
        }
        Block newBlock=SearchForNextBlock(Blockchain.back(), takenTransactions);
        Blockchain.push_back(newBlock);

    }
    return 0;
}

bool transactionConfirmation(Transaction takenTransaction, vector<User>& AllUsers){
    int senderKey;
    int recipientKey;
    bool confirmSender = false;
    bool confirmRecipient = false;
    for(int i = 0; i<AllUsers.size();i++){
        if(takenTransaction.senderKey == AllUsers[i].public_key){
            if(AllUsers[i].balance >= takenTransaction.sum && takenTransaction.sum > 0){
                 confirmSender = true;
                 senderKey = i;
            }
        }
        if(takenTransaction.recipientKey == AllUsers[i].public_key){
                confirmRecipient = true;
                recipientKey=i;
        }
    }
    bool answer;
    if(confirmSender == true && confirmRecipient == true){
        answer = true;
        AllUsers[senderKey].balance -= takenTransaction.sum;
        AllUsers[recipientKey].balance += takenTransaction.sum;
    }
    else answer = false;

    return answer;
}
string getBlockMerkelRootHash(const vector<Transaction>& t){
    vector<string>hashes;
    string finalHash;
    for(int i = 0; i<t.size();i+=2){
        auto first = (t.begin()+(i/2))->transactionID;
        auto second = (prev(t.end())-(i/2))->transactionID;
        hashes.push_back(hash_function(first + second));
    }
    while(hashes.size()!=1){
        hashes=getVectorMerkelRootHash(hashes);
    }
    finalHash = hashes[0];
    return finalHash;
}

vector<string> getVectorMerkelRootHash(const vector<string>& t){
    vector<string> hashes;
    for(int i = 0; i<t.size();i+=2){
        auto first = *(t.begin()+(i/2));
        auto second = *(prev(t.end())-(i/2));
        hashes.push_back(hash_function(first + second));
    }
    return hashes;
}

Block SearchForNextBlock(const Block& lastBlock, const vector<Transaction>& t){
    Block block;
    uint32_t nextNonce = 0;
    int diff = lastBlock.difficultyTarget;
    block.difficultyTarget = diff;
    block.Transactions = t;
    block.merkelRootHash = getBlockMerkelRootHash(t);
    block.timeStamp = time(0);
    block.nonce = -1;
    block.version = "v0.1";
    string prevBlockHash = hash_function(hash_function(lastBlock.prevBlockHash + lastBlock.merkelRootHash + to_string(lastBlock.nonce) + to_string(lastBlock.timeStamp) + lastBlock.version + to_string(lastBlock.difficultyTarget)));
    while(block.nonce == -1){
        string blockHash = hash_function(hash_function(prevBlockHash + block.merkelRootHash + to_string(nextNonce) + to_string(block.timeStamp) + block.version + to_string(block.difficultyTarget)));
        for(int i = 0; i<diff;i++){
            if(blockHash[i]!='a')
                break;
            else if (i == diff-1 && blockHash[i]=='a'){
                block.prevBlockHash = prevBlockHash;
                block.nonce=nextNonce;
                cout << "New block created: " << blockHash << "\n";
                break;
            }
        }
        nextNonce++;
    }

    return block;
}



string hash_function(string fraze){
    string ID[5]={"01000100111110010111000000110001","11010000010010000000000000000001","01000100111110010111011110110001","11011111110010000000011000111101","11010100111110010111000100110001"};
    string hex;
    for(int i = 0; i<fraze.size();i++){
            hex += bitset<8>(fraze.c_str()[i]).to_string();
        }
        hex += "1";
        while(hex.size()%448!=0){
            hex+="0";
        }
        for(int i = 0; i<56;i++, hex+="0");
        hex += bitset<8>(fraze.size()*8).to_string();
        int dydis = hex.size()/32;
        string hexiukai[dydis];
        string zodziai[40];
        for(int i = 0;i<dydis;i++){
            hexiukai[i]=popas(hex);
            hex.erase(hex.begin(),hex.begin()+32);
        }
        for(int i = 0, j = 2, p = 8, k = 13, h = 0; h < 40;h++,i++,j++,p++,k++){
            if(i > dydis-1) i=0;
            if(j > dydis-1) j=0;
            if(p > dydis-1) p=0;
            if(k > dydis-1) k=0;
            zodziai[h]=xoras(xoras(xoras(hexiukai[k],hexiukai[p]),hexiukai[j]),hexiukai[i]);
            zodziai[h]+=zodziai[h][0];
            zodziai[h].erase(zodziai[h].begin(),zodziai[h].begin()+1);
        }
        for(int i = 0; i<5;i++){
            for(int j = 0; j<40;j++){
                if(i%2==0){
                    ID[i]=andas(ID[i],notas(zodziai[j]));
                    ID[i]+=ID[i][0];
                    ID[i]+=ID[i][1];
                    ID[i].erase(ID[i].begin(),ID[i].begin()+2);
                }
                else{
                    ID[i]=oras(notas(ID[i]),zodziai[j]);
                    ID[i]+=ID[i][0];
                    ID[i].erase(ID[i].begin(),ID[i].begin()+1);
                }
            }
        }
        stringstream ff;
        for(int i = 0; i<5;i++){
            if(ID[i][0]=='0')
                ID[i][0]='1';
            bitset<32> set(ID[i]);
            ff << std::hex << set.to_ulong();
            }
        ff >> fraze;
    return fraze;
}
string popas(string hex){
    hex.erase(hex.begin()+32,hex.end());
    return hex;
}

string xoras(string a,string b){
    string ats;
    for(int i = 0; i < 32;i++){
        if(a[i]=='1' && b[i]=='0' || b[i]=='1' && a[i]=='0')
            ats+="1";
        else ats+="0";
    }
    return ats;
}
string andas(string a, string b){
    string ats;
    for(int i = 0; i < 32; i++){
        if(a[i]=='1' && b[i]=='1' || a[i]=='0' && b[i]=='0' )
            ats+="1";
        else ats+="0";
    }
    return ats;
}
string notas(string a){
    string ats;
    for(int i = 0; i < 32; i++){
        if(a[i]=='1')
            ats+="0";
        else ats+="1";
    }
    return ats;
}
string oras(string a, string b){
    string ats;
    for(int i = 0; i < 32; i++){
        if(a[i]=='1' || b[i]=='1')
            ats+="1";
        else ats+="0";
    }
    return ats;
}



