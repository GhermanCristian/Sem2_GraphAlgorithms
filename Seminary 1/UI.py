from graph1 import Graph1
from graph2 import Graph2
from graph3 import Graph3

#the UI is used for testing small graphs, the actual results were obtained using testTimes (see main)
class UI:
    def __init__(self):
        self._graph = Graph1(10)
        #self._graph = Graph2()
        #self._graph = Graph3(5)
    
    def start(self):
        print ("0. Exit")
        print ("1. Parse inbound edges for a vertex")
        print ("2. Parse all the vertices")
        print ("3. Print the entire graph")
        
        while True:
            command = input("Insert the command: ")
            
            if command == '0':
                print ("Program has ended")
                return
            
            if command == '1':
                vertex = input("Insert the vertex: ")
                for x in self._graph.iterateInboundEdges(int(vertex)):
                    print (x)
                print ("done")
            
            elif command == '2':
                for x in self._graph.iterateVertices():
                    print (x)
                print ("done")
                    
            elif command == '3':
                for x in self._graph.iterateVertices():
                    line = str(x) + " :"
                    for out in self._graph.iterateOutboundEdges(x):
                        line = line + " " + str(out)
                    print (line)
    
    