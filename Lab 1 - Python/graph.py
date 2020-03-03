import copy

class Graph:
    def __init__(self, isOriented, weighted = False):
        self._dictIn = {}
        self._dictOut = {}
        
        self._isOriented = isOriented
        self._nrVertices = -1
        self._nrEdges = -1
        
        self.loadGraph(weighted)
        
    def _isVertex(self, index):
        return index in self._dictIn.keys() or index in self._dictOut.keys()    
        
    def _newVertex(self, index):
        self._dictIn[index] = []
        self._dictOut[index] = []     
        
    def _initEmptyGraph(self):
        for index in range(self._nrVertices):
            self._newVertex(index)    
        
    def loadGraph(self, weighted):
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
                srcVertex, destVertex, cost = line.split()
                srcVertex = int(srcVertex)
                destVertex = int(destVertex)
                cost = int(cost)
                
                if weighted == False:
                    self.addEdge(srcVertex, destVertex)
                else:
                    self.addEdge(srcVertex, destVertex, cost)
                
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
        
        if self._isOriented == False:
            self._dictIn[srcVertex].append(destVertex)
            self._dictOut[destVertex].append(srcVertex)
            self._nrEdges += 1
                
    def removeEdge(self, srcVertex, destVertex):
        '''
        '''
        if self._isVertex(srcVertex) == False or self._isVertex(destVertex) == False:
            raise ValueError("Invalid vertices")
        if self.isEdge(srcVertex, destVertex) == False:
            raise ValueError("Edge doesn't exist")
        
        for index in range(len(self._dictOut[srcVertex])):
            if self._dictOut[srcVertex][index] == destVertex:
                self._dictOut[srcVertex].pop(index)
                break
            
        for index in range(len(self._dictIn[destVertex])):
            if self._dictIn[destVertex][index] == srcVertex:
                self._dictIn[destVertex].pop(index)
                break 
            
        self._nrEdges -= 1
    
    def addVertex(self, index):
        '''
        '''
        if self._isVertex(index) == True:
            raise ValueError("Vertex already exists")
        
        self._newVertex(index)
        if index >= self._nrVertices:
            self._nrVertices = index + 1 
            
    def removeVertex(self, index):
        '''
        '''
        if self._isVertex(index) == False:
            raise ValueError("Vertex doesn't exist") 
        
        #remove all the edges which have as destination the crt vertex
        #no need to do this for dictOut[index], because we'll just delete that altogether
        for vertex in self._dictIn[index]:
            self.removeEdge(vertex, index)
        
        del self._dictIn[index]
        del self._dictOut[index]
        
        if index == self._nrVertices - 1:
            self._nrVertices -= 1
        
    def createCopy(self):
        return copy.deepcopy(self) 
        
        
            