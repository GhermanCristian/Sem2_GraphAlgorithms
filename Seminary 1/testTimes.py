import timeit
from texttable import Texttable
from graph1 import Graph1
from graph3 import Graph3
from graph2 import Graph2

class TestTimes:
    def __init__(self):
        pass
    
    def displayParseVertices(self):
        table = Texttable()
        table.add_row(['Nr elems', 'g1', 'g2', 'g3'])
        for term in [100, 1000, 10000, 100000, 1000000]:
            g1 = Graph1(term)
            g2 = Graph2(term)
            if term <= 10000:
                g3 = Graph3(term)
            
            startTime1 = timeit.default_timer()
            g1.iterateVertices()
            endTime1 = timeit.default_timer()
            
            startTime2 = timeit.default_timer()
            g2.iterateVertices()
            endTime2 = timeit.default_timer()
            
            if term <= 10000:
                startTime3 = timeit.default_timer()
                g3.iterateVertices()
                endTime3 = timeit.default_timer()
            else:
                startTime3 = 1
                endTime3 = 0
            
            table.add_row([term, endTime1 - startTime1, endTime2 - startTime2, endTime3 - startTime3])
            
        print(table.draw())
        
    def displayParseOut(self):
        table = Texttable()
        table.add_row(['Nr elems', 'g1', 'g2', 'g3'])
        for term in [100, 1000, 10000, 100000, 1000000]:
            g1 = Graph1(term)
            g2 = Graph2(term)
            if term <= 10000:
                g3 = Graph3(term)
            
            startTime1 = timeit.default_timer()
            for vertex in g1.iterateVertices():
                for anotherVertex in g1.iterateOutboundEdges(vertex):
                    pass
                
            endTime1 = timeit.default_timer()
            
            startTime2 = timeit.default_timer()
            for vertex in g2.iterateVertices():
                for anotherVertex in g2.iterateOutboundEdges(vertex):
                    pass
            endTime2 = timeit.default_timer()
            
            if term <= 10000:
                startTime3 = timeit.default_timer()
                for vertex in g3.iterateVertices():
                    for anotherVertex in g3.iterateOutboundEdges(vertex):
                        pass
                endTime3 = timeit.default_timer()
            else:
                startTime3 = 1
                endTime3 = 0
            
            table.add_row([term, endTime1 - startTime1, endTime2 - startTime2, endTime3 - startTime3])
            
        print(table.draw())
        
    def displayParseIn(self):
        table = Texttable()
        table.add_row(['Nr elems', 'g1', 'g2', 'g3'])
        for term in [100, 1000, 10000, 100000, 1000000]:
            g1 = Graph1(term)
            g2 = Graph2(term)
            if term <= 10000:
                g3 = Graph3(term)
            
            startTime1 = timeit.default_timer()
            for vertex in g1.iterateVertices():
                for x in g1.iterateInboundEdges(vertex):
                    pass
            endTime1 = timeit.default_timer()
            
            startTime2 = timeit.default_timer()
            for vertex in g2.iterateVertices():
                for x in g2.iterateInboundEdges(vertex):
                    pass
            endTime2 = timeit.default_timer()
            
            if term <= 10000:
                startTime3 = timeit.default_timer()
                for vertex in g3.iterateVertices():
                    for x in g3.iterateInboundEdges(vertex):
                        pass
                endTime3 = timeit.default_timer()
            else:
                startTime3 = 1
                endTime3 = 0
                
            print([term, endTime1 - startTime1, endTime2 - startTime2, endTime3 - startTime3])
            table.add_row([term, endTime1 - startTime1, endTime2 - startTime2, endTime3 - startTime3])
            
        print(table.draw())
        
        
        
        