import copy
import random

class Graph:
    def __init__(self):
        self._dictIn = {}
        self._dictOut = {}
        
        self._nrVertices = 0
        self._nrEdges = 0
        self._nextVertex = 0
        
    def _isActiveVertex(self, index):
        '''
        Checks if a given vertex is still active (hasn't been removed)
        @param:
            - index = integer, the vertex we check
        @return:
            - The truth value of the condition
        '''
        return index in self._dictIn.keys() or index in self._dictOut.keys()    
        
    def _newVertex(self, index):
        '''
        Adds an empty (isolated) vertex at a given position
        @param:
            - index = integer, the vertex we want to add
        @return:
            - None
        '''
        self._dictIn[index] = []
        self._dictOut[index] = []     
        
    def _initEmptyGraph(self):
        '''
        Initialises an empty graph with a given number of vertices
        @param:
            - None
        @return:
            - None
        '''
        self._dictIn.clear()
        self._dictOut.clear()
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
            self._nrVertices = self._nextVertex = int(self._nrVertices)
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
                file.write("%d %d\n" % (vertex, neighbour))
        
        file.close()
        
    def getVerticesCount(self):
        '''
        Determines the number of (active) vertices in the graph
        @param:
            - None
        @return:
            - self._nrVertices = integer = the number of active vertices in the graph
        '''
        return self._nrVertices
    
    def getVertices(self):
        '''
        Iterates over the (active) vertices in the graph
        @param:
            - None
        @return:
            - A list of the active vertices in the graph
        '''
        for vertex in self._dictIn.keys():
            yield vertex
    
    def isEdge(self, srcVertex, destVertex):
        '''
        Checks if an edge exists
        @param:
            - srcVertex = integer = source vertex
            - destVertex = integer = destination vertex
        @return:
            - The truth value of the condition
        '''
        for vertex in self._dictOut[srcVertex]:
            if vertex == destVertex:
                return True
            
        return False
    
    def getInDegree(self, vertex):
        '''
        Determines the in degree of a vertex
        @param:
            - vertex = integer = the vertex we check
        @return:
            - The in degree of the vertex = integer
        @raise:
            - ValueError, if the vertex doesn't exist
        '''
        if self._isActiveVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        return len(self._dictIn[vertex])
    
    def getOutDegree(self, vertex):
        '''
        Determines the out degree of a vertex
        @param:
            - vertex = integer = the vertex we check
        @return:
            - The out degree of the vertex = integer
        @raise:
            - ValueError, if the vertex doesn't exist
        '''
        if self._isActiveVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        return len(self._dictOut[vertex])
        
    def getInEdges(self, vertex):
        '''
        Determines the inbound edges of a vertex
        @param:
            - vertex = integer = the vertex we check
        @return:
            - A list of the inbound edges of this vertex
        @raise:
            - ValueError, if the vertex doesn't exist
        '''
        if self._isActiveVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        for neighbor in self._dictIn[vertex]:
            yield neighbor
    
    def getOutEdges(self, vertex):
        '''
        Determines the outbound edges of a vertex
        @param:
            - vertex = integer = the vertex we check
        @return:
            - A list of the outbound edges of this vertex
        @raise:
            - ValueError, if the vertex doesn't exist
        '''
        if self._isActiveVertex(vertex) == False:
            raise ValueError("Vertex doesn't exist")
        
        for neighbor in self._dictOut[vertex]:
            yield neighbor
        
    def addEdge(self, srcVertex, destVertex):
        '''
        Adds a new edge to the graph
        @param:
            - srcVertex = integer = source vertex
            - destVertex = integer = destination vertex
        @return:
            - None
        @raise:
            - ValueError, if either of the vertices doesn't exist or if the edge already exists
        '''
        #the edge already exists
        if self._isActiveVertex(srcVertex) == False or self._isActiveVertex(destVertex) == False:
            raise ValueError("Invalid vertices")
        if self.isEdge(srcVertex, destVertex) == True:
            raise ValueError("Edge already exists")
        
        self._dictIn[destVertex].append(srcVertex)
        self._dictOut[srcVertex].append(destVertex)
        self._nrEdges += 1
                
    def removeEdge(self, srcVertex, destVertex):
        '''
        Removes an edge from the graph
        @param:
            - srcVertex = integer = source vertex
            - destVertex = integer = destination vertex
        @return:
            - None
        @raise:
            - ValueError, if either of the vertices doesn't exist or if the edge already exists
        '''
        if self._isActiveVertex(srcVertex) == False or self._isActiveVertex(destVertex) == False:
            raise ValueError("Invalid vertices")
        if self.isEdge(srcVertex, destVertex) == False:
            raise ValueError("Edge doesn't exist")
        
        self._dictOut[srcVertex].remove(destVertex)
        self._dictIn[destVertex].remove(srcVertex)
            
        self._nrEdges -= 1
    
    def addVertex(self):
        '''
        Adds a new vertex
        @param:
            - None
        @return:
            - None
        '''
        self._newVertex(self._nextVertex)
        self._nextVertex += 1
        self._nrVertices += 1
            
    def removeVertex(self, index):
        '''
        Removes a given vertex
        @param:
            - index = integer = the vertex we want to remove
        @return:
            - None
        @raise:
            - ValueError, if the vertex doesn't exist
        '''
        if self._isActiveVertex(index) == False:
            raise ValueError("Vertex doesn't exist") 
        
        #remove all the edges which have as destination the crt vertex
        #we have to create a copy of this list because removeEdge will affect it and we might lose some vertices in the process
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
        '''
        Creates a copy of the current graph
        @param:
            - None
        @return:
            - A copy of the current graph
        '''
        return copy.deepcopy(self)
    
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
                self.addEdge(srcVertex, destVertex)
            except:
                pass
        
        
        
            