/* Enrique Saldaña Vacio
Intentar decir si el grafo es bipartito o no
*/

#include <iostream>
#include <vector>
#include <queue>
#include <locale.h>

using namespace std;

bool esBipartito(vector<vector<int> >& grafo, int n) 
{
	//"Coloreo" del grafo.
    vector<int> color(n, -1); 

    for(int i=0; i<n; i++) 
	{
        if(color[i]==-1) 
		{ 
            queue<int> q;
            q.push(i);
            color[i]= 0; 

            while(!q.empty()) 
			{
                int u= q.front();
                q.pop();

                for(int j=0; j<grafo[u].size(); j++) 
				{
                    int v= grafo[u][j];

                    if(color[v]==-1) 
					{
                        color[v]= 1-color[u];
                        q.push(v);
                    } 
                    else if(color[v]==color[u]) 
					{
                        return false;
                    }
                }
            }
        }
    }
    return true;  
};

int main() 
{
	setlocale(LC_ALL, "");
	
    int n, m;
    cout << "Dame el número de vértices: ";
    cin >> n;
    cout << "Dame la cantidad de aristas: ";
    cin >> m;

    vector<vector<int> > grafo(n); 

    cout << "Ingrese las aristas (u v) entre 1 y " << n << ":" << endl;
    
	for(int i=0; i<m; i++) 
	{
        int u, v;
        cin >> u >> v;
		u--;
        v--;
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }

    if(esBipartito(grafo, n))
    {
    cout << "\nEl grafo ES bipartito" << endl;
	}
    else
    {
    cout << "\nEl grafo NO es bipartito" << endl;
	}
    return 0;  
};
