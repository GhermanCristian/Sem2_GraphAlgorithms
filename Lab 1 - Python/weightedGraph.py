from graph import Graph

class WeightedGraph(Graph):
    def __init__(self, isOriented):
        self._dictCost = {}
        Graph.__init__(self, isOriented, True)
        
    def _newVertex(self, index):
        Graph._newVertex(self, index)
        self._dictCost[index] = []
        
    def addEdge(self, srcVertex, destVertex, cost):
        Graph.addEdge(self, srcVertex, destVertex)
        
        self._dictCost[(srcVertex, destVertex)] = cost
    
    def removeEdge(self, srcVertex, destVertex):
        Graph.removeEdge(self, srcVertex, destVertex)
        
        del self._dictCost[(srcVertex, destVertex)]
        
    def removeVertex(self, index):
        Graph.removeVertex(self, index)
        
        #remove all the pairs which contain one of the nodes
        for pair in self._dictCost:
            if pair[0] == index or pair[1] == index:
                del self._dictCost[pair]    
        
    def getEdgeCost(self, srcVertex, destVertex):
        if self.isEdge(srcVertex, destVertex) == False:
            raise ValueError("Edge doesn't exist")
        return self._dictCost[(srcVertex, destVertex)]
    
    def modifyEdgeCost(self, srcVertex, destVertex, newCost):
        if self.isEdge(srcVertex, destVertex) == False:
            raise ValueError("Edge doesn't exist")
        self._dictCost[(srcVertex, destVertex)] = newCost
    
    def saveGraph(self):
        '''
        '''
        file = open("graph.txt", "w")
        
        file.write("%d %d\n" % (self._nrVertices, self._nrEdges))
        for vertex in self._dictOut.keys():
            for neighbour in self._dictOut[vertex]:
                file.write("%d %d %d\n" % (vertex, neighbour, self._dictCost[(vertex, neighbour)]))
        
        file.close()
        
    def printGraph(self):
        print ("Out graph")
        for i in self._dictOut:
            print (str(i) + ": ", end = '')
            for j in self._dictOut[i]:
                print("(%d, c = %d) " % (j, self._dictCost[(i, j)]), end = '')
            print()    
        
        print ()
        print ("In graph")
        for i in self._dictIn:
            print (str(i) + ": ", end = '')
            for j in self._dictIn[i]:
                print("(%d, c = %d) " % (j, self._dictCost[(j, i)]), end = '')
            print() 
            
    