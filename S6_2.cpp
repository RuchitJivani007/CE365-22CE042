#include<bits/stdc++.h>
using namespace std;
int main()
{
    int nsymbols,nstates,istate,nas,as;
    string symbol[100];

    cout<<"Enter number of input symbols: ";
    cin>>nsymbols;
    for(int i=0;i<nsymbols;i++)
    {
        cout<<"Enter input symbol "<<i+1<<": ";
        cin>>symbol[i];
    }
    cout<<"Enter Number of states: ";
    cin>>nstates;
    cout<<"Enter initial states: ";
    cin>>istate;
    cout<<"Enter number of accepting states: ";
    cin>>nas;
    cout<<"Enter accepting state: ";
    cin>>as;

    int TransitionTable[nstates][nsymbols];
    for(int i=0;i<nstates;i++)
    {
        for(int j=0;j<nsymbols;j++)
        {
            cout<<"Input for "<<i+1;
            // cin>>;
        }
    }

}