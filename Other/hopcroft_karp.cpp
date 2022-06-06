#include <list>
#include <queue>
#include <iostream>

using namespace std;

#define NIL 0
#define INT_MAX 10
#define INF INT_MAX

// Deklariert den Datentyp für die Knoten des Graphen
struct Node
{
    int index;
    string value;
    Node* next;
};

// Deklariert die Klasse für den bipartiten Graphen
class BipartiteGraph
{
    int count1, count2; // Anzahl der Knoten auf der linken und rechten Seite des bipartiten Graphen
    list<Node>* adjacencyList; // Anzahl der Knoten auf der linken und rechten Seite des bipartiten Graphen
    Node* pair1, * pair2; int distance[]; // Basiszeiger, die in der Methode HopcroftKarp verwendet werden

// Deklariert die Interfaces für die Methoden
public:
    BipartiteGraph(int count1, int count2); // Konstruktor
    void AddEdge(Node* startNode, Node* targetNode);
    bool BreadthFirstSearch();
    bool DepthFirstSearch(Node* startNode);
    int HopcroftKarp();
};

// Gibt die Matchingzahl des maximalen Matching zurück
int BipartiteGraph::HopcroftKarp()
{
    pair1 = new Node[count1 + 1]; // Speichert ein Paar von Knoten, wobei pair1[u] eine Ecke auf der linken Seite des bipartiten Graphen ist. Wenn nicht vorhanden, wird der Nullzeiger NIL gespeichert.
    pair2 = new Node[count2 + 1]; // Speichert ein Paar von Knoten, wobei pair1[v] eine Ecke auf der rechten Seite des bipartiten Graphen ist. Wenn nicht vorhanden, wird der Nullzeiger NIL gespeichert.
    // Initialisiert die Paare mit dem Nullzeiger NIL
    for (int i = 0; i <= count1; i++)
    {
        (&pair1)[i] = NIL;
    }
    for (int i = 0; i <= count2; i++)
    {
        (&pair2)[i] = NIL;
    }
    int result = 0; // Initialisierung
    while (BreadthFirstSearch())
    {
        for (int i = 1; i <= count1; i++)
        {
            Node* node = &pair1[i];
            if (node == NIL && DepthFirstSearch(node))
            {
                result++;
            }
        }
    }
    return result;
}

// Gibt true zurück, wenn es einen augmentierenden Pfad gibt, sonst false
bool BipartiteGraph::BreadthFirstSearch()
{
    queue<Node> nodeQueue;
    for (int i = 1; i <= count1; i++)
    {
        Node* node = &pair1[i];
        if (node == NIL)
        {
            distance[i] = 0;
            nodeQueue.push(*node);
        }
        else
        {
            distance[i] = INF;
        }
    }
    distance[NIL] = INF;
    while (!nodeQueue.empty())
    {
        int currentIndex = nodeQueue.front().index;
        nodeQueue.pop();
        if (distance[currentIndex] < distance[NIL])
        {
            list<Node>::iterator i;
            for (i = adjacencyList[currentIndex].begin(); i != adjacencyList[currentIndex].end(); ++i)
            {
                Node* node = &pair2[(*i).index];
                int index = (*node).index;
                if (distance[index] == INF)
                {
                    distance[index] = distance[currentIndex] + 1;
                    nodeQueue.push(*node);
                }
            }
        }
    }
    return (distance[NIL] != INF);
}

// Gibt true zurück, wenn es einen augmentierenden Pfad mit startNode gibt, sonst false
bool BipartiteGraph::DepthFirstSearch(Node* startNode)
{
    int startIndex = startNode->index; //
    if (startNode != NIL)
    {
        list<Node>::iterator i;
        for (i = adjacencyList[startIndex].begin(); i != adjacencyList[startIndex].end(); ++i)
        {
            Node j = *i;
            if (distance[pair2[startIndex].index] == distance[startIndex] + 1)
            {
                if (DepthFirstSearch(&pair2[startIndex]))
                {
                    pair2[startIndex] = *startNode;
                    pair1[startIndex] = j;
                    return true;
                }
            }
        }
        distance[startIndex] = INF; // Es gibt keinen augmentierenden Pfad, der mit startNode beginnt.
        return false;
    }
    return true;
}

// Konstruktor mit der Anzahl count1 und count2
BipartiteGraph::BipartiteGraph(int count1, int count2)
{
    this->count1 = count1;
    this->count2 = count2;
    adjacencyList = new list<Node>[count1 + 1];
}

// Diese Methode verbindet die Knoten startNode und targetNode miteinander.
void BipartiteGraph::AddEdge(Node* startNode, Node* targetNode)
{
    adjacencyList[(*startNode).index].push_back(*targetNode);
}

// Hauptmethode, die das Programm ausführt
int main()
{
    // Deklariert und initialisiert 4 Knoten
    Node node1 = Node{ 1, "A", NIL };
    Node node2 = Node{ 2, "B", NIL };
    Node node3 = Node{ 3, "C", NIL };
    Node node4 = Node{ 4, "D", NIL };
    // Verbindet Knoten des Graphen miteinander
    BipartiteGraph bipartiteGraph(4, 4);
    bipartiteGraph.AddEdge(&node1, &node2);
    bipartiteGraph.AddEdge(&node1, &node3);
    bipartiteGraph.AddEdge(&node2, &node1);
    bipartiteGraph.AddEdge(&node3, &node2);
    bipartiteGraph.AddEdge(&node4, &node2);
    bipartiteGraph.AddEdge(&node4, &node4);
    cout << "Size of maximum matching is " << bipartiteGraph.HopcroftKarp(); // Ausgabe auf der Konsole
}
