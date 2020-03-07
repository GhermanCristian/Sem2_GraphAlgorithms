import unittest
from weightedGraph import WeightedGraph

class Test(unittest.TestCase):
    def testAddVertex(self):
        self.graph = WeightedGraph()
        
        self.graph.addVertex()
        self.assertEqual(self.graph.getVerticesCount(), 1)
        self.assertEqual(self.graph.getInDegree(0), 0)
        self.assertEqual(self.graph.getOutDegree(0), 0)
        self.assertEqual(self.graph.getVertices(), [0])
        
        self.graph.addVertex()
        self.assertEqual(self.graph.getVerticesCount(), 2)
        self.assertEqual(self.graph.getInDegree(1), 0)
        self.assertEqual(self.graph.getOutDegree(1), 0)
        self.assertEqual(self.graph.getVertices(), [0, 1])
        
        self.graph.addVertex()
        self.assertEqual(self.graph.getVerticesCount(), 3)
        self.assertEqual(self.graph.getInDegree(1), 0)
        self.assertEqual(self.graph.getOutDegree(1), 0)
        self.assertEqual(self.graph.getVertices(), [0, 1, 2])
        
    #version without edges
    def testRemoveVertex1(self):
        self.graph = WeightedGraph()
        
        self.graph.addVertex()
        self.graph.addVertex()
        self.graph.addVertex()
        self.assertEqual(self.graph.getVerticesCount(), 3)
        self.assertEqual(self.graph.getInDegree(1), 0)
        self.assertEqual(self.graph.getOutDegree(1), 0)
        self.assertEqual(self.graph.getVertices(), [0, 1, 2])
        
        self.graph.removeVertex(1)
        self.assertEqual(self.graph.getVerticesCount(), 2)
        self.assertEqual(self.graph.getVertices(), [0, 2])
        self.assertRaises(ValueError, self.graph.removeVertex, 1)
        
        self.graph.addVertex()
        self.assertEqual(self.graph.getVerticesCount(), 3)
        self.assertEqual(self.graph.getVertices(), [0, 2, 3])
        
        self.graph.removeVertex(3)
        self.assertEqual(self.graph.getVerticesCount(), 2)
        self.assertEqual(self.graph.getVertices(), [0, 2])
        self.assertRaises(ValueError, self.graph.removeVertex, 3)
        
        self.graph.addVertex()
        self.assertEqual(self.graph.getVerticesCount(), 3)
        self.assertEqual(self.graph.getVertices(), [0, 2, 4])
        
        self.graph.removeVertex(2)
        self.assertEqual(self.graph.getVerticesCount(), 2)
        self.assertEqual(self.graph.getVertices(), [0, 4])
        self.assertRaises(ValueError, self.graph.removeVertex, 2)
        
        self.graph.removeVertex(0)
        self.assertEqual(self.graph.getVerticesCount(), 1)
        self.assertEqual(self.graph.getVertices(), [4])
        self.assertRaises(ValueError, self.graph.removeVertex, 0)
        
        self.graph.removeVertex(4)
        self.assertEqual(self.graph.getVerticesCount(), 0)
        self.assertEqual(self.graph.getVertices(), [])
        self.assertRaises(ValueError, self.graph.removeVertex, 4)
        


        
