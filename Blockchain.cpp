
#include <vector>

#include <bitset>
#include <sstream>

using std::vector;
using std::string;

using std::string;
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

string hash_function(string toHash);

string popas(string hex);
string xoras(string a,string b);
string andas(string a, string b);
string notas(string a);
string oras(string a, string b);

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
        ///takenTransactions.push_back(transactionPool.pop_back());
        ///Block newBlock=SearchForNextBlock();
        ///newblock.Transactions = takenTransactions;
        for(int i = 0; i<100;i++){
        ///transactionConfirmation(newblock.Transactions[i]);
        }
    }
    return 0;
}
string hash_function(string toHash){
    string fraze;
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
        string zodziai[80];
        for(int i = 0;i<dydis;i++){
            hexiukai[i]=popas(hex);
            hex.erase(hex.begin(),hex.begin()+32);
        }
        for(int i = 0, j = 2, p = 8, k = 13, h = 0; h < 80;h++,i++,j++,p++,k++){
            if(i > dydis-1) i=0;
            if(j > dydis-1) j=0;
            if(p > dydis-1) p=0;
            if(k > dydis-1) k=0;
            zodziai[h]=xoras(xoras(xoras(hexiukai[k],hexiukai[p]),hexiukai[j]),hexiukai[i]);
            zodziai[h]+=zodziai[h][0];
            zodziai[h].erase(zodziai[h].begin(),zodziai[h].begin()+1);
        }
        for(int i = 0; i<5;i++){
            for(int j = 0; j<80;j++){
                if(i%2==0){
                    ID[i]=andas(ID[i],notas(zodziai[j]));
                    ID[i]+=ID[i][0];
                    ID[i].erase(ID[i].begin(),ID[i].begin()+1);
                }
                else
                    ID[i]=oras(notas(ID[i]),zodziai[j]);
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



