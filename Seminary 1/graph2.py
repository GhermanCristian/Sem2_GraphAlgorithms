import random

class Graph2:
    def __init__(self, nrVertices):
        self._inEdges = {}
        self._outEdges = {}
        self._nrVertices = 0
        self._nrEdges = 0
        
        self.generateRandomGraph(nrVertices, nrVertices * 10)
        
    def addVertex(self):
        self._outEdges[self._nrVertices] = []
        self._inEdges[self._nrVertices] = []
        self._nrVertices += 1
        
    def __isEdge(self, srcVertex, destVertex):
        return destVertex in self._outEdges[srcVertex]    
        
    def addEdge(self, srcVertex, destVertex):
        self._outEdges[srcVertex].append(destVertex)
        self._inEdges[destVertex].append(srcVertex)
        self._nrEdges += 1
        
    def iterateVertices(self):
        for vertex in self._outEdges.keys():
            yield vertex
            
    def iterateInboundEdges(self, vertex):        
        for neighbour in self._inEdges[vertex]:
            yield neighbour

    def iterateOutboundEdges(self, vertex):
        for neighbour in self._outEdges[vertex]:
            yield neighbour
            
    def generateRandomGraph(self, nrVertices, nrEdges):
        for i in range(nrVertices):
            self.addVertex()
            
        while self._nrEdges < nrEdges:
            srcVertex = random.randint(0, nrVertices - 1)
            destVertex = random.randint(0, nrVertices - 1)
            if not self.__isEdge(srcVertex, destVertex):
                self.addEdge(srcVertex, destVertex)


    