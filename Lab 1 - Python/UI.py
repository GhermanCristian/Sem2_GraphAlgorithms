from weightedGraph import WeightedGraph

class UI:
    def __init__(self):
        self.__graph = WeightedGraph()
    
    def __readIntegers(self, nrIntegers):
        numbers = input("Please insert the numbers: ")
        
        try:
            numbers = numbers.split()
            if len(numbers) != nrIntegers:
                raise ValueError("Incorrect no. of parameters")
        except Exception as e:
            return str(e)
        
        for i in range(nrIntegers):
            numbers[i] = int(numbers[i])
        return numbers
    
    def __printEdges(self, srcVertex, neighbourList, direction):
        for nbr in neighbourList:
            if direction == 1:
                print ("%d -> %d" % (srcVertex, nbr))
            else: #direction = 0
                print ("%d -> %d" % (nbr, srcVertex))
                
    def __printVertices(self, vertexGenerator):
        for vertex in vertexGenerator:
            print (vertex, end = " ")
        print ()
    
    def start(self):
        print("""
            Insert the command: 
            0. Exit
            1. Get the number of vertices
            2. Parse the set of vertices
            3. Check if the edge exists
            4. Determine the in degree of a vertex
            5. Determine the out degree of a vertex
            6. Parse the set of inbound edges of a vertex
            7. Parse the set of outbound edges of a vertex
            8. Get the endpoints of an edge
            9. Get the cost of an edge
            10. Modify the cost of an edge
            11. Add edge
            12. Remove edge
            13. Add vertex
            14. Remove vertex
            15. Make a copy of the graph
            16. Print the graph
            17. Load the graph from a file
            18. Save the graph to a file
            19. Generate a random graph
        """)
        
        commandList = [
            0,                              # 0 params (exit)
            self.__graph.getVerticesCount,  # 0 params
            self.__graph.getVertices,       # 0 params
            self.__graph.isEdge,            # 2 params
            self.__graph.getInDegree,       # 1 params
            self.__graph.getOutDegree,      # 1 params
            self.__graph.getInEdges,        # 1 params     
            self.__graph.getOutEdges,       # 1 params
            8,                              # 0 params (not implemented yet)
            self.__graph.getEdgeCost,       # 2 params
            self.__graph.modifyEdgeCost,    # 3 params
            self.__graph.addEdge,           # 3 params
            self.__graph.removeEdge,        # 2 params
            self.__graph.addVertex,         # 0 params
            self.__graph.removeVertex,      # 1 params
            self.__graph.createCopy,        # 0 params
            self.__graph.printGraph,        # 0 params
            self.__graph.loadGraph,         # 0 params
            self.__graph.saveGraph,         # 0 params
            self.__graph.generateRandomGraph# 2 params
        ]
        
        #no of parameters for each command
        noOfParameters = [0, 0, 0, 2, 1, 1, 1, 1, 0, 2, 3, 3, 2, 0, 1, 0, 0, 0, 0, 2]
        
        while True:
            command = self.__readIntegers(1)[0]
            
            if command == 0:
                print ("Program has ended")
                return
            
            try:
                if noOfParameters[command]:
                    params = self.__readIntegers(noOfParameters[command])
                
                if noOfParameters[command] == 0:
                    result = commandList[command]()
                elif noOfParameters[command] == 1:
                    result = commandList[command](params[0])
                elif noOfParameters[command] == 2:
                    result = commandList[command](params[0], params[1])
                elif noOfParameters[command] == 3:
                    result = commandList[command](params[0], params[1], params[2])
                    
                if command == 2:
                    self.__printVertices(result)
                    
                if command in [6, 7]:
                    self.__printEdges(params[0], result, command == 7)
                    
                elif command in [1, 3, 4, 5, 9]:
                    print (result)
                    
            except Exception as e:
                print (str(e))
                
            
        
        