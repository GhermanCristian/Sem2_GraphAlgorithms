from graph import Graph, random

class WeightedGraph(Graph):
    def __init__(self):
        self._dictCost = {}
        Graph.__init__(self)
    
    def _initEmptyGraph(self):
        Graph._initEmptyGraph(self)
        self._dictCost.clear()
    
    def loadGraph(self):
        '''
        Loads a graph (and its number of vertices/ edges) from a text file
        @param:
            - None
        @return:
            - None
        '''
        file = open("graph.txt", "r")
        
        line = file.readline()
        try:
            self._nrVertices, self._nrEdges = line.split()
            self._nrVertices = self._nextVertex = int(self._nrVertices)
            #self._nrEdges = int(self._nrEdges)
            self._nrEdges = 0
        except Exception as e:
            return (str(e))
        
        self._initEmptyGraph()
        
        while True:
            line = file.readline()
            
            if line == "":
                break
            
            line = line[:-1]
            try:
                srcVertex, destVertex, cost = line.split()
                srcVertex = int(srcVertex)
                destVertex = int(destVertex)
                cost = int(cost)
                
                self.addEdge(srcVertex, destVertex, cost)
                
            except Exception as e:
                return str(e)
            
        file.close()
        
    def addEdge(self, srcVertex, destVertex, cost):
        '''
        Adds a new edge to the graph
        @param:
            - srcVertex = integer = source vertex
            - destVertex = integer = destination vertex
            - cost = integer = cost of the edge
        @return:
            - ValueError, if either of the vertices doesn't exist or if the edge already exists
        '''
        #the 'parent' function checks for the validity of the operation, no need to do it here
        Graph.addEdge(self, srcVertex, destVertex)
        
        self._dictCost[(srcVertex, destVertex)] = cost
    
    def removeEdge(self, srcVertex, destVertex):
        '''
        Removes a given edge from the graph
        @param:
            - srcVertex = integer = source vertex
            - destVertex = integer = destination vertex
        @return:
            - None
        @raise:
            - ValueError, if either of the vertices doesn't exist or if the edge already exists
        '''
        #the 'parent' function checks for the validity of the operation, no need to do it here
        Graph.removeEdge(self, srcVertex, destVertex)
        
        del self._dictCost[(srcVertex, destVertex)]
        
    def removeVertex(self, index):
        '''
        Removes a given vertex from the graph
        @param:
            - index = integer = the vertex we want to delete
        @return:
            - None
        @raise:
            - ValueError, if the vertex doesn't exist
        '''
        #the 'parent' function checks for the existance of the vertex, no need to also do it here
        Graph.removeVertex(self, index)
        
        #remove all the pairs which contain one of the nodes
        for pair in self._dictCost.keys():
            if pair[0] == index or pair[1] == index:
                del self._dictCost[pair]    
        
    def getEdgeCost(self, srcVertex, destVertex):
        '''
        Determiness the cost of a given edge
        @param:
            - srcVertex = integer = source vertex
            - destVertex = integer = destination vertex
            - newCost = integer = the new cost of the edge
        @return:
            - The cost of the edge = integer
        @raise:
            - ValueError, if the edge doesn't exist
        '''
        if self.isEdge(srcVertex, destVertex) == False:
            raise ValueError("Edge doesn't exist")
        return self._dictCost[(srcVertex, destVertex)]
    
    def modifyEdgeCost(self, srcVertex, destVertex, newCost):
        '''
        Modifies the cost of a given edge
        @param:
            - srcVertex = integer = source vertex
            - destVertex = integer = destination vertex
            - newCost = integer = the new cost of the edge
        @return:
            - None
        @raise:
            - ValueError, if the edge doesn't exist
        '''
        if self.isEdge(srcVertex, destVertex) == False:
            raise ValueError("Edge doesn't exist")
        self._dictCost[(srcVertex, destVertex)] = newCost
    
    def saveGraph(self):
        '''
        Writes the graph to a file
        @param:
            - None
        @return:
            - None
        '''
        file = open("graph.txt", "w")
        
        file.write("%d %d\n" % (self._nrVertices, self._nrEdges))
        for vertex in self._dictOut.keys():
            for neighbour in self._dictOut[vertex]:
                file.write("%d %d %d\n" % (vertex, neighbour, self._dictCost[(vertex, neighbour)]))
        
        file.close()
        
    def generateRandomGraph(self, nrVertices, nrEdges):
        '''
        Generates a random graph with a given number of vertices and edges
        @param:
            - nrVertices = the number of vertices of the graph
            - nrEdges = the number of edges of the graph
        @return:
            - None
        '''
        self._nrVertices = self._nextVertex = nrVertices
        self._nrEdges = 0
        
        self._initEmptyGraph()
        
        while (self._nrEdges < nrEdges):
            srcVertex = random.randint(0, nrVertices - 1)
            destVertex = random.randint(0, nrVertices - 1)
            try:
                cost = random.randint(-100, 100)
                self.addEdge(srcVertex, destVertex, cost)
            except:
                pass

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
            
    