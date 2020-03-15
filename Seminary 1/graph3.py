import random

class Graph3:
    def __init__(self, nrVertices):
        self._adjMatrix = []
        self._nrVertices = 0
        self._nrEdges = 0
        
        self.generateRandomGraph(nrVertices, nrVertices * 10)
    
    def __initEmptyGraph(self):
        for i in range(self._nrVertices):
            self._adjMatrix.append([])
            for j in range(self._nrVertices):
                self._adjMatrix[i].append(False)
        
    def __isEdge(self, srcVertex, destVertex):
        return self._adjMatrix[srcVertex][destVertex] == True
    
    def addEdge(self, srcVertex, destVertex):
        self._adjMatrix[srcVertex][destVertex] = True
        self._nrEdges += 1
        
    def iterateVertices(self):
        return range(self._nrVertices)
    
    def iterateInboundEdges(self, vertex):        
        for i in range(self._nrVertices):
            yield self._adjMatrix[i][vertex]

    def iterateOutboundEdges(self, vertex):
        for i in range(self._nrVertices):
            yield self._adjMatrix[vertex][i]
            
    def generateRandomGraph(self, nrVertices, nrEdges):
        self._nrVertices = nrVertices
        self.__initEmptyGraph()
            
        while self._nrEdges < nrEdges:
            srcVertex = random.randint(0, nrVertices - 1)
            destVertex = random.randint(0, nrVertices - 1)
            if not self.__isEdge(srcVertex, destVertex):
                self.addEdge(srcVertex, destVertex)
