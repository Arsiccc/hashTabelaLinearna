#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;




const int SIZE_OF_TABLE = 10;
 
class HashNode {
public:

    int k;
    string value;
    HashNode(int kValue, const string& value) : k(kValue), value(value){};
};

class HashMap{
    private:
        HashNode **hashtable;
    public:
        HashMap(){
            hashtable = new HashNode* [SIZE_OF_TABLE];
            for (int i = 0; i < SIZE_OF_TABLE; i++){
                hashtable[i] = NULL;
            }
        }
 
        ~HashMap()
        {
            for (int i = 0; i < SIZE_OF_TABLE; i++){
                if (hashtable[i] != NULL)
                    delete hashtable[i];
            }
            delete[] hashtable;
        }


        int HashFunc(int k){
            return k % SIZE_OF_TABLE;
        }



        void Insert(int k, const string& value){
            int hash_val = HashFunc(k);
            int starting = -1;
            
            while (hash_val != starting || hashtable[hash_val]!= NULL && hashtable[hash_val]->k != k){
                if (starting == -1)
                    starting = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (hashtable[hash_val] == NULL || hash_val == starting)
                hashtable[hash_val] = new HashNode(k, value);
            

            if(starting != hash_val){

                    if (hashtable[hash_val] != NULL){
                        if (hashtable[hash_val]->k == k)
                            hashtable[hash_val]->value = value;
                    }
                else
                    hashtable[hash_val] = new HashNode(k, value);
            }
        }


        int Search(int k){
            int hash_val = HashFunc(k);
            int starting = -1;
            while (hash_val != starting || hashtable[hash_val] != NULL && hashtable[hash_val]->k != k){
                if (starting == -1)
                    starting = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (hashtable[hash_val] == NULL || hash_val == starting)
                return -1;
            else
                return hashtable[hash_val]->k;
        }


        void Remove(int k){
            int hash_val = HashFunc(k);
            int starting = -1;
            while (hash_val != starting && (hashtable[hash_val] != NULL && hashtable[hash_val]->k != k)){
                if (starting == -1)
                    starting = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (hash_val != starting && hashtable[hash_val] != NULL && hashtable[hash_val]->k == k){
                delete hashtable[hash_val];
                hashtable[hash_val] = NULL;
                cout << "Brisanje je uspesno" << endl;
            } else{
                cout << "Brisanje nije uspesno" << endl;
            }
        }


        void DisplayHashashtable(HashMap& hash){
            cout << "\nHash tabela:" << endl;
            cout << "Index | Kljuc" << endl;
            cout << "-------------" << endl;
            for (int i = 0; i < SIZE_OF_TABLE; ++i){
                if (hash.hashtable[i] != NULL) {
                    cout <<  i << " | " << hash.hashtable[i]->value << endl;
                } else {
                    cout <<  i << " | -" << endl;
                }
            }
            cout << "-------------" << endl;
        }


        int tablesize(){
            return SIZE_OF_TABLE;
        }

        double kCount(){
            double count = 0;
            for(int i = 0; i < SIZE_OF_TABLE; i++){
                if(hashtable[i] != NULL){
                    count++;
                }
            }
            return count;
        }

        double fillRatio(){
            return kCount() / SIZE_OF_TABLE;
        }
};



 

int main(){
    HashMap hash;
    int k;
    string value;
    int choice;

    while (true){
        cout << "" << endl;
        cout << "\n----------------------" << endl;
        cout << "1.Ubaci elemente u hash tabelu" << endl;
        cout << "2.Pretrazi element u hash tabeli" << endl;
        cout << "3.Obrisi element sa datim kljucem" << endl;
        cout << "4.Prikazi hash tabelu" << endl;
        cout << "5.Prikazi broj kljuceva u hash tabeli" << endl;
        cout << "6.Prikazi popunjenost tabele" << endl;
        cout << "7.Izlaz" << endl;
        cout << "Unesi svoj izbor: ";
        cin >> choice;

        switch (choice){
            case 1:
                cout << "Unesi kljuc na kojem zelis da ubacis element: ";
                cin >> k;
                cout << "Unesi vrednost koju zelis da ubacis: ";
                cin >> value;
                hash.Insert(k, value);
                break;

            case 2:
                cout << "Unesi kljuc elementa koji trazis: ";
                cin >> k;
                if (hash.Search(k) == -1) {
                    cout << "Nije pronadjen element na kljucu " << k << endl;
                } else {
                    cout << "Element na kljucu " << k << " je pronadjen u hash tabeli" << endl;
                }
                break;
            case 3:
                cout << "Unesi kljuc elementa koji zelis da izbrises: ";
                cin >> k;
                hash.Remove(k);
                break;
            case 4:
                hash.DisplayHashashtable(hash);
                break;
            case 5:
                cout << "Broj kljuceva u hash tabeli je: " << hash.kCount() << endl;
                break;
            case 6:
                cout << "Odnos popunjenosti hash tabele je: " << hash.fillRatio() << endl;
                break;
            case 7:
                exit(0);
            default:
                cout << "\nPogresna opcija\n";
        }
    }     
    return 0;
}
