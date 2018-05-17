import Data.List (sort)
import Data.Map (insert, empty)

data Vertex = Vertex String [Float] deriving (Ord, Show)
data Edge = Edge Float Vertex Vertex deriving (Eq, Ord, Show)

instance Eq Vertex where (==) (Vertex x _) (Vertex y _) = x == y

distance :: Vertex -> Vertex -> Float
distance (Vertex _ a) (Vertex _ b) =
  sqrt $ foldl (\acc (x,y) -> acc + (x-y)^2 ) 0 $
  zipWith (\f s -> (f,s) ) a b

edges [] = []
edges (x:xs) = (foldl (\acc y -> (Edge (distance x y) x y) : acc) [] xs) ++ edges xs

get_edges l = sort $ edges l

-- get_edges [ (Vertex "a" [0, 0]), (Vertex "b" [0, 1]), (Vertex "c" [0, 2]) ]

kruskal _ 0  = Data.Map.empty
kruskal [] _ = Data.Map.empty
kruskal ((Edge _ v y):rest) k = Data.Map.insert v 1 $ kruskal rest (k-1)
