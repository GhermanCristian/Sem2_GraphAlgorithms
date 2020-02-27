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
        
    def getEdgeCost(self, srcVertex, destVertex):
        if self.isEdge(srcVertex, destVertex) == False:
            return 
        return self._dictCost[(srcVertex, destVertex)]
    
    def modifyEdgeCost(self, srcVertex, destVertex, newCost):
        if self.isEdge(srcVertex, destVertex) == False:
            return
        self._dictCost[(srcVertex, destVertex)] = newCost
        
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
            
    