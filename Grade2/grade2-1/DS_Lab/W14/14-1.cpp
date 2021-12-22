#include<iostream>
#include<cstring>
using namespace std;

class Trie{
public:
    Trie(){
        for(int i=0;i<26;i++){
            next[i] = NULL;
        }
    }
    void insert(string str){
        Trie *node = this;
        for(int i=0;i<str.size();i++){
            char c = str[i];
            if(node->next[c-'a']==NULL){
                node->next[c-'a'] = new Trie();
            }
            node = node->next[c-'a'];
        }
        node->isWord = true;
    }
    bool find(string str){
        Trie *node = this;
        for(int i=0;i<str.size();i++){
            char c = str[i];
            if(node->next[c-'a']!=NULL){
                node = node->next[c-'a'];
            }
            else return false;
        }
        return node->isWord;
    }
private:
    Trie *next[26];
    bool isWord = false;
};

int main(){
    int n=0, m=0;
    cin>>n>>m;
    Trie *trie = new Trie();
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        for(int j=0;j<s.size();j++){
            s[j] = tolower(s[j]);
        }
        trie->insert(s);
    }
    for(int i=0;i<m;i++){
        string s;
        cin>>s;
        for(int j=0;j<s.size();j++){
            s[j] = tolower(s[j]);
        }
        if(trie->find(s)) cout<<"1"<<endl;
        else cout<<"0"<<endl;
    }

    return 0;
}
