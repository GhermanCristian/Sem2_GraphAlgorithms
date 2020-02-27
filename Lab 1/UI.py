from weightedGraph import WeightedGraph
from graph import Graph

class UI:
    def __init__(self):
        self.__graph = WeightedGraph(True)
    
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
    
    def start(self):
        print("""
            Insert the command: 
            0. Exit
            1. Get the number of vertices
            2. Parse the set of vertices
            3. Check if the edge exists
            4. Determine the in/ out degree of a vertex
            5. Parse the set of inbound edges of a vertex
            6. Parse the set of outbound edges of a vertex
            7. Get the endpoints of an edge
            8. Get the cost of an edge
            9. Modify the cost of an edge
            10. Add edge
            11. Remove edge
            12. Add vertex
            13. Remove vertex
            14. Make a copy
        """)
        while True:
            command = self.__readIntegers(1)[0]
            
            if command == 0:
                print ("Program has ended")
                return
            
            #get the number of vertices
            elif command == 1:
                print (self.__graph.getVerticesCount())
                
            #get the set of vertices
            elif command == 2:
                print (self.__graph.getVertices())
            
            #check if the edge exists
            elif command == 3:
                numbers = self.__readIntegers(2)
                print (self.__graph.isEdge(numbers[0], numbers[1]))
                
            #get the in/ out degree of a vertex
            elif command == 4:
                numbers = self.__readIntegers(1)
                print ("In degree = %d\nOut degree = %d" % (self.__graph.getInDegree(numbers[0]), self.__graph.getOutDegree(numbers[0])))
            
            #get the inbound edges for a vertex
            elif command == 5:
                numbers = self.__readIntegers(1)
                print ("Inbound edges")
                for vertex in self.__graph.getInEdges(numbers[0]):
                    print ("%d %d" % (vertex, numbers[0]))
            
            #get the outbound edges for a vertex
            elif command == 6:
                numbers = self.__readIntegers(1)
                print ("Outbound edges")
                for vertex in self.__graph.getOutEdges(numbers[0]):
                    print ("%d %d" % (numbers[0], vertex))
            
            #get the endpoints of an edge
            elif command == 7:
                pass
            
            #get the cost of an edge (identified by its endpoints)
            elif command == 8:
                numbers = self.__readIntegers(2)
                print (self.__graph.getEdgeCost(numbers[0], numbers[1]))
            
            #modify the cost of an edge (identified by its endpoints)
            elif command == 9:
                numbers = self.__readIntegers(3)
                print (self.__graph.modifyEdgeCost(numbers[0], numbers[1], numbers[2]))
            
            #add edge
            elif command == 10:
                numbers = self.__readIntegers(3)
                self.__graph.addEdge(numbers[0], numbers[1], numbers[2])
            
            #remove edge
            elif command == 11:
                numbers = self.__readIntegers(2)
                self.__graph.removeEdge(numbers[0], numbers[1]) 
                
            #add vertex
            elif command == 12:
                numbers = self.__readIntegers(1)
                self.__graph.addVertex(numbers[0])
                
            #remove vertex
            elif command == 13:
                numbers = self.__readIntegers(1)
                self.__graph.removeVertex(numbers[0])
                
            #make a copy of the graph
            elif command == 14:
                pass    
                
            #print the graph
            elif command == 15:
                self.__graph.printGraph()
                
            
        
        