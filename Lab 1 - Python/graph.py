import copy
import random

class Graph:
    def __init__(self):
        self._dictIn = {}
        self._dictOut = {}
        
        self._nrVertices = 0
        self._nrEdges = 0
        self._nextVertex = 0
        
    def _isVertex(self, index):
        return index in self._dictIn.keys() or index in self._dictOut.keys()    
        
    def _newVertex(self, index):
        self._dictIn[index] = []
        self._dictOut[index] = []     
        
    def _initEmptyGraph(self):
        for index in range(self._nrVertices):
            self._newVertex(index)    
        
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
            self._nrVertices = int(self._nrVertices)
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
                srcVertex, destVertex = line.split()
                srcVertex = int(srcVertex)
                destVertex = int(destVertex)
                
                self.addEdge(srcVertex, destVertex)
                
            except Exception as e:
                return str(e)
            
        file.close()
    
    def saveGraph(self):
        '''
        '''
        file = open("graph.txt", "w")
        
        file.write("%d %d\n" % (self._nrVertices, self._nrEdges))
        for vertex in self._dictOut.keys():
            for neighbour in self._dictOut[vertex]:
                file.write("%d %d\n" % (vertex, neighbour))
        
        file.close()
        
    def getVerticesCount(self):
        return self._nrVertices
    
    def getVertices(self):
        return list(self._dictIn.keys())
    
    def isEdge(self, srcVertex, destVertex):
        '''
        '''
        for vertex in self._dictOut[srcVertex]:
            if vertex == destVertex:
                return True
            
        return False
    
    def getInDegree(self, vertex):
        if self._isVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        return len(self._dictIn[vertex])
    
    def getOutDegree(self, vertex):
        if self._isVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        return len(self._dictOut[vertex])
        
    def getInEdges(self, vertex):
        if self._isVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        return self._dictIn[vertex]
    
    def getOutEdges(self, vertex):
        if self._isVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        return self._dictOut[vertex]  
        
    def addEdge(self, srcVertex, destVertex):
        '''
        '''
        #the edge already exists
        if self._isVertex(srcVertex) == False or self._isVertex(destVertex) == False:
            raise ValueError("Invalid vertices")
        if self.isEdge(srcVertex, destVertex) == True:
            raise ValueError("Edge already exists")
        
        self._dictIn[destVertex].append(srcVertex)
        self._dictOut[srcVertex].append(destVertex)
        self._nrEdges += 1
                
    def removeEdge(self, srcVertex, destVertex):
        '''
        '''
        if self._isVertex(srcVertex) == False or self._isVertex(destVertex) == False:
            raise ValueError("Invalid vertices")
        if self.isEdge(srcVertex, destVertex) == False:
            raise ValueError("Edge doesn't exist")
        
        self._dictOut[srcVertex].remove(destVertex)
        self._dictIn[destVertex].remove(srcVertex)
            
        self._nrEdges -= 1
    
    def addVertex(self):
        '''
        '''
        self._newVertex(self._nextVertex)
        self._nextVertex += 1
        self._nrVertices += 1
            
    def removeVertex(self, index):
        '''
        '''
        if self._isVertex(index) == False:
            raise ValueError("Vertex doesn't exist") 
        
        #remove all the edges which have as destination the crt vertex
        temp = self._dictIn[index][:]
        for vertex in temp:
            self.removeEdge(vertex, index)
            
        #remove all the edges which start from the crt vertex
        temp = self._dictOut[index][:]
        for vertex in temp:
            self.removeEdge(index, vertex)
        
        del self._dictIn[index]
        del self._dictOut[index]
        
        self._nrVertices -= 1
        
    def createCopy(self):
        return copy.deepcopy(self)
    
    def generateRandomGraph(self, nrVertices, nrEdges):
        self._nrVertices = nrVertices
        self._nrEdges = 0
        
        self._initEmptyGraph()
        
        while (self._nrEdges < nrEdges):
            srcVertex = random.randint(0, nrVertices - 1)
            destVertex = random.randint(0, nrVertices - 1)
            try:
                self.addEdge(srcVertex, destVertex)
            except:
                pass
        
        
        
            